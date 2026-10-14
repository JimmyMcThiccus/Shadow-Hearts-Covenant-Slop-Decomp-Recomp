/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdAromaBlend   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdAromaBlend.md).
 */

/* JP: 0x00460f50  CmdAromaBlend::CmdAromaBlend()   [__ct__13CmdAromaBlendFv]  size=0x84 */
int __ct__13CmdAromaBlendFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdAromaBlend;
  *(undefined4 *)(param_1 + 0x18) = 0x408774;
  *(undefined4 *)(param_1 + 0x24) = 0x408780;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x00460fe0  CmdAromaBlend::~CmdAromaBlend()   [__dt__13CmdAromaBlendFv]  size=0xec */
int __dt__13CmdAromaBlendFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdAromaBlend;
    *(undefined4 *)(param_1 + 0x18) = 0x408774;
    *(undefined4 *)(param_1 + 0x24) = 0x408780;
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

/* JP: 0x004610d0  CmdAromaBlend::CreateScene(CmdAroma*)   [CreateScene__13CmdAromaBlendFP8CmdAroma]  size=0x360 */
void CreateScene__13CmdAromaBlendFP8CmdAroma(int param_1,int param_2)

{
  undefined2 uVar1;
  short sVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  int iVar6;
  short sVar7;
  float fVar8;
  undefined4 uStack_2c;
  
  sVar2 = *(short *)(param_2 + 0x11e) + -1;
  uVar1 = *(undefined2 *)(*(int *)(param_2 + 0x51c) + 4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  uVar4 = __nwa__FUi(sVar2 * 0x1b0 + 0x10);
  uVar3 = __construct_new_array(uVar4,0x450610,0x4502f0,0x1b0,sVar2);
  *(undefined4 *)(param_1 + 0x124) = uVar3;
  iVar6 = *(int *)(param_1 + 0x124);
  uStack_2c = 0.0;
  for (sVar7 = 0; sVar7 < sVar2; sVar7 = sVar7 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,3,iVar6 + 0x150);
    SetIcon__10MenuCommonFcP10MenuSprite((char)uVar1,iVar6 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0x150);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar6 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,2,iVar6 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar6);
    *(short *)(iVar6 + 0x16) = sVar7;
    *(undefined2 *)(iVar6 + 0x1c) = 0;
    *(short *)(iVar6 + 0x1e) = sVar7;
    (**(code **)(*(int *)(iVar6 + 8) + 0x24))
              (*(undefined4 *)(iVar6 + 0x24),uStack_2c + *(float *)(iVar6 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar6);
    uVar5 = GetRealHeight__8FontItemCFv(iVar6 + 0x50);
    if ((long)uVar5 < 0) {
      fVar8 = (float)(uVar5 & 0xffffffff);
    }
    else {
      fVar8 = (float)(int)uVar5;
    }
    uStack_2c = uStack_2c + fVar8;
    iVar6 = iVar6 + 0x1b0;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(*(int *)(param_1 + 0x124) + 0x164) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00461430  CmdAromaBlend::UpdateScene(CmdAroma*, short)   [UpdateScene__13CmdAromaBlendFP8CmdAromas]  size=0x3f0 */
void UpdateScene__13CmdAromaBlendFP8CmdAromas(int param_1,int param_2,short param_3)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  int iVar8;
  short sVar9;
  undefined1 auStack_50 [8];
  int iStack_48;
  int iStack_44;
  int iStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  byte bStack_32;
  byte bStack_31;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  iVar2 = *(int *)(*(int *)(param_2 + 0x58) + 0x5c);
  bStack_32 = *(byte *)(*(int *)(iVar2 + 4) + 0xdae);
  sVar1 = *(short *)(param_2 + 0x11e);
  iStack_48 = iVar2;
  iStack_44 = iVar2;
  iStack_40 = iVar2;
  bStack_31 = bStack_32;
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  iVar8 = *(int *)(iStack_30 + 0x124);
  sVar4 = (sVar1 + -1) * sStack_10;
  for (sVar9 = 0; sVar9 < sVar1; sVar9 = sVar9 + 1) {
    if ((((uint)bStack_31 & 1 << ((int)sVar9 & 0x1fU)) != 0) && (sVar9 != sStack_10)) {
      uStack_38 = GetRegDat__9RegDatApiFiii(0x10,sVar9,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0x50,uStack_38,*(byte *)(iVar8 + 0xa8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb4,iVar8 + 0x50,((ulong)*(byte *)(iVar8 + 0xa8) & 0xf) >> 3,0);
      if (-1 < (long)((ulong)*(byte *)(iVar8 + 0x21) << 0x3c)) {
        (**(code **)(*(int *)(iVar8 + 8) + 0x34))(0x40000000);
      }
      iVar5 = (int)sVar4;
      if (sVar4 < 0) {
        iVar5 = iVar5 + 7;
      }
      uVar7 = (long)sVar4 & 7;
      uVar6 = (uint)uVar7;
      if (((long)sVar4 < 0) && (uVar7 != 0)) {
        uVar6 = uVar6 - 8;
      }
      if (((int)(uint)*(byte *)(*(int *)(iVar2 + 4) + (iVar5 >> 3) + 0xe3c) >> (uVar6 & 0x1f) & 1U)
          == 0) {
        uStack_3c = *(undefined4 *)(*(int *)(iStack_20 + 0x28) + 0x1c);
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0xd0,uStack_3c,*(byte *)(iVar8 + 0x128) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb4,iVar8 + 0xd0,((ulong)*(byte *)(iVar8 + 0x128) & 0xf) >> 3,0
                       );
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xf7;
        (**(code **)(*(int *)(iVar8 + 8) + 0x34))(0x40000000);
      }
      else {
        uVar3 = *(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x18);
        iVar5 = GetRegDat__9RegDatApiFiii(0x3c,sVar4,0xffffffffffffffff);
        sprintf(auStack_50,uVar3,*(undefined2 *)(iVar5 + 0x1e));
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0xd0,auStack_50,*(byte *)(iVar8 + 0x128) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb4,iVar8 + 0xd0,((ulong)*(byte *)(iVar8 + 0x128) & 0xf) >> 3,0
                       );
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0xf7 | 8;
      }
      *(short *)(iVar8 + 0x16) = sVar4;
      iVar8 = iVar8 + 0x1b0;
    }
    sVar4 = sVar4 + 1;
  }
  *(short *)(iStack_30 + 0xae) = sStack_10;
  Open__10MenuWindowFUci(iStack_30,*(byte *)(iStack_30 + 0xb0) & 7,
                  *(undefined4 *)(*(int *)(iStack_30 + 0x34) + 0x10));
  return;
}

/* JP: 0x00461820  CmdAromaBlend::Select(CmdAroma*, MenuGroup*, MenuGroup*)   [Select__13CmdAromaBlendFP8CmdAromaP9MenuGroupP9MenuGroup]  size=0x17c */
void Select__13CmdAromaBlendFP8CmdAromaP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  undefined8 uVar1;
  undefined8 unaff_s6;
  
  if (param_4 != 0) {
    uVar1 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar1,0);
    uVar1 = FindPlace__9MenuGroupFs(param_4,0x14);
    SetCSA__8FontItemFUc(uVar1,0);
  }
  if (param_3 != 0) {
    uVar1 = FindPlace__9MenuGroupFs(param_3,10);
    SetCSA__8FontItemFUc(uVar1,1);
    uVar1 = FindPlace__9MenuGroupFs(param_3,0x14);
    SetCSA__8FontItemFUc(uVar1,1);
    if ((long)((ulong)*(byte *)(param_3 + 0x21) << 0x3c) < 0) {
      unaff_s6 = GetRegDat__9RegDatApiFiii(0x1a,*(undefined2 *)(param_3 + 0x16),0xffffffffffffffff);
    }
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(*(int *)(param_2 + 0x58) + 100),unaff_s6);
  }
  return;
}

/* JP: 0x004619a0  CmdAromaBlend::~CmdAromaBlend()   [@24@__dt__13CmdAromaBlendFv]  size=0x8 */
undefined4 * _24___dt__13CmdAromaBlendFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdAromaBlend;
    *param_1 = 0x408774;
    param_1[3] = 0x408780;
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

/* JP: 0x004619b0  CmdAromaBlend::~CmdAromaBlend()   [@36@__dt__13CmdAromaBlendFv]  size=0x8 */
undefined4 * _36___dt__13CmdAromaBlendFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdAromaBlend;
    param_1[-3] = 0x408774;
    *param_1 = 0x408780;
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
