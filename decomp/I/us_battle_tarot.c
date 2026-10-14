/* Section I -- cleaned Ghidra output of the retail tarot-card system in SH2US_BATTLE.BIN.
 *   BtlTarotSelect (BtlMenu-style class; ct 0x5718b0, dt 0x5725b0, Destruct 0x572780, Polling 0x572850, MakePacket 0x576820): the card pick screen.
 *   BtlTarotEffect (ct 0x57a510, dt 0x57acf0, Destruct 0x57ae50, Polling 0x57af20, MakePacket 0x57b2d0, EndSet 0x57d9f0): the card activation effect.
 *   CBattle::TarotApplyCard 0x6a0c30 / TarotRevertCard 0x69e160: apply or undo the card's stat modification on the party (bTarotFlags +0x407c,
 *   nTarotCard +0x407e, nTarotParam +0x4080).
 * Analysis output, not compilable source.  Field names as in us_battle_phases.c. */

/* ---- 0x005718b0  __ct__13BtlTarotSelectFv  (size 0xd00) ----
 *   nStep values: []
 *   nPhase targets: ['0x43e880']
 *   bState targets: [] */
undefined8
__ct__13BtlTarotSelectFv
          (undefined8 this,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5)

{
  undefined8 uVar1;
  bool bVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 *puVar10;
  int iVar11;
  int this;
  uint uVar13;
  int iVar14;
  float fVar15;
  undefined1 in_vf0 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auStack_540 [64];
  undefined1 auStack_500 [64];
  undefined4 uStack_4c0;
  undefined4 uStack_4bc;
  undefined4 uStack_4b8;
  undefined4 uStack_4b4;
  undefined4 uStack_4b0;
  undefined4 uStack_4ac;
  undefined4 uStack_4a8;
  undefined4 uStack_4a4;
  undefined4 uStack_4a0;
  undefined4 uStack_49c;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined4 uStack_490;
  undefined4 uStack_48c;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined4 uStack_480;
  undefined4 uStack_47c;
  undefined4 uStack_478;
  undefined4 uStack_474;
  int iStack_470;
  int iStack_46c;
  undefined4 auStack_460 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined4 uStack_400;
  undefined4 uStack_3fc;
  undefined4 uStack_3f8;
  undefined4 uStack_3f4;
  undefined1 auStack_3f0 [576];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [240];
  undefined4 uStack_80;
  undefined4 uStack_7c;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(this,param_2,param_3);
  /* this = this */
  *(undefined4 *)(this + 0x14) = 0x43e870;
  this->nPhase = 0x43e880;
  *(undefined4 *)(this + 0x34) = 0x43e890;
  puVar8 = (undefined4 *)(this + 0x80);
  do {
    *puVar8 = in_zero_lo;
    puVar8[1] = in_zero_hi;
    puVar8[2] = in_zero_udw;
    puVar8[3] = in_register_0000000c;
    puVar8 = puVar8 + 4;
  } while (puVar8 != (undefined4 *)(this + 0xb0));
  *(undefined4 *)(this + 0xb0) = in_zero_lo;
  *(undefined4 *)(this + 0xb4) = in_zero_hi;
  *(undefined4 *)(this + 0xb8) = in_zero_udw;
  *(undefined4 *)(this + 0xbc) = in_register_0000000c;
  *(undefined4 *)(this + 0xd0) = in_zero_lo;
  *(undefined4 *)(this + 0xd4) = in_zero_hi;
  *(undefined4 *)(this + 0xd8) = in_zero_udw;
  *(undefined4 *)(this + 0xdc) = in_register_0000000c;
  *(undefined4 *)(this + 0xe0) = in_zero_lo;
  *(undefined4 *)(this + 0xe4) = in_zero_hi;
  *(undefined4 *)(this + 0xe8) = in_zero_udw;
  *(undefined4 *)(this + 0xec) = in_register_0000000c;
  *(undefined4 *)(this + 0x40) = 0;
  this->nCmd0_target = (int)param_2;
  this->nCmd1 = (int)param_3;
  this->nCmdKind = 0x19;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  this->nCmdMask = 0;
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  _sqc2(in_vf0);
  _sqc2(auVar16);
  _sqc2(auVar17);
  _sqc2(auVar18);
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar16);
  auStack_30 = _sqc2(auVar17);
  auStack_40 = _sqc2(auVar18);
  sceVu0RotMatrixX(0x3f490fdb,auStack_40,auStack_40);
  __amu__7FVectorFf(0x3f19999a,auStack_40);
  __amu__7FVectorFf(0x3f19999a,auStack_30);
  __amu__7FVectorFf(0x3f19999a,auStack_20);
  uStack_480 = 0;
  uStack_47c = 0;
  uStack_478 = 0xc4c80000;
  uStack_474 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&fStack_50,auStack_40,&uStack_480);
  *(float *)(this + 0x68) = -fStack_4c;
  *(float *)(this + 0x6c) = -fStack_48;
  *(undefined2 *)(this + 0x5c) = 0;
  *(byte *)(this + 0x5c) = *(byte *)(this + 0x5c) & 0xf8 | (byte)param_5 & 7;
  *(undefined1 *)(this + 0x5e) = 0;
  *(undefined1 *)(this + 0x5f) = 0;
  uVar3 = GetTimer__7SysToolFv();
  this->nShortcutTarget = uVar3;
  *(undefined4 *)(this + 100) = 0;
  uStack_490 = 0;
  uStack_48c = 0xc3200000;
  uStack_488 = 0xc4000000;
  uStack_484 = 0x3f800000;
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 0xd4) = 0xc3200000;
  *(undefined4 *)(this + 0xd8) = 0xc4000000;
  *(undefined4 *)(this + 0xdc) = 0x3f800000;
  uStack_4a0 = 0;
  uStack_49c = 0;
  uStack_498 = 0;
  uStack_494 = 0x3f800000;
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe4) = 0;
  *(undefined4 *)(this + 0xe8) = 0;
  *(undefined4 *)(this + 0xec) = 0x3f800000;
  *(undefined4 *)(this + 0xf0) = 0x3fc00000;
  *(undefined4 *)(this + 0xf4) = 0;
  *(undefined4 *)(this + 0xf8) = 0;
  iVar4 = GetRegCnt__9RegDatApiFii(0x44,0xffffffffffffffff);
  *(undefined4 *)(this + 0x70) = 0;
  for (uVar13 = 0; (int)uVar13 < iVar4; uVar13 = uVar13 + 1) {
    if ((uVar13 != 0x14) || (param_5 == 0)) {
      uVar9 = uVar13 & 7;
      if (((int)uVar13 < 0) && (uVar9 != 0)) {
        uVar9 = uVar9 - 8;
      }
      if (((uint)*(byte *)(iGpffff83b4 + ((int)uVar13 >> 3) + 0xf3f) & 1 << (uVar9 & 0x1f)) != 0) {
        *(int *)(this + 0x70) = *(int *)(this + 0x70) + 1;
      }
    }
  }
  __ct__9GsxCameraFv(auStack_3f0);
  uStack_80 = 0x41200000;
  uStack_7c = 0x46fa0000;
  SetViewMatrix__9GsxCameraFfffff(0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,auStack_3f0);
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_180 = _sqc2(in_vf0);
  auStack_190 = _sqc2(auVar16);
  auStack_1a0 = _sqc2(auVar17);
  auStack_1b0 = _sqc2(auVar18);
  uStack_400 = 0;
  uStack_3fc = 0;
  uStack_3f8 = 0xc4000000;
  uStack_3f4 = 0x3f800000;
  uStack_4b0 = 0;
  uStack_4ac = 0x3f800000;
  uStack_4a8 = 0;
  uStack_4a4 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_410,auStack_1b0,&uStack_4b0);
  uStack_4c0 = 0;
  uStack_4bc = 0;
  uStack_4b8 = 0x3f800000;
  uStack_4b4 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_420,auStack_1b0,&uStack_4c0);
  sceVu0CameraMatrix(auStack_170,&uStack_400,auStack_420,auStack_410);
  GetViewScreenMatrix__9GsxCameraFv(auStack_500,auStack_3f0);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    *(undefined4 *)(this + iVar4 * 0x10 + 0x100) = *(undefined4 *)(auStack_40 + iVar4 * 0x10);
    *(undefined4 *)(this + iVar4 * 0x10 + 0x104) = *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 4);
    *(undefined4 *)(this + iVar4 * 0x10 + 0x108) = *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 8);
    *(undefined4 *)(this + iVar4 * 0x10 + 0x10c) =
         *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 0xc);
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_540,uGpffff84bc);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    auStack_460[iVar4 * 4] = *(undefined4 *)(auStack_40 + iVar4 * 0x10);
    auStack_460[iVar4 * 4 + 1] = *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 4);
    auStack_460[iVar4 * 4 + 2] = *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 8);
    auStack_460[iVar4 * 4 + 3] = *(undefined4 *)(auStack_40 + iVar4 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(&iStack_470,auStack_460,param_4,1,0);
  fStack_4c = (float)iStack_46c / 16.0 - 2048.0;
  fStack_50 = (float)iStack_470 / 16.0 - 2048.0;
  fStack_48 = 0.0;
  uStack_44 = 0x3f800000;
  __amu__7FVectorFf((*(float *)(this + 0x6c) + 512.0) / 512.0,&fStack_50);
  fStack_48 = *(float *)(this + 0x6c);
  this->flTurnPush = fStack_50;
  *(float *)(this + 0x94) = fStack_4c;
  *(float *)(this + 0x98) = fStack_48;
  *(undefined4 *)(this + 0x9c) = uStack_44;
  *(int *)(this + 0x80) = (int)this->flTurnPush;
  this->flMenuTimer = (int)((ulong)this->flTurnPush >> 0x20);
  this->flMenuTimer2 = *(undefined4 *)(this + 0x98);
  *(undefined4 *)(this + 0x8c) = *(undefined4 *)(this + 0x9c);
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa4) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xac) = 0x3f800000;
  *(undefined4 *)(this + 0xb0) = 0x3f490fdb;
  *(undefined4 *)(this + 0xb4) = 0;
  *(undefined4 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xbc) = 0x3f800000;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  *(undefined4 *)(this + 0x74) = 0;
  bVar2 = false;
  if (((*(char *)(iGpffff83b4 + 0x2ab) == 'E') || (*(char *)(iGpffff83b4 + 0x2ac) == 'E')) ||
     (*(char *)(iGpffff83b4 + 0x2ad) == 'E')) {
    bVar2 = true;
  }
  if (((*(byte *)(this + 0x5c) & 7) == 2) || ((*(byte *)(this + 0x5c) & 7) == 4)) {
    bVar2 = true;
  }
  *(undefined4 *)(this + 0x144) = 0;
  *(undefined4 *)(this + 0x140) = 0;
  iVar5 = rand();
  iVar4 = *(int *)(this + 0x70);
  fVar15 = 0.0;
  do {
    for (iVar14 = 0; iVar14 < *(int *)(this + 0x70); iVar14 = iVar14 + 1) {
      lVar6 = __nw__FUi(0x280);
      puVar8 = (undefined4 *)lVar6;
      if (lVar6 != 0) {
        puVar8[4] = in_zero_lo;
        puVar8[5] = in_zero_hi;
        puVar8[6] = in_zero_udw;
        puVar8[7] = in_register_0000000c;
        puVar8[8] = in_zero_lo;
        puVar8[9] = in_zero_hi;
        puVar8[10] = in_zero_udw;
        puVar8[0xb] = in_register_0000000c;
        puVar10 = puVar8 + 0x10;
        do {
          *puVar10 = in_zero_lo;
          puVar10[1] = in_zero_hi;
          puVar10[2] = in_zero_udw;
          puVar10[3] = in_register_0000000c;
          puVar10 = puVar10 + 4;
        } while (puVar10 != puVar8 + 0x18);
        puVar8[0x18] = in_zero_lo;
        puVar8[0x19] = in_zero_hi;
        puVar8[0x1a] = in_zero_udw;
        puVar8[0x1b] = in_register_0000000c;
        puVar10 = puVar8 + 0x40;
        do {
          *puVar10 = in_zero_lo;
          puVar10[1] = in_zero_hi;
          puVar10[2] = in_zero_udw;
          puVar10[3] = in_register_0000000c;
          puVar10 = puVar10 + 4;
        } while (puVar10 != puVar8 + 0x80);
      }
      if (*(int *)(this + 0x144) == 0) {
        *(undefined4 **)(this + 0x144) = puVar8;
        *(undefined4 **)(this + 0x140) = puVar8;
        *puVar8 = 0;
      }
      else {
        *(undefined4 **)(*(int *)(this + 0x144) + 4) = puVar8;
        *puVar8 = *(undefined4 *)(this + 0x144);
        *(undefined4 **)(this + 0x144) = puVar8;
      }
      puVar8[1] = 0;
      *(undefined2 *)(puVar8 + 2) = 0;
      if (((bVar2) || (iVar14 == iVar5 % iVar4)) &&
         (((*(byte *)(this + 0x5c) & 7) != 1 && ((*(byte *)(this + 0x5c) & 7) != 3)))) {
        *(byte *)(puVar8 + 2) = *(byte *)(puVar8 + 2) & 0xfe | 1;
      }
      if (*(int *)(this + 0x74) < *(int *)(this + 0x70)) {
        *(byte *)(puVar8 + 2) = *(byte *)(puVar8 + 2) & 0xfd | 2;
      }
      *(undefined1 *)((int)puVar8 + 10) = 0;
      uVar1 = *(undefined8 *)(this + 0x80);
      uVar3 = this->flMenuTimer2;
      uVar7 = *(undefined4 *)(this + 0x8c);
      puVar8[0x18] = (int)uVar1;
      puVar8[0x19] = (int)((ulong)uVar1 >> 0x20);
      puVar8[0x1a] = uVar3;
      puVar8[0x1b] = uVar7;
      puVar8[0x14] = (int)*(undefined8 *)(puVar8 + 0x18);
      puVar8[0x15] = (int)((ulong)*(undefined8 *)(puVar8 + 0x18) >> 0x20);
      puVar8[0x16] = puVar8[0x1a];
      puVar8[0x17] = puVar8[0x1b];
      puVar8[0x10] = (int)*(undefined8 *)(puVar8 + 0x14);
      puVar8[0x11] = (int)((ulong)*(undefined8 *)(puVar8 + 0x14) >> 0x20);
      puVar8[0x12] = puVar8[0x16];
      puVar8[0x13] = puVar8[0x17];
      puVar8[4] = (int)*(undefined8 *)(puVar8 + 0x10);
      puVar8[5] = (int)((ulong)*(undefined8 *)(puVar8 + 0x10) >> 0x20);
      puVar8[6] = puVar8[0x12];
      puVar8[7] = puVar8[0x13];
      uVar1 = *(undefined8 *)(this + 0xb0);
      uVar3 = *(undefined4 *)(this + 0xb8);
      uVar7 = *(undefined4 *)(this + 0xbc);
      puVar8[8] = (int)uVar1;
      puVar8[9] = (int)((ulong)uVar1 >> 0x20);
      puVar8[10] = uVar3;
      puVar8[0xb] = uVar7;
      puVar8[0x1d] = fVar15;
      if ((fVar15 != 0.0) && (*(int *)(this + 0x70) <= *(int *)(this + 0x74))) {
        *(byte *)(puVar8 + 2) = *(byte *)(puVar8 + 2) & 0xfd;
      }
      puVar8[0x1e] = 0;
      puVar8[0xc] = *(undefined4 *)(this + 0xc0);
      for (iVar11 = 0; iVar11 < 0x10; iVar11 = iVar11 + 1) {
        *(undefined2 *)((int)puVar8 + iVar11 * 2 + 0x80) = 0;
      }
      fVar15 = fVar15 + 0.016666668;
      *(int *)(this + 0x74) = *(int *)(this + 0x74) + 1;
    }
  } while (*(int *)(this + 0x74) < 10);
  iVar4 = *(int *)(this + 0x140);
  for (fVar15 = 0.7853982 - *(float *)(this + 0xb4); fVar15 < -3.1415927;
      fVar15 = fVar15 + 6.2831855) {
  }
  for (; 3.1415927 <= fVar15; fVar15 = fVar15 - 6.2831855) {
  }
  iVar5 = *(int *)(this + 0x70);
  while (iVar4 != 0) {
    *(float *)(iVar4 + 0x70) = fVar15;
    iVar4 = *(int *)(iVar4 + 4);
    fVar15 = fVar15 - 6.2831855 / (((float)(iVar5 + -5) * 20.0) / 17.0 + 20.0);
    if (fVar15 < -3.1415927) {
      fVar15 = fVar15 + 6.2831855;
    }
  }
  Entry__7CPollerFP7CPolObjib(iGpffff84b0 + 0x48,this,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff8610,0xffffffffffffffff,this);
  Retail_CBtlPAfter2_SetDDispMode9(0x3f000000,uGpffff8618);
  uVar3 = PlaySEHold__6HNMSndFUibP7FVector(uGpffff8374,0x3008,1,0);
  *(undefined4 *)(this + 0x148) = uVar3;
  __dt__9GsxCameraFv(auStack_3f0,0xffffffffffffffff);
  return this;
}

/* ---- 0x005725b0  __dt__13BtlTarotSelectFv  (size 0x1d0) ----
 *   nStep values: []
 *   nPhase targets: ['0x43e880', '0x43f4c0']
 *   bState targets: [] */
int __dt__13BtlTarotSelectFv(int this,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (this != 0) {
    *(undefined4 *)(this + 0x14) = 0x43e870;
    this->nPhase = 0x43e880;
    *(undefined4 *)(this + 0x34) = 0x43e890;
    if (*(int *)(this + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(this + 0x18));
    }
    if (*(int *)(this + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(this + 0x1c));
    }
    iVar2 = *(int *)(this + 0x140);
    while (iVar2 != 0) {
      iVar1 = *(int *)(iVar2 + 4);
      __dl__FPv(iVar2);
      iVar2 = iVar1;
    }
    if (*(int *)(this + 0x148) != -1) {
      SetSEEnd__6HNMSndFUii(uGpffff8374,0x3008,*(undefined4 *)(this + 0x148));
    }
    if (this != 0) {
      *(undefined4 *)(this + 0x14) = 0x43f4b0;
      this->nPhase = 0x43f4c0;
      *(undefined4 *)(this + 0x34) = 0x43f4d0;
      if (this != -0x2c) {
        *(undefined4 *)(this + 0x34) = 0x437f60;
      }
      __dt__8VIF1PrimFv(this + 0x18,0);
      __dt__7CPolObjFv(this,0);
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

/* ---- 0x00572780  Destruct__13BtlTarotSelectFv  (size 0xd0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void Destruct__13BtlTarotSelectFv(int this)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff8610,0xffffffffffffffff,this);
  if ((long)((ulong)*(byte *)(this + 0x40) << 0x3e) < 0) {
    iVar1 = this;
    if (this != 0) {
      iVar1 = this + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x45a200,iVar1);
  }
  *(byte *)(this + 0x40) = *(byte *)(this + 0x40) & 0xfd;
  Dispose__7CPollerFP7CPolObj(iGpffff84b0 + 0x48,this);
  (**(code **)(*(int *)(this + 0x34) + 0xc))();
  return;
}

/* ---- 0x00572850  Polling__13BtlTarotSelectFv  (size 0x3fd0) ----
 *   nStep values: []
 *   nPhase targets: ['0x0']
 *   bState targets: [] */
undefined8 Polling__13BtlTarotSelectFv(int this)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [12];
  undefined1 auVar9 [12];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  ulong uVar17;
  int iVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  undefined1 in_vf0 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [8];
  undefined4 uStack_4a8;
  undefined4 uStack_4a4;
  float fStack_4a0;
  float fStack_49c;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined1 auStack_490 [8];
  undefined4 uStack_488;
  undefined4 uStack_484;
  float fStack_480;
  float fStack_47c;
  undefined4 uStack_478;
  undefined4 uStack_474;
  undefined4 uStack_470;
  undefined4 uStack_46c;
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined4 uStack_460;
  undefined4 uStack_45c;
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined4 uStack_450;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined4 uStack_444;
  undefined8 uStack_440;
  undefined4 uStack_438;
  undefined4 uStack_434;
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined8 uStack_420;
  undefined4 uStack_418;
  undefined4 uStack_414;
  float afStack_410 [4];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [8];
  float fStack_3d8;
  undefined4 uStack_3d0;
  undefined4 uStack_3cc;
  undefined4 uStack_3c8;
  undefined4 uStack_3c4;
  undefined1 auStack_3c0 [16];
  undefined4 uStack_3b0;
  undefined4 uStack_3ac;
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  undefined1 auStack_3a0 [16];
  undefined4 uStack_390;
  undefined4 uStack_38c;
  float fStack_388;
  undefined4 uStack_384;
  undefined1 auStack_380 [8];
  undefined4 uStack_378;
  undefined4 uStack_374;
  undefined4 uStack_370;
  undefined4 uStack_36c;
  float fStack_368;
  undefined4 uStack_364;
  undefined1 auStack_360 [8];
  undefined4 uStack_358;
  undefined4 uStack_354;
  undefined4 uStack_350;
  undefined4 uStack_34c;
  float fStack_348;
  undefined4 uStack_344;
  undefined1 auStack_340 [8];
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  undefined4 uStack_32c;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [8];
  undefined4 uStack_318;
  undefined4 uStack_314;
  undefined4 uStack_310;
  undefined4 uStack_30c;
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined1 auStack_300 [8];
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  undefined4 uStack_2f0;
  undefined4 uStack_2ec;
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined1 auStack_2e0 [8];
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [8];
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined4 uStack_2b0;
  undefined4 uStack_2ac;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined1 auStack_2a0 [8];
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined4 uStack_290;
  undefined4 uStack_28c;
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [8];
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined4 uStack_270;
  float fStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined8 uStack_260;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  float fStack_240;
  float fStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined4 uStack_230;
  undefined4 uStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined8 uStack_220;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [8];
  undefined4 uStack_1f8;
  undefined1 auStack_1f0 [16];
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 uStack_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1b0;
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined8 uStack_1a0;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  float fStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [256];
  
  fVar19 = *(float *)(this + 0xb4);
  auStack_110._4_4_ = in_zero_hi;
  auStack_110._0_4_ = in_zero_lo;
  uStack_108 = in_zero_udw;
  uStack_104 = in_register_0000000c;
  auVar23 = _vmr32(in_vf0);
  auVar24 = _vmr32(auVar23);
  auVar25 = _vmr32(auVar24);
  auStack_150 = _sqc2(in_vf0);
  auStack_160 = _sqc2(auVar23);
  auStack_170 = _sqc2(auVar24);
  auStack_180 = _sqc2(auVar25);
  iVar10 = GetRegDat__9RegDatApiFiii(0x44,0,0xffffffffffffffff);
  iVar11 = GetTimer__7SysToolFv();
  fVar21 = (float)(uint)(iVar11 - this->nShortcutTarget) * 0.001;
  this->nShortcutTarget = iVar11;
  switch(*(undefined1 *)(this + 0x5e)) {
  case 0:
    cVar1 = *(char *)(this + 0x5f);
    if (cVar1 == '\x02') {
      *(float *)(this + 100) = *(float *)(this + 100) + fVar21 / 0.75;
      if (1.0 < *(float *)(this + 100)) {
        *(undefined4 *)(this + 100) = 0x3f800000;
      }
      uStack_1a8 = *(undefined4 *)(this + 0x6c);
      uStack_1ac = *(undefined4 *)(this + 0x68);
      uStack_1b0 = 0;
      uStack_1a4 = 0x3f800000;
      auVar8._8_4_ = 0;
      auVar8._0_8_ = *(ulong *)(this + 0x68);
      auVar24._12_4_ = 0x3f800000;
      auVar24._0_12_ = auVar8 << 0x20;
      auVar23 = _lqc2(auVar24);
      auVar24 = _lqc2(*(undefined1 (*) [16])(this + 0x90));
      auVar23 = _vsub(auVar23,auVar24);
      auStack_4c0 = _sqc2(auVar23);
      __ct__7FVectorFPC7FVector(&uStack_1a0,auStack_4c0);
      uStack_108 = uStack_198;
      auStack_110 = (undefined1  [8])uStack_1a0;
      uStack_104 = uStack_194;
      __amu__7FVectorFf(*(undefined4 *)(this + 100),auStack_110);
      auVar23 = _lqc2(_auStack_110);
      auVar24 = _lqc2(*(undefined1 (*) [16])(this + 0x90));
      auVar23 = _vadd(auVar23,auVar24);
      auStack_4d0 = _sqc2(auVar23);
      __ct__7FVectorFPC7FVector(auStack_1c0,auStack_4d0);
      *(int *)(this + 0x80) = auStack_1c0._0_4_;
      this->flMenuTimer = auStack_1c0._4_4_;
      this->flMenuTimer2 = uStack_1b8;
      *(undefined4 *)(this + 0x8c) = uStack_1b4;
      *(float *)(this + 0xb4) = *(float *)(this + 0xb4) + fVar21 * 1.3962635;
      if (3.1415927 <= *(float *)(this + 0xb4)) {
        *(float *)(this + 0xb4) = *(float *)(this + 0xb4) - 6.2831855;
      }
      *(undefined4 *)(this + 0xc0) = 0x3f19999a;
      if (1.0 <= *(float *)(this + 100)) {
        *(undefined1 *)(this + 0x5e) = 1;
        *(undefined1 *)(this + 0x5f) = 0;
        *(undefined4 *)(this + 100) = 0;
        uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x67,0);
        *(undefined4 *)(iGpffff8610 + 0x78) = uVar15;
        uStack_1d0 = 0x43800000;
        uStack_1cc = 0x43133333;
        uStack_1c8 = 0;
        uStack_1c4 = 0x3f800000;
        MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori(0xc,0,2,2,0,0,&uStack_1d0,0);
        uStack_1e0 = 0x43800000;
        uStack_1dc = 0x43966666;
        uStack_1d8 = 0;
        uStack_1d4 = 0x3f800000;
        MakeCursole__7BtlMenuFiUcUcUcUcUcP7FVectori(0xc,0,2,1,0,0,&uStack_1e0,1);
        iVar10 = FindBCursole__7BtlMenuFi(0);
        ReleaseOT__5WorldFP8VIF1Prim(0x45a200,iVar10 + 0xc);
        AddOT__5WorldFiP8VIF1Prim(0x45a200,0xc,iVar10 + 0xc);
        iVar10 = FindBCursole__7BtlMenuFi(1);
        ReleaseOT__5WorldFP8VIF1Prim(0x45a200,iVar10 + 0xc);
        AddOT__5WorldFiP8VIF1Prim(0x45a200,0xc,iVar10 + 0xc);
      }
    }
    else if ((cVar1 != '\x01') && (cVar1 == '\0')) {
      *(float *)(this + 100) = *(float *)(this + 100) + fVar21 / 0.75;
      if (1.0 < *(float *)(this + 100)) {
        *(undefined4 *)(this + 100) = 0x3f800000;
      }
      uStack_188 = *(undefined4 *)(this + 0x6c);
      fStack_18c = *(float *)(this + 0x68) - 512.0;
      uStack_190 = 0;
      uStack_184 = 0x3f800000;
      *(undefined4 *)(this + 0x80) = 0;
      this->flMenuTimer = fStack_18c;
      this->flMenuTimer2 = uStack_188;
      *(undefined4 *)(this + 0x8c) = 0x3f800000;
      *(float *)(this + 0xb4) = *(float *)(this + 0xb4) + fVar21 * 1.3962635;
      if (3.1415927 <= *(float *)(this + 0xb4)) {
        *(float *)(this + 0xb4) = *(float *)(this + 0xb4) - 6.2831855;
      }
      *(float *)(this + 0xc0) = *(float *)(this + 100) * 0.6;
      if (1.0 <= *(float *)(this + 100)) {
        *(undefined1 *)(this + 0x5f) = 1;
        *(undefined4 *)(this + 100) = 0;
        this->flTurnPush = (int)*(undefined8 *)(this + 0x80);
        *(int *)(this + 0x94) = (int)((ulong)*(undefined8 *)(this + 0x80) >> 0x20);
        *(undefined4 *)(this + 0x98) = this->flMenuTimer2;
        *(undefined4 *)(this + 0x9c) = *(undefined4 *)(this + 0x8c);
        iVar10 = *(int *)(this + 0x140);
        for (fVar22 = 0.7853982 - *(float *)(this + 0xb4); fVar22 < -3.1415927;
            fVar22 = fVar22 + 6.2831855) {
        }
        for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
        }
        while (iVar10 != 0) {
          *(byte *)(iVar10 + 8) = *(byte *)(iVar10 + 8) & 0xfd | 2;
          *(undefined1 *)(iVar10 + 10) = 1;
          *(float *)(iVar10 + 0x70) = fVar22;
          iVar10 = *(int *)(iVar10 + 4);
          fVar22 = fVar22 - 0.15707964;
          if (fVar22 < -3.1415927) {
            fVar22 = fVar22 + 6.2831855;
          }
        }
      }
    }
    break;
  case 1:
    *(float *)(this + 100) = *(float *)(this + 100) + fVar21;
    *(float *)(this + 0xb4) = *(float *)(this + 0xb4) + fVar21 * 1.3962635;
    if (3.1415927 <= *(float *)(this + 0xb4)) {
      *(float *)(this + 0xb4) = *(float *)(this + 0xb4) - 6.2831855;
    }
    if (((chr(iGpffff8610,iGpffff8610->cActor)->nSp < 1) ||
        ((long)((ulong)chr(iGpffff8610,iGpffff8610->cActor)->bFlagsA1 << 0x3b
               ) < 0)) || ((long)((ulong)iGpffff8610->bFlags24 << 0x3a) < 0)) {
      if (*(float *)(this + 100) < 1.0) break;
    }
    else if ((*(ushort *)(*(int *)(*(int *)(iGpffff861c + 4) * 4 + 0x43fca8) + 0x6c) & 0x2000) == 0)
    break;
    *(undefined1 *)(this + 0x5e) = 2;
    *(undefined1 *)(this + 0x5f) = 0;
    iVar11 = *(int *)(this + 0x140);
    fVar22 = 6.2831855;
    for (iVar18 = iVar11; iVar18 != 0; iVar18 = *(int *)(iVar18 + 4)) {
      for (fVar20 = *(float *)(this + 0xb4) + *(float *)(iVar18 + 0x70); fVar20 < -3.1415927;
          fVar20 = fVar20 + 6.2831855) {
      }
      for (; 3.1415927 <= fVar20; fVar20 = fVar20 - 6.2831855) {
      }
      if (fVar20 < 0.0) {
        fVar20 = fVar20 * -1.0;
      }
      iVar12 = iVar18;
      if (fVar22 <= fVar20) {
        fVar20 = fVar22;
        iVar12 = iVar11;
      }
      iVar11 = iVar12;
      *(undefined1 *)(iVar18 + 10) = 2;
      *(undefined4 *)(iVar18 + 0x74) = 0;
      fVar22 = fVar20;
    }
    *(undefined1 *)(iVar11 + 10) = 3;
    *(undefined1 *)(iVar11 + 0xb) = 0;
    auVar23 = _lqc2(*(undefined1 (*) [16])(iVar11 + 0x10));
    auVar24 = _lqc2(*(undefined1 (*) [16])(iVar11 + 0x60));
    auVar23 = _vsub(auVar23,auVar24);
    auStack_4e0 = _sqc2(auVar23);
    __ct__7FVectorFPC7FVector(auStack_1f0,auStack_4e0);
    uVar15 = Length__7FVectorCFv(auStack_110);
    *(undefined4 *)(iVar11 + 0x70) = uVar15;
    uVar13 = __ct__7FVectorFPC7FVector(auStack_210,auStack_110);
    Get3DAngle3__F7FVector(auStack_200,uVar13);
    *(undefined4 *)(iVar11 + 0x74) = uStack_1f8;
    *(undefined4 *)(iVar11 + 0x78) = 0;
    uStack_230 = 0;
    uStack_22c = 0;
    uStack_228 = 0;
    uStack_224 = 0x3f800000;
    auVar23._12_4_ = 0x3f800000;
    auVar23._0_12_ = ZEXT812(0);
    auVar23 = _lqc2(auVar23);
    auVar24 = _lqc2(*(undefined1 (*) [16])(iVar11 + 0x10));
    auVar23 = _vsub(auVar23,auVar24);
    auStack_4f0 = _sqc2(auVar23);
    __ct__7FVectorFPC7FVector(&uStack_220,auStack_4f0);
    uStack_108 = uStack_218;
    auStack_110 = (undefined1  [8])uStack_220;
    uStack_104 = uStack_214;
    uVar15 = Length__7FVectorCFv(auStack_110);
    *(undefined4 *)(iVar11 + 0x7c) = uVar15;
    iGpffff8610->nCmd1 = 0;
    if ((*(byte *)(iVar11 + 8) & 1) != 0) {
      iGpffff8610->nCmd1 = iGpffff8610->nCmd1 | 1;
    }
    iVar11 = rand();
    if ((((iVar11 % 100 < (int)(uint)*(byte *)(iVar10 + iGpffff8610->nCmd0_target * 8 + 4)) ||
         ((*(byte *)(this + 0x5c) & 7) == 3)) || ((*(byte *)(this + 0x5c) & 7) == 4)) &&
       (((*(byte *)(this + 0x5c) & 7) != 1 && ((*(byte *)(this + 0x5c) & 7) != 2)))) {
      iGpffff8610->nCmd1 = iGpffff8610->nCmd1 | 2;
    }
    if (-1 < *(int *)(iGpffff8610 + 0x78)) {
      SetMesWinClose__7BtlMenuFi(*(undefined4 *)(iGpffff8610 + 0x78));
    }
    *(undefined4 *)(iGpffff8610 + 0x78) = 0xffffffff;
    AllBCurDestruct__7BtlMenuFv();
    if (*(int *)(this + 0x148) != -1) {
      SetSEEnd__6HNMSndFUii(uGpffff8374,0x3008,*(undefined4 *)(this + 0x148));
    }
    *(undefined4 *)(this + 0x148) = 0xffffffff;
    PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x3009,1,0);
    break;
  case 2:
    *(float *)(this + 0xb4) = *(float *)(this + 0xb4) + fVar21 * 1.3962635;
    if (3.1415927 <= *(float *)(this + 0xb4)) {
      *(float *)(this + 0xb4) = *(float *)(this + 0xb4) - 6.2831855;
    }
    iVar11 = 0;
    for (iVar10 = *(int *)(this + 0x140); iVar10 != 0; iVar10 = *(int *)(iVar10 + 4)) {
      if (((long)((ulong)*(byte *)(iVar10 + 8) << 0x3e) < 0) && (*(char *)(iVar10 + 10) == '\x02'))
      {
        iVar11 = iVar11 + 1;
      }
    }
    if (iVar11 == 0) {
      *(undefined1 *)(this + 0x5e) = 3;
    }
    break;
  case 4:
    *(float *)(this + 100) = *(float *)(this + 100) + fVar21;
    bVar3 = false;
    if ((0.5 <= *(float *)(this + 100)) &&
       ((*(ushort *)(*(int *)(*(int *)(iGpffff861c + 4) * 4 + 0x43fca8) + 0x6c) & 0x2000) != 0)) {
      bVar3 = true;
    }
    if (1.0 < *(float *)(this + 100)) {
      bVar3 = true;
    }
    if (bVar3) {
      *(undefined1 *)(this + 0x5e) = 5;
      *(ushort *)(this + 0x5c) = *(ushort *)(this + 0x5c) & 0xfe3f | 0x40;
    }
  }
  uVar17 = ((ulong)*(byte *)(this + 0x5c) & 0x3f) >> 3;
  if (((uVar17 != 2) && (uVar17 == 1)) &&
     (*(float *)(this + 0xd8) = *(float *)(this + 0xd8) + fVar21 * 512.0 * 2.0,
     0.0 <= *(float *)(this + 0xd8))) {
    *(undefined4 *)(this + 0xd8) = 0;
    *(byte *)(this + 0x5c) = *(byte *)(this + 0x5c) & 199 | 0x10;
    if ((*(float *)(this + 0xc4) == 0.0) && ((iGpffff8610->nCmd1 & 2) != 0)) {
      *(undefined4 *)(this + 0xc4) = 0x3f800000;
    }
  }
  if (((ulong)*(ushort *)(this + 0x5c) & 0x1ff) >> 6 == 1) {
    *(float *)(this + 0xf4) = *(float *)(this + 0xf4) + fVar21 * 20.0;
    *(float *)(this + 0xf8) = *(float *)(this + 0xf8) + fVar21 * 3.1415927 * 1.2;
    if (3.1415927 <= *(float *)(this + 0xf8)) {
      *(float *)(this + 0xf8) = *(float *)(this + 0xf8) - 6.2831855;
    }
  }
  if (*(float *)(this + 0xc4) != 0.0) {
    *(float *)(this + 0xc4) = *(float *)(this + 0xc4) - fVar21;
    if (0.0 < *(float *)(this + 0xc4)) {
      iVar10 = rand();
      fVar22 = *(float *)(this + 0xc4) * (((float)iVar10 / 2.1474836e+09) * 16.0 - 8.0);
      iVar10 = rand();
      fStack_240 = *(float *)(this + 0xc4) * (((float)iVar10 / 2.1474836e+09) * 16.0 - 8.0);
      uStack_238 = 0;
      uStack_234 = 0x3f800000;
      *(float *)(this + 0xa0) = fStack_240;
      *(float *)(this + 0xa4) = fVar22;
      *(undefined4 *)(this + 0xa8) = 0;
      *(undefined4 *)(this + 0xac) = 0x3f800000;
      fStack_23c = fVar22;
    }
    else {
      *(undefined4 *)(this + 0xc4) = 0;
      uStack_250 = 0;
      uStack_24c = 0;
      uStack_248 = 0;
      uStack_244 = 0x3f800000;
      *(undefined4 *)(this + 0xa0) = 0;
      *(undefined4 *)(this + 0xa4) = 0;
      *(undefined4 *)(this + 0xa8) = 0;
      *(undefined4 *)(this + 0xac) = 0x3f800000;
    }
  }
  if (fVar21 != 0.0) {
    iVar10 = *(int *)(this + 0x140);
    while (iVar10 != 0) {
      if ((long)((ulong)*(byte *)(iVar10 + 8) << 0x3e) < 0) {
        cVar1 = *(char *)(iVar10 + 10);
        if (cVar1 != '\x05') {
          if (cVar1 == '\x03') {
            if (iGpffff8610->nCmd1 == 3) {
              uStack_3d0 = 0;
              uStack_3cc = 0x42200000;
              uStack_3c8 = 0;
              uStack_3c4 = 0x3f800000;
              auVar25._12_4_ = 0x3f800000;
              auVar25._0_12_ = ZEXT812(0x4220000000000000);
              auVar23 = _lqc2(auVar25);
              auVar24 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x10));
              auVar23 = _vsub(auVar23,auVar24);
              auStack_520 = _sqc2(auVar23);
              __ct__7FVectorFPC7FVector(auStack_3c0,auStack_520);
            }
            else {
              uStack_3b0 = 0;
              uStack_3ac = 0;
              uStack_3a8 = 0;
              uStack_3a4 = 0x3f800000;
              auVar6._12_4_ = 0x3f800000;
              auVar6._0_12_ = ZEXT812(0);
              auVar23 = _lqc2(auVar6);
              auVar24 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x10));
              auVar23 = _vsub(auVar23,auVar24);
              auStack_510 = _sqc2(auVar23);
              __ct__7FVectorFPC7FVector(auStack_3a0,auStack_510);
            }
            fVar20 = (float)Length__7FVectorCFv(auStack_110);
            uVar13 = __ct__7FVectorFPC7FVector(auStack_3f0,auStack_110);
            Get3DAngle3__F7FVector(auStack_3e0,uVar13);
            for (fVar22 = fStack_3d8 - *(float *)(iVar10 + 0x74); fVar22 < -3.1415927;
                fVar22 = fVar22 + 6.2831855) {
            }
            for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
            }
            *(float *)(iVar10 + 0x78) = *(float *)(iVar10 + 0x78) + fVar21;
            cVar1 = *(char *)(iVar10 + 0xb);
            if (cVar1 == '\x02') {
              if (fVar22 < -0.19634955) {
                fVar22 = -0.19634955;
              }
              else if (0.19634955 < fVar22) {
                fVar22 = 0.19634955;
              }
              *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) + fVar22 * fVar21 * 60.0;
              while (*(float *)(iVar10 + 0x74) < -3.1415927) {
                *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) + 6.2831855;
              }
              while (3.1415927 <= *(float *)(iVar10 + 0x74)) {
                *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) - 6.2831855;
              }
              fVar20 = fVar20 / 4.0;
              if (fVar20 < 0.25) {
                fVar20 = 0.25;
              }
              if (fVar20 < *(float *)(iVar10 + 0x70)) {
                *(float *)(iVar10 + 0x70) = fVar20;
              }
              if (0.0 < iVar10->nPhase) {
                iVar10->nPhase = iVar10->nPhase + fVar21 * 7.853982;
                while (iVar10->nPhase < -3.1415927) {
                  iVar10->nPhase = iVar10->nPhase + 6.2831855;
                }
                while (3.1415927 <= iVar10->nPhase) {
                  iVar10->nPhase = iVar10->nPhase - 6.2831855;
                }
              }
              else {
                iVar10->nPhase = iVar10->nPhase + fVar21 * 7.853982;
                while (iVar10->nPhase < -3.1415927) {
                  iVar10->nPhase = iVar10->nPhase + 6.2831855;
                }
                while (3.1415927 <= iVar10->nPhase) {
                  iVar10->nPhase = iVar10->nPhase - 6.2831855;
                }
                if (0.0 <= iVar10->nPhase) {
                  iVar10->nPhase = 0;
                }
              }
              if ((iVar10->bFlags24 != -3.1415927) &&
                 (iVar10->bFlags24 = iVar10->bFlags24 + fVar21 * 6.2831855,
                 3.1415927 <= iVar10->bFlags24)) {
                iVar10->bFlags24 = 0xc0490fdb;
              }
            }
            else if (cVar1 == '\x01') {
              if (fVar22 < -0.19634955) {
                fVar22 = -0.19634955;
              }
              else if (0.19634955 < fVar22) {
                fVar22 = 0.19634955;
              }
              *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) + fVar22 * fVar21 * 60.0;
              while (*(float *)(iVar10 + 0x74) < -3.1415927) {
                *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) + 6.2831855;
              }
              while (3.1415927 <= *(float *)(iVar10 + 0x74)) {
                *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) - 6.2831855;
              }
              fVar20 = fVar20 / 4.0;
              if (fVar20 < 0.25) {
                fVar20 = 0.25;
              }
              if (fVar20 < *(float *)(iVar10 + 0x70)) {
                *(float *)(iVar10 + 0x70) = fVar20;
              }
              if (0.0 < iVar10->nPhase) {
                iVar10->nPhase = iVar10->nPhase + fVar21 * 7.853982;
                while (iVar10->nPhase < -3.1415927) {
                  iVar10->nPhase = iVar10->nPhase + 6.2831855;
                }
                while (3.1415927 <= iVar10->nPhase) {
                  iVar10->nPhase = iVar10->nPhase - 6.2831855;
                }
              }
              else {
                iVar10->nPhase = iVar10->nPhase + fVar21 * 7.853982;
                while (iVar10->nPhase < -3.1415927) {
                  iVar10->nPhase = iVar10->nPhase + 6.2831855;
                }
                while (3.1415927 <= iVar10->nPhase) {
                  iVar10->nPhase = iVar10->nPhase - 6.2831855;
                }
                if (0.0 <= iVar10->nPhase) {
                  iVar10->nPhase = 0;
                }
              }
            }
            else if (cVar1 == '\0') {
              iVar10->nPhase = iVar10->nPhase + fVar21 * 7.853982;
              while (iVar10->nPhase < -3.1415927) {
                iVar10->nPhase = iVar10->nPhase + 6.2831855;
              }
              while (3.1415927 <= iVar10->nPhase) {
                iVar10->nPhase = iVar10->nPhase - 6.2831855;
              }
              if (0.2 <= *(float *)(iVar10 + 0x78)) {
                *(undefined1 *)(iVar10 + 0xb) = 1;
              }
            }
            fVar22 = -*(float *)(iVar10 + 0x18);
            if (0.0 < fVar22) {
              if (fVar21 * 8.0 < fVar22) {
                fVar22 = fVar21 * 8.0;
              }
              *(float *)(iVar10 + 0x18) = *(float *)(iVar10 + 0x18) + fVar22;
            }
            else if (fVar22 < 0.0) {
              if (fVar22 < -fVar21 * 8.0) {
                fVar22 = -fVar21 * 8.0;
              }
              *(float *)(iVar10 + 0x18) = *(float *)(iVar10 + 0x18) + fVar22;
            }
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixZ(-*(float *)(iVar10 + 0x74),auStack_180,auStack_180);
            afStack_410[0] = *(float *)(iVar10 + 0x70) * fVar21 * 60.0;
            afStack_410[1] = 0.0;
            afStack_410[2] = 0.0;
            afStack_410[3] = 1.0;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_400,auStack_180,afStack_410);
            auVar24 = _lqc2(auStack_400);
            auVar23 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x10));
            auVar23 = _vadd(auVar23,auVar24);
            auVar23 = _sqc2(auVar23);
            *(undefined1 (*) [16])(iVar10 + 0x10) = auVar23;
            iVar10->nCurTurnChr = *(float *)(iVar10 + 0x78) * 0.5 + 0.6;
            if (1.0 < iVar10->nCurTurnChr) {
              iVar10->nCurTurnChr = 0x3f800000;
            }
            if (iGpffff8610->nCmd1 == 3) {
              uStack_450 = 0;
              uStack_44c = 0x42200000;
              uStack_448 = 0;
              uStack_444 = 0x3f800000;
              auVar4._12_4_ = 0x3f800000;
              auVar4._0_12_ = ZEXT812(0x4220000000000000);
              auVar23 = _lqc2(auVar4);
              auVar24 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x10));
              auVar23 = _vsub(auVar23,auVar24);
              auStack_540 = _sqc2(auVar23);
              __ct__7FVectorFPC7FVector(&uStack_440,auStack_540);
              uStack_108 = uStack_438;
              auStack_110 = (undefined1  [8])uStack_440;
              uStack_104 = uStack_434;
            }
            else {
              uStack_430 = 0;
              uStack_42c = 0;
              uStack_428 = 0;
              uStack_424 = 0x3f800000;
              auVar5._12_4_ = 0x3f800000;
              auVar5._0_12_ = ZEXT812(0);
              auVar23 = _lqc2(auVar5);
              auVar24 = _lqc2(*(undefined1 (*) [16])(iVar10 + 0x10));
              auVar23 = _vsub(auVar23,auVar24);
              auStack_530 = _sqc2(auVar23);
              __ct__7FVectorFPC7FVector(&uStack_420,auStack_530);
              uStack_108 = uStack_418;
              auStack_110 = (undefined1  [8])uStack_420;
              uStack_104 = uStack_414;
            }
            fVar22 = (float)Length__7FVectorCFv(auStack_110);
            if (((*(char *)(iVar10 + 0xb) == '\x01') && (fVar22 < *(float *)(iVar10 + 0x7c))) &&
               ((*(undefined1 *)(iVar10 + 0xb) = 2, (*(byte *)(iVar10 + 8) & 1) != 0 ||
                ((iGpffff8610->nCmd1 & 2) != 0)))) {
              *(byte *)(this + 0x5c) = *(byte *)(this + 0x5c) & 199 | 8;
            }
            *(float *)(iVar10 + 0x7c) = fVar22;
            if ((((fVar22 <= 0.5) && (*(char *)(iVar10 + 0xb) == '\x02')) &&
                (iVar10->bFlags24 == -3.1415927)) && (iVar10->nPhase == 0.0)) {
              *(undefined1 *)(iVar10 + 10) = 5;
              *(undefined1 *)(iVar10 + 0xb) = 0;
              if (iGpffff8610->nCmd1 == 3) {
                uStack_470 = 0;
                uStack_46c = 0x42200000;
                uStack_468 = 0;
                uStack_464 = 0x3f800000;
                *(undefined4 *)(iVar10 + 0x10) = 0;
                *(undefined4 *)(iVar10 + 0x14) = 0x42200000;
                *(undefined4 *)(iVar10 + 0x18) = 0;
                *(undefined4 *)(iVar10 + 0x1c) = 0x3f800000;
              }
              else {
                uStack_460 = 0;
                uStack_45c = 0;
                uStack_458 = 0;
                uStack_454 = 0x3f800000;
                *(undefined4 *)(iVar10 + 0x10) = 0;
                *(undefined4 *)(iVar10 + 0x14) = 0;
                *(undefined4 *)(iVar10 + 0x18) = 0;
                *(undefined4 *)(iVar10 + 0x1c) = 0x3f800000;
              }
              *(undefined4 *)(iVar10 + 0x70) = 0;
              if (-1 < *(int *)(iGpffff8610 + 0x80)) {
                SetMesWinClose__7BtlMenuFi(*(undefined4 *)(iGpffff8610 + 0x80));
              }
              *(undefined4 *)(iGpffff8610 + 0x80) = 0xffffffff;
              while (*(int *)(iGpffff8610 + 0x80) < 0) {
                if ((*(byte *)(iVar10 + 8) & 1) == 0) {
                  if ((iGpffff8610->nCmd1 & 2) == 0) {
                    uVar13 = GetRegDat__9RegDatApiFiii(0x2b,0x82,0xffffffffffffffff);
                    uVar14 = GetRegDat__9RegDatApiFiii(0xe,iGpffff8610->nCmd0_target,
                                             0xffffffffffffffff);
                    sprintf(auStack_100,uVar13,uVar14);
                  }
                  else {
                    uVar13 = GetRegDat__9RegDatApiFiii(0x2b,0x83,0xffffffffffffffff);
                    uVar14 = GetRegDat__9RegDatApiFiii(0xe,iGpffff8610->nCmd0_target,
                                             0xffffffffffffffff);
                    sprintf(auStack_100,uVar13,uVar14);
                  }
                }
                else if ((iGpffff8610->nCmd1 & 2) == 0) {
                  uVar13 = GetRegDat__9RegDatApiFiii(0x2b,0x84,0xffffffffffffffff);
                  uVar14 = GetRegDat__9RegDatApiFiii(0xe,iGpffff8610->nCmd0_target,
                                           0xffffffffffffffff);
                  sprintf(auStack_100,uVar13,uVar14);
                }
                else {
                  uVar13 = GetRegDat__9RegDatApiFiii(0x2b,0x85,0xffffffffffffffff);
                  uVar14 = GetRegDat__9RegDatApiFiii(0xe,iGpffff8610->nCmd0_target,
                                           0xffffffffffffffff);
                  sprintf(auStack_100,uVar13,uVar14);
                }
                uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x146,auStack_100);
                *(undefined4 *)(iGpffff8610 + 0x80) = uVar15;
              }
              if (-1 < *(int *)(iGpffff8610 + 0x7c)) {
                SetMesWinClose__7BtlMenuFi(*(undefined4 *)(iGpffff8610 + 0x7c));
              }
              *(undefined4 *)(iGpffff8610 + 0x7c) = 0xffffffff;
              if ((*(byte *)(iVar10 + 8) & 1) == 0) {
                if ((iGpffff8610->nCmd1 & 2) == 0) {
                  uVar13 = GetRegDat__9RegDatApiFiii(0x25,iGpffff8610->nCmd0_target,0);
                  uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x148,uVar13);
                  *(undefined4 *)(iGpffff8610 + 0x7c) = uVar15;
                }
                else {
                  uVar13 = GetRegDat__9RegDatApiFiii(0x25,iGpffff8610->nCmd0_target,2);
                  uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x148,uVar13);
                  *(undefined4 *)(iGpffff8610 + 0x7c) = uVar15;
                }
              }
              else if ((iGpffff8610->nCmd1 & 2) == 0) {
                uVar13 = GetRegDat__9RegDatApiFiii(0x25,iGpffff8610->nCmd0_target,1);
                uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x148,uVar13);
                *(undefined4 *)(iGpffff8610 + 0x7c) = uVar15;
              }
              else {
                uVar13 = GetRegDat__9RegDatApiFiii(0x25,iGpffff8610->nCmd0_target,3);
                uVar15 = SetBtlMessage__7CBattleFiPv(iGpffff8610,0x148,uVar13);
                *(undefined4 *)(iGpffff8610 + 0x7c) = uVar15;
              }
              *(undefined1 *)(this + 0x5e) = 4;
              *(undefined4 *)(this + 100) = 0;
            }
          }
          else if (cVar1 == '\x02') {
            for (fVar22 = fVar19 + *(float *)(iVar10 + 0x70); fVar22 < -3.1415927;
                fVar22 = fVar22 + 6.2831855) {
            }
            for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
            }
            if ((0.0 <= fVar22) && (fVar22 < 0.7853982)) {
              for (fVar22 = *(float *)(this + 0xb4) + *(float *)(iVar10 + 0x70);
                  fVar22 < -3.1415927; fVar22 = fVar22 + 6.2831855) {
              }
              for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
              }
              if (0.7853982 <= fVar22) {
                *(float *)(iVar10 + 0x70) =
                     *(float *)(iVar10 + 0x70) -
                     ((float)*(int *)(this + 0x74) * 6.2831855) / 40.0;
                while (*(float *)(iVar10 + 0x70) < -3.1415927) {
                  *(float *)(iVar10 + 0x70) = *(float *)(iVar10 + 0x70) + 6.2831855;
                }
                while (3.1415927 <= *(float *)(iVar10 + 0x70)) {
                  *(float *)(iVar10 + 0x70) = *(float *)(iVar10 + 0x70) - 6.2831855;
                }
              }
            }
            *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) + fVar21 * 30.0 * 48.0;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            iVar10->nShortcutTarget = (int)*(undefined8 *)(iVar10 + 0x10);
            *(int *)(iVar10 + 100) = (int)((ulong)*(undefined8 *)(iVar10 + 0x10) >> 0x20);
            *(undefined4 *)(iVar10 + 0x68) = *(undefined4 *)(iVar10 + 0x18);
            *(undefined4 *)(iVar10 + 0x6c) = *(undefined4 *)(iVar10 + 0x1c);
            fStack_348 = -1600.0 - *(float *)(iVar10 + 0x74);
            uStack_350 = 0;
            uStack_34c = 0;
            uStack_344 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_340,auStack_180,&uStack_350);
            *(int *)(iVar10 + 0x10) = auStack_340._0_4_;
            *(int *)(iVar10 + 0x14) = auStack_340._4_4_;
            *(undefined4 *)(iVar10 + 0x18) = uStack_338;
            *(undefined4 *)(iVar10 + 0x1c) = uStack_334;
            fVar22 = (((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0) * 6.2831855) /
                     10053.097;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            fStack_368 = -1600.0 - *(float *)(iVar10 + 0x74);
            uStack_370 = 0;
            uStack_36c = 0;
            uStack_364 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_360,auStack_180,&uStack_370);
            *(int *)(iVar10 + 0x40) = auStack_360._0_4_;
            iVar10->nCmd0_target = auStack_360._4_4_;
            iVar10->nCmd1 = uStack_358;
            iVar10->nCmdKind = uStack_354;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(-fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            fStack_388 = -1600.0 - *(float *)(iVar10 + 0x74);
            uStack_390 = 0;
            uStack_38c = 0;
            uStack_384 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_380,auStack_180,&uStack_390);
            iVar10->nCmd3 = auStack_380._0_4_;
            iVar10->nCmdMask = auStack_380._4_4_;
            *(undefined4 *)(iVar10 + 0x58) = uStack_378;
            *(undefined4 *)(iVar10 + 0x5c) = uStack_374;
            uVar13 = *(undefined8 *)(this + 0xb0);
            uVar15 = *(undefined4 *)(this + 0xb8);
            uVar16 = *(undefined4 *)(this + 0xbc);
            *(int *)(iVar10 + 0x20) = (int)uVar13;
            iVar10->bFlags24 = (int)((ulong)uVar13 >> 0x20);
            iVar10->nPhase = uVar15;
            iVar10->cActor = uVar16;
            iVar10->bFlags24 = iVar10->bFlags24 + *(float *)(iVar10 + 0x70);
            while (iVar10->bFlags24 < -3.1415927) {
              iVar10->bFlags24 = iVar10->bFlags24 + 6.2831855;
            }
            while (3.1415927 <= iVar10->bFlags24) {
              iVar10->bFlags24 = iVar10->bFlags24 - 6.2831855;
            }
            iVar10->nCurTurnChr = *(undefined4 *)(this + 0xc0);
            if (800.0 <= *(float *)(iVar10 + 0x74)) {
              *(byte *)(iVar10 + 8) = *(byte *)(iVar10 + 8) & 0xfd;
            }
          }
          else if (cVar1 == '\x01') {
            for (fVar22 = fVar19 + *(float *)(iVar10 + 0x70); fVar22 < -3.1415927;
                fVar22 = fVar22 + 6.2831855) {
            }
            for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
            }
            if ((0.0 <= fVar22) && (fVar22 < 0.7853982)) {
              for (fVar22 = *(float *)(this + 0xb4) + *(float *)(iVar10 + 0x70);
                  fVar22 < -3.1415927; fVar22 = fVar22 + 6.2831855) {
              }
              for (; 3.1415927 <= fVar22; fVar22 = fVar22 - 6.2831855) {
              }
              if (0.7853982 <= fVar22) {
                *(float *)(iVar10 + 0x70) =
                     *(float *)(iVar10 + 0x70) -
                     ((float)*(int *)(this + 0x74) * 6.2831855) / 40.0;
                while (*(float *)(iVar10 + 0x70) < -3.1415927) {
                  *(float *)(iVar10 + 0x70) = *(float *)(iVar10 + 0x70) + 6.2831855;
                }
                while (3.1415927 <= *(float *)(iVar10 + 0x70)) {
                  *(float *)(iVar10 + 0x70) = *(float *)(iVar10 + 0x70) - 6.2831855;
                }
              }
            }
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            if (((*(float *)(iVar10 + 0x10) != iVar10->nShortcutTarget) ||
                (*(float *)(iVar10 + 0x14) != *(float *)(iVar10 + 100))) ||
               (*(float *)(iVar10 + 0x18) != *(float *)(iVar10 + 0x68))) {
              iVar10->nShortcutTarget = (int)*(undefined8 *)(iVar10 + 0x10);
              *(int *)(iVar10 + 100) = (int)((ulong)*(undefined8 *)(iVar10 + 0x10) >> 0x20);
              *(undefined4 *)(iVar10 + 0x68) = *(undefined4 *)(iVar10 + 0x18);
              *(undefined4 *)(iVar10 + 0x6c) = *(undefined4 *)(iVar10 + 0x1c);
            }
            uStack_2f0 = 0;
            uStack_2ec = 0;
            uStack_2e8 = 0xc4c80000;
            uStack_2e4 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_2e0,auStack_180,&uStack_2f0);
            *(int *)(iVar10 + 0x10) = auStack_2e0._0_4_;
            *(int *)(iVar10 + 0x14) = auStack_2e0._4_4_;
            *(undefined4 *)(iVar10 + 0x18) = uStack_2d8;
            *(undefined4 *)(iVar10 + 0x1c) = uStack_2d4;
            fVar22 = (((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0) * 6.2831855) /
                     10053.097;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            uStack_310 = 0;
            uStack_30c = 0;
            uStack_308 = 0xc4c80000;
            uStack_304 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_300,auStack_180,&uStack_310);
            *(int *)(iVar10 + 0x40) = auStack_300._0_4_;
            iVar10->nCmd0_target = auStack_300._4_4_;
            iVar10->nCmd1 = uStack_2f8;
            iVar10->nCmdKind = uStack_2f4;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(-fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_180);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_170);
            __amu__7FVectorFf(*(undefined4 *)(this + 0xc0),auStack_160);
            auStack_150 = *(undefined1 (*) [16])(this + 0x80);
            uStack_330 = 0;
            uStack_32c = 0;
            uStack_328 = 0xc4c80000;
            uStack_324 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_320,auStack_180,&uStack_330);
            iVar10->nCmd3 = auStack_320._0_4_;
            iVar10->nCmdMask = auStack_320._4_4_;
            *(undefined4 *)(iVar10 + 0x58) = uStack_318;
            *(undefined4 *)(iVar10 + 0x5c) = uStack_314;
            uVar13 = *(undefined8 *)(this + 0xb0);
            uVar15 = *(undefined4 *)(this + 0xb8);
            uVar16 = *(undefined4 *)(this + 0xbc);
            *(int *)(iVar10 + 0x20) = (int)uVar13;
            iVar10->bFlags24 = (int)((ulong)uVar13 >> 0x20);
            iVar10->nPhase = uVar15;
            iVar10->cActor = uVar16;
            *(undefined4 *)(iVar10 + 0x20) = 0;
            iVar10->bFlags24 = iVar10->bFlags24 + *(float *)(iVar10 + 0x70);
            while (iVar10->bFlags24 < -3.1415927) {
              iVar10->bFlags24 = iVar10->bFlags24 + 6.2831855;
            }
            while (3.1415927 <= iVar10->bFlags24) {
              iVar10->bFlags24 = iVar10->bFlags24 - 6.2831855;
            }
            iVar10->nCurTurnChr = *(undefined4 *)(this + 0xc0);
          }
          else if (cVar1 == '\0') {
            if (*(float *)(iVar10 + 0x74) != 0.0) {
              *(float *)(iVar10 + 0x74) = *(float *)(iVar10 + 0x74) - fVar21;
              if (0.0 < *(float *)(iVar10 + 0x74)) goto LAB_00575f60;
              *(float *)(iVar10 + 0x78) = -*(float *)(iVar10 + 0x74) * 1.5;
              *(undefined4 *)(iVar10 + 0x74) = 0;
            }
            *(float *)(iVar10 + 0x78) = *(float *)(iVar10 + 0x78) + fVar21 * 1.5;
            if (1.0 < *(float *)(iVar10 + 0x78)) {
              *(undefined4 *)(iVar10 + 0x78) = 0x3f800000;
            }
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_170);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_160);
            uStack_268 = *(undefined4 *)(this + 0x6c);
            fStack_26c = *(float *)(this + 0x68) - 512.0;
            uStack_270 = 0;
            uStack_264 = 0x3f800000;
            auVar9._4_4_ = uStack_268;
            auVar9._0_4_ = fStack_26c;
            auVar9._8_4_ = 0;
            auVar7._12_4_ = 0x3f800000;
            auVar7._0_12_ = auVar9 << 0x20;
            auVar23 = _lqc2(auVar7);
            auVar24 = _lqc2(*(undefined1 (*) [16])(this + 0x90));
            auVar23 = _vsub(auVar23,auVar24);
            auStack_500 = _sqc2(auVar23);
            __ct__7FVectorFPC7FVector(&uStack_260,auStack_500);
            uStack_108 = uStack_258;
            auStack_110 = (undefined1  [8])uStack_260;
            uStack_104 = uStack_254;
            __amu__7FVectorFf(*(undefined4 *)(iVar10 + 0x78),auStack_110);
            auVar24 = _lqc2(*(undefined1 (*) [16])(this + 0x90));
            auVar23 = _lqc2(_auStack_110);
            auVar23 = _vadd(auVar23,auVar24);
            auStack_150 = _sqc2(auVar23);
            uStack_290 = 0;
            uStack_28c = 0;
            uStack_288 = 0xc4c80000;
            uStack_284 = 0x3f800000;
            _auStack_110 = auStack_150;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_280,auStack_180,&uStack_290);
            *(int *)(iVar10 + 0x10) = auStack_280._0_4_;
            *(int *)(iVar10 + 0x14) = auStack_280._4_4_;
            *(undefined4 *)(iVar10 + 0x18) = uStack_278;
            *(undefined4 *)(iVar10 + 0x1c) = uStack_274;
            iVar10->nShortcutTarget = (int)*(undefined8 *)(iVar10 + 0x10);
            *(int *)(iVar10 + 100) = (int)((ulong)*(undefined8 *)(iVar10 + 0x10) >> 0x20);
            *(undefined4 *)(iVar10 + 0x68) = *(undefined4 *)(iVar10 + 0x18);
            *(undefined4 *)(iVar10 + 0x6c) = *(undefined4 *)(iVar10 + 0x1c);
            fVar22 = (((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0) * 6.2831855) /
                     10053.097;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_170);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_160);
            auStack_150 = _auStack_110;
            uStack_2b0 = 0;
            uStack_2ac = 0;
            uStack_2a8 = 0xc4c80000;
            uStack_2a4 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_2a0,auStack_180,&uStack_2b0);
            *(int *)(iVar10 + 0x40) = auStack_2a0._0_4_;
            iVar10->nCmd0_target = auStack_2a0._4_4_;
            iVar10->nCmd1 = uStack_298;
            iVar10->nCmdKind = uStack_294;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            sceVu0RotMatrixY(*(undefined4 *)(this + 0xb4),auStack_180,auStack_180);
            sceVu0RotMatrixY(*(undefined4 *)(iVar10 + 0x70),auStack_180,auStack_180);
            sceVu0RotMatrixY(-fVar22,auStack_180,auStack_180);
            sceVu0RotMatrixX(*(undefined4 *)(this + 0xb0),auStack_180,auStack_180);
            sceVu0RotMatrixZ(*(undefined4 *)(this + 0xb8),auStack_180,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_180);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_170);
            __amu__7FVectorFf(*(float *)(iVar10 + 0x78) * 0.6,auStack_160);
            auStack_150 = _auStack_110;
            uStack_2d0 = 0;
            uStack_2cc = 0;
            uStack_2c8 = 0xc4c80000;
            uStack_2c4 = 0x3f800000;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_2c0,auStack_180,&uStack_2d0);
            iVar10->nCmd3 = auStack_2c0._0_4_;
            iVar10->nCmdMask = auStack_2c0._4_4_;
            *(undefined4 *)(iVar10 + 0x58) = uStack_2b8;
            *(undefined4 *)(iVar10 + 0x5c) = uStack_2b4;
            uVar13 = *(undefined8 *)(this + 0xb0);
            uVar15 = *(undefined4 *)(this + 0xb8);
            uVar16 = *(undefined4 *)(this + 0xbc);
            *(int *)(iVar10 + 0x20) = (int)uVar13;
            iVar10->bFlags24 = (int)((ulong)uVar13 >> 0x20);
            iVar10->nPhase = uVar15;
            iVar10->cActor = uVar16;
            *(undefined4 *)(iVar10 + 0x20) = 0;
            iVar10->bFlags24 = iVar10->bFlags24 + *(float *)(iVar10 + 0x70);
            while (iVar10->bFlags24 < -3.1415927) {
              iVar10->bFlags24 = iVar10->bFlags24 + 6.2831855;
            }
            while (3.1415927 <= iVar10->bFlags24) {
              iVar10->bFlags24 = iVar10->bFlags24 - 6.2831855;
            }
            iVar10->nCurTurnChr = *(float *)(iVar10 + 0x78) * 0.6;
          }
        }
LAB_00575f60:
        if ((*(byte *)(iVar10 + 8) & 1) == 0) {
          iVar11 = 0;
          fVar22 = 0.0;
        }
        else if ((*(char *)(this + 0x5e) == '\0') && (*(char *)(this + 0x5f) < '\x02')) {
          iVar11 = 4;
          fVar22 = 0.008333334;
        }
        else {
          iVar11 = 2;
          fVar22 = 0.008333334;
        }
        for (iVar18 = 0; iVar18 < 0x10; iVar18 = iVar18 + 1) {
          sVar2 = *(short *)(iVar10 + iVar18 * 2 + 0x80);
          if (sVar2 == 1) {
            iVar12 = iVar10 + iVar18 * 4;
            *(float *)(iVar12 + 0xc0) = *(float *)(iVar12 + 0xc0) + fVar21;
            *(float *)(iVar10 + iVar18 * 4 + 0x240) =
                 (0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1;
            *(float *)(iVar10 + iVar18 * 4 + 0x200) =
                 iVar10->nCurTurnChr * ((0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1);
            if ((0.1 <= *(float *)(iVar10 + iVar18 * 4 + 0xc0)) &&
               (*(undefined2 *)(iVar10 + iVar18 * 2 + 0x80) = 0, iVar11 != 0)) {
              iVar12 = rand();
              fVar20 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) *
                       ((float)iVar12 / 2.1474836e+09) -
                       (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
              iVar12 = rand();
              fStack_4a0 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) *
                           ((float)iVar12 / 2.1474836e+09) -
                           (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
              uStack_498 = 0;
              uStack_494 = 0x3f800000;
              auStack_110._4_4_ = fVar20;
              auStack_110._0_4_ = fStack_4a0;
              uStack_108 = 0;
              uStack_104 = 0x3f800000;
              auVar23 = _vmr32(in_vf0);
              auVar24 = _vmr32(auVar23);
              auVar25 = _vmr32(auVar24);
              auStack_150 = _sqc2(in_vf0);
              auStack_160 = _sqc2(auVar23);
              auStack_170 = _sqc2(auVar24);
              auStack_180 = _sqc2(auVar25);
              fStack_49c = fVar20;
              sceVu0RotMatrix(auStack_180,auStack_180,iVar10 + 0x20);
              __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_180);
              __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_170);
              __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_160);
              auStack_150 = *(undefined1 (*) [16])(iVar10 + 0x10);
              *(undefined2 *)(iVar10 + iVar18 * 2 + 0x80) = 1;
              ApplyMatrix__6MatrixCFRC7FVector(auStack_4b0,auStack_180,auStack_110);
              iVar12 = iVar10 + iVar18 * 0x10;
              *(int *)(iVar12 + 0x100) = auStack_4b0._0_4_;
              *(int *)(iVar12 + 0x104) = auStack_4b0._4_4_;
              *(undefined4 *)(iVar12 + 0x108) = uStack_4a8;
              *(undefined4 *)(iVar12 + 0x10c) = uStack_4a4;
              *(float *)(iVar10 + iVar18 * 4 + 0xc0) = fVar22;
              *(float *)(iVar10 + iVar18 * 4 + 0x240) =
                   (0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1;
              *(float *)(iVar10 + iVar18 * 4 + 0x200) =
                   iVar10->nCurTurnChr *
                   ((0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1);
              iVar11 = iVar11 + -1;
              if ((*(char *)(this + 0x5e) == '\0') && (*(char *)(this + 0x5f) < '\x02')) {
                fVar22 = fVar22 + 0.00083333335;
              }
              else {
                fVar22 = fVar22 + 0.00083333335;
              }
            }
          }
          else if ((sVar2 == 0) && (iVar11 != 0)) {
            iVar12 = rand();
            fVar20 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) *
                     ((float)iVar12 / 2.1474836e+09) -
                     (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
            iVar12 = rand();
            fStack_480 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) *
                         ((float)iVar12 / 2.1474836e+09) -
                         (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
            uStack_478 = 0;
            uStack_474 = 0x3f800000;
            auStack_110._4_4_ = fVar20;
            auStack_110._0_4_ = fStack_480;
            uStack_108 = 0;
            uStack_104 = 0x3f800000;
            auVar23 = _vmr32(in_vf0);
            auVar24 = _vmr32(auVar23);
            auVar25 = _vmr32(auVar24);
            auStack_150 = _sqc2(in_vf0);
            auStack_160 = _sqc2(auVar23);
            auStack_170 = _sqc2(auVar24);
            auStack_180 = _sqc2(auVar25);
            fStack_47c = fVar20;
            sceVu0RotMatrix(auStack_180,auStack_180,iVar10 + 0x20);
            __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_180);
            __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_170);
            __amu__7FVectorFf(iVar10->nCurTurnChr,auStack_160);
            auStack_150 = *(undefined1 (*) [16])(iVar10 + 0x10);
            *(undefined2 *)(iVar10 + iVar18 * 2 + 0x80) = 1;
            ApplyMatrix__6MatrixCFRC7FVector(auStack_490,auStack_180,auStack_110);
            iVar12 = iVar10 + iVar18 * 0x10;
            *(int *)(iVar12 + 0x100) = auStack_490._0_4_;
            *(int *)(iVar12 + 0x104) = auStack_490._4_4_;
            *(undefined4 *)(iVar12 + 0x108) = uStack_488;
            *(undefined4 *)(iVar12 + 0x10c) = uStack_484;
            *(float *)(iVar10 + iVar18 * 4 + 0xc0) = fVar22;
            *(float *)(iVar10 + iVar18 * 4 + 0x240) =
                 (0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1;
            *(float *)(iVar10 + iVar18 * 4 + 0x200) =
                 iVar10->nCurTurnChr * ((0.1 - *(float *)(iVar10 + iVar18 * 4 + 0xc0)) / 0.1);
            iVar11 = iVar11 + -1;
            if ((*(char *)(this + 0x5e) == '\0') && (*(char *)(this + 0x5f) < '\x02')) {
              fVar22 = fVar22 + 0.00083333335;
            }
            else {
              fVar22 = fVar22 + 0.00083333335;
            }
          }
        }
        iVar10 = *(int *)(iVar10 + 4);
      }
      else {
        iVar10 = *(int *)(iVar10 + 4);
      }
    }
  }
  return 0;
}

/* ---- 0x00576820  MakePacket__13BtlTarotSelectFv  (size 0x3cf0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void MakePacket__13BtlTarotSelectFv(int this)

{
  bool bVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined1 auVar4 [16];
  undefined8 uVar5;
  undefined1 auVar6 [16];
  bool bVar7;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar8;
  uint uVar9;
  float fVar11;
  ulong uVar10;
  float fVar12;
  float fVar13;
  undefined4 uVar14;
  float *pfVar15;
  int iVar16;
  undefined8 uVar18;
  undefined1 auVar17 [16];
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  byte bVar27;
  float fVar28;
  float fVar29;
  undefined1 in_vf0 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  uint uStack_830;
  int aiStack_620 [24];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [16];
  int aiStack_580 [148];
  undefined1 auStack_330 [8];
  float fStack_328;
  float fStack_324;
  float afStack_320 [4];
  undefined1 auStack_310 [32];
  undefined1 auStack_2f0 [544];
  float afStack_d0 [36];
  char cStack_40;
  char acStack_3f [31];
  byte abStack_20 [20];
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fVar28 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff8610 + 0x459c) + 0x53) << 0x3a) >>
                              0x3c));
  fVar29 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) /
           (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff8610 + 0x459c) + 0x50) << 0x1e) >>
                              0x3c));
  pfVar15 = afStack_d0;
  do {
    *pfVar15 = in_zero_lo;
    pfVar15[1] = in_zero_hi;
    pfVar15[2] = in_zero_udw;
    pfVar15[3] = in_register_0000000c;
    pfVar15 = pfVar15 + 4;
  } while (pfVar15 != (float *)&cStack_40);
  pfVar15 = afStack_320;
  do {
    *pfVar15 = in_zero_lo;
    pfVar15[1] = in_zero_hi;
    pfVar15[2] = in_zero_udw;
    pfVar15[3] = in_register_0000000c;
    pfVar15 = pfVar15 + 4;
  } while (pfVar15 != afStack_d0);
  auStack_330._4_4_ = in_zero_hi;
  auStack_330._0_4_ = in_zero_lo;
  fStack_328 = in_zero_udw;
  fStack_324 = in_register_0000000c;
  auVar30 = _vmr32(in_vf0);
  auVar31 = _vmr32(auVar30);
  auVar32 = _vmr32(auVar31);
  auStack_590 = _sqc2(in_vf0);
  auStack_5a0 = _sqc2(auVar30);
  auStack_5b0 = _sqc2(auVar31);
  auStack_5c0 = _sqc2(auVar32);
  afStack_d0[0] = 0.0;
  afStack_d0[1] = 0.0;
  afStack_d0[2] = 0.0;
  afStack_d0[3] = 1.0;
  afStack_d0[4] = 0.0;
  afStack_d0[5] = (float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[6] = 0.0;
  afStack_d0[7] = 1.0;
  afStack_d0[8] = 0.0;
  afStack_d0[9] = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[10] = 0.0;
  afStack_d0[0xb] = 1.0;
  afStack_d0[0xc] = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
  afStack_d0[0xd] = (float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[0xe] = 0.0;
  afStack_d0[0xf] = 1.0;
  afStack_d0[0x10] = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
  afStack_d0[0x11] = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[0x12] = 0.0;
  afStack_d0[0x13] = 1.0;
  afStack_d0[0x14] = (float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
  afStack_d0[0x15] = (float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[0x16] = 0.0;
  afStack_d0[0x17] = 1.0;
  afStack_d0[0x18] = (float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) / 2.0;
  afStack_d0[0x19] = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) / 2.0;
  afStack_d0[0x1a] = 0.0;
  afStack_d0[0x1b] = 1.0;
  afStack_d0[0x1c] = -64.0;
  afStack_d0[0x1d] = -64.0;
  afStack_d0[0x1e] = 0.0;
  afStack_d0[0x1f] = 1.0;
  fVar12 = 0.0;
  uVar14 = 0x3f800000;
  afStack_d0[0x20] = 64.0;
  afStack_d0[0x21] = 64.0;
  afStack_d0[0x22] = 0.0;
  afStack_d0[0x23] = 1.0;
  iVar20 = *(int *)(this + 0x140);
  iVar25 = 0;
  iVar24 = -1;
  while (iVar20 != 0) {
    if ((long)((ulong)*(byte *)(iVar20 + 8) << 0x3e) < 0) {
      if (2 < CONCAT44((int)((long)((ulong)(uint)(int)*(char *)(iVar20 + 10) << 0x38) >> 0x3f),
                       (int)*(char *)(iVar20 + 10))) {
        iVar24 = iVar25;
      }
      auVar30 = _vmr32(in_vf0);
      auVar31 = _vmr32(auVar30);
      auVar32 = _vmr32(auVar31);
      auStack_590 = _sqc2(in_vf0);
      auStack_5a0 = _sqc2(auVar30);
      auStack_5b0 = _sqc2(auVar31);
      auStack_5c0 = _sqc2(auVar32);
      sceVu0RotMatrix(auStack_5c0,auStack_5c0,iVar20 + 0x20);
      __amu__7FVectorFf(iVar20->nCurTurnChr,auStack_5c0);
      __amu__7FVectorFf(iVar20->nCurTurnChr,auStack_5b0);
      __amu__7FVectorFf(iVar20->nCurTurnChr,auStack_5a0);
      fVar12 = *(float *)(iVar20 + 0x18);
      uVar14 = *(undefined4 *)(iVar20 + 0x1c);
      auStack_590 = *(undefined1 (*) [16])(iVar20 + 0x10);
      RotTransVector(afStack_320 + iVar25 * 4,afStack_d0,auStack_5c0,1);
      aiStack_620[iVar25] = iVar20;
      iVar25 = iVar25 + 1;
      iVar20 = *(int *)(iVar20 + 4);
    }
    else {
      iVar20 = *(int *)(iVar20 + 4);
    }
  }
  for (iVar20 = 0; iVar21 = iVar20, iVar23 = iVar20, iVar20 < iVar25; iVar20 = iVar20 + 1) {
    while (iVar16 = iVar23, iVar21 = iVar21 + 1, iVar21 < iVar25) {
      iVar23 = iVar21;
      if (afStack_320[iVar21 * 4 + 2] <= afStack_320[iVar16 * 4 + 2]) {
        iVar23 = iVar16;
      }
    }
    if (iVar16 != iVar20) {
      if (iVar20 == iVar24) {
        iVar24 = iVar16;
      }
      if (iVar16 == iVar24) {
        iVar24 = iVar20;
      }
      iVar21 = aiStack_620[iVar20];
      aiStack_620[iVar20] = aiStack_620[iVar16];
      aiStack_620[iVar16] = iVar21;
      auStack_330._0_4_ = afStack_320[iVar20 * 4];
      auStack_330._4_4_ = afStack_320[iVar20 * 4 + 1];
      fVar12 = afStack_320[iVar20 * 4 + 2];
      uVar14 = *(undefined4 *)(auStack_310 + iVar20 * 0x10 + -4);
      fStack_328 = fVar12;
      fStack_324 = (float)uVar14;
      fVar11 = afStack_320[iVar16 * 4 + 1];
      fVar13 = afStack_320[iVar16 * 4 + 2];
      uVar8 = *(undefined4 *)(auStack_310 + iVar16 * 0x10 + -4);
      afStack_320[iVar20 * 4] = afStack_320[iVar16 * 4];
      afStack_320[iVar20 * 4 + 1] = fVar11;
      afStack_320[iVar20 * 4 + 2] = fVar13;
      *(undefined4 *)(auStack_310 + iVar20 * 0x10 + -4) = uVar8;
      afStack_320[iVar16 * 4] = (float)auStack_330._0_4_;
      afStack_320[iVar16 * 4 + 1] = (float)auStack_330._4_4_;
      afStack_320[iVar16 * 4 + 2] = fVar12;
      *(undefined4 *)(auStack_310 + iVar16 * 0x10 + -4) = uVar14;
    }
  }
  bVar1 = (*(byte *)(this + 0x40) & 1) == 0;
  uStack_830 = (uint)bVar1;
  if (*(int *)(this + uStack_830 * 4 + 0x18) == 0) {
    uVar8 = __nwa__FUi(0x6670);
    *(undefined4 *)(this + uStack_830 * 4 + 0x18) = uVar8;
    puVar3 = *(undefined4 **)(this + uStack_830 * 4 + 0x18);
    *puVar3 = 0x10000004;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0x50000004;
    *(undefined8 *)(puVar3 + 4) = 0x3000000000008001;
    *(undefined8 *)(puVar3 + 6) = 0xe8e;
    *(undefined8 *)(puVar3 + 8) = 0x60;
    *(undefined8 *)(puVar3 + 10) = 0x14;
    *(undefined8 *)(puVar3 + 0xc) = 5;
    *(undefined8 *)(puVar3 + 0xe) = 0;
    *(undefined8 *)(puVar3 + 0x10) = 0x3001;
    *(undefined8 *)(puVar3 + 0x12) = 0x47;
    iVar20 = 5;
    for (iVar21 = 0; iVar21 < 0x16; iVar21 = iVar21 + 1) {
      puVar3[iVar20 * 4 + 2] = 0;
      puVar3[iVar20 * 4 + 3] = 0;
      puVar3[(iVar20 + 1) * 4] = 0x10000010;
      puVar3[(iVar20 + 1) * 4 + 1] = 0;
      puVar3[(iVar20 + 1) * 4 + 2] = 0;
      puVar3[(iVar20 + 1) * 4 + 3] = 0x50000010;
      *(undefined8 *)(puVar3 + (iVar20 + 2) * 4) = 0x3000000000000001;
      *(undefined8 *)(puVar3 + (iVar20 + 2) * 4 + 2) = 0x6ee;
      *(undefined8 *)(puVar3 + (iVar20 + 3) * 4) = 1;
      *(undefined8 *)(puVar3 + (iVar20 + 3) * 4 + 2) = 0x3f;
      *(undefined8 *)(puVar3 + (iVar20 + 4) * 4) = 0x44;
      *(undefined8 *)(puVar3 + (iVar20 + 4) * 4 + 2) = 0x42;
      *(undefined8 *)(puVar3 + (iVar20 + 5) * 4 + 2) = 0;
      auVar30._4_4_ = in_zero_hi;
      auVar30._0_4_ = in_zero_lo;
      auVar30._8_4_ = in_zero_udw;
      auVar30._12_4_ = in_register_0000000c;
      auVar31._8_4_ = fVar12;
      auVar31._0_8_ = 0x8400000000000001;
      auVar31._12_4_ = uVar14;
      auVar30 = _pcpyld(auVar30,auVar31);
      *(long *)(puVar3 + (iVar20 + 6) * 4) = auVar30._0_8_;
      *(undefined8 *)(puVar3 + (iVar20 + 6) * 4 + 2) = 0xc12c12f0;
      *(undefined8 *)(puVar3 + (iVar20 + 7) * 4) = 0x55;
      *(undefined8 *)(puVar3 + (iVar20 + 7) * 4 + 2) = 0;
      *(undefined8 *)(puVar3 + (iVar20 + 0xb) * 4) = 0x3400000000008004;
      *(undefined8 *)(puVar3 + (iVar20 + 0xb) * 4 + 2) = 0x412;
      iVar23 = iVar20 + 0x12;
      puVar3[iVar23 * 4] = 0x50000000;
      puVar3[iVar23 * 4 + 1] =
           *(undefined4 *)
            (*(int *)(iGpffff8610 + 0x45b4) +
             (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 10) * 4 + 0xc);
      puVar3[iVar23 * 4 + 2] = 0;
      puVar3[iVar23 * 4 + 3] = 0;
      puVar3[(iVar20 + 0x13) * 4] = 0x10000035;
      puVar3[(iVar20 + 0x13) * 4 + 1] = 0;
      puVar3[(iVar20 + 0x13) * 4 + 2] = 0;
      puVar3[(iVar20 + 0x13) * 4 + 3] = 0x50000035;
      *(undefined8 *)(puVar3 + (iVar20 + 0x14) * 4) = 0x3000000000000001;
      *(undefined8 *)(puVar3 + (iVar20 + 0x14) * 4 + 2) = 0x6ee;
      *(undefined8 *)(puVar3 + (iVar20 + 0x15) * 4) = 1;
      *(undefined8 *)(puVar3 + (iVar20 + 0x15) * 4 + 2) = 0x3f;
      *(undefined8 *)(puVar3 + (iVar20 + 0x16) * 4) = 0x48;
      *(undefined8 *)(puVar3 + (iVar20 + 0x16) * 4 + 2) = 0x42;
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45b4),1);
      *(undefined8 *)(puVar3 + (iVar20 + 0x17) * 4) = uVar5;
      *(undefined8 *)(puVar3 + (iVar20 + 0x17) * 4 + 2) = 0;
      *(undefined8 *)(puVar3 + (iVar20 + 0x18) * 4) = 0x6400000000008010;
      *(undefined8 *)(puVar3 + (iVar20 + 0x18) * 4 + 2) = 0x43c310;
      iVar20 = iVar20 + 0x19;
      for (iVar23 = 0; iVar23 < 0x10; iVar23 = iVar23 + 1) {
        *(undefined8 *)(puVar3 + iVar20 * 4) = 0x156;
        *(undefined8 *)(puVar3 + (iVar20 + 1) * 4) = 0;
        uVar9 = (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 4);
        *(ulong *)(puVar3 + (iVar20 + 2) * 4) =
             (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 2) << 4) |
             CONCAT44((int)(short)((uVar9 << 4) >> 0x10),uVar9 << 0x14);
        iVar20 = iVar20 + 3;
      }
    }
    puVar3[iVar20 * 4] = 0x50000000;
    puVar3[iVar20 * 4 + 1] =
         *(undefined4 *)
          (*(int *)(iGpffff8610 + 0x45b0) +
           (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b0) + 10) * 4 + 0xc);
    puVar3[iVar20 * 4 + 2] = 0;
    puVar3[iVar20 * 4 + 3] = 0;
    puVar3[(iVar20 + 1) * 4] = 0x1000000d;
    puVar3[(iVar20 + 1) * 4 + 1] = 0;
    puVar3[(iVar20 + 1) * 4 + 2] = 0;
    puVar3[(iVar20 + 1) * 4 + 3] = 0x5000000d;
    *(undefined8 *)(puVar3 + (iVar20 + 2) * 4) = 0x4000000000000001;
    *(undefined8 *)(puVar3 + (iVar20 + 2) * 4 + 2) = 0x6eee;
    *(undefined8 *)(puVar3 + (iVar20 + 3) * 4) = 1;
    *(undefined8 *)(puVar3 + (iVar20 + 3) * 4 + 2) = 0x3f;
    *(undefined8 *)(puVar3 + (iVar20 + 4) * 4) = 0x44;
    *(undefined8 *)(puVar3 + (iVar20 + 4) * 4 + 2) = 0x42;
    uVar10 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45b0),1);
    *(ulong *)(puVar3 + (iVar20 + 5) * 4) = uVar10 & 0xfffffffc0fffff | 0x2000000001300000;
    *(undefined8 *)(puVar3 + (iVar20 + 5) * 4 + 2) = 0x16;
    *(undefined8 *)(puVar3 + (iVar20 + 6) * 4 + 2) = 0;
    auVar32._4_4_ = in_zero_hi;
    auVar32._0_4_ = in_zero_lo;
    auVar32._8_4_ = in_zero_udw;
    auVar32._12_4_ = in_register_0000000c;
    auVar6._8_4_ = fVar12;
    auVar6._0_8_ = 0xe400000000008001;
    auVar6._12_4_ = uVar14;
    auVar30 = _pcpyld(auVar32,auVar6);
    *(long *)(puVar3 + (iVar20 + 7) * 4) = auVar30._0_8_;
    uVar18 = auVar30._8_8_;
    *(undefined8 *)(puVar3 + (iVar20 + 7) * 4 + 2) = 0x43c343c343c310;
    *(undefined8 *)(puVar3 + (iVar20 + 8) * 4) = 0x156;
    *(undefined8 *)(puVar3 + (iVar20 + 8) * 4 + 2) = 0x80808080;
    *(undefined8 *)(puVar3 + (iVar20 + 9) * 4) = 0x2600000;
    *(undefined8 *)(puVar3 + (iVar20 + 10) * 4) = 0x4400660;
    *(undefined8 *)(puVar3 + (iVar20 + 0xb) * 4) = 0;
    *(undefined8 *)(puVar3 + (iVar20 + 0xc) * 4) = 0x2600630;
    *(undefined8 *)(puVar3 + (iVar20 + 0xd) * 4) = 0x630;
    *(undefined8 *)(puVar3 + (iVar20 + 0xe) * 4) = 0x2100ab0;
    iVar21 = iVar20 + 0xf;
    puVar3[iVar21 * 4] = 0x50000000;
    puVar3[iVar21 * 4 + 1] =
         *(undefined4 *)
          (*(int *)(iGpffff8610 + 0x45b4) +
           (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 10) * 4 + 0xc);
    puVar3[iVar21 * 4 + 2] = 0;
    puVar3[iVar21 * 4 + 3] = 0;
    puVar3[(iVar20 + 0x10) * 4] = 0x1000000a;
    puVar3[(iVar20 + 0x10) * 4 + 1] = 0;
    puVar3[(iVar20 + 0x10) * 4 + 2] = 0;
    puVar3[(iVar20 + 0x10) * 4 + 3] = 0x5000000a;
    *(undefined8 *)(puVar3 + (iVar20 + 0x11) * 4) = 0x3000000000000001;
    *(undefined8 *)(puVar3 + (iVar20 + 0x11) * 4 + 2) = 0x6ee;
    *(undefined8 *)(puVar3 + (iVar20 + 0x12) * 4) = 1;
    *(undefined8 *)(puVar3 + (iVar20 + 0x12) * 4 + 2) = 0x3f;
    *(undefined8 *)(puVar3 + (iVar20 + 0x13) * 4) = 0x48;
    *(undefined8 *)(puVar3 + (iVar20 + 0x13) * 4 + 2) = 0x42;
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45b4),1);
    *(undefined8 *)(puVar3 + (iVar20 + 0x14) * 4) = uVar5;
    *(undefined8 *)(puVar3 + (iVar20 + 0x14) * 4 + 2) = 0;
    auVar17._8_8_ = uVar18;
    auVar17._0_8_ = 0xa400000000008001;
    auVar4._4_4_ = in_zero_hi;
    auVar4._0_4_ = in_zero_lo;
    auVar4._8_4_ = in_zero_udw;
    auVar4._12_4_ = in_register_0000000c;
    auVar30 = _pcpyld(auVar4,auVar17);
    *(long *)(puVar3 + (iVar20 + 0x15) * 4) = auVar30._0_8_;
    *(undefined8 *)(puVar3 + (iVar20 + 0x15) * 4 + 2) = 0x4343c3c310;
    *(undefined8 *)(puVar3 + (iVar20 + 0x16) * 4) = 0x154;
    *(undefined8 *)(puVar3 + (iVar20 + 0x16) * 4 + 2) = 0x80808080;
    *(undefined8 *)(puVar3 + (iVar20 + 0x17) * 4) = 0;
    *(long *)(puVar3 + (iVar20 + 0x18) * 4) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 4) << 4) << 0x10;
    *(long *)(puVar3 + (iVar20 + 0x19) * 4) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 2) << 4);
    *(long *)(puVar3 + (iVar20 + 0x1a) * 4) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 4) << 4) << 0x10;
  }
  iVar20 = *(int *)(this + uStack_830 * 4 + 0x18);
  iVar21 = 5;
  for (iVar23 = 0; iVar23 < iVar25; iVar23 = iVar23 + 1) {
    auVar30 = _vmr32(in_vf0);
    auVar31 = _vmr32(auVar30);
    auVar32 = _vmr32(auVar31);
    auStack_590 = _sqc2(in_vf0);
    auStack_5a0 = _sqc2(auVar30);
    auStack_5b0 = _sqc2(auVar31);
    auStack_5c0 = _sqc2(auVar32);
    sceVu0RotMatrix(auStack_5c0,auStack_5c0,aiStack_620[iVar23] + 0x20);
    __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5c0);
    __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5b0);
    __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5a0);
    _auStack_330 = *(undefined1 (*) [16])(aiStack_620[iVar23] + 0x10);
    if (*(float *)(this + 0xc4) != 0.0) {
      auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
      auVar30 = _lqc2(_auStack_330);
      auVar30 = _vadd(auVar30,auVar31);
      _auStack_330 = _sqc2(auVar30);
    }
    auStack_590 = _auStack_330;
    RotTransVector(afStack_320,afStack_d0,auStack_5c0,1);
    if (CONCAT44((int)((long)((ulong)(uint)(int)*(char *)(aiStack_620[iVar23] + 10) << 0x38) >> 0x3f
                      ),(int)*(char *)(aiStack_620[iVar23] + 10)) < 3) {
      auVar30 = _vmr32(in_vf0);
      auVar31 = _vmr32(auVar30);
      auVar32 = _vmr32(auVar31);
      auStack_590 = _sqc2(in_vf0);
      auStack_5a0 = _sqc2(auVar30);
      auStack_5b0 = _sqc2(auVar31);
      auStack_5c0 = _sqc2(auVar32);
      sceVu0RotMatrix(auStack_5c0,auStack_5c0,aiStack_620[iVar23] + 0x20);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5c0);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5b0);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5a0);
      _auStack_330 = *(undefined1 (*) [16])(aiStack_620[iVar23] + 0x40);
      if (*(float *)(this + 0xc4) != 0.0) {
        auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
        auVar30 = _lqc2(_auStack_330);
        auVar30 = _vadd(auVar30,auVar31);
        _auStack_330 = _sqc2(auVar30);
      }
      auStack_590 = _auStack_330;
      RotTransVector(auStack_310,afStack_d0 + 4,auStack_5c0,2);
      auVar30 = _vmr32(in_vf0);
      auVar31 = _vmr32(auVar30);
      auVar32 = _vmr32(auVar31);
      auStack_590 = _sqc2(in_vf0);
      auStack_5a0 = _sqc2(auVar30);
      auStack_5b0 = _sqc2(auVar31);
      auStack_5c0 = _sqc2(auVar32);
      sceVu0RotMatrix(auStack_5c0,auStack_5c0,aiStack_620[iVar23] + 0x20);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5c0);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5b0);
      __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + 0x30),auStack_5a0);
      _auStack_330 = *(undefined1 (*) [16])(aiStack_620[iVar23] + 0x50);
      if (*(float *)(this + 0xc4) != 0.0) {
        auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
        auVar30 = _lqc2(_auStack_330);
        auVar30 = _vadd(auVar30,auVar31);
        _auStack_330 = _sqc2(auVar30);
      }
      auStack_590 = _auStack_330;
      RotTransVector(auStack_2f0,afStack_d0 + 4,auStack_5c0,2);
    }
    else {
      RotTransVector(auStack_310,afStack_d0 + 0xc,auStack_5c0,4);
    }
    iVar26 = 0;
    for (iVar16 = 0; iVar16 < 0x10; iVar16 = iVar16 + 1) {
      sVar2 = *(short *)(aiStack_620[iVar23] + iVar16 * 2 + 0x80);
      if (CONCAT44(sVar2 >> 0xf,(int)sVar2) != 0) {
        auVar30 = _vmr32(in_vf0);
        auVar31 = _vmr32(auVar30);
        auVar32 = _vmr32(auVar31);
        auStack_590 = _sqc2(in_vf0);
        auStack_5a0 = _sqc2(auVar30);
        auStack_5b0 = _sqc2(auVar31);
        auStack_5c0 = _sqc2(auVar32);
        __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + iVar16 * 4 + 0x200),auStack_5c0);
        __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + iVar16 * 4 + 0x200),auStack_5b0);
        __amu__7FVectorFf(*(undefined4 *)(aiStack_620[iVar23] + iVar16 * 4 + 0x200),auStack_5a0);
        _auStack_330 = *(undefined1 (*) [16])(aiStack_620[iVar23] + iVar16 * 0x10 + 0x100);
        if (*(float *)(this + 0xc4) != 0.0) {
          auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
          auVar30 = _lqc2(_auStack_330);
          auVar30 = _vadd(auVar30,auVar31);
          _auStack_330 = _sqc2(auVar30);
        }
        auStack_590 = _auStack_330;
        RotTransVector(afStack_320 + (iVar26 * 2 + 5) * 4,afStack_d0 + 0x1c,auStack_5c0,2);
        fVar12 = *(float *)(aiStack_620[iVar23] + iVar16 * 4 + 0x240) * 128.0;
        if (fVar12 < 2.1474836e+09) {
          bVar27 = (byte)(int)fVar12;
        }
        else {
          bVar27 = (byte)(int)(fVar12 - 2.1474836e+09);
        }
        abStack_20[iVar26] = bVar27;
        iVar26 = iVar26 + 1;
      }
    }
    sceVu0RotTransPersN(aiStack_580,this + 0x100,afStack_320,iVar26 * 2 + 5,0);
    bVar7 = false;
    if ((1.5707964 <= *(float *)(aiStack_620[iVar23] + 0x24)) ||
       (*(float *)(aiStack_620[iVar23] + 0x24) <= -1.5707964)) {
      bVar7 = true;
    }
    cStack_40 = '\0';
    for (iVar16 = 0; iVar16 < 5; iVar16 = iVar16 + 1) {
      if ((((aiStack_580[iVar16 * 4] >> 0x1f < 0) || (0xffff < aiStack_580[iVar16 * 4])) ||
          (aiStack_580[iVar16 * 4 + 1] >> 0x1f < 0)) ||
         ((0xffff < aiStack_580[iVar16 * 4 + 1] || (aiStack_580[iVar16 * 4 + 2] >> 0x1f < 0)))) {
        cStack_40 = '\x01';
      }
    }
    if (((aiStack_580[0] < 0x7000) && (aiStack_580[4] < 0x7000)) &&
       ((aiStack_580[8] < 0x7000 && ((aiStack_580[0xc] < 0x7000 && (aiStack_580[0x10] < 0x7000))))))
    {
      cStack_40 = '\x01';
    }
    if ((((0x9000 < aiStack_580[0]) && (0x9000 < aiStack_580[4])) && (0x9000 < aiStack_580[8])) &&
       ((0x9000 < aiStack_580[0xc] && (0x9000 < aiStack_580[0x10])))) {
      cStack_40 = '\x01';
    }
    if (((aiStack_580[1] < 0x7200) && (aiStack_580[5] < 0x7200)) &&
       ((aiStack_580[9] < 0x7200 && ((aiStack_580[0xd] < 0x7200 && (aiStack_580[0x11] < 0x7200))))))
    {
      cStack_40 = '\x01';
    }
    if ((((0x8e00 < aiStack_580[1]) && (0x8e00 < aiStack_580[5])) && (0x8e00 < aiStack_580[9])) &&
       ((0x8e00 < aiStack_580[0xd] && (0x8e00 < aiStack_580[0x11])))) {
      cStack_40 = '\x01';
    }
    *(byte *)(aiStack_620[iVar23] + 8) = *(byte *)(aiStack_620[iVar23] + 8) & 0xfb;
    if (cStack_40 != '\0') {
      *(byte *)(aiStack_620[iVar23] + 8) = *(byte *)(aiStack_620[iVar23] + 8) & 0xfb | 4;
    }
    for (iVar16 = 0; iVar16 < iVar26; iVar16 = iVar16 + 1) {
      acStack_3f[iVar16] = '\0';
      if (((aiStack_580[(iVar16 * 2 + 5) * 4] >> 0x1f < 0) ||
          (0xffff < aiStack_580[(iVar16 * 2 + 5) * 4])) ||
         ((aiStack_580[(iVar16 * 2 + 5) * 4 + 1] >> 0x1f < 0 ||
          ((0xffff < aiStack_580[(iVar16 * 2 + 5) * 4 + 1] ||
           (aiStack_580[(iVar16 * 2 + 5) * 4 + 2] >> 0x1f < 0)))))) {
        acStack_3f[iVar16] = '\x01';
      }
      if ((((aiStack_580[(iVar16 * 2 + 6) * 4] >> 0x1f < 0) ||
           (0xffff < aiStack_580[(iVar16 * 2 + 6) * 4])) ||
          (aiStack_580[(iVar16 * 2 + 6) * 4 + 1] >> 0x1f < 0)) ||
         ((0xffff < aiStack_580[(iVar16 * 2 + 6) * 4 + 1] ||
          (aiStack_580[(iVar16 * 2 + 6) * 4 + 2] >> 0x1f < 0)))) {
        acStack_3f[iVar16] = '\x01';
      }
      if ((aiStack_580[(iVar16 * 2 + 5) * 4] < 0x7000) &&
         (aiStack_580[(iVar16 * 2 + 6) * 4] < 0x7000)) {
        acStack_3f[iVar16] = '\x01';
      }
      if ((0x9000 < aiStack_580[(iVar16 * 2 + 5) * 4]) &&
         (0x9000 < aiStack_580[(iVar16 * 2 + 6) * 4])) {
        acStack_3f[iVar16] = '\x01';
      }
      if ((aiStack_580[(iVar16 * 2 + 5) * 4 + 1] < 0x7200) &&
         (aiStack_580[(iVar16 * 2 + 6) * 4 + 1] < 0x7200)) {
        acStack_3f[iVar16] = '\x01';
      }
      if ((0x8e00 < aiStack_580[(iVar16 * 2 + 5) * 4 + 1]) &&
         (0x8e00 < aiStack_580[(iVar16 * 2 + 6) * 4 + 1])) {
        acStack_3f[iVar16] = '\x01';
      }
    }
    *(undefined4 *)(iVar20 + iVar21 * 0x10) = 0x50000000;
    if ((iVar24 < 0) || (iVar23 != iVar24)) {
      iVar16 = *(int *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484);
      *(undefined4 *)(iVar20 + iVar21 * 0x10 + 4) =
           *(undefined4 *)(iVar16 + (uint)*(ushort *)(iVar16 + 10) * 4 + 0xc);
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484),1);
      *(undefined8 *)(iVar20 + (iVar21 + 5) * 0x10) = uVar5;
      if (((*(char *)(aiStack_620[iVar23] + 10) == '\x01') ||
          (*(char *)(aiStack_620[iVar23] + 10) == '\x02')) && (bVar7)) {
        cStack_40 = '\x01';
      }
      bVar7 = false;
    }
    else if (bVar7) {
      *(undefined4 *)(iVar20 + iVar21 * 0x10 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff8610 + 0x45ac) +
             (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45ac) + 10) * 4 + 0xc);
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45ac),1);
      *(undefined8 *)(iVar20 + (iVar21 + 5) * 0x10) = uVar5;
    }
    else {
      iVar16 = *(int *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484);
      *(undefined4 *)(iVar20 + iVar21 * 0x10 + 4) =
           *(undefined4 *)(iVar16 + (uint)*(ushort *)(iVar16 + 10) * 4 + 0xc);
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484),1);
      *(undefined8 *)(iVar20 + (iVar21 + 5) * 0x10) = uVar5;
    }
    if (cStack_40 == '\0') {
      fVar12 = 16.0 / (float)aiStack_580[3];
      *(ulong *)(iVar20 + (iVar21 + 8) * 0x10) =
           CONCAT44((fVar29 / 2.0) * fVar12,(fVar28 / 2.0) * fVar12);
      *(ulong *)(iVar20 + (iVar21 + 8) * 0x10 + 8) = (ulong)(uint)fVar12 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[2];
      if (aiStack_580[2] < 0) {
        iVar16 = aiStack_580[2] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 9) * 0x10) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[0] | (long)aiStack_580[1] << 0x10;
      fVar12 = 16.0 / (float)aiStack_580[7];
      if ((bVar7) && ((iGpffff8610->nCmd1 & 2) != 0)) {
        fStack_8 = fVar28 * fVar12;
        fStack_c = fVar29 * fVar12;
      }
      else {
        fStack_8 = 0.0;
        fStack_c = 0.0;
      }
      *(ulong *)(iVar20 + (iVar21 + 9) * 0x10 + 8) = CONCAT44(fStack_c,fStack_8);
      *(ulong *)(iVar20 + (iVar21 + 10) * 0x10) = (ulong)(uint)fVar12 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[6];
      if (aiStack_580[6] < 0) {
        iVar16 = aiStack_580[6] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 10) * 0x10 + 8) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[4] | (long)aiStack_580[5] << 0x10;
      *(ulong *)(iVar20 + (iVar21 + 0x10) * 0x10 + 8) = CONCAT44(fStack_c,fStack_8);
      *(ulong *)(iVar20 + (iVar21 + 0x11) * 0x10) = (ulong)(uint)fVar12 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[6];
      if (aiStack_580[6] < 0) {
        iVar16 = aiStack_580[6] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 0x11) * 0x10 + 8) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[4] | (long)aiStack_580[5] << 0x10;
      fVar12 = 16.0 / (float)aiStack_580[0xf];
      if ((bVar7) && ((iGpffff8610->nCmd1 & 2) != 0)) {
        fStack_8 = 0.0;
        fStack_c = fVar29 * fVar12;
      }
      else {
        fStack_8 = fVar28 * fVar12;
        fStack_c = 0.0;
      }
      *(ulong *)(iVar20 + (iVar21 + 0xc) * 0x10) = CONCAT44(fStack_c,fStack_8);
      *(ulong *)(iVar20 + (iVar21 + 0xc) * 0x10 + 8) = (ulong)(uint)fVar12 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[0xe];
      if (aiStack_580[0xe] < 0) {
        iVar16 = aiStack_580[0xe] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 0xd) * 0x10) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[0xc] | (long)aiStack_580[0xd] << 0x10;
      fVar12 = 16.0 / (float)aiStack_580[0x13];
      if ((bVar7) && ((iGpffff8610->nCmd1 & 2) != 0)) {
        fStack_8 = 0.0;
        fStack_c = 0.0;
      }
      else {
        fStack_8 = fVar28 * fVar12;
        fStack_c = fVar29 * fVar12;
      }
      *(ulong *)(iVar20 + (iVar21 + 0xd) * 0x10 + 8) = CONCAT44(fStack_c,fStack_8);
      *(ulong *)(iVar20 + (iVar21 + 0xe) * 0x10) = (ulong)(uint)fVar12 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[0x12];
      if (aiStack_580[0x12] < 0) {
        iVar16 = aiStack_580[0x12] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[0x10] | (long)aiStack_580[0x11] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_580[0xb];
      if ((bVar7) && ((iGpffff8610->nCmd1 & 2) != 0)) {
        fStack_8 = fVar28 * fStack_4;
        fStack_c = 0.0;
      }
      else {
        fStack_8 = 0.0;
        fStack_c = fVar29 * fStack_4;
      }
      *(ulong *)(iVar20 + (iVar21 + 0xf) * 0x10) = CONCAT44(fStack_c,fStack_8);
      *(ulong *)(iVar20 + (iVar21 + 0xf) * 0x10 + 8) = (ulong)(uint)fStack_4 << 0x20 | 0x80808080;
      iVar16 = aiStack_580[10];
      if (aiStack_580[10] < 0) {
        iVar16 = aiStack_580[10] + 0xf;
      }
      *(long *)(iVar20 + (iVar21 + 0x10) * 0x10) =
           (long)(iVar16 >> 4) << 0x20 | (long)aiStack_580[8] | (long)aiStack_580[9] << 0x10;
    }
    else {
      *(undefined8 *)(iVar20 + (iVar21 + 9) * 0x10) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 10) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xd) * 0x10) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0x10) * 0x10) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0x11) * 0x10 + 8) = 0x71006f00;
    }
    iVar21 = iVar21 + 0x19;
    iVar16 = 0;
    if (cStack_40 == '\0') {
      for (iVar22 = 0; iVar22 < iVar26; iVar22 = iVar22 + 1) {
        if (acStack_3f[iVar22] == '\0') {
          *(ulong *)(iVar20 + iVar21 * 0x10 + 8) = (ulong)abStack_20[iVar22] << 0x18 | 0x100208080;
          iVar19 = aiStack_580[(iVar22 * 2 + 5) * 4 + 2];
          if (iVar19 < 0) {
            iVar19 = iVar19 + 0xf;
          }
          *(long *)(iVar20 + (iVar21 + 1) * 0x10 + 8) =
               (long)(iVar19 >> 4) << 0x20 |
               (long)aiStack_580[(iVar22 * 2 + 5) * 4] |
               (long)aiStack_580[(iVar22 * 2 + 5) * 4 + 1] << 0x10;
          iVar19 = aiStack_580[(iVar22 * 2 + 6) * 4 + 2];
          if (iVar19 < 0) {
            iVar19 = iVar19 + 0xf;
          }
          *(long *)(iVar20 + (iVar21 + 2) * 0x10 + 8) =
               (long)(iVar19 >> 4) << 0x20 |
               (long)aiStack_580[(iVar22 * 2 + 6) * 4] |
               (long)aiStack_580[(iVar22 * 2 + 6) * 4 + 1] << 0x10;
          iVar21 = iVar21 + 3;
          iVar16 = iVar16 + 1;
        }
      }
    }
    for (; iVar16 < 0x10; iVar16 = iVar16 + 1) {
      *(undefined8 *)(iVar20 + (iVar21 + 1) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 2) * 0x10 + 8) = 0x71006f00;
      iVar21 = iVar21 + 3;
    }
  }
  for (; iVar23 < 0x16; iVar23 = iVar23 + 1) {
    *(undefined4 *)(iVar20 + iVar21 * 0x10) = 0x50000000;
    iVar24 = *(int *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484);
    *(undefined4 *)(iVar20 + iVar21 * 0x10 + 4) =
         *(undefined4 *)(iVar24 + (uint)*(ushort *)(iVar24 + 10) * 4 + 0xc);
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484),1);
    *(undefined8 *)(iVar20 + (iVar21 + 5) * 0x10) = uVar5;
    *(undefined8 *)(iVar20 + (iVar21 + 9) * 0x10) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 10) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xd) * 0x10) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0x10) * 0x10) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0x11) * 0x10 + 8) = 0x71006f00;
    iVar21 = iVar21 + 0x19;
    for (iVar24 = 0; iVar24 < 0x10; iVar24 = iVar24 + 1) {
      *(undefined8 *)(iVar20 + (iVar21 + 1) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 2) * 0x10 + 8) = 0x71006f00;
      iVar21 = iVar21 + 3;
    }
  }
  if (((ulong)*(byte *)(this + 0x5c) & 0x3f) >> 3 == 0) {
    *(undefined8 *)(iVar20 + (iVar21 + 9) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 10) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xb) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xc) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xd) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar10 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45b0),1);
    if ((iGpffff8610->nCmd1 & 2) == 0) {
      *(ulong *)(iVar20 + (iVar21 + 6) * 0x10) = uVar10 & 0xffffffffffffff | 0x200000000000000;
    }
    else {
      *(ulong *)(iVar20 + (iVar21 + 6) * 0x10) = uVar10 & 0xffffffffffffff | 0x300000000000000;
    }
    iVar24 = iGpffff8610->nCmd1;
    if (iVar24 == 3) {
      afStack_d0[0] = -51.0;
      afStack_d0[1] = -16.0;
      afStack_d0[2] = 0.0;
      afStack_d0[3] = 1.0;
      afStack_d0[4] = 51.0;
      afStack_d0[5] = 14.0;
      afStack_d0[6] = 0.0;
      afStack_d0[7] = 1.0;
      afStack_d0[8] = -90.0;
      afStack_d0[9] = 16.0;
      afStack_d0[10] = 0.0;
      afStack_d0[0xb] = 1.0;
      afStack_d0[0xc] = 9.0;
      afStack_d0[0xd] = 54.0;
      afStack_d0[0xe] = 0.0;
      afStack_d0[0xf] = 1.0;
      afStack_d0[0x10] = 18.0;
      afStack_d0[0x11] = 16.0;
      afStack_d0[0x12] = 0.0;
      afStack_d0[0x13] = 1.0;
      afStack_d0[0x14] = 90.0;
      afStack_d0[0x15] = 49.0;
      afStack_d0[0x16] = 0.0;
      afStack_d0[0x17] = 1.0;
    }
    else if (iVar24 == 2) {
      afStack_d0[0] = -91.5;
      afStack_d0[1] = -16.0;
      afStack_d0[2] = 0.0;
      afStack_d0[3] = 1.0;
      afStack_d0[4] = 10.5;
      afStack_d0[5] = 14.0;
      afStack_d0[6] = 0.0;
      afStack_d0[7] = 1.0;
      afStack_d0[8] = 0.0;
      afStack_d0[9] = 0.0;
      afStack_d0[10] = 0.0;
      afStack_d0[0xb] = 1.0;
      afStack_d0[0xc] = 0.0;
      afStack_d0[0xd] = 0.0;
      afStack_d0[0xe] = 0.0;
      afStack_d0[0xf] = 1.0;
      afStack_d0[0x10] = 19.5;
      afStack_d0[0x11] = -16.0;
      afStack_d0[0x12] = 0.0;
      afStack_d0[0x13] = 1.0;
      afStack_d0[0x14] = 91.5;
      afStack_d0[0x15] = 17.0;
      afStack_d0[0x16] = 0.0;
      afStack_d0[0x17] = 1.0;
    }
    else if (iVar24 == 1) {
      afStack_d0[0] = 0.0;
      afStack_d0[1] = 0.0;
      afStack_d0[2] = 0.0;
      afStack_d0[3] = 1.0;
      afStack_d0[4] = 0.0;
      afStack_d0[5] = 0.0;
      afStack_d0[6] = 0.0;
      afStack_d0[7] = 1.0;
      afStack_d0[8] = -90.0;
      afStack_d0[9] = -16.0;
      afStack_d0[10] = 0.0;
      afStack_d0[0xb] = 1.0;
      afStack_d0[0xc] = 9.0;
      afStack_d0[0xd] = 22.0;
      afStack_d0[0xe] = 0.0;
      afStack_d0[0xf] = 1.0;
      afStack_d0[0x10] = 18.0;
      afStack_d0[0x11] = -16.0;
      afStack_d0[0x12] = 0.0;
      afStack_d0[0x13] = 1.0;
      afStack_d0[0x14] = 90.0;
      afStack_d0[0x15] = 17.0;
      afStack_d0[0x16] = 0.0;
      afStack_d0[0x17] = 1.0;
    }
    auVar30 = _vmr32(in_vf0);
    auVar31 = _vmr32(auVar30);
    auVar32 = _vmr32(auVar31);
    auStack_590 = _sqc2(in_vf0);
    auStack_5a0 = _sqc2(auVar30);
    auStack_5b0 = _sqc2(auVar31);
    auStack_5c0 = _sqc2(auVar32);
    sceVu0RotMatrix(auStack_5c0,auStack_5c0,this + 0xe0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf0),auStack_5c0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf0),auStack_5b0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf0),auStack_5a0);
    _auStack_330 = *(undefined1 (*) [16])(this + 0xd0);
    if (*(float *)(this + 0xc4) != 0.0) {
      auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
      auVar30 = _lqc2(_auStack_330);
      auVar30 = _vadd(auVar30,auVar31);
      _auStack_330 = _sqc2(auVar30);
    }
    auStack_590 = _auStack_330;
    RotTransVector(afStack_320,afStack_d0,auStack_5c0,6);
    sceVu0RotTransPersN(aiStack_580,this + 0x100,afStack_320,6,0);
    cStack_40 = '\0';
    for (iVar24 = 0; iVar24 < 6; iVar24 = iVar24 + 1) {
      if ((((aiStack_580[iVar24 * 4] < 0) || (0xffff < aiStack_580[iVar24 * 4])) ||
          (aiStack_580[iVar24 * 4 + 1] < 0)) ||
         ((0xffff < aiStack_580[iVar24 * 4 + 1] || (aiStack_580[iVar24 * 4 + 2] < 0)))) {
        cStack_40 = '\x01';
      }
    }
    if (cStack_40 == '\0') {
      if ((iGpffff8610->nCmd1 & 2) == 0) {
        *(undefined8 *)(iVar20 + (iVar21 + 9) * 0x10 + 8) = 0x71006f00;
        *(undefined8 *)(iVar20 + (iVar21 + 10) * 0x10 + 8) = 0x71006f00;
      }
      else {
        uVar9 = __fixunssfdi((float)aiStack_580[2] / 16.0);
        *(ulong *)(iVar20 + (iVar21 + 9) * 0x10 + 8) =
             (ulong)uVar9 << 0x20 |
             (long)aiStack_580[0] |
             CONCAT44((int)(short)((uint)aiStack_580[1] >> 0x10),aiStack_580[1] << 0x10);
        uVar9 = __fixunssfdi((float)aiStack_580[6] / 16.0);
        *(ulong *)(iVar20 + (iVar21 + 10) * 0x10 + 8) =
             (ulong)uVar9 << 0x20 |
             (long)aiStack_580[4] |
             CONCAT44((int)(short)((uint)aiStack_580[5] >> 0x10),aiStack_580[5] << 0x10);
      }
      if ((iGpffff8610->nCmd1 & 1) == 0) {
        *(undefined8 *)(iVar20 + (iVar21 + 0xb) * 0x10 + 8) = 0x71006f00;
        *(undefined8 *)(iVar20 + (iVar21 + 0xc) * 0x10 + 8) = 0x71006f00;
      }
      else {
        uVar9 = __fixunssfdi((float)aiStack_580[10] / 16.0);
        *(ulong *)(iVar20 + (iVar21 + 0xb) * 0x10 + 8) =
             (ulong)uVar9 << 0x20 |
             (long)aiStack_580[8] |
             CONCAT44((int)(short)((uint)aiStack_580[9] >> 0x10),aiStack_580[9] << 0x10);
        uVar9 = __fixunssfdi((float)aiStack_580[0xe] / 16.0);
        *(ulong *)(iVar20 + (iVar21 + 0xc) * 0x10 + 8) =
             (ulong)uVar9 << 0x20 |
             (long)aiStack_580[0xc] |
             CONCAT44((int)(short)((uint)aiStack_580[0xd] >> 0x10),aiStack_580[0xd] << 0x10);
      }
      uVar9 = __fixunssfdi((float)aiStack_580[0x12] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0xd) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 |
           (long)aiStack_580[0x10] |
           CONCAT44((int)(short)((uint)aiStack_580[0x11] >> 0x10),aiStack_580[0x11] << 0x10);
      uVar9 = __fixunssfdi((float)aiStack_580[0x16] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 | (long)aiStack_580[0x14] | (long)aiStack_580[0x15] << 0x10;
    }
    else {
      *(undefined8 *)(iVar20 + (iVar21 + 9) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 10) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xb) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xc) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xd) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0xe) * 0x10 + 8) = 0x71006f00;
    }
  }
  if (((ulong)*(ushort *)(this + 0x5c) & 0x1ff) >> 6 == 0) {
    *(undefined8 *)(iVar20 + (iVar21 + 0x17) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0x18) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0x19) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar20 + (iVar21 + 0x1a) * 0x10 + 8) = 0x71006f00;
  }
  else {
    afStack_d0[0] = -32.0;
    afStack_d0[1] = -32.0;
    afStack_d0[2] = 0.0;
    afStack_d0[3] = 1.0;
    afStack_d0[4] = -32.0;
    afStack_d0[5] = 32.0;
    afStack_d0[6] = 0.0;
    afStack_d0[7] = 1.0;
    afStack_d0[8] = 32.0;
    afStack_d0[9] = -32.0;
    afStack_d0[10] = 0.0;
    afStack_d0[0xb] = 1.0;
    afStack_d0[0xc] = 32.0;
    afStack_d0[0xd] = 32.0;
    afStack_d0[0xe] = 0.0;
    afStack_d0[0xf] = 1.0;
    auVar30 = _vmr32(in_vf0);
    auVar31 = _vmr32(auVar30);
    auVar32 = _vmr32(auVar31);
    auStack_590 = _sqc2(in_vf0);
    auStack_5a0 = _sqc2(auVar30);
    auStack_5b0 = _sqc2(auVar31);
    auStack_5c0 = _sqc2(auVar32);
    sceVu0RotMatrixZ(*(undefined4 *)(this + 0xf8),auStack_5c0,auStack_5c0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf4),auStack_5c0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf4),auStack_5b0);
    __amu__7FVectorFf(*(undefined4 *)(this + 0xf4),auStack_5a0);
    _auStack_330 = ZEXT812(0);
    fStack_324 = 1.0;
    if (*(float *)(this + 0xc4) != 0.0) {
      auVar31 = _lqc2(*(undefined1 (*) [16])(this + 0xa0));
      auVar30 = _lqc2(_auStack_330);
      auVar30 = _vadd(auVar30,auVar31);
      _auStack_330 = _sqc2(auVar30);
    }
    auStack_590 = _auStack_330;
    RotTransVector(afStack_320,afStack_d0,auStack_5c0,4);
    sceVu0RotTransPersN(aiStack_580,this + 0x100,afStack_320,4,0);
    cStack_40 = '\0';
    for (iVar24 = 0; iVar24 < 4; iVar24 = iVar24 + 1) {
      if (((aiStack_580[iVar24 * 4] < 0) || (0xffff < aiStack_580[iVar24 * 4])) ||
         ((aiStack_580[iVar24 * 4 + 1] < 0 ||
          ((0xffff < aiStack_580[iVar24 * 4 + 1] || (aiStack_580[iVar24 * 4 + 2] < 0)))))) {
        cStack_40 = '\x01';
      }
    }
    if (cStack_40 == '\0') {
      uVar9 = __fixunssfdi((float)aiStack_580[2] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0x17) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 |
           (long)aiStack_580[0] |
           CONCAT44((int)(short)((uint)aiStack_580[1] >> 0x10),aiStack_580[1] << 0x10);
      uVar9 = __fixunssfdi((float)aiStack_580[6] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0x18) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 |
           (long)aiStack_580[4] |
           CONCAT44((int)(short)((uint)aiStack_580[5] >> 0x10),aiStack_580[5] << 0x10);
      uVar9 = __fixunssfdi((float)aiStack_580[10] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0x19) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 |
           (long)aiStack_580[8] |
           CONCAT44((int)(short)((uint)aiStack_580[9] >> 0x10),aiStack_580[9] << 0x10);
      uVar9 = __fixunssfdi((float)aiStack_580[0xe] / 16.0);
      *(ulong *)(iVar20 + (iVar21 + 0x1a) * 0x10 + 8) =
           (ulong)uVar9 << 0x20 | (long)aiStack_580[0xc] | (long)aiStack_580[0xd] << 0x10;
    }
    else {
      *(undefined8 *)(iVar20 + (iVar21 + 0x17) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0x18) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0x19) * 0x10 + 8) = 0x71006f00;
      *(undefined8 *)(iVar20 + (iVar21 + 0x1a) * 0x10 + 8) = 0x71006f00;
    }
  }
  this->nCmdMask = iVar20 + (iVar21 + 0x1b) * 0x10;
  *(byte *)(this + 0x40) = *(byte *)(this + 0x40) & 0xfe | bVar1;
  return;
}

/* ---- 0x0057a510  __ct__14BtlTarotEffectFv  (size 0x7e0) ----
 *   nStep values: []
 *   nPhase targets: ['0x43e830']
 *   bState targets: [] */
undefined8 __ct__14BtlTarotEffectFv(undefined8 this,undefined8 param_2,undefined8 param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  int this;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [16];
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  int aiStack_30 [12];
  
  __ct__6BtlEffFii(this,param_2,param_3);
  /* this = this */
  *(undefined4 *)(this + 0x14) = 0x43e820;
  this->nPhase = 0x43e830;
  *(undefined4 *)(this + 0x34) = 0x43e840;
  *(undefined4 *)(this + 0x70) = in_zero_lo;
  *(undefined4 *)(this + 0x74) = in_zero_hi;
  *(undefined4 *)(this + 0x78) = in_zero_udw;
  *(undefined4 *)(this + 0x7c) = in_register_0000000c;
  *(undefined4 *)(this + 0x80) = in_zero_lo;
  this->flMenuTimer = in_zero_hi;
  this->flMenuTimer2 = in_zero_udw;
  *(undefined4 *)(this + 0x8c) = in_register_0000000c;
  *(undefined4 *)(this + 0x40) = 0;
  this->nCmd0_target = (int)param_2;
  this->nCmd1 = (int)param_3;
  this->nCmdKind = 10;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  this->nCmdMask = 0;
  *(undefined4 *)(this + 0x5c) = 0;
  this->nShortcutTarget = 0;
  iVar4 = 0;
  for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
    if (((((chr(iGpffff8610,iVar1)->bFlagsA & 1) != 0) &&
         ((long)((ulong)chr(iGpffff8610,iVar1)->bFlagsA << 0x3e) < 0)) &&
        (-1 < (long)((ulong)chr(iGpffff8610,iVar1)->bFlagsA2 << 0x3c))) &&
       (((chr(iGpffff8610,iVar1)->bFlagsB & 1) == 0 ||
        (0 < chr(iGpffff8610,iVar1)->nHp)))) {
      aiStack_30[iVar4] = iVar1;
      iVar4 = iVar4 + 1;
    }
  }
  auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[0] * 0x510 + 0x160));
  auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[0] * 0x510 + 0x3a0));
  auVar7 = _vadd(auVar7,auVar8);
  auStack_d0 = _sqc2(auVar7);
  uStack_40 = in_zero_lo;
  uStack_3c = in_zero_hi;
  uStack_38 = in_zero_udw;
  uStack_34 = in_register_0000000c;
  __ct__7FVectorFPC7FVector(&uStack_60,auStack_d0);
  auStack_50._8_4_ = uStack_58;
  auStack_50._0_8_ = uStack_60;
  auStack_50._12_4_ = uStack_54;
  for (iVar1 = 1; iVar1 < iVar4; iVar1 = iVar1 + 1) {
    auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar1] * 0x510 + 0x160));
    auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar1] * 0x510 + 0x3a0));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_e0 = _sqc2(auVar7);
    __ct__7FVectorFPC7FVector(auStack_70,auStack_e0);
    auVar8 = _lqc2(auStack_70);
    auVar7 = _lqc2(auStack_50);
    auVar7 = _vadd(auVar7,auVar8);
    auStack_50 = _sqc2(auVar7);
  }
  __adv__7FVectorFf((float)iVar4,auStack_50);
  uStack_80 = auStack_50._0_4_;
  uStack_7c = 0;
  uStack_78 = auStack_50._8_4_;
  uStack_74 = 0x3f800000;
  *(undefined4 *)(this + 0x70) = auStack_50._0_4_;
  *(undefined4 *)(this + 0x74) = 0;
  *(undefined4 *)(this + 0x78) = auStack_50._8_4_;
  *(undefined4 *)(this + 0x7c) = 0x3f800000;
  fVar6 = 0.0;
  for (iVar1 = 0; iVar1 < iVar4; iVar1 = iVar1 + 1) {
    auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar1] * 0x510 + 0x160));
    auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar1] * 0x510 + 0x3a0));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_f0 = _sqc2(auVar7);
    __ct__7FVectorFPC7FVector(&uStack_90,auStack_f0);
    auStack_50._8_4_ = uStack_88;
    auStack_50._0_8_ = uStack_90;
    auStack_50._12_4_ = uStack_84;
    fVar5 = fVar6;
    iVar3 = iVar1;
    while (fVar6 = fVar5, iVar3 = iVar3 + 1, iVar3 < iVar4) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar3] * 0x510 + 0x160));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff8610 + aiStack_30[iVar3] * 0x510 + 0x3a0));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_110 = _sqc2(auVar7);
      __ct__7FVectorFPC7FVector(auStack_b0,auStack_110);
      auVar7 = _lqc2(auStack_b0);
      auVar8 = _lqc2(auStack_50);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_100 = _sqc2(auVar7);
      __ct__7FVectorFPC7FVector(auStack_a0,auStack_100);
      uStack_40 = auStack_a0._0_4_;
      uStack_38 = uStack_98;
      uStack_34 = uStack_94;
      uStack_3c = 0;
      fVar5 = (float)Length__7FVectorCFv(&uStack_40);
      if (fVar5 <= fVar6) {
        fVar5 = fVar6;
      }
    }
  }
  fVar6 = fVar6 / 2.0;
  if (fVar6 == 0.0) {
    fVar6 = (float)Length__7FVectorCFv(iGpffff8610 + aiStack_30[0] * 0x510 + 0x3b0);
  }
  this->flTurnPush = fVar6;
  uStack_c0 = 0;
  uStack_bc = 0;
  uStack_b8 = 0;
  uStack_b4 = 0x3f800000;
  *(undefined4 *)(this + 0x80) = 0;
  this->flMenuTimer = 0;
  this->flMenuTimer2 = 0;
  *(undefined4 *)(this + 0x8c) = 0x3f800000;
  *(undefined4 *)(this + 0x94) = 0x3fa00000;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  fVar6 = -3.1415927;
  for (iVar4 = 0; iVar4 < 0x80; iVar4 = iVar4 + 1) {
    *(float *)(this + iVar4 * 4 + 0xa0) = fVar6;
    iVar1 = rand();
    *(float *)(this + iVar4 * 4 + 0x4a0) = ((float)iVar1 / 2.1474836e+09) * -60.0 + 10.0;
    fVar6 = fVar6 + 0.049087387;
  }
  fVar6 = -3.1415927;
  for (iVar4 = 0x80; iVar4 < 0x100; iVar4 = iVar4 + 1) {
    *(float *)(this + iVar4 * 4 + 0xa0) = fVar6;
    iVar1 = rand();
    *(float *)(this + iVar4 * 4 + 0x4a0) = ((float)iVar1 / 2.1474836e+09) * -60.0 + 10.0;
    fVar6 = fVar6 + 0.09817477;
    if (3.1415927 <= fVar6) {
      fVar6 = fVar6 - 6.2831855;
    }
  }
  Entry__7CPollerFP7CPolObjib(iGpffff84b0 + 0x48,this,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff8610,this->nCmd1,this);
  if ((iGpffff8610->nCmd1 & 2) == 0) {
    PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x300a,1,0);
  }
  else {
    PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x300b,1,0);
  }
  return this;
}

/* ---- 0x0057acf0  __dt__14BtlTarotEffectFv  (size 0x160) ----
 *   nStep values: []
 *   nPhase targets: ['0x43e830', '0x43f4c0']
 *   bState targets: [] */
int __dt__14BtlTarotEffectFv(int this,short param_2)

{
  if (this != 0) {
    *(undefined4 *)(this + 0x14) = 0x43e820;
    this->nPhase = 0x43e830;
    *(undefined4 *)(this + 0x34) = 0x43e840;
    if (*(int *)(this + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(this + 0x18));
    }
    if (*(int *)(this + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(this + 0x1c));
    }
    if (this != 0) {
      *(undefined4 *)(this + 0x14) = 0x43f4b0;
      this->nPhase = 0x43f4c0;
      *(undefined4 *)(this + 0x34) = 0x43f4d0;
      if (this != -0x2c) {
        *(undefined4 *)(this + 0x34) = 0x437f60;
      }
      __dt__8VIF1PrimFv(this + 0x18,0);
      __dt__7CPolObjFv(this,0);
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

/* ---- 0x0057ae50  Destruct__14BtlTarotEffectFv  (size 0xd0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void Destruct__14BtlTarotEffectFv(int this)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff8610,this->nCmd1,this);
  if ((long)((ulong)*(byte *)(this + 0x40) << 0x3e) < 0) {
    iVar1 = this;
    if (this != 0) {
      iVar1 = this + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x45a200,iVar1);
  }
  *(byte *)(this + 0x40) = *(byte *)(this + 0x40) & 0xfd;
  Dispose__7CPollerFP7CPolObj(iGpffff84b0 + 0x48,this);
  (**(code **)(*(int *)(this + 0x34) + 0xc))();
  return;
}

/* ---- 0x0057af20  Polling__14BtlTarotEffectFv  (size 0x3b0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
undefined4 Polling__14BtlTarotEffectFv(int this)

{
  int iVar1;
  int iVar2;
  float fStack_14;
  
  fStack_14 = iGpffff8610->flDeltaT;
  if ((iGpffff8610->bFlags24 & 1) != 0) {
    fStack_14 = 0.0;
  }
  this->nShortcutTarget = this->nShortcutTarget + fStack_14;
  this->flMenuTimer = this->flMenuTimer + (fStack_14 * 6.2831855 * 4.0) / 32.0;
  if (3.1415927 <= this->flMenuTimer) {
    this->flMenuTimer = this->flMenuTimer - 6.2831855;
  }
  *(float *)(this + 0x9c) =
       *(float *)(this + 0x9c) +
       ((1.8 - this->nShortcutTarget) / 1.8 + 0.25) * this->flTurnPush * fStack_14;
  iVar2 = *(int *)(this + 0x5c);
  if (iVar2 == 2) {
    *(float *)(this + 0x98) = (1.8 - this->nShortcutTarget) * 2.5;
    if (*(float *)(this + 0x98) <= 0.0) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff8610,this->nCmd1,this);
      if ((long)((ulong)*(byte *)(this + 0x40) << 0x3e) < 0) {
        iVar2 = this;
        if (this != 0) {
          iVar2 = this + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x45a200,iVar2);
      }
      *(byte *)(this + 0x40) = *(byte *)(this + 0x40) & 0xfd;
      (**(code **)(*(int *)(this + 0x34) + 0xc))();
      return 1;
    }
  }
  else if (iVar2 == 1) {
    if (1.4 <= this->nShortcutTarget) {
      *(undefined4 *)(this + 0x5c) = 2;
    }
  }
  else if ((iVar2 == 0) &&
          (*(float *)(this + 0x98) = this->nShortcutTarget * 2.5,
          1.0 <= *(float *)(this + 0x98))) {
    *(undefined4 *)(this + 0x98) = 0x3f800000;
    *(undefined4 *)(this + 0x5c) = 1;
  }
  for (iVar2 = 0; iVar2 < 0x100; iVar2 = iVar2 + 1) {
    iVar1 = this + iVar2 * 4;
    *(float *)(iVar1 + 0x4a0) = *(float *)(iVar1 + 0x4a0) - fStack_14 * 90.0;
    if (*(float *)(this + iVar2 * 4 + 0x4a0) < -50.0) {
      iVar1 = this + iVar2 * 4;
      *(float *)(iVar1 + 0x4a0) = *(float *)(iVar1 + 0x4a0) + 60.0;
    }
  }
  return 0;
}

/* ---- 0x0057b2d0  MakePacket__14BtlTarotEffectFv  (size 0x2720) ----
 *   nStep values: []
 *   nPhase targets: ['0x6ee8ee']
 *   bState targets: [] */
void MakePacket__14BtlTarotEffectFv(int this)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar14;
  undefined8 uVar15;
  undefined8 extraout_v0_udw;
  undefined1 auVar16 [16];
  float *pfVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  byte bVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  undefined1 in_vf0 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auStack_8c70 [16];
  undefined1 auStack_8c60 [16];
  undefined1 auStack_8c50 [16];
  undefined1 auStack_8c40 [16];
  undefined1 auStack_8c30 [16];
  undefined1 auStack_8c20 [16];
  undefined1 auStack_8c10 [16];
  undefined1 auStack_8c00 [16];
  undefined1 auStack_8bf0 [16];
  undefined1 auStack_8be0 [64];
  float fStack_8ba0;
  float fStack_8b9c;
  float fStack_8b98;
  float fStack_8b94;
  float fStack_8b90;
  float fStack_8b8c;
  float fStack_8b88;
  float fStack_8b84;
  undefined4 uStack_8b80;
  undefined4 uStack_8b7c;
  float fStack_8b78;
  undefined4 uStack_8b74;
  float fStack_8b70;
  float fStack_8b6c;
  float fStack_8b68;
  float fStack_8b64;
  undefined4 uStack_8b60;
  undefined4 uStack_8b5c;
  undefined4 uStack_8b58;
  undefined4 uStack_8b54;
  undefined4 uStack_8b50;
  undefined4 uStack_8b4c;
  undefined4 uStack_8b48;
  undefined4 uStack_8b44;
  undefined4 uStack_8b40;
  undefined4 uStack_8b3c;
  undefined4 uStack_8b38;
  undefined4 uStack_8b34;
  undefined4 uStack_8b30;
  undefined4 uStack_8b2c;
  undefined4 uStack_8b28;
  undefined4 uStack_8b24;
  float fStack_8b20;
  float fStack_8b1c;
  float fStack_8b18;
  float fStack_8b14;
  float fStack_8b10;
  float fStack_8b0c;
  float fStack_8b08;
  float fStack_8b04;
  undefined4 uStack_8b00;
  undefined4 uStack_8afc;
  float fStack_8af8;
  undefined4 uStack_8af4;
  float fStack_8af0;
  float fStack_8aec;
  float fStack_8ae8;
  float fStack_8ae4;
  undefined4 uStack_8ae0;
  undefined4 uStack_8adc;
  undefined4 uStack_8ad8;
  undefined4 uStack_8ad4;
  undefined4 uStack_8ad0;
  undefined4 uStack_8acc;
  undefined4 uStack_8ac8;
  undefined4 uStack_8ac4;
  undefined4 uStack_8ac0;
  undefined4 uStack_8abc;
  undefined4 uStack_8ab8;
  undefined4 uStack_8ab4;
  undefined4 uStack_8ab0;
  undefined4 uStack_8aac;
  undefined4 uStack_8aa8;
  undefined4 uStack_8aa4;
  float fStack_8aa0;
  float fStack_8a9c;
  float fStack_8a98;
  float fStack_8a94;
  float fStack_8a90;
  float fStack_8a8c;
  float fStack_8a88;
  float fStack_8a84;
  undefined1 auStack_8a80 [16];
  undefined1 auStack_8a70 [16];
  float fStack_8a60;
  float fStack_8a5c;
  float fStack_8a58;
  float fStack_8a54;
  undefined4 uStack_8a50;
  undefined4 uStack_8a4c;
  undefined4 uStack_8a48;
  undefined4 uStack_8a44;
  float fStack_8a40;
  float fStack_8a3c;
  float fStack_8a38;
  undefined4 uStack_8a34;
  float fStack_8a30;
  float fStack_8a2c;
  float fStack_8a28;
  undefined4 uStack_8a24;
  float fStack_8a20;
  float fStack_8a1c;
  float fStack_8a18;
  undefined4 uStack_8a14;
  float fStack_8a10;
  float fStack_8a0c;
  float fStack_8a08;
  undefined4 uStack_8a04;
  int aiStack_8a00 [4096];
  undefined4 auStack_4a00 [16];
  undefined1 auStack_49c0 [16];
  undefined1 auStack_49b0 [16];
  undefined1 auStack_49a0 [16];
  undefined1 auStack_4990 [16];
  float fStack_4980;
  float fStack_497c;
  float fStack_4978;
  float fStack_4974;
  float fStack_4970;
  float fStack_496c;
  float fStack_4968;
  float fStack_4964;
  float fStack_4960;
  float fStack_495c;
  float fStack_4958;
  float fStack_4954;
  float fStack_4950;
  float fStack_494c;
  float fStack_4948;
  float fStack_4944;
  float afStack_4940 [4105];
  float fStack_91c;
  float fStack_918;
  undefined4 uStack_914;
  float fStack_910;
  float fStack_90c;
  float fStack_908;
  undefined4 uStack_904;
  byte abStack_900 [256];
  int aiStack_800 [128];
  int aiStack_600 [128];
  undefined4 auStack_400 [256];
  
  pfVar17 = afStack_4940;
  do {
    *pfVar17 = in_zero_lo;
    pfVar17[1] = in_zero_hi;
    pfVar17[2] = in_zero_udw;
    pfVar17[3] = in_register_0000000c;
    pfVar17 = pfVar17 + 4;
  } while (pfVar17 != afStack_4940 + 0x1000);
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  _sqc2(in_vf0);
  _sqc2(auVar27);
  _sqc2(auVar28);
  _sqc2(auVar29);
  fVar25 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff8610 + 0x459c) + 0x53) << 0x3a) >>
                              0x3c));
  fVar26 = (float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) /
           (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff8610 + 0x459c) + 0x50) << 0x1e) >>
                              0x3c));
  fStack_8a08 = -*(float *)(this + 0x9c);
  fStack_8a0c = ((float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) *
                *(float *)(this + 0x94)) / 128.0;
  fStack_8a10 = ((float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) *
                *(float *)(this + 0x94)) / 128.0;
  uStack_8a04 = 0x3f800000;
  afStack_4940[0x1003] = 1.0;
  fStack_8a18 = -*(float *)(this + 0x9c);
  fStack_8a1c = ((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) * *(float *)(this + 0x94)
                ) / 128.0;
  fStack_8a20 = ((float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) *
                *(float *)(this + 0x94)) / 128.0;
  uStack_8a14 = 0x3f800000;
  afStack_4940[0x1007] = 1.0;
  fStack_8a28 = -*(float *)(this + 0x9c);
  fStack_8a2c = ((float)(int)-(uint)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) *
                *(float *)(this + 0x94)) / 128.0;
  fStack_8a30 = ((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) * *(float *)(this + 0x94)
                ) / 128.0;
  uStack_8a24 = 0x3f800000;
  uStack_914 = 0x3f800000;
  fStack_8a38 = -*(float *)(this + 0x9c);
  fStack_8a3c = ((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 4) * *(float *)(this + 0x94)
                ) / 128.0;
  fStack_8a40 = ((float)*(ushort *)(*(int *)(iGpffff8610 + 0x459c) + 2) * *(float *)(this + 0x94)
                ) / 128.0;
  uStack_8a34 = 0x3f800000;
  uStack_904 = 0x3f800000;
  iVar20 = 0;
  fStack_4980 = in_zero_lo;
  fStack_497c = in_zero_hi;
  fStack_4978 = in_zero_udw;
  fStack_4974 = in_register_0000000c;
  fStack_4970 = in_zero_lo;
  fStack_496c = in_zero_hi;
  fStack_4968 = in_zero_udw;
  fStack_4964 = in_register_0000000c;
  fStack_4960 = in_zero_lo;
  fStack_495c = in_zero_hi;
  fStack_4958 = in_zero_udw;
  fStack_4954 = in_register_0000000c;
  fStack_4950 = in_zero_lo;
  fStack_494c = in_zero_hi;
  fStack_4948 = in_zero_udw;
  fStack_4944 = in_register_0000000c;
  afStack_4940[0x1000] = fStack_8a10;
  afStack_4940[0x1001] = fStack_8a0c;
  afStack_4940[0x1002] = fStack_8a08;
  afStack_4940[0x1004] = fStack_8a20;
  afStack_4940[0x1005] = fStack_8a1c;
  afStack_4940[0x1006] = fStack_8a18;
  afStack_4940[0x1008] = fStack_8a30;
  fStack_91c = fStack_8a2c;
  fStack_918 = fStack_8a28;
  fStack_910 = fStack_8a40;
  fStack_90c = fStack_8a3c;
  fStack_908 = fStack_8a38;
  for (iVar18 = 0; iVar18 < 0x80; iVar18 = iVar18 + 1) {
    auVar27 = _vmr32(in_vf0);
    auVar28 = _vmr32(auVar27);
    auVar29 = _vmr32(auVar28);
    auStack_4990 = _sqc2(in_vf0);
    auStack_49a0 = _sqc2(auVar27);
    auStack_49b0 = _sqc2(auVar28);
    auStack_49c0 = _sqc2(auVar29);
    sceVu0RotMatrixY(*(undefined4 *)(this + iVar18 * 4 + 0xa0),auStack_49c0,auStack_49c0);
    sceVu0RotMatrix(auStack_49c0,auStack_49c0,this + 0x80);
    uStack_8a48 = *(undefined4 *)(this + 0x78);
    uStack_8a4c = *(undefined4 *)(this + iVar18 * 4 + 0x4a0);
    uStack_8a50 = *(undefined4 *)(this + 0x70);
    uStack_8a44 = 0x3f800000;
    auStack_4990._4_4_ = uStack_8a4c;
    auStack_4990._0_4_ = uStack_8a50;
    auStack_4990._8_4_ = uStack_8a48;
    auStack_4990._12_4_ = 0x3f800000;
    RotTransVector(afStack_4940 + iVar20 * 0x10,afStack_4940 + 0x1000,auStack_49c0,4);
    auVar27 = _lqc2(*(undefined1 (*) [16])(afStack_4940 + iVar20 * 0x10));
    auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_4940 + (iVar20 * 4 + 1) * 4));
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c60 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(auStack_8a80,auStack_8c60);
    auVar27 = _lqc2(auStack_8a80);
    auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_4940 + (iVar20 * 4 + 2) * 4));
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c70 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(auStack_8a70,auStack_8c70);
    auVar27 = _lqc2(auStack_8a70);
    auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_4940 + (iVar20 * 4 + 3) * 4));
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8bf0 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8a60,auStack_8bf0);
    fStack_4980 = fStack_8a60;
    fStack_497c = fStack_8a5c;
    fStack_4978 = fStack_8a58;
    fStack_4974 = fStack_8a54;
    __adv__7FVectorFf(0x40800000,&fStack_4980);
    auVar27._4_4_ = fStack_497c;
    auVar27._0_4_ = fStack_4980;
    auVar27._8_4_ = fStack_4978;
    auVar27._12_4_ = fStack_4974;
    auVar27 = _lqc2(auVar27);
    auVar29._4_4_ = fStack_496c;
    auVar29._0_4_ = fStack_4970;
    auVar29._8_4_ = fStack_4968;
    auVar29._12_4_ = fStack_4964;
    auVar28 = _lqc2(auVar29);
    auVar27 = _vsub(auVar27,auVar28);
    auStack_8c00 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8a90,auStack_8c00);
    fStack_4960 = fStack_8a90;
    fStack_495c = fStack_8a8c;
    fStack_4958 = fStack_8a88;
    fStack_4954 = fStack_8a84;
    Normalize__7FVectorFv(&fStack_4960);
    auVar27 = _lqc2(*(undefined1 (*) [16])(iGpffff8610->pCamera + 0x30));
    auVar28._4_4_ = fStack_497c;
    auVar28._0_4_ = fStack_4980;
    auVar28._8_4_ = fStack_4978;
    auVar28._12_4_ = fStack_4974;
    auVar28 = _lqc2(auVar28);
    auVar27 = _vsub(auVar27,auVar28);
    auStack_8c10 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8aa0,auStack_8c10);
    fStack_4950 = fStack_8aa0;
    fStack_494c = fStack_8a9c;
    fStack_4948 = fStack_8a98;
    fStack_4944 = fStack_8a94;
    auVar9._4_4_ = fStack_8a9c;
    auVar9._0_4_ = fStack_8aa0;
    auVar9._8_4_ = fStack_8a98;
    auVar9._12_4_ = fStack_8a94;
    auVar27 = _lqc2(auVar9);
    auVar8._4_4_ = fStack_495c;
    auVar8._0_4_ = fStack_4960;
    auVar8._8_4_ = fStack_4958;
    auVar8._12_4_ = fStack_4954;
    auVar28 = _lqc2(auVar8);
    auVar27 = _vmul(auVar27,auVar28);
    auVar27 = _vaddbc(auVar27,auVar27);
    auVar27 = _vaddbc(auVar27,auVar27);
    auVar27 = _qmfc2(auVar27._0_4_);
    if (auVar27._0_4_ < 0.0) {
      auStack_400[iVar20] = 1;
    }
    if (-40.0 < *(float *)(this + iVar18 * 4 + 0x4a0)) {
      fVar24 = *(float *)(this + 0x98) * 80.0;
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    else {
      fVar24 = *(float *)(this + 0x98) * 80.0 *
               ((*(float *)(this + iVar18 * 4 + 0x4a0) + 50.0) / 10.0);
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    iVar20 = iVar20 + 1;
  }
  uStack_8ab0 = 0xc0200000;
  uStack_8aac = 0xc0f00000;
  uStack_8aa8 = 0;
  uStack_8aa4 = 0x3f800000;
  afStack_4940[0x1000] = -2.5;
  afStack_4940[0x1001] = -7.5;
  afStack_4940[0x1002] = 0.0;
  afStack_4940[0x1003] = 1.0;
  uStack_8ac0 = 0x40200000;
  uStack_8abc = 0x40f00000;
  uStack_8ab8 = 0;
  uStack_8ab4 = 0x3f800000;
  afStack_4940[0x1004] = 2.5;
  afStack_4940[0x1005] = 7.5;
  afStack_4940[0x1006] = 0.0;
  afStack_4940[0x1007] = 1.0;
  auStack_49c0 = *(undefined1 (*) [16])(iGpffff84bc + 0x240);
  auStack_49b0 = *(undefined1 (*) [16])(iGpffff84bc + 0x250);
  auStack_49a0 = *(undefined1 (*) [16])(iGpffff84bc + 0x260);
  uStack_8ad0 = 0;
  uStack_8acc = 0;
  uStack_8ac8 = 0;
  uStack_8ac4 = 0x3f800000;
  auStack_4990._0_12_ = ZEXT812(0);
  auStack_4990._12_4_ = 0x3f800000;
  RotTransVector(afStack_4940 + 0x1008,afStack_4940 + 0x1000,auStack_49c0,2);
  for (iVar18 = 0x80; iVar18 < 0xc0; iVar18 = iVar18 + 1) {
    auVar27 = _vmr32(in_vf0);
    auVar28 = _vmr32(auVar27);
    auVar29 = _vmr32(auVar28);
    auStack_4990 = _sqc2(in_vf0);
    auStack_49a0 = _sqc2(auVar27);
    auStack_49b0 = _sqc2(auVar28);
    auStack_49c0 = _sqc2(auVar29);
    sceVu0RotMatrixY(*(undefined4 *)(this + iVar18 * 4 + 0xa0),auStack_49c0,auStack_49c0);
    sceVu0RotMatrix(auStack_49c0,auStack_49c0,this + 0x80);
    uStack_8ad8 = *(undefined4 *)(this + 0x78);
    uStack_8adc = *(undefined4 *)(this + iVar18 * 4 + 0x4a0);
    uStack_8ae0 = *(undefined4 *)(this + 0x70);
    uStack_8ad4 = 0x3f800000;
    auStack_4990._4_4_ = uStack_8adc;
    auStack_4990._0_4_ = uStack_8ae0;
    auStack_4990._8_4_ = uStack_8ad8;
    auStack_4990._12_4_ = 0x3f800000;
    fStack_8af8 = -*(float *)(this + 0x9c);
    uStack_8b00 = 0;
    uStack_8afc = 0;
    uStack_8af4 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(&fStack_8af0,auStack_49c0,&uStack_8b00);
    fStack_4980 = fStack_8af0;
    fStack_497c = fStack_8aec;
    fStack_4978 = fStack_8ae8;
    fStack_4974 = fStack_8ae4;
    auVar4._4_4_ = fStack_8aec;
    auVar4._0_4_ = fStack_8af0;
    auVar4._8_4_ = fStack_8ae8;
    auVar4._12_4_ = fStack_8ae4;
    auVar27 = _lqc2(auVar4);
    auVar10._4_4_ = fStack_91c;
    auVar10._0_4_ = afStack_4940[0x1008];
    auVar10._8_4_ = fStack_918;
    auVar10._12_4_ = uStack_914;
    auVar28 = _lqc2(auVar10);
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c20 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8b10,auStack_8c20);
    afStack_4940[iVar20 * 0x10] = fStack_8b10;
    afStack_4940[iVar20 * 0x10 + 1] = fStack_8b0c;
    afStack_4940[iVar20 * 0x10 + 2] = fStack_8b08;
    afStack_4940[iVar20 * 0x10 + 3] = fStack_8b04;
    auVar5._4_4_ = fStack_497c;
    auVar5._0_4_ = fStack_4980;
    auVar5._8_4_ = fStack_4978;
    auVar5._12_4_ = fStack_4974;
    auVar27 = _lqc2(auVar5);
    auVar12._4_4_ = fStack_90c;
    auVar12._0_4_ = fStack_910;
    auVar12._8_4_ = fStack_908;
    auVar12._12_4_ = uStack_904;
    auVar28 = _lqc2(auVar12);
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c30 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8b20,auStack_8c30);
    iVar21 = iVar20 * 4 + 1;
    afStack_4940[iVar21 * 4] = fStack_8b20;
    afStack_4940[iVar21 * 4 + 1] = fStack_8b1c;
    afStack_4940[iVar21 * 4 + 2] = fStack_8b18;
    afStack_4940[iVar21 * 4 + 3] = fStack_8b14;
    if (-40.0 < *(float *)(this + iVar18 * 4 + 0x4a0)) {
      fVar24 = *(float *)(this + 0x98) * 128.0;
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    else {
      fVar24 = *(float *)(this + 0x98) * 128.0 *
               ((*(float *)(this + iVar18 * 4 + 0x4a0) + 50.0) / 10.0);
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    iVar20 = iVar20 + 1;
  }
  uStack_8b30 = 0xc0400000;
  uStack_8b2c = 0xc0400000;
  uStack_8b28 = 0;
  uStack_8b24 = 0x3f800000;
  afStack_4940[0x1000] = -3.0;
  afStack_4940[0x1001] = -3.0;
  afStack_4940[0x1002] = 0.0;
  afStack_4940[0x1003] = 1.0;
  uStack_8b40 = 0x40400000;
  uStack_8b3c = 0x40400000;
  uStack_8b38 = 0;
  uStack_8b34 = 0x3f800000;
  afStack_4940[0x1004] = 3.0;
  afStack_4940[0x1005] = 3.0;
  afStack_4940[0x1006] = 0.0;
  afStack_4940[0x1007] = 1.0;
  auStack_49c0 = *(undefined1 (*) [16])(iGpffff84bc + 0x240);
  auStack_49b0 = *(undefined1 (*) [16])(iGpffff84bc + 0x250);
  auStack_49a0 = *(undefined1 (*) [16])(iGpffff84bc + 0x260);
  uStack_8b50 = 0;
  uStack_8b4c = 0;
  uStack_8b48 = 0;
  uStack_8b44 = 0x3f800000;
  auStack_4990._0_12_ = ZEXT812(0);
  auStack_4990._12_4_ = 0x3f800000;
  RotTransVector(afStack_4940 + 0x1008,afStack_4940 + 0x1000,auStack_49c0,2);
  for (iVar18 = 0xc0; iVar18 < 0x100; iVar18 = iVar18 + 1) {
    auVar27 = _vmr32(in_vf0);
    auVar28 = _vmr32(auVar27);
    auVar29 = _vmr32(auVar28);
    auStack_4990 = _sqc2(in_vf0);
    auStack_49a0 = _sqc2(auVar27);
    auStack_49b0 = _sqc2(auVar28);
    auStack_49c0 = _sqc2(auVar29);
    sceVu0RotMatrixY(*(undefined4 *)(this + iVar18 * 4 + 0xa0),auStack_49c0,auStack_49c0);
    sceVu0RotMatrix(auStack_49c0,auStack_49c0,this + 0x80);
    uStack_8b58 = *(undefined4 *)(this + 0x78);
    uStack_8b5c = *(undefined4 *)(this + iVar18 * 4 + 0x4a0);
    uStack_8b60 = *(undefined4 *)(this + 0x70);
    uStack_8b54 = 0x3f800000;
    auStack_4990._4_4_ = uStack_8b5c;
    auStack_4990._0_4_ = uStack_8b60;
    auStack_4990._8_4_ = uStack_8b58;
    auStack_4990._12_4_ = 0x3f800000;
    fStack_8b78 = -*(float *)(this + 0x9c);
    uStack_8b80 = 0;
    uStack_8b7c = 0;
    uStack_8b74 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(&fStack_8b70,auStack_49c0,&uStack_8b80);
    fStack_4980 = fStack_8b70;
    fStack_497c = fStack_8b6c;
    fStack_4978 = fStack_8b68;
    fStack_4974 = fStack_8b64;
    auVar6._4_4_ = fStack_8b6c;
    auVar6._0_4_ = fStack_8b70;
    auVar6._8_4_ = fStack_8b68;
    auVar6._12_4_ = fStack_8b64;
    auVar27 = _lqc2(auVar6);
    auVar11._4_4_ = fStack_91c;
    auVar11._0_4_ = afStack_4940[0x1008];
    auVar11._8_4_ = fStack_918;
    auVar11._12_4_ = uStack_914;
    auVar28 = _lqc2(auVar11);
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c40 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8b90,auStack_8c40);
    afStack_4940[iVar20 * 0x10] = fStack_8b90;
    afStack_4940[iVar20 * 0x10 + 1] = fStack_8b8c;
    afStack_4940[iVar20 * 0x10 + 2] = fStack_8b88;
    afStack_4940[iVar20 * 0x10 + 3] = fStack_8b84;
    auVar7._4_4_ = fStack_497c;
    auVar7._0_4_ = fStack_4980;
    auVar7._8_4_ = fStack_4978;
    auVar7._12_4_ = fStack_4974;
    auVar27 = _lqc2(auVar7);
    auVar13._4_4_ = fStack_90c;
    auVar13._0_4_ = fStack_910;
    auVar13._8_4_ = fStack_908;
    auVar13._12_4_ = uStack_904;
    auVar28 = _lqc2(auVar13);
    auVar27 = _vadd(auVar27,auVar28);
    auStack_8c50 = _sqc2(auVar27);
    __ct__7FVectorFPC7FVector(&fStack_8ba0,auStack_8c50);
    iVar21 = iVar20 * 4 + 1;
    afStack_4940[iVar21 * 4] = fStack_8ba0;
    afStack_4940[iVar21 * 4 + 1] = fStack_8b9c;
    afStack_4940[iVar21 * 4 + 2] = fStack_8b98;
    afStack_4940[iVar21 * 4 + 3] = fStack_8b94;
    if (-40.0 < *(float *)(this + iVar18 * 4 + 0x4a0)) {
      fVar24 = *(float *)(this + 0x98) * 128.0;
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    else {
      fVar24 = *(float *)(this + 0x98) * 128.0 *
               ((*(float *)(this + iVar18 * 4 + 0x4a0) + 50.0) / 10.0);
      if (fVar24 < 2.1474836e+09) {
        bVar23 = (byte)(int)fVar24;
      }
      else {
        bVar23 = (byte)(int)(fVar24 - 2.1474836e+09);
      }
      abStack_900[iVar20] = bVar23;
    }
    iVar20 = iVar20 + 1;
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_8be0,iGpffff84bc);
  for (iVar18 = 0; iVar18 < 4; iVar18 = iVar18 + 1) {
    auStack_4a00[iVar18 * 4] = *(undefined4 *)(auStack_49c0 + iVar18 * 0x10);
    auStack_4a00[iVar18 * 4 + 1] = *(undefined4 *)(auStack_49c0 + iVar18 * 0x10 + 4);
    auStack_4a00[iVar18 * 4 + 2] = *(undefined4 *)(auStack_49c0 + iVar18 * 0x10 + 8);
    auStack_4a00[iVar18 * 4 + 3] = *(undefined4 *)(auStack_49c0 + iVar18 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_8a00,auStack_4a00,afStack_4940,iVar20 << 2,0);
  for (iVar18 = 0; iVar18 < 0x80; iVar18 = iVar18 + 1) {
    aiStack_800[iVar18] = 0;
    if ((((aiStack_8a00[iVar18 * 0x10] < 0) || (0xffff < aiStack_8a00[iVar18 * 0x10])) ||
        (aiStack_8a00[iVar18 * 0x10 + 1] < 0)) ||
       ((0xffff < aiStack_8a00[iVar18 * 0x10 + 1] || (aiStack_8a00[iVar18 * 0x10 + 2] < 0)))) {
      aiStack_800[iVar18] = 1;
    }
    if (((aiStack_8a00[(iVar18 * 4 + 1) * 4] < 0) || (0xffff < aiStack_8a00[(iVar18 * 4 + 1) * 4]))
       || ((aiStack_8a00[(iVar18 * 4 + 1) * 4 + 1] < 0 ||
           ((0xffff < aiStack_8a00[(iVar18 * 4 + 1) * 4 + 1] ||
            (aiStack_8a00[(iVar18 * 4 + 1) * 4 + 2] < 0)))))) {
      aiStack_800[iVar18] = 1;
    }
    if ((((aiStack_8a00[(iVar18 * 4 + 2) * 4] < 0) || (0xffff < aiStack_8a00[(iVar18 * 4 + 2) * 4]))
        || (aiStack_8a00[(iVar18 * 4 + 2) * 4 + 1] < 0)) ||
       ((0xffff < aiStack_8a00[(iVar18 * 4 + 2) * 4 + 1] ||
        (aiStack_8a00[(iVar18 * 4 + 2) * 4 + 2] < 0)))) {
      aiStack_800[iVar18] = 1;
    }
    if (((aiStack_8a00[(iVar18 * 4 + 3) * 4] < 0) || (0xffff < aiStack_8a00[(iVar18 * 4 + 3) * 4]))
       || ((aiStack_8a00[(iVar18 * 4 + 3) * 4 + 1] < 0 ||
           ((0xffff < aiStack_8a00[(iVar18 * 4 + 3) * 4 + 1] ||
            (aiStack_8a00[(iVar18 * 4 + 3) * 4 + 2] < 0)))))) {
      aiStack_800[iVar18] = 1;
    }
  }
  for (iVar18 = 0x80; iVar18 < 0x100; iVar18 = iVar18 + 1) {
    aiStack_800[iVar18] = 0;
    if ((((aiStack_8a00[iVar18 * 0x10] < 0) || (0xffff < aiStack_8a00[iVar18 * 0x10])) ||
        (aiStack_8a00[iVar18 * 0x10 + 1] < 0)) ||
       ((0xffff < aiStack_8a00[iVar18 * 0x10 + 1] || (aiStack_8a00[iVar18 * 0x10 + 2] < 0)))) {
      aiStack_800[iVar18] = 1;
    }
    if (((aiStack_8a00[(iVar18 * 4 + 1) * 4] < 0) || (0xffff < aiStack_8a00[(iVar18 * 4 + 1) * 4]))
       || ((aiStack_8a00[(iVar18 * 4 + 1) * 4 + 1] < 0 ||
           ((0xffff < aiStack_8a00[(iVar18 * 4 + 1) * 4 + 1] ||
            (aiStack_8a00[(iVar18 * 4 + 1) * 4 + 2] < 0)))))) {
      aiStack_800[iVar18] = 1;
    }
  }
  bVar1 = (*(byte *)(this + 0x40) & 1) == 0;
  uVar22 = (uint)bVar1;
  if (*(int *)(this + uVar22 * 4 + 0x18) == 0) {
    uVar14 = __nwa__FUi(0x4990);
    *(undefined4 *)(this + uVar22 * 4 + 0x18) = uVar14;
    iVar18 = *(int *)(this + uVar22 * 4 + 0x18);
    *(undefined4 *)(iVar18 + 0x10) = 0x1000030a;
    *(undefined4 *)(iVar18 + 0x14) = 0;
    *(undefined4 *)(iVar18 + 0x18) = 0;
    *(undefined4 *)(iVar18 + 0x1c) = 0x5000030a;
    *(undefined8 *)(iVar18 + 0x20) = 0x6000000000000001;
    iVar18->nPhase = 0x6ee8ee;
    iVar18->nCurTurnChr = 1;
    iVar18->flDeltaT = 0x3f;
    *(undefined8 *)(iVar18 + 0x40) = 0x60;
    iVar18->nCmd1 = 0x14;
    iVar18->nCmd3 = 5;
    *(undefined8 *)(iVar18 + 0x58) = 0;
    iVar18->nShortcutTarget = 0x53001;
    *(undefined8 *)(iVar18 + 0x68) = 0x47;
    *(undefined8 *)(iVar18 + 0x70) = 0x48;
    *(undefined8 *)(iVar18 + 0x78) = 0x42;
    iVar18->flMenuTimer2 = 0;
    iVar18->flTurnPush = 0x2400000000000001;
    *(undefined8 *)(iVar18 + 0x98) = 0xf0;
    *(undefined8 *)(iVar18 + 0xa0) = 0x5c;
    *(undefined8 *)(iVar18 + 0xa8) = 0;
    auVar16._8_8_ = extraout_v0_udw;
    auVar16._0_8_ = 0xc400000000008080;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar27 = _pcpyld(auVar3,auVar16);
    *(long *)(iVar18 + 0xb0) = auVar27._0_8_;
    *(undefined8 *)(iVar18 + 0xb8) = 0x412412c12c12;
    iVar21 = 0xc;
    for (iVar20 = 0; iVar20 < 0x80; iVar20 = iVar20 + 1) {
      iVar21 = iVar21 + 6;
    }
    *(undefined4 *)(iVar18 + iVar21 * 0x10) = 0x50000000;
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 4) =
         *(undefined4 *)
          (*(int *)(iGpffff8610 + 0x44f8) +
           (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x44f8) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 8) = 0;
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 0xc) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10) = 0x100000c4;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 4) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 8) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 0xc) = 0x500000c4;
    *(undefined8 *)(iVar18 + (iVar21 + 2) * 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar18 + (iVar21 + 2) * 0x10 + 8) = 0x6e;
    *(undefined8 *)(iVar18 + (iVar21 + 3) * 0x10) = 1;
    *(undefined8 *)(iVar18 + (iVar21 + 3) * 0x10 + 8) = 0x3f;
    uVar15 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x44f8),1);
    *(undefined8 *)(iVar18 + (iVar21 + 4) * 0x10) = uVar15;
    *(undefined8 *)(iVar18 + (iVar21 + 4) * 0x10 + 8) = 0;
    *(undefined8 *)(iVar18 + (iVar21 + 5) * 0x10) = 0x6400000000008040;
    *(undefined8 *)(iVar18 + (iVar21 + 5) * 0x10 + 8) = 0x43c310;
    iVar21 = iVar21 + 6;
    for (iVar20 = 0; iVar20 < 0x40; iVar20 = iVar20 + 1) {
      *(undefined8 *)(iVar18 + iVar21 * 0x10) = 0x156;
      *(undefined8 *)(iVar18 + (iVar21 + 1) * 0x10) = 0;
      *(long *)(iVar18 + (iVar21 + 2) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x44f8) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x44f8) + 4) << 4) << 0x10;
      iVar21 = iVar21 + 3;
    }
    *(undefined4 *)(iVar18 + iVar21 * 0x10) = 0x50000000;
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 4) =
         *(undefined4 *)
          (*(int *)(iGpffff8610 + 0x45b4) +
           (uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 8) = 0;
    *(undefined4 *)(iVar18 + iVar21 * 0x10 + 0xc) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10) = 0x100000c4;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 4) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 8) = 0;
    *(undefined4 *)(iVar18 + (iVar21 + 1) * 0x10 + 0xc) = 0x500000c4;
    *(undefined8 *)(iVar18 + (iVar21 + 2) * 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar18 + (iVar21 + 2) * 0x10 + 8) = 0x6e;
    *(undefined8 *)(iVar18 + (iVar21 + 3) * 0x10) = 1;
    *(undefined8 *)(iVar18 + (iVar21 + 3) * 0x10 + 8) = 0x3f;
    uVar15 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + 0x45b4),1);
    *(undefined8 *)(iVar18 + (iVar21 + 4) * 0x10) = uVar15;
    *(undefined8 *)(iVar18 + (iVar21 + 4) * 0x10 + 8) = 0;
    *(undefined8 *)(iVar18 + (iVar21 + 5) * 0x10) = 0x6400000000008040;
    *(undefined8 *)(iVar18 + (iVar21 + 5) * 0x10 + 8) = 0x43c310;
    iVar21 = iVar21 + 6;
    for (iVar20 = 0; iVar20 < 0x40; iVar20 = iVar20 + 1) {
      *(undefined8 *)(iVar18 + iVar21 * 0x10) = 0x156;
      *(undefined8 *)(iVar18 + (iVar21 + 1) * 0x10) = 0;
      *(long *)(iVar18 + (iVar21 + 2) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff8610 + 0x45b4) + 4) << 4) << 0x10;
      iVar21 = iVar21 + 3;
    }
  }
  puVar2 = *(undefined4 **)(this + uVar22 * 4 + 0x18);
  *puVar2 = 0x50000000;
  iVar18 = *(int *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484);
  puVar2[1] = *(undefined4 *)(iVar18 + (uint)*(ushort *)(iVar18 + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  uVar15 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff8610 + (iGpffff8620 + 0x46) * 4 + 0x4484),1);
  *(undefined8 *)(puVar2 + 0x20) = uVar15;
  iVar21 = 0xc;
  iVar18 = 0;
  for (iVar20 = 0; iVar20 < 0x80; iVar20 = iVar20 + 1) {
    if (aiStack_800[iVar20] == 0) {
      iVar19 = aiStack_8a00[iVar20 * 0x10 + 3];
      *(undefined8 *)(puVar2 + iVar21 * 4) = 0;
      *(ulong *)(puVar2 + iVar21 * 4 + 2) =
           (ulong)abStack_900[iVar20] << 0x18 | 0x808080 |
           (ulong)(uint)(16.0 / (float)iVar19) << 0x20;
      iVar19 = aiStack_8a00[iVar20 * 0x10 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 1) * 4) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[iVar20 * 0x10] | (long)aiStack_8a00[iVar20 * 0x10 + 1] << 0x10;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 1) * 4 + 3];
      *(ulong *)(puVar2 + (iVar21 + 1) * 4 + 2) =
           (ulong)(uint)(fVar26 * (16.0 / (float)iVar19)) << 0x20;
      *(ulong *)(puVar2 + (iVar21 + 2) * 4) =
           (ulong)abStack_900[iVar20] << 0x18 | 0x808080 |
           (ulong)(uint)(16.0 / (float)iVar19) << 0x20;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 1) * 4 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 2) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4] |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4 + 1] << 0x10;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 2) * 4 + 3];
      *(ulong *)(puVar2 + (iVar21 + 3) * 4) = (ulong)(uint)(fVar25 * (16.0 / (float)iVar19));
      *(ulong *)(puVar2 + (iVar21 + 3) * 4 + 2) =
           (ulong)abStack_900[iVar20] << 0x18 | 0x808080 |
           (ulong)(uint)(16.0 / (float)iVar19) << 0x20;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 2) * 4 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 4) * 4) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[(iVar20 * 4 + 2) * 4] |
           (long)aiStack_8a00[(iVar20 * 4 + 2) * 4 + 1] << 0x10;
      fVar24 = 16.0 / (float)aiStack_8a00[(iVar20 * 4 + 3) * 4 + 3];
      *(ulong *)(puVar2 + (iVar21 + 4) * 4 + 2) = CONCAT44(fVar26 * fVar24,fVar25 * fVar24);
      *(ulong *)(puVar2 + (iVar21 + 5) * 4) =
           (ulong)abStack_900[iVar20] << 0x18 | 0x808080 | (ulong)(uint)fVar24 << 0x20;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 3) * 4 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 5) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[(iVar20 * 4 + 3) * 4] |
           (long)aiStack_8a00[(iVar20 * 4 + 3) * 4 + 1] << 0x10;
      iVar21 = iVar21 + 6;
      iVar18 = iVar18 + 1;
    }
  }
  for (; iVar18 < 0x80; iVar18 = iVar18 + 1) {
    *(undefined8 *)(puVar2 + (iVar21 + 1) * 4) = 0x71006f00;
    *(undefined8 *)(puVar2 + (iVar21 + 2) * 4 + 2) = 0x71006f00;
    *(undefined8 *)(puVar2 + (iVar21 + 4) * 4) = 0x71006f00;
    *(undefined8 *)(puVar2 + (iVar21 + 5) * 4 + 2) = 0x71006f00;
    iVar21 = iVar21 + 6;
  }
  iVar21 = iVar21 + 6;
  iVar18 = 0;
  for (iVar20 = 0x80; iVar20 < 0xc0; iVar20 = iVar20 + 1) {
    if (aiStack_800[iVar20] == 0) {
      *(ulong *)(puVar2 + iVar21 * 4 + 2) = (ulong)abStack_900[iVar20] << 0x18 | 0x808080;
      iVar19 = aiStack_8a00[iVar20 * 0x10 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 1) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[iVar20 * 0x10] | (long)aiStack_8a00[iVar20 * 0x10 + 1] << 0x10;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 1) * 4 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 2) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4] |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4 + 1] << 0x10;
      iVar21 = iVar21 + 3;
      iVar18 = iVar18 + 1;
    }
  }
  for (; iVar18 < 0x40; iVar18 = iVar18 + 1) {
    *(undefined8 *)(puVar2 + (iVar21 + 1) * 4 + 2) = 0x71006f00;
    *(undefined8 *)(puVar2 + (iVar21 + 2) * 4 + 2) = 0x71006f00;
    iVar21 = iVar21 + 3;
  }
  iVar21 = iVar21 + 6;
  iVar18 = 0;
  for (iVar20 = 0xc0; iVar20 < 0x100; iVar20 = iVar20 + 1) {
    if (aiStack_800[iVar20] == 0) {
      *(ulong *)(puVar2 + iVar21 * 4 + 2) = (ulong)abStack_900[iVar20] << 0x18 | 0x808080;
      iVar19 = aiStack_8a00[iVar20 * 0x10 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 1) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[iVar20 * 0x10] | (long)aiStack_8a00[iVar20 * 0x10 + 1] << 0x10;
      iVar19 = aiStack_8a00[(iVar20 * 4 + 1) * 4 + 2];
      if (iVar19 < 0) {
        iVar19 = iVar19 + 0xf;
      }
      *(long *)(puVar2 + (iVar21 + 2) * 4 + 2) =
           (long)(iVar19 >> 4) << 0x20 |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4] |
           (long)aiStack_8a00[(iVar20 * 4 + 1) * 4 + 1] << 0x10;
      iVar21 = iVar21 + 3;
      iVar18 = iVar18 + 1;
    }
  }
  for (; iVar18 < 0x40; iVar18 = iVar18 + 1) {
    *(undefined8 *)(puVar2 + (iVar21 + 1) * 4 + 2) = 0x71006f00;
    *(undefined8 *)(puVar2 + (iVar21 + 2) * 4 + 2) = 0x71006f00;
    iVar21 = iVar21 + 3;
  }
  *(undefined4 **)(this + 0x54) = puVar2 + iVar21 * 4;
  *(byte *)(this + 0x40) = *(byte *)(this + 0x40) & 0xfe | bVar1;
  return;
}

/* ---- 0x0057d9f0  EndSet__14BtlTarotEffectFv  (size 0x10) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void EndSet__14BtlTarotEffectFv(void)

{
  return;
}

/* ---- 0x0069e160  TarotRevertCard__7CBattleFii  (size 0x2ad0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void TarotRevertCard__7CBattleFii(int this,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int aiStack_60 [12];
  int iStack_30;
  undefined4 uStack_20;
  int iStack_10;
  
  iStack_30 = this;
  uStack_20 = param_2;
  iStack_10 = param_3;
  iVar4 = 0;
  for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
    if ((((chr(iStack_30,iVar5)->bFlagsA & 1) != 0) &&
        ((long)((ulong)chr(iStack_30,iVar5)->bFlagsA << 0x3e) < 0)) &&
       (-1 < (long)((ulong)chr(iStack_30,iVar5)->bFlagsA2 << 0x3c))) {
      for (iVar6 = 0; iVar6 < 0x20; iVar6 = iVar6 + 1) {
        if ((*(char *)(iStack_30 + iVar5 * 0x510 + iVar6 * 0xc + 0x1d0) != '\0') &&
           (((ulong)*(ushort *)(iStack_30 + iVar5 * 0x510 + iVar6 * 0xc + 0x1cc) & 0x3ff) >> 6 == 6)
           ) {
          uVar1 = *(undefined1 *)(iStack_30 + iVar5 * 0x510 + iVar6 * 0xc + 0x1d0);
          *(undefined1 *)(iStack_30 + iVar5 * 0x510 + iVar6 * 0xc + 0x1d0) = 0;
          EffectEndFunc__7CBattleFiii(iStack_30,iVar5,uVar1,iVar6);
        }
      }
      aiStack_60[iVar4] = iVar5;
      iVar4 = iVar4 + 1;
    }
  }
  if ((iStack_30->bTarotFlags & 1) != 0) {
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe;
    switch(iStack_30->nTarotCard) {
    case 4:
      for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
        if ((*(byte *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0xb4) & 1) == 0) {
          GetTurnInterval__7CBattleFi(iStack_30,aiStack_60[iVar5]);
          iVar6 = iStack_30 + aiStack_60[iVar5] * 0x510;
          *(float *)(iVar6 + 0x194) =
               *(float *)(iVar6 + 0x194) * (float)(uint)(10000 / iStack_30->nTarotParam);
          iVar6 = iStack_30 + aiStack_60[iVar5] * 0x510;
          *(float *)(iVar6 + 0x194) = *(float *)(iVar6 + 0x194) / 100.0;
        }
      }
      break;
    case 10:
      for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
        if ((*(byte *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0xb4) & 1) == 0) {
          uVar2 = GetLuc__7CBattleFii(iStack_30,aiStack_60[iVar5],0xfffffffffffffffe);
          *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x13e) = uVar2;
          GetTurnInterval__7CBattleFi(iStack_30,aiStack_60[iVar5]);
        }
      }
      break;
    case 0x11:
      for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
        if ((*(byte *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0xb4) & 1) == 0) {
          uVar3 = GetMaxHP__7CBattleFi(iStack_30,aiStack_60[iVar5]);
          *(undefined4 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 300) = uVar3;
          if (*(uint *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 300) <
              *(uint *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x130)) {
            *(undefined4 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x130) =
                 *(undefined4 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 300);
          }
        }
      }
      break;
    case 0x12:
      for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
        if ((*(byte *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0xb4) & 1) == 0) {
          uVar2 = GetMaxMP__7CBattleFi(iStack_30,aiStack_60[iVar5]);
          *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x134) = uVar2;
          if ((long)(ulong)*(ushort *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x134) <
              (long)*(short *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x136)) {
            *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x136) =
                 *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x134);
          }
        }
      }
      break;
    case 0x13:
      for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
        if ((*(byte *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0xb4) & 1) == 0) {
          uVar2 = GetMaxSP__7CBattleFi(iStack_30,aiStack_60[iVar5]);
          *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x138) = uVar2;
          if ((long)(ulong)*(ushort *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x138) <
              (long)*(short *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x13a)) {
            *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x13a) =
                 *(undefined2 *)(iStack_30 + aiStack_60[iVar5] * 0x510 + 0x138);
          }
        }
      }
    }
  }
  uVar2 = (undefined2)uStack_20;
  switch(uStack_20) {
  case 0:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x19;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 400;
    }
    else {
      iStack_30->nTarotParam = 200;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 1:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 400;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 200;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 0x19;
    }
    else {
      iStack_30->nTarotParam = 0x32;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 2:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 3:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x19;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 400;
    }
    else {
      iStack_30->nTarotParam = 200;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 4:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 400;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 200;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 0x19;
    }
    else {
      iStack_30->nTarotParam = 0x32;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 5:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 6:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 7:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 8:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
      iStack_30->nTarotParam = 400;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
      iStack_30->nTarotParam = 200;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
      iStack_30->nTarotParam = 400;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
      iStack_30->nTarotParam = 200;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 9:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 10:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x100;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x80;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 0x100;
    }
    else {
      iStack_30->nTarotParam = 0x80;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0xb:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0xc:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0xd:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0xe:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 400;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 200;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 0x19;
    }
    else {
      iStack_30->nTarotParam = 0x32;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0xf:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    else {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 0x10;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0x10:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
    }
    iStack_30->nTarotParam = 0;
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0x11:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 200;
    }
    else {
      iStack_30->nTarotParam = 0x96;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0x12:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 200;
    }
    else {
      iStack_30->nTarotParam = 0x96;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0x13:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7 | 8;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 200;
    }
    else {
      iStack_30->nTarotParam = 0x96;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
    break;
  case 0x15:
    iStack_30->bTarotFlags = 0;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfe | 1;
    iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xe7;
    iStack_30->nTarotCard = uVar2;
    if (iStack_10 == 3) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x19;
    }
    else if (iStack_10 == 2) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfd | 2;
      iStack_30->nTarotParam = 0x32;
    }
    else if (iStack_10 == 1) {
      iStack_30->bTarotFlags = iStack_30->bTarotFlags & 0xfb | 4;
      iStack_30->nTarotParam = 400;
    }
    else {
      iStack_30->nTarotParam = 200;
    }
    *(undefined4 *)(iStack_30 + 0x4084) = 0;
    *(undefined4 *)(iStack_30 + 0x4088) = 0;
    *(undefined4 *)(iStack_30 + 0x408c) = 0;
  }
  return;
}

/* ---- 0x006a0c30  TarotApplyCard__7CBattleFii  (size 0x41b0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: ['0x18', '0x25', '0x26', '0x27'] */
void TarotApplyCard__7CBattleFii(int this,int param_2)

{
  bool bVar1;
  char cVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  uint uVar9;
  undefined8 unaff_s3;
  uint uVar10;
  undefined4 uStack_230;
  char acStack_22c [4];
  uint auStack_228 [70];
  int aiStack_110 [6];
  short sStack_f6;
  short sStack_f2;
  short sStack_f0;
  short sStack_ee;
  undefined2 uStack_ce;
  undefined2 uStack_cc;
  byte bStack_ca;
  uint uStack_c8;
  undefined4 uStack_a0;
  undefined1 uStack_9c;
  undefined1 uStack_9b;
  ushort uStack_9a;
  uint uStack_98;
  undefined4 uStack_94;
  undefined1 uStack_90;
  undefined1 uStack_8f;
  short sStack_8e;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined1 uStack_84;
  undefined1 uStack_83;
  short sStack_82;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined1 uStack_78;
  undefined1 uStack_77;
  short sStack_76;
  undefined4 uStack_74;
  int iStack_38;
  int iStack_34;
  uint uStack_30;
  int iStack_2c;
  int iStack_28;
  uint uStack_24;
  int iStack_20;
  int iStack_10;
  
  uVar8 = 0;
  iVar7 = 0;
  iStack_20 = this;
  iStack_10 = param_2;
  iStack_38 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
  memset(aiStack_110,0,0x70);
  uStack_30 = 0;
  bVar1 = 0 < chr(iStack_20,iStack_10)->nHp;
  if (bVar1) {
    uStack_30 = 1;
  }
  uStack_30 = (uint)bVar1;
  uVar9 = (uint)((long)((ulong)iStack_20->bTarotFlags << 0x3d) < 0);
  if ((long)((ulong)iStack_20->bTarotFlags << 0x3e) < 0) {
    uVar9 = uVar9 | 2;
  }
  if (iStack_20->nMsgHandle < 0) {
    uStack_24 = uVar9 + iStack_20->nTarotCard * 4;
    uVar3 = SetBtlMessage__7CBattleFiPv(iStack_20,0xde,&uStack_24);
    iStack_20->nMsgHandle = uVar3;
  }
  switch(iStack_20->nTarotCard) {
  case 0:
    return;
  case 1:
    return;
  case 2:
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    if (uVar9 == 3) {
      uStack_a0 = 0x4183;
      uStack_9c = 0x47;
      uStack_98 = 0;
    }
    else if (uVar9 == 2) {
      uStack_a0 = 0x4583;
      uStack_9c = 0x41;
      uStack_98 = 0x32;
    }
    else if (uVar9 == 1) {
      uStack_a0 = 0x4583;
      uStack_9c = 7;
      uStack_98 = 100;
    }
    else {
      uStack_a0 = 0x4583;
      uStack_9c = 7;
      uStack_98 = 0x32;
    }
    uVar8 = 1;
    unaff_s3 = 1;
    break;
  case 3:
    if ((long)((ulong)iStack_20->bTarotFlags << 0x3e) < 0) {
      if ((long)((ulong)iStack_20->bTarotFlags << 0x3d) < 0) {
        uStack_cc = 0xffb5;
      }
      else {
        uStack_cc = 0xffce;
      }
    }
    else if ((long)((ulong)iStack_20->bTarotFlags << 0x3d) < 0) {
      uStack_cc = 300;
    }
    else {
      uStack_cc = 100;
    }
    unaff_s3 = 5;
    break;
  case 4:
    GetTurnInterval__7CBattleFi(iStack_20,iStack_10);
    iVar6 = iStack_20 + iStack_10 * 0x510;
    *(float *)(iVar6 + 0x194) = *(float *)(iVar6 + 0x194) * (float)iStack_20->nTarotParam;
    iVar6 = iStack_20 + iStack_10 * 0x510;
    *(float *)(iVar6 + 0x194) = *(float *)(iVar6 + 0x194) / 100.0;
    if ((long)((ulong)iStack_20->bTarotFlags << 0x3e) < 0) {
      if ((long)((ulong)iStack_20->bTarotFlags << 0x3d) < 0) {
        uStack_ce = 300;
      }
      else {
        uStack_ce = 100;
      }
      bStack_ca = bStack_ca & 0x9f | 0x40;
    }
    else {
      if ((long)((ulong)iStack_20->bTarotFlags << 0x3d) < 0) {
        uStack_ce = 0xffb5;
      }
      else {
        uStack_ce = 0xffce;
      }
      bStack_ca = bStack_ca & 0x9f | 0x20;
    }
    unaff_s3 = 5;
    break;
  case 5:
    uStack_a0 = 0x4583;
    uStack_9c = 6;
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    if (uVar9 == 3) {
      uStack_98 = 100;
    }
    else if (uVar9 == 2) {
      uStack_98 = 0x32;
    }
    else if (uVar9 == 1) {
      uStack_98 = 100;
    }
    else {
      uStack_98 = 0x32;
    }
    uVar8 = 1;
    unaff_s3 = 1;
    break;
  case 6:
    if (uVar9 == 3) {
      uStack_a0 = 0x4183;
      uStack_9c = 0x49;
      uStack_9a = iStack_20->nTarotCard << 6;
      uStack_9b = 100;
      uStack_98 = 0;
      uStack_94 = 0x4183;
      uStack_90 = 0x4a;
      sStack_8e = iStack_20->nTarotCard << 6;
      uStack_8f = 100;
      uStack_8c = 0;
      uStack_88 = 0x4183;
      uStack_84 = 0x4b;
      sStack_82 = iStack_20->nTarotCard << 6;
      uStack_83 = 100;
      uStack_80 = 0;
      uVar8 = 3;
    }
    else if (uVar9 == 2) {
      uStack_a0 = 0x4583;
      uStack_9c = 0x40;
      uStack_9a = iStack_20->nTarotCard << 6;
      uStack_9b = 100;
      uStack_98 = 0x32;
      uStack_94 = 0x4583;
      uStack_90 = 0x41;
      sStack_8e = iStack_20->nTarotCard << 6;
      uStack_8f = 100;
      uStack_8c = 0x32;
      uStack_88 = 0x4583;
      uStack_84 = 0x42;
      sStack_82 = iStack_20->nTarotCard << 6;
      uStack_83 = 100;
      uStack_80 = 0x32;
      uVar8 = 3;
    }
    else if (uVar9 == 1) {
      uStack_a0 = 0x4d83;
      uStack_9c = 0x2c;
      uStack_9a = iStack_20->nTarotCard << 6;
      uStack_9b = 100;
      uStack_98 = 100;
      uVar8 = 1;
    }
    else {
      uStack_a0 = 0x4583;
      uStack_9c = 0x2c;
      uStack_9a = iStack_20->nTarotCard << 6;
      uStack_9b = 100;
      uStack_98 = 0x32;
      uVar8 = 1;
    }
    uStack_9b = 100;
    unaff_s3 = 1;
    break;
  case 7:
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    if (uVar9 == 3) {
      uStack_a0 = 0x4183;
      uStack_9c = 0x49;
      uStack_98 = 0;
    }
    else if (uVar9 == 2) {
      uStack_a0 = 0x4583;
      uStack_9c = 0x43;
      uStack_98 = 0x32;
    }
    else if (uVar9 == 1) {
      uStack_a0 = 0x4183;
      uStack_9c = 0x49;
      uStack_98 = 0;
    }
    else {
      uStack_a0 = 0x4583;
      uStack_9c = 0x43;
      uStack_98 = 0x32;
    }
    uVar8 = 1;
    unaff_s3 = 1;
    break;
  case 8:
    return;
  case 9:
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    if (uVar9 == 3) {
      uStack_a0 = 0x4183;
      uStack_9c = 0x4b;
      uStack_98 = 0;
    }
    else if (uVar9 == 2) {
      uStack_a0 = 0x4583;
      uStack_9c = 0x42;
      uStack_98 = 0x32;
    }
    else if (uVar9 == 1) {
      uStack_a0 = 0x4d83;
      uStack_9c = 8;
      uStack_98 = 100;
    }
    else {
      uStack_a0 = 0x4583;
      uStack_9c = 8;
      uStack_98 = 0x32;
    }
    uVar8 = 1;
    unaff_s3 = 1;
    break;
  case 10:
    uStack_24 = (uint)chr(iStack_20,iStack_10)->f8e;
    uVar3 = GetLuc__7CBattleFii(iStack_20,iStack_10,0xfffffffffffffffe);
    chr(iStack_20,iStack_10)->f8e = uVar3;
    sStack_f6 = chr(iStack_20,iStack_10)->f8e - (short)uStack_24;
    GetTurnInterval__7CBattleFi(iStack_20,iStack_10);
    unaff_s3 = 0;
    break;
  case 0xb:
    unaff_s3 = 2;
    break;
  case 0xc:
    uStack_a0 = 0x4183;
    uStack_9c = 0x51;
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    uStack_98 = 0;
    if (uVar9 == 3) {
      uStack_9a = uStack_9a | 2;
    }
    else if (uVar9 == 2) {
      uStack_9a = uStack_9a | 1;
    }
    else if (uVar9 == 1) {
      uStack_9a = uStack_9a | 2;
    }
    else {
      uStack_9a = uStack_9a | 1;
    }
    uVar8 = 1;
    unaff_s3 = 1;
    break;
  case 0xd:
    unaff_s3 = 3;
    break;
  case 0xe:
    return;
  case 0xf:
    unaff_s3 = 4;
    break;
  case 0x10:
    puVar5 = (uint *)(*(int *)(iGpffff8324 + 0xc) + (uint)*(byte *)(iGpffff83b4 + 2) * 4 + 4);
    uStack_24 = *puVar5;
    if (uVar9 == 3) {
      iVar7 = uStack_24 + 2;
      if (iVar7 < 0) {
        iVar7 = uStack_24 + 5;
      }
      uStack_24 = iVar7 >> 2;
    }
    else if (uVar9 == 2) {
      iVar7 = uStack_24 + 1;
      if (iVar7 < 0) {
        iVar7 = uStack_24 + 2;
      }
      uStack_24 = iVar7 >> 1;
    }
    else if (uVar9 == 1) {
      uStack_24 = uStack_24 << 2;
    }
    else {
      uStack_24 = uStack_24 << 1;
    }
    if ((int)uStack_24 < 0) {
      uStack_24 = 0;
    }
    if (99999999 < (int)uStack_24) {
      uStack_24 = 99999999;
    }
    *puVar5 = uStack_24;
    return;
  case 0x11:
    uStack_24 = *(uint *)(iStack_20 + iStack_10 * 0x510 + 300);
    uVar4 = GetMaxHP__7CBattleFi(iStack_20,iStack_10);
    *(undefined4 *)(iStack_20 + iStack_10 * 0x510 + 300) = uVar4;
    if (*(uint *)(iStack_20 + iStack_10 * 0x510 + 300) <
        chr(iStack_20,iStack_10)->nHp) {
      chr(iStack_20,iStack_10)->nHp =
           *(undefined4 *)(iStack_20 + iStack_10 * 0x510 + 300);
    }
    sStack_f2 = (short)*(undefined4 *)(iStack_20 + iStack_10 * 0x510 + 300) - (short)uStack_24;
    unaff_s3 = 0;
    break;
  case 0x12:
    uStack_24 = (uint)chr(iStack_20,iStack_10)->f84;
    uVar3 = GetMaxMP__7CBattleFi(iStack_20,iStack_10);
    chr(iStack_20,iStack_10)->f84 = uVar3;
    if ((long)(ulong)chr(iStack_20,iStack_10)->f84 <
        (long)chr(iStack_20,iStack_10)->f86) {
      chr(iStack_20,iStack_10)->f86 =
           chr(iStack_20,iStack_10)->f84;
    }
    sStack_f0 = chr(iStack_20,iStack_10)->f84 - (short)uStack_24;
    unaff_s3 = 0;
    break;
  case 0x13:
    uStack_24 = (uint)chr(iStack_20,iStack_10)->f88;
    uVar3 = GetMaxSP__7CBattleFi(iStack_20,iStack_10);
    chr(iStack_20,iStack_10)->f88 = uVar3;
    if ((long)(ulong)chr(iStack_20,iStack_10)->f88 <
        (long)chr(iStack_20,iStack_10)->nSp) {
      chr(iStack_20,iStack_10)->nSp =
           chr(iStack_20,iStack_10)->f88;
    }
    sStack_ee = chr(iStack_20,iStack_10)->f88 - (short)uStack_24;
    unaff_s3 = 0;
    break;
  case 0x14:
    return;
  case 0x15:
    return;
  }
  switch(unaff_s3) {
  case 1:
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,uVar8,&uStack_a0,aiStack_110,0,
                    iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    break;
  case 2:
    uStack_a0 = 0x183;
    uStack_9c = 0x54;
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    uStack_98 = 0x80;
    uStack_94 = 0x4183;
    uStack_90 = 0x2b;
    sStack_8e = iStack_20->nTarotCard << 6;
    uStack_8f = 100;
    uStack_8c = 0;
    uStack_88 = 0x8983;
    uStack_84 = 0x54;
    sStack_82 = iStack_20->nTarotCard << 6;
    uStack_83 = 100;
    uStack_80 = 0;
    uStack_7c = 0x4583;
    uStack_78 = 6;
    sStack_76 = iStack_20->nTarotCard << 6;
    uStack_77 = 100;
    uStack_74 = 100;
    if (chr(iStack_20,iStack_10)->nCharId == 3) {
      if (uVar9 == 3) {
        EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                        iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
      }
      else if (uVar9 == 2) {
        EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,3,&uStack_94,aiStack_110,0,
                        iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
      }
      else if (uVar9 == 1) {
        EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,3,&uStack_94,aiStack_110,0,
                        iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
      }
      else {
        EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                        iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
      }
    }
    else if (uVar9 == 3) {
      EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                      iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    }
    else if (uVar9 == 2) {
      EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                      iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    }
    else if (uVar9 == 1) {
      EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,3,&uStack_94,aiStack_110,0,
                      iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    }
    else {
      EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,3,&uStack_94,aiStack_110,0,
                      iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    }
    break;
  case 3:
    uStack_a0 = 0x183;
    uStack_9c = 0x54;
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    uStack_98 = 0x80;
    if (uVar9 == 3) {
      uStack_a0 = 0x4183;
    }
    else if ((uVar9 != 2) && (uVar9 == 1)) {
      uStack_a0 = 0x4183;
    }
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                    iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
    break;
  case 4:
    uVar10 = 0;
    iStack_2c = 0;
    for (uStack_24 = 0; (int)uStack_24 < 0x20; uStack_24 = uStack_24 + 1) {
      if (*(char *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1d0) == 'T') {
        if ((((ulong)*(byte *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1cd) & 0x3f) >> 3
             == 0) &&
           ((*(uint *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1d4) & 3) != 0)) {
          iStack_2c = 1;
        }
        if (((ulong)*(byte *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1cd) & 0x3f) >> 3
            == 2) {
          if (((long)*(int *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1cc) & 0x1ffffU)
              >> 0xf == 0) {
            uVar10 = uVar10 | *(uint *)(iStack_20 + iStack_10 * 0x510 + uStack_24 * 0xc + 0x1d4);
          }
          else {
            uVar10 = uVar10 | 0xff;
          }
        }
      }
    }
    if ((chr(iStack_20,iStack_10)->bFlagsB & 1) == 0) {
      for (uStack_24 = 0; (int)uStack_24 < 3; uStack_24 = uStack_24 + 1) {
        if (-1 < *(char *)(iGpffff83b4 + chr(iStack_20,iStack_10)->nCharId * 0xc0 +
                           uStack_24 + 0x6b)) {
          cVar2 = *(char *)(iGpffff83b4 + chr(iStack_20,iStack_10)->nCharId * 0xc0 +
                            uStack_24 + 0x6b);
          iStack_34 = iStack_38 + (cVar2 * 10 + (int)cVar2) * 4 + 0x10;
          iVar6 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(chr(iStack_20,iStack_10)->nCharId,7,
                                  *(undefined1 *)
                                   (iGpffff83b4 +
                                    chr(iStack_20,iStack_10)->nCharId * 0xc0 +
                                    uStack_24 + 0x6b),iStack_34,&uStack_230 + iVar7 * 3,
                                  iStack_20 + iStack_10 * 0x510 + 0xb0);
          iVar7 = iVar7 + iVar6;
        }
      }
      for (uStack_24 = 0; (int)uStack_24 < iVar7; uStack_24 = uStack_24 + 1) {
        if ((acStack_22c[uStack_24 * 0xc] == 'T') &&
           (((ulong)*(byte *)((int)&uStack_230 + uStack_24 * 0xc + 1) & 0x3f) >> 3 == 2)) {
          if (((long)(int)(&uStack_230)[uStack_24 * 3] & 0x1ffffU) >> 0xf == 0) {
            uVar10 = uVar10 | auStack_228[uStack_24 * 3];
          }
          else {
            uVar10 = uVar10 | 0xff;
          }
        }
      }
    }
    else {
      iVar7 = chr(iStack_20,iStack_10)->pParam;
      if ((*(byte *)(iVar7 + 0x34) & 1) != 0) {
        uVar10 = uVar10 | 1;
      }
      if ((long)((ulong)*(byte *)(iVar7 + 0x34) << 0x3e) < 0) {
        uVar10 = uVar10 | 2;
      }
      if ((long)((ulong)*(byte *)(iVar7 + 0x34) << 0x3d) < 0) {
        uVar10 = uVar10 | 4;
      }
      if ((long)((ulong)*(byte *)(iVar7 + 0x34) << 0x3c) < 0) {
        uVar10 = uVar10 | 8;
      }
      if ((long)((ulong)*(byte *)(iVar7 + 0x34) << 0x3b) < 0) {
        uVar10 = uVar10 | 0x20;
      }
    }
    uStack_a0 = 0x183;
    uStack_9c = 0x54;
    uStack_9a = iStack_20->nTarotCard << 6;
    uStack_9b = 100;
    uStack_98 = 0;
    uStack_24 = 0;
    if (iStack_2c == 0) {
      if ((uVar10 & 1) == 0) {
        uStack_98 = 1;
        uStack_24 = 1;
      }
    }
    else if ((uVar10 & 2) == 0) {
      uStack_98 = 1;
      uStack_24 = 1;
    }
    if ((uVar10 & 4) == 0) {
      uStack_98 = uStack_98 | 4;
      uStack_24 = uStack_24 + 1;
    }
    if ((uVar10 & 8) == 0) {
      uStack_98 = uStack_98 | 8;
      uStack_24 = uStack_24 + 1;
    }
    if ((uVar10 & 0x20) == 0) {
      uStack_98 = uStack_98 | 0x20;
      uStack_24 = uStack_24 + 1;
    }
    do {
      if ((((uVar9 & 1) != 0) || ((int)uStack_24 < 2)) &&
         (((uVar9 & 1) == 0 || ((int)uStack_24 < 3)))) goto LAB_006a4578;
      iStack_28 = rand();
      iStack_28 = iStack_28 % (int)uStack_24;
      iVar7 = 0;
      for (uVar10 = 0; (int)uVar10 < 0x18; uVar10 = uVar10 + 1) {
        if ((uStack_98 & 1 << (uVar10 & 0x1f)) != 0) {
          if (iVar7 == iStack_28) {
            uStack_98 = uStack_98 - (1 << (uVar10 & 0x1f));
            uStack_24 = uStack_24 - 1;
            break;
          }
          iVar7 = iVar7 + 1;
        }
      }
    } while( true );
  case 5:
    IdelMotionReset__Fi(iStack_10,0);
    EffectMesCall__7CBattleFiP8ECResultP7FVectorb(iStack_20,iStack_10,aiStack_110,0,0,1);
    return;
  }
switchD_006a3278_caseD_0:
  IdelMotionReset__Fi(iStack_10,0);
  EffectMesCall__7CBattleFiP8ECResultP7FVectorb(iStack_20,iStack_10,aiStack_110,0,0,0);
  if (chr(iStack_20,iStack_10)->nHp < 1) {
    if ((chr(iStack_20,iStack_10)->bFlagsB & 1) == 0) {
      if ((chr(iStack_20,iStack_10)->bState < '\x19') ||
         ('*' < chr(iStack_20,iStack_10)->bState)) {
        chr(iStack_20,iStack_10)->bState = 0x26;
        chr(iStack_20,iStack_10)->bState2 = 0;
      }
      else if (chr(iStack_20,iStack_10)->bState == '*') {
        chr(iStack_20,iStack_10)->bState = 0x25;
        chr(iStack_20,iStack_10)->bState2 = 0;
      }
      if (uStack_30 != 0) {
        iVar7 = iGpffff83b4 + chr(iStack_20,iStack_10)->nCharId * 0x24;
        *(int *)(iVar7 + 0x1508) = *(int *)(iVar7 + 0x1508) + 1;
      }
    }
    else {
      DeathInit__7CBattleFi(iStack_20,iStack_10);
      cVar2 = chr(iStack_20,iStack_10)->ff3;
      if (((cVar2 == '\x03') || (cVar2 == '\x02')) || (cVar2 == '\x01')) {
        if ((chr(iStack_20,iStack_10)->bState < '\x19') ||
           ('*' < chr(iStack_20,iStack_10)->bState)) {
          chr(iStack_20,iStack_10)->bState = 0x26;
          chr(iStack_20,iStack_10)->bState2 = 0;
        }
        else if (chr(iStack_20,iStack_10)->bState == '*') {
          chr(iStack_20,iStack_10)->bState = 0x25;
          chr(iStack_20,iStack_10)->bState2 = 0;
        }
      }
    }
  }
  else if (((chr(iStack_20,iStack_10)->nHp < 1) || ((uStack_c8 & 0x20) == 0)) ||
          (('\x18' < chr(iStack_20,iStack_10)->bState &&
           (chr(iStack_20,iStack_10)->bState < '+')))) {
    if (((chr(iStack_20,iStack_10)->nHp < 1) || ((uStack_c8 & 0x20) == 0)) ||
       (chr(iStack_20,iStack_10)->bState != '*')) {
      if (((0 < chr(iStack_20,iStack_10)->nHp) &&
          ((chr(iStack_20,iStack_10)->bState < '\x19' ||
           ('*' < chr(iStack_20,iStack_10)->bState)))) && (aiStack_110[0] < 0)) {
        chr(iStack_20,iStack_10)->bState = 0x18;
        chr(iStack_20,iStack_10)->bState2 = 0;
        if (chr(iStack_20,iStack_10)->bState == '\x11') {
          chr(iStack_20,iStack_10)->fc = 1;
        }
        else {
          chr(iStack_20,iStack_10)->fc = 0;
        }
      }
    }
    else {
      chr(iStack_20,iStack_10)->bState = 0x25;
      chr(iStack_20,iStack_10)->bState2 = 0;
    }
  }
  else {
    chr(iStack_20,iStack_10)->bState = 0x27;
    chr(iStack_20,iStack_10)->bState2 = 0;
  }
  return;
LAB_006a4578:
  if (uStack_98 == 0) {
    uStack_98 = 1;
  }
  EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_10,1,&uStack_a0,aiStack_110,0,
                  iStack_20 + iStack_10 * 0x510 + 0xb0,0,0);
  goto switchD_006a3278_caseD_0;
}
