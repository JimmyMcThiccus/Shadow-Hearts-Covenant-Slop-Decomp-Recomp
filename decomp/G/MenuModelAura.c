/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: MenuModelAura   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/MenuModelAura.md).
 */

/* JP: 0x004999f0  MenuModelAura::MenuModelAura()   [__ct__13MenuModelAuraFv]  size=0x11c */
int __ct__13MenuModelAuraFv(int param_1)

{
  __ct__16MenuModelManegerFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__13MenuModelAura;
  __construct_array(param_1 + 0x70,0x498fe0,0x499190,0x14,2);
  __construct_array(param_1 + 0x98,0x499240,0x499290,0x18,2);
  __construct_array(param_1 + 200,0x291a90,0x291ae0,0x18,3);
  *(undefined1 *)(param_1 + 0x1b8) = 0;
  *(undefined1 *)(param_1 + 0x1b9) = 0;
  *(undefined1 *)(param_1 + 0x1ba) = 0;
  *(undefined1 *)(param_1 + 0x1bb) = 0;
  memset(param_1 + 0x140,0,0x28);
  memset(param_1 + 0x118,0,0x28);
  memset(param_1 + 0x168,0,0x50);
  return param_1;
}

/* JP: 0x00499b10  MenuModelAura::~MenuModelAura()   [__dt__13MenuModelAuraFv]  size=0xd4 */
int __dt__13MenuModelAuraFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__13MenuModelAura;
    __destroy_arr(param_1 + 200,0x291ae0,0x18,3);
    __destroy_arr(param_1 + 0x98,0x499290,0x18,2);
    __destroy_arr(param_1 + 0x70,0x499190,0x14,2);
    __dt__16MenuModelManegerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00499bf0  MenuModelAura::CreateAura(MenuModelManeger*, MenuAuraData*)   [CreateAura__13MenuModelAuraFP16MenuModelManegerP12MenuAuraData]  size=0x70c */
void CreateAura__13MenuModelAuraFP16MenuModelManegerP12MenuAuraData
               (int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [4];
  undefined1 auStack_bc [4];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [4];
  undefined4 uStack_8c;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [4];
  undefined1 auStack_6c [4];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined1 uStack_58;
  undefined1 uStack_57;
  undefined1 uStack_56;
  undefined1 uStack_55;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined1 auStack_44 [4];
  undefined1 auStack_40 [4];
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  undefined4 uStack_34;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iVar1 = *(int *)(param_2 + 0x18);
  iStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  Create__16MenuModelManegerFPCc(param_1,0);
  Reset__16MenuModelManegerFv(iStack_30);
  Access__16MenuModelManegerFv(iStack_30);
  for (uVar7 = 0; uVar7 < 5; uVar7 = uVar7 + 1 & 0xffff) {
    iVar5 = *(int *)(iVar1 + uVar7 * 4 + 0x3c);
    if (iVar5 != 0) {
      uStack_48 = *(undefined4 *)(iVar5 + 4);
      *(undefined4 *)(iStack_30 + uVar7 * 4 + 0x48) = uStack_48;
    }
  }
  iVar5 = *(int *)(iStack_30 + 0x18);
  *(undefined2 *)(iVar5 + 0x6c) = 2;
  *(undefined2 *)(iVar5 + 0x6e) = 2;
  *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(iVar1 + 0x10);
  *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(iVar1 + 0x14);
  uStack_50 = *(undefined4 *)(*(int *)(iVar1 + 0x20) + 0x4b8);
  uStack_4c = uStack_50;
  SetAngle__9MenuModelFf(uStack_50,*(undefined4 *)(iVar5 + 0x20));
  *(undefined1 *)(iStack_30 + 0x47) = 7;
  *(byte *)(iStack_30 + 0x47) = *(byte *)(iStack_30 + 0x47) & 0xfb;
  *(byte *)(iStack_30 + 0x47) = *(byte *)(iStack_30 + 0x47) & 0xfe;
  *(byte *)(iStack_30 + 0x46) = *(byte *)(iStack_30 + 0x46) & 0xfd;
  uStack_34 = *(undefined4 *)(*(int *)(iVar1 + 0x20) + 0x30);
  uVar3 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_f0);
  __as__7FVectorFRC7FVector(auStack_a0,uVar3);
  uVar3 = __ct__7FVectorFffff(0,0xbf000000,0,0x3f800000,auStack_100);
  __as__7FVectorFRC7FVector(auStack_90,uVar3);
  uVar3 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_110);
  __as__7FVectorFRC7FVector(auStack_80,uVar3);
  uVar3 = __ct__7_rgba32FUcUcUcUc(auStack_38,0xff,0xff,0xff,0xff);
  __as__7_rgba32FRC7_rgba32(auStack_70,uVar3);
  uVar3 = __ct__7_rgba32FUcUcUcUc(auStack_3c,0xff,0xff,0xff,0xff);
  __as__7_rgba32FRC7_rgba32(auStack_6c,uVar3);
  uStack_58 = 0;
  uStack_57 = 0;
  uStack_56 = 10;
  uStack_55 = 0;
  uStack_54 = 0;
  uStack_68 = *(undefined4 *)(iStack_10 + 0x30);
  uStack_64 = *(undefined4 *)(iStack_10 + 0x34);
  uStack_8c = *(undefined4 *)(iStack_10 + 0x38);
  uStack_5c = 0x1e;
  uStack_60 = 4;
  uVar3 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_120);
  __as__7FVectorFRC7FVector(auStack_e0,uVar3);
  uVar3 = __ct__7FVectorFffff(0x42c80000,0xc2c80000,0x42c80000,0x3f800000,auStack_130);
  __as__7FVectorFRC7FVector(auStack_d0,uVar3);
  uVar3 = __ct__7_rgba32FUcUcUcUc(auStack_40,0xdc,0xdc,0xff,0x78);
  __as__7_rgba32FRC7_rgba32(auStack_c0,uVar3);
  uVar3 = __ct__7_rgba32FUcUcUcUc(auStack_44,0,0,200,0x50);
  __as__7_rgba32FRC7_rgba32(auStack_bc,uVar3);
  uStack_b0 = 0x42700000;
  uStack_a4 = 0;
  uStack_a8 = 0;
  uStack_b8 = 0x3dcccccd;
  uStack_b4 = 0x3e4ccccd;
  uStack_ac = 0x10;
  memcpy(auStack_c0,iStack_10 + 0x2c,4);
  memcpy(auStack_bc,iStack_10 + 0x2c,4);
  uVar8 = 0;
  while ((long)uVar8 < (long)*(char *)(iStack_10 + 0x28)) {
    iVar1 = (int)uVar8;
    uVar2 = searchFrame__5FrameFPCc(uStack_34,*(undefined4 *)(iStack_10 + iVar1 * 4));
    *(undefined4 *)(iStack_30 + iVar1 * 4 + 0x118) = uVar2;
    lVar4 = __nw__FUi(0x100);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__7FpSmokeFv(lVar4);
    }
    iVar5 = (int)uVar3;
    (**(code **)(*(int *)(iVar5 + 0x10) + 0x2c))(uVar3,8);
    (**(code **)(*(int *)(iVar5 + 0x10) + 0x30))(uVar3,0);
    CreateEffect__7FpSmokeFP12FpSmokeParam(uVar3,auStack_a0);
    SetRegAlpha__6FpPrimFUl(uVar3,0x48);
    (**(code **)(*(int *)(iVar5 + 0x10) + 0x3c))
              (uVar3,*(undefined1 *)(iStack_10 + 0x2c),*(undefined1 *)(iStack_10 + 0x2d),
               *(undefined1 *)(iStack_10 + 0x2e),*(undefined1 *)(iStack_10 + 0x2f));
    (**(code **)(*(int *)(iVar5 + 0x10) + 0x40))
              (uVar3,*(undefined1 *)(iStack_10 + 0x2c),*(undefined1 *)(iStack_10 + 0x2d),
               *(undefined1 *)(iStack_10 + 0x2e),*(undefined1 *)(iStack_10 + 0x2f));
    (**(code **)(*(int *)(iVar5 + 0x10) + 0x38))(uVar3,0);
    lVar4 = __nw__FUi(0x70);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__9FpThunderFv(lVar4);
    }
    iVar6 = (int)uVar3;
    (**(code **)(*(int *)(iVar6 + 0x10) + 0x2c))(uVar3,7);
    (**(code **)(*(int *)(iVar6 + 0x10) + 0x30))(uVar3,0);
    CreateEffect__9FpThunderFP14FpThunderParam(uVar3,auStack_e0);
    (**(code **)(*(int *)(iVar6 + 0x10) + 0x38))(uVar3,0);
    *(int *)(iStack_30 + iVar1 * 4 + 0x140) = iVar5;
    *(int *)(iStack_30 + iVar1 * 8 + 0x168) = iVar6;
    uVar8 = (long)(iVar1 + 1) & 0xffff;
  }
  *(int *)(iStack_30 + 0x110) = iStack_20;
  *(int *)(iStack_30 + 0x114) = iStack_10;
  return;
}

/* JP: 0x0049a3c0  MenuModelAura::Boot()   [Boot__13MenuModelAuraFv]  size=0x234 */
void Boot__13MenuModelAuraFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iVar1 = *(int *)(param_1 + 0x18);
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  iStack_10 = param_1;
  Order__13MenuModelPackFv(iVar1);
  *(undefined2 *)(iStack_10 + 0x6a) = 1;
  uVar2 = *(undefined4 *)(iVar1 + 0x20);
  if (*(int *)(iVar1 + 0x28) != 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0x28);
  }
  if (*(int *)(iVar1 + 0x2c) != 0) {
    uVar2 = *(undefined4 *)(iVar1 + 0x2c);
  }
  AddOTBefor__5WorldFP8VIF1PrimP8VIF1Prim(0x42bf10,*(undefined4 *)(iVar1 + 0x20),iStack_10 + 0x70);
  AddOTAfter__5WorldFP8VIF1PrimP8VIF1Prim(0x42bf10,uVar2,iStack_10 + 0x98);
  for (uVar3 = 0; uVar3 < 10; uVar3 = uVar3 + 1 & 0xffff) {
    if ((*(int *)(iStack_10 + uVar3 * 4 + 0x140) != 0) &&
       (*(int *)(iStack_10 + uVar3 * 4 + 0x118) != 0)) {
      getWorldPos__5FrameFi(auStack_30,*(undefined4 *)(iStack_10 + uVar3 * 4 + 0x118),m_Env__8VIF1Prim & 1);
      iVar1 = *(int *)(iStack_10 + uVar3 * 4 + 0x140);
      (**(code **)(*(int *)(iVar1 + 0x10) + 0x48))(iVar1,auStack_30,1);
      iVar1 = *(int *)(iStack_10 + uVar3 * 4 + 0x140);
      (**(code **)(*(int *)(iVar1 + 0x10) + 0x34))(0x3f800000,iVar1,0);
    }
    if (*(int *)(iStack_10 + uVar3 * 8 + 0x168) != 0) {
      iVar1 = *(int *)(iStack_10 + uVar3 * 8 + 0x168);
      (**(code **)(*(int *)(iVar1 + 0x10) + 0x34))(0x3f800000,iVar1,0);
    }
  }
  *(undefined1 *)(iStack_10 + 0x1ba) = 1;
  *(undefined1 *)(iStack_10 + 0x1bb) = 1;
  return;
}

/* JP: 0x0049a600  MenuModelAura::Standby(unsigned char)   [Standby__13MenuModelAuraFUc]  size=0x150 */
void Standby__13MenuModelAuraFUc(int param_1,char param_2)

{
  uint uVar1;
  
  Standby__13MenuModelPackFv(*(undefined4 *)(param_1 + 0x18));
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1 + 0x98);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1 + 0x70);
  for (uVar1 = 0; uVar1 < 10; uVar1 = uVar1 + 1 & 0xffff) {
    if (param_2 != '\0') {
      if (*(int *)(param_1 + uVar1 * 4 + 0x140) != 0) {
        Delete__8PutiPrimFv(*(undefined4 *)(param_1 + uVar1 * 4 + 0x140));
        *(undefined4 *)(param_1 + uVar1 * 4 + 0x140) = 0;
      }
      if (*(int *)(param_1 + uVar1 * 8 + 0x168) != 0) {
        Delete__8PutiPrimFv(*(undefined4 *)(param_1 + uVar1 * 8 + 0x168));
        *(undefined4 *)(param_1 + uVar1 * 8 + 0x168) = 0;
      }
    }
  }
  *(undefined1 *)(param_1 + 0x1ba) = 0;
  *(undefined1 *)(param_1 + 0x1bb) = 0;
  *(char *)(param_1 + 0x1b9) = param_2;
  return;
}

/* JP: 0x0049a750  MenuModelAura::Close()   [Close__13MenuModelAuraFv]  size=0x38 */
void Close__13MenuModelAuraFv(int param_1)

{
  EnableAlpha__13MenuModelPackFv(*(undefined4 *)(param_1 + 0x18));
  *(undefined2 *)(param_1 + 0x6a) = 2;
  return;
}

/* JP: 0x0049a790  MenuModelAura::CloseEffect()   [CloseEffect__13MenuModelAuraFv]  size=0xe4 */
void CloseEffect__13MenuModelAuraFv(int param_1)

{
  int iVar1;
  uint uVar2;
  
  for (uVar2 = 0; uVar2 < 10; uVar2 = uVar2 + 1 & 0xffff) {
    if (*(int *)(param_1 + uVar2 * 4 + 0x140) != 0) {
      iVar1 = *(int *)(param_1 + uVar2 * 4 + 0x140);
      (**(code **)(*(int *)(iVar1 + 0x10) + 0x34))(0,iVar1,0x100);
    }
    if (*(int *)(param_1 + uVar2 * 8 + 0x168) != 0) {
      iVar1 = *(int *)(param_1 + uVar2 * 8 + 0x168);
      (**(code **)(*(int *)(iVar1 + 0x10) + 0x34))(0,iVar1,0x100);
    }
  }
  *(undefined1 *)(param_1 + 0x1bb) = 0;
  return;
}

/* JP: 0x0049a880  MenuModelAura::Polling()   [Polling__13MenuModelAuraFv]  size=0x5f0 */
undefined1 Polling__13MenuModelAuraFv(undefined8 param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined1 uVar6;
  short sVar7;
  int iVar8;
  undefined8 uVar9;
  ulong uVar10;
  undefined8 uVar11;
  char cVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  undefined4 uVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_60;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [8];
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
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uVar6 = Polling__16MenuModelManegerFv(param_1);
  iVar15 = (int)param_1;
  if (*(short *)(iVar15 + 0x6a) == 5) {
    Standby__13MenuModelAuraFUc(param_1,0);
    *(undefined2 *)(iVar15 + 0x6a) = 0;
  }
  if ((*(char *)(iVar15 + 0x1b8) == '\0') && (-1 < (long)((ulong)*(byte *)(iVar15 + 0x47) << 0x3e)))
  {
    iVar8 = *(int *)(iVar15 + 0x18);
    iVar2 = *(int *)(iVar8 + 0x20);
    uVar16 = getSequenceTime__5ModelFQ25Model10MotionKind(*(undefined4 *)(*(int *)(*(int *)(iVar15 + 0x110) + 0x18) + 0x20),0);
    iVar3 = *(int *)(iVar15 + 0x114);
    (**(code **)(*(int *)(iVar2 + 0x10) + 0x2c))(uVar16);
    SetSingleColor__9MenuModelFUcUcUc(iVar2,*(undefined1 *)(iVar3 + 0x2c),*(undefined1 *)(iVar3 + 0x2d),
                    *(undefined1 *)(iVar3 + 0x2e));
    if (*(int *)(iVar8 + 0x28) != 0) {
      iVar2 = *(int *)(iVar8 + 0x28);
      (**(code **)(*(int *)(iVar2 + 0x10) + 0x2c))(uVar16);
      SetSingleColor__9MenuModelFUcUcUc(iVar2,*(undefined1 *)(iVar3 + 0x2c),*(undefined1 *)(iVar3 + 0x2d),
                      *(undefined1 *)(iVar3 + 0x2e));
    }
    if (*(int *)(iVar8 + 0x2c) != 0) {
      iVar8 = *(int *)(iVar8 + 0x2c);
      (**(code **)(*(int *)(iVar8 + 0x10) + 0x2c))(uVar16);
      SetSingleColor__9MenuModelFUcUcUc(iVar8,*(undefined1 *)(iVar3 + 0x2c),*(undefined1 *)(iVar3 + 0x2d),
                      *(undefined1 *)(iVar3 + 0x2e));
    }
    Create__19MenuModelAuraPacketFsUc
              (iVar15 + 0x98,*(undefined1 *)(iVar3 + 0x29),*(undefined1 *)(iVar3 + 0x2f));
    *(undefined1 *)(iVar15 + 0x1b8) = 1;
  }
  if (*(char *)(iVar15 + 0x1ba) != '\0') {
    uStack_30 = in_zero_lo;
    uStack_2c = in_zero_hi;
    uStack_28 = in_zero_udw;
    uStack_24 = in_register_0000000c;
    uStack_20 = in_zero_lo;
    uStack_1c = in_zero_hi;
    uStack_18 = in_zero_udw;
    uStack_14 = in_register_0000000c;
    uVar9 = searchFrame__5FrameFPCc(*(undefined4 *)(*(int *)(*(int *)(iVar15 + 0x18) + 0x20) + 0x30),
                            0x555970);
    getWorldPos__5FrameFi(auStack_40,uVar9,m_Env__8VIF1Prim & 1);
    uStack_10 = auStack_40._0_4_;
    uStack_c = auStack_40._4_4_;
    uStack_8 = uStack_38;
    uStack_4 = uStack_34;
    Run__19MenuModelAuraPacketFv(iVar15 + 0x98);
    if (-1 < *(short *)(*(int *)(iVar15 + 0x114) + 0x2a)) {
      *(undefined1 *)
       (*(int *)(*(int *)(*(int *)(*(int *)(iVar15 + 0x18) + 0x20) + 0x48) +
                *(short *)(*(int *)(iVar15 + 0x114) + 0x2a) * 4) + 0x2b3) = 0;
    }
    if (*(char *)(iVar15 + 0x1bb) != '\0') {
      for (uVar13 = 0; uVar13 < 10; uVar13 = uVar13 + 1 & 0xffff) {
        if ((*(int *)(iVar15 + uVar13 * 4 + 0x118) != 0) &&
           (*(int *)(iVar15 + uVar13 * 4 + 0x140) != 0)) {
          getWorldPos__5FrameFi(auStack_50,*(undefined4 *)(iVar15 + uVar13 * 4 + 0x118),m_Env__8VIF1Prim & 1);
          iVar8 = *(int *)(iVar15 + uVar13 * 4 + 0x140);
          (**(code **)(*(int *)(iVar8 + 0x10) + 0x48))(iVar8,auStack_50,0);
        }
      }
      piVar14 = (int *)(iVar15 + 0x168);
      for (uVar13 = 0; uVar13 < 10; uVar13 = uVar13 + 1 & 0xffff) {
        if (*piVar14 != 0) {
          cVar12 = *(char *)(*piVar14 + 0x68);
          sVar7 = (short)piVar14[1] + -1;
          *(short *)(piVar14 + 1) = sVar7;
          if (sVar7 < 0) {
            cVar12 = cVar12 != '\x01';
            (**(code **)(*(int *)(*piVar14 + 0x10) + 0x38))(*piVar14,cVar12);
            uVar10 = rand();
            sVar7 = (short)(uVar10 & 7);
            if (((long)uVar10 < 0) && ((uVar10 & 7) != 0)) {
              sVar7 = sVar7 + -8;
            }
            *(short *)(piVar14 + 1) = sVar7;
            if ((bool)cVar12) {
              iVar8 = rand();
              getWorldPos__5FrameFi(&uStack_60,*(undefined4 *)(iVar15 + uVar13 * 4 + 0x118),
                              m_Env__8VIF1Prim & 1);
              uStack_20 = (undefined4)uStack_60;
              uStack_1c = (undefined4)((ulong)uStack_60 >> 0x20);
              uStack_18 = uStack_58;
              uStack_14 = uStack_54;
              auVar18._8_4_ = uStack_58;
              auVar18._0_8_ = uStack_60;
              auVar18._12_4_ = uStack_54;
              auVar17 = _lqc2(auVar18);
              auVar5._4_4_ = uStack_c;
              auVar5._0_4_ = uStack_10;
              auVar5._8_4_ = uStack_8;
              auVar5._12_4_ = uStack_4;
              auVar18 = _lqc2(auVar5);
              auVar17 = _vsub(auVar17,auVar18);
              auStack_c0 = _sqc2(auVar17);
              __ct__7FVectorFRC7FVector(auStack_70,auStack_c0);
              uStack_30 = auStack_70._0_4_;
              uStack_2c = auStack_70._4_4_;
              uStack_28 = uStack_68;
              uStack_24 = uStack_64;
              Normalize__7FVectorFv(&uStack_30);
              auVar17._4_4_ = uStack_2c;
              auVar17._0_4_ = uStack_30;
              auVar17._8_4_ = uStack_28;
              auVar17._12_4_ = uStack_24;
              auVar17 = _lqc2(auVar17);
              auVar18 = _qmtc2((float)(iVar8 % 100) / 25.0 + 3.0);
              auVar17 = _vmulbc(auVar17,auVar18);
              auStack_e0 = _sqc2(auVar17);
              __ct__7FVectorFRC7FVector(auStack_90,auStack_e0);
              auVar4._4_4_ = uStack_1c;
              auVar4._0_4_ = uStack_20;
              auVar4._8_4_ = uStack_18;
              auVar4._12_4_ = uStack_14;
              auVar17 = _lqc2(auVar4);
              auVar18 = _lqc2(auStack_90);
              auVar17 = _vadd(auVar17,auVar18);
              auStack_d0 = _sqc2(auVar17);
              __ct__7FVectorFRC7FVector(auStack_80,auStack_d0);
              uStack_30 = auStack_80._0_4_;
              uStack_2c = auStack_80._4_4_;
              uStack_28 = uStack_78;
              uStack_24 = uStack_74;
              uVar9 = __ct__7FVectorFRC7FVector(auStack_a0,&uStack_20);
              uVar11 = __ct__7FVectorFRC7FVector(auStack_b0,&uStack_30);
              SetPos__9FpThunderF7FVector7FVector(*piVar14,uVar9,uVar11);
              *(short *)(piVar14 + 1) = (short)piVar14[1] + 1;
            }
            else {
              *(short *)(piVar14 + 1) = (short)piVar14[1] + 10;
            }
          }
          if (cVar12 != '\0') {
            ChangeForm__9FpThunderFf(0x3f800000,*piVar14);
          }
        }
        piVar14 = piVar14 + 2;
      }
    }
  }
  if ((*(char *)(iVar15 + 0x1b9) != '\0') &&
     (bVar1 = *(byte *)(iVar15 + 0x1b9), *(byte *)(iVar15 + 0x1b9) = bVar1 + 1, 1 < bVar1)) {
    Destroy__16MenuModelManegerFUc(param_1,1);
    *(undefined1 *)(iVar15 + 0x1b9) = 0;
  }
  return uVar6;
}

/* JP: 0x0049ae70  MenuModelAura::Event(MenuModel*, const char*, const char*)   [Event__13MenuModelAuraFP9MenuModelPCcPCc]  size=0x104 */
void Event__13MenuModelAuraFP9MenuModelPCcPCc(int param_1,undefined8 param_2,undefined4 param_3)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  
  lVar2 = strncmp(param_3,0x555978,8);
  if (lVar2 == 0) {
    for (uVar3 = 0; uVar3 < 10; uVar3 = uVar3 + 1 & 0xffff) {
      if (*(int *)(param_1 + uVar3 * 4 + 0x140) != 0) {
        iVar1 = *(int *)(param_1 + uVar3 * 4 + 0x140);
        (**(code **)(*(int *)(iVar1 + 0x10) + 0x38))(iVar1,0);
      }
      if (*(int *)(param_1 + uVar3 * 8 + 0x168) != 0) {
        iVar1 = *(int *)(param_1 + uVar3 * 8 + 0x168);
        (**(code **)(*(int *)(iVar1 + 0x10) + 0x38))(iVar1,0);
      }
    }
    *(undefined1 *)(param_1 + 0x1bb) = 0;
  }
  return;
}
