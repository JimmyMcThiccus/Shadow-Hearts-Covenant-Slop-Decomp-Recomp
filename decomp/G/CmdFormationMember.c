/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFormationMember   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFormationMember.md).
 */

/* JP: 0x0047f440  CmdFormationMember::CmdFormationMember()   [__ct__18CmdFormationMemberFv]  size=0xfc */
int __ct__18CmdFormationMemberFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdFormationMember;
  *(undefined4 *)(param_1 + 0x18) = 0x408ec4;
  *(undefined4 *)(param_1 + 0x24) = 0x408ed0;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xe4);
  __ct__11MenuTextureFv(param_1 + 0x128);
  __ct__11SendOnLocalFv(param_1 + 0x168);
  __construct_array(param_1 + 0x198,0x266140,0x2661a0,0x60,4);
  __construct_array(param_1 + 0x318,0x276640,0x2766d0,0x84,4);
  __ct__11MenuPolygonFv(param_1 + 0x528);
  return param_1;
}

/* JP: 0x0047f540  CmdFormationMember::~CmdFormationMember()   [__dt__18CmdFormationMemberFv]  size=0x164 */
int __dt__18CmdFormationMemberFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdFormationMember;
    *(undefined4 *)(param_1 + 0x18) = 0x408ec4;
    *(undefined4 *)(param_1 + 0x24) = 0x408ed0;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x47f6b0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x528,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x318,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x198,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x168,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047f820  CmdFormationMember::CreateScene(CmdFormation*)   [CreateScene__18CmdFormationMemberFP12CmdFormation]  size=0xad0 */
void CreateScene__18CmdFormationMemberFP12CmdFormation(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  short sVar7;
  short sVar8;
  int iVar9;
  undefined1 auStack_120 [84];
  int iStack_cc;
  int iStack_c4;
  undefined4 uStack_c0;
  undefined4 *puStack_bc;
  int iStack_b8;
  undefined4 uStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  int iStack_8c;
  int iStack_88;
  undefined4 uStack_84;
  undefined4 *puStack_80;
  undefined4 *puStack_7c;
  int iStack_78;
  int *piStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  float fStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  short sStack_44;
  short sStack_42;
  short sStack_40;
  ushort uStack_3e;
  short sStack_3c;
  short sStack_3a;
  ushort uStack_38;
  ushort uStack_36;
  undefined2 uStack_34;
  short sStack_32;
  short sStack_30;
  short sStack_2e;
  ushort uStack_2c;
  ushort uStack_2a;
  ushort uStack_28;
  ushort uStack_26;
  short sStack_24;
  byte bStack_22;
  undefined1 uStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  __ct__9MenuSceneFv(auStack_120);
  iStack_6c = *(int *)(iStack_10 + 0x10);
  iStack_70 = iStack_6c + 0xb8;
  sStack_32 = *(short *)(iStack_6c + 0xc6);
  piVar3 = (int *)(iStack_6c + 0xe8);
  iStack_58 = (int)sStack_32;
  piStack_74 = piVar3;
  iStack_4c = iStack_70;
  iStack_48 = iStack_6c;
  sStack_24 = sStack_32;
  uVar6 = __nwa__FUi(iStack_58 * 0x9c0 + 0x10);
  iVar4 = __construct_new_array(uVar6,0x4802f0,0x47f6b0,0x9c0,iStack_58);
  *(int *)(iStack_20 + 0x124) = iVar4;
  iStack_5c = sm_pCmdMenu__7MenuObj;
  puStack_80 = (undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x70);
  puStack_7c = puStack_80;
  iStack_78 = iVar4;
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_120,*puStack_80,0);
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_20 + 0xe4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xe4);
  for (sVar8 = 0; sVar8 < sStack_24; sVar8 = sVar8 + 1) {
    uStack_34 = *(undefined2 *)(*piVar3 + 8);
    puVar5 = (undefined4 *)FindAttachFile__9MenuSceneCFs(auStack_120,uStack_34);
    Create__11MenuTextureFPUc6GS_PSMUii(iVar4 + 0x50,*puVar5,0x30,0,0);
    uStack_84 = *(undefined4 *)(iVar4 + 100);
    iStack_88 = iVar4 + 0x68;
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iVar4 + 0x90,iStack_88,uStack_84,1,0xffffffffffffffff);
    SetData__9MenuSceneFUsP10MenuSprite(iStack_10,0,iVar4 + 0xc0);
    *(int *)(iVar4 + 0x11c) = iVar4 + 0x90;
    *(byte *)(iVar4 + 0xd2) = *(byte *)(iVar4 + 0xd2) & 0xdf;
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0xc0);
    SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar4 + 0x120);
    iStack_8c = *piVar3 + 10;
    iStack_60 = iStack_8c;
    SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0x120,iStack_8c,*(byte *)(iVar4 + 0x178) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xe4,iVar4 + 0x120,((ulong)*(byte *)(iVar4 + 0x178) & 0xf) >> 3,0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x120);
    iVar9 = iVar4 + 0x1a0;
    for (sVar7 = 0; sVar7 < 6; sVar7 = sVar7 + 1) {
      SetData__9MenuSceneFUsP8MenuFont(iStack_10,sVar7,iVar9);
      AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar9);
      if (sVar7 < 3) {
        uStack_36 = *(ushort *)(iVar9 + 0x22);
        uStack_94 = *(undefined4 *)((uint)uStack_36 * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
        uStack_90 = uStack_94;
        uStack_26 = uStack_36;
        (**(code **)(*(int *)(iVar9 + 8) + 0x68))(iVar9,uStack_94);
      }
      iVar9 = iVar9 + 0xb0;
    }
    uStack_21 = *(undefined1 *)(*piVar3 + 3);
    uStack_38 = *(ushort *)(iVar4 + 0x3d2);
    uStack_9c = *(undefined4 *)((uint)uStack_38 * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
    uStack_98 = uStack_9c;
    uStack_28 = uStack_38;
    (**(code **)(*(int *)(iVar4 + 0x3b8) + 0x68))(iVar4 + 0x3b0,uStack_9c,uStack_21);
    iVar9 = iVar4 + 0x460;
    for (sVar7 = 0; sVar7 < 2; sVar7 = sVar7 + 1) {
      sVar1 = *(short *)((int)piVar3 + sVar7 * 2 + 10);
      sVar2 = *(short *)((int)piVar3 + sVar7 * 2 + 0x10);
      sStack_3c = sVar2;
      sStack_3a = sVar1;
      SetData__9MenuSceneFUsP10MenuSprite(iStack_10,sVar7 + 2,iVar4 + sVar7 * 0x60 + 0x5c0);
      SetData__9MenuSceneFUsP10MenuSprite(iStack_10,sVar7 + 4,iVar4 + (sVar7 * 0xc + (int)sVar7) * 8 + 0x680);
      AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + (sVar7 * 0xc + (int)sVar7) * 8 + 0x680);
      AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + sVar7 * 0x60 + 0x5c0);
      SetBar__7MenuBarFv(iVar4 + (sVar7 * 0xc + (int)sVar7) * 8 + 0x680);
      SetRange__7MenuBarFii(iVar4 + (sVar7 * 0xc + (int)sVar7) * 8 + 0x680,sVar1,sVar2);
      uStack_3e = *(ushort *)(iVar9 + 0x22);
      uStack_a4 = *(undefined4 *)((uint)uStack_3e * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
      uStack_a0 = uStack_a4;
      uStack_2a = uStack_3e;
      (**(code **)(*(int *)(iVar9 + 8) + 0x68))(iVar9,uStack_a4,sVar1,sVar2);
      fStack_54 = (float)(int)sVar1 / (float)(int)sVar2;
      if (fStack_54 <= 0.25) {
        SetFontColor__14PluralFontItemFUsUsUcUcUc(iVar9,0,3,0xc4,0,0);
      }
      else if (fStack_54 <= 0.5) {
        SetFontColor__14PluralFontItemFUsUsUcUcUc(iVar9,0,3,0xc4,0xc4,0);
      }
      iVar9 = iVar9 + 0xb0;
    }
    iVar9 = iVar4 + 0x750;
    for (sVar7 = 0; sVar7 < 4; sVar7 = sVar7 + 1) {
      SetData__9MenuSceneFUsP11MenuPolygon(iStack_10,sVar7,iVar9);
      AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar9);
      iVar9 = iVar9 + 0x84;
    }
    SetData__9MenuSceneFUsP10MenuSprite(iStack_10,8,iVar4 + 0x960);
    *(byte *)(iVar4 + 0x981) = *(byte *)(iVar4 + 0x981) & 0xdf;
    *(byte *)(iVar4 + 0x972) = *(byte *)(iVar4 + 0x972) & 0xfe;
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x960);
    uVar6 = SetData__9MenuSceneFUsP9MenuGroup(iStack_10,0,iVar4);
    bStack_22 = *(byte *)(*piVar3 + 2);
    uStack_2c = (ushort)bStack_22;
    *(ushort *)(iVar4 + 0x16) = uStack_2c;
    *(short *)(iVar4 + 0x22) = sVar8;
    AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar4,uVar6);
    piVar3 = piVar3 + 0x13;
    iVar4 = iVar4 + 0x9c0;
  }
  iStack_50 = iStack_20 + 0x198;
  for (sVar8 = 0; sVar8 < 4; sVar8 = sVar8 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(iStack_10,1,iStack_50);
    iStack_50 = iStack_50 + 0x60;
  }
  iVar4 = iStack_20 + 0x318;
  for (sVar8 = 4; sVar8 < 8; sVar8 = sVar8 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(iStack_10,sVar8,iVar4);
    iVar4 = iVar4 + 0x84;
  }
  iStack_a8 = iStack_48 + 0x348;
  iStack_b0 = iStack_48 + 0x4a0;
  uStack_b4 = *(undefined4 *)(iStack_48 + 0x4b4);
  iStack_b8 = iStack_48 + 0x4b8;
  iStack_ac = iStack_b0;
  iStack_64 = iStack_a8;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_20 + 0xb4,iStack_b8,uStack_b4,1,0xffffffffffffffff);
  iStack_68 = *(int *)(iStack_20 + 0x124) + 0x5c0;
  sStack_42 = *(short *)(*(int *)(iStack_20 + 0x124) + 0x5d4);
  sStack_2e = sStack_42 + -1;
  *(short *)(iStack_20 + 200) = sStack_2e;
  sStack_40 = sStack_42;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  puStack_bc = (undefined4 *)(iStack_cc + 0x40);
  Create__11MenuTextureFPUc6GS_PSMUii(iStack_20 + 0x128,*puStack_bc,0x30,0,0);
  uStack_c0 = *(undefined4 *)(iStack_20 + 0x13c);
  iStack_c4 = iStack_20 + 0x140;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_20 + 0x168,iStack_c4,uStack_c0,1,0xffffffffffffffff);
  sStack_44 = *(short *)(iStack_20 + 0x1ac);
  sStack_30 = sStack_44 + -1;
  *(short *)(iStack_20 + 0x17c) = sStack_30;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0x168);
  SetData__9MenuSceneFUsP11MenuPolygon(iStack_10,0x13,iStack_20 + 0x528);
  AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iStack_20 + 0x528);
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_20);
  AddOT__7MenuObjFv(iStack_20);
  __dt__9MenuSceneFv(auStack_120,0xffffffffffffffff);
  return;
}

/* JP: 0x00480440  CmdFormationMember::UpdateScene(CmdFormation*, short)   [UpdateScene__18CmdFormationMemberFP12CmdFormations]  size=0x348 */
void UpdateScene__18CmdFormationMemberFP12CmdFormations(int param_1,int param_2,undefined2 param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  char *pcVar9;
  float fStack_44;
  
  sVar1 = *(short *)(*(int *)(param_2 + 0x10) + 0xc6);
  iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (char)param_3 * 0x20;
  pcVar9 = (char *)(iVar3 + 0x96);
  sVar2 = *(short *)(*(int *)(param_2 + 0x38) + 0x1e);
  for (uVar4 = param_1 + 0x198; uVar4 < param_1 + 0x318U; uVar4 = uVar4 + 0x60) {
    sVar8 = *(short *)(uVar4 + 0x16);
    if (-1 < sVar8) {
      RemovePlace__9MenuGroupFP9MenuPlace(*(int *)(param_1 + 0x124) + (sVar8 * 0x28 - (int)sVar8) * 0x40,uVar4);
      *(undefined2 *)(uVar4 + 0x16) = 0xffff;
    }
  }
  iVar5 = param_1 + 0x198;
  fStack_44 = 0.0;
  for (sVar8 = 0; sVar8 < sVar1; sVar8 = sVar8 + 1) {
    sVar7 = 0;
    iVar6 = *(int *)(param_1 + 0x124);
    while( true ) {
      if ((long)*pcVar9 == (long)*(short *)(iVar6 + 0x16)) break;
      iVar6 = iVar6 + 0x9c0;
      sVar7 = sVar7 + 1;
    }
    *(undefined2 *)(iVar6 + 0x1c) = 0;
    *(short *)(iVar6 + 0x1e) = sVar8;
    (**(code **)(*(int *)(iVar6 + 8) + 0x24))(0,fStack_44);
    if ((long)sVar8 < (long)*(char *)(iVar3 + 0x95)) {
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar5);
      *(short *)(iVar5 + 0x16) = sVar7;
      iVar5 = iVar5 + 0x60;
    }
    fStack_44 = fStack_44 + (float)(int)sVar2;
    pcVar9 = pcVar9 + 1;
  }
  *(byte *)(param_1 + 0x53a) = *(byte *)(param_1 + 0x53a) & 0xfe;
  if (*(char *)(iVar3 + 0x95) != '\0') {
    (**(code **)(*(int *)(param_1 + 0x530) + 0x28))
              (*(undefined4 *)(param_1 + 0x554),
               (float)(int)((int)*(char *)(iVar3 + 0x95) *
                           (uint)*(ushort *)(*(int *)(param_2 + 0x3c) + 0x15a)));
    *(byte *)(param_1 + 0x53a) = *(byte *)(param_1 + 0x53a) & 0xfe | 1;
  }
  *(undefined2 *)(param_1 + 0xae) = param_3;
  return;
}

/* JP: 0x00480790  CmdFormationMember::Select(MenuPlace*, MenuPlace*)   [Select__18CmdFormationMemberFP9MenuPlaceP9MenuPlace]  size=0x1c0 */
void Select__18CmdFormationMemberFP9MenuPlaceP9MenuPlace(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if (param_3 != 0) {
    iVar1 = *(int *)(param_1 + 0x124) +
            (*(short *)(param_3 + 0x22) * 0x28 - (int)*(short *)(param_3 + 0x22)) * 0x40;
    uVar2 = iVar1 + 0x750;
    iVar3 = param_1 + 0x318;
    while( true ) {
      if (iVar1 + 0x960U <= uVar2) break;
      RemovePlace__9MenuGroupFP9MenuPlace(iVar1,iVar3);
      AddPlace__9MenuGroupFP9MenuPlace(iVar1,uVar2);
      uVar2 = uVar2 + 0x84;
      iVar3 = iVar3 + 0x84;
    }
    SetCSA__8FontItemFUc(iVar1 + 0x120,0);
    SetScale__10MenuSpriteFf(0xc1200000,iVar1 + 0xc0);
  }
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x124) +
            (*(short *)(param_2 + 0x22) * 0x28 - (int)*(short *)(param_2 + 0x22)) * 0x40;
    uVar2 = param_1 + 0x318;
    iVar3 = iVar1 + 0x750;
    while( true ) {
      if (param_1 + 0x528U <= uVar2) break;
      RemovePlace__9MenuGroupFP9MenuPlace(iVar1,iVar3);
      AddPlace__9MenuGroupFP9MenuPlace(iVar1,uVar2);
      uVar2 = uVar2 + 0x84;
      iVar3 = iVar3 + 0x84;
    }
    SetCSA__8FontItemFUc(iVar1 + 0x120,1);
    SetScale__10MenuSpriteFf(0x41200000,iVar1 + 0xc0);
  }
  return;
}

/* JP: 0x00480950  CmdFormationMember::Blackout(CmdFormation*, int, char*, char*)   [Blackout__18CmdFormationMemberFP12CmdFormationiPcPc]  size=0x368 */
void Blackout__18CmdFormationMemberFP12CmdFormationiPcPc
               (int param_1,int param_2,int param_3,char *param_4,char *param_5)

{
  short sVar1;
  uint uVar2;
  ulong uVar3;
  uint uVar4;
  char *pcVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  
  sVar1 = *(short *)(*(int *)(param_2 + 0x10) + 0xc6);
  sVar8 = (short)*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                           (char)*(undefined2 *)(param_1 + 0xae) * 0x20 + 0x95);
  if (param_3 == 1) {
    sVar6 = sVar8;
    sVar7 = 0;
  }
  else {
    sVar6 = 0;
    sVar7 = 0;
    if (param_3 == 0) {
      sVar6 = sVar1;
      sVar7 = sVar8;
    }
  }
  uVar4 = *(uint *)(param_1 + 0x124);
  uVar2 = uVar4 + (sVar1 * 0x28 - (int)sVar1) * 0x40;
  for (; uVar4 < uVar2; uVar4 = uVar4 + 0x9c0) {
    pcVar5 = param_4;
    if (param_3 < 2) {
      *(undefined2 *)(uVar4 + 0x44) = 0x8000;
      uVar3 = (ulong)*(byte *)(uVar4 + 0x11) & 0xffffffffffffffef | 0x10;
      *(char *)(uVar4 + 0x11) = (char)uVar3;
      *(byte *)(uVar4 + 0x10) =
           *(byte *)(uVar4 + 0x10) & 0xef | (byte)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
      *(byte *)(uVar4 + 0x21) = *(byte *)(uVar4 + 0x21) & 0xfd | 2;
      *(byte *)(uVar4 + 0x972) = *(byte *)(uVar4 + 0x972) & 0xfe;
    }
    for (; (pcVar5 < param_5 && ((long)*pcVar5 != (long)*(short *)(uVar4 + 0x16)));
        pcVar5 = pcVar5 + 1) {
    }
    if (((sVar7 <= *(short *)(uVar4 + 0x1e)) && (*(short *)(uVar4 + 0x1e) < sVar6)) ||
       (pcVar5 != param_5)) {
      *(undefined2 *)(uVar4 + 0x44) = 0x2000;
      uVar3 = (ulong)*(byte *)(uVar4 + 0x11) & 0xffffffffffffffef | 0x10;
      *(char *)(uVar4 + 0x11) = (char)uVar3;
      *(byte *)(uVar4 + 0x10) =
           *(byte *)(uVar4 + 0x10) & 0xef | (byte)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
      *(byte *)(uVar4 + 0x21) = *(byte *)(uVar4 + 0x21) & 0xfd;
      *(byte *)(uVar4 + 0x972) = *(byte *)(uVar4 + 0x972) & 0xfe | 1;
    }
  }
  return;
}

/* JP: 0x00480cc0  CmdFormationMember::~CmdFormationMember()   [@24@__dt__18CmdFormationMemberFv]  size=0x8 */
undefined4 * _24___dt__18CmdFormationMemberFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdFormationMember;
    *param_1 = 0x408ec4;
    param_1[3] = 0x408ed0;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x47f6b0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x144,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xc0,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x60,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00480cd0  CmdFormationMember::~CmdFormationMember()   [@36@__dt__18CmdFormationMemberFv]  size=0x8 */
undefined4 * _36___dt__18CmdFormationMemberFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdFormationMember;
    param_1[-3] = 0x408ec4;
    *param_1 = 0x408ed0;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x47f6b0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x141,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xbd,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x5d,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x51,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
