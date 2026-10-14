/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSelectTarget   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSelectTarget.md).
 */

/* JP: 0x00442bd0  CmdSelectTarget::CmdSelectTarget()   [__ct__15CmdSelectTargetFv]  size=0x1e8 */
int __ct__15CmdSelectTargetFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdSelectTarget;
  __ct__10MenuWindowFv(param_1 + 0x74);
  __construct_array(param_1 + 0x128,0x2676b0,0x2677a0,0x40,2);
  __ct__11MenuTextureFv(param_1 + 0x1a8);
  __ct__11SendOnLocalFv(param_1 + 0x1e8);
  __ct__11SendOnLocalFv(param_1 + 0x218);
  __ct__10MenuSpriteFv(param_1 + 0x248);
  __ct__10MenuSpriteFv(param_1 + 0x2a8);
  __ct__8FontDrawFv(param_1 + 0x308);
  __ct__8MenuTextFv(param_1 + 0x348);
  __ct__8MenuTextFv(param_1 + 0x3c8);
  __ct__8MenuTextFv(param_1 + 0x448);
  __ct__8MenuTextFv(param_1 + 0x4c8);
  __ct__8MenuTextFv(param_1 + 0x548);
  __ct__8MenuTextFv(param_1 + 0x5c8);
  __ct__8MenuTextFv(param_1 + 0x648);
  __ct__8MenuTextFv(param_1 + 0x6c8);
  __ct__8MenuTextFv(param_1 + 0x748);
  __ct__8MenuTextFv(param_1 + 0x7c8);
  *(undefined4 *)(param_1 + 0x848) = 0;
  *(undefined4 *)(param_1 + 0x84c) = 0;
  __ct__10MenuWindowFv(param_1 + 0x850);
  __ct__8FontDrawFv(param_1 + 0x904);
  __ct__8MenuTextFv(param_1 + 0x944);
  __ct__7KeyWaitFv(param_1 + 0x9c4);
  memset(param_1 + 0x5c,0,0x18);
  return param_1;
}

/* JP: 0x00442dc0  CmdSelectTarget::~CmdSelectTarget()   [__dt__15CmdSelectTargetFv]  size=0x2e8 */
int __dt__15CmdSelectTargetFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdSelectTarget;
    if (*(int *)(param_1 + 0x848) != 0) {
      iVar1 = *(int *)(param_1 + 0x848);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0x848) = 0;
    }
    if (*(int *)(param_1 + 0x84c) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x84c),0x4430b0);
      *(undefined4 *)(param_1 + 0x84c) = 0;
    }
    __dt__7KeyWaitFv(param_1 + 0x9c4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x944,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x904,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x850,0xffffffffffffffff);
    if (param_1 != -0x6c8) {
      __dt__8MenuTextFv(param_1 + 0x7c8,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x748,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x6c8,0xffffffffffffffff);
    }
    if (param_1 != -0x548) {
      __dt__8MenuTextFv(param_1 + 0x648,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x5c8,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x548,0xffffffffffffffff);
    }
    if (param_1 != -0x3c8) {
      __dt__8MenuTextFv(param_1 + 0x4c8,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x448,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x3c8,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 0x348,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x308,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x2a8,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x248,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x218,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x1e8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1a8,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x128,0x2677a0,0x40,2);
    __dt__10MenuWindowFv(param_1 + 0x74,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004431a0  CmdSelectTarget::GetReady()   [GetReady__15CmdSelectTargetFv]  size=0x7c8 */
undefined4 GetReady__15CmdSelectTargetFv(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  long lVar4;
  undefined8 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 uStack_20;
  
  sVar1 = *(short *)(*(int *)(param_1 + 0x10) + 0xc6);
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x1a8,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x218,param_1 + 0x1c0,*(undefined4 *)(param_1 + 0x1bc),1,
                  0xffffffffffffffff);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x2a8);
  *(int *)(param_1 + 0x304) = param_1 + 0x218;
  *(byte *)(param_1 + 0x2ba) = *(byte *)(param_1 + 0x2ba) & 0xdf;
  *(undefined2 *)(param_1 + 0x1fe) = 0;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,param_1 + 0x2a8);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,1,param_1 + 0x248);
  *(int *)(param_1 + 0x2a4) = param_1 + 0x1e8;
  *(byte *)(param_1 + 0x25a) = *(byte *)(param_1 + 0x25a) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,param_1 + 0x248);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x308);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x8c,param_1 + 0x308);
  SetData__9MenuSceneFUsP8MenuText(param_1,0,param_1 + 0x348);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,param_1 + 0x348);
  iVar7 = param_1 + 0x3c8;
  for (iVar8 = 0; iVar8 < 3; iVar8 = iVar8 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_1,iVar8 + 2U & 0xffff,iVar7);
    SetData__9MenuSceneFUsP8MenuText(param_1,iVar8 + 6U & 0xffff,iVar7 + 0x80);
    SetData__9MenuSceneFUsP8MenuText(param_1,iVar8 + 10U & 0xffff,iVar7 + 0x100);
    SetMessage__8MenuTextFPcUiUcUc(iVar7,*(undefined4 *)
                           ((uint)*(ushort *)(iVar7 + 0x22) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                    *(byte *)(iVar7 + 0x58) & 7,0,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,iVar7);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,iVar7 + 0x80);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,iVar7 + 0x100);
    iVar7 = iVar7 + 0x180;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_1,2,param_1 + 0x904);
  SetData__9MenuSceneFUsP8MenuText(param_1,0xe,param_1 + 0x944);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,1,param_1 + 0x850);
  Create__7KeyWaitFv(param_1 + 0x9c4);
  *(int *)(param_1 + 0x898) = param_1 + 0x9c4;
  *(int *)(param_1 + 0x9dc) = param_1 + 0x850;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x868,param_1 + 0x904);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x850,param_1 + 0x944);
  AddOT__7MenuObjFv(param_1 + 0x850);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x74);
  AddOT__7MenuObjFv(param_1 + 0x74);
  *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = 0xf4;
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),param_1 + 0x248);
  if (*(char *)(param_1 + 0x61) == '\x05') {
    lVar4 = __nw__FUi(0x40);
    uVar2 = 0;
    if (lVar4 != 0) {
      uVar2 = __ct__8FontDrawFv(lVar4);
    }
    *(undefined4 *)(param_1 + 0x848) = uVar2;
    uVar5 = __nwa__FUi(sVar1 * 0x358 + 0x10);
    uVar2 = __construct_new_array(uVar5,0x443970,0x4430b0,0x358,sVar1);
    *(undefined4 *)(param_1 + 0x84c) = uVar2;
    SetData__9MenuSceneFUsP8FontDraw(param_1,1,*(undefined4 *)(param_1 + 0x848));
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x8c,*(undefined4 *)(param_1 + 0x848));
    uVar6 = *(uint *)(param_1 + 0x84c);
    uVar3 = uVar6 + sVar1 * 0x358;
    uStack_20 = 0.0;
    for (; uVar6 < uVar3; uVar6 = uVar6 + 0x358) {
      SetData__9MenuSceneFUsP8MenuText(param_1,1,uVar6 + 0x50);
      SetData__9MenuSceneFUsP8MenuText(param_1,5,uVar6 + 0xd0);
      SetData__9MenuSceneFUsP8MenuText(param_1,9,uVar6 + 0x150);
      SetData__9MenuSceneFUsP8MenuText(param_1,0xd,uVar6 + 0x1d0);
      SetData__9MenuSceneFUsP11MenuPolygon(param_1,0,uVar6 + 0x250);
      SetData__9MenuSceneFUsP11MenuPolygon(param_1,1,uVar6 + 0x2d4);
      AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0x50);
      uVar5 = AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0xd0);
      AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0x150,uVar5);
      AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0x1d0);
      AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0x250);
      AddPlace__9MenuGroupFP9MenuPlace(uVar6,uVar6 + 0x2d4);
      SetData__9MenuSceneFUsP9MenuGroup(param_1,0,uVar6);
      (**(code **)(*(int *)(uVar6 + 8) + 0x24))(0,uStack_20);
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x74,uVar6);
      uStack_20 = uStack_20 + *(float *)(uVar6 + 0x30);
    }
    *(undefined2 *)(param_1 + 0x62) = 999;
  }
  else if (*(char *)(param_1 + 0x60) != '\0') {
    if (1 < sVar1) {
      CreateScrollMark__10MenuWindowFUc(param_1 + 0x74,0xc);
    }
    *(undefined2 *)(param_1 + 0x62) = 0;
  }
  SetParameter__15CmdSelectTargetFi(param_1,*(undefined2 *)(param_1 + 0x62));
  Open__10MenuWindowFUci(param_1 + 0x74,*(byte *)(param_1 + 0x124) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xa8) + 0x10));
  *(undefined1 *)(param_1 + 0x20) = 3;
  return 1;
}

/* JP: 0x00443a10  CmdSelectTarget::Run()   [Run__15CmdSelectTargetFv]  size=0x6e4 */
undefined4 Run__15CmdSelectTargetFv(int param_1)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  bool bVar4;
  long lVar5;
  undefined4 unaff_s4_lo;
  
  uVar3 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  cVar1 = *(char *)(param_1 + 0x20);
  if (cVar1 == '\r') {
    *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf9) = 1;
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x70));
    Close__10MenuWindowFUci(param_1 + 0x74,((ulong)*(byte *)(param_1 + 0x124) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xa8) + 0x14));
    *(undefined1 *)(param_1 + 0x20) = 4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
  }
  else if (cVar1 == '\x04') {
    if ((*(char *)(param_1 + 0x11c) == '\x01') || (*(char *)(param_1 + 0x11c) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      ReleaseOT__7MenuObjFv(param_1 + 0x74);
      ReleaseOT__7MenuObjFv(param_1 + 0x850);
      return 1;
    }
  }
  else if (cVar1 == '\x03') {
    if ((*(char *)(param_1 + 0x11c) == '\x01') || (*(char *)(param_1 + 0x11c) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      *(undefined1 *)(param_1 + 0x20) = 0xf;
    }
  }
  else if (cVar1 == '\x10') {
    if ((*(char *)(param_1 + 0x8f8) == '\x01') || (*(char *)(param_1 + 0x8f8) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      *(byte *)(param_1 + 0x9d6) = *(byte *)(param_1 + 0x9d6) & 0xfe;
      *(undefined1 *)(param_1 + 0x20) = 0xf;
    }
  }
  else if (cVar1 == '\x0e') {
    if ((uVar3 & 0x6000) != 0) {
      Close__10MenuWindowFUci(param_1 + 0x850,((ulong)*(byte *)(param_1 + 0x900) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0x884) + 0x14));
      *(undefined1 *)(param_1 + 0x20) = 0x10;
      return 1;
    }
  }
  else if (cVar1 == '\x0f') {
    if ((uVar3 & 0x2000) == 0) {
      if ((uVar3 & 0x4000) != 0) {
        *(undefined1 *)(param_1 + 0x20) = 0xd;
        return 1;
      }
      if (*(int *)(param_1 + 0xb8) != 0) {
        sVar2 = *(short *)(param_1 + 0x62);
        if ((uVar3 & 0x480) == 0) {
          if ((uVar3 & 0x820) != 0) {
            *(short *)(param_1 + 0x62) = *(short *)(param_1 + 0x62) + 1;
          }
        }
        else {
          *(short *)(param_1 + 0x62) = *(short *)(param_1 + 0x62) + -1;
        }
        if (sVar2 != *(short *)(param_1 + 0x62)) {
          if (*(short *)(param_1 + 0x62) < 0) {
            *(short *)(param_1 + 0x62) = *(short *)(*(int *)(param_1 + 0x10) + 0xc6) + -1;
          }
          else if (*(short *)(*(int *)(param_1 + 0x10) + 0xc6) <= *(short *)(param_1 + 0x62)) {
            *(undefined2 *)(param_1 + 0x62) = 0;
          }
          SetParameter__15CmdSelectTargetFi(param_1,*(undefined2 *)(param_1 + 0x62));
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),6,0,0);
        }
      }
    }
    else {
      lVar5 = Use__15CmdSelectTargetFi(param_1,*(undefined2 *)(param_1 + 0x62));
      if (lVar5 == 2) {
        unaff_s4_lo = *(undefined4 *)(param_1 + 0x68);
      }
      else if (lVar5 == 1) {
        unaff_s4_lo = *(undefined4 *)(param_1 + 0x6c);
      }
      else if (lVar5 == 0) {
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),4,0,0);
        return 0;
      }
      SetParameter__15CmdSelectTargetFi(param_1,*(undefined2 *)(param_1 + 0x62));
      ClearImage__8FontDrawFv(param_1 + 0x904);
      SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x944,unaff_s4_lo,*(byte *)(param_1 + 0x99c) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x904,param_1 + 0x944,((ulong)*(byte *)(param_1 + 0x99c) & 0xf) >> 3
                      ,0);
      SetSize__10MenuWindowFff(*(float *)(param_1 + 0x970) + *(float *)(param_1 + 0xa44),
                      *(undefined4 *)(param_1 + 0x974),param_1 + 0x850);
      Open__10MenuWindowFUci(param_1 + 0x850,*(byte *)(param_1 + 0x900) & 7,
                      *(undefined4 *)(*(int *)(param_1 + 0x884) + 0x10));
      SetPosition__7KeyWaitFi(param_1 + 0x9c4,1);
      *(byte *)(param_1 + 0x9d6) = *(byte *)(param_1 + 0x9d6) & 0xfe | 1;
      *(undefined1 *)(param_1 + 0x20) = 0xe;
    }
  }
  return 0;
}

/* JP: 0x00444100  CmdSelectTarget::SetParameter(int)   [SetParameter__15CmdSelectTargetFi]  size=0xa60 */
void SetParameter__15CmdSelectTargetFi(int param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined2 uVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  undefined1 auStack_140 [8];
  undefined1 auStack_138 [12];
  int iStack_12c;
  undefined4 *puStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  float fStack_114;
  float fStack_110;
  undefined4 uStack_10c;
  int iStack_108;
  undefined4 uStack_104;
  int iStack_100;
  undefined4 *puStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  int *piStack_d0;
  int *piStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int *piStack_bc;
  int *piStack_b8;
  int *piStack_b4;
  int iStack_b0;
  int iStack_ac;
  int *piStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int *piStack_60;
  int iStack_5c;
  int iStack_58;
  short sStack_52;
  short sStack_50;
  ushort uStack_4e;
  short sStack_4c;
  short sStack_4a;
  undefined2 uStack_48;
  ushort uStack_46;
  ushort uStack_44;
  ushort uStack_42;
  undefined2 uStack_40;
  undefined2 uStack_3e;
  undefined2 uStack_3c;
  undefined2 uStack_3a;
  short sStack_38;
  short sStack_36;
  ushort uStack_34;
  ushort uStack_32;
  ushort uStack_30;
  ushort uStack_2e;
  ushort uStack_2c;
  ushort uStack_2a;
  undefined2 uStack_28;
  short sStack_26;
  short sStack_24;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_64 = *(int *)(param_1 + 0x10);
  iStack_b0 = iStack_64 + 0xb8;
  piVar3 = *(int **)(iStack_b0 + param_2 * 4 + 0x10);
  piVar7 = piVar3 + 2;
  piStack_bc = piVar3 + 2;
  piVar5 = piVar3 + 4;
  iStack_c0 = *(int *)(param_1 + 0x44) + 0x10;
  piStack_b8 = piVar7;
  piStack_b4 = piVar3;
  iStack_ac = iStack_b0;
  iStack_5c = iStack_c0;
  iStack_58 = iStack_b0;
  iStack_20 = param_1;
  iStack_10 = param_2;
  ClearImage__8FontDrawFv(param_1 + 0x308);
  if (iStack_10 == 999) {
    iVar6 = *(int *)(iStack_20 + 0x84c);
    iStack_68 = *(int *)(iStack_20 + 0x10);
    iStack_c8 = iStack_68 + 0xb8;
    piVar3 = (int *)(iStack_68 + 200);
    iStack_70 = *(int *)(iStack_20 + 0x10);
    iStack_d8 = iStack_70 + 0xb8;
    sStack_38 = *(short *)(iStack_70 + 0xc6);
    piStack_60 = piVar3 + sStack_38;
    iStack_d4 = iStack_d8;
    piStack_d0 = piVar3;
    piStack_cc = piVar3;
    iStack_c4 = iStack_c8;
    iStack_74 = iStack_d8;
    iStack_6c = iStack_c8;
    sStack_36 = sStack_38;
    ClearImage__8FontDrawFv(*(undefined4 *)(iStack_20 + 0x848));
    for (; piVar3 < piStack_60; piVar3 = piVar3 + 1) {
      iStack_78 = *piVar3;
      uVar4 = *(undefined2 *)(iStack_78 + 10);
      iStack_7c = *piVar3;
      uVar1 = *(undefined2 *)(iStack_7c + 0x10);
      piStack_a8 = (int *)*piVar3;
      iStack_e0 = *piStack_a8 + 10;
      iStack_dc = iStack_e0;
      iStack_80 = iStack_e0;
      uStack_40 = uVar1;
      uStack_3e = uVar1;
      uStack_3c = uVar4;
      uStack_3a = uVar4;
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x50,iStack_e0,*(byte *)(iVar6 + 0xa8) & 7,0,1);
      uStack_84 = *(undefined4 *)(iStack_20 + 0x848);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_84,iVar6 + 0x50,((ulong)*(byte *)(iVar6 + 0xa8) & 0xf) >> 3,0);
      uStack_42 = *(ushort *)(iVar6 + 0xf2);
      uStack_e8 = *(undefined4 *)((uint)uStack_42 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      uStack_e4 = uStack_e8;
      uStack_88 = uStack_e8;
      uStack_34 = uStack_42;
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0xd0,uStack_e8,*(byte *)(iVar6 + 0x128) & 7,0,1);
      uStack_8c = *(undefined4 *)(iStack_20 + 0x848);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_8c,iVar6 + 0xd0,((ulong)*(byte *)(iVar6 + 0x128) & 0xf) >> 3,0);
      uStack_44 = *(ushort *)(iVar6 + 0x172);
      uStack_f0 = *(undefined4 *)((uint)uStack_44 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      uStack_ec = uStack_f0;
      uStack_2e = uStack_44;
      sprintf(auStack_138,uStack_f0,uVar4);
      uStack_46 = *(ushort *)(iVar6 + 0x1f2);
      uStack_f8 = *(undefined4 *)((uint)uStack_46 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      uStack_f4 = uStack_f8;
      uStack_30 = uStack_46;
      sprintf(auStack_140,uStack_f8,uVar1);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x150,auStack_138,*(byte *)(iVar6 + 0x1a8) & 7,0,1);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x1d0,auStack_140,*(byte *)(iVar6 + 0x228) & 7,0,1);
      uStack_90 = *(undefined4 *)(iStack_20 + 0x848);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_90,iVar6 + 0x150,((ulong)*(byte *)(iVar6 + 0x1a8) & 0xf) >> 3,0);
      uStack_94 = *(undefined4 *)(iStack_20 + 0x848);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(uStack_94,iVar6 + 0x1d0,((ulong)*(byte *)(iVar6 + 0x228) & 0xf) >> 3,0);
      SetParameter__7CmdMenuFP8MenuTextss(iVar6 + 0x150,uVar4,uVar1);
      iVar6 = iVar6 + 0x358;
    }
    uStack_28 = (undefined2)iStack_10;
    sStack_26 = 2;
    puStack_fc = (undefined4 *)(*(int *)(iStack_20 + 0x28) + 0x10);
    uStack_98 = *puStack_fc;
    SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x348,uStack_98,*(byte *)(iStack_20 + 0x3a0) & 7,0,1);
  }
  else {
    uStack_48 = *(undefined2 *)(*piVar3 + 8);
    sStack_26 = 0;
    iStack_100 = *piVar3 + 10;
    iStack_9c = iStack_100;
    uStack_28 = uStack_48;
    SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x348,iStack_100,*(byte *)(iStack_20 + 0x3a0) & 7,0,1);
  }
  sStack_4a = *(short *)(iStack_20 + 0x1fe);
  puVar2 = (undefined4 *)FindAttachFile__9MenuSceneCFs(iStack_20,uStack_28);
  Create__11MenuTextureFPUc6GS_PSMUii(iStack_20 + sStack_4a * 0x40 + 0x128,*puVar2,0x30,0,0);
  sStack_4c = *(short *)(iStack_20 + 0x1fe);
  iStack_108 = iStack_20 + sStack_4c * 0x40;
  iStack_a0 = iStack_108 + 0x128;
  uStack_104 = *(undefined4 *)(iStack_108 + 0x13c);
  iStack_108 = iStack_108 + 0x140;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_20 + 0x1e8,iStack_108,uStack_104,1,0xffffffffffffffff);
  uStack_4e = *(ushort *)(iStack_20 + 0x1fe);
  uStack_32 = uStack_4e ^ 1;
  *(ushort *)(iStack_20 + 0x1fe) = uStack_32;
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x308,iStack_20 + 0x348,
                  ((ulong)*(byte *)(iStack_20 + 0x3a0) & 0xf) >> 3,0);
  uStack_10c = *(undefined4 *)(iStack_20 + 0x370);
  fStack_110 = *(float *)(iStack_20 + 0x374);
  fStack_114 = *(float *)(iStack_20 + 0xe0);
  (**(code **)(*(int *)(iStack_20 + 0x350) + 0x24))
            ((float)(int)*(short *)(iStack_5c + 4) + (fStack_114 - fStack_110) * 0.5,uStack_10c);
  iVar6 = iStack_20 + 0x3c8;
  sStack_24 = 0;
  while( true ) {
    piVar7 = (int *)((int)piVar7 + 2);
    if (2 < sStack_24) break;
    sStack_50 = *(short *)(iVar6 + 0xa2);
    uStack_2a = sStack_26 + sStack_50;
    sStack_52 = *(short *)(iVar6 + 0x122);
    uStack_2c = sStack_26 + sStack_52;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x308,iVar6,((ulong)*(byte *)(iVar6 + 0x58) & 0xf) >> 3,0);
    if (sStack_26 == 0) {
      uStack_120 = *(undefined4 *)((uint)uStack_2a * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      sprintf(auStack_138,uStack_120,*(undefined2 *)piVar7);
      uStack_124 = *(undefined4 *)((uint)uStack_2c * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      sprintf(auStack_140,uStack_124,(short)*piVar5);
      uVar4 = *(undefined2 *)piVar7;
      uVar1 = (undefined2)*piVar5;
    }
    else {
      uStack_118 = *(undefined4 *)((uint)uStack_2a * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      strcpy(auStack_138,uStack_118);
      uStack_11c = *(undefined4 *)((uint)uStack_2c * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
      strcpy(auStack_140,uStack_11c);
      uVar4 = 1;
      uVar1 = 1;
    }
    SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x80,auStack_138,*(byte *)(iVar6 + 0xd8) & 7,0,1);
    SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x100,auStack_140,*(byte *)(iVar6 + 0x158) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x308,iVar6 + 0x80,((ulong)*(byte *)(iVar6 + 0xd8) & 0xf) >> 3,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x308,iVar6 + 0x100,((ulong)*(byte *)(iVar6 + 0x158) & 0xf) >> 3,0);
    if (sStack_24 < 2) {
      SetParameter__7CmdMenuFP8MenuTextss(iVar6 + 0x80,uVar4,uVar1);
    }
    sStack_24 = sStack_24 + 1;
    iVar6 = iVar6 + 0x180;
    piVar5 = (int *)((int)piVar5 + 2);
  }
  if (*(int *)(iStack_20 + 0xb8) != 0) {
    puStack_128 = (undefined4 *)(iStack_20 + 0x36c);
    iStack_12c = *(int *)(iStack_20 + 0xb8);
    bStack_21 = *(byte *)(iStack_12c + 0x83) & 0xf;
    iStack_a4 = iStack_12c;
    SetArea__10ScrollMarkFUcffff(*puStack_128,*(undefined4 *)(iStack_20 + 0x370),
                    *(undefined4 *)(iStack_20 + 0x374),*(undefined4 *)(iStack_20 + 0x378),iStack_12c
                    ,bStack_21);
  }
  *(short *)(iStack_20 + 0x62) = (short)iStack_10;
  return;
}

/* JP: 0x00444b60  CmdSelectTarget::Use(int)   [Use__15CmdSelectTargetFi]  size=0x414 */
undefined2 Use__15CmdSelectTargetFi(int param_1,uint param_2)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined8 uVar5;
  long lVar6;
  short sVar7;
  uint uVar8;
  undefined2 uVar9;
  short asStack_120 [48];
  undefined1 auStack_c0 [96];
  int iStack_60;
  int iStack_5c;
  byte *pbStack_58;
  byte *pbStack_54;
  int *piStack_50;
  undefined4 *puStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int *piStack_3c;
  int *piStack_38;
  int iStack_34;
  byte *pbStack_30;
  float fStack_2c;
  short sStack_26;
  undefined1 uStack_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  int iStack_20;
  uint uStack_10;
  
  uVar8 = 0xffffffff;
  iVar2 = *(int *)(param_1 + 0x10);
  iStack_48 = iVar2 + 0xb8;
  sVar1 = *(short *)(iVar2 + 0xc6);
  iStack_44 = iStack_48;
  iStack_34 = iVar2;
  sStack_26 = sVar1;
  iStack_20 = param_1;
  uStack_10 = param_2;
  uVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(0,*(undefined2 *)(param_1 + 0x5e),*(undefined2 *)(param_1 + 0x5c),
                          *(undefined4 *)(param_1 + 100),auStack_c0,0);
  uVar9 = 2;
  if (uStack_10 != 999) {
    uVar8 = 1 << (uStack_10 & 0x1f);
  }
  puVar3 = (undefined4 *)(iVar2 + 200);
  puStack_4c = puVar3;
  for (sVar7 = 0; sVar7 < sVar1; sVar7 = sVar7 + 1) {
    if ((uVar8 & 1 << ((int)sVar7 & 0x1fU)) != 0) {
      piStack_38 = (int *)*puVar3;
      uStack_22 = *(undefined1 *)(*piStack_38 + 2);
      uStack_21 = uStack_22;
      EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,uStack_22,uVar5,auStack_c0,asStack_120,&fStack_2c,0,0,0);
      if (fStack_2c != 0.0) break;
    }
    puVar3 = puVar3 + 1;
  }
  if (sVar7 == sVar1) {
    uVar9 = 0;
  }
  else {
    piVar4 = (int *)(iVar2 + 200);
    piStack_50 = piVar4;
    for (sVar7 = 0; sVar7 < sVar1; sVar7 = sVar7 + 1) {
      if ((uVar8 & 1 << ((int)sVar7 & 0x1fU)) != 0) {
        piStack_3c = (int *)*piVar4;
        uStack_24 = *(undefined1 *)(*piStack_3c + 2);
        uStack_23 = uStack_24;
        EffectCodeFunc__FiiP6EFFTBLfP8ECResultPfP11BtlChrParambb(0x3f800000,uStack_24,uVar5,auStack_c0,asStack_120,0,0,0,0);
        if (asStack_120[0] != 0) {
          iStack_40 = *piVar4;
          pbStack_58 = *(byte **)(iStack_40 + 0x48);
          pbStack_54 = pbStack_58;
          pbStack_30 = pbStack_58;
          if (pbStack_58 != (byte *)0x0) {
            iStack_60 = *(int *)*piVar4;
            *(short *)(iStack_60 + 0x1e) =
                 *(short *)(iStack_60 + 0x1e) +
                 ((short)((int)((int)asStack_120[0] * (uint)*pbStack_58) / 100) - asStack_120[0]);
            iStack_5c = iStack_60;
            if (*(ushort *)(iStack_60 + 0x1c) < *(ushort *)(iStack_60 + 0x1e)) {
              *(undefined2 *)(iStack_60 + 0x1e) = *(undefined2 *)(iStack_60 + 0x1c);
            }
          }
        }
        lVar6 = FlushParameter__5CmdPCFP8ECResult(*piVar4,asStack_120);
        if (lVar6 == 0) {
          uVar9 = 1;
        }
      }
      piVar4 = piVar4 + 1;
    }
    if (asStack_120[0] == 0) {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_20 + 0x58),0x1006,0,0);
    }
    else {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_20 + 0x58),0x1005,0,0);
    }
  }
  return uVar9;
}
