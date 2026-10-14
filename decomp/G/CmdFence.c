/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFence   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFence.md).
 */

/* JP: 0x0049af80  CmdFence::CmdFence()   [__ct__8CmdFenceFv]  size=0xa4 */
int __ct__8CmdFenceFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdFence;
  *(undefined4 *)(param_1 + 0x18) = 0x4094d4;
  *(undefined4 *)(param_1 + 0x24) = 0x4094e0;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__8FontDrawFv(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0x168) = 0;
  *(undefined4 *)(param_1 + 0x16c) = 0;
  *(undefined4 *)(param_1 + 0x170) = 0;
  return param_1;
}

/* JP: 0x0049b030  CmdFence::~CmdFence()   [__dt__8CmdFenceFv]  size=0x164 */
int __dt__8CmdFenceFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdFence;
    *(undefined4 *)(param_1 + 0x18) = 0x4094d4;
    *(undefined4 *)(param_1 + 0x24) = 0x4094e0;
    if (*(int *)(param_1 + 0x168) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x168),0x2661a0);
      *(undefined4 *)(param_1 + 0x168) = 0;
    }
    if (*(int *)(param_1 + 0x16c) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x16c),0x27c030);
      *(undefined4 *)(param_1 + 0x16c) = 0;
    }
    if (*(int *)(param_1 + 0x170) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x170),0x2766d0);
      *(undefined4 *)(param_1 + 0x170) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0049b1a0  CmdFence::CreateFence(MenuScene*, unsigned char*)   [CreateFence__8CmdFenceFP9MenuScenePUc]  size=0x544 */
void CreateFence__8CmdFenceFP9MenuScenePUc(int param_1,int param_2,int param_3)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  undefined4 uStack_10;
  
  sVar7 = 0;
  sVar1 = *(short *)(*(int *)(param_2 + 0x3c) + 0x10);
  uVar4 = __nwa__FUi(sVar1 * 0x60 + 0x10);
  uVar2 = __construct_new_array(uVar4,0x266140,0x2661a0,0x60,(int)sVar1);
  *(undefined4 *)(param_1 + 0x168) = uVar2;
  if (*(int *)(param_2 + 0x44) == 0) {
    uVar8 = 0;
  }
  else {
    uVar8 = *(uint *)(*(int *)(param_2 + 0x44) + 8) & 0xffff;
  }
  if (uVar8 != 0) {
    sVar7 = *(short *)(*(int *)(param_2 + 0x44) + 0x10);
    if (sVar7 != 0) {
      SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0x128);
      AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x128);
      uVar4 = __nwa__FUi(sVar7 * 0x80 + 0x10);
      uVar2 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,sVar7);
      *(undefined4 *)(param_1 + 0x16c) = uVar2;
      iVar3 = *(int *)(param_1 + 0x16c);
      for (sVar6 = 0; sVar6 < sVar7; sVar6 = sVar6 + 1) {
        SetData__9MenuSceneFUsP8MenuText(param_2,sVar6,iVar3);
        SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)
                               ((uint)*(ushort *)(iVar3 + 0x22) * 8 + *(int *)(param_2 + 0x24) +
                               0x10),*(byte *)(iVar3 + 0x58) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x128,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
        AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
        iVar3 = iVar3 + 0x80;
      }
    }
  }
  if (*(int *)(param_2 + 0x40) == 0) {
    uVar8 = 0;
  }
  else {
    uVar8 = *(uint *)(*(int *)(param_2 + 0x40) + 8) & 0xffff;
  }
  sVar6 = (short)uVar8;
  if (uVar8 != 0) {
    uVar4 = __nwa__FUi(sVar6 * 0x84 + 0x10);
    iVar3 = __construct_new_array(uVar4,0x276640,0x2766d0,0x84,sVar6);
    *(int *)(param_1 + 0x170) = iVar3;
    for (sVar5 = 0; sVar5 < sVar6; sVar5 = sVar5 + 1) {
      SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar5,iVar3);
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
      iVar3 = iVar3 + 0x84;
    }
  }
  iVar3 = *(int *)(param_1 + 0x168);
  for (sVar6 = 0; sVar6 < sVar1; sVar6 = sVar6 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar6,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    iVar3 = iVar3 + 0x60;
  }
  uStack_10 = param_3;
  if (param_3 == 0) {
    uStack_10 = *(int *)(*(int *)(param_2 + 0x54) + 0x10);
  }
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,uStack_10,0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(*(int *)(param_1 + 0x168) + 0x14) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  *(short *)(param_1 + 0xae) = sVar7;
  return;
}

/* JP: 0x0049b6f0  CmdFence::SetTitle(MenuScene*, short)   [SetTitle__8CmdFenceFP9MenuScenes]  size=0x174 */
void SetTitle__8CmdFenceFP9MenuScenes(int param_1,int param_2,ushort param_3)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  ushort uStack_10;
  
  ClearImage__8FontDrawFv(param_1 + 0x128);
  puVar3 = (undefined4 *)((uint)param_3 * 8 + *(int *)(param_2 + 0x24) + 0x10);
  sVar1 = *(short *)(param_1 + 0xae);
  iVar2 = *(int *)(param_1 + 0x16c);
  for (uStack_10 = param_3; (short)uStack_10 < (short)(sVar1 + param_3); uStack_10 = uStack_10 + 1)
  {
    SetMessage__8MenuTextFPcUiUcUc(iVar2,*puVar3,*(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x128,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              ((float)(int)*(short *)(puVar3 + 1),(float)(int)*(short *)((int)puVar3 + 6));
    iVar2 = iVar2 + 0x80;
    puVar3 = puVar3 + 2;
  }
  return;
}

/* JP: 0x0049b870  CmdFence::~CmdFence()   [@24@__dt__8CmdFenceFv]  size=0x8 */
undefined4 * _24___dt__8CmdFenceFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__8CmdFence;
    *param_1 = 0x4094d4;
    param_1[3] = 0x4094e0;
    if (param_1[0x54] != 0) {
      __destroy_new_array(param_1[0x54],0x2661a0);
      param_1[0x54] = 0;
    }
    if (param_1[0x55] != 0) {
      __destroy_new_array(param_1[0x55],0x27c030);
      param_1[0x55] = 0;
    }
    if (param_1[0x56] != 0) {
      __destroy_new_array(param_1[0x56],0x2766d0);
      param_1[0x56] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0049b880  CmdFence::~CmdFence()   [@36@__dt__8CmdFenceFv]  size=0x8 */
undefined4 * _36___dt__8CmdFenceFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__8CmdFence;
    param_1[-3] = 0x4094d4;
    *param_1 = 0x4094e0;
    if (param_1[0x51] != 0) {
      __destroy_new_array(param_1[0x51],0x2661a0);
      param_1[0x51] = 0;
    }
    if (param_1[0x52] != 0) {
      __destroy_new_array(param_1[0x52],0x27c030);
      param_1[0x52] = 0;
    }
    if (param_1[0x53] != 0) {
      __destroy_new_array(param_1[0x53],0x2766d0);
      param_1[0x53] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
