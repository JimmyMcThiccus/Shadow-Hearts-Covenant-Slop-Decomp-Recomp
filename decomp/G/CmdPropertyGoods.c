/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPropertyGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPropertyGoods.md).
 */

/* JP: 0x0049e200  CmdPropertyGoods::CmdPropertyGoods()   [__ct__16CmdPropertyGoodsFv]  size=0x84 */
int __ct__16CmdPropertyGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdPropertyGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x409544;
  *(undefined4 *)(param_1 + 0x24) = 0x409550;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x0049e290  CmdPropertyGoods::~CmdPropertyGoods()   [__dt__16CmdPropertyGoodsFv]  size=0xec */
int __dt__16CmdPropertyGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdPropertyGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x409544;
    *(undefined4 *)(param_1 + 0x24) = 0x409550;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x4502f0);
      *(undefined4 *)(param_1 + 0x124) = 0;
    }
    __dt__11SendOnLocalFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0049e380  CmdPropertyGoods::CreateScene(CmdPropertyList*, short)   [CreateScene__16CmdPropertyGoodsFP15CmdPropertyLists]  size=0x2d4 */
void CreateScene__16CmdPropertyGoodsFP15CmdPropertyLists
               (int param_1,undefined4 param_2,short param_3)

{
  int iVar1;
  undefined8 uVar2;
  short sVar3;
  float fStack_34;
  
  uVar2 = __nwa__FUi(param_3 * 0x1b0 + 0x10);
  iVar1 = __construct_new_array(uVar2,0x450610,0x4502f0,0x1b0,param_3);
  *(int *)(param_1 + 0x124) = iVar1;
  fStack_34 = 0.0;
  for (sVar3 = 0; sVar3 < param_3; sVar3 = sVar3 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar1 + 0xd0);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0,iVar1 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar1);
    *(undefined2 *)(iVar1 + 0x1c) = 0;
    *(short *)(iVar1 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))(0,fStack_34);
    *(byte *)(iVar1 + 0x21) = *(byte *)(iVar1 + 0x21) & 0xfe | 1;
    fStack_34 = fStack_34 + *(float *)(iVar1 + 0x30);
    iVar1 = iVar1 + 0x1b0;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(*(int *)(param_1 + 0x124) + 0x164) + -1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0x124) + 0x1b0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xb4;
  SetScroll__10MenuWindowFss(param_1,0,0);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0049e660  CmdPropertyGoods::UpdateScene(CmdPropertyList*, short, short)   [UpdateScene__16CmdPropertyGoodsFP15CmdPropertyListss]  size=0xa20 */
/* WARNING: Removing unreachable block (ram,0x0049e920) */

void UpdateScene__16CmdPropertyGoodsFP15CmdPropertyListss
               (int param_1,int param_2,short param_3,ushort param_4)

{
  int iVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  char *pcVar5;
  short *psVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  ulong uVar10;
  int iVar11;
  int unaff_s3_lo;
  undefined1 auStack_c0 [12];
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  byte *pbStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  ushort uStack_58;
  ushort uStack_56;
  short sStack_54;
  short sStack_52;
  short sStack_50;
  ushort uStack_4e;
  short sStack_4c;
  short sStack_4a;
  ushort uStack_48;
  short sStack_46;
  short sStack_44;
  byte bStack_42;
  byte bStack_41;
  int iStack_40;
  int iStack_30;
  short sStack_20;
  ushort uStack_10;
  
  iVar1 = *(int *)(param_2 + 0x68);
  iStack_70 = *(int *)(param_2 + 0x140);
  iVar7 = iStack_70 + param_3 * 0xc;
  iStack_6c = iVar1;
  iStack_40 = param_1;
  iStack_30 = param_2;
  sStack_20 = param_3;
  uStack_10 = param_4;
  sStack_46 = GetRegCnt__9RegDatApiFii(*(undefined2 *)(iVar7 + 8),0xffffffffffffffff);
  iVar11 = 0;
  psVar6 = &sStack_44;
  sVar3 = 0;
  pcVar5 = (char *)(iVar7 + 10);
  bVar2 = false;
  uStack_5c = 0;
  switch(sStack_20) {
  case 0:
    iVar11 = 0x1c;
    pbStack_84 = (byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c);
    bStack_42 = *pbStack_84;
    iStack_88 = *(int *)(iStack_30 + 0x144);
    psVar6 = (short *)(iStack_88 + (uint)bStack_42 * 2 + 0x12);
    iStack_8c = *(int *)(iVar1 + 8);
    unaff_s3_lo = iStack_8c;
    break;
  case 1:
    sVar3 = 0xc;
    iStack_90 = *(int *)(iStack_30 + 0x148);
    pcVar5 = (char *)(iStack_90 + 8);
    iStack_94 = *(int *)(iVar1 + 8) + 0x80;
    unaff_s3_lo = iStack_94;
    break;
  case 2:
    iStack_98 = *(int *)(iVar1 + 8) + 0xe0;
    unaff_s3_lo = iStack_98;
    break;
  case 3:
    iStack_9c = *(int *)(iVar1 + 8) + 0x110;
    unaff_s3_lo = iStack_9c;
    break;
  case 4:
    iVar11 = 8;
    iStack_74 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c;
    bStack_41 = *(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28d);
    iStack_78 = *(int *)(iStack_30 + 0x15c);
    psVar6 = (short *)(iStack_78 + (uint)bStack_41 * 2);
    iStack_7c = *(int *)(iVar1 + 8) + 0x160;
    bVar2 = true;
    unaff_s3_lo = iStack_7c;
    break;
  case 5:
    iStack_a0 = *(int *)(iVar1 + 8) + 0x174;
    unaff_s3_lo = iStack_a0;
    break;
  case 9:
    iStack_80 = *(int *)(iVar1 + 8) + 0x40;
    bVar2 = true;
    sStack_46 = 0x90;
    unaff_s3_lo = iStack_80;
  }
  sVar4 = (short)(iVar11 >> 1);
  sStack_44 = 0;
  *(undefined2 *)(iStack_40 + 0x12a) = 0;
  iVar11 = *(int *)(iStack_40 + 0x124);
  *(byte *)(iVar11 + 0x162) = *(byte *)(iVar11 + 0x162) & 0xfe | 1;
  ClearPlace__10MenuWindowFv(iStack_40);
  if (bVar2) {
    for (; sStack_44 < sStack_46; sStack_44 = sStack_44 + 1) {
      uVar10 = (long)*psVar6 & 7;
      uVar8 = (uint)uVar10;
      if (((long)*psVar6 < 0) && (uVar10 != 0)) {
        uVar8 = uVar8 - 8;
      }
      iVar9 = (int)*psVar6;
      if (*psVar6 < 0) {
        iVar9 = iVar9 + 7;
      }
      if ((1 << (uVar8 & 0x1f) & (uint)*(byte *)(unaff_s3_lo + (iVar9 >> 3))) != 0) {
        *(byte *)(iVar11 + 0xe2) = *(byte *)(iVar11 + 0xe2) & 0xfe;
        if (-1 < (long)((ulong)*(byte *)(iVar11 + 0x21) << 0x3c)) {
          *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xf7 | 8;
          (**(code **)(*(int *)(iVar11 + 8) + 0x34))(0x40000000);
        }
        uStack_64 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(iVar7 + 2),*psVar6,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar11 + 0x50,uStack_64,*(byte *)(iVar11 + 0xa8) & 7,0,0);
        if (sStack_20 == 4) {
          uStack_58 = *(ushort *)(iVar11 + 0xf2);
          uStack_b0 = *(undefined4 *)((uint)uStack_58 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
          uStack_ac = uStack_b0;
          uStack_4e = uStack_58;
          iVar9 = GetRegDat__9RegDatApiFiii(0x37,*psVar6,0xffffffffffffffff);
          sprintf(auStack_c0,uStack_b0,*(undefined1 *)(iVar9 + 4));
          SetMessage__8MenuTextFPcUiUcUc(iVar11 + 0xd0,auStack_c0,*(byte *)(iVar11 + 0x128) & 7,1,0);
          *(byte *)(iVar11 + 0xe2) = *(byte *)(iVar11 + 0xe2) & 0xfe | 1;
        }
        else {
          sStack_50 = sStack_44;
          iVar9 = (int)sStack_44;
          if (sStack_44 < 0) {
            iVar9 = iVar9 + 7;
          }
          uVar10 = (long)sStack_44 & 7;
          uVar8 = (uint)uVar10;
          if (((long)sStack_44 < 0) && (uVar10 != 0)) {
            uVar8 = uVar8 - 8;
          }
          if (((uint)*(byte *)(*(int *)(iVar1 + 8) + (iVar9 >> 3) + 0x60) & 1 << (uVar8 & 0x1f)) !=
              0) {
            (**(code **)(*(int *)(iVar11 + 8) + 0x34))(0x3f000000);
            *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xf7;
          }
        }
        SetIcon__10MenuCommonFcP10MenuSprite(*pcVar5,iVar11 + 0x150);
        sStack_52 = *psVar6;
        *(short *)(iVar11 + 0x16) = sStack_52;
        sStack_54 = (short)*pcVar5;
        *(short *)(iVar11 + 0x22) = sStack_54;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40,iVar11);
        iVar11 = iVar11 + 0x1b0;
        *(short *)(iStack_40 + 0x12a) = *(short *)(iStack_40 + 0x12a) + 1;
      }
      pcVar5 = pcVar5 + sVar3;
      psVar6 = psVar6 + sVar4;
    }
  }
  else {
    for (; sStack_44 < sStack_46; sStack_44 = sStack_44 + 1) {
      if (*(char *)(unaff_s3_lo + *psVar6) != '\0') {
        if (-1 < (long)((ulong)*(byte *)(iVar11 + 0x21) << 0x3c)) {
          *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xf7 | 8;
          (**(code **)(*(int *)(iVar11 + 8) + 0x34))(0x40000000);
        }
        uStack_60 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(iVar7 + 2),*psVar6,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar11 + 0x50,uStack_60,*(byte *)(iVar11 + 0xa8) & 7,0,0);
        uStack_56 = *(ushort *)(iVar11 + 0xf2);
        uStack_a8 = *(undefined4 *)((uint)uStack_56 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
        uStack_a4 = uStack_a8;
        uStack_48 = uStack_56;
        sprintf(auStack_c0,uStack_a8,*(undefined1 *)(unaff_s3_lo + *psVar6));
        SetMessage__8MenuTextFPcUiUcUc(iVar11 + 0xd0,auStack_c0,*(byte *)(iVar11 + 0x128) & 7,1,0);
        *(byte *)(iVar11 + 0xe2) = *(byte *)(iVar11 + 0xe2) & 0xfe | 1;
        SetIcon__10MenuCommonFcP10MenuSprite(*pcVar5,iVar11 + 0x150);
        sStack_4a = *psVar6;
        *(short *)(iVar11 + 0x16) = sStack_4a;
        sStack_4c = (short)*pcVar5;
        *(short *)(iVar11 + 0x22) = sStack_4c;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_40,iVar11);
        iVar11 = iVar11 + 0x1b0;
        *(short *)(iStack_40 + 0x12a) = *(short *)(iStack_40 + 0x12a) + 1;
      }
      pcVar5 = pcVar5 + sVar3;
      psVar6 = psVar6 + sVar4;
    }
  }
  if (*(short *)(iStack_40 + 0x12a) == 0) {
    if (-1 < (long)((ulong)*(byte *)(iVar11 + 0x21) << 0x3c)) {
      *(byte *)(iVar11 + 0x21) = *(byte *)(iVar11 + 0x21) & 0xf7 | 8;
      (**(code **)(*(int *)(iVar11 + 8) + 0x34))(0x40000000);
    }
    uStack_b4 = *(undefined4 *)((uint)uStack_10 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
    uStack_68 = uStack_b4;
    SetMessage__8MenuTextFPcUiUcUc(iVar11 + 0x50,uStack_b4,*(byte *)(iVar11 + 0xa8) & 7,0,0);
    *(byte *)(iVar11 + 0xe2) = *(byte *)(iVar11 + 0xe2) & 0xfe;
    *(byte *)(iVar11 + 0x162) = *(byte *)(iVar11 + 0x162) & 0xfe;
    *(undefined2 *)(iVar11 + 0x16) = 0xffff;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_40,iVar11);
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + 0x18,iStack_40 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_40 + 0x18,iStack_40 + 0xf4);
  SetScroll__10MenuWindowFss(iStack_40,0,0);
  *(undefined2 *)(iStack_40 + 0x128) = *(undefined2 *)(iVar7 + 4);
  return;
}

/* JP: 0x0049f080  CmdPropertyGoods::Select(CmdNote*, MenuGroup*, MenuGroup*)   [Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup]  size=0x168 */
void Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
               (int param_1,int param_2,int param_3,int param_4)

{
  undefined8 uVar1;
  int iVar2;
  
  if (param_4 != 0) {
    iVar2 = *(int *)(param_1 + 0x124) + *(short *)(param_4 + 0x1e) * 0x1b0;
    SetCSA__8FontItemFUc(iVar2 + 0x50,0);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,0);
  }
  if (param_3 != 0) {
    iVar2 = *(int *)(param_1 + 0x124) + *(short *)(param_3 + 0x1e) * 0x1b0;
    SetCSA__8FontItemFUc(iVar2 + 0x50,1);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,1);
    if (param_2 != 0) {
      uVar1 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(param_1 + 0x128),*(undefined2 *)(param_3 + 0x16),
                              0xffffffffffffffff);
      SetExplanation__7CmdNoteFPCce(param_2,uVar1);
    }
  }
  return;
}

/* JP: 0x0049f1f0  CmdPropertyGoods::~CmdPropertyGoods()   [@24@__dt__16CmdPropertyGoodsFv]  size=0x8 */
undefined4 * _24___dt__16CmdPropertyGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdPropertyGoods;
    *param_1 = 0x409544;
    param_1[3] = 0x409550;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x4502f0);
      param_1[0x43] = 0;
    }
    __dt__11SendOnLocalFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0049f200  CmdPropertyGoods::~CmdPropertyGoods()   [@36@__dt__16CmdPropertyGoodsFv]  size=0x8 */
undefined4 * _36___dt__16CmdPropertyGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdPropertyGoods;
    param_1[-3] = 0x409544;
    *param_1 = 0x409550;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x4502f0);
      param_1[0x40] = 0;
    }
    __dt__11SendOnLocalFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
