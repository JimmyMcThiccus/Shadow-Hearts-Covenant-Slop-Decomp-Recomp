/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFormationTeam   functions: 15
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFormationTeam.md).
 */

/* JP: 0x00480ce0  CmdFormationTeam::CmdFormationTeam()   [__ct__16CmdFormationTeamFv]  size=0x124 */
int __ct__16CmdFormationTeamFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdFormationTeam;
  *(undefined4 *)(param_1 + 0x18) = 0x408f04;
  *(undefined4 *)(param_1 + 0x24) = 0x408f10;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11MenuTextureFv(param_1 + 0xf8);
  __construct_array(param_1 + 0x138,0x277820,0x277890,0x30,2);
  __ct__9MenuGroupFv(param_1 + 0x198);
  __construct_array(param_1 + 0x1e8,0x276640,0x2766d0,0x84,8);
  *(undefined4 *)(param_1 + 0x608) = 0;
  *(undefined4 *)(param_1 + 0x60c) = 0;
  __construct_array(param_1 + 0x610,0x267090,0x2670d0,0x30,3);
  __ct__11MenuPolygonFv(param_1 + 0x6a4);
  return param_1;
}

/* JP: 0x00480e10  CmdFormationTeam::~CmdFormationTeam()   [__dt__16CmdFormationTeamFv]  size=0x1ec */
int __dt__16CmdFormationTeamFv(int param_1,short param_2)

{
  uint uVar1;
  uint uVar2;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdFormationTeam;
    *(undefined4 *)(param_1 + 0x18) = 0x408f04;
    *(undefined4 *)(param_1 + 0x24) = 0x408f10;
    if (*(int *)(param_1 + 0x608) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x608),0x481000);
    }
    if (*(int *)(param_1 + 0x60c) != 0) {
      uVar1 = *(uint *)(param_1 + 0x60c);
      uVar2 = uVar1 + *(short *)(param_1 + 0xae) * 0x40;
      for (; uVar1 < uVar2; uVar1 = uVar1 + 0x40) {
        *(undefined4 *)(uVar1 + 0x14) = 0;
      }
      __destroy_new_array(*(undefined4 *)(param_1 + 0x60c),0x2677a0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x6a4,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x610,0x2670d0,0x30,3);
    __destroy_arr(param_1 + 0x1e8,0x2766d0,0x84,8);
    __dt__9MenuGroupFv(param_1 + 0x198,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x138,0x277890,0x30,2);
    __dt__11MenuTextureFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00481100  CmdFormationTeam::CreateScene(CmdFormation*)   [CreateScene__16CmdFormationTeamFP12CmdFormation]  size=0xa18 */
void CreateScene__16CmdFormationTeamFP12CmdFormation(int param_1,int param_2)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  undefined8 uVar9;
  int iVar10;
  short sVar11;
  int iVar12;
  int iVar13;
  undefined4 uStack_9c;
  float fStack_64;
  float fStack_60;
  char *pcStack_5c;
  int iStack_54;
  int *piStack_50;
  short sStack_26;
  
  iVar13 = *(int *)(param_2 + 0x10);
  piStack_50 = (int *)(iVar13 + 0xe8);
  sVar3 = *(short *)(iVar13 + 0xc6);
  sStack_26 = *(short *)(param_2 + 0xe50);
  sVar1 = *(short *)(param_2 + 0xe52);
  uVar9 = __nwa__FUi(sVar3 * 0x40 + 0x10);
  iVar4 = __construct_new_array(uVar9,0x2676b0,0x2677a0,0x40,(int)sVar3);
  uVar9 = __nwa__FUi(sVar1 * 0x598 + 0x10);
  iVar5 = __construct_new_array(uVar9,0x481b20,0x481000,0x598,(int)sVar1);
  *(int *)(param_1 + 0x60c) = iVar4;
  *(int *)(param_1 + 0x608) = iVar5;
  *(short *)(param_1 + 0xae) = sVar3;
  for (sVar11 = 0; sVar11 < 3; sVar11 = sVar11 + 1) {
    iVar10 = *(int *)(((int)sVar11 + 2U & 0xffff) * 0xc + *(int *)(param_2 + 0x54) + 0x10);
    if (*(short *)(iVar10 + 6) == 0x10) {
      uStack_9c = 4;
    }
    else {
      uStack_9c = 8;
    }
    Create__10ClutRasterFiUiib(param_1 + sVar11 * 0x30 + 0x610,0,iVar10 + *(int *)(iVar10 + 0xc),uStack_9c,0);
  }
  for (sVar11 = 0; sVar11 < sVar3; sVar11 = sVar11 + 1) {
    uVar2 = *(undefined2 *)(*piStack_50 + 8);
    *(undefined2 *)(iVar4 + 0x38) = uVar2;
    puVar6 = (undefined4 *)FindAttachFile__9MenuSceneCFs(param_2,uVar2);
    Create__11MenuTextureFPUc6GS_PSMUii(iVar4,*puVar6,0x30,0,0);
    *(int *)(iVar4 + 0x14) = param_1 + *(short *)((int)puVar6 + 6) * 0x30 + 0x610;
    piStack_50 = piStack_50 + 0x13;
    iVar4 = iVar4 + 0x40;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  fStack_64 = 0.0;
  for (sVar3 = 0; sVar3 < sVar1; sVar3 = sVar3 + 1) {
    iVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (char)sStack_26 * 0x20;
    pcStack_5c = (char *)(iVar4 + 0x96);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar5 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar5 + 0x50);
    fStack_60 = 0.0;
    iVar12 = iVar5 + 400;
    iVar10 = iVar5 + 0x310;
    iStack_54 = iVar5 + 0xd0;
    sVar11 = 0;
    while( true ) {
      if ((long)*(char *)(iVar4 + 0x94) <= (long)sVar11) break;
      SetData__9MenuSceneFUsP10MenuSprite(param_2,6,iVar12);
      SetData__9MenuSceneFUsP10MenuSprite(param_2,7,iVar10);
      *(int *)(iVar10 + 0x5c) = iStack_54;
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xdf;
      *(short *)(iVar12 + 0x1c) = sVar11;
      *(short *)(iVar12 + 0x1e) = sVar3;
      *(short *)(iVar10 + 0x1c) = sVar11;
      *(short *)(iVar10 + 0x1e) = sVar3;
      (**(code **)(*(int *)(iVar12 + 8) + 0x24))
                (fStack_60 + *(float *)(iVar12 + 0x24),*(undefined4 *)(iVar12 + 0x28));
      (**(code **)(*(int *)(iVar10 + 8) + 0x24))
                (fStack_60 + *(float *)(iVar10 + 0x24),*(undefined4 *)(iVar10 + 0x28));
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar12);
      AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar10);
      fStack_60 = fStack_60 + (float)(int)*(short *)(iVar12 + 0x22);
      if ((long)sVar11 < (long)*(char *)(iVar4 + 0x95)) {
        *(short *)(iVar10 + 0x16) = (short)*pcStack_5c;
        *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe | 1;
        piVar7 = (int *)FindPC__8CmdPartyFUs(iVar13 + 0xb8,*pcStack_5c);
        iVar8 = FindFace__16CmdFormationTeamFs(param_1,*(undefined2 *)(*piVar7 + 8));
        Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_54,iVar8 + 0x18,*(undefined4 *)(iVar8 + 0x14),1,0xffffffffffffffff);
      }
      sVar11 = sVar11 + 1;
      iVar12 = iVar12 + 0x60;
      iVar10 = iVar10 + 0x60;
      iStack_54 = iStack_54 + 0x30;
      pcStack_5c = pcStack_5c + 1;
    }
    iVar10 = iVar5 + 0x490;
    sVar11 = 8;
    while( true ) {
      if (9 < sVar11) break;
      SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar11,iVar10);
      AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar10);
      sVar11 = sVar11 + 1;
      iVar10 = iVar10 + 0x84;
    }
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,iVar5);
    *(short *)(iVar5 + 0x16) = sStack_26;
    *(short *)(iVar5 + 0x22) = (short)*(char *)(iVar4 + 0x94);
    *(undefined2 *)(iVar5 + 0x1c) = 0;
    *(short *)(iVar5 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar5 + 8) + 0x24))
              (*(undefined4 *)(iVar5 + 0x24),fStack_64 + *(float *)(iVar5 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
    fStack_64 = fStack_64 + *(float *)(iVar5 + 0x30);
    iVar5 = iVar5 + 0x598;
    sStack_26 = sStack_26 + 1;
  }
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xf8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x138,param_1 + 0x110,*(undefined4 *)(param_1 + 0x10c),1,
                  0xffffffffffffffff);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x168,param_1 + 0x110,*(undefined4 *)(param_1 + 0x10c),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x14c) = *(short *)(*(int *)(param_1 + 0x608) + 0x1a4) + -1;
  *(short *)(param_1 + 0x17c) = *(short *)(param_1 + 0x14c) + 5;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x138);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x168);
  SetData__9MenuSceneFUsP9MenuGroup(param_2,2,param_1 + 0x198);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x198);
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,0x12,param_1 + 0x6a4);
  iVar13 = param_1 + 0x1e8;
  for (sVar3 = 10; sVar3 < 0x12; sVar3 = sVar3 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar3,iVar13);
    AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x198,iVar13);
    iVar13 = iVar13 + 0x84;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00481c00  CmdFormationTeam::UpdateName(CmdFormation*)   [UpdateName__16CmdFormationTeamFP12CmdFormation]  size=0x160 */
void UpdateName__16CmdFormationTeamFP12CmdFormation(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  sVar3 = *(short *)(param_2 + 0xe50);
  sVar1 = sVar3 + *(short *)(param_2 + 0xe52);
  iVar2 = *(int *)(param_1 + 0x608);
  for (; sVar3 < sVar1; sVar3 = sVar3 + 1) {
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x50,*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (char)sVar3 * 0x20 + 0x84,
                    *(byte *)(iVar2 + 0xa8) & 7,0,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar2 + 0x50,((ulong)*(byte *)(iVar2 + 0xa8) & 0xf) >> 3,0);
    iVar2 = iVar2 + 0x598;
  }
  return;
}

/* JP: 0x00481d60  CmdFormationTeam::UpdateSlot(CmdFormation*, short)   [UpdateSlot__16CmdFormationTeamFP12CmdFormations]  size=0x62c */
void UpdateSlot__16CmdFormationTeamFP12CmdFormations(int param_1,int param_2,short param_3)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  short sVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  short sVar10;
  char acStack_98 [8];
  int iStack_90;
  undefined4 uStack_8c;
  int iStack_88;
  undefined4 uStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int *piStack_70;
  int *piStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  uint uStack_58;
  int iStack_54;
  int iStack_50;
  short sStack_4a;
  short sStack_48;
  undefined2 uStack_46;
  undefined2 uStack_44;
  short sStack_42;
  undefined2 uStack_40;
  undefined2 uStack_3e;
  short sStack_3c;
  undefined2 uStack_3a;
  short sStack_38;
  short sStack_36;
  short sStack_34;
  char cStack_31;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  iStack_74 = *(int *)(param_2 + 0x10);
  iStack_78 = iStack_74 + 0xb8;
  iVar8 = *(int *)(param_1 + 0x608) + *(short *)(param_1 + 0x6a2) * 0x598;
  iVar1 = iVar8 + *(short *)(param_1 + 0x6a0) * 0x60;
  sVar10 = *(short *)(iVar1 + 0x326);
  sStack_38 = *(short *)(iVar8 + 0x22);
  uStack_3a = *(undefined2 *)(iVar8 + 0x16);
  cStack_31 = (char)uStack_3a;
  iVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + cStack_31 * 0x20;
  iStack_80 = iVar2 + 0x84;
  uVar5 = iVar8 + 0x310;
  uStack_58 = uVar5 + sStack_38 * 0x60;
  for (; (uVar7 = 0, uVar5 < uStack_58 &&
         ((iVar1 + 0x310U == uVar5 ||
          (sStack_3c = *(short *)(uVar5 + 0x16), uVar7 = uVar5, param_3 != sStack_3c))));
      uVar5 = uVar5 + 0x60) {
  }
  *(undefined2 *)(iVar1 + 0x326) = 0xffff;
  *(byte *)(iVar1 + 0x322) = *(byte *)(iVar1 + 0x322) & 0xfe;
  iStack_7c = iStack_80;
  iStack_54 = iStack_78;
  iStack_50 = iStack_74;
  sStack_36 = sVar10;
  sStack_34 = sStack_38;
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  if (sVar10 != param_3) {
    *(short *)(iVar1 + 0x326) = param_3;
    *(byte *)(iVar1 + 0x322) = *(byte *)(iVar1 + 0x322) & 0xfe | 1;
    uVar3 = (ulong)*(byte *)(iVar1 + 0x321) & 0xfffffffffffffffd | 2;
    *(char *)(iVar1 + 0x321) = (char)uVar3;
    *(byte *)(iVar1 + 800) =
         *(byte *)(iVar1 + 800) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
    piStack_6c = (int *)FindPC__8CmdPartyFUs(iStack_78,param_3);
    uStack_40 = *(undefined2 *)(*piStack_6c + 8);
    uStack_3e = uStack_40;
    iStack_60 = FindFace__16CmdFormationTeamFs(iStack_30,uStack_40);
    sStack_42 = *(short *)(iVar1 + 0x32c);
    iStack_5c = iVar8 + sStack_42 * 0x30 + 0xd0;
    uStack_84 = *(undefined4 *)(iStack_60 + 0x14);
    iStack_88 = iStack_60 + 0x18;
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_5c,iStack_88,uStack_84,1,0xffffffffffffffff);
  }
  if (uVar7 != 0) {
    *(short *)(uVar7 + 0x16) = sVar10;
    uVar3 = (ulong)*(byte *)(uVar7 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(uVar7 + 0x11) = (char)uVar3;
    *(byte *)(uVar7 + 0x10) =
         *(byte *)(uVar7 + 0x10) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
    *(byte *)(uVar7 + 0x12) = *(byte *)(uVar7 + 0x12) & 0xfe;
    if (-1 < sVar10) {
      piStack_70 = (int *)FindPC__8CmdPartyFUs(iStack_54,sVar10);
      uStack_46 = *(undefined2 *)(*piStack_70 + 8);
      uStack_44 = uStack_46;
      iStack_68 = FindFace__16CmdFormationTeamFs(iStack_30,uStack_46);
      sStack_48 = *(short *)(uVar7 + 0x1c);
      iStack_64 = iVar8 + sStack_48 * 0x30 + 0xd0;
      uStack_8c = *(undefined4 *)(iStack_68 + 0x14);
      iStack_90 = iStack_68 + 0x18;
      Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_64,iStack_90,uStack_8c,1,0xffffffffffffffff);
      *(byte *)(uVar7 + 0x12) = *(byte *)(uVar7 + 0x12) & 0xfe | 1;
    }
  }
  memcpy(acStack_98,iVar2 + 0x96,8);
  sVar10 = 0;
  pcVar9 = (char *)(iVar2 + 0x96);
  uVar5 = iVar8 + 0x310;
  uStack_58 = uVar5 + *(char *)(iVar2 + 0x94) * 0x60;
  for (; uVar5 < uStack_58; uVar5 = uVar5 + 0x60) {
    sStack_4a = *(short *)(uVar5 + 0x16);
    if (-1 < sStack_4a) {
      *pcVar9 = (char)sStack_4a;
      pcVar6 = acStack_98;
      for (sVar4 = 0; (long)sVar4 < (long)*(char *)(iVar2 + 0x93); sVar4 = sVar4 + 1) {
        if (*pcVar9 == *pcVar6) {
          *pcVar6 = -1;
          break;
        }
        pcVar6 = pcVar6 + 1;
      }
      sVar10 = sVar10 + 1;
      pcVar9 = pcVar9 + 1;
    }
  }
  *(char *)(iVar2 + 0x95) = (char)sVar10;
  do {
    if ((long)*(char *)(iVar2 + 0x93) <= (long)sVar10) {
      return;
    }
    pcVar6 = acStack_98;
    for (sVar4 = 0; (long)sVar4 < (long)*(char *)(iVar2 + 0x93); sVar4 = sVar4 + 1) {
      if (-1 < *pcVar6) {
        *pcVar9 = *pcVar6;
        *pcVar6 = -1;
        break;
      }
      pcVar6 = pcVar6 + 1;
    }
    pcVar9 = pcVar9 + 1;
    sVar10 = sVar10 + 1;
  } while( true );
}

/* JP: 0x00482390  CmdFormationTeam::ChoiceMember(CmdFormation*)   [ChoiceMember__16CmdFormationTeamFP12CmdFormation]  size=0x2b4 */
void ChoiceMember__16CmdFormationTeamFP12CmdFormation(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined1 auStack_50 [12];
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  uint uStack_38;
  uint uStack_34;
  short sStack_2e;
  undefined2 uStack_2c;
  undefined2 uStack_2a;
  undefined2 uStack_28;
  short sStack_26;
  short sStack_24;
  char cStack_22;
  char cStack_21;
  int aiStack_20 [4];
  int iStack_10;
  
  iVar2 = param_2 + 0x178;
  sVar1 = *(short *)(param_1 + 0x6a2);
  iVar3 = *(int *)(param_1 + 0x608) + sVar1 * 0x598;
  sStack_26 = *(short *)(iVar3 + 0x22);
  uStack_2a = *(undefined2 *)(iVar3 + *(short *)(param_1 + 0x6a0) * 0x60 + 0x326);
  cStack_21 = (char)uStack_2a;
  uStack_2c = *(undefined2 *)(iVar3 + 0x16);
  cStack_22 = (char)uStack_2c;
  iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + cStack_22 * 0x20;
  iStack_44 = iVar3 + 0x84;
  iStack_40 = iStack_44;
  iStack_3c = iVar2;
  uStack_28 = uStack_2a;
  sStack_24 = sStack_26;
  aiStack_20[0] = param_1;
  iStack_10 = param_2;
  Blackout__18CmdFormationMemberFP12CmdFormationiPcPc(iVar2,param_2,0xffffffffffffffff,0,0);
  if (((uint)*(ushort *)(iVar3 + 0x9e) & 1 << ((int)cStack_21 & 0x1fU)) != 0) {
    Blackout__18CmdFormationMemberFP12CmdFormationiPcPc(iVar2,iStack_10,0,&cStack_21,aiStack_20);
  }
  if (*(byte *)(iStack_10 + 0x23) >> 6 != 0) {
    puVar6 = auStack_50;
    uVar4 = *(uint *)(aiStack_20[0] + 0x608);
    sStack_2e = *(short *)(iStack_10 + 0xe52);
    uStack_34 = uVar4 + sStack_2e * 0x598;
    for (; uVar4 < uStack_34; uVar4 = uVar4 + 0x598) {
      if (sVar1 != *(short *)(uVar4 + 0x1e)) {
        uVar5 = uVar4 + 0x310;
        uStack_38 = uVar5 + sStack_24 * 0x60;
        for (; uVar5 < uStack_38; uVar5 = uVar5 + 0x60) {
          *puVar6 = (char)*(undefined2 *)(uVar5 + 0x16);
          puVar6 = puVar6 + 1;
        }
      }
    }
    Blackout__18CmdFormationMemberFP12CmdFormationiPcPc(iVar2,iStack_10,2,auStack_50,puVar6);
  }
  return;
}

/* JP: 0x00482650  CmdFormationTeam::Select(CmdFormation*, MenuPlace*, MenuPlace*)   [Select__16CmdFormationTeamFP12CmdFormationP9MenuPlaceP9MenuPlace]  size=0x2fc */
void Select__16CmdFormationTeamFP12CmdFormationP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  int iVar2;
  ulong uVar3;
  int iVar4;
  uint uVar5;
  
  if (param_4 != 0) {
    sVar1 = *(short *)(param_4 + 0x1e);
    iVar4 = *(int *)(param_1 + 0x608) + sVar1 * 0x598;
    SetCSA__8FontItemFUc(iVar4 + 0x50,0);
    *(undefined2 *)(iVar4 + 0x44) = 0x2000;
    uVar3 = (ulong)*(byte *)(iVar4 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar4 + 0x11) = (char)uVar3;
    *(byte *)(iVar4 + 0x10) =
         *(byte *)(iVar4 + 0x10) & 0xef | (byte)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
    iVar2 = param_1 + sVar1 * 0x108;
    for (uVar5 = iVar2 + 0x1e8; uVar5 < iVar2 + 0x3f8U; uVar5 = uVar5 + 0x84) {
      RemovePlace__10MenuWindowFP9MenuPlace(param_1,uVar5);
      AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x198,uVar5);
    }
    RemovePlace__9MenuGroupFP9MenuPlace(iVar4,param_1 + 0x6a4);
  }
  if (param_3 != 0) {
    sVar1 = *(short *)(param_3 + 0x1e);
    iVar4 = *(int *)(param_1 + 0x608) + sVar1 * 0x598;
    SetCSA__8FontItemFUc(iVar4 + 0x50,1);
    *(undefined2 *)(iVar4 + 0x44) = 0x8000;
    uVar3 = (ulong)*(byte *)(iVar4 + 0x11) & 0xffffffffffffffef | 0x10;
    *(char *)(iVar4 + 0x11) = (char)uVar3;
    *(byte *)(iVar4 + 0x10) =
         *(byte *)(iVar4 + 0x10) & 0xef | (byte)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
    iVar2 = param_1 + sVar1 * 0x108;
    for (uVar5 = iVar2 + 0x1e8; uVar5 < iVar2 + 0x3f8U; uVar5 = uVar5 + 0x84) {
      RemovePlace__9MenuGroupFP9MenuPlace(param_1 + 0x198,uVar5);
      AddPlace__10MenuWindowFP9MenuPlace(param_1,uVar5);
    }
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,param_1 + 0x6a4);
    *(short *)(param_1 + 0x6a2) = sVar1;
    UpdateScene__18CmdFormationMemberFP12CmdFormations
              (param_2 + 0x178,param_2,*(undefined2 *)(param_3 + 0x16));
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 0x6c),*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x40),
               *(undefined4 *)(iVar4 + 0xb0));
  }
  return;
}

/* JP: 0x00482950  CmdFormationTeam::MoveSlot(CmdFormation*, int)   [MoveSlot__16CmdFormationTeamFP12CmdFormationi]  size=0x364 */
void MoveSlot__16CmdFormationTeamFP12CmdFormationi(int param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  int iVar10;
  
  iVar7 = *(int *)(param_2 + 0x10);
  iVar9 = *(int *)(param_1 + 0x608) + *(short *)(param_1 + 0x6a2) * 0x598;
  sVar1 = *(short *)(param_1 + 0x6a0);
  if (param_3 != 0) {
    sVar3 = *(short *)(iVar9 + 0x22) + -1;
    sVar8 = sVar1 + (short)param_3;
    if ((-1 < sVar8) && (bVar2 = sVar3 < sVar8, sVar3 = sVar8, bVar2)) {
      sVar3 = 0;
    }
    *(short *)(param_1 + 0x6a0) = sVar3;
    iVar4 = iVar9 + sVar3 * 0x60;
    iVar5 = iVar9 + sVar3 * 0x60;
    iVar10 = iVar5 + 400;
    (**(code **)(*(int *)(iVar5 + 0x198) + 0x30))(iVar10,0,0xf8,0xc0);
    ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs(0x41900000,param_1,iVar9,iVar10,5);
    ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs
              (0x41800000,param_1,iVar9,iVar4 + 0x310,5);
    sVar3 = *(short *)(iVar4 + 0x326);
    if (sVar3 < 0) {
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_2 + 0x6c),*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x50));
    }
    else {
      piVar6 = (int *)FindPC__8CmdPartyFUs(iVar7 + 0xb8,sVar3);
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_2 + 0x6c),*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x48),
                 *piVar6 + 10);
    }
    ChoiceMember__16CmdFormationTeamFP12CmdFormation(param_1,param_2);
  }
  if (-1 < sVar1) {
    iVar7 = iVar9 + sVar1 * 0x60;
    iVar4 = iVar7 + 400;
    (**(code **)(*(int *)(iVar7 + 0x198) + 0x30))(iVar4,0x80,0x80,0x80);
    ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs
              (0xc1900000,param_1,iVar9,iVar4,0xfffffffffffffffb);
    ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs
              (0xc1800000,param_1,iVar9,iVar9 + sVar1 * 0x60 + 0x310,0xfffffffffffffffb);
  }
  return;
}

/* JP: 0x00482cc0  CmdFormationTeam::FindFace(short)   [FindFace__16CmdFormationTeamFs]  size=0xa8 */
uint FindFace__16CmdFormationTeamFs(int param_1,short param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x60c);
  uVar2 = uVar1 + *(short *)(param_1 + 0xae) * 0x40;
  while( true ) {
    if (uVar2 <= uVar1) {
      return 0;
    }
    if (param_2 == *(short *)(uVar1 + 0x38)) break;
    uVar1 = uVar1 + 0x40;
  }
  return uVar1;
}

/* JP: 0x00482d70  CmdFormationTeam::ScaleSprite(MenuGroup*, MenuSprite*, float, short)   [ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs]  size=0xa8 */
void ScaleSprite__16CmdFormationTeamFP9MenuGroupP10MenuSpritefs
               (undefined4 param_1,undefined8 param_2,undefined4 param_3,int param_4,short param_5)

{
  SetScale__10MenuSpriteFf(param_1,param_4);
  *(short *)(param_4 + 0x14) = param_5 + *(short *)(param_4 + 0x14);
  RemovePlace__9MenuGroupFP9MenuPlace(param_3,param_4);
  AddPlace__9MenuGroupFP9MenuPlace(param_3,param_4);
  return;
}

/* JP: 0x00482e20  CmdFormationTeam::ResetTeam(CmdFormation*)   [ResetTeam__16CmdFormationTeamFP12CmdFormation]  size=0x134 */
void ResetTeam__16CmdFormationTeamFP12CmdFormation(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x608) + *(short *)(param_1 + 0x6a2) * 0x598;
  uVar1 = *(undefined2 *)(iVar4 + 0x16);
  iVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  for (uVar3 = iVar4 + 0x310; uVar3 < iVar4 + 0x490U; uVar3 = uVar3 + 0x60) {
    *(undefined2 *)(uVar3 + 0x16) = 0xffff;
    *(byte *)(uVar3 + 0x12) = *(byte *)(uVar3 + 0x12) & 0xfe;
  }
  *(undefined1 *)(iVar2 + (char)uVar1 * 0x20 + 0x95) = 0;
  UpdateScene__18CmdFormationMemberFP12CmdFormations(param_2 + 0x178,param_2,uVar1);
  ChoiceMember__16CmdFormationTeamFP12CmdFormation(param_1,param_2);
  return;
}

/* JP: 0x00482f60  CmdFormationTeam::IsFull(CmdFormation*)   [IsFull__16CmdFormationTeamFP12CmdFormation]  size=0xdc */
undefined4 IsFull__16CmdFormationTeamFP12CmdFormation(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *(uint *)(param_1 + 0x608);
  uVar3 = uVar2 + *(short *)(param_2 + 0xe52) * 0x598;
  do {
    if (uVar3 <= uVar2) {
      return 1;
    }
    for (uVar1 = uVar2 + 0x310; uVar1 < uVar2 + 0x490; uVar1 = uVar1 + 0x60) {
      if (*(short *)(uVar1 + 0x16) < 0) {
        return 0;
      }
    }
    uVar2 = uVar2 + 0x598;
  } while( true );
}

/* JP: 0x00483040  CmdFormationTeam::IsBlank(CmdFormation*, short, short)   [IsBlank__16CmdFormationTeamFP12CmdFormationss]  size=0xe8 */
undefined4
IsBlank__16CmdFormationTeamFP12CmdFormationss
          (int param_1,undefined8 param_2,short param_3,short param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = *(int *)(param_1 + 0x608) + param_3 * 0x598;
  uVar3 = uVar2 + param_4 * 0x598;
  do {
    if (uVar3 <= uVar2) {
      return 1;
    }
    for (uVar1 = uVar2 + 0x310; uVar1 < uVar2 + 0x490; uVar1 = uVar1 + 0x60) {
      if (-1 < *(short *)(uVar1 + 0x16)) {
        return 0;
      }
    }
    uVar2 = uVar2 + 0x598;
  } while( true );
}

/* JP: 0x00483130  CmdFormationTeam::~CmdFormationTeam()   [@24@__dt__16CmdFormationTeamFv]  size=0x8 */
undefined4 * _24___dt__16CmdFormationTeamFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdFormationTeam;
    *param_1 = 0x408f04;
    param_1[3] = 0x408f10;
    if (param_1[0x17c] != 0) {
      __destroy_new_array(param_1[0x17c],0x481000);
    }
    if (param_1[0x17d] != 0) {
      uVar2 = param_1[0x17d];
      uVar3 = uVar2 + *(short *)((int)param_1 + 0x96) * 0x40;
      for (; uVar2 < uVar3; uVar2 = uVar2 + 0x40) {
        *(undefined4 *)(uVar2 + 0x14) = 0;
      }
      __destroy_new_array(param_1[0x17d],0x2677a0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x1a3,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x17e,0x2670d0,0x30,3);
    __destroy_arr(param_1 + 0x74,0x2766d0,0x84,8);
    __dt__9MenuGroupFv(param_1 + 0x60,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x48,0x277890,0x30,2);
    __dt__11MenuTextureFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00483140  CmdFormationTeam::~CmdFormationTeam()   [@36@__dt__16CmdFormationTeamFv]  size=0x8 */
undefined4 * _36___dt__16CmdFormationTeamFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdFormationTeam;
    param_1[-3] = 0x408f04;
    *param_1 = 0x408f10;
    if (param_1[0x179] != 0) {
      __destroy_new_array(param_1[0x179],0x481000);
    }
    if (param_1[0x17a] != 0) {
      uVar2 = param_1[0x17a];
      uVar3 = uVar2 + *(short *)((int)param_1 + 0x8a) * 0x40;
      for (; uVar2 < uVar3; uVar2 = uVar2 + 0x40) {
        *(undefined4 *)(uVar2 + 0x14) = 0;
      }
      __destroy_new_array(param_1[0x17a],0x2677a0);
    }
    __dt__11MenuPolygonFv(param_1 + 0x1a0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x17b,0x2670d0,0x30,3);
    __destroy_arr(param_1 + 0x71,0x2766d0,0x84,8);
    __dt__9MenuGroupFv(param_1 + 0x5d,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x45,0x277890,0x30,2);
    __dt__11MenuTextureFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
