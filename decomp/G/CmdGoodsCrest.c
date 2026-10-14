/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsCrest   functions: 11
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsCrest.md).
 */

/* JP: 0x004950b0  CmdGoodsCrest::CmdGoodsCrest()   [__ct__13CmdGoodsCrestFv]  size=0xbc */
int __ct__13CmdGoodsCrestFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdGoodsCrest;
  *(undefined4 *)(param_1 + 0x18) = 0x4093a4;
  *(undefined4 *)(param_1 + 0x24) = 0x4093b0;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xe4);
  __ct__11SendOnLocalFv(param_1 + 0x114);
  __ct__11SendOnLocalFv(param_1 + 0x144);
  __ct__8FontDrawFv(param_1 + 0x174);
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  return param_1;
}

/* JP: 0x00495170  CmdGoodsCrest::~CmdGoodsCrest()   [__dt__13CmdGoodsCrestFv]  size=0x188 */
int __dt__13CmdGoodsCrestFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdGoodsCrest;
    *(undefined4 *)(param_1 + 0x18) = 0x4093a4;
    *(undefined4 *)(param_1 + 0x24) = 0x4093b0;
    if (*(int *)(param_1 + 0x1b4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x1b4),0x495300);
      *(undefined4 *)(param_1 + 0x1b4) = 0;
    }
    if (*(int *)(param_1 + 0x1b8) != 0) {
      iVar1 = *(int *)(param_1 + 0x1b8);
      if (iVar1 != 0) {
        __dt__8MenuTextFv(iVar1 + 0x50,0xffffffffffffffff);
        __dt__9MenuGroupFv(iVar1,0xffffffffffffffff);
        __dl__FPv(iVar1);
      }
      *(undefined4 *)(param_1 + 0x1b8) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x174,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x144,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x114,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00495430  CmdGoodsCrest::CreateScene(MenuScene*, short, short, short)   [CreateScene__13CmdGoodsCrestFP9MenuScenesss]  size=0x484 */
void CreateScene__13CmdGoodsCrestFP9MenuScenesss
               (int param_1,undefined4 param_2,undefined2 param_3,short param_4,short param_5)

{
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  short sVar4;
  int iVar5;
  short sVar6;
  
  uVar2 = __nwa__FUi(param_4 * 0x65c + 0x10);
  iVar1 = __construct_new_array(uVar2,0x4958c0,0x495300,0x65c,(int)param_4);
  *(int *)(param_1 + 0x1b4) = iVar1;
  for (sVar6 = 0; sVar6 < param_4; sVar6 = sVar6 + 1) {
    iVar5 = iVar1 + 0x50;
    for (sVar4 = 0; sVar4 < 2; sVar4 = sVar4 + 1) {
      SetData__9MenuSceneFUsP8MenuText(param_2,sVar4,iVar5);
      AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar5);
      iVar5 = iVar5 + 0x80;
    }
    iVar5 = iVar1 + 0x1d4;
    for (sVar4 = 0; sVar4 < 0xb; sVar4 = sVar4 + 1) {
      SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar4,iVar5);
      AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar5);
      iVar5 = iVar5 + 0x60;
    }
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0xb,iVar1 + 0x5f4);
    SetBar__7MenuBarFv(iVar1 + 0x5f4);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x5f4);
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,0,iVar1 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar1);
    *(byte *)(iVar1 + 0x21) = *(byte *)(iVar1 + 0x21) & 0xfe | 1;
    iVar1 = iVar1 + 0x65c;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0x174);
  *(short *)(param_1 + 200) = *(short *)(*(int *)(param_1 + 0x1b4) + 0x248) + -1;
  *(short *)(param_1 + 0xf8) = *(short *)(*(int *)(param_1 + 0x1b4) + 0x608) + -1;
  *(short *)(param_1 + 0x128) = *(short *)(*(int *)(param_1 + 0x1b4) + 0x428) + -1;
  *(short *)(param_1 + 0x158) = *(short *)(*(int *)(param_1 + 0x1b4) + 0x1e8) + -1;
  if (param_5 != 0) {
    lVar3 = __nw__FUi(0xd0);
    iVar1 = 0;
    if (lVar3 != 0) {
      __ct__9MenuGroupFv(lVar3);
      iVar1 = (int)lVar3;
      __ct__8MenuTextFv(iVar1 + 0x50);
    }
    *(int *)(param_1 + 0x1b8) = iVar1;
    SetData__9MenuSceneFUsP8MenuText(param_2,2,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar1);
  }
  iVar1 = *(int *)(param_1 + 0x1b4);
  *(undefined2 *)(iVar1 + 0x1c) = 0;
  *(undefined2 *)(iVar1 + 0x1e) = 1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(undefined4 *)(param_1 + 0x1b4));
  SetData__9MenuSceneFUsP10MenuWindow(param_2,param_3,param_1);
  AddOT__7MenuObjFv(param_1);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0x174;
  return;
}

/* JP: 0x004959b0  CmdGoodsCrest::CreateImage(MenuTexture*)   [CreateImage__13CmdGoodsCrestFP11MenuTexture]  size=0xd4 */
void CreateImage__13CmdGoodsCrestFP11MenuTexture(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uStack_10;
  
  uStack_10 = param_2;
  for (uVar1 = param_1 + 0xb4; uVar1 < param_1 + 0x144U; uVar1 = uVar1 + 0x30) {
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(uVar1,uStack_10 + 0x18,*(undefined4 *)(uStack_10 + 0x14),1,0xffffffffffffffff);
    uStack_10 = uStack_10 + 0x40;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x144,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  return;
}

/* JP: 0x00495a90  CmdGoodsCrest::Select(MenuScene*, CmdNote*, MenuGroup*, MenuGroup*)   [Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup]  size=0x12c */
void Select__13CmdGoodsCrestFP9MenuSceneP7CmdNoteP9MenuGroupP9MenuGroup
               (undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  short sVar1;
  undefined8 uVar2;
  
  if (param_5 != 0) {
    SetClut__13CmdGoodsCrestFP9MenuGroupUc(param_1,param_5,0);
  }
  if (param_4 != 0) {
    sVar1 = *(short *)(param_4 + 0x16);
    SetClut__13CmdGoodsCrestFP9MenuGroupUc(param_1,param_4,1);
    if (param_3 != 0) {
      if (sVar1 < 0) {
        SetExplanation__7CmdNoteFPCce
                  (param_3,*(undefined4 *)
                            (((int)sVar1 + 3U & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x14));
      }
      else {
        uVar2 = GetRegDat__9RegDatApiFiii(0x1e,sVar1,0xffffffffffffffff);
        SetExplanation__7CmdNoteFPCce(param_3,uVar2);
      }
    }
  }
  return;
}

/* JP: 0x00495bc0  CmdGoodsCrest::SetClut(MenuGroup*, unsigned char)   [SetClut__13CmdGoodsCrestFP9MenuGroupUc]  size=0xe4 */
void SetClut__13CmdGoodsCrestFP9MenuGroupUc(int param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  if (*(short *)(param_2 + 0x16) < -1) {
    SetCSA__8FontItemFUc(*(int *)(param_1 + 0x1b8) + 0x50,param_3);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x1b4) +
            ((int)*(short *)(param_2 + 0x1e) - (int)*(short *)(param_1 + 0xae)) * 0x65c;
    SetCSA__8FontItemFUc(iVar1 + 0x50,param_3);
    SetCSA__8FontItemFUc(iVar1 + 0xd0,param_3);
  }
  return;
}

/* JP: 0x00495cb0  CmdGoodsCrest::Start()   [Start__13CmdGoodsCrestFv]  size=0x7c */
void Start__13CmdGoodsCrestFv(int param_1)

{
  uint uVar1;
  
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x174);
  for (uVar1 = param_1 + 0xb4; uVar1 < param_1 + 0x174U; uVar1 = uVar1 + 0x30) {
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,uVar1);
  }
  return;
}

/* JP: 0x00495d30  CmdGoodsCrest::Reset()   [Reset__13CmdGoodsCrestFv]  size=0x54 */
void Reset__13CmdGoodsCrestFv(int param_1)

{
  ClearPlace__10MenuWindowFv(param_1);
  *(undefined2 *)(param_1 + 0x1be) = 0;
  *(undefined2 *)(param_1 + 0x1c0) = 0;
  *(undefined2 *)(param_1 + 0xae) = 0;
  *(undefined2 *)(param_1 + 0x1c2) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  return;
}

/* JP: 0x00495d90  CmdGoodsCrest::SetCrest(MenuScene*, short, int, int)   [SetCrest__13CmdGoodsCrestFP9MenuScenesii]  size=0x57c */
int SetCrest__13CmdGoodsCrestFP9MenuScenesii
              (int param_1,int param_2,short param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined1 auStack_78 [16];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined2 uStack_52;
  int iStack_50;
  int iStack_40;
  short sStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_50 = param_1;
  iStack_40 = param_2;
  sStack_30 = param_3;
  iStack_20 = param_4;
  iStack_10 = param_5;
  if (param_3 < -1) {
    iVar3 = *(int *)(param_1 + 0x1b8);
    uStack_58 = *(undefined4 *)
                 (((int)param_3 + 3U & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x10);
    SetMessage__8MenuTextFPcUiUcUc(*(int *)(param_1 + 0x1b8) + 0x50,uStack_58,
                    *(byte *)(*(int *)(param_1 + 0x1b8) + 0xa8) & 7,0,0);
    SetCSA__8FontItemFUc(*(int *)(iStack_50 + 0x1b8) + 0x50,0);
    *(short *)(iVar3 + 0x16) = sStack_30;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iVar3);
    *(undefined2 *)(iStack_50 + 0xae) = 1;
  }
  else {
    uVar2 = 0;
    iVar3 = *(int *)(param_1 + 0x1b4) + *(short *)(param_1 + 0x1be) * 0x65c;
    *(short *)(param_1 + 0x1be) = *(short *)(param_1 + 0x1be) + 1;
    uStack_52 = *(undefined2 *)(param_1 + 0x1c0);
    *(undefined2 *)(iVar3 + 0x1c) = 0;
    *(undefined2 *)(iVar3 + 0x1e) = uStack_52;
    *(byte *)(iVar3 + 0x21) = *(byte *)(iVar3 + 0x21) & 0xfd | 2;
    SetCSA__8FontItemFUc(iVar3 + 0x50,0);
    SetCSA__8FontItemFUc(iVar3 + 0xd0,0);
    *(byte *)(iVar3 + 0x606) = *(byte *)(iVar3 + 0x606) & 0xfe;
    *(byte *)(iVar3 + 0x5a6) = *(byte *)(iVar3 + 0x5a6) & 0xfe;
    if (-1 < (long)((ulong)*(byte *)(iVar3 + 0x21) << 0x3c)) {
      *(byte *)(iVar3 + 0x21) = *(byte *)(iVar3 + 0x21) & 0xf7 | 8;
      (**(code **)(*(int *)(iVar3 + 0x58) + 0x34))(0x40000000);
      (**(code **)(*(int *)(iVar3 + 0xd8) + 0x34))(0x40000000);
      (**(code **)(*(int *)(iVar3 + 0x1dc) + 0x34))(0x40000000);
    }
    if (sStack_30 < 0) {
      uStack_60 = *(undefined4 *)(*(int *)(iStack_40 + 0x28) + 0x28);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,uStack_60,*(byte *)(iVar3 + 0xa8) & 7,0,0);
      uStack_64 = *(undefined4 *)(*(int *)(iStack_40 + 0x24) + 0x18);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0xd0,uStack_64,*(byte *)(iVar3 + 0x128) & 7,0,0);
      *(byte *)(iVar3 + 0x1e6) = *(byte *)(iVar3 + 0x1e6) & 0xfe;
    }
    else {
      *(byte *)(iVar3 + 0x1e6) = *(byte *)(iVar3 + 0x1e6) & 0xfe | 1;
      iVar1 = GetRegDat__9RegDatApiFiii(0x37,sStack_30,0xffffffffffffffff);
      uVar2 = (uint)*(byte *)(iVar1 + 4);
      uStack_5c = GetRegDat__9RegDatApiFiii(0xd,sStack_30,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,uStack_5c,*(byte *)(iVar3 + 0xa8) & 7,0,0);
      uStack_68 = *(undefined4 *)(*(int *)(iStack_40 + 0x24) + 0x10);
      sprintf(auStack_78,uStack_68,uVar2);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0xd0,auStack_78,*(byte *)(iVar3 + 0x128) & 7,1,0);
      if (iStack_10 < (int)uVar2) {
        *(byte *)(iVar3 + 0x5a6) = *(byte *)(iVar3 + 0x5a6) & 0xfe | 1;
      }
      else {
        *(byte *)(iVar3 + 0x606) = *(byte *)(iVar3 + 0x606) & 0xfe | 1;
        SetRange__7MenuBarFii(iVar3 + 0x5f4,uVar2,iStack_10);
      }
      if (iStack_20 < (int)uVar2) {
        *(byte *)(iVar3 + 0x21) = *(byte *)(iVar3 + 0x21) & 0xf7;
        (**(code **)(*(int *)(iVar3 + 0x58) + 0x34))(0x3f000000);
        (**(code **)(*(int *)(iVar3 + 0xd8) + 0x34))(0x3f000000);
        (**(code **)(*(int *)(iVar3 + 0x1dc) + 0x34))(0x3f000000);
      }
      *(short *)(iStack_50 + 0x1c2) = *(short *)(iStack_50 + 0x1c2) + 1;
    }
    *(short *)(iVar3 + 0x16) = sStack_30;
    *(short *)(iVar3 + 0x22) = (short)uVar2;
    (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,*(undefined4 *)(iStack_50 + 0x1c4));
    AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iVar3);
  }
  *(short *)(iStack_50 + 0x1c0) = *(short *)(iStack_50 + 0x1c0) + 1;
  *(float *)(iStack_50 + 0x1c4) =
       *(float *)(iStack_50 + 0x1c4) + *(float *)(*(int *)(iStack_50 + 0x1b4) + 0x30);
  return iVar3;
}

/* JP: 0x00496310  CmdGoodsCrest::~CmdGoodsCrest()   [@24@__dt__13CmdGoodsCrestFv]  size=0x8 */
undefined4 * _24___dt__13CmdGoodsCrestFv(undefined4 *param_1,short param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + -6;
  if (puVar2 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdGoodsCrest;
    *param_1 = 0x4093a4;
    param_1[3] = 0x4093b0;
    if (param_1[0x67] != 0) {
      __destroy_new_array(param_1[0x67],0x495300);
      param_1[0x67] = 0;
    }
    if (param_1[0x68] != 0) {
      iVar1 = param_1[0x68];
      if (iVar1 != 0) {
        __dt__8MenuTextFv(iVar1 + 0x50,0xffffffffffffffff);
        __dt__9MenuGroupFv(iVar1,0xffffffffffffffff);
        __dl__FPv(iVar1);
      }
      param_1[0x68] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x57,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x4b,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x3f,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar2,0);
    if (0 < param_2) {
      __dl__FPv(puVar2);
    }
  }
  return puVar2;
}

/* JP: 0x00496320  CmdGoodsCrest::~CmdGoodsCrest()   [@36@__dt__13CmdGoodsCrestFv]  size=0x8 */
undefined4 * _36___dt__13CmdGoodsCrestFv(undefined4 *param_1,short param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + -9;
  if (puVar2 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdGoodsCrest;
    param_1[-3] = 0x4093a4;
    *param_1 = 0x4093b0;
    if (param_1[100] != 0) {
      __destroy_new_array(param_1[100],0x495300);
      param_1[100] = 0;
    }
    if (param_1[0x65] != 0) {
      iVar1 = param_1[0x65];
      if (iVar1 != 0) {
        __dt__8MenuTextFv(iVar1 + 0x50,0xffffffffffffffff);
        __dt__9MenuGroupFv(iVar1,0xffffffffffffffff);
        __dl__FPv(iVar1);
      }
      param_1[0x65] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x48,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x3c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar2,0);
    if (0 < param_2) {
      __dl__FPv(puVar2);
    }
  }
  return puVar2;
}
