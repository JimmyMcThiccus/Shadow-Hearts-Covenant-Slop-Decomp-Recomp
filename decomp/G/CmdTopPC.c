/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTopPC   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTopPC.md).
 */

/* JP: 0x00451bc0  CmdTopPC::CmdTopPC()   [__ct__8CmdTopPCFv]  size=0x16c */
int __ct__8CmdTopPCFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdTopPC;
  *(undefined4 *)(param_1 + 0x18) = 0x408194;
  *(undefined4 *)(param_1 + 0x24) = 0x4081a0;
  __ct__11SendOnLocalFv(param_1 + 0xb8);
  __ct__8FontDrawFv(param_1 + 0xe8);
  __construct_array(param_1 + 0x128,0x276640,0x2766d0,0x84,7);
  __construct_array(param_1 + 0x4c4,0x276640,0x2766d0,0x84,4);
  __construct_array(param_1 + 0x6d8,0x451fa0,0x451d30,0xd70,8);
  __construct_array(param_1 + 0x7258,0x28d000,0x28d070,0x28,2);
  *(undefined2 *)(param_1 + 0x72a8) = 0;
  __ct__11MenuTextureFv(param_1 + 0x72b0);
  __ct__11SendOnLocalFv(param_1 + 0x72f0);
  __construct_array(param_1 + 0x7320,0x266140,0x2661a0,0x60,4);
  return param_1;
}

/* JP: 0x00452150  CmdTopPC::~CmdTopPC()   [__dt__8CmdTopPCFv]  size=0x184 */
int __dt__8CmdTopPCFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdTopPC;
    *(undefined4 *)(param_1 + 0x18) = 0x408194;
    *(undefined4 *)(param_1 + 0x24) = 0x4081a0;
    __destroy_arr(param_1 + 0x7320,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x72f0,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x72b0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x7258,0x28d070,0x28,2);
    __destroy_arr(param_1 + 0x6d8,0x451d30,0xd70,8);
    __destroy_arr(param_1 + 0x4c4,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x128,0x2766d0,0x84,7);
    __dt__8FontDrawFv(param_1 + 0xe8,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004522e0  CmdTopPC::CreateScene(CmdTop*)   [CreateScene__8CmdTopPCFP6CmdTop]  size=0xb1c */
void CreateScene__8CmdTopPCFP6CmdTop(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int *piVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  short sVar10;
  int iVar11;
  short sVar12;
  int iVar13;
  int iVar14;
  float fStack_60;
  
  iVar13 = *(int *)(param_2 + 0x10);
  sVar6 = *(short *)(iVar13 + 0xc6);
  cVar1 = *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80);
  iVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  iVar7 = param_1 + 0x6d8;
  iVar8 = param_1 + 0x7320;
  fStack_60 = 0.0;
  *(int *)(param_1 + 0xb4) = iVar13 + 0xb8;
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xe8);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xe8);
  for (sVar12 = 0; sVar12 < sVar6; sVar12 = sVar12 + 1) {
    piVar5 = *(int **)(iVar13 + 0xb8 + sVar12 * 4 + 0x10);
    puVar9 = (undefined4 *)FindAttachFile__9MenuSceneCFs(param_2,*(undefined2 *)(*piVar5 + 8));
    Create__11MenuTextureFPUc6GS_PSMUii(iVar7 + 0x50,*puVar9,0x30,0,0);
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iVar7 + 0x90,iVar7 + 0x68,*(undefined4 *)(iVar7 + 100),1,0xffffffffffffffff);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,8,iVar7 + 0xc0);
    *(int *)(iVar7 + 0x11c) = iVar7 + 0x90;
    *(byte *)(iVar7 + 0xd2) = *(byte *)(iVar7 + 0xd2) & 0xdf;
    AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar7 + 0xc0);
    SetData__9MenuSceneFUsP8MenuText(param_2,2,iVar7 + 0x120);
    SetMessage__8MenuTextFPcUiUcUc(iVar7 + 0x120,*piVar5 + 10,*(byte *)(iVar7 + 0x178) & 7,0,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xe8,iVar7 + 0x120,((ulong)*(byte *)(iVar7 + 0x178) & 0xf) >> 3,0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar7 + 0x120);
    SetData__9MenuSceneFUsP8MenuFont(param_2,0,iVar7 + 0x1a0);
    SetData__9MenuSceneFUsP8MenuFont(param_2,4,iVar7 + 0x250);
    (**(code **)(*(int *)(iVar7 + 0x1a8) + 0x68))
              (iVar7 + 0x1a0,
               *(undefined4 *)
                ((uint)*(ushort *)(iVar7 + 0x1c2) * 8 + *(int *)(param_2 + 0x24) + 0x10));
    (**(code **)(*(int *)(iVar7 + 600) + 0x68))
              (iVar7 + 0x250,
               *(undefined4 *)
                ((uint)*(ushort *)(iVar7 + 0x272) * 8 + *(int *)(param_2 + 0x24) + 0x10),
               *(undefined1 *)(*piVar5 + 3));
    AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar7 + 0x1a0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar7 + 0x250);
    iVar11 = iVar7 + 0x460;
    for (sVar10 = 0; sVar10 < 3; sVar10 = sVar10 + 1) {
      sVar2 = *(short *)((int)piVar5 + sVar10 * 2 + 10);
      sVar3 = *(short *)((int)piVar5 + sVar10 * 2 + 0x10);
      iVar14 = iVar11 + 0xb0;
      SetData__9MenuSceneFUsP8MenuFont(param_2,sVar10 + 1,iVar11);
      SetData__9MenuSceneFUsP8MenuFont(param_2,sVar10 + 5,iVar14);
      SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar10 + 2,iVar11 + 0x160);
      SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar10 + 5,iVar11 + 0x1c0);
      (**(code **)(*(int *)(iVar11 + 8) + 0x68))
                (iVar11,*(undefined4 *)
                         ((uint)*(ushort *)(iVar11 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10));
      SetBar__7MenuBarFv(iVar11 + 0x1c0);
      SetRange__7MenuBarFii(iVar11 + 0x1c0,sVar2,sVar3);
      (**(code **)(*(int *)(iVar11 + 0xb8) + 0x68))
                (iVar14,*(undefined4 *)
                         ((uint)*(ushort *)(iVar11 + 0xd2) * 8 + *(int *)(param_2 + 0x24) + 0x10),
                 sVar2,sVar3);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar14);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar11);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar11 + 0x160);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar11 + 0x1c0);
      if (sVar10 < 2) {
        if ((float)(int)sVar2 / (float)(int)sVar3 < 0.25) {
          SetFontColor__14PluralFontItemFUsUsUcUcUc(iVar14,0,3,0xc4,0,0);
        }
        else if ((float)(int)sVar2 / (float)(int)sVar3 < 0.5) {
          SetFontColor__14PluralFontItemFUsUsUcUcUc(iVar14,0,3,0xc4,0xc4,0);
        }
      }
      iVar11 = iVar11 + 0x228;
    }
    iVar11 = iVar7 + 0xad8;
    for (sVar10 = 0; sVar10 < 5; sVar10 = sVar10 + 1) {
      SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar10,iVar11);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar11);
      iVar11 = iVar11 + 0x84;
    }
    if ((long)sVar12 < (long)*(char *)(iVar4 + cVar1 * 0x20 + 0x95)) {
      SetData__9MenuSceneFUsP10MenuSprite(param_2,9,iVar8);
      AddPlace__9MenuGroupFP9MenuPlace(iVar7,iVar8);
      iVar8 = iVar8 + 0x60;
    }
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar7);
    *(short *)(iVar7 + 0x16) = sVar12;
    *(ushort *)(iVar7 + 0x22) = (ushort)*(byte *)(*piVar5 + 2);
    *(undefined2 *)(iVar7 + 0x1c) = 0;
    *(short *)(iVar7 + 0x1e) = sVar12;
    (**(code **)(*(int *)(iVar7 + 8) + 0x24))
              (*(undefined4 *)(iVar7 + 0x24),fStack_60 + *(float *)(iVar7 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar7);
    fStack_60 = fStack_60 + *(float *)(iVar7 + 0x30);
    iVar7 = iVar7 + 0xd70;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb8,iVar13 + 0x4b8,*(undefined4 *)(iVar13 + 0x4b4),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0xcc) = *(short *)(param_1 + 0xcac) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb8);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x72b0,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x40),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x72f0,param_1 + 0x72c8,*(undefined4 *)(param_1 + 0x72c4),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x7304) = *(short *)(param_1 + 0x7334) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x72f0);
  iVar13 = param_1 + 0x4c4;
  for (sVar6 = 5; sVar6 < 9; sVar6 = sVar6 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar6,iVar13);
    iVar13 = iVar13 + 0x84;
  }
  CreatePacket__10MenuPacketFUs(param_1 + 0x7270,4);
  SetRegister__12MenuRegisterFiUlUl(param_1 + 0x7258,0,0x42,0x48);
  *(short *)(param_1 + 0x726c) = *(short *)(param_1 + 0x4d8) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x7258);
  CreatePacket__10MenuPacketFUs(param_1 + 0x7298,4);
  SetRegister__12MenuRegisterFiUlUl(param_1 + 0x7280,0,0x42,0x44);
  *(short *)(param_1 + 0x7294) = *(short *)(param_1 + 0x4d8) + 1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x7280);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00452e00  CmdTopPC::Select(CmdTop*, MenuGroup*, MenuGroup*)   [Select__8CmdTopPCFP6CmdTopP9MenuGroupP9MenuGroup]  size=0x274 */
void Select__8CmdTopPCFP6CmdTopP9MenuGroupP9MenuGroup
               (int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_4 != 0) {
    iVar1 = param_1 + *(short *)(param_4 + 0x16) * 0xd70;
    SetCSA__8FontItemFUc(iVar1 + 0x7f8,0);
    SetScale__10MenuSpriteFf(0xc1000000,iVar1 + 0x798);
    iVar3 = param_1 + 0x4c4;
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      RemovePlace__9MenuGroupFP9MenuPlace(param_4,iVar3);
      iVar3 = iVar3 + 0x84;
    }
    iVar1 = iVar1 + 0x11b0;
    for (iVar2 = 0; iVar2 < 5; iVar2 = iVar2 + 1) {
      *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfe | 1;
      iVar1 = iVar1 + 0x84;
    }
  }
  if (param_3 != 0) {
    iVar1 = param_1 + *(short *)(param_3 + 0x16) * 0xd70;
    SetCSA__8FontItemFUc(iVar1 + 0x7f8,1);
    SetScale__10MenuSpriteFf(0x41000000,iVar1 + 0x798);
    param_1 = param_1 + 0x4c4;
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      AddPlace__9MenuGroupFP9MenuPlace(param_3,param_1);
      param_1 = param_1 + 0x84;
    }
    iVar1 = iVar1 + 0x11b0;
    for (iVar2 = 0; iVar2 < 5; iVar2 = iVar2 + 1) {
      *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xfe;
      iVar1 = iVar1 + 0x84;
    }
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 0x7c),
               *(undefined4 *)
                ((uint)*(ushort *)(param_2 + 0x1e) * 8 + *(int *)(param_2 + 0x24) + 0x10));
  }
  return;
}

/* JP: 0x00453080  CmdTopPC::BlinkSelect()   [BlinkSelect__8CmdTopPCFv]  size=0x170 */
void BlinkSelect__8CmdTopPCFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x72a8) = *(short *)(param_1 + 0x72a8) + (short)sm_iPassTime__7MenuObj;
  if (0x3c0 < *(short *)(param_1 + 0x72a8)) {
    *(short *)(param_1 + 0x72a8) = *(short *)(param_1 + 0x72a8) + -0x780;
  }
  if (*(short *)(param_1 + 0x72a8) < 0) {
    iVar1 = -(int)*(short *)(param_1 + 0x72a8);
  }
  else {
    iVar1 = (int)*(short *)(param_1 + 0x72a8);
  }
  param_1 = param_1 + 0x4c4;
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    (**(code **)(*(int *)(param_1 + 8) + 0x2c))(param_1,0x60 - (iVar1 / 0x28 & 0xffU) & 0xff);
    param_1 = param_1 + 0x84;
  }
  return;
}

/* JP: 0x004531f0  CmdTopPC::SetTarget(short)   [SetTarget__8CmdTopPCFs]  size=0x240 */
short SetTarget__8CmdTopPCFs(int param_1,short param_2)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  long lVar4;
  char cVar5;
  short sVar6;
  short sVar7;
  
  iVar2 = *(int *)(param_1 + 0xb4);
  param_1 = param_1 + 0x6d8;
  sVar1 = *(short *)(iVar2 + 0xe);
  sVar7 = 0;
  for (sVar6 = 0; sVar6 < sVar1; sVar6 = sVar6 + 1) {
    piVar3 = *(int **)(iVar2 + sVar6 * 4 + 0x10);
    cVar5 = '\x01';
    if (param_2 == 2) {
      if (*(char *)(piVar3[1] + 0x32) == -1) {
        cVar5 = '\0';
      }
    }
    else if (param_2 == 1) {
      if (((char)piVar3[0x10] == -1) ||
         (lVar4 = CreateMagic__5CmdPCFP8CmdPartysPc(piVar3,iVar2,0,0), lVar4 == 0)) {
        cVar5 = '\0';
      }
    }
    else if ((param_2 == 0) && (*(char *)(*piVar3 + 2) != '\v')) {
      cVar5 = '\0';
    }
    *(byte *)(param_1 + 0x21) = *(byte *)(param_1 + 0x21) & 0xfd | cVar5 << 1;
    if (cVar5 == '\0') {
      (**(code **)(*(int *)(param_1 + 8) + 0x34))(0x3f000000);
    }
    else {
      sVar7 = sVar7 + 1;
    }
    SetCommand__5CmdPCFc(piVar3,cVar5 + -1);
    param_1 = param_1 + 0xd70;
  }
  return sVar7;
}

/* JP: 0x00453430  CmdTopPC::ClearTarget()   [ClearTarget__8CmdTopPCFv]  size=0xf0 */
void ClearTarget__8CmdTopPCFv(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  iVar2 = param_1 + 0x6d8;
  sVar1 = *(short *)(*(int *)(param_1 + 0xb4) + 0xe);
  for (sVar3 = 0; sVar3 < sVar1; sVar3 = sVar3 + 1) {
    if (-1 < (long)((ulong)*(byte *)(iVar2 + 0x21) << 0x3e)) {
      *(byte *)(iVar2 + 0x21) = *(byte *)(iVar2 + 0x21) & 0xfd | 2;
      (**(code **)(*(int *)(iVar2 + 8) + 0x34))(0x40000000);
    }
    iVar2 = iVar2 + 0xd70;
  }
  return;
}

/* JP: 0x00453520  CmdTopPC::~CmdTopPC()   [@24@__dt__8CmdTopPCFv]  size=0x8 */
undefined4 * _24___dt__8CmdTopPCFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__8CmdTopPC;
    *param_1 = 0x408194;
    param_1[3] = 0x4081a0;
    __destroy_arr(param_1 + 0x1cc2,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x1cb6,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1ca6,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x1c90,0x28d070,0x28,2);
    __destroy_arr(param_1 + 0x1b0,0x451d30,0xd70,8);
    __destroy_arr(param_1 + 299,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x44,0x2766d0,0x84,7);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00453530  CmdTopPC::~CmdTopPC()   [@36@__dt__8CmdTopPCFv]  size=0x8 */
undefined4 * _36___dt__8CmdTopPCFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__8CmdTopPC;
    param_1[-3] = 0x408194;
    *param_1 = 0x4081a0;
    __destroy_arr(param_1 + 0x1cbf,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x1cb3,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1ca3,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x1c8d,0x28d070,0x28,2);
    __destroy_arr(param_1 + 0x1ad,0x451d30,0xd70,8);
    __destroy_arr(param_1 + 0x128,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x41,0x2766d0,0x84,7);
    __dt__8FontDrawFv(param_1 + 0x31,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
