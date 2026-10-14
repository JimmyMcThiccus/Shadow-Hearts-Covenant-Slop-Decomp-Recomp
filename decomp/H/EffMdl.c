/* decomp/H/EffMdl.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 23 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00519f50  __ct__6EffMdlFPUcPUcfii
 * C++: EffMdl::__ct(uchar *, uchar *, float, int, int)
 * size: 0x37c bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__6EffMdlFPUcPUcfii
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,long param_4,undefined4 param_5,
          undefined4 param_6)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 extraout_v0_udw;
  undefined8 extraout_v0_udw_00;
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined8 uVar3;
  ulong *puVar4;
  int iVar5;
  int iVar6;
  
  __ct__7CPolObjFv(param_2);
  iVar5 = (int)param_2;
  __ct__7ExModelFv(iVar5 + 0x20);
  *(undefined4 *)(iVar5 + 0x14) = 0x409fc0;
  *(undefined4 *)(iVar5 + 0x30) = 0x409fd0;
  *(undefined4 *)(iVar5 + 0x3c) = 0x409fe0;
  *(undefined4 *)(iVar5 + 0x540) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x544) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x548) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x54c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x550) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x554) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x558) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x55c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x560) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x564) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x568) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x56c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x570) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x574) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x578) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x57c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x590) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x594) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x598) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x59c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x5a8) = param_5;
  *(undefined4 *)(iVar5 + 0x5a0) = param_6;
  *(undefined4 *)(iVar5 + 0x5a4) = 0;
  *(undefined4 *)(iVar5 + 0x534) = 0;
  *(undefined4 *)(iVar5 + 0x530) = 0;
  *(undefined4 *)(iVar5 + 0x538) = 0;
  *(undefined4 *)(iVar5 + 0x540) = 0;
  *(undefined4 *)(iVar5 + 0x544) = 0;
  *(undefined4 *)(iVar5 + 0x548) = 0;
  *(undefined4 *)(iVar5 + 0x54c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x550) = 0;
  *(undefined4 *)(iVar5 + 0x554) = 0;
  *(undefined4 *)(iVar5 + 0x558) = 0;
  *(undefined4 *)(iVar5 + 0x55c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x560) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x564) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x568) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x56c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x580) = param_1;
  *(undefined4 *)(iVar5 + 0x584) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x590) = 0x60000000;
  *(undefined4 *)(iVar5 + 0x594) = 0;
  *(undefined4 *)(iVar5 + 0x598) = 0;
  *(undefined4 *)(iVar5 + 0x59c) = 0;
  *(undefined4 *)(iVar5 + 0x5ac) = 0;
  *(undefined4 *)(iVar5 + 0x5b0) = 0;
  *(undefined4 *)(iVar5 + 0x5b8) = 0;
  *(undefined4 *)(iVar5 + 0x5b4) = 0xffffffff;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  create__7ExModelFPUc(iVar5 + 0x20,param_3);
  calcMatrix__7ExModelFP6Matrix(iVar5 + 0x20,0);
  uVar3 = extraout_v0_udw;
  if (param_4 != 0) {
    createMotion__5ModelFPUc(iVar5 + 0x20,param_4);
    uVar3 = extraout_v0_udw_00;
  }
  if ((((*(int *)(iVar5 + 0x5a0) == 9) || (*(int *)(iVar5 + 0x5a0) == 10)) ||
      (*(int *)(iVar5 + 0x5a0) == 0xb)) || (*(int *)(iVar5 + 0x5a0) == 0xc)) {
    for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)(*(int *)(iVar5 + 0x84) + 4); iVar6 = iVar6 + 1) {
      puVar4 = (ulong *)(*(int *)(*(int *)(iVar5 + 0x6c) + iVar6 * 0x4c + 0x18) + 0x80);
      auVar1._8_8_ = uVar3;
      auVar1._0_8_ = 0xfffffffffffeffff;
      auVar2._4_4_ = in_zero_hi;
      auVar2._0_4_ = in_zero_lo;
      auVar2._8_4_ = in_zero_udw;
      auVar2._12_4_ = in_register_0000000c;
      auVar2 = _pcpyld(auVar2,auVar1);
      uVar3 = auVar2._8_8_;
      *puVar4 = *puVar4 & auVar2._0_8_;
    }
  }
  if (*(int *)(iVar5 + 0x5a0) == 0xd) {
    for (iVar6 = 0; iVar6 < (int)(uint)*(ushort *)(*(int *)(iVar5 + 0x84) + 4); iVar6 = iVar6 + 1) {
      changeGSAlpha__7TextureFiiiii(*(int *)(iVar5 + 0x6c) + iVar6 * 0x4c,0,2,0,1,0);
    }
    SetAlpha2__6EffMdlFf(0,param_2);
  }
  EffMdlEntry__7CBattleFP6EffMdl(uGpffff86b4,param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051a2d0  __dt__6EffMdlFv
 * C++: EffMdl::__dt()
 * size: 0xe0 bytes
 * --------------------------------------------------------------------------- */
int __dt__6EffMdlFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409fc0;
    *(undefined4 *)(param_1 + 0x30) = 0x409fd0;
    *(undefined4 *)(param_1 + 0x3c) = 0x409fe0;
    if ((*(int *)(param_1 + 0x5b8) != 0) && (*(int *)(param_1 + 0x5b8) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x5b8) + -0x10);
    }
    __dt__7ExModelFv(param_1 + 0x20,0);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051a3b0  DeleteSetUp__6EffMdlFv
 * C++: EffMdl::DeleteSetUp()
 * size: 0x2e8 bytes
 * --------------------------------------------------------------------------- */
void DeleteSetUp__6EffMdlFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x5a0);
  if (iVar1 == 0xd) {
    if (*(int *)(param_1 + 0x5b8) != 0) {
      for (iVar1 = 0;
          iVar1 < (int)(uint)*(ushort *)
                              (*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(param_1 + 0x5a8) * 0x4f0 + 0x144)
                                                + 0x52c) + 100) + 4); iVar1 = iVar1 + 1) {
        **(undefined4 **)
          (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x5a8) * 0x4f0 + 0x144) +
                            0x52c) + 0x4c) + iVar1 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_1 + 0x5b8) + iVar1 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x5a8) * 0x4f0 +
                                             0x144) + 0x52c) + 0x4c) + iVar1 * 0x4c) + 0xf4) =
             *(undefined4 *)(*(int *)(param_1 + 0x5b8) + iVar1 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x5a8) * 0x4f0 +
                                             0x144) + 0x52c) + 0x4c) + iVar1 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_1 + 0x5b8) + iVar1 * 0x410 + 0x400);
      }
    }
  }
  else if ((((iVar1 == 6) || (iVar1 == 4)) || (iVar1 == 3)) && (*(int *)(param_1 + 0x5a4) != 0)) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x5ac));
  }
  DeleteSetUp__5ModelFv(param_1 + 0x20);
  OTRelease__6EffMdlFv(param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x3c) + 0xc))();
  EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051a6a0  Polling__6EffMdlFv
 * C++: EffMdl::Polling()
 * size: 0x1a84 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__6EffMdlFv(undefined8 param_1)

{
  ushort uVar1;
  uint uVar2;
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
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 uVar20;
  undefined4 uVar21;
  float fVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  int iVar25;
  byte *pbVar26;
  undefined8 *puVar27;
  undefined1 (*pauVar28) [16];
  int iVar29;
  int iVar30;
  float fVar31;
  float fVar32;
  undefined1 in_vf0 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [8];
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  undefined1 auStack_3a0 [8];
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined1 auStack_390 [8];
  undefined4 uStack_388;
  undefined4 uStack_384;
  undefined1 auStack_380 [8];
  undefined4 uStack_378;
  undefined4 uStack_374;
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [8];
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [8];
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined4 uStack_290;
  float fStack_28c;
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [8];
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined4 uStack_270;
  float fStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [8];
  undefined4 uStack_258;
  undefined4 uStack_254;
  float afStack_250 [2];
  undefined4 uStack_248;
  undefined4 uStack_244;
  float afStack_240 [2];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined4 uStack_230;
  undefined4 uStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [16];
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  float afStack_190 [35];
  undefined4 uStack_104;
  float fStack_100;
  float fStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
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
  float fStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar33 = _vmr32(in_vf0);
  auVar34 = _vmr32(auVar33);
  auVar35 = _vmr32(auVar34);
  auStack_1a0 = _sqc2(in_vf0);
  auStack_1b0 = _sqc2(auVar33);
  auStack_1c0 = _sqc2(auVar34);
  auStack_1d0 = _sqc2(auVar35);
  iVar30 = (int)param_1;
  fVar32 = *(float *)(iGpffff86b4 + 0x38) * *(float *)(iVar30 + 0x580);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar32 = 0.0;
  }
  afStack_190[0] = in_zero_lo;
  afStack_190[1] = in_zero_hi;
  afStack_190[2] = (float)in_zero_udw;
  afStack_190[3] = (float)in_register_0000000c;
  afStack_190[4] = in_zero_lo;
  afStack_190[5] = in_zero_hi;
  afStack_190[6] = (float)in_zero_udw;
  afStack_190[7] = (float)in_register_0000000c;
  afStack_190[8] = in_zero_lo;
  afStack_190[9] = in_zero_hi;
  afStack_190[10] = (float)in_zero_udw;
  afStack_190[0xb] = (float)in_register_0000000c;
  fStack_90 = in_zero_lo;
  fStack_8c = in_zero_hi;
  uStack_88 = in_zero_udw;
  uStack_84 = in_register_0000000c;
  fStack_80 = in_zero_lo;
  fStack_7c = in_zero_hi;
  uStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  uStack_68 = in_zero_udw;
  uStack_64 = in_register_0000000c;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  switch(*(undefined4 *)(iVar30 + 0x5a0)) {
  case 3:
    if (*(int *)(iVar30 + 0x5a4) != 1) {
      if (*(int *)(iVar30 + 0x5a4) != 0) break;
      uStack_1f0 = 0x3f000000;
      uStack_1ec = 0x3f000000;
      uStack_1e8 = 0x3f800000;
      uStack_1e4 = 0x3f800000;
      uVar20 = __ct__7FVectorFRC7FVector(auStack_1e0,iVar30 + 0x540);
      uVar21 = CreatePoint__12LightControlF7FVector7FVector(uVar20,&uStack_1f0);
      *(undefined4 *)(iVar30 + 0x5ac) = uVar21;
      changeShadowFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      changeInterFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      *(undefined4 *)(iVar30 + 0x5a4) = 1;
    }
    if ((long)((ulong)*(byte *)(iVar30 + 0x538) << 0x3e) < 0) {
      changeStrength__12LightControlFif(0,*(undefined4 *)(iVar30 + 0x5ac));
    }
    else {
      fVar22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(iVar30 + 0x20,0);
      fVar31 = 1.0;
      if (0.5 <= fVar22) {
        fVar31 = 1.0 - (fVar22 - 0.5) * 2.0;
      }
      if (fVar31 < 0.0) {
        fVar31 = 0.0;
      }
      changeStrength__12LightControlFif(fVar31 * 8.0,*(undefined4 *)(iVar30 + 0x5ac));
    }
    break;
  case 4:
    if (*(int *)(iVar30 + 0x5a4) != 1) {
      if (*(int *)(iVar30 + 0x5a4) != 0) break;
      uStack_210 = 0x3f800000;
      uStack_20c = 0x3f000000;
      uStack_208 = 0x3f000000;
      uStack_204 = 0x3f800000;
      uVar20 = __ct__7FVectorFRC7FVector(auStack_200,iVar30 + 0x540);
      uVar21 = CreatePoint__12LightControlF7FVector7FVector(uVar20,&uStack_210);
      *(undefined4 *)(iVar30 + 0x5ac) = uVar21;
      changeShadowFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      changeInterFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      *(undefined4 *)(iVar30 + 0x5a4) = 1;
    }
    if ((long)((ulong)*(byte *)(iVar30 + 0x538) << 0x3e) < 0) {
      changeStrength__12LightControlFif(0,*(undefined4 *)(iVar30 + 0x5ac));
    }
    else {
      fVar22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(iVar30 + 0x20,0);
      fVar31 = 1.0;
      if (0.5 <= fVar22) {
        fVar31 = 1.0 - (fVar22 - 0.5) * 2.0;
      }
      if (fVar31 < 0.0) {
        fVar31 = 0.0;
      }
      changeStrength__12LightControlFif(fVar31 * 8.0,*(undefined4 *)(iVar30 + 0x5ac));
    }
    break;
  case 5:
    *(float *)(iVar30 + 0x584) = *(float *)(iVar30 + 0x584) - fVar32 * 3.0;
    if (*(float *)(iVar30 + 0x584) <= 0.0) {
      DeleteSetUp__5ModelFv(iVar30 + 0x20);
      OTRelease__6EffMdlFv(param_1);
      (**(code **)(*(int *)(iVar30 + 0x3c) + 0xc))();
      EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,param_1);
      return 1;
    }
    *(undefined4 *)(iVar30 + 0x510) = *(undefined4 *)(iVar30 + 0x584);
    break;
  case 6:
    if (*(int *)(iVar30 + 0x5a4) == 1) {
      changeStrength__12LightControlFif(0,*(undefined4 *)(iVar30 + 0x5ac));
    }
    else if (*(int *)(iVar30 + 0x5a4) == 0) {
      uStack_230 = 0x3f800000;
      uStack_22c = 0x3f800000;
      uStack_228 = 0x3f4ccccd;
      uStack_224 = 0x3f800000;
      uVar20 = __ct__7FVectorFRC7FVector(auStack_220,iVar30 + 0x540);
      uVar21 = CreatePoint__12LightControlF7FVector7FVector(uVar20,&uStack_230);
      *(undefined4 *)(iVar30 + 0x5ac) = uVar21;
      changeShadowFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      changeStrength__12LightControlFif(0x41000000,*(undefined4 *)(iVar30 + 0x5ac));
      changeInterFlg__12LightControlFib(*(undefined4 *)(iVar30 + 0x5ac),0);
      *(undefined4 *)(iVar30 + 0x5a4) = 1;
    }
    break;
  case 7:
    *(float *)(iVar30 + 0x53c) = *(float *)(iVar30 + 0x53c) + fVar32;
    for (iVar29 = 0; iVar29 < 0xc; iVar29 = iVar29 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb2) << 0x3d) &&
          (((*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb4) & 1) == 0 &&
           (*(short *)(iGpffff86b4 + iVar29 * 0x4f0 + 0x120) == 3)))))) {
        auVar33 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar29 * 0x4f0 + 0x150));
        auVar34 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar29 * 0x4f0 + 0x390));
        auVar33 = _vadd(auVar33,auVar34);
        auStack_3d0 = _sqc2(auVar33);
        __ct__7FVectorFRC7FVector(afStack_240,auStack_3d0);
        fStack_10 = afStack_240[0];
        uStack_8 = uStack_238;
        uStack_4 = uStack_234;
        fStack_c = -0.2;
        SetPos__6EffMdlFP7FVector(param_1,&fStack_10);
        *(undefined4 *)(iVar30 + 0x584) =
             *(undefined4 *)(*(int *)(iGpffff86b4 + iVar29 * 0x4f0 + 0x144) + 0x4ec);
        if (-1 < (long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar29 * 0x4f0 + 0x144) + 0x4b0) <<
                       0x3e)) {
          *(undefined4 *)(iVar30 + 0x584) = 0;
        }
        SetAlpha__6EffMdlFf(*(undefined4 *)(iVar30 + 0x584),param_1);
        break;
      }
    }
    if ((*(short *)(iGpffff86b4 + 0x3ef0) < 0) && (0.5 <= *(float *)(iVar30 + 0x53c))) {
      *(undefined4 *)(iVar30 + 0x5a0) = 8;
      *(undefined4 *)(iVar30 + 0x53c) = 0x3f800000;
    }
    break;
  case 8:
    *(float *)(iVar30 + 0x53c) = *(float *)(iVar30 + 0x53c) - fVar32;
    if (*(float *)(iVar30 + 0x53c) <= 0.0) {
      DeleteSetUp__5ModelFv(iVar30 + 0x20);
      OTRelease__6EffMdlFv(param_1);
      (**(code **)(*(int *)(iVar30 + 0x3c) + 0xc))();
      EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,param_1);
      return 1;
    }
    for (iVar29 = 0; iVar29 < 0xc; iVar29 = iVar29 + 1) {
      if (((((*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb0) & 1) != 0) &&
           ((long)((ulong)*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
          (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb2) << 0x3d))) &&
         (((*(byte *)(iGpffff86b4 + iVar29 * 0x4f0 + 0xb4) & 1) == 0 &&
          (*(short *)(iGpffff86b4 + iVar29 * 0x4f0 + 0x120) == 3)))) {
        auVar33 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar29 * 0x4f0 + 0x150));
        auVar34 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar29 * 0x4f0 + 0x390));
        auVar33 = _vadd(auVar33,auVar34);
        auStack_3e0 = _sqc2(auVar33);
        __ct__7FVectorFRC7FVector(afStack_250,auStack_3e0);
        fStack_10 = afStack_250[0];
        uStack_8 = uStack_248;
        uStack_4 = uStack_244;
        fStack_c = -0.2;
        SetPos__6EffMdlFP7FVector(param_1,&fStack_10);
        *(float *)(iVar30 + 0x584) =
             *(float *)(*(int *)(iGpffff86b4 + iVar29 * 0x4f0 + 0x144) + 0x4ec) *
             *(float *)(iVar30 + 0x53c);
        SetAlpha__6EffMdlFf(*(undefined4 *)(iVar30 + 0x584),param_1);
        break;
      }
    }
    break;
  case 9:
    auVar33 = _lqc2(*(undefined1 (*) [16])
                     (iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x45af) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x45af)
                      ) * 0x10 + 0x150));
    auVar34 = _lqc2(*(undefined1 (*) [16])
                     (iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x45af) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x45af)
                      ) * 0x10 + 0x350));
    auVar33 = _vadd(auVar33,auVar34);
    auStack_3f0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_260,auStack_3f0);
    fStack_10 = auStack_260._0_4_;
    fStack_c = auStack_260._4_4_;
    uStack_8 = uStack_258;
    uStack_4 = uStack_254;
    SetPos__6EffMdlFP7FVector(param_1,&fStack_10);
    fStack_26c = (float)GetRad(180.0 - *(float *)(iGpffff86b4 +
                                                           (*(char *)(iGpffff86b4 + 0x45af) * 0x50 -
                                                           (int)*(char *)(iGpffff86b4 + 0x45af)) *
                                                           0x10 + 0x174));
    uStack_270 = 0;
    uStack_268 = 0;
    uStack_264 = 0x3f800000;
    fStack_10 = 0.0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    fStack_c = fStack_26c;
    SetAngle__6EffMdlFP7FVector(param_1,&fStack_10);
    break;
  case 0xb:
    auVar33 = _lqc2(*(undefined1 (*) [16])
                     (iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x45b7) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x45b7)
                      ) * 0x10 + 0x150));
    auVar34 = _lqc2(*(undefined1 (*) [16])
                     (iGpffff86b4 +
                      (*(char *)(iGpffff86b4 + 0x45b7) * 0x50 - (int)*(char *)(iGpffff86b4 + 0x45b7)
                      ) * 0x10 + 0x350));
    auVar33 = _vadd(auVar33,auVar34);
    auStack_400 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_280,auStack_400);
    fStack_10 = auStack_280._0_4_;
    fStack_c = auStack_280._4_4_;
    uStack_8 = uStack_278;
    uStack_4 = uStack_274;
    SetPos__6EffMdlFP7FVector(param_1,&fStack_10);
    fStack_28c = (float)GetRad(180.0 - *(float *)(iGpffff86b4 +
                                                           (*(char *)(iGpffff86b4 + 0x45b7) * 0x50 -
                                                           (int)*(char *)(iGpffff86b4 + 0x45b7)) *
                                                           0x10 + 0x174));
    uStack_290 = 0;
    uStack_288 = 0;
    uStack_284 = 0x3f800000;
    fStack_10 = 0.0;
    uStack_8 = 0;
    uStack_4 = 0x3f800000;
    fStack_c = fStack_28c;
    SetAngle__6EffMdlFP7FVector(param_1,&fStack_10);
    break;
  case 0xd:
    iVar29 = *(int *)(iVar30 + 0x5a4);
    afStack_190[0x20] = in_zero_lo;
    afStack_190[0x21] = in_zero_hi;
    afStack_190[0x22] = (float)in_zero_udw;
    uStack_104 = in_register_0000000c;
    fStack_100 = in_zero_lo;
    fStack_fc = in_zero_hi;
    uStack_f8 = in_zero_udw;
    uStack_f4 = in_register_0000000c;
    fStack_f0 = in_zero_lo;
    fStack_ec = in_zero_hi;
    uStack_e8 = in_zero_udw;
    uStack_e4 = in_register_0000000c;
    fStack_e0 = in_zero_lo;
    fStack_dc = in_zero_hi;
    uStack_d8 = in_zero_udw;
    uStack_d4 = in_register_0000000c;
    fStack_d0 = in_zero_lo;
    fStack_cc = in_zero_hi;
    uStack_c8 = in_zero_udw;
    uStack_c4 = in_register_0000000c;
    fStack_c0 = in_zero_lo;
    fStack_bc = in_zero_hi;
    uStack_b8 = in_zero_udw;
    uStack_b4 = in_register_0000000c;
    fStack_b0 = in_zero_lo;
    fStack_ac = in_zero_hi;
    uStack_a8 = in_zero_udw;
    uStack_a4 = in_register_0000000c;
    fStack_a0 = in_zero_lo;
    fStack_9c = in_zero_hi;
    uStack_98 = in_zero_udw;
    uStack_94 = in_register_0000000c;
    fStack_60 = in_zero_lo;
    fStack_5c = in_zero_hi;
    uStack_58 = in_zero_udw;
    uStack_54 = in_register_0000000c;
    fStack_50 = in_zero_lo;
    fStack_4c = in_zero_hi;
    uStack_48 = in_zero_udw;
    uStack_44 = in_register_0000000c;
    fStack_40 = in_zero_lo;
    fStack_3c = in_zero_hi;
    uStack_38 = in_zero_udw;
    uStack_34 = in_register_0000000c;
    fStack_30 = in_zero_lo;
    fStack_2c = in_zero_hi;
    uStack_28 = in_zero_udw;
    uStack_24 = in_register_0000000c;
    fStack_20 = in_zero_lo;
    fStack_1c = in_zero_hi;
    uStack_18 = in_zero_udw;
    uStack_14 = in_register_0000000c;
    if (iVar29 == 2) {
      *(undefined4 *)(iVar30 + 0x584) = 0x3f800000;
    }
    else {
      if (iVar29 != 1) {
        if (iVar29 != 0) goto code_r0x0051b8a0;
        uVar1 = *(ushort *)
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144)
                                   + 0x52c) + 100) + 4);
        uVar20 = __nwa__FUi((uint)uVar1 * 0x410 + 0x10);
        uVar21 = __construct_new_array(uVar20,0x51c130,0,0x410,uVar1);
        *(undefined4 *)(iVar30 + 0x5b8) = uVar21;
        for (iVar29 = 0;
            iVar29 < (int)(uint)*(ushort *)
                                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                             *(int *)(iVar30 + 0x5a8) * 0x4f0 +
                                                            0x144) + 0x52c) + 100) + 4);
            iVar29 = iVar29 + 1) {
          *(undefined4 *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + 0x400) =
               **(undefined4 **)
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x4c) + iVar29 * 0x4c + 0xc);
          for (iVar25 = 0;
              iVar25 < *(int *)(*(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                                    *(int *)(iVar30 + 0x5a8) * 0x4f0
                                                                   + 0x144) + 0x52c) + 0x4c) +
                                         iVar29 * 0x4c + 0xc) + 4); iVar25 = iVar25 + 1) {
            uVar2 = ((uint)*(byte *)(*(int *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + 0x400) +
                                     iVar25 * 4 + 2) +
                    (uint)*(byte *)(*(int *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + 0x400) +
                                   iVar25 * 4) +
                    (uint)*(byte *)(*(int *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + 0x400) +
                                    iVar25 * 4 + 1)) / 3;
            *(char *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + iVar25 * 4) =
                 (char)((uVar2 * *(byte *)(*(int *)(iVar30 + 0x5b4) * 0xc + 0x652b68)) / 0xff);
            *(char *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + iVar25 * 4 + 1) =
                 (char)((uVar2 * *(byte *)(*(int *)(iVar30 + 0x5b4) * 0xc + 0x652b69)) / 0xff);
            *(char *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + iVar25 * 4 + 2) =
                 (char)((uVar2 * *(byte *)(*(int *)(iVar30 + 0x5b4) * 0xc + 0x652b6a)) / 0xff);
            *(undefined1 *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + iVar25 * 4 + 3) =
                 *(undefined1 *)
                  (*(int *)(*(int *)(iVar30 + 0x5b8) + iVar29 * 0x410 + 0x400) + iVar25 * 4 + 3);
          }
          **(int **)(*(int *)(iVar30 + 0x6c) + iVar29 * 0x4c + 0xc) =
               *(int *)(iVar30 + 0x5b8) + iVar29 * 0x410;
          *(int *)(*(int *)(*(int *)(iVar30 + 0x6c) + iVar29 * 0x4c) + 0xf4) =
               *(int *)(iVar30 + 0x5b8) + iVar29 * 0x410;
          *(int *)(*(int *)(*(int *)(iVar30 + 0x6c) + iVar29 * 0x4c + 4) + 0xf4) =
               *(int *)(iVar30 + 0x5b8) + iVar29 * 0x410;
        }
        *(undefined4 *)(iVar30 + 0x5a4) = 1;
      }
      *(float *)(iVar30 + 0x584) = *(float *)(iVar30 + 0x584) + fVar32;
      if (1.0 <= *(float *)(iVar30 + 0x584)) {
        *(undefined4 *)(iVar30 + 0x584) = 0x3f800000;
        *(undefined4 *)(iVar30 + 0x5a4) = 2;
      }
    }
code_r0x0051b8a0:
    *(float *)(iVar30 + 0x584) =
         *(float *)(iVar30 + 0x584) *
         *(float *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144) + 0x4e4) *
         *(float *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144) + 0x4ec);
    *(float *)(iVar30 + 0x5b0) = *(float *)(iVar30 + 0x5b0) + fVar32 * 6.2831855 * 0.75;
    if (3.1415927 <= *(float *)(iVar30 + 0x5b0)) {
      *(float *)(iVar30 + 0x5b0) = *(float *)(iVar30 + 0x5b0) - 6.2831855;
    }
    fVar31 = (float)sinf(*(undefined4 *)(iVar30 + 0x5b0));
    *(float *)(iVar30 + 0x584) = *(float *)(iVar30 + 0x584) * ((fVar31 + 3.0) / 3.0);
    if (*(float *)(iVar30 + 0x584) < 0.0) {
      *(undefined4 *)(iVar30 + 0x584) = 0;
    }
    SetAlpha2__6EffMdlFf(*(undefined4 *)(iVar30 + 0x584),param_1);
    pbVar26 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 +
                                                 0x144) + 0x52c) + 0xe4) + 0x110);
    pauVar28 = (undefined1 (*) [16])
               (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144) +
                                 0x52c) + 0x30) + (uint)*pbVar26 * 0x1f0 + (bGpffff8340 & 1) * 0x40)
    ;
    auStack_1d0 = *pauVar28;
    auStack_1c0 = pauVar28[1];
    auStack_1b0 = pauVar28[2];
    auStack_1a0 = pauVar28[3];
    for (iVar29 = 0; iVar29 < 8; iVar29 = iVar29 + 1) {
      uVar20 = *(undefined8 *)(pbVar26 + iVar29 * 0x10 + 0x10);
      fVar31 = *(float *)(pbVar26 + iVar29 * 0x10 + 0x18);
      fVar22 = *(float *)(pbVar26 + iVar29 * 0x10 + 0x1c);
      afStack_190[iVar29 * 4] = (float)uVar20;
      afStack_190[iVar29 * 4 + 1] = (float)((ulong)uVar20 >> 0x20);
      afStack_190[iVar29 * 4 + 2] = fVar31;
      afStack_190[iVar29 * 4 + 3] = fVar22;
    }
    RotTransVector(&fStack_90,afStack_190,auStack_1d0,8);
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x560),auStack_1d0);
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x564),auStack_1c0);
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x568),auStack_1b0);
    RotTransVector(afStack_190 + 0x20,afStack_190,auStack_1d0,8);
    auVar12._4_4_ = fStack_8c;
    auVar12._0_4_ = fStack_90;
    auVar12._8_4_ = uStack_88;
    auVar12._12_4_ = uStack_84;
    auVar33 = _lqc2(auVar12);
    auVar13._4_4_ = fStack_7c;
    auVar13._0_4_ = fStack_80;
    auVar13._8_4_ = uStack_78;
    auVar13._12_4_ = uStack_74;
    auVar34 = _lqc2(auVar13);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_460 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_300,auStack_460);
    auVar33 = _lqc2(auStack_300);
    auVar14._4_4_ = fStack_6c;
    auVar14._0_4_ = fStack_70;
    auVar14._8_4_ = uStack_68;
    auVar14._12_4_ = uStack_64;
    auVar34 = _lqc2(auVar14);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_470 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2f0,auStack_470);
    auVar33 = _lqc2(auStack_2f0);
    auVar15._4_4_ = fStack_5c;
    auVar15._0_4_ = fStack_60;
    auVar15._8_4_ = uStack_58;
    auVar15._12_4_ = uStack_54;
    auVar34 = _lqc2(auVar15);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_480 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2e0,auStack_480);
    auVar33 = _lqc2(auStack_2e0);
    auVar16._4_4_ = fStack_4c;
    auVar16._0_4_ = fStack_50;
    auVar16._8_4_ = uStack_48;
    auVar16._12_4_ = uStack_44;
    auVar34 = _lqc2(auVar16);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_490 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2d0,auStack_490);
    auVar33 = _lqc2(auStack_2d0);
    auVar17._4_4_ = fStack_3c;
    auVar17._0_4_ = fStack_40;
    auVar17._8_4_ = uStack_38;
    auVar17._12_4_ = uStack_34;
    auVar34 = _lqc2(auVar17);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4a0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2c0,auStack_4a0);
    auVar33 = _lqc2(auStack_2c0);
    auVar18._4_4_ = fStack_2c;
    auVar18._0_4_ = fStack_30;
    auVar18._8_4_ = uStack_28;
    auVar18._12_4_ = uStack_24;
    auVar34 = _lqc2(auVar18);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4b0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2b0,auStack_4b0);
    auVar33 = _lqc2(auStack_2b0);
    auVar19._4_4_ = fStack_1c;
    auVar19._0_4_ = fStack_20;
    auVar19._8_4_ = uStack_18;
    auVar19._12_4_ = uStack_14;
    auVar34 = _lqc2(auVar19);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_410 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_2a0,auStack_410);
    afStack_190[0] = auStack_2a0._0_4_;
    afStack_190[1] = auStack_2a0._4_4_;
    afStack_190[2] = (float)uStack_298;
    afStack_190[3] = (float)uStack_294;
    __adv__7FVectorFf(0x41000000,afStack_190);
    auVar4._4_4_ = afStack_190[0x21];
    auVar4._0_4_ = afStack_190[0x20];
    auVar4._8_4_ = afStack_190[0x22];
    auVar4._12_4_ = uStack_104;
    auVar33 = _lqc2(auVar4);
    auVar5._4_4_ = fStack_fc;
    auVar5._0_4_ = fStack_100;
    auVar5._8_4_ = uStack_f8;
    auVar5._12_4_ = uStack_f4;
    auVar34 = _lqc2(auVar5);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4c0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_370,auStack_4c0);
    auVar33 = _lqc2(auStack_370);
    auVar6._4_4_ = fStack_ec;
    auVar6._0_4_ = fStack_f0;
    auVar6._8_4_ = uStack_e8;
    auVar6._12_4_ = uStack_e4;
    auVar34 = _lqc2(auVar6);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4d0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_360,auStack_4d0);
    auVar33 = _lqc2(auStack_360);
    auVar7._4_4_ = fStack_dc;
    auVar7._0_4_ = fStack_e0;
    auVar7._8_4_ = uStack_d8;
    auVar7._12_4_ = uStack_d4;
    auVar34 = _lqc2(auVar7);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4e0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_350,auStack_4e0);
    auVar33 = _lqc2(auStack_350);
    auVar8._4_4_ = fStack_cc;
    auVar8._0_4_ = fStack_d0;
    auVar8._8_4_ = uStack_c8;
    auVar8._12_4_ = uStack_c4;
    auVar34 = _lqc2(auVar8);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_4f0 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_340,auStack_4f0);
    auVar33 = _lqc2(auStack_340);
    auVar9._4_4_ = fStack_bc;
    auVar9._0_4_ = fStack_c0;
    auVar9._8_4_ = uStack_b8;
    auVar9._12_4_ = uStack_b4;
    auVar34 = _lqc2(auVar9);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_500 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_330,auStack_500);
    auVar33 = _lqc2(auStack_330);
    auVar10._4_4_ = fStack_ac;
    auVar10._0_4_ = fStack_b0;
    auVar10._8_4_ = uStack_a8;
    auVar10._12_4_ = uStack_a4;
    auVar34 = _lqc2(auVar10);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_510 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_320,auStack_510);
    auVar33 = _lqc2(auStack_320);
    auVar11._4_4_ = fStack_9c;
    auVar11._0_4_ = fStack_a0;
    auVar11._8_4_ = uStack_98;
    auVar11._12_4_ = uStack_94;
    auVar34 = _lqc2(auVar11);
    auVar33 = _vadd(auVar33,auVar34);
    auStack_420 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_310,auStack_420);
    afStack_190[4] = auStack_310._0_4_;
    afStack_190[5] = auStack_310._4_4_;
    afStack_190[6] = (float)uStack_308;
    afStack_190[7] = (float)uStack_304;
    __adv__7FVectorFf(0x41000000,afStack_190 + 4);
    auVar34._4_4_ = afStack_190[1];
    auVar34._0_4_ = afStack_190[0];
    auVar34._8_4_ = afStack_190[2];
    auVar34._12_4_ = afStack_190[3];
    auVar33 = _lqc2(auVar34);
    auVar35._4_4_ = afStack_190[5];
    auVar35._0_4_ = afStack_190[4];
    auVar35._8_4_ = afStack_190[6];
    auVar35._12_4_ = afStack_190[7];
    auVar34 = _lqc2(auVar35);
    auVar33 = _vsub(auVar33,auVar34);
    auStack_430 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_380,auStack_430);
    afStack_190[8] = auStack_380._0_4_;
    afStack_190[9] = auStack_380._4_4_;
    afStack_190[10] = (float)uStack_378;
    afStack_190[0xb] = (float)uStack_374;
    puVar27 = (undefined8 *)
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x144) +
                                0x52c) + 0x30) + (bGpffff8340 & 1) * 0x40);
    iVar29 = *(int *)(iVar30 + 0x50);
    uVar20 = *puVar27;
    uVar21 = *(undefined4 *)(puVar27 + 1);
    uVar23 = *(undefined4 *)((int)puVar27 + 0xc);
    *(int *)(iVar29 + 0x160) = (int)uVar20;
    *(int *)(iVar29 + 0x164) = (int)((ulong)uVar20 >> 0x20);
    *(undefined4 *)(iVar29 + 0x168) = uVar21;
    *(undefined4 *)(iVar29 + 0x16c) = uVar23;
    uVar21 = *(undefined4 *)((int)puVar27 + 0x14);
    uVar23 = *(undefined4 *)(puVar27 + 3);
    uVar24 = *(undefined4 *)((int)puVar27 + 0x1c);
    *(undefined4 *)(iVar29 + 0x170) = *(undefined4 *)(puVar27 + 2);
    *(undefined4 *)(iVar29 + 0x174) = uVar21;
    *(undefined4 *)(iVar29 + 0x178) = uVar23;
    *(undefined4 *)(iVar29 + 0x17c) = uVar24;
    uVar21 = *(undefined4 *)((int)puVar27 + 0x24);
    uVar23 = *(undefined4 *)(puVar27 + 5);
    uVar24 = *(undefined4 *)((int)puVar27 + 0x2c);
    *(undefined4 *)(iVar29 + 0x180) = *(undefined4 *)(puVar27 + 4);
    *(undefined4 *)(iVar29 + 0x184) = uVar21;
    *(undefined4 *)(iVar29 + 0x188) = uVar23;
    *(undefined4 *)(iVar29 + 0x18c) = uVar24;
    uVar21 = *(undefined4 *)((int)puVar27 + 0x34);
    uVar23 = *(undefined4 *)(puVar27 + 7);
    uVar24 = *(undefined4 *)((int)puVar27 + 0x3c);
    *(undefined4 *)(iVar29 + 400) = *(undefined4 *)(puVar27 + 6);
    *(undefined4 *)(iVar29 + 0x194) = uVar21;
    *(undefined4 *)(iVar29 + 0x198) = uVar23;
    *(undefined4 *)(iVar29 + 0x19c) = uVar24;
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x560),*(int *)(iVar30 + 0x50) + 0x160);
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x564),*(int *)(iVar30 + 0x50) + 0x170);
    __amu__7FVectorFf(*(undefined4 *)(iVar30 + 0x568),*(int *)(iVar30 + 0x50) + 0x180);
    pauVar28 = (undefined1 (*) [16])(*(int *)(iVar30 + 0x50) + 400);
    auVar3._4_4_ = afStack_190[9];
    auVar3._0_4_ = afStack_190[8];
    auVar3._8_4_ = afStack_190[10];
    auVar3._12_4_ = afStack_190[0xb];
    auVar34 = _lqc2(auVar3);
    auVar33 = _lqc2(*pauVar28);
    auVar33 = _vadd(auVar33,auVar34);
    auVar33 = _sqc2(auVar33);
    *pauVar28 = auVar33;
    myMatrixUpdate__5FrameFv(*(undefined4 *)(iVar30 + 0x50));
    break;
  case 0xe:
    auVar33 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x150));
    auVar34 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x350));
    auVar33 = _vadd(auVar33,auVar34);
    auStack_440 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_390,auStack_440);
    fStack_90 = auStack_390._0_4_;
    uStack_88 = uStack_388;
    uStack_84 = uStack_384;
    fStack_8c = auStack_390._4_4_ -
                (*(float *)(iGpffff86b4 + *(int *)(iVar30 + 0x5a8) * 0x4f0 + 0x364) + 8.0);
    auVar34 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
    auVar33._4_4_ = fStack_8c;
    auVar33._0_4_ = fStack_90;
    auVar33._8_4_ = uStack_388;
    auVar33._12_4_ = uStack_384;
    auVar33 = _lqc2(auVar33);
    auVar33 = _vsub(auVar34,auVar33);
    auStack_450 = _sqc2(auVar33);
    __ct__7FVectorFRC7FVector(auStack_3a0,auStack_450);
    fStack_80 = auStack_3a0._0_4_;
    fStack_7c = auStack_3a0._4_4_;
    uStack_78 = uStack_398;
    uStack_74 = uStack_394;
    uVar20 = __ct__7FVectorFRC7FVector(auStack_3c0,&fStack_80);
    Get3DAngleRad__F7FVector(auStack_3b0,uVar20);
    fStack_80 = auStack_3b0._0_4_;
    fStack_6c = auStack_3b0._4_4_;
    uStack_68 = uStack_3a8;
    uStack_64 = uStack_3a4;
    fStack_7c = -fStack_6c;
    uStack_78 = 0;
    fStack_70 = fStack_80;
    SetPosAngle__6EffMdlFP7FVectorP7FVector(param_1,&fStack_90,&fStack_80);
  }
  (**(code **)(*(int *)(iVar30 + 0x30) + 0x2c))(fVar32);
  calcMatrix__7ExModelFP6Matrix(iVar30 + 0x20,0);
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c170  TranseCallBack__6EffMdlFRC7FVector7FVector
 * C++: EffMdl::TranseCallBack(FVector *, FVector)
 * size: 0xb0 bytes
 * --------------------------------------------------------------------------- */
void TranseCallBack__6EffMdlFRC7FVector7FVector
               (undefined8 param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined1 (*pauVar2) [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_2 + 0x560));
  pauVar2 = (undefined1 (*) [16])param_4;
  auVar3 = _lqc2(*pauVar2);
  auVar3 = _vmul(auVar3,auVar4);
  auVar3 = _sqc2(auVar3);
  *pauVar2 = auVar3;
  uVar1 = __ct__7FVectorFRC7FVector(auStack_20,param_4);
  TranseCallBack__7ExModelFRC7FVector7FVector(auStack_10,param_2 + 0x20,param_3,uVar1);
  *(int *)*pauVar2 = auStack_10._0_4_;
  *(int *)(*pauVar2 + 4) = auStack_10._4_4_;
  *(undefined4 *)(*pauVar2 + 8) = uStack_8;
  *(undefined4 *)(*pauVar2 + 0xc) = uStack_4;
  *(int *)(param_2 + 0x540) = (int)*(undefined8 *)(param_2 + 0x4e0);
  *(int *)(param_2 + 0x544) = (int)((ulong)*(undefined8 *)(param_2 + 0x4e0) >> 0x20);
  *(undefined4 *)(param_2 + 0x548) = *(undefined4 *)(param_2 + 0x4e8);
  *(undefined4 *)(param_2 + 0x54c) = *(undefined4 *)(param_2 + 0x4ec);
  __ct__7FVectorFRC7FVector(param_1,param_4);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c220  MotionEndCallBack__6EffMdlFPCc
 * C++: EffMdl::MotionEndCallBack(char *)
 * size: 0x1e8 bytes
 * --------------------------------------------------------------------------- */
void MotionEndCallBack__6EffMdlFPCc(int param_1,undefined4 param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x5a0);
  if (iVar1 != 0xd) {
    if ((iVar1 == 8) || (iVar1 == 7)) {
      lVar2 = strcmp(param_2,0x652d30);
      if (lVar2 == 0) {
        setMotion__7ExModelFPCc(param_1 + 0x20,0x652d38);
      }
    }
    else if (iVar1 != 5) {
      if (((iVar1 == 6) || (iVar1 == 4)) || (iVar1 == 3)) {
        if (*(int *)(param_1 + 0x5a4) != 0) {
          release__12LightControlFi(*(undefined4 *)(param_1 + 0x5ac));
        }
      }
      else {
        if (iVar1 == 2) {
          lVar2 = strcmp(param_2,0x652d30);
          if (lVar2 != 0) {
            return;
          }
          setMotion__7ExModelFPCc(param_1 + 0x20,0x652d38);
          return;
        }
        if (iVar1 == 1) {
          *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x5a8) * 0x4f0 + 0x192) = 0xffff;
        }
      }
      DeleteSetUp__5ModelFv(param_1 + 0x20);
      OTRelease__6EffMdlFv(param_1);
      Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
      (**(code **)(*(int *)(param_1 + 0x3c) + 0xc))();
      EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,param_1);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c410  OTEntry__6EffMdlFii
 * C++: EffMdl::OTEntry(int, int)
 * size: 0x94 bytes
 * --------------------------------------------------------------------------- */
void OTEntry__6EffMdlFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0x538) & 1) == 0) {
    iVar1 = param_1;
    if (param_1 != 0) {
      iVar1 = param_1 + 0x20;
    }
    AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,iVar1);
  }
  *(byte *)(param_1 + 0x538) = *(byte *)(param_1 + 0x538) & 0xfe | 1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c4b0  OTRelease__6EffMdlFv
 * C++: EffMdl::OTRelease()
 * size: 0xa8 bytes
 * --------------------------------------------------------------------------- */
void OTRelease__6EffMdlFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  while( true ) {
    iVar2 = param_1;
    if (param_1 != 0) {
      iVar2 = param_1 + 0x20;
    }
    lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,iVar2);
    if (lVar1 == 0) break;
    iVar2 = param_1;
    if (param_1 != 0) {
      iVar2 = param_1 + 0x20;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar2);
  }
  *(byte *)(param_1 + 0x538) = *(byte *)(param_1 + 0x538) & 0xfe;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c560  SetPos__6EffMdlFP7FVector
 * C++: EffMdl::SetPos(FVector *)
 * size: 0xa0 bytes
 * --------------------------------------------------------------------------- */
void SetPos__6EffMdlFP7FVector(int param_1,undefined8 param_2)

{
  undefined1 (*pauVar1) [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10,param_2);
  *(int *)(param_1 + 0x540) = auStack_10._0_4_;
  *(int *)(param_1 + 0x544) = auStack_10._4_4_;
  *(undefined4 *)(param_1 + 0x548) = uStack_8;
  *(undefined4 *)(param_1 + 0x54c) = uStack_4;
  pauVar1 = (undefined1 (*) [16])(*(int *)(param_1 + 0x50) + 400);
  _lqc2(*pauVar1);
  auVar2 = _lqc2(*(undefined1 (*) [16])param_2);
  auVar2 = _vmove(auVar2);
  auVar2 = _sqc2(auVar2);
  *pauVar1 = auVar2;
  myMatrixUpdate__5FrameFv(*(undefined4 *)(param_1 + 0x50));
  if ((long)((ulong)*(byte *)(param_1 + 0x538) << 0x3d) < 0) {
    SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(param_1 + 0x20,param_1 + 0x540,param_1 + 0x550,param_1 + 0x560);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c600  SetAngle__6EffMdlFP7FVector
 * C++: EffMdl::SetAngle(FVector *)
 * size: 0xb4 bytes
 * --------------------------------------------------------------------------- */
void SetAngle__6EffMdlFP7FVector(int param_1)

{
  int iVar1;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10);
  *(int *)(param_1 + 0x550) = auStack_10._0_4_;
  *(int *)(param_1 + 0x554) = auStack_10._4_4_;
  *(undefined4 *)(param_1 + 0x558) = uStack_8;
  *(undefined4 *)(param_1 + 0x55c) = uStack_4;
  __ct__6MatrixFRC7FVectorRC7FVector(&uStack_50,param_1 + 0x550,param_1 + 0x540);
  iVar1 = *(int *)(param_1 + 0x50);
  *(undefined4 *)(iVar1 + 0x160) = uStack_50;
  *(undefined4 *)(iVar1 + 0x164) = uStack_4c;
  *(undefined4 *)(iVar1 + 0x168) = uStack_48;
  *(undefined4 *)(iVar1 + 0x16c) = uStack_44;
  *(undefined4 *)(iVar1 + 0x170) = uStack_40;
  *(undefined4 *)(iVar1 + 0x174) = uStack_3c;
  *(undefined4 *)(iVar1 + 0x178) = uStack_38;
  *(undefined4 *)(iVar1 + 0x17c) = uStack_34;
  *(undefined4 *)(iVar1 + 0x180) = uStack_30;
  *(undefined4 *)(iVar1 + 0x184) = uStack_2c;
  *(undefined4 *)(iVar1 + 0x188) = uStack_28;
  *(undefined4 *)(iVar1 + 0x18c) = uStack_24;
  *(undefined4 *)(iVar1 + 400) = uStack_20;
  *(undefined4 *)(iVar1 + 0x194) = uStack_1c;
  *(undefined4 *)(iVar1 + 0x198) = uStack_18;
  *(undefined4 *)(iVar1 + 0x19c) = uStack_14;
  myMatrixUpdate__5FrameFv(*(undefined4 *)(param_1 + 0x50));
  if ((long)((ulong)*(byte *)(param_1 + 0x538) << 0x3d) < 0) {
    SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(param_1 + 0x20,param_1 + 0x540,param_1 + 0x550,param_1 + 0x560);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c6c0  SetPosAngle__6EffMdlFP7FVectorP7FVector
 * C++: EffMdl::SetPosAngle(FVector *, FVector *)
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void SetPosAngle__6EffMdlFP7FVectorP7FVector
               (undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iVar1;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFPC7FVector(auStack_10);
  iVar1 = (int)param_1;
  *(int *)(iVar1 + 0x540) = auStack_10._0_4_;
  *(int *)(iVar1 + 0x544) = auStack_10._4_4_;
  *(undefined4 *)(iVar1 + 0x548) = uStack_8;
  *(undefined4 *)(iVar1 + 0x54c) = uStack_4;
  SetAngle__6EffMdlFP7FVector(param_1,param_3);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c720  SetScale__6EffMdlF7FVector
 * C++: EffMdl::SetScale(FVector)
 * size: 0x68 bytes
 * --------------------------------------------------------------------------- */
void SetScale__6EffMdlF7FVector(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1];
  uVar2 = param_2[2];
  uVar3 = param_2[3];
  *(undefined4 *)(param_1 + 0x560) = *param_2;
  *(undefined4 *)(param_1 + 0x564) = uVar1;
  *(undefined4 *)(param_1 + 0x568) = uVar2;
  *(undefined4 *)(param_1 + 0x56c) = uVar3;
  SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(param_1 + 0x20,param_1 + 0x540,param_1 + 0x550,param_1 + 0x560);
  *(byte *)(param_1 + 0x538) = *(byte *)(param_1 + 0x538) & 0xfb | 4;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c790  SetAlpha__6EffMdlFf
 * C++: EffMdl::SetAlpha(float)
 * size: 0x3c bytes
 * --------------------------------------------------------------------------- */
void SetAlpha__6EffMdlFf(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x584) = param_1;
  *(undefined4 *)(param_2 + 0x510) = *(undefined4 *)(param_2 + 0x584);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c7d0  SetAlpha2__6EffMdlFf
 * C++: EffMdl::SetAlpha2(float)
 * size: 0x44 bytes
 * --------------------------------------------------------------------------- */
void SetAlpha2__6EffMdlFf(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x584) = param_1;
  SetAlphaWeight2__7ExModelFf(*(undefined4 *)(param_2 + 0x584),param_2 + 0x20);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c820  DispOn__6EffMdlFv
 * C++: EffMdl::DispOn()
 * size: 0x34 bytes
 * --------------------------------------------------------------------------- */
void DispOn__6EffMdlFv(int param_1)

{
  *(byte *)(param_1 + 0x538) = *(byte *)(param_1 + 0x538) & 0xfd;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c860  DispOff__6EffMdlFv
 * C++: EffMdl::DispOff()
 * size: 0x98 bytes
 * --------------------------------------------------------------------------- */
void DispOff__6EffMdlFv(int param_1)

{
  *(byte *)(param_1 + 0x538) = *(byte *)(param_1 + 0x538) & 0xfd | 2;
  if (((*(int *)(param_1 + 0x5a0) == 3) || (*(int *)(param_1 + 0x5a0) == 4)) ||
     (*(int *)(param_1 + 0x5a0) == 6)) {
    changeStrength__12LightControlFif(0,*(undefined4 *)(param_1 + 0x5ac));
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051c900  getPacket__6EffMdlFv
 * C++: EffMdl::getPacket()
 * size: 0x58 bytes
 * --------------------------------------------------------------------------- */
int getPacket__6EffMdlFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x538) << 0x3e) < 0) {
    param_1 = param_1 + 0x590;
  }
  else {
    param_1 = getPacket__7ExModelFv(param_1 + 0x20);
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b690  @52@__dt__6EffMdlFv
 * C++: @52@__dt__6EffMdlFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _52___dt__6EffMdlFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x34;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x20) = 0x409fc0;
    *(undefined4 *)(param_1 + -4) = 0x409fd0;
    *(undefined4 *)(param_1 + 8) = 0x409fe0;
    if ((*(int *)(param_1 + 0x584) != 0) && (*(int *)(param_1 + 0x584) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x584) + -0x10);
    }
    __dt__7ExModelFv(param_1 + -0x14,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6a0  @32@DeleteSetUp__6EffMdlFv
 * C++: @32@DeleteSetUp__6EffMdlFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
void _32_DeleteSetUp__6EffMdlFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 + -0x20;
  iVar2 = *(int *)(param_1 + 0x580);
  if (iVar2 == 0xd) {
    if (*(int *)(param_1 + 0x598) != 0) {
      for (iVar2 = 0;
          iVar2 < (int)(uint)*(ushort *)
                              (*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(param_1 + 0x588) * 0x4f0 + 0x144)
                                                + 0x52c) + 100) + 4); iVar2 = iVar2 + 1) {
        **(undefined4 **)
          (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x588) * 0x4f0 + 0x144) +
                            0x52c) + 0x4c) + iVar2 * 0x4c + 0xc) =
             *(undefined4 *)(*(int *)(param_1 + 0x598) + iVar2 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x588) * 0x4f0 +
                                             0x144) + 0x52c) + 0x4c) + iVar2 * 0x4c) + 0xf4) =
             *(undefined4 *)(*(int *)(param_1 + 0x598) + iVar2 * 0x410 + 0x400);
        *(undefined4 *)
         (*(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x588) * 0x4f0 +
                                             0x144) + 0x52c) + 0x4c) + iVar2 * 0x4c + 4) + 0xf4) =
             *(undefined4 *)(*(int *)(param_1 + 0x598) + iVar2 * 0x410 + 0x400);
      }
    }
  }
  else if ((((iVar2 == 6) || (iVar2 == 4)) || (iVar2 == 3)) && (*(int *)(param_1 + 0x584) != 0)) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x58c));
  }
  DeleteSetUp__5ModelFv(param_1);
  OTRelease__6EffMdlFv(iVar1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,iVar1);
  (**(code **)(*(int *)(param_1 + 0x1c) + 0xc))();
  EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,iVar1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6b0  @32@MotionEndCallBack__6EffMdlFPCc
 * C++: @32@MotionEndCallBack__6EffMdlFPCc
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
void _32_MotionEndCallBack__6EffMdlFPCc(int param_1,undefined4 param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  iVar3 = param_1 + -0x20;
  iVar1 = *(int *)(param_1 + 0x580);
  if (iVar1 != 0xd) {
    if ((iVar1 == 8) || (iVar1 == 7)) {
      lVar2 = strcmp(param_2,0x652d30);
      if (lVar2 == 0) {
        setMotion__7ExModelFPCc(param_1,0x652d38);
      }
    }
    else if (iVar1 != 5) {
      if (((iVar1 == 6) || (iVar1 == 4)) || (iVar1 == 3)) {
        if (*(int *)(param_1 + 0x584) != 0) {
          release__12LightControlFi(*(undefined4 *)(param_1 + 0x58c));
        }
      }
      else {
        if (iVar1 == 2) {
          lVar2 = strcmp(param_2,0x652d30);
          if (lVar2 != 0) {
            return;
          }
          setMotion__7ExModelFPCc(param_1,0x652d38);
          return;
        }
        if (iVar1 == 1) {
          *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x588) * 0x4f0 + 0x192) = 0xffff;
        }
      }
      DeleteSetUp__5ModelFv(param_1);
      OTRelease__6EffMdlFv(iVar3);
      Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,iVar3);
      (**(code **)(*(int *)(param_1 + 0x1c) + 0xc))();
      EffMdlRelease__7CBattleFP6EffMdl(iGpffff86b4,iVar3);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6c0  @32@getPacket__6EffMdlFv
 * C++: @32@getPacket__6EffMdlFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _32_getPacket__6EffMdlFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x518) << 0x3e) < 0) {
    param_1 = param_1 + 0x570;
  }
  else {
    param_1 = getPacket__7ExModelFv(param_1);
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6d0  @32@TranseCallBack__6EffMdlFRC7FVector7FVector
 * C++: @32@TranseCallBack__6EffMdlFRC7FVector7FVector
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
void _32_TranseCallBack__6EffMdlFRC7FVector7FVector
               (undefined8 param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined1 (*pauVar2) [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_2 + 0x540));
  pauVar2 = (undefined1 (*) [16])param_4;
  auVar3 = _lqc2(*pauVar2);
  auVar3 = _vmul(auVar3,auVar4);
  auVar3 = _sqc2(auVar3);
  *pauVar2 = auVar3;
  uVar1 = __ct__7FVectorFRC7FVector(auStack_20,param_4);
  TranseCallBack__7ExModelFRC7FVector7FVector(auStack_10,param_2,param_3,uVar1);
  *(int *)*pauVar2 = auStack_10._0_4_;
  *(int *)(*pauVar2 + 4) = auStack_10._4_4_;
  *(undefined4 *)(*pauVar2 + 8) = uStack_8;
  *(undefined4 *)(*pauVar2 + 0xc) = uStack_4;
  *(int *)(param_2 + 0x520) = (int)*(undefined8 *)(param_2 + 0x4c0);
  *(int *)(param_2 + 0x524) = (int)((ulong)*(undefined8 *)(param_2 + 0x4c0) >> 0x20);
  *(undefined4 *)(param_2 + 0x528) = *(undefined4 *)(param_2 + 0x4c8);
  *(undefined4 *)(param_2 + 0x52c) = *(undefined4 *)(param_2 + 0x4cc);
  __ct__7FVectorFRC7FVector(param_1,param_4);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6e0  @32@__dt__6EffMdlFv
 * C++: @32@__dt__6EffMdlFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _32___dt__6EffMdlFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x20;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0xc) = 0x409fc0;
    *(undefined4 *)(param_1 + 0x10) = 0x409fd0;
    *(undefined4 *)(param_1 + 0x1c) = 0x409fe0;
    if ((*(int *)(param_1 + 0x598) != 0) && (*(int *)(param_1 + 0x598) != 0)) {
      __dla__FPv(*(int *)(param_1 + 0x598) + -0x10);
    }
    __dt__7ExModelFv(param_1,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

