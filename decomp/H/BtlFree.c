/* decomp/H/BtlFree.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 30 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c60  Get3DAngle__F7FVector
 * C++: Get3DAngle(FVector)
 * size: 0x398 bytes
 * --------------------------------------------------------------------------- */
void Get3DAngle__F7FVector(undefined8 param_1,undefined8 param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 (*pauVar3) [16];
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  Normalize__7FVectorFv(param_2);
  __ct__7FVectorFRC7FVector(&uStack_50,param_2);
  uStack_4c = 0;
  Normalize__7FVectorFv(&uStack_50);
  auVar6._4_4_ = uStack_4c;
  auVar6._0_4_ = uStack_50;
  auVar6._8_4_ = uStack_48;
  auVar6._12_4_ = uStack_44;
  auVar6 = _lqc2(auVar6);
  auVar7 = _lqc2(auRam00657080);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ <= -1.0) {
    fVar4 = 3.141592;
  }
  else if (1.0 <= auVar6._0_4_) {
    fVar4 = 0.0;
  }
  else {
    fVar4 = (float)acosf();
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixY(fVar4,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_60,auStack_40,0x657080);
  auVar7._4_4_ = uStack_5c;
  auVar7._0_4_ = uStack_60;
  auVar7._8_4_ = uStack_58;
  auVar7._12_4_ = uStack_54;
  auVar6 = _lqc2(auVar7);
  auVar8._4_4_ = uStack_4c;
  auVar8._0_4_ = uStack_50;
  auVar8._8_4_ = uStack_48;
  auVar8._12_4_ = uStack_44;
  auVar7 = _lqc2(auVar8);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ < 0.999999) {
    fVar4 = -fVar4;
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixY(-fVar4,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_70,auStack_40,param_2);
  pauVar3 = (undefined1 (*) [16])param_2;
  *(undefined4 *)*pauVar3 = uStack_70;
  *(undefined4 *)(*pauVar3 + 4) = uStack_6c;
  *(undefined4 *)(*pauVar3 + 8) = uStack_68;
  *(undefined4 *)(*pauVar3 + 0xc) = uStack_64;
  uStack_50 = *(undefined4 *)*pauVar3;
  uStack_48 = *(undefined4 *)(*pauVar3 + 8);
  uStack_44 = *(undefined4 *)(*pauVar3 + 0xc);
  uStack_4c = 0;
  Normalize__7FVectorFv(&uStack_50);
  auVar6 = _lqc2(*pauVar3);
  auVar2._4_4_ = uStack_4c;
  auVar2._0_4_ = uStack_50;
  auVar2._8_4_ = uStack_48;
  auVar2._12_4_ = uStack_44;
  auVar7 = _lqc2(auVar2);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ <= -1.0) {
    fVar5 = 3.141592;
  }
  else if (1.0 <= auVar6._0_4_) {
    fVar5 = 0.0;
  }
  else {
    fVar5 = (float)acosf();
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixX(fVar5,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_80,auStack_40,&uStack_50);
  uStack_60 = uStack_80;
  uStack_5c = uStack_7c;
  uStack_58 = uStack_78;
  uStack_54 = uStack_74;
  auVar1._4_4_ = uStack_7c;
  auVar1._0_4_ = uStack_80;
  auVar1._8_4_ = uStack_78;
  auVar1._12_4_ = uStack_74;
  auVar6 = _lqc2(auVar1);
  auVar7 = _lqc2(*pauVar3);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ < 0.999999) {
    fVar5 = -fVar5;
  }
  *(float *)*pauVar3 = -fVar5 * 57.29579;
  *(float *)(*pauVar3 + 4) = -fVar4 * 57.29579;
  *(undefined4 *)(*pauVar3 + 0xc) = 0;
  *(undefined4 *)(*pauVar3 + 8) = 0;
  __ct__7FVectorFRC7FVector(param_1,param_2);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d9000  Get3DAngleRad__F7FVector
 * C++: Get3DAngleRad(FVector)
 * size: 0x378 bytes
 * --------------------------------------------------------------------------- */
void Get3DAngleRad__F7FVector(undefined8 param_1,undefined8 param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 (*pauVar3) [16];
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  Normalize__7FVectorFv(param_2);
  __ct__7FVectorFRC7FVector(&uStack_50,param_2);
  uStack_4c = 0;
  Normalize__7FVectorFv(&uStack_50);
  auVar6._4_4_ = uStack_4c;
  auVar6._0_4_ = uStack_50;
  auVar6._8_4_ = uStack_48;
  auVar6._12_4_ = uStack_44;
  auVar6 = _lqc2(auVar6);
  auVar7 = _lqc2(auRam00657080);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ <= -1.0) {
    fVar4 = 3.1415927;
  }
  else if (1.0 <= auVar6._0_4_) {
    fVar4 = 0.0;
  }
  else {
    fVar4 = (float)acosf();
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixY(fVar4,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_60,auStack_40,0x657080);
  auVar7._4_4_ = uStack_5c;
  auVar7._0_4_ = uStack_60;
  auVar7._8_4_ = uStack_58;
  auVar7._12_4_ = uStack_54;
  auVar6 = _lqc2(auVar7);
  auVar8._4_4_ = uStack_4c;
  auVar8._0_4_ = uStack_50;
  auVar8._8_4_ = uStack_48;
  auVar8._12_4_ = uStack_44;
  auVar7 = _lqc2(auVar8);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ < 0.999999) {
    fVar4 = -fVar4;
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixY(-fVar4,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_70,auStack_40,param_2);
  pauVar3 = (undefined1 (*) [16])param_2;
  *(undefined4 *)*pauVar3 = uStack_70;
  *(undefined4 *)(*pauVar3 + 4) = uStack_6c;
  *(undefined4 *)(*pauVar3 + 8) = uStack_68;
  *(undefined4 *)(*pauVar3 + 0xc) = uStack_64;
  uStack_50 = *(undefined4 *)*pauVar3;
  uStack_48 = *(undefined4 *)(*pauVar3 + 8);
  uStack_44 = *(undefined4 *)(*pauVar3 + 0xc);
  uStack_4c = 0;
  Normalize__7FVectorFv(&uStack_50);
  auVar6 = _lqc2(*pauVar3);
  auVar2._4_4_ = uStack_4c;
  auVar2._0_4_ = uStack_50;
  auVar2._8_4_ = uStack_48;
  auVar2._12_4_ = uStack_44;
  auVar7 = _lqc2(auVar2);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ <= -1.0) {
    fVar5 = 3.1415927;
  }
  else if (1.0 <= auVar6._0_4_) {
    fVar5 = 0.0;
  }
  else {
    fVar5 = (float)acosf();
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  sceVu0RotMatrixX(fVar5,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_80,auStack_40,&uStack_50);
  uStack_60 = uStack_80;
  uStack_5c = uStack_7c;
  uStack_58 = uStack_78;
  uStack_54 = uStack_74;
  auVar1._4_4_ = uStack_7c;
  auVar1._0_4_ = uStack_80;
  auVar1._8_4_ = uStack_78;
  auVar1._12_4_ = uStack_74;
  auVar6 = _lqc2(auVar1);
  auVar7 = _lqc2(*pauVar3);
  auVar6 = _vmul(auVar6,auVar7);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _vaddbc(auVar6,auVar6);
  auVar6 = _qmfc2(auVar6._0_4_);
  if (auVar6._0_4_ < 0.999999) {
    fVar5 = -fVar5;
  }
  *(float *)*pauVar3 = -fVar5;
  *(float *)(*pauVar3 + 4) = -fVar4;
  *(undefined4 *)(*pauVar3 + 0xc) = 0;
  *(undefined4 *)(*pauVar3 + 8) = 0;
  __ct__7FVectorFRC7FVector(param_1,param_2);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d9380  Get3DAngle2__F7FVector
 * C++: Get3DAngle2(FVector)
 * size: 0x884 bytes
 * --------------------------------------------------------------------------- */
void Get3DAngle2__F7FVector(undefined8 param_1,undefined8 param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 (*pauVar12) [16];
  float fVar13;
  float fVar14;
  undefined1 in_vf0 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  __ct__7FVectorFRC7FVector(&uStack_50,param_2);
  Normalize__7FVectorFv(param_2);
  __ct__7FVectorFRC7FVector(&uStack_60,param_2);
  uStack_58 = 0;
  Normalize__7FVectorFv(&uStack_60);
  uStack_80 = 0x3f800000;
  uStack_7c = 0;
  uStack_78 = 0;
  uStack_74 = 0x3f800000;
  auVar16._4_4_ = uStack_5c;
  auVar16._0_4_ = uStack_60;
  auVar16._8_4_ = uStack_58;
  auVar16._12_4_ = uStack_54;
  auVar16 = _lqc2(auVar16);
  auVar15._12_4_ = 0x3f800000;
  auVar15._0_12_ = ZEXT812(0x3f800000);
  auVar15 = _lqc2(auVar15);
  auVar15 = _vmul(auVar16,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ <= -1.0) {
    fVar13 = 3.141592;
  }
  else if (1.0 <= auVar15._0_4_) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = (float)acosf();
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixZ(fVar13,auStack_40,auStack_40);
  uStack_90 = 0x3f800000;
  uStack_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_70,auStack_40,&uStack_90);
  auVar17._4_4_ = uStack_6c;
  auVar17._0_4_ = uStack_70;
  auVar17._8_4_ = uStack_68;
  auVar17._12_4_ = uStack_64;
  auVar15 = _lqc2(auVar17);
  auVar7._4_4_ = uStack_5c;
  auVar7._0_4_ = uStack_60;
  auVar7._8_4_ = uStack_58;
  auVar7._12_4_ = uStack_54;
  auVar16 = _lqc2(auVar7);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ < 0.999999) {
    fVar13 = -fVar13;
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixZ(-fVar13,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_a0,auStack_40,param_2);
  pauVar12 = (undefined1 (*) [16])param_2;
  *(undefined4 *)*pauVar12 = uStack_a0;
  *(undefined4 *)(*pauVar12 + 4) = uStack_9c;
  *(undefined4 *)(*pauVar12 + 8) = uStack_98;
  *(undefined4 *)(*pauVar12 + 0xc) = uStack_94;
  uStack_60 = *(undefined4 *)*pauVar12;
  uStack_58 = *(undefined4 *)(*pauVar12 + 8);
  uStack_54 = *(undefined4 *)(*pauVar12 + 0xc);
  uStack_5c = 0;
  Normalize__7FVectorFv(&uStack_60);
  uStack_b0 = 0x3f800000;
  uStack_ac = 0;
  uStack_a8 = 0;
  uStack_a4 = 0x3f800000;
  auVar15 = _lqc2(*pauVar12);
  auVar3._12_4_ = 0x3f800000;
  auVar3._0_12_ = ZEXT812(0x3f800000);
  auVar16 = _lqc2(auVar3);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ <= -1.0) {
    fVar14 = 3.141592;
  }
  else if (1.0 <= auVar15._0_4_) {
    fVar14 = 0.0;
  }
  else {
    fVar14 = (float)acosf();
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixY(fVar14,auStack_40,auStack_40);
  uStack_d0 = 0x3f800000;
  uStack_cc = 0;
  uStack_c8 = 0;
  uStack_c4 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_c0,auStack_40,&uStack_d0);
  uStack_70 = uStack_c0;
  uStack_6c = uStack_bc;
  uStack_68 = uStack_b8;
  uStack_64 = uStack_b4;
  auVar4._4_4_ = uStack_bc;
  auVar4._0_4_ = uStack_c0;
  auVar4._8_4_ = uStack_b8;
  auVar4._12_4_ = uStack_b4;
  auVar15 = _lqc2(auVar4);
  auVar16 = _lqc2(*pauVar12);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ < 0.999999) {
    fVar14 = -fVar14;
  }
  *(float *)(*pauVar12 + 4) = -fVar14 * 57.29579;
  *(float *)(*pauVar12 + 8) = -fVar13 * 57.29579;
  Normalize__7FVectorFv(&uStack_50);
  uStack_60 = uStack_50;
  uStack_58 = uStack_48;
  uStack_54 = uStack_44;
  uStack_5c = 0;
  Normalize__7FVectorFv(&uStack_60);
  uStack_e0 = 0x3f800000;
  uStack_dc = 0;
  uStack_d8 = 0;
  uStack_d4 = 0x3f800000;
  auVar8._4_4_ = uStack_5c;
  auVar8._0_4_ = uStack_60;
  auVar8._8_4_ = uStack_58;
  auVar8._12_4_ = uStack_54;
  auVar15 = _lqc2(auVar8);
  auVar2._12_4_ = 0x3f800000;
  auVar2._0_12_ = ZEXT812(0x3f800000);
  auVar16 = _lqc2(auVar2);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ <= -1.0) {
    fVar13 = 3.141592;
  }
  else if (1.0 <= auVar15._0_4_) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = (float)acosf();
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixY(fVar13,auStack_40,auStack_40);
  uStack_100 = 0x3f800000;
  uStack_fc = 0;
  uStack_f8 = 0;
  uStack_f4 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_f0,auStack_40,&uStack_100);
  uStack_70 = uStack_f0;
  uStack_6c = uStack_ec;
  uStack_68 = uStack_e8;
  uStack_64 = uStack_e4;
  auVar5._4_4_ = uStack_ec;
  auVar5._0_4_ = uStack_f0;
  auVar5._8_4_ = uStack_e8;
  auVar5._12_4_ = uStack_e4;
  auVar15 = _lqc2(auVar5);
  auVar9._4_4_ = uStack_5c;
  auVar9._0_4_ = uStack_60;
  auVar9._8_4_ = uStack_58;
  auVar9._12_4_ = uStack_54;
  auVar16 = _lqc2(auVar9);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ < 0.999999) {
    fVar13 = -fVar13;
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixY(-fVar13,auStack_40,auStack_40);
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_110,auStack_40,&uStack_50);
  uStack_50 = uStack_110;
  uStack_4c = uStack_10c;
  uStack_48 = uStack_108;
  uStack_44 = uStack_104;
  uStack_60 = uStack_110;
  uStack_5c = uStack_10c;
  uStack_54 = uStack_104;
  uStack_58 = 0;
  Normalize__7FVectorFv(&uStack_60);
  uStack_120 = 0x3f800000;
  uStack_11c = 0;
  uStack_118 = 0;
  uStack_114 = 0x3f800000;
  auVar10._4_4_ = uStack_4c;
  auVar10._0_4_ = uStack_50;
  auVar10._8_4_ = uStack_48;
  auVar10._12_4_ = uStack_44;
  auVar15 = _lqc2(auVar10);
  auVar1._12_4_ = 0x3f800000;
  auVar1._0_12_ = ZEXT812(0x3f800000);
  auVar16 = _lqc2(auVar1);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ <= -1.0) {
    fVar13 = 3.141592;
  }
  else if (1.0 <= auVar15._0_4_) {
    fVar13 = 0.0;
  }
  else {
    fVar13 = (float)acosf();
  }
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar15);
  auStack_30 = _sqc2(auVar16);
  auStack_40 = _sqc2(auVar17);
  sceVu0RotMatrixZ(fVar13,auStack_40,auStack_40);
  uStack_140 = 0x3f800000;
  uStack_13c = 0;
  uStack_138 = 0;
  uStack_134 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_130,auStack_40,&uStack_140);
  uStack_70 = uStack_130;
  uStack_6c = uStack_12c;
  uStack_68 = uStack_128;
  uStack_64 = uStack_124;
  auVar6._4_4_ = uStack_12c;
  auVar6._0_4_ = uStack_130;
  auVar6._8_4_ = uStack_128;
  auVar6._12_4_ = uStack_124;
  auVar15 = _lqc2(auVar6);
  auVar11._4_4_ = uStack_4c;
  auVar11._0_4_ = uStack_50;
  auVar11._8_4_ = uStack_48;
  auVar11._12_4_ = uStack_44;
  auVar16 = _lqc2(auVar11);
  auVar15 = _vmul(auVar15,auVar16);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _vaddbc(auVar15,auVar15);
  auVar15 = _qmfc2(auVar15._0_4_);
  if (auVar15._0_4_ < 0.999999) {
    fVar13 = -fVar13;
  }
  *(float *)*pauVar12 = -fVar13 * 57.29579;
  *(undefined4 *)(*pauVar12 + 0xc) = 0;
  __ct__7FVectorFRC7FVector(param_1,param_2);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d9c10  GetPointToLineLength__F7FVector7FVector7FVectorP7FVector
 * C++: GetPointToLineLength(FVector, FVector, FVector, FVector *)
 * size: 0x1a0 bytes
 * --------------------------------------------------------------------------- */
void GetPointToLineLength__F7FVector7FVector7FVectorP7FVector
               (undefined1 (*param_1) [16],undefined1 (*param_2) [16],undefined1 (*param_3) [16],
               float *param_4)

{
  float fVar1;
  float fVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  float fStack_10;
  float fStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  auVar3 = _lqc2(*param_2);
  auVar4 = _lqc2(*param_1);
  auVar3 = _vsub(auVar3,auVar4);
  auStack_30 = _sqc2(auVar3);
  __ct__7FVectorFRC7FVector(&fStack_10,auStack_30);
  auVar3 = _lqc2(*param_3);
  auVar4 = _lqc2(*param_1);
  auVar3 = _vsub(auVar3,auVar4);
  auStack_40 = _sqc2(auVar3);
  __ct__7FVectorFRC7FVector(auStack_20,auStack_40);
  fVar2 = (float)Length__7FVectorCFv(&fStack_10);
  Normalize__7FVectorFv(&fStack_10);
  auVar3._4_4_ = fStack_c;
  auVar3._0_4_ = fStack_10;
  auVar3._8_4_ = fStack_8;
  auVar3._12_4_ = uStack_4;
  auVar3 = _lqc2(auVar3);
  auVar4 = _lqc2(auStack_20);
  auVar3 = _vmul(auVar3,auVar4);
  auVar3 = _vaddbc(auVar3,auVar3);
  auVar3 = _vaddbc(auVar3,auVar3);
  auVar3 = _qmfc2(auVar3._0_4_);
  fVar1 = auVar3._0_4_;
  if (fVar1 < 0.0) {
    fVar2 = 0.0;
  }
  else if (fVar1 <= fVar2) {
    fVar2 = fVar1;
  }
  *param_4 = *(float *)*param_1 + fStack_10 * fVar2;
  param_4[1] = *(float *)(*param_1 + 4) + fStack_c * fVar2;
  param_4[2] = *(float *)(*param_1 + 8) + fStack_8 * fVar2;
  param_4[3] = 1.0;
  fStack_10 = *param_4 - *(float *)*param_3;
  fStack_c = param_4[1] - *(float *)(*param_3 + 4);
  fStack_8 = param_4[2] - *(float *)(*param_3 + 8);
  uStack_4 = 0x3f800000;
  Length__7FVectorCFv(&fStack_10);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d9db0  IdelMotionReset__Fi
 * C++: IdelMotionReset(int)
 * size: 0x688 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005da1ac) */

void IdelMotionReset__Fi(int param_1)

{
  bool bVar1;
  long lVar2;
  int iVar3;
  
  bVar1 = false;
  if (1 < *(byte *)(iGpffff86b4 + param_1 * 0x4f0 + 0xb1) >> 5) {
    lVar2 = strcmp(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x6554f8);
    bVar1 = lVar2 != 0;
    if (bVar1) {
      strcpy(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x6554f8);
    }
    if (((*(short *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4f0) == 1) && (bVar1)) ||
       ((*(byte *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4b1) & 1) != 0)) {
      SetNextBtlMotion__8BtlModelFif
                (0x3f800000,*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),1);
    }
  }
  iVar3 = 0;
  while( true ) {
    if (0x1f < iVar3) {
      lVar2 = (long)((int)(uint)*(ushort *)(iGpffff86b4 + param_1 * 0x4f0 + 0x122) >> 2);
      if ((1 < *(ushort *)(iGpffff86b4 + param_1 * 0x4f0 + 0x122)) && (lVar2 == 0)) {
        lVar2 = 1;
      }
      if (lVar2 < *(short *)(iGpffff86b4 + param_1 * 0x4f0 + 0x124)) {
        lVar2 = strcmp(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x6554f8);
        if (lVar2 != 0) {
          strcpy(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x6554f8);
          bVar1 = true;
        }
      }
      else {
        lVar2 = strcmp(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x655500);
        if (lVar2 != 0) {
          strcpy(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x655500);
          bVar1 = true;
        }
      }
      if (((*(short *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4f0) == 1) && (bVar1)) ||
         ((*(byte *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4b1) & 1) != 0)) {
        SetNextBtlMotion__8BtlModelFif
                  (0x3f800000,*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),1);
      }
      return;
    }
    if (((*(char *)(iGpffff86b4 + param_1 * 0x4f0 + iVar3 * 0xc + 0x1bc) == 'G') &&
        (((ulong)*(byte *)(iGpffff86b4 + param_1 * 0x4f0 + iVar3 * 0xc + 0x1b9) & 0x1f) >> 2 == 0))
       && ((*(uint *)(iGpffff86b4 + param_1 * 0x4f0 + iVar3 * 0xc + 0x1c0) & 7) != 0)) break;
    iVar3 = iVar3 + 1;
  }
  lVar2 = strcmp(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x655500);
  if (lVar2 != 0) {
    strcpy(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x50c,0x655500);
    bVar1 = true;
  }
  if (((*(short *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4f0) != 1) || (!bVar1)) &&
     ((*(byte *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4b1) & 1) == 0)) {
    return;
  }
  SetNextBtlMotion__8BtlModelFif
            (0x3f800000,*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005da440  StatusRecovery__Fii
 * C++: StatusRecovery(int, int)
 * size: 0x13d4 bytes
 * --------------------------------------------------------------------------- */
void StatusRecovery__Fii(int param_1,int param_2)

{
  undefined8 uVar1;
  int iVar2;
  ulong uVar3;
  uint uVar4;
  ulong uVar5;
  long lVar6;
  undefined1 auStack_f0 [96];
  undefined2 uStack_90;
  byte abStack_8e [6];
  undefined4 auStack_88 [23];
  float fStack_2c;
  int iStack_28;
  char cStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_28 = 0;
  iStack_20 = param_1;
  iStack_10 = param_2;
  memset(auStack_f0,0,0x60);
  if (pCGpffff86b4->nPhase == 10) {
    lVar6 = (long)pCGpffff86b4->nCmdKind;
  }
  else if (pCGpffff86b4->nPhase == 0xb) {
    lVar6 = (long)pCGpffff86b4->nCmdKind;
  }
  else if (pCGpffff86b4->nPhase == 0xc) {
    lVar6 = 5;
  }
  else if (pCGpffff86b4->nPhase == 3) {
    lVar6 = (long)pCGpffff86b4->nCmdKind;
  }
  else {
    lVar6 = -1;
  }
  switch(lVar6) {
  case 0:
    iVar2 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,2,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x44 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20);
    break;
  case 1:
    iVar2 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,3,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x30 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20);
    break;
  case 2:
    if ((*(byte *)((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1) == 0
       ) {
      lVar6 = (long)*(short *)((int)pCGpffff86b4 +
                              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                              0x120);
    }
    else {
      switch(*(undefined2 *)
              ((int)pCGpffff86b4 +
              (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
      case 0:
      case 1:
        lVar6 = 0xc;
        break;
      case 2:
      case 3:
        lVar6 = 0xd;
        break;
      case 4:
      case 5:
        lVar6 = 0xe;
        break;
      case 6:
      case 7:
        lVar6 = 0xf;
        break;
      case 8:
      case 9:
        lVar6 = 0x10;
        break;
      case 10:
      case 0xb:
        lVar6 = 0x11;
        break;
      case 0xc:
      case 0xd:
        lVar6 = 0x12;
        break;
      case 0xe:
        lVar6 = 0x13;
        break;
      case 0xf:
        lVar6 = 0x14;
        break;
      case 0x10:
        lVar6 = 0x15;
      }
    }
    iVar2 = GetRegDat__9RegDatApiFiii(0x36,lVar6,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,1,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x40 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20);
    break;
  case 3:
    iVar2 = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,1,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x20 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    uVar1 = EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                            pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20,uVar1);
    break;
  case 4:
    iVar2 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,4,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x40 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20);
    break;
  case 5:
    iVar2 = GetRegDat__9RegDatApiFiii(0x3d,0,0xffffffffffffffff);
    iStack_28 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(pCGpffff86b4->cActor,5,pCGpffff86b4->nCmd0,
                                iVar2 + pCGpffff86b4->nCmd0 * 0x40 + 8,&uStack_90,
                                (int)pCGpffff86b4 +
                                (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 +
                                0xb0);
    if (0 < iStack_10) {
      StepEffectFunc__7CBattleFiPiP6EFFTBL(pCGpffff86b4,iStack_10,&iStack_28,&uStack_90);
    }
    fStack_2c = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,(uchar *)0x0,&cStack_21);
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(fStack_2c,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,cStack_21 != '\0');
    IdelMotionReset__Fi(iStack_20);
    break;
  case 6:
    if ((pCGpffff86b4->aChr[iStack_20].bFlagsB & 1) == 0) {
      return;
    }
    uVar5 = (ulong)pCGpffff86b4->aChr[iStack_20].nSubId;
    uVar3 = uVar5 & 7;
    uVar4 = (uint)uVar3;
    if (((long)uVar5 < 0) && (uVar3 != 0)) {
      uVar4 = uVar4 - 8;
    }
    iVar2 = ourBtlSaveDat + ((int)pCGpffff86b4->aChr[iStack_20].nSubId >> 3);
    *(byte *)(iVar2 + 0xdcf) = *(byte *)(iVar2 + 0xdcf) | (byte)(1 << (uVar4 & 0x1f));
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x3a) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 1;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x4d) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 2;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x26) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 4;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x33) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 8;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0xcc) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 0x10;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x6f) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 0x20;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x7e) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 0x40;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x82) {
      *(byte *)(ourBtlSaveDat + 0xe2f) = *(byte *)(ourBtlSaveDat + 0xe2f) | 0x80;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId == 0x92) {
      *(byte *)(ourBtlSaveDat + 0xe30) = *(byte *)(ourBtlSaveDat + 0xe30) | 1;
    }
    if (pCGpffff86b4->aChr[iStack_20].nSubId != 0x9c) {
      return;
    }
    *(byte *)(ourBtlSaveDat + 0xe30) = *(byte *)(ourBtlSaveDat + 0xe30) | 2;
    return;
  case 7:
    *(byte *)(&uStack_90 + iStack_28 * 6) =
         *(byte *)(&uStack_90 + iStack_28 * 6) & 0xc0 |
         (byte)pCGpffff86b4->aChr[iStack_20].nCharId & 0x3f;
    (&uStack_90)[iStack_28 * 6] = (&uStack_90)[iStack_28 * 6] & 0xfe3f | 0x1c0;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xfd;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xe3;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xdf;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0x3f | 0x40;
    abStack_8e[iStack_28 * 0xc] = abStack_8e[iStack_28 * 0xc] & 0xfe;
    abStack_8e[iStack_28 * 0xc + 2] = 0x2b;
    abStack_8e[iStack_28 * 0xc + 3] = 0;
    abStack_8e[iStack_28 * 0xc + 4] = 100;
    abStack_8e[iStack_28 * 0xc + 5] = 0x27;
    auStack_88[iStack_28 * 3] = 0;
    iStack_28 = iStack_28 + 1;
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,0);
    IdelMotionReset__Fi(iStack_20);
    break;
  case 8:
    *(byte *)(&uStack_90 + iStack_28 * 6) =
         *(byte *)(&uStack_90 + iStack_28 * 6) & 0xc0 |
         (byte)pCGpffff86b4->aChr[iStack_20].nCharId & 0x3f;
    (&uStack_90)[iStack_28 * 6] = (&uStack_90)[iStack_28 * 6] & 0xfe3f | 0x1c0;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xfd | 2;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xe3;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0xdf | 0x20;
    *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) =
         *(byte *)((int)&uStack_90 + iStack_28 * 0xc + 1) & 0x3f;
    abStack_8e[iStack_28 * 0xc] = abStack_8e[iStack_28 * 0xc] & 0xfe;
    abStack_8e[iStack_28 * 0xc + 2] = 6;
    abStack_8e[iStack_28 * 0xc + 3] = 0;
    abStack_8e[iStack_28 * 0xc + 4] = 100;
    abStack_8e[iStack_28 * 0xc + 5] = 0x41;
    auStack_88[iStack_28 * 3] = 5;
    iStack_28 = iStack_28 + 1;
    EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,iStack_20,iStack_28,&uStack_90,auStack_f0,0,
                    pCGpffff86b4->aChr + iStack_20,0,0);
    IdelMotionReset__Fi(iStack_20);
  }
  EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,iStack_20,auStack_f0,0,0);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005dba20  CameraControlStatus__Fb
 * C++: CameraControlStatus(bool)
 * size: 0xf0 bytes
 * --------------------------------------------------------------------------- */
void CameraControlStatus__Fb(char param_1)

{
  if (param_1 == '\x01') {
    if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) << 0x3e) < 0) {
      *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) =
           *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) & 0xfb | 4;
    }
  }
  else if (-1 < (long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) << 0x3e)) {
    *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) =
         *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) & 0xfd | 2;
    *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) =
         *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) & 0xfb;
    CameraCutChange__Fv();
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005dbb10  BeginMagicEffectClear__Fi
 * C++: BeginMagicEffectClear(int)
 * size: 0x128 bytes
 * --------------------------------------------------------------------------- */
void BeginMagicEffectClear__Fi(int param_1)

{
  if (*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x558) != 0) {
    *(undefined4 *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x558) + 0x5a0) = 5;
  }
  *(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x558) = 0;
  if (*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x554) != 0) {
    (**(code **)(*(int *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x554) + 0x14) + 0x3c))();
  }
  *(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x554) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005dbc40  BeginMagicEffectClear2__Fi
 * C++: BeginMagicEffectClear2(int)
 * size: 0xb0 bytes
 * --------------------------------------------------------------------------- */
void BeginMagicEffectClear2__Fi(int param_1)

{
  int iVar1;
  
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4378); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x534)) {
    if (*(int *)(iVar1 + 0x5b4) == param_1) {
      *(undefined4 *)(iVar1 + 0x5a0) = 5;
    }
  }
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4370); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (*(int *)(iVar1 + 0x58) == param_1) {
      (**(code **)(*(int *)(iVar1 + 0x14) + 0x3c))();
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005dbcf0  MagicMotionEndSet__Fi
 * C++: MagicMotionEndSet(int)
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void MagicMotionEndSet__Fi(int param_1)

{
  SetNextBtlMotion__8BtlModelFif
            (0x3f800000,*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),0x29);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005dbd50  EffectDamageSet__Fisss7FVectorbiiiii
 * C++: EffectDamageSet(int, short, short, short, FVector, bool, int, int, int, int, int)
 * size: 0x5728 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005dd814) */

uint EffectDamageSet__Fisss7FVectorbiiiii
               (undefined8 param_1,short param_2,undefined2 param_3,undefined2 param_4,
               undefined8 param_5,ulong param_6,int param_7,int param_8,int param_9,int param_10)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  undefined4 in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  float *pfVar7;
  int def;
  long lVar8;
  ulong uVar9;
  ulong unaff_s4;
  long lVar10;
  uint element;
  float fVar11;
  int iVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [8];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  float fStack_178;
  float fStack_174;
  undefined1 auStack_170 [8];
  float fStack_168;
  float fStack_164;
  undefined1 auStack_160 [8];
  float fStack_158;
  float fStack_154;
  undefined1 auStack_150 [8];
  float fStack_148;
  float fStack_144;
  undefined1 auStack_140 [8];
  float fStack_138;
  float fStack_134;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  float fStack_108;
  float fStack_104;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [8];
  float fStack_d8;
  float fStack_d4;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  short asStack_a0 [2];
  short sStack_9c;
  byte bStack_62;
  undefined4 uStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  uint uStack_c;
  int iStack_8;
  char cStack_2;
  uchar uStack_1;
  
  iVar12 = 0;
  element = 6;
  uVar6 = 0xffffffff;
  bVar3 = false;
  if ((pCGpffff86b4->bNoEvade == 1) && (pCGpffff86b4->bBattleSub == 0xc)) {
    pCGpffff86b4->bBattleSub = 0xd;
    *(undefined4 *)&pCGpffff86b4->field_0x464c = 0;
  }
  uStack_40 = in_zero_lo;
  fStack_3c = in_zero_hi;
  uStack_38 = in_zero_udw;
  uStack_34 = in_register_0000000c;
  memset(asStack_a0,0,0x60);
  def = (int)param_1;
  if ((pCGpffff86b4->aChr[def].nHp < 1) &&
     ((long)((ulong)pCGpffff86b4->aChr[def].bFlagsB << 0x3c) < 0)) {
    uVar6 = 0xffffffff;
  }
  else if (param_9 == 0) {
    auVar16 = _lqc2(*(undefined1 (*) [16])pCGpffff86b4->aChr[def].aPos);
    auVar17 = _lqc2(*(undefined1 (*) [16])&pCGpffff86b4->aChr[def].field_0x2a0);
    auVar16 = _vadd(auVar16,auVar17);
    auStack_1b0 = _sqc2(auVar16);
    __ct__7FVectorFRC7FVector(auStack_b0,auStack_1b0);
    uStack_30 = auStack_b0._0_4_;
    uStack_2c = auStack_b0._4_4_;
    uStack_28 = uStack_a8;
    uStack_24 = uStack_a4;
    bStack_62 = bStack_62 & 0xfe | 1;
    EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
    uVar6 = 0xffffffff;
  }
  else {
    pfVar7 = (float *)param_5;
    fStack_18 = pfVar7[2];
    fStack_14 = pfVar7[3];
    uStack_20 = (undefined4)*(undefined8 *)pfVar7;
    uStack_1c = (undefined4)((ulong)*(undefined8 *)pfVar7 >> 0x20);
    Normalize__7FVectorFv(&uStack_20);
    __amu__7FVectorFf(*(undefined4 *)&pCGpffff86b4->aChr[def].field_0x300,&uStack_20);
    auVar16 = _lqc2(*(undefined1 (*) [16])pCGpffff86b4->aChr[def].aPos);
    auVar17 = _lqc2(*(undefined1 (*) [16])&pCGpffff86b4->aChr[def].field_0x2a0);
    auVar16 = _vadd(auVar16,auVar17);
    auStack_1d0 = _sqc2(auVar16);
    __ct__7FVectorFRC7FVector(auStack_d0,auStack_1d0);
    auVar17 = _lqc2(auStack_d0);
    auVar16._4_4_ = uStack_1c;
    auVar16._0_4_ = uStack_20;
    auVar16._8_4_ = fStack_18;
    auVar16._12_4_ = fStack_14;
    auVar16 = _lqc2(auVar16);
    auVar16 = _vadd(auVar17,auVar16);
    auStack_1c0 = _sqc2(auVar16);
    __ct__7FVectorFRC7FVector(auStack_c0,auStack_1c0);
    uStack_30 = auStack_c0._0_4_;
    uStack_2c = auStack_c0._4_4_;
    uStack_28 = uStack_b8;
    uStack_24 = uStack_b4;
    if (pCGpffff86b4->aChr[def].bState == 0x27) {
      if (pCGpffff86b4->aChr[def].bState2 == 0) {
        bStack_62 = bStack_62 & 0xfe | 1;
        EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        return 0xffffffff;
      }
      if ((long)((ulong)(byte)pCGpffff86b4->aChr[def].pModel[0x4b0] << 0x3d) < 0) {
        bStack_62 = bStack_62 & 0xfe | 1;
        EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        return 0xffffffff;
      }
      fVar11 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(pCGpffff86b4->aChr[def].pModel,0);
      if (fVar11 < 0.5) {
        bStack_62 = bStack_62 & 0xfe | 1;
        EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        return 0xffffffff;
      }
    }
    if ((pCGpffff86b4->aChr[def].bState == 0x29) || (pCGpffff86b4->aChr[def].bState == 0x2c)) {
      bStack_62 = bStack_62 & 0xfe | 1;
      EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
      uVar6 = 0xffffffff;
    }
    else if ((pCGpffff86b4->aChr[def].bState == 0x26) && (pCGpffff86b4->aChr[def].nHp < 1)) {
      bStack_62 = bStack_62 & 0xfe | 1;
      EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
      uVar6 = 0xffffffff;
    }
    else {
      if (param_8 == 2) {
        if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) {
          bStack_62 = bStack_62 & 0xfe | 1;
          EffectMesCall__7CBattleFiP8ECResultP7FVectorb
                    (pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
          return 0xffffffff;
        }
      }
      else if ((param_8 == 1) && (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3)) {
        bStack_62 = bStack_62 & 0xfe | 1;
        EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        return 0xffffffff;
      }
      fVar11 = GetJRingAreaResult__7CBattleFiPUcPc(pCGpffff86b4,-1,&uStack_1,&cStack_2);
      iVar13 = pCGpffff86b4->nCmdKind;
      if (iVar13 == 4) {
        iVar13 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
        iVar12 = (int)*(short *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 0x1c);
        element = *(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 4) & 7;
        unaff_s4 = ((ulong)*(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 5) & 0x7f) >> 6;
      }
      else if (iVar13 == 3) {
        iVar13 = GetRegDat__9RegDatApiFiii(0x36,0x17,0xffffffffffffffff);
        iVar12 = (int)*(short *)(iVar13 + pCGpffff86b4->nCmd0 * 0x20 + 0x1c);
        element = *(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x20 + 4) & 7;
        unaff_s4 = ((ulong)*(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x20 + 5) & 0x7f) >> 6;
      }
      else if (iVar13 == 2) {
        if ((*(byte *)((int)pCGpffff86b4 +
                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xb1) & 1)
            == 0) {
          unaff_s4 = (ulong)*(short *)((int)pCGpffff86b4 +
                                      (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) *
                                      0x10 + 0x120);
        }
        else {
          switch(*(undefined2 *)
                  ((int)pCGpffff86b4 +
                  (pCGpffff86b4->cActor * 0x50 - (int)pCGpffff86b4->cActor) * 0x10 + 0xba)) {
          case 0:
          case 1:
            unaff_s4 = 0xc;
            break;
          case 2:
          case 3:
            unaff_s4 = 0xd;
            break;
          case 4:
          case 5:
            unaff_s4 = 0xe;
            break;
          case 6:
          case 7:
            unaff_s4 = 0xf;
            break;
          case 8:
          case 9:
            unaff_s4 = 0x10;
            break;
          case 10:
          case 0xb:
            unaff_s4 = 0x11;
            break;
          case 0xc:
          case 0xd:
            unaff_s4 = 0x12;
            break;
          case 0xe:
            unaff_s4 = 0x13;
            break;
          case 0xf:
            unaff_s4 = 0x14;
            break;
          case 0x10:
            unaff_s4 = 0x15;
          }
        }
        iVar13 = GetRegDat__9RegDatApiFiii(0x36,unaff_s4,0xffffffffffffffff);
        iVar12 = (int)*(short *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 0x1c);
        element = *(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 4) & 7;
        unaff_s4 = ((ulong)*(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x40 + 5) & 0x7f) >> 6;
      }
      else if (iVar13 == 1) {
        iVar13 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
        iVar12 = 0;
        element = *(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x30 + 4) & 7;
        unaff_s4 = ((ulong)*(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x30 + 5) & 0x7f) >> 6;
      }
      else if (iVar13 == 0) {
        iVar13 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
        iVar12 = (int)*(short *)(iVar13 + pCGpffff86b4->nCmd0 * 0x44 + 0x1c);
        element = *(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x44 + 4) & 7;
        unaff_s4 = ((ulong)*(byte *)(iVar13 + pCGpffff86b4->nCmd0 * 0x44 + 5) & 0x7f) >> 6;
      }
      if (unaff_s4 == 0) {
        fVar11 = GetSkillPAtkDamage__7CBattleFiiPiPiififPf
                           (pCGpffff86b4,(int)pCGpffff86b4->cActor,def,&iStack_8,&uStack_c,iVar12,
                            fVar11,element,(float)param_7 / 100.0,&fStack_10);
      }
      else {
        fVar11 = GetSAtkDamage__7CBattleFiiPiPiififPf
                           (pCGpffff86b4,(int)pCGpffff86b4->cActor,def,&iStack_8,&uStack_c,iVar12,
                            fVar11,element,(float)param_7 / 100.0,&fStack_10);
      }
      fVar15 = 1.0;
      if (iStack_8 == 4) {
        fVar15 = 0.0;
      }
      else if (iStack_8 == 3) {
        fVar15 = 0.5;
      }
      else if (iStack_8 == 2) {
        fVar15 = 0.5;
      }
      else if (iStack_8 == 1) {
        fVar15 = 0.25;
      }
      iVar12 = (int)((*(float *)&pCGpffff86b4->aChr[def].field_0x47c + fVar11 * fVar15) -
                    (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478);
      lVar10 = (long)iVar12;
      iVar13 = (int)((*(float *)&pCGpffff86b4->aChr[def].field_0x480 + fStack_10 * fVar15) -
                    (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a);
      lVar8 = (long)iVar13;
      fVar14 = fVar11 * fVar15;
      if (fVar15 != 0.0) {
        if ((0.0 < fVar11) && (lVar10 == 0)) {
          lVar10 = (long)(iVar12 + 1);
        }
        if ((fVar11 < 0.0) && (lVar10 == 0)) {
          lVar10 = -1;
        }
        if ((0.0 < fStack_10) && (lVar8 == 0)) {
          lVar8 = (long)(iVar13 + 1);
        }
        if ((fStack_10 < 0.0) && (lVar8 == 0)) {
          lVar8 = -1;
        }
      }
      if ((((-1 < (long)((ulong)(byte)pCGpffff86b4->aChr[def].field_0x454 << 0x3c)) && (lVar10 != 0)
           ) && (lVar10 == lVar8)) && (pCGpffff86b4->nComboCnt != 0)) {
        if (lVar10 < 1) {
          if (lVar10 < 0) {
            lVar10 = (long)((int)lVar10 + -1);
            fVar14 = fVar14 - 1.0;
          }
        }
        else {
          lVar10 = (long)((int)lVar10 + 1);
          fVar14 = fVar14 + 1.0;
        }
      }
      if ((iStack_8 == 0) || (pCGpffff86b4->aChr[def].nHp <= lVar10)) {
        pCGpffff86b4->bFlags25 = pCGpffff86b4->bFlags25 & 0xf7 | 8;
        if (param_6 != 0) {
          pCGpffff86b4->bFlags25 = pCGpffff86b4->bFlags25 & 0xef | 0x10;
        }
        uVar6 = (uint)(uStack_1 == '\x03');
        if (pCGpffff86b4->aChr[def].wVulnCount == 0) {
          pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xef;
          pCGpffff86b4->aChr[def].flVulnA = 0.0;
          pCGpffff86b4->aChr[def].flVulnB = 0.0;
          *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x470 = 0;
          *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x474 = 0;
          *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x478 = 0;
          *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x47a = 0;
          *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x47c = 0;
          *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x480 = 0;
          if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 != 0) {
            pCGpffff86b4->aChr[def].flVulnB = 0.1;
          }
        }
        else if (pCGpffff86b4->aChr[def].nVulnTurn != pCGpffff86b4->nTurnNo) {
          pCGpffff86b4->aChr[def].flVulnA =
               ((float)pCGpffff86b4->aChr[def].wVulnCount * 2.0) / 100.0;
          pCGpffff86b4->aChr[def].flVulnB = 0.0;
          if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 != 0) {
            pCGpffff86b4->aChr[def].flVulnB = 0.1;
          }
        }
        pCGpffff86b4->aChr[def].wVulnCount = pCGpffff86b4->aChr[def].wVulnCount + 1;
        iVar12 = (int)((*(float *)&pCGpffff86b4->aChr[def].field_0x47c + fVar11) -
                      (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478);
        lVar10 = (long)iVar12;
        iVar13 = (int)((*(float *)&pCGpffff86b4->aChr[def].field_0x480 + fStack_10) -
                      (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a);
        lVar8 = (long)iVar13;
        if ((0.0 < fVar11) && (lVar10 == 0)) {
          lVar10 = (long)(iVar12 + 1);
        }
        if ((fVar11 < 0.0) && (lVar10 == 0)) {
          lVar10 = -1;
        }
        if ((0.0 < fStack_10) && (lVar8 == 0)) {
          lVar8 = (long)(iVar13 + 1);
        }
        if ((fStack_10 < 0.0) && (lVar8 == 0)) {
          lVar8 = -1;
        }
        if ((((-1 < (long)((ulong)(byte)pCGpffff86b4->aChr[def].field_0x454 << 0x3c)) &&
             (lVar10 != 0)) && (lVar10 == lVar8)) && (pCGpffff86b4->nComboCnt != 0)) {
          if (lVar10 < 1) {
            if (lVar10 < 0) {
              lVar10 = (long)((int)lVar10 + -1);
              fVar11 = fVar11 - 1.0;
            }
          }
          else {
            lVar10 = (long)((int)lVar10 + 1);
            fVar11 = fVar11 + 1.0;
          }
        }
        sVar1 = pCGpffff86b4->aChr[def].nHp;
        bVar2 = false;
        if (((0 < pCGpffff86b4->aChr[def].nHp) && (pCGpffff86b4->aChr[def].nHp <= lVar10)) &&
           (-1 < (long)((ulong)pCGpffff86b4->aChr[def].bFlagsA2 << 0x3e))) {
          pCGpffff86b4->aChr[def].bFlagsA2 = pCGpffff86b4->aChr[def].bFlagsA2 & 0xfd | 2;
          DeadReset__7CBattleFi(pCGpffff86b4,param_1);
          bVar2 = true;
        }
        asStack_a0[0] = (short)lVar10;
        pCGpffff86b4->aChr[def].nHp = pCGpffff86b4->aChr[def].nHp - asStack_a0[0];
        if (pCGpffff86b4->aChr[def].nHp < 0) {
          pCGpffff86b4->aChr[def].nHp = 0;
        }
        if ((long)(ulong)pCGpffff86b4->aChr[def].wMaxHP < (long)pCGpffff86b4->aChr[def].nHp) {
          pCGpffff86b4->aChr[def].nHp = pCGpffff86b4->aChr[def].wMaxHP;
        }
        *(int *)&pCGpffff86b4->aChr[def].field_0x470 =
             *(int *)&pCGpffff86b4->aChr[def].field_0x470 + (int)lVar10;
        *(int *)&pCGpffff86b4->aChr[def].field_0x474 =
             *(int *)&pCGpffff86b4->aChr[def].field_0x474 + ((int)lVar10 - (int)lVar8);
        *(short *)&pCGpffff86b4->aChr[def].field_0x478 =
             *(short *)&pCGpffff86b4->aChr[def].field_0x478 + asStack_a0[0];
        *(short *)&pCGpffff86b4->aChr[def].field_0x47a =
             *(short *)&pCGpffff86b4->aChr[def].field_0x47a + (short)lVar8;
        *(float *)&pCGpffff86b4->aChr[def].field_0x47c =
             *(float *)&pCGpffff86b4->aChr[def].field_0x47c + fVar11;
        *(float *)&pCGpffff86b4->aChr[def].field_0x480 =
             *(float *)&pCGpffff86b4->aChr[def].field_0x480 + fStack_10;
        *(short *)&pCGpffff86b4->aChr[def].field_0x462 = asStack_a0[0];
        if (*(float *)&pCGpffff86b4->aChr[def].field_0x47c <
            (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478) {
          *(float *)&pCGpffff86b4->aChr[def].field_0x47c =
               (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478;
        }
        if (*(float *)&pCGpffff86b4->aChr[def].field_0x480 <
            (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a) {
          *(float *)&pCGpffff86b4->aChr[def].field_0x480 =
               (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a;
        }
        pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xf7 | 8;
        asStack_a0[0] = -asStack_a0[0];
        if (bVar2) {
          bStack_62 = bStack_62 & 0xf7 | 8;
        }
        if (param_10 == 1) {
          StatusRecovery__7CBattleFiP8ECResultP7FVector(pCGpffff86b4,param_1,asStack_a0,&uStack_30);
        }
        else {
          EffectMesCall__7CBattleFiP8ECResultP7FVectorb
                    (pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        }
        if (((0 < sVar1) && (pCGpffff86b4->aChr[def].nHp < 1)) &&
           ((pCGpffff86b4->aChr[def].bFlagsB & 1) == 0)) {
          iVar12 = ourBtlSaveDat + pCGpffff86b4->aChr[def].nCharId * 0x24;
          *(int *)(iVar12 + 0x1190) = *(int *)(iVar12 + 0x1190) + 1;
        }
        if ((pCGpffff86b4->aChr[def].bFlagsB & 1) == 0) {
          if ((pCGpffff86b4->aChr[def].bFlagsA1 & 1) == 0) {
            uVar9 = (ulong)(*(byte *)(ourBtlSaveDat + pCGpffff86b4->aChr[def].nSubId * 0xc0 + 0x44) >>
                           5);
          }
          else {
            uVar9 = ((ulong)(byte)pCGpffff86b4->aChr[def].pParam[4] & 0x3f) >> 3;
          }
        }
        else {
          uVar9 = ((ulong)(byte)pCGpffff86b4->aChr[def].pParam[0x14] & 0x3f) >> 3;
        }
        for (iVar12 = 0; iVar12 < 0x20; iVar12 = iVar12 + 1) {
          if (((pCGpffff86b4->aChr[def].aStatus[iVar12].bKind == 0x47) &&
              (((ulong)pCGpffff86b4->aChr[def].aStatus[iVar12].bFlags & 0x1f) >> 2 == 0)) &&
             ((pCGpffff86b4->aChr[def].aStatus[iVar12].nValue & 0x20U) != 0)) {
            bVar3 = true;
          }
        }
        if (bVar3) {
          if (pCGpffff86b4->aChr[def].bState == 0x24) {
            if (0 < pCGpffff86b4->aChr[def].nHp) {
              puVar5 = &pCGpffff86b4->aChr[def].field_0x454;
              *puVar5 = *puVar5 & 0xf8;
              pCGpffff86b4->aChr[def].nVulnTurn = pCGpffff86b4->nTurnNo;
              pCGpffff86b4->aChr[def].field_0x455 = pCGpffff86b4->cActor;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x456 = 0xffff;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45c = param_3;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45e = param_4;
              if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                 (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
                pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfd | 2
                ;
              }
              if ((pCGpffff86b4->wTurnPendMask != 0) && ((param_6 & 0xff) == 1)) {
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xdf;
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xbf | 0x40;
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0x7f;
                *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x100 = 0x3f088889;
              }
              BtlEffAllEndSet__7CBattleFi(pCGpffff86b4,param_1);
              return uVar6;
            }
          }
          else if (pCGpffff86b4->aChr[def].bState == 0x25) {
            if (0 < pCGpffff86b4->aChr[def].nHp) {
              puVar5 = &pCGpffff86b4->aChr[def].field_0x454;
              *puVar5 = *puVar5 & 0xf8;
              pCGpffff86b4->aChr[def].nVulnTurn = pCGpffff86b4->nTurnNo;
              pCGpffff86b4->aChr[def].field_0x455 = pCGpffff86b4->cActor;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x456 = 0xffff;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45c = param_3;
              *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45e = param_4;
              if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                 (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
                pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfd | 2
                ;
              }
              if ((pCGpffff86b4->wTurnPendMask != 0) && ((param_6 & 0xff) == 1)) {
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xdf;
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xbf | 0x40;
                pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0x7f;
                *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x100 = 0x3f088889;
              }
              BtlEffAllEndSet__7CBattleFi(pCGpffff86b4,param_1);
              return uVar6;
            }
          }
          else if ((0 < pCGpffff86b4->aChr[def].nHp) &&
                  (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0)) {
            pCGpffff86b4->aChr[def].bState = 0x24;
            puVar5 = &pCGpffff86b4->aChr[def].field_0x454;
            *puVar5 = *puVar5 & 0xf8;
            pCGpffff86b4->aChr[def].nVulnTurn = pCGpffff86b4->nTurnNo;
            pCGpffff86b4->aChr[def].field_0x455 = pCGpffff86b4->cActor;
            *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x456 = 0xffff;
            *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45c = param_3;
            *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45e = param_4;
            if (((uVar9 == 3) || ((uVar9 == 4 || (uVar9 == 5)))) &&
               (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfd | 2;
            }
            pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xbf;
            pCGpffff86b4->aChr[def].bState2 = 0;
            __ct__7FVectorFPC7FVector(auStack_110,pCGpffff86b4->aChr[def].pModel + 0x4c0);
            pCGpffff86b4->aChr[def].aPos[0] = auStack_110._0_4_;
            pCGpffff86b4->aChr[def].aPos[1] = auStack_110._4_4_;
            pCGpffff86b4->aChr[def].aPos[2] = fStack_108;
            pCGpffff86b4->aChr[def].aPos[3] = fStack_104;
            if (0.0 < pCGpffff86b4->aChr[def].aPos[1]) {
              pCGpffff86b4->aChr[def].aPos[1] = 0.0;
            }
            *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc0 = 0;
            *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc8 = 0;
            if (((*pfVar7 != 0.0) || (pfVar7[1] != 0.0)) || (pfVar7[2] != 0.0)) {
              uVar4 = __ct__7FVectorFRC7FVector(auStack_130,param_5);
              Get3DAngle__F7FVector(auStack_120,uVar4);
              uStack_40 = auStack_120._0_4_;
              fStack_3c = auStack_120._4_4_;
              uStack_38 = uStack_118;
              uStack_34 = uStack_114;
              ChangeBtlChrAngle__7CBattleFif(-fStack_3c,pCGpffff86b4,param_1);
            }
            pCGpffff86b4->aChr[def].bFlagsB1 = pCGpffff86b4->aChr[def].bFlagsB1 & 0xf7;
            if ((pCGpffff86b4->wTurnPendMask != 0) && ((param_6 & 0xff) == 1)) {
              pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xdf;
              pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xbf | 0x40;
              pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0x7f;
              *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x100 = 0x3f088889;
            }
            BtlEffAllEndSet__7CBattleFi(pCGpffff86b4,param_1);
            return uVar6;
          }
        }
        if ((pCGpffff86b4->aChr[def].bState == 0x24) || (pCGpffff86b4->aChr[def].bState == 0x25)) {
          lVar8 = __nw__FUi(0x84);
          if (lVar8 != 0) {
            __ct__9BreakBBoxFiii(lVar8,0,param_1,0);
          }
          ClutCtrl__8BtlModelFffff(0,0,0,0,pCGpffff86b4->aChr[def].pModel);
        }
        IdelMotionReset__Fi(param_1);
        puVar5 = &pCGpffff86b4->aChr[def].field_0x454;
        *puVar5 = *puVar5 & 0xf8;
        pCGpffff86b4->aChr[def].nVulnTurn = pCGpffff86b4->nTurnNo;
        pCGpffff86b4->aChr[def].field_0x455 = pCGpffff86b4->cActor;
        *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x456 = 0xffff;
        *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45c = param_3;
        *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45e = param_4;
        switch(param_2) {
        default:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x16;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) &&
                  (((pCGpffff86b4->aChr[def].bFlagsB & 1) != 0 || (0 < pCGpffff86b4->aChr[def].nHp))
                  )) {
            pCGpffff86b4->aChr[def].bState = 0x16;
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          break;
        case 1:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) &&
                  (((pCGpffff86b4->aChr[def].bFlagsB & 1) != 0 || (0 < pCGpffff86b4->aChr[def].nHp))
                  )) {
            if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
               (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].bState = 0x16;
              pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfb | 4;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x18;
            }
          }
          else if (((uVar9 == 3) || ((uVar9 == 4 || (uVar9 == 5)))) &&
                  (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1c;
          }
          break;
        case 2:
          __ct__7FVectorFPC7FVector(auStack_140,pCGpffff86b4->aChr[def].pModel + 0x4c0);
          pCGpffff86b4->aChr[def].aPos[0] = auStack_140._0_4_;
          pCGpffff86b4->aChr[def].aPos[1] = auStack_140._4_4_;
          pCGpffff86b4->aChr[def].aPos[2] = fStack_138;
          pCGpffff86b4->aChr[def].aPos[3] = fStack_134;
          pCGpffff86b4->aChr[def].aPos[1] = 0.0;
          SetPos__8BtlModelFP7FVector(pCGpffff86b4->aChr[def].pModel,pCGpffff86b4->aChr[def].aPos);
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9;
            if ((pCGpffff86b4->aChr[def].nHp < 1) && ((param_6 & 0xff) == 1)) {
              pCGpffff86b4->aChr[def].bState = 0x17;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x19;
            }
          }
          else if ((pCGpffff86b4->aChr[def].nHp < 1) && ((param_6 & 0xff) == 1)) {
            pCGpffff86b4->aChr[def].bState = 0x1b;
          }
          else {
            if (pCGpffff86b4->aChr[def].aPos[1] == 0.0) {
              pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9;
            }
            else {
              pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9 | 2;
            }
            pCGpffff86b4->aChr[def].bState = 0x19;
          }
          break;
        case 3:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) {
            if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
               (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].bState = 0x16;
              pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfb | 4;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x1b;
              if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
                 (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
                *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                     *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
              }
            }
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          break;
        case 4:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) {
            if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
               (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].bState = 0x16;
              pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfb | 4;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x1c;
            }
          }
          else if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                  (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1c;
          }
          break;
        case 5:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 < 2) {
            if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) {
              if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                 (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
                pCGpffff86b4->aChr[def].bState = 0x16;
                pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfb | 4
                ;
              }
              else {
                pCGpffff86b4->aChr[def].bState = 0x1d;
              }
            }
            else if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                    (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].bState = 0x1b;
              if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
                 (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
                *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                     *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
              }
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x1d;
            }
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          break;
        case 6:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) {
            if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
               (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
              pCGpffff86b4->aChr[def].bState = 0x16;
              pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfb | 4;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x1e;
            }
          }
          else if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
                  (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1e;
          }
          break;
        case 7:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x17;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 3) {
            pCGpffff86b4->aChr[def].bState = 0x22;
          }
          else if (((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) {
            pCGpffff86b4->aChr[def].bState = 0x23;
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          break;
        case 8:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            __ct__7FVectorFPC7FVector(auStack_150,pCGpffff86b4->aChr[def].pModel + 0x4c0);
            pCGpffff86b4->aChr[def].aPos[0] = auStack_150._0_4_;
            pCGpffff86b4->aChr[def].aPos[1] = auStack_150._4_4_;
            pCGpffff86b4->aChr[def].aPos[2] = fStack_148;
            pCGpffff86b4->aChr[def].aPos[3] = fStack_144;
            pCGpffff86b4->aChr[def].aPos[1] = 0.0;
            SetPos__8BtlModelFP7FVector(pCGpffff86b4->aChr[def].pModel,pCGpffff86b4->aChr[def].aPos);
            pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9;
            if ((pCGpffff86b4->aChr[def].nHp < 1) && ((param_6 & 0xff) == 1)) {
              pCGpffff86b4->aChr[def].bState = 0x17;
            }
            else {
              pCGpffff86b4->aChr[def].bState = 0x1a;
            }
          }
          else {
            __ct__7FVectorFPC7FVector(auStack_160,pCGpffff86b4->aChr[def].pModel + 0x4c0);
            pCGpffff86b4->aChr[def].aPos[0] = auStack_160._0_4_;
            pCGpffff86b4->aChr[def].aPos[1] = auStack_160._4_4_;
            pCGpffff86b4->aChr[def].aPos[2] = fStack_158;
            pCGpffff86b4->aChr[def].aPos[3] = fStack_154;
            if (0.0 < pCGpffff86b4->aChr[def].aPos[1]) {
              pCGpffff86b4->aChr[def].aPos[1] = 0.0;
            }
            SetPos__8BtlModelFP7FVector(pCGpffff86b4->aChr[def].pModel,pCGpffff86b4->aChr[def].aPos);
            if ((pCGpffff86b4->aChr[def].nHp < 1) && ((param_6 & 0xff) == 1)) {
              pCGpffff86b4->aChr[def].bState = 0x1b;
            }
            else {
              if (pCGpffff86b4->aChr[def].aPos[1] < 0.0) {
                pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9 | 2;
              }
              else {
                pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9;
              }
              pCGpffff86b4->aChr[def].bState = 0x1a;
            }
          }
          break;
        case 9:
          if (*(short *)&pCGpffff86b4->aChr[def].field_0xdc == 499) {
            pCGpffff86b4->aChr[def].bState = 0x16;
          }
          else if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 0) &&
                  (((pCGpffff86b4->aChr[def].bFlagsB & 1) != 0 || (0 < pCGpffff86b4->aChr[def].nHp))
                  )) {
            pCGpffff86b4->aChr[def].bState = 0x16;
          }
          else {
            pCGpffff86b4->aChr[def].bState = 0x1b;
            if ((((ulong)pCGpffff86b4->aChr[def].bFlagsB & 7) >> 1 == 1) &&
               (10 < *(short *)&pCGpffff86b4->aChr[def].field_0x45c)) {
              *(short *)&pCGpffff86b4->aChr[def].field_0x45c =
                   *(short *)&pCGpffff86b4->aChr[def].field_0x45c + -10;
            }
          }
          break;
        case 10:
          __ct__7FVectorFPC7FVector(auStack_170,pCGpffff86b4->aChr[def].pModel + 0x4c0);
          pCGpffff86b4->aChr[def].aPos[0] = auStack_170._0_4_;
          pCGpffff86b4->aChr[def].aPos[1] = auStack_170._4_4_;
          pCGpffff86b4->aChr[def].aPos[2] = fStack_168;
          pCGpffff86b4->aChr[def].aPos[3] = fStack_164;
          pCGpffff86b4->aChr[def].aPos[1] = 0.0;
          SetPos__8BtlModelFP7FVector(pCGpffff86b4->aChr[def].pModel,pCGpffff86b4->aChr[def].aPos);
          pCGpffff86b4->aChr[def].bState = 0x16;
          pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xf9;
        }
        if ((((uVar9 == 3) || (uVar9 == 4)) || (uVar9 == 5)) &&
           (((ulong)(byte)pCGpffff86b4->field_0x4336 & 7) >> 1 != 3)) {
          pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xfd | 2;
        }
        pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xbf;
        pCGpffff86b4->aChr[def].bState2 = 0;
        __ct__7FVectorFPC7FVector(auStack_180,pCGpffff86b4->aChr[def].pModel + 0x4c0);
        pCGpffff86b4->aChr[def].aPos[0] = auStack_180._0_4_;
        pCGpffff86b4->aChr[def].aPos[1] = auStack_180._4_4_;
        pCGpffff86b4->aChr[def].aPos[2] = fStack_178;
        pCGpffff86b4->aChr[def].aPos[3] = fStack_174;
        if (0.0 < pCGpffff86b4->aChr[def].aPos[1]) {
          pCGpffff86b4->aChr[def].aPos[1] = 0.0;
        }
        *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc0 = 0;
        *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc8 = 0;
        if (((*pfVar7 != 0.0) || (pfVar7[1] != 0.0)) || (pfVar7[2] != 0.0)) {
          uVar4 = __ct__7FVectorFRC7FVector(auStack_1a0,param_5);
          Get3DAngle__F7FVector(auStack_190,uVar4);
          uStack_40 = auStack_190._0_4_;
          fStack_3c = auStack_190._4_4_;
          uStack_38 = uStack_188;
          uStack_34 = uStack_184;
          ChangeBtlChrAngle__7CBattleFif(-fStack_3c,pCGpffff86b4,param_1);
        }
        pCGpffff86b4->aChr[def].bFlagsB1 = pCGpffff86b4->aChr[def].bFlagsB1 & 0xf7;
        if (pCGpffff86b4->aChr[def].nHp < 1) {
          if (((param_6 & 0xff) == 1) || (param_2 == 9)) {
            pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xdf;
            pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xbf;
            pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0x7f;
            *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x100 = 0;
            iVar12 = GetRegDat__9RegDatApiFiii(0x2e,0,0xffffffffffffffff);
            if (((pCGpffff86b4->aChr[def].bFlagsB & 1) == 0) ||
               (((long)((ulong)pCGpffff86b4->aChr[def].bFlagsB << 0x3c) < 0 ||
                (((ulong)*(byte *)(iVar12 + pCGpffff86b4->aChr[def].nSubId * 0x38 + 0x15) & 0x1f) >>
                 3 != 0)))) {
              if (pCGpffff86b4->aChr[def].bState == 0x16) {
                pCGpffff86b4->aChr[def].bState = 0x23;
              }
            }
            else {
              DeathInit__7CBattleFi(pCGpffff86b4,def);
            }
            if ((param_6 & 0xff) == 0) {
              pCGpffff86b4->bFlags25 = pCGpffff86b4->bFlags25 & 0xef | 0x10;
            }
          }
        }
        else if ((pCGpffff86b4->wTurnPendMask != 0) && ((param_6 & 0xff) == 1)) {
          pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xdf;
          pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0xbf | 0x40;
          pCGpffff86b4->aChr[def].bFlagsA = pCGpffff86b4->aChr[def].bFlagsA & 0x7f;
          *(undefined4 *)&pCGpffff86b4->aChr[def].field_0x100 = 0x3f088889;
        }
      }
      else {
        sVar1 = (short)lVar10;
        asStack_a0[0] = -sVar1;
        *(int *)&pCGpffff86b4->aChr[def].field_0x470 =
             *(int *)&pCGpffff86b4->aChr[def].field_0x470 + (int)lVar10;
        *(int *)&pCGpffff86b4->aChr[def].field_0x474 =
             *(int *)&pCGpffff86b4->aChr[def].field_0x474 + ((int)lVar10 - (int)lVar8);
        *(short *)&pCGpffff86b4->aChr[def].field_0x478 =
             *(short *)&pCGpffff86b4->aChr[def].field_0x478 + sVar1;
        *(short *)&pCGpffff86b4->aChr[def].field_0x47a =
             *(short *)&pCGpffff86b4->aChr[def].field_0x47a + (short)lVar8;
        *(float *)&pCGpffff86b4->aChr[def].field_0x47c =
             *(float *)&pCGpffff86b4->aChr[def].field_0x47c + fVar14;
        *(float *)&pCGpffff86b4->aChr[def].field_0x480 =
             *(float *)&pCGpffff86b4->aChr[def].field_0x480 + fStack_10 * fVar15;
        *(short *)&pCGpffff86b4->aChr[def].field_0x462 = sVar1;
        if (*(float *)&pCGpffff86b4->aChr[def].field_0x47c <
            (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478) {
          *(float *)&pCGpffff86b4->aChr[def].field_0x47c =
               (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x478;
        }
        if (*(float *)&pCGpffff86b4->aChr[def].field_0x480 <
            (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a) {
          *(float *)&pCGpffff86b4->aChr[def].field_0x480 =
               (float)(int)*(short *)&pCGpffff86b4->aChr[def].field_0x47a;
        }
        if (((((iStack_8 == 2) && ((pCGpffff86b4->aChr[def].bFlagsB & 1) == 0)) &&
             (-1 < (long)((ulong)pCGpffff86b4->aChr[def].bFlagsB1 << 0x3a))) &&
            ((pCGpffff86b4->aChr[def].nCharId != 8 && (pCGpffff86b4->aChr[def].nCharId != 9)))) &&
           (pCGpffff86b4->aChr[def].nCharId != 10)) {
          pCGpffff86b4->aChr[def].nSp = pCGpffff86b4->aChr[def].nSp + -1;
          sStack_9c = sStack_9c + -1;
          if (pCGpffff86b4->aChr[def].nSp < -99) {
            pCGpffff86b4->aChr[def].nSp = -99;
          }
        }
        EffectMesCall__7CBattleFiP8ECResultP7FVectorb(pCGpffff86b4,param_1,asStack_a0,&uStack_30,1);
        pCGpffff86b4->aChr[def].nHp = pCGpffff86b4->aChr[def].nHp - sVar1;
        if (pCGpffff86b4->aChr[def].nHp < 0) {
          pCGpffff86b4->aChr[def].nHp = 0;
        }
        if ((long)(ulong)pCGpffff86b4->aChr[def].wMaxHP < (long)pCGpffff86b4->aChr[def].nHp) {
          pCGpffff86b4->aChr[def].nHp = pCGpffff86b4->aChr[def].wMaxHP;
        }
        pCGpffff86b4->aChr[def].field_0x454 = pCGpffff86b4->aChr[def].field_0x454 & 0xf7 | 8;
        IdelMotionReset__Fi(param_1);
        pCGpffff86b4->aChr[def].bFlagsB = pCGpffff86b4->aChr[def].bFlagsB & 0xbf;
        pCGpffff86b4->aChr[def].bState2 = 0;
        MaxHitFunc__7CBattleFi(pCGpffff86b4,param_1);
        pCGpffff86b4->aChr[def].wVulnCount = 0;
        pCGpffff86b4->aChr[def].flVulnA = 0.0;
        pCGpffff86b4->aChr[def].flVulnB = 0.0;
        *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45c = param_3;
        *(undefined2 *)&pCGpffff86b4->aChr[def].field_0x45e = param_4;
        __ct__7FVectorFPC7FVector(auStack_e0,pCGpffff86b4->aChr[def].pModel + 0x4c0);
        pCGpffff86b4->aChr[def].aPos[0] = auStack_e0._0_4_;
        pCGpffff86b4->aChr[def].aPos[1] = auStack_e0._4_4_;
        pCGpffff86b4->aChr[def].aPos[2] = fStack_d8;
        pCGpffff86b4->aChr[def].aPos[3] = fStack_d4;
        if (0.0 < pCGpffff86b4->aChr[def].aPos[1]) {
          pCGpffff86b4->aChr[def].aPos[1] = 0.0;
        }
        *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc0 = 0;
        *(undefined4 *)&pCGpffff86b4->aChr[def].field_0xc8 = 0;
        if (((*pfVar7 != 0.0) || (pfVar7[1] != 0.0)) || (pfVar7[2] != 0.0)) {
          uVar4 = __ct__7FVectorFRC7FVector(auStack_100,param_5);
          Get3DAngle__F7FVector(auStack_f0,uVar4);
          uStack_40 = auStack_f0._0_4_;
          fStack_3c = auStack_f0._4_4_;
          uStack_38 = uStack_e8;
          uStack_34 = uStack_e4;
          ChangeBtlChrAngle__7CBattleFif(-fStack_3c,pCGpffff86b4,param_1);
        }
        if (iStack_8 == 4) {
          uVar6 = 5;
          pCGpffff86b4->aChr[def].bState = 0x10;
        }
        else if (iStack_8 == 3) {
          uVar6 = 5;
          pCGpffff86b4->aChr[def].bState = 0x12;
        }
        else if (iStack_8 == 2) {
          uVar6 = 5;
          pCGpffff86b4->aChr[def].bState = 0x10;
        }
        else if (iStack_8 == 1) {
          uVar6 = 4;
          pCGpffff86b4->aChr[def].bState = 0xf;
        }
      }
      BtlEffAllEndSet__7CBattleFi(pCGpffff86b4,param_1);
    }
  }
  return uVar6;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e1480  GetBattleBgModel__Fv
 * C++: GetBattleBgModel()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
undefined4 GetBattleBgModel__Fv(void)

{
  return *(undefined4 *)(iGpffff86b4 + 0x3f20);
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e1490  ChangeFusionModel__Fv
 * C++: ChangeFusionModel()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
undefined4 ChangeFusionModel__Fv(void)

{
  undefined4 uVar1;
  
  if ((*(short *)(iGpffff86b4 + 0x28) == 9) && (*(short *)(iGpffff86b4 + 0x2a) == 4)) {
    *(undefined4 *)(iGpffff86b4 + 0x4c) = 1;
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e14f0  ComboStopOff__Fi
 * C++: ComboStopOff(int)
 * size: 0x484 bytes
 * --------------------------------------------------------------------------- */
void ComboStopOff__Fi(int param_1)

{
  int iVar1;
  int iVar2;
  long lVar3;
  
  if (param_1 < 0) {
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d))) {
        iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
        *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0xdf;
        iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
        *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0xbf;
        iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
        *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0x7f;
        *(undefined4 *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x1b0) = 0;
      }
    }
  }
  else {
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb0) = *(byte *)(iVar1 + 0xb0) & 0xdf;
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb0) = *(byte *)(iVar1 + 0xb0) & 0xbf;
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb0) = *(byte *)(iVar1 + 0xb0) & 0x7f;
    *(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x1b0) = 0;
    for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d))) {
        lVar3 = 0;
        while ((lVar3 < *(short *)(iGpffff86b4 + 0x3c32) &&
               (*(int *)(iGpffff86b4 + (int)lVar3 * 0x14 + 0x3d24) != iVar1))) {
          lVar3 = (long)((int)lVar3 + 1);
        }
        if (*(short *)(iGpffff86b4 + 0x3c32) <= lVar3) {
          iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
          *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0xdf;
          iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
          *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0xbf;
          iVar2 = iGpffff86b4 + iVar1 * 0x4f0;
          *(byte *)(iVar2 + 0xb0) = *(byte *)(iVar2 + 0xb0) & 0x7f;
          *(undefined4 *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x1b0) = 0;
        }
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e1980  GetFusionCharactor__FPiPi
 * C++: GetFusionCharactor(int *, int *)
 * size: 0x228 bytes
 * --------------------------------------------------------------------------- */
void GetFusionCharactor__FPiPi(int *param_1,int *param_2)

{
  if (*(short *)(iGpffff86b4 + 0x28) == 9) {
    if ((*(byte *)(iGpffff86b4 + *(int *)(iGpffff86b4 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) {
      if (*(short *)(iGpffff86b4 + *(int *)(iGpffff86b4 + 0x48) * 0x4f0 + 0x120) == 0) {
        *param_1 = 0;
      }
      else {
        *param_1 = 1;
      }
    }
    else {
      *param_1 = *(short *)(iGpffff86b4 + *(int *)(iGpffff86b4 + 0x48) * 0x4f0 + 0xba) + 2;
    }
    if ((*(byte *)(iGpffff86b4 +
                   (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                   0x10 + 0xb1) & 1) == 0) {
      if (*(short *)(iGpffff86b4 +
                     (*(char *)(iGpffff86b4 + 0x2c) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x2c)) *
                     0x10 + 0x120) == 0) {
        *param_2 = 0;
      }
      else {
        *param_2 = 1;
      }
    }
    else {
      *param_2 = *(short *)(iGpffff86b4 +
                            (*(char *)(iGpffff86b4 + 0x2c) * 0x50 -
                            (int)*(char *)(iGpffff86b4 + 0x2c)) * 0x10 + 0xba) + 2;
    }
  }
  else {
    *param_1 = -1;
    *param_2 = -1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e1bb0  CameraCutChange__Fv
 * C++: CameraCutChange()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void CameraCutChange__Fv(void)

{
  *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x18) =
       *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x18) & 0x7f | 0x80;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e1be0  CharactorShow__Fib
 * C++: CharactorShow(int, bool)
 * size: 0x85c bytes
 * --------------------------------------------------------------------------- */
void CharactorShow__Fib(int param_1,char param_2)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  long lVar4;
  
  if (param_1 < 0) {
    for (iVar3 = 0; iVar3 < 0xc; iVar3 = iVar3 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar3 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar3 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar3 * 0x4f0 + 0xb2) << 0x3d))) {
        lVar4 = 0;
        while ((lVar4 < *(short *)(iGpffff86b4 + 0x3c30) &&
               (*(int *)(iGpffff86b4 + (int)lVar4 * 0x14 + 0x3c34) != iVar3))) {
          lVar4 = (long)((int)lVar4 + 1);
        }
        if (*(short *)(iGpffff86b4 + 0x3c30) <= lVar4) {
          lVar4 = 0;
          while ((lVar4 < *(short *)(iGpffff86b4 + 0x3c32) &&
                 (*(int *)(iGpffff86b4 + (int)lVar4 * 0x14 + 0x3d24) != iVar3))) {
            lVar4 = (long)((int)lVar4 + 1);
          }
          if (*(short *)(iGpffff86b4 + 0x3c32) <= lVar4) {
            if (param_2 == '\x01') {
              if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144) + 0x4b1) <<
                        0x3e) < 0) {
                OTEntry__8BtlModelFii(*(undefined4 *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144),4,8);
                ShadowOn__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144));
              }
              iVar1 = *(int *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144);
              *(byte *)(iVar1 + 0x4b1) = *(byte *)(iVar1 + 0x4b1) & 0xfd;
              if (((*(byte *)(iGpffff86b4 + iVar3 * 0x4f0 + 0xb4) & 1) == 0) &&
                 (*(short *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x120) == 3)) {
                for (iVar1 = *(int *)(iGpffff86b4 + 0x4378); iVar1 != 0;
                    iVar1 = *(int *)(iVar1 + 0x534)) {
                  if ((*(int *)(iVar1 + 0x5a0) == 7) || (*(int *)(iVar1 + 0x5a0) == 8)) {
                    OTEntry__6EffMdlFii(iVar1,4,8);
                  }
                }
              }
            }
            else {
              if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144) + 0x4b0) <<
                        0x3e) < 0) {
                OTRelease__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144));
                ShadowOff__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144));
                iVar1 = *(int *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x144);
                *(byte *)(iVar1 + 0x4b1) = *(byte *)(iVar1 + 0x4b1) & 0xfd | 2;
              }
              if (((*(byte *)(iGpffff86b4 + iVar3 * 0x4f0 + 0xb4) & 1) == 0) &&
                 (*(short *)(iGpffff86b4 + iVar3 * 0x4f0 + 0x120) == 3)) {
                for (iVar1 = *(int *)(iGpffff86b4 + 0x4378); iVar1 != 0;
                    iVar1 = *(int *)(iVar1 + 0x534)) {
                  if ((*(int *)(iVar1 + 0x5a0) == 7) || (*(int *)(iVar1 + 0x5a0) == 8)) {
                    OTRelease__6EffMdlFv(iVar1);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else if (param_2 == '\x01') {
    if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4b1) << 0x3e) <
        0) {
      uVar2 = OTEntry__8BtlModelFii(*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),4,8);
      ShadowOn__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),param_1,uVar2);
    }
    iVar3 = *(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144);
    *(byte *)(iVar3 + 0x4b1) = *(byte *)(iVar3 + 0x4b1) & 0xfd;
    if (((*(byte *)(iGpffff86b4 + param_1 * 0x4f0 + 0xb4) & 1) == 0) &&
       (*(short *)(iGpffff86b4 + param_1 * 0x4f0 + 0x120) == 3)) {
      for (iVar3 = *(int *)(iGpffff86b4 + 0x4378); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x534)) {
        if ((*(int *)(iVar3 + 0x5a0) == 7) || (*(int *)(iVar3 + 0x5a0) == 8)) {
          OTEntry__6EffMdlFii(iVar3,4,8);
        }
      }
    }
  }
  else {
    if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144) + 0x4b0) << 0x3e) <
        0) {
      OTRelease__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144));
      ShadowOff__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144));
      iVar3 = *(int *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144);
      *(byte *)(iVar3 + 0x4b1) = *(byte *)(iVar3 + 0x4b1) & 0xfd | 2;
    }
    if (((*(byte *)(iGpffff86b4 + param_1 * 0x4f0 + 0xb4) & 1) == 0) &&
       (*(short *)(iGpffff86b4 + param_1 * 0x4f0 + 0x120) == 3)) {
      for (iVar3 = *(int *)(iGpffff86b4 + 0x4378); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x534)) {
        if ((*(int *)(iVar3 + 0x5a0) == 7) || (*(int *)(iVar3 + 0x5a0) == 8)) {
          OTRelease__6EffMdlFv(iVar3);
        }
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e2440  WeaponShow__Fiib
 * C++: WeaponShow(int, int, bool)
 * size: 0x78 bytes
 * --------------------------------------------------------------------------- */
void WeaponShow__Fiib(int param_1,undefined4 param_2,undefined1 param_3)

{
  if ((-1 < param_1) && (param_1 < 0xc)) {
    WeaponShow__8BtlModelFib(*(undefined4 *)(iGpffff86b4 + param_1 * 0x4f0 + 0x144),param_2,param_3)
    ;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e24c0  BattleBGShow__Fb
 * C++: BattleBGShow(bool)
 * size: 0x148 bytes
 * --------------------------------------------------------------------------- */
void BattleBGShow__Fb(char param_1)

{
  if (param_1 == '\x01') {
    if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) << 0x3e) < 0) {
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x4c))
                (*(int *)(iGpffff86b4 + 0x3f20),1,2);
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x58))
                (0x3f800000,*(int *)(iGpffff86b4 + 0x3f20),0,0xaf);
    }
    *(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) =
         *(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) & 0xfd;
  }
  else if ((*(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) & 1) != 0) {
    (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x50))();
    (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x58))
              (0,*(int *)(iGpffff86b4 + 0x3f20),0,0xaf);
    *(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) =
         *(byte *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b0) & 0xfd | 2;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e2610  MagicStartEffectCall__Fi
 * C++: MagicStartEffectCall(int)
 * size: 0x6d8 bytes
 * --------------------------------------------------------------------------- */
void MagicStartEffectCall__Fi(undefined8 param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  float fVar6;
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar5 = (int)param_1;
  if ((*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb4) & 1) == 0) {
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0xe);
      uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0xf);
      uVar1 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar3,uVar4,param_1,2);
    }
    *(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) = uVar1;
    uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x10);
    createMotion__5ModelFPUc(*(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) + 0x20,uVar3);
    setMotion__7ExModelFPCc(*(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) + 0x20,0x655608);
    auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x150));
    auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x390));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_70 = _sqc2(auVar7);
    __ct__7FVectorFRC7FVector(auStack_20,auStack_70);
    uStack_8 = uStack_18;
    uStack_4 = uStack_14;
    uStack_c = 0xbe4ccccd;
    SetPos__6EffMdlFP7FVector(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558),&uStack_10);
    OTEntry__6EffMdlFii(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558),4,8);
    lVar2 = __nw__FUi(0x690);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__7FVectorFRC7FVector(auStack_30,&uStack_10);
      uVar1 = __ct__15MgcInvkParticleFii7FVectorf(0x41200000,lVar2,0,param_1,uVar3);
    }
    *(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x554) = uVar1;
  }
  else {
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x11);
      uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x12);
      uVar1 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar3,uVar4,param_1,2);
    }
    *(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) = uVar1;
    uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x13);
    createMotion__5ModelFPUc(*(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) + 0x20,uVar3);
    setMotion__7ExModelFPCc(*(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558) + 0x20,0x655608);
    auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x150));
    auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x390));
    auVar7 = _vadd(auVar7,auVar8);
    auStack_80 = _sqc2(auVar7);
    __ct__7FVectorFRC7FVector(auStack_40,auStack_80);
    uStack_8 = uStack_38;
    uStack_4 = uStack_34;
    uStack_c = 0xbe4ccccd;
    SetPos__6EffMdlFP7FVector(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558),&uStack_10);
    fVar6 = (*(float *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x3b0) + 5.0) / 10.0;
    fStack_50 = (fVar6 - 1.0) / 2.0 + 1.0;
    fStack_4c = ((fVar6 - 1.0) / 2.0) * 1.2 + 1.0;
    fStack_48 = (fVar6 - 1.0) / 2.0 + 1.0;
    uStack_44 = 0x3f800000;
    SetScale__6EffMdlF7FVector(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558),&fStack_50);
    OTEntry__6EffMdlFii(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x558),4,8);
  }
  auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x150));
  auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar5 * 0x4f0 + 0x390));
  auVar7 = _vadd(auVar7,auVar8);
  auStack_90 = _sqc2(auVar7);
  __ct__7FVectorFRC7FVector(auStack_60,auStack_90);
  uStack_10 = auStack_60._0_4_;
  uStack_c = auStack_60._4_4_;
  uStack_8 = uStack_58;
  uStack_4 = uStack_54;
  PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2002000,1,&uStack_10);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e2cf0  MagicStartEffectCall2__FiiP7FVectorff
 * C++: MagicStartEffectCall2(int, int, FVector *, float, float)
 * size: 0x3d0 bytes
 * --------------------------------------------------------------------------- */
void MagicStartEffectCall2__FiiP7FVectorff
               (float param_1,float param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [24];
  float fStack_58;
  float fStack_54;
  int iStack_50;
  undefined4 uStack_40;
  int iStack_30;
  float fStack_20;
  float fStack_10;
  
  *(undefined4 *)(param_5 + 4) = 0xbe4ccccd;
  iStack_50 = param_3;
  uStack_40 = param_4;
  iStack_30 = param_5;
  fStack_20 = param_1;
  fStack_10 = param_2;
  if (param_3 == 0) {
    lVar2 = __nw__FUi(0x5c0);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0xe);
      uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0xf);
      uVar3 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar3,uVar4,0xffffffffffffffff,2);
    }
    uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x10);
    iVar1 = (int)uVar3;
    createMotion__5ModelFPUc(iVar1 + 0x20,uVar4);
    setMotion__7ExModelFPCc(iVar1 + 0x20,0x655608);
    SetPos__6EffMdlFP7FVector(uVar3,iStack_30);
    OTEntry__6EffMdlFii(uVar3,4,8);
    *(undefined4 *)(iVar1 + 0x5b4) = uStack_40;
    lVar2 = __nw__FUi(0x690);
    iVar1 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__7FVectorFPC7FVector(auStack_70,iStack_30);
      iVar1 = __ct__15MgcInvkParticleFii7FVectorf(0x41200000,lVar2,0,0xffffffffffffffff,uVar3);
    }
    *(undefined4 *)(iVar1 + 0x58) = uStack_40;
  }
  else {
    lVar2 = __nw__FUi(0x5c0);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x11);
      uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x12);
      uVar3 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar3,uVar4,0xffffffffffffffff,2);
    }
    uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x13);
    iVar1 = (int)uVar3;
    createMotion__5ModelFPUc(iVar1 + 0x20,uVar4);
    setMotion__7ExModelFPCc(iVar1 + 0x20,0x655608);
    SetPos__6EffMdlFP7FVector(uVar3,iStack_30);
    fStack_54 = (fStack_20 + 5.0) / 10.0;
    fStack_58 = fStack_10 / 20.0;
    fStack_80 = (fStack_54 - 1.0) / 2.0 + 1.0;
    fStack_7c = ((fStack_54 - 1.0) / 2.0) * 1.2 + 1.0;
    fStack_78 = (fStack_54 - 1.0) / 2.0 + 1.0;
    uStack_74 = 0x3f800000;
    SetScale__6EffMdlF7FVector(uVar3,&fStack_80);
    OTEntry__6EffMdlFii(uVar3,4,8);
    *(undefined4 *)(iVar1 + 0x5b4) = uStack_40;
  }
  PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2002000,1,iStack_30);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e30c0  HitMarkEffectCall__Fi7FVector7FVectorf
 * C++: HitMarkEffectCall(int, FVector, FVector, float)
 * size: 0x6b8 bytes
 * --------------------------------------------------------------------------- */
void HitMarkEffectCall__Fi7FVector7FVectorf
               (float param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [4];
  float fStack_1c;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uVar1 = __ct__7FVectorFRC7FVector(auStack_30,param_4);
  Get3DAngle__F7FVector(auStack_20,uVar1);
  param_1 = param_1 * 1.25;
  switch(param_2) {
  case 0:
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),1);
      uVar1 = __ct__6EffMdlFPUcPUcfii(param_1,lVar2,uVar1,uVar3,0xffffffffffffffff,3);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655610);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    SetAlpha__6EffMdlFf(0x3f400000,uVar1);
    OTEntry__6EffMdlFii(uVar1,4,8);
    break;
  case 1:
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),2);
      uVar1 = __ct__6EffMdlFPUcPUcfii(param_1,lVar2,uVar1,uVar3,0xffffffffffffffff,4);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655618);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    uStack_40 = 0x3fa00000;
    uStack_3c = 0x3fa00000;
    uStack_38 = 0x3fa00000;
    uStack_34 = 0x3f800000;
    SetScale__6EffMdlF7FVector(uVar1,&uStack_40);
    SetAlpha__6EffMdlFf(0x3f400000,uVar1);
    OTEntry__6EffMdlFii(uVar1,4,8);
    break;
  case 2:
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),3);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),4);
      uVar1 = __ct__6EffMdlFPUcPUcfii(param_1,lVar2,uVar1,uVar3,0xffffffffffffffff,3);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655610);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    SetAlpha__6EffMdlFf(0x3f400000,uVar1);
    OTEntry__6EffMdlFii(uVar1,4,8);
    break;
  case 3:
    lVar2 = __nw__FUi(0x90);
    if (lVar2 != 0) {
      uVar1 = __ct__7FVectorFRC7FVector(auStack_50,param_3);
      __ct__7HitMarkFii7FVectorif(param_1 * 1.6,lVar2,0,0xffffffffffffffff,uVar1,3);
    }
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),3);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),5);
      uVar1 = __ct__6EffMdlFPUcPUcfii(param_1,lVar2,uVar1,uVar3,0xffffffffffffffff,4);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655618);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    uStack_60 = 0x3fa00000;
    uStack_5c = 0x3fa00000;
    uStack_58 = 0x3fa00000;
    uStack_54 = 0x3f800000;
    SetScale__6EffMdlF7FVector(uVar1,&uStack_60);
    SetAlpha__6EffMdlFf(0x3f400000,uVar1);
    OTEntry__6EffMdlFii(uVar1,4,8);
    break;
  case 4:
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),6);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),7);
      uVar1 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar1,uVar3,0xffffffffffffffff,0);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655610);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    uStack_c = GetRad(-fStack_1c);
    uStack_10 = 0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    SetAngle__6EffMdlFP7FVector(uVar1,&uStack_10);
    OTEntry__6EffMdlFii(uVar1,4,8);
    break;
  case 5:
    lVar2 = __nw__FUi(0x5c0);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),8);
      uVar3 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),9);
      uVar1 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar2,uVar1,uVar3,0xffffffffffffffff,0);
    }
    setMotion__7ExModelFPCc((int)uVar1 + 0x20,0x655610);
    SetPos__6EffMdlFP7FVector(uVar1,param_3);
    uStack_c = GetRad(-fStack_1c);
    uStack_10 = 0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    SetAngle__6EffMdlFP7FVector(uVar1,&uStack_10);
    OTEntry__6EffMdlFii(uVar1,4,8);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e3780  BattleBGShowParts__FUiUi
 * C++: BattleBGShowParts(uint, uint)
 * size: 0x6c bytes
 * --------------------------------------------------------------------------- */
undefined4 BattleBGShowParts__FUiUi(uint param_1,uint param_2)

{
  *(uint *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214) =
       *(uint *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214) | param_1;
  *(uint *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214) =
       *(int *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214) -
       (*(uint *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214) & param_2);
  return *(undefined4 *)(*(int *)(iGpffff86b4 + 0x4324) + 0x214);
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e37f0  CharacterPushMode__Fib
 * C++: CharacterPushMode(int, bool)
 * size: 0xac bytes
 * --------------------------------------------------------------------------- */
void CharacterPushMode__Fib(int param_1,char param_2)

{
  int iVar1;
  
  if (param_2 == '\x01') {
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb5) = *(byte *)(iVar1 + 0xb5) & 0xfe;
  }
  else {
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb5) = *(byte *)(iVar1 + 0xb5) & 0xfe | 1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e38a0  GetWarpPos__Fib
 * C++: GetWarpPos(int, bool)
 * size: 0x3334 bytes
 * --------------------------------------------------------------------------- */
void GetWarpPos__Fib(int param_1,int param_2,char param_3)

{
  bool bVar1;
  bool bVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  ulong uVar10;
  undefined8 uVar11;
  byte bVar12;
  ulong uVar13;
  undefined8 in_v1_udw;
  undefined2 uVar14;
  int iVar15;
  int iVar16;
  short sVar17;
  int iVar18;
  int iVar19;
  long lVar20;
  long lVar21;
  float fVar22;
  float fVar23;
  undefined1 in_vf0 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [8];
  undefined4 uStack_448;
  undefined4 uStack_444;
  undefined1 auStack_440 [8];
  float fStack_438;
  undefined4 uStack_434;
  undefined1 auStack_430 [8];
  float fStack_428;
  undefined4 uStack_424;
  undefined1 auStack_420 [8];
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  float fStack_3d0;
  float fStack_3cc;
  float fStack_3c8;
  undefined4 uStack_3c4;
  float fStack_3c0;
  float fStack_3bc;
  float fStack_3b8;
  undefined4 uStack_3b4;
  float fStack_3b0;
  float fStack_3ac;
  float fStack_3a8;
  undefined4 uStack_3a4;
  float fStack_390;
  float fStack_38c;
  float fStack_388;
  undefined4 uStack_384;
  short asStack_380 [11];
  short sStack_36a;
  short asStack_280 [272];
  int aiStack_60 [12];
  int aiStack_30 [12];
  
  iVar8 = 0;
  iVar6 = 0;
  auVar24 = _vmr32(in_vf0);
  auVar25 = _vmr32(auVar24);
  auVar26 = _vmr32(auVar25);
  auStack_3e0 = _sqc2(in_vf0);
  auStack_3f0 = _sqc2(auVar24);
  auStack_400 = _sqc2(auVar25);
  auStack_410 = _sqc2(auVar26);
  uVar14 = (undefined2)param_2;
  fStack_3d0 = in_zero_lo;
  fStack_3cc = in_zero_hi;
  fStack_3c8 = in_zero_udw;
  uStack_3c4 = in_register_0000000c;
  fStack_3c0 = in_zero_lo;
  fStack_3bc = in_zero_hi;
  fStack_3b8 = in_zero_udw;
  uStack_3b4 = in_register_0000000c;
  fStack_3b0 = in_zero_lo;
  fStack_3ac = in_zero_hi;
  fStack_3a8 = in_zero_udw;
  uStack_3a4 = in_register_0000000c;
  if (param_3 == '\x01') {
    if (*(short *)(iGpffff86b4 + param_2 * 0x4f0 + 0x18c) == 499) {
      iVar6 = iGpffff86b4 + param_2 * 0x4f0;
      fStack_388 = *(float *)(iVar6 + 0x168);
      uStack_384 = *(undefined4 *)(iVar6 + 0x16c);
      fStack_390 = (float)*(undefined8 *)(iVar6 + 0x160);
      fStack_38c = (float)((ulong)*(undefined8 *)(iVar6 + 0x160) >> 0x20);
      if ((*(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8) < '\x16') ||
         ('&' < *(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8))) {
        iVar6 = iGpffff86b4 + param_2 * 0x4f0;
        *(byte *)(iVar6 + 0xb1) = *(byte *)(iVar6 + 0xb1) & 0xef | 0x10;
      }
      *(undefined2 *)(iGpffff86b4 + 0x45d4) = uVar14;
      *(undefined1 *)(iGpffff86b4 + 0x45c0) = 1;
      __ct__7FVectorFRC7FVector(param_1,&fStack_390);
      return;
    }
    for (iVar18 = 0; iVar18 < 0xc; iVar18 = iVar18 + 1) {
      if (((((*(byte *)(iGpffff86b4 + iVar18 * 0x4f0 + 0xb0) & 1) != 0) &&
           ((long)((ulong)*(byte *)(iGpffff86b4 + iVar18 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
          (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar18 * 0x4f0 + 0xb2) << 0x3d))) &&
         (0 < *(short *)(iGpffff86b4 + iVar18 * 0x4f0 + 0x124))) {
        if ((*(byte *)(iGpffff86b4 + *(int *)(iGpffff86b4 + 0x3d24) * 0x4f0 + 0xb4) & 1) ==
            (*(byte *)(iGpffff86b4 + iVar18 * 0x4f0 + 0xb4) & 1)) {
          aiStack_60[iVar6] = iVar18;
          iVar6 = iVar6 + 1;
        }
        else {
          aiStack_30[iVar8] = iVar18;
          iVar8 = iVar8 + 1;
        }
      }
    }
    asStack_280[0] = (short)(int)-(*(float *)(iGpffff86b4 + 0x3f14) / 2.0);
    asStack_280[1] = (short)(int)-(*(float *)(iGpffff86b4 + 0x3f1c) / 2.0);
    asStack_280[2] = (short)(int)*(float *)(iGpffff86b4 + 0x3f14);
    asStack_280[3] = (short)(int)*(float *)(iGpffff86b4 + 0x3f1c);
    iVar18 = 1;
    iVar6 = param_1;
    for (iVar19 = 0; iVar19 < iVar8; iVar19 = iVar19 + 1) {
      asStack_380[0] =
           (short)(int)(*(float *)(iGpffff86b4 + aiStack_30[iVar19] * 0x4f0 + 0x160) -
                       (*(float *)(iGpffff86b4 + aiStack_30[iVar19] * 0x4f0 + 0x3b0) + 0.5));
      asStack_380[1] =
           (short)(int)(*(float *)(iGpffff86b4 + aiStack_30[iVar19] * 0x4f0 + 0x168) -
                       (*(float *)(iGpffff86b4 + aiStack_30[iVar19] * 0x4f0 + 0x3b0) + 0.5));
      asStack_380[2] =
           (short)(int)(*(float *)(iGpffff86b4 + aiStack_30[iVar19] * 0x4f0 + 0x3b0) * 2.0 + 0.5);
      iVar6 = 1;
      asStack_380[3] = asStack_380[2];
      do {
        for (iVar15 = 0; iVar15 < iVar18; iVar15 = iVar15 + 1) {
          iVar16 = (int)asStack_280[iVar15 * 4 + 2];
          if (asStack_280[iVar15 * 4 + 2] < 0) {
            iVar16 = iVar16 + 1;
          }
          iVar7 = (int)asStack_380[2];
          if (asStack_380[2] < 0) {
            iVar7 = iVar7 + 1;
          }
          sVar17 = (asStack_280[iVar15 * 4] + (short)(iVar16 >> 1)) -
                   (asStack_380[0] + (short)(iVar7 >> 1));
          if (sVar17 < 0) {
            sVar17 = -sVar17;
          }
          iVar16 = (int)asStack_380[2] + (int)asStack_280[iVar15 * 4 + 2];
          if (iVar16 < 0) {
            iVar16 = iVar16 + 1;
          }
          if ((long)sVar17 <= (long)(iVar16 >> 1)) {
            iVar16 = (int)asStack_280[iVar15 * 4 + 3];
            if (asStack_280[iVar15 * 4 + 3] < 0) {
              iVar16 = iVar16 + 1;
            }
            iVar7 = (int)asStack_380[3];
            if (asStack_380[3] < 0) {
              iVar7 = iVar7 + 1;
            }
            sVar17 = (asStack_280[iVar15 * 4 + 1] + (short)(iVar16 >> 1)) -
                     (asStack_380[1] + (short)(iVar7 >> 1));
            if (sVar17 < 0) {
              sVar17 = -sVar17;
            }
            iVar16 = (int)asStack_380[3] + (int)asStack_280[iVar15 * 4 + 3];
            if (iVar16 < 0) {
              iVar16 = iVar16 + 1;
            }
            if ((long)sVar17 <= (long)(iVar16 >> 1)) break;
          }
        }
        if (iVar15 < iVar18) {
          if (asStack_280[iVar15 * 4] < asStack_380[0]) {
            asStack_280[iVar18 * 4] = asStack_280[iVar15 * 4];
            asStack_280[iVar18 * 4 + 1] = asStack_280[iVar15 * 4 + 1];
            asStack_280[iVar18 * 4 + 2] = asStack_380[0] - asStack_280[iVar15 * 4];
            asStack_280[iVar18 * 4 + 3] = asStack_280[iVar15 * 4 + 3];
            asStack_280[iVar15 * 4 + 2] =
                 asStack_280[iVar15 * 4 + 2] - (asStack_380[0] - asStack_280[iVar15 * 4]);
            asStack_280[iVar15 * 4] = asStack_380[0];
            iVar18 = iVar18 + 1;
          }
          else if (asStack_380[0] < asStack_280[iVar15 * 4]) {
            asStack_380[iVar6 * 4] = asStack_380[0];
            asStack_380[iVar6 * 4 + 1] = asStack_380[1];
            asStack_380[iVar6 * 4 + 2] = asStack_280[iVar15 * 4] - asStack_380[0];
            asStack_380[iVar6 * 4 + 3] = asStack_380[3];
            asStack_380[2] = asStack_380[2] - (asStack_280[iVar15 * 4] - asStack_380[0]);
            asStack_380[0] = asStack_280[iVar15 * 4];
            iVar6 = iVar6 + 1;
          }
          if (asStack_280[iVar15 * 4 + 1] < asStack_380[1]) {
            asStack_280[iVar18 * 4] = asStack_280[iVar15 * 4];
            asStack_280[iVar18 * 4 + 1] = asStack_280[iVar15 * 4 + 1];
            asStack_280[iVar18 * 4 + 2] = asStack_280[iVar15 * 4 + 2];
            asStack_280[iVar18 * 4 + 3] = asStack_380[1] - asStack_280[iVar15 * 4 + 1];
            asStack_280[iVar15 * 4 + 3] =
                 asStack_280[iVar15 * 4 + 3] - (asStack_380[1] - asStack_280[iVar15 * 4 + 1]);
            asStack_280[iVar15 * 4 + 1] = asStack_380[1];
            iVar18 = iVar18 + 1;
          }
          else if (asStack_380[1] < asStack_280[iVar15 * 4 + 1]) {
            asStack_380[iVar6 * 4] = asStack_380[0];
            asStack_380[iVar6 * 4 + 1] = asStack_380[1];
            asStack_380[iVar6 * 4 + 2] = asStack_380[2];
            asStack_380[iVar6 * 4 + 3] = asStack_280[iVar15 * 4 + 1] - asStack_380[1];
            asStack_380[3] = asStack_380[3] - (asStack_280[iVar15 * 4 + 1] - asStack_380[1]);
            asStack_380[1] = asStack_280[iVar15 * 4 + 1];
            iVar6 = iVar6 + 1;
          }
          if ((int)asStack_380[0] + (int)asStack_380[2] <
              (int)asStack_280[iVar15 * 4] + (int)asStack_280[iVar15 * 4 + 2]) {
            asStack_280[iVar18 * 4] = asStack_380[0] + asStack_380[2];
            asStack_280[iVar18 * 4 + 1] = asStack_280[iVar15 * 4 + 1];
            asStack_280[iVar18 * 4 + 2] =
                 (asStack_280[iVar15 * 4] + asStack_280[iVar15 * 4 + 2]) - asStack_280[iVar18 * 4];
            asStack_280[iVar18 * 4 + 3] = asStack_280[iVar15 * 4 + 3];
            asStack_280[iVar15 * 4 + 2] = asStack_280[iVar18 * 4] - asStack_280[iVar15 * 4];
            iVar18 = iVar18 + 1;
          }
          else if ((int)asStack_280[iVar15 * 4] + (int)asStack_280[iVar15 * 4 + 2] <
                   (int)asStack_380[0] + (int)asStack_380[2]) {
            asStack_380[iVar6 * 4] = asStack_280[iVar15 * 4] + asStack_280[iVar15 * 4 + 2];
            asStack_380[iVar6 * 4 + 1] = asStack_380[1];
            asStack_380[iVar6 * 4 + 2] = (asStack_380[0] + asStack_380[2]) - asStack_380[iVar6 * 4];
            asStack_380[iVar6 * 4 + 3] = asStack_380[3];
            asStack_380[2] = asStack_380[iVar6 * 4] - asStack_380[0];
            iVar6 = iVar6 + 1;
          }
          if ((int)asStack_380[1] + (int)asStack_380[3] <
              (int)asStack_280[iVar15 * 4 + 1] + (int)asStack_280[iVar15 * 4 + 3]) {
            asStack_280[iVar18 * 4] = asStack_280[iVar15 * 4];
            asStack_280[iVar18 * 4 + 1] = asStack_380[1] + asStack_380[3];
            asStack_280[iVar18 * 4 + 2] = asStack_280[iVar15 * 4 + 2];
            asStack_280[iVar18 * 4 + 3] =
                 (asStack_280[iVar15 * 4 + 1] + asStack_280[iVar15 * 4 + 3]) -
                 asStack_280[iVar18 * 4 + 1];
            asStack_280[iVar15 * 4 + 3] = asStack_280[iVar18 * 4 + 1] - asStack_280[iVar15 * 4 + 1];
            iVar18 = iVar18 + 1;
          }
          else if ((int)asStack_280[iVar15 * 4 + 1] + (int)asStack_280[iVar15 * 4 + 3] <
                   (int)asStack_380[1] + (int)asStack_380[3]) {
            asStack_380[iVar6 * 4] = asStack_380[0];
            asStack_380[iVar6 * 4 + 1] = asStack_280[iVar15 * 4 + 1] + asStack_280[iVar15 * 4 + 3];
            asStack_380[iVar6 * 4 + 2] = asStack_380[2];
            asStack_380[iVar6 * 4 + 3] =
                 (asStack_380[1] + asStack_380[3]) - asStack_380[iVar6 * 4 + 1];
            asStack_380[3] = asStack_380[iVar6 * 4 + 1] - asStack_380[1];
            iVar6 = iVar6 + 1;
          }
          while (iVar16 = iVar15 + 1, iVar16 < iVar18) {
            asStack_280[iVar15 * 4] = asStack_280[iVar16 * 4];
            asStack_280[iVar15 * 4 + 1] = asStack_280[iVar16 * 4 + 1];
            asStack_280[iVar15 * 4 + 2] = asStack_280[iVar16 * 4 + 2];
            asStack_280[iVar15 * 4 + 3] = asStack_280[iVar16 * 4 + 3];
            iVar15 = iVar16;
          }
          iVar18 = iVar18 + -1;
        }
        for (iVar15 = 1; iVar15 < iVar6; iVar15 = iVar15 + 1) {
          asStack_380[(iVar15 + -1) * 4] = asStack_380[iVar15 * 4];
          asStack_380[(iVar15 + -1) * 4 + 1] = asStack_380[iVar15 * 4 + 1];
          asStack_380[(iVar15 + -1) * 4 + 2] = asStack_380[iVar15 * 4 + 2];
          asStack_380[(iVar15 + -1) * 4 + 3] = asStack_380[iVar15 * 4 + 3];
        }
        iVar6 = iVar6 + -1;
      } while (0 < iVar6);
    }
    bVar2 = true;
LAB_005e5f38:
    if (bVar2) {
      bVar2 = false;
      for (iVar8 = 0; iVar19 = iVar8, iVar8 < iVar18; iVar8 = iVar8 + 1) {
        do {
          iVar19 = iVar19 + 1;
          if (iVar18 <= iVar19) goto LAB_005e5f18;
          iVar15 = (int)asStack_280[iVar8 * 4 + 2];
          if (asStack_280[iVar8 * 4 + 2] < 0) {
            iVar15 = iVar15 + 1;
          }
          iVar16 = (int)asStack_280[iVar19 * 4 + 2];
          if (asStack_280[iVar19 * 4 + 2] < 0) {
            iVar16 = iVar16 + 1;
          }
          sVar17 = (asStack_280[iVar8 * 4] + (short)(iVar15 >> 1)) -
                   (asStack_280[iVar19 * 4] + (short)(iVar16 >> 1));
          if (sVar17 < 0) {
            sVar17 = -sVar17;
          }
          iVar15 = (int)asStack_280[iVar8 * 4 + 2] + (int)asStack_280[iVar19 * 4 + 2];
          if (iVar15 < 0) {
            iVar15 = iVar15 + 1;
          }
          bVar1 = (long)sVar17 < (long)(iVar15 >> 1);
          iVar15 = (int)asStack_280[iVar8 * 4 + 3];
          if (asStack_280[iVar8 * 4 + 3] < 0) {
            iVar15 = iVar15 + 1;
          }
          iVar16 = (int)asStack_280[iVar19 * 4 + 3];
          if (asStack_280[iVar19 * 4 + 3] < 0) {
            iVar16 = iVar16 + 1;
          }
          sVar17 = (asStack_280[iVar8 * 4 + 1] + (short)(iVar15 >> 1)) -
                   (asStack_280[iVar19 * 4 + 1] + (short)(iVar16 >> 1));
          if (sVar17 < 0) {
            sVar17 = -sVar17;
          }
          iVar15 = (int)asStack_280[iVar8 * 4 + 3] + (int)asStack_280[iVar19 * 4 + 3];
          if (iVar15 < 0) {
            iVar15 = iVar15 + 1;
          }
          bVar12 = bVar1;
          if ((long)sVar17 < (long)(iVar15 >> 1)) {
            bVar12 = 2;
          }
          if ((((long)asStack_280[iVar8 * 4] ==
                (long)((int)asStack_280[iVar19 * 4] + (int)asStack_280[iVar19 * 4 + 2])) ||
              ((long)asStack_280[iVar19 * 4] ==
               (long)((int)asStack_280[iVar8 * 4] + (int)asStack_280[iVar8 * 4 + 2]))) &&
             ((bVar12 & 2) != 0)) {
            asStack_380[4] = asStack_280[iVar8 * 4 + 2] * asStack_280[iVar8 * 4 + 3];
            asStack_380[5] = asStack_280[iVar19 * 4 + 2] * asStack_280[iVar19 * 4 + 3];
            asStack_380[0] = asStack_280[iVar8 * 4];
            if (asStack_280[iVar19 * 4] < asStack_280[iVar8 * 4]) {
              asStack_380[0] = asStack_280[iVar19 * 4];
            }
            asStack_380[1] = asStack_280[iVar8 * 4 + 1];
            if (asStack_380[1] < asStack_280[iVar19 * 4 + 1]) {
              asStack_380[1] = asStack_280[iVar19 * 4 + 1];
            }
            asStack_380[2] = asStack_280[iVar8 * 4 + 2] + asStack_280[iVar19 * 4 + 2];
            asStack_380[3] = asStack_280[iVar8 * 4 + 1] + asStack_280[iVar8 * 4 + 3];
            if ((long)((int)asStack_280[iVar19 * 4 + 1] + (int)asStack_280[iVar19 * 4 + 3]) <
                (long)asStack_380[3]) {
              asStack_380[3] = asStack_280[iVar19 * 4 + 1] + asStack_280[iVar19 * 4 + 3];
            }
            asStack_380[3] = asStack_380[3] - asStack_380[1];
            asStack_380[6] = asStack_380[2] * asStack_380[3];
            if ((asStack_380[4] < asStack_380[6]) &&
               ((short)(asStack_280[iVar19 * 4 + 2] * asStack_280[iVar19 * 4 + 3]) < asStack_380[6])
               ) {
              iVar6 = 1;
              if (asStack_280[iVar8 * 4 + 1] < asStack_280[iVar19 * 4 + 1]) {
                asStack_380[4] = asStack_280[iVar8 * 4];
                asStack_380[5] = asStack_280[iVar8 * 4 + 1];
                asStack_380[6] = asStack_280[iVar8 * 4 + 2];
                asStack_380[7] = asStack_280[iVar19 * 4 + 1] - asStack_280[iVar8 * 4 + 1];
                asStack_280[iVar8 * 4 + 3] =
                     asStack_280[iVar8 * 4 + 3] -
                     (asStack_280[iVar19 * 4 + 1] - asStack_280[iVar8 * 4 + 1]);
                asStack_280[iVar8 * 4 + 1] = asStack_280[iVar19 * 4 + 1];
                iVar6 = 2;
              }
              else if (asStack_280[iVar19 * 4 + 1] < asStack_280[iVar8 * 4 + 1]) {
                asStack_380[4] = asStack_280[iVar19 * 4];
                asStack_380[5] = asStack_280[iVar19 * 4 + 1];
                asStack_380[6] = asStack_280[iVar19 * 4 + 2];
                asStack_380[7] = asStack_280[iVar8 * 4 + 1] - asStack_280[iVar19 * 4 + 1];
                asStack_280[iVar19 * 4 + 3] =
                     asStack_280[iVar19 * 4 + 3] -
                     (asStack_280[iVar8 * 4 + 1] - asStack_280[iVar19 * 4 + 1]);
                asStack_280[iVar19 * 4 + 1] = asStack_280[iVar8 * 4 + 1];
                iVar6 = 2;
              }
              if ((int)asStack_280[iVar19 * 4 + 1] + (int)asStack_280[iVar19 * 4 + 3] <
                  (int)asStack_280[iVar8 * 4 + 1] + (int)asStack_280[iVar8 * 4 + 3]) {
                asStack_380[iVar6 * 4] = asStack_280[iVar8 * 4];
                asStack_380[iVar6 * 4 + 1] =
                     asStack_280[iVar19 * 4 + 1] + asStack_280[iVar19 * 4 + 3];
                asStack_380[iVar6 * 4 + 2] = asStack_280[iVar8 * 4 + 2];
                asStack_380[iVar6 * 4 + 3] =
                     (asStack_280[iVar8 * 4 + 1] + asStack_280[iVar8 * 4 + 3]) -
                     asStack_380[iVar6 * 4 + 1];
                asStack_280[iVar8 * 4 + 3] = asStack_380[iVar6 * 4 + 1] - asStack_280[iVar8 * 4 + 1]
                ;
                iVar6 = iVar6 + 1;
              }
              else if ((int)asStack_280[iVar8 * 4 + 1] + (int)asStack_280[iVar8 * 4 + 3] <
                       (int)asStack_280[iVar19 * 4 + 1] + (int)asStack_280[iVar19 * 4 + 3]) {
                asStack_380[iVar6 * 4] = asStack_280[iVar19 * 4];
                asStack_380[iVar6 * 4 + 1] = asStack_280[iVar8 * 4 + 1] + asStack_280[iVar8 * 4 + 3]
                ;
                asStack_380[iVar6 * 4 + 2] = asStack_280[iVar19 * 4 + 2];
                asStack_380[iVar6 * 4 + 3] =
                     (asStack_280[iVar19 * 4 + 1] + asStack_280[iVar19 * 4 + 3]) -
                     asStack_380[iVar6 * 4 + 1];
                asStack_280[iVar19 * 4 + 3] =
                     asStack_380[iVar6 * 4 + 1] - asStack_280[iVar19 * 4 + 1];
                iVar6 = iVar6 + 1;
              }
              bVar2 = true;
            }
          }
          else if ((((long)asStack_280[iVar8 * 4 + 1] ==
                     (long)((int)asStack_280[iVar19 * 4 + 1] + (int)asStack_280[iVar19 * 4 + 3])) ||
                   ((long)asStack_280[iVar19 * 4 + 1] ==
                    (long)((int)asStack_280[iVar8 * 4 + 1] + (int)asStack_280[iVar8 * 4 + 3]))) &&
                  (bVar1)) {
            asStack_380[4] = asStack_280[iVar8 * 4 + 2] * asStack_280[iVar8 * 4 + 3];
            asStack_380[5] = asStack_280[iVar19 * 4 + 2] * asStack_280[iVar19 * 4 + 3];
            asStack_380[0] = asStack_280[iVar8 * 4];
            if (asStack_380[0] < asStack_280[iVar19 * 4]) {
              asStack_380[0] = asStack_280[iVar19 * 4];
            }
            asStack_380[1] = asStack_280[iVar8 * 4 + 1];
            if (asStack_280[iVar19 * 4 + 1] < asStack_280[iVar8 * 4 + 1]) {
              asStack_380[1] = asStack_280[iVar19 * 4 + 1];
            }
            asStack_380[2] = asStack_280[iVar8 * 4] + asStack_280[iVar8 * 4 + 2];
            if ((long)((int)asStack_280[iVar19 * 4] + (int)asStack_280[iVar19 * 4 + 2]) <
                (long)asStack_380[2]) {
              asStack_380[2] = asStack_280[iVar19 * 4] + asStack_280[iVar19 * 4 + 2];
            }
            asStack_380[2] = asStack_380[2] - asStack_380[0];
            asStack_380[3] = asStack_280[iVar8 * 4 + 3] + asStack_280[iVar19 * 4 + 3];
            asStack_380[6] = asStack_380[2] * asStack_380[3];
            if (((short)(asStack_280[iVar8 * 4 + 2] * asStack_280[iVar8 * 4 + 3]) < asStack_380[6])
               && ((short)(asStack_280[iVar19 * 4 + 2] * asStack_280[iVar19 * 4 + 3]) <
                   asStack_380[6])) {
              iVar6 = 1;
              if (asStack_280[iVar8 * 4] < asStack_280[iVar19 * 4]) {
                asStack_380[4] = asStack_280[iVar8 * 4];
                asStack_380[5] = asStack_280[iVar8 * 4 + 1];
                asStack_380[6] = asStack_280[iVar19 * 4] - asStack_280[iVar8 * 4];
                asStack_380[7] = asStack_280[iVar8 * 4 + 3];
                asStack_280[iVar8 * 4 + 2] =
                     asStack_280[iVar8 * 4 + 2] - (asStack_280[iVar19 * 4] - asStack_280[iVar8 * 4])
                ;
                asStack_280[iVar8 * 4] = asStack_280[iVar19 * 4];
                iVar6 = 2;
              }
              else if (asStack_280[iVar19 * 4] < asStack_280[iVar8 * 4]) {
                asStack_380[4] = asStack_280[iVar19 * 4];
                asStack_380[5] = asStack_280[iVar19 * 4 + 1];
                asStack_380[6] = asStack_280[iVar8 * 4] - asStack_280[iVar19 * 4];
                asStack_380[7] = asStack_280[iVar19 * 4 + 3];
                asStack_280[iVar19 * 4 + 2] =
                     asStack_280[iVar19 * 4 + 2] -
                     (asStack_280[iVar8 * 4] - asStack_280[iVar19 * 4]);
                asStack_280[iVar19 * 4] = asStack_280[iVar8 * 4];
                iVar6 = 2;
              }
              if ((int)asStack_280[iVar19 * 4] + (int)asStack_280[iVar19 * 4 + 2] <
                  (int)asStack_280[iVar8 * 4] + (int)asStack_280[iVar8 * 4 + 2]) {
                asStack_380[iVar6 * 4] = asStack_280[iVar19 * 4] + asStack_280[iVar19 * 4 + 2];
                asStack_380[iVar6 * 4 + 1] = asStack_280[iVar8 * 4 + 1];
                asStack_380[iVar6 * 4 + 2] =
                     (asStack_280[iVar8 * 4] + asStack_280[iVar8 * 4 + 2]) - asStack_380[iVar6 * 4];
                asStack_380[iVar6 * 4 + 3] = asStack_280[iVar8 * 4 + 3];
                asStack_280[iVar8 * 4 + 2] = asStack_380[iVar6 * 4] - asStack_280[iVar8 * 4];
                iVar6 = iVar6 + 1;
              }
              else if ((int)asStack_280[iVar8 * 4] + (int)asStack_280[iVar8 * 4 + 2] <
                       (int)asStack_280[iVar19 * 4] + (int)asStack_280[iVar19 * 4 + 2]) {
                asStack_380[iVar6 * 4] = asStack_280[iVar8 * 4] + asStack_280[iVar8 * 4 + 2];
                asStack_380[iVar6 * 4 + 1] = asStack_280[iVar19 * 4 + 1];
                asStack_380[iVar6 * 4 + 2] =
                     (asStack_280[iVar19 * 4] + asStack_280[iVar19 * 4 + 2]) -
                     asStack_380[iVar6 * 4];
                asStack_380[iVar6 * 4 + 3] = asStack_280[iVar19 * 4 + 3];
                asStack_280[iVar19 * 4 + 2] = asStack_380[iVar6 * 4] - asStack_280[iVar19 * 4];
                iVar6 = iVar6 + 1;
              }
              bVar2 = true;
            }
          }
        } while (!bVar2);
        asStack_280[iVar8 * 4] = asStack_380[0];
        asStack_280[iVar8 * 4 + 1] = asStack_380[1];
        asStack_280[iVar8 * 4 + 2] = asStack_380[2];
        asStack_280[iVar8 * 4 + 3] = asStack_380[3];
        if (iVar6 < 2) {
          for (; iVar19 + 1 < iVar18; iVar19 = iVar19 + 1) {
            asStack_280[iVar19 * 4] = asStack_280[(iVar19 + 1) * 4];
            asStack_280[iVar19 * 4 + 1] = asStack_280[(iVar19 + 1) * 4 + 1];
            asStack_280[iVar19 * 4 + 2] = asStack_280[(iVar19 + 1) * 4 + 2];
            asStack_280[iVar19 * 4 + 3] = asStack_280[(iVar19 + 1) * 4 + 3];
          }
          iVar18 = iVar18 + -1;
        }
        else {
          asStack_280[iVar19 * 4] = asStack_380[4];
          asStack_280[iVar19 * 4 + 1] = asStack_380[5];
          asStack_280[iVar19 * 4 + 2] = asStack_380[6];
          asStack_280[iVar19 * 4 + 3] = asStack_380[7];
          if (2 < iVar6) {
            asStack_280[iVar18 * 4] = asStack_380[8];
            asStack_280[iVar18 * 4 + 1] = asStack_380[9];
            asStack_280[iVar18 * 4 + 2] = asStack_380[10];
            asStack_280[iVar18 * 4 + 3] = sStack_36a;
            iVar18 = iVar18 + 1;
          }
        }
LAB_005e5f18:
        if (bVar2) break;
      }
      goto LAB_005e5f38;
    }
    iVar6 = 0;
    for (iVar8 = 1; iVar8 < iVar18; iVar8 = iVar8 + 1) {
      if ((int)asStack_280[iVar6 * 4 + 2] * (int)asStack_280[iVar6 * 4 + 3] <
          (int)asStack_280[iVar8 * 4 + 2] * (int)asStack_280[iVar8 * 4 + 3]) {
        iVar6 = iVar8;
      }
    }
    iVar8 = (int)asStack_280[iVar6 * 4 + 2];
    if (asStack_280[iVar6 * 4 + 2] < 0) {
      iVar8 = iVar8 + 1;
    }
    fStack_390 = (float)((int)asStack_280[iVar6 * 4] + (iVar8 >> 1));
    fStack_38c = 0.0;
    iVar8 = (int)asStack_280[iVar6 * 4 + 3];
    if (asStack_280[iVar6 * 4 + 3] < 0) {
      iVar8 = iVar8 + 1;
    }
    fStack_388 = (float)((int)asStack_280[iVar6 * 4 + 1] + (iVar8 >> 1));
    uStack_384 = 0x3f800000;
    fVar22 = *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x154);
    iVar6 = iGpffff86b4 + param_2 * 0x4f0;
    *(float *)(iVar6 + 0x160) = fStack_390;
    *(undefined4 *)(iVar6 + 0x164) = 0;
    *(float *)(iVar6 + 0x168) = fStack_388;
    *(undefined4 *)(iVar6 + 0x16c) = 0x3f800000;
    auVar4._4_4_ = 0;
    auVar4._0_4_ = fStack_390;
    auVar4._8_4_ = fStack_388;
    auVar4._12_4_ = 0x3f800000;
    auVar24 = _lqc2(auVar4);
    auVar25 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + param_2 * 0x4f0 + 0x390));
    auVar24 = _vsub(auVar24,auVar25);
    auStack_460 = _sqc2(auVar24);
    __ct__7FVectorFRC7FVector(auStack_420,auStack_460);
    iVar6 = iGpffff86b4 + param_2 * 0x4f0;
    *(int *)(iVar6 + 0x150) = auStack_420._0_4_;
    *(int *)(iVar6 + 0x154) = auStack_420._4_4_;
    *(undefined4 *)(iVar6 + 0x158) = uStack_418;
    *(undefined4 *)(iVar6 + 0x15c) = uStack_414;
    iVar6 = (int)(short)(int)fVar22;
    *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x154) = (float)iVar6;
    if (((float)iVar6 == 0.0) &&
       ((*(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8) < '\x16' ||
        ('&' < *(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8))))) {
      iVar6 = iGpffff86b4 + param_2 * 0x4f0;
      *(byte *)(iVar6 + 0xb1) = *(byte *)(iVar6 + 0xb1) & 0xef | 0x10;
    }
    *(undefined2 *)(iGpffff86b4 + 0x45d4) = uVar14;
    *(undefined1 *)(iGpffff86b4 + 0x45c0) = 1;
  }
  else {
    fStack_390 = in_zero_lo;
    fStack_38c = in_zero_hi;
    fStack_388 = in_zero_udw;
    uStack_384 = in_register_0000000c;
    for (lVar21 = 0; lVar21 < *(char *)(iGpffff86b4 + 0x45c0); lVar21 = (long)((int)lVar21 + 1)) {
      sVar17 = *(short *)(iGpffff86b4 + (int)lVar21 * 2 + 0x45d4);
      iVar6 = iGpffff86b4 + (sVar17 * 0x50 - (int)sVar17) * 0x10;
      fStack_3c8 = *(float *)(iVar6 + 0x168);
      uStack_3c4 = *(undefined4 *)(iVar6 + 0x16c);
      fStack_3d0 = (float)*(undefined8 *)(iVar6 + 0x160);
      fStack_3cc = (float)((ulong)*(undefined8 *)(iVar6 + 0x160) >> 0x20);
      sVar17 = *(short *)(iGpffff86b4 + (int)lVar21 * 2 + 0x45d4);
      asStack_380[0] =
           (short)(int)(*(float *)(iGpffff86b4 + (sVar17 * 0x50 - (int)sVar17) * 0x10 + 0x3b0) +
                        *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) + 5.0);
      iVar6 = 0;
      for (fVar22 = -3.1415927; fVar22 < 3.1415927; fVar22 = fVar22 + 0.09817477) {
        fVar23 = (float)cosf(fVar22);
        fStack_3c0 = fStack_3d0 + (float)(int)asStack_380[0] * fVar23;
        fStack_3bc = 0.0;
        uVar9 = fptodp(fVar22);
        uVar10 = sin(uVar9);
        auVar25._8_8_ = in_v1_udw;
        auVar25._0_8_ = 0x8000000000000000;
        auVar24._4_4_ = in_zero_hi;
        auVar24._0_4_ = in_zero_lo;
        auVar24._8_4_ = in_zero_udw;
        auVar24._12_4_ = in_register_0000000c;
        auVar24 = _pcpyld(auVar24,auVar25);
        uVar13 = auVar24._0_8_;
        uVar9 = litodp(asStack_380[0]);
        uVar9 = dpmul(uVar9,uVar10 ^ uVar13);
        uVar11 = fptodp(fStack_3c8);
        uVar9 = dpadd(uVar11,uVar9);
        fStack_3b8 = (float)dptofp(uVar9);
        uStack_3b4 = 0x3f800000;
        in_v1_udw = auVar24._8_8_;
        if ((((-*(float *)(iGpffff86b4 + 0x3f14) / 2.0 +
               *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) <= fStack_3c0) &&
             (fStack_3c0 <=
              *(float *)(iGpffff86b4 + 0x3f14) / 2.0 -
              *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0))) &&
            (-*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 +
             *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) <= fStack_3b8)) &&
           (fStack_3b8 <=
            *(float *)(iGpffff86b4 + 0x3f1c) / 2.0 -
            *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0))) {
          for (iVar8 = 0; iVar8 < 0xc; iVar8 = iVar8 + 1) {
            if ((((*(byte *)(iGpffff86b4 + iVar8 * 0x4f0 + 0xb0) & 1) != 0) &&
                ((long)((ulong)*(byte *)(iGpffff86b4 + iVar8 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
               ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar8 * 0x4f0 + 0xb2) << 0x3d) &&
                ((0 < *(short *)(iGpffff86b4 + iVar8 * 0x4f0 + 0x124) &&
                 ((*(byte *)(iGpffff86b4 + iVar8 * 0x4f0 + 0xb4) & 1) !=
                  (*(byte *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb4) & 1))))))) {
              auVar24 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar8 * 0x4f0 + 0x160));
              auVar26._4_4_ = fStack_3bc;
              auVar26._0_4_ = fStack_3c0;
              auVar26._8_4_ = fStack_3b8;
              auVar26._12_4_ = uStack_3b4;
              auVar25 = _lqc2(auVar26);
              auVar24 = _vsub(auVar24,auVar25);
              auStack_470 = _sqc2(auVar24);
              __ct__7FVectorFRC7FVector(auStack_430,auStack_470);
              fStack_3b0 = auStack_430._0_4_;
              fStack_3a8 = fStack_428;
              uStack_3a4 = uStack_424;
              fStack_3ac = 0.0;
              fVar23 = (float)Length__7FVectorCFv(&fStack_3b0);
              if (fVar23 < *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) +
                           *(float *)(iGpffff86b4 + iVar8 * 0x4f0 + 0x3b0) + 3.0) break;
            }
          }
          if (0xb < iVar8) {
            lVar20 = 0;
            while (lVar20 < *(char *)(iGpffff86b4 + 0x45c0)) {
              iVar8 = (int)lVar20;
              auVar24 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar8 * 0x4f0 + 0x160));
              auVar3._4_4_ = fStack_3bc;
              auVar3._0_4_ = fStack_3c0;
              auVar3._8_4_ = fStack_3b8;
              auVar3._12_4_ = uStack_3b4;
              auVar25 = _lqc2(auVar3);
              auVar24 = _vsub(auVar24,auVar25);
              auStack_480 = _sqc2(auVar24);
              __ct__7FVectorFRC7FVector(auStack_440,auStack_480);
              fStack_3b0 = auStack_440._0_4_;
              fStack_3a8 = fStack_438;
              uStack_3a4 = uStack_434;
              fStack_3ac = 0.0;
              fVar23 = (float)Length__7FVectorCFv(&fStack_3b0);
              if (fVar23 < *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) +
                           *(float *)(iGpffff86b4 + iVar8 * 0x4f0 + 0x3b0) + 3.0) break;
              lVar20 = (long)(iVar8 + 1);
            }
            if (*(char *)(iGpffff86b4 + 0x45c0) <= lVar20) {
              asStack_280[iVar6 * 4] = (short)(int)fStack_3c0;
              asStack_280[iVar6 * 4 + 1] = 0;
              asStack_280[iVar6 * 4 + 2] = (short)(int)fStack_3b8;
              asStack_280[iVar6 * 4 + 3] = 1;
              iVar6 = iVar6 + 1;
            }
          }
        }
      }
      if (iVar6 != 0) {
        iVar8 = rand();
        iVar8 = iVar8 % iVar6;
        lVar21 = (long)iVar8;
        if (iVar6 == 0) {
          trap(7);
        }
        fStack_390 = (float)(int)asStack_280[iVar8 * 4];
        fStack_38c = (float)(int)asStack_280[iVar8 * 4 + 1];
        fStack_388 = (float)(int)asStack_280[iVar8 * 4 + 2];
        uStack_384 = 0x3f800000;
        fVar22 = *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x154);
        iVar6 = iGpffff86b4 + param_2 * 0x4f0;
        *(float *)(iVar6 + 0x160) = fStack_390;
        *(float *)(iVar6 + 0x164) = fStack_38c;
        *(float *)(iVar6 + 0x168) = fStack_388;
        *(undefined4 *)(iVar6 + 0x16c) = 0x3f800000;
        auVar5._4_4_ = fStack_38c;
        auVar5._0_4_ = fStack_390;
        auVar5._8_4_ = fStack_388;
        auVar5._12_4_ = 0x3f800000;
        auVar24 = _lqc2(auVar5);
        auVar25 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + param_2 * 0x4f0 + 0x390));
        auVar24 = _vsub(auVar24,auVar25);
        auStack_490 = _sqc2(auVar24);
        __ct__7FVectorFRC7FVector(auStack_450,auStack_490);
        iVar6 = iGpffff86b4 + param_2 * 0x4f0;
        *(int *)(iVar6 + 0x150) = auStack_450._0_4_;
        *(int *)(iVar6 + 0x154) = auStack_450._4_4_;
        *(undefined4 *)(iVar6 + 0x158) = uStack_448;
        *(undefined4 *)(iVar6 + 0x15c) = uStack_444;
        *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x154) = fVar22;
        if ((fVar22 == 0.0) &&
           ((*(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8) < '\x16' ||
            ('&' < *(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8))))) {
          iVar6 = iGpffff86b4 + param_2 * 0x4f0;
          *(byte *)(iVar6 + 0xb1) = *(byte *)(iVar6 + 0xb1) & 0xef | 0x10;
        }
        *(undefined2 *)(iGpffff86b4 + *(char *)(iGpffff86b4 + 0x45c0) * 2 + 0x45d4) = uVar14;
        *(char *)(iGpffff86b4 + 0x45c0) = *(char *)(iGpffff86b4 + 0x45c0) + '\x01';
      }
    }
  }
  __ct__7FVectorFRC7FVector(param_1,&fStack_390);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e6be0  CharacterTargetMove__Fiifb
 * C++: CharacterTargetMove(int, int, float, bool)
 * size: 0x578 bytes
 * --------------------------------------------------------------------------- */
undefined4
CharacterTargetMove__Fiifb(float param_1,undefined8 param_2,undefined8 param_3,char param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  auStack_10._4_4_ = in_zero_hi;
  auStack_10._0_4_ = in_zero_lo;
  auStack_10._8_4_ = in_zero_udw;
  auStack_10._12_4_ = in_register_0000000c;
  iVar4 = (int)param_2;
  if (*(char *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb8) != '\n') {
    iVar1 = (int)param_3;
    if (param_4 == '\x01') {
      FindAdjacentEffectPos__7CBattleFiifP7FVector(param_1,iGpffff86b4,param_2,param_3,auStack_10);
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar1 * 0x4f0 + 0x150));
      auVar9 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar1 * 0x4f0 + 0x350));
      auVar8 = _vadd(auVar8,auVar9);
      auStack_90 = _sqc2(auVar8);
      __ct__7FVectorFRC7FVector(&uStack_40,auStack_90);
      uStack_30 = (undefined4)uStack_40;
      uStack_2c = (undefined4)((ulong)uStack_40 >> 0x20);
      uStack_28 = uStack_38;
      uStack_24 = uStack_34;
      fVar5 = *(float *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x360);
      fVar6 = *(float *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x368);
      fVar7 = *(float *)(iGpffff86b4 + iVar4 * 0x4f0 + 0x3b0);
      auVar8._8_4_ = uStack_38;
      auVar8._0_8_ = uStack_40;
      auVar8._12_4_ = uStack_34;
      auVar9 = _lqc2(auVar8);
      auVar8 = _lqc2(auStack_10);
      auVar8 = _vsub(auVar8,auVar9);
      auVar8 = _sqc2(auVar8);
      auStack_10._8_8_ = auVar8._8_8_;
      auStack_10._0_4_ = auVar8._0_4_;
      auStack_10._4_4_ = 0;
      Normalize__7FVectorFv(auStack_10);
      __amu__7FVectorFf(param_1 + fVar7 + (fVar5 + fVar6) / 2.0,auStack_10);
      auVar9._4_4_ = uStack_2c;
      auVar9._0_4_ = uStack_30;
      auVar9._8_4_ = uStack_28;
      auVar9._12_4_ = uStack_24;
      auVar9 = _lqc2(auVar9);
      auVar8 = _lqc2(auStack_10);
      auVar8 = _vadd(auVar8,auVar9);
      auVar8 = _sqc2(auVar8);
      auStack_10._8_8_ = auVar8._8_8_;
      auStack_10._0_4_ = auVar8._0_4_;
      auStack_10._4_4_ = 0;
      auVar9 = auStack_10;
      iVar1 = iGpffff86b4 + iVar4 * 0x4f0;
      auStack_10._8_4_ = auVar8._8_4_;
      auStack_10._12_4_ = auVar8._12_4_;
      *(undefined4 *)(iVar1 + 0x160) = auStack_10._0_4_;
      *(undefined4 *)(iVar1 + 0x164) = 0;
      *(undefined4 *)(iVar1 + 0x168) = auStack_10._8_4_;
      *(undefined4 *)(iVar1 + 0x16c) = auStack_10._12_4_;
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar4 * 0x4f0 + 0x160));
      auVar10 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar4 * 0x4f0 + 0x390));
      auVar8 = _vsub(auVar8,auVar10);
      auStack_a0 = _sqc2(auVar8);
      auStack_10 = auVar9;
      __ct__7FVectorFRC7FVector(auStack_50,auStack_a0);
      iVar1 = iGpffff86b4 + iVar4 * 0x4f0;
      *(int *)(iVar1 + 0x150) = auStack_50._0_4_;
      *(int *)(iVar1 + 0x154) = auStack_50._4_4_;
      *(undefined4 *)(iVar1 + 0x158) = uStack_48;
      *(undefined4 *)(iVar1 + 0x15c) = uStack_44;
      *(undefined4 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0x154) = 0;
      SetTargetAngle__7CBattleFii(iGpffff86b4,param_2,param_3);
      return 1;
    }
    *(undefined1 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb8) = 10;
    *(undefined1 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb9) = 0;
    *(int *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xbc) = iVar1;
    *(undefined4 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xc4) = 0;
    *(float *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xdc) = param_1;
    auStack_10 = *(undefined1 (*) [16])(iGpffff86b4 + iVar4 * 0x4f0 + 0x160);
    auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar4 * 0x4f0 + 0x150));
    auVar9 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar4 * 0x4f0 + 0x390));
    auVar8 = _vadd(auVar8,auVar9);
    auStack_b0 = _sqc2(auVar8);
    __ct__7FVectorFRC7FVector(auStack_60,auStack_b0);
    auVar9 = _lqc2(auStack_60);
    auVar8 = _lqc2(auStack_10);
    auVar8 = _vsub(auVar8,auVar9);
    auStack_10 = _sqc2(auVar8);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_80,auStack_10);
    Get3DAngle__F7FVector(auStack_70,uVar3);
    uStack_20 = auStack_70._0_4_;
    fStack_1c = auStack_70._4_4_;
    uStack_18 = uStack_68;
    uStack_14 = uStack_64;
    ChangeBtlChrAngle__7CBattleFif(180.0 - fStack_1c,iGpffff86b4,param_2);
  }
  if (*(char *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb9) == '\x02') {
    *(undefined1 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb8) = 7;
    *(undefined1 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xb9) = 1;
    uVar2 = 1;
  }
  else {
    if (param_4 == '\x01') {
      *(undefined4 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0xc4) = 1;
    }
    uVar2 = 0;
  }
  return uVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e7160  SetForceDeath__Fi
 * C++: SetForceDeath(int)
 * size: 0x298 bytes
 * --------------------------------------------------------------------------- */
void SetForceDeath__Fi(int param_1)

{
  pCGpffff86b4->aChr[param_1].bFlagsB = pCGpffff86b4->aChr[param_1].bFlagsB & 0xf7 | 8;
  pCGpffff86b4->aChr[param_1].bState = 0x2a;
  pCGpffff86b4->aChr[param_1].bState2 = 2;
  pCGpffff86b4->aChr[param_1].nHp = 0;
  *(undefined2 *)&pCGpffff86b4->aChr[param_1].field_0xe2 = 0xffff;
  pCGpffff86b4->aChr[param_1].bFlagsB1 = pCGpffff86b4->aChr[param_1].bFlagsB1 & 0xfe | 1;
  *(undefined4 *)(pCGpffff86b4->aChr[param_1].pModel + 0x4e4) = 0;
  OTRelease__8BtlModelFv(pCGpffff86b4->aChr[param_1].pModel);
  ShadowOff__8BtlModelFv(pCGpffff86b4->aChr[param_1].pModel);
  if ((pCGpffff86b4->aChr[param_1].bFlagsB & 1) == 0) {
    pCGpffff86b4->aChr[param_1].bFlagsA2 = pCGpffff86b4->aChr[param_1].bFlagsA2 & 0xfb | 4;
  }
  else {
    AddTrophy__7CBattleFiP12MONSTERParam
              (pCGpffff86b4,param_1,(MONSTERParam *)pCGpffff86b4->aChr[param_1].pParam);
  }
  pCGpffff86b4->bFlags25 = pCGpffff86b4->bFlags25 & 0xef | 0x10;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e7400  SetCharacterWallHitMode__Fib
 * C++: SetCharacterWallHitMode(int, bool)
 * size: 0xb4 bytes
 * --------------------------------------------------------------------------- */
void SetCharacterWallHitMode__Fib(int param_1,char param_2)

{
  int iVar1;
  
  if (param_2 == '\x01') {
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb5) = *(byte *)(iVar1 + 0xb5) & 0xfd;
  }
  else {
    iVar1 = iGpffff86b4 + param_1 * 0x4f0;
    *(byte *)(iVar1 + 0xb5) = *(byte *)(iVar1 + 0xb5) & 0xfd | 2;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e74c0  BattleNext__Fv
 * C++: BattleNext()
 * size: 0x2c bytes
 * --------------------------------------------------------------------------- */
void BattleNext__Fv(void)

{
  *(byte *)(iGpffff86b4 + 0x25) = *(byte *)(iGpffff86b4 + 0x25) & 0x7f | 0x80;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005e74f0  BattleCheck__Fii
 * C++: BattleCheck(int, int)
 * size: 0x504 bytes
 * --------------------------------------------------------------------------- */
undefined4 BattleCheck__Fii(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 2) {
    if (param_1 == 1) {
      if (*(short *)(iGpffff86b4 + 0x28) != 9) {
        return 0;
      }
      if (*(short *)(iGpffff86b4 + 0x2a) != 2) {
        return 0;
      }
      *(undefined4 *)(iGpffff86b4 + 0x4c) = 1;
    }
    else if (((((param_1 == 0) && ((*(byte *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb0) & 1) != 0)) &&
              ((long)((ulong)*(byte *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
             ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb2) << 0x3d) &&
              (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb0) << 0x3a))))) &&
            ((*(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb8) == '\x1e' &&
             (*(char *)(iGpffff86b4 + param_2 * 0x4f0 + 0xb9) < '\x02')))) {
      return 0;
    }
    return 1;
  }
  iVar1 = 0;
  do {
    if (0xb < iVar1) {
      return 0;
    }
    if (((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d))) &&
       (((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb4) & 1) != 0 &&
        (0 < *(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x124))))) {
      iVar2 = 0;
      while ((iVar2 < 0x20 &&
             (((*(char *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar2 * 0xc + 0x1bc) != 'G' ||
               (((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar2 * 0xc + 0x1b9) & 0x1f) >> 2 !=
                0)) || ((*(uint *)(iGpffff86b4 + iVar1 * 0x4f0 + iVar2 * 0xc + 0x1c0) & 0x20) == 0))
             ))) {
        iVar2 = iVar2 + 1;
      }
      if (0x1f < iVar2) {
        if ((param_2 == 0) && (*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x18c) == 500)) {
          return 1;
        }
        if ((param_2 == 1) && (*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x18c) == 0x1f5)) {
          return 1;
        }
        if ((param_2 == 2) && (*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x18c) == 0x1f6)) {
          return 1;
        }
      }
    }
    iVar1 = iVar1 + 1;
  } while( true );
}

