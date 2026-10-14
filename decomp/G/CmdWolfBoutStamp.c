/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdWolfBoutStamp   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdWolfBoutStamp.md).
 */

/* JP: 0x00485250  CmdWolfBoutStamp::CmdWolfBoutStamp()   [__ct__16CmdWolfBoutStampFv]  size=0xc4 */
int __ct__16CmdWolfBoutStampFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdWolfBoutStamp;
  *(undefined4 *)(param_1 + 0x18) = 0x408fc4;
  *(undefined4 *)(param_1 + 0x24) = 0x408fd0;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  __ct__11MenuTextureFv(param_1 + 0x188);
  __ct__11SendOnLocalFv(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x1f8) = 0;
  __ct__10ScrollMarkFv(param_1 + 0x1fc);
  return param_1;
}

/* JP: 0x00485320  CmdWolfBoutStamp::~CmdWolfBoutStamp()   [__dt__16CmdWolfBoutStampFv]  size=0x134 */
int __dt__16CmdWolfBoutStampFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdWolfBoutStamp;
    *(undefined4 *)(param_1 + 0x18) = 0x408fc4;
    *(undefined4 *)(param_1 + 0x24) = 0x408fd0;
    if (*(int *)(param_1 + 0x1f8) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x1f8),0x2661a0);
    }
    __dt__10ScrollMarkFv(param_1 + 0x1fc,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x1c8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x188,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00485460  CmdWolfBoutStamp::CreateScene(CmdWolfBout*, short)   [CreateScene__16CmdWolfBoutStampFP11CmdWolfBouts]  size=0x5e0 */
void CreateScene__16CmdWolfBoutStampFP11CmdWolfBouts(int param_1,int param_2,short param_3)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  undefined8 uVar6;
  ushort uVar7;
  ushort uVar8;
  short sVar9;
  byte *pbVar10;
  
  iVar5 = *(int *)(*(int *)(param_2 + 0x58) + 0x5c);
  uVar2 = *(ushort *)(*(int *)(param_2 + 0x8c) + 4) & 0xff;
  uVar3 = (ushort)*(byte *)(*(int *)(iVar5 + 4) + 0xe43);
  uVar7 = 0;
  bVar1 = true;
  if (param_3 == 0) {
    uVar8 = uVar2;
    if (uVar3 <= uVar2) {
      bVar1 = false;
      uVar8 = uVar3;
    }
  }
  else {
    uVar8 = uVar3 - uVar2;
    uVar7 = uVar2;
  }
  pbVar10 = (byte *)(*(int *)(iVar5 + 4) + 0xe44 + (int)(short)uVar7);
  if (uVar8 != 0) {
    uVar6 = __nwa__FUi((short)uVar8 * 0x60 + 0x10);
    iVar5 = __construct_new_array(uVar6,0x266140,0x2661a0,0x60,uVar8);
    *(int *)(param_1 + 0x1f8) = iVar5;
    sVar9 = 0;
    sVar4 = uVar7 + uVar8;
    for (; (short)uVar7 < sVar4; uVar7 = uVar7 + 1) {
      SetData__9MenuSceneFUsP10MenuSprite(param_2,uVar7 + 2,iVar5);
      *(ushort *)(iVar5 + 0x16) = (ushort)*pbVar10;
      *(ushort *)(iVar5 + 0x22) = uVar7;
      *(short *)(iVar5 + 0x1c) = sVar9 % 3;
      *(short *)(iVar5 + 0x1e) = sVar9 / 3;
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
      pbVar10 = pbVar10 + 1;
      iVar5 = iVar5 + 0x60;
      sVar9 = sVar9 + 1;
    }
    Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x188,
                    *(undefined4 *)
                     (((int)param_3 + 3U & 0xffff) * 0xc + *(int *)(param_2 + 0x54) + 0x10),0x30,0,0
                   );
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1c8,param_1 + 0x1a0,*(undefined4 *)(param_1 + 0x19c),1,
                    0xffffffffffffffff);
    *(short *)(param_1 + 0x1dc) = *(short *)(*(int *)(param_1 + 0x1f8) + 0x14) + -1;
    AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x1c8);
  }
  SetData__9MenuSceneFUsP10MenuSprite(param_2,param_3,param_1 + 0x128);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,
                  *(undefined4 *)
                   (((int)param_3 + 1U & 0xffff) * 0xc + *(int *)(param_2 + 0x54) + 0x10),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(param_1 + 0x13c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,param_3,param_1);
  AddOT__7MenuObjFv(param_1);
  if (bVar1) {
    Create__10ScrollMarkFUcP10MenuWindowUc(param_1 + 0x1fc,1 << (((int)param_3 ^ 1U) & 0x1f) & 0xff,0,0);
    *(int *)(param_1 + 0x44) = param_1 + 0x1fc;
    *(byte *)(param_1 + 0xb2) = *(byte *)(param_1 + 0xb2) & 0xfd | 2;
    SetArea__10ScrollMarkFUcffff(0xbf800000,0xbf800000,*(float *)(param_1 + 0x6c) + 2.0,
                    *(float *)(param_1 + 0x70) + 2.0,*(undefined4 *)(param_1 + 0x44),
                    *(undefined1 *)(param_1 + 0xa9));
  }
  *(short *)(param_1 + 0xae) = param_3;
  return;
}

/* JP: 0x00485a40  CmdWolfBoutStamp::Select(CmdWolfBout*, MenuPlace*, MenuPlace*)   [Select__16CmdWolfBoutStampFP11CmdWolfBoutP9MenuPlaceP9MenuPlace]  size=0xb4 */
void Select__16CmdWolfBoutStampFP11CmdWolfBoutP9MenuPlaceP9MenuPlace
               (undefined8 param_1,int param_2,int param_3)

{
  if (param_3 != 0) {
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(*(int *)(param_2 + 0x58) + 100),
               *(undefined4 *)
                ((*(short *)(param_2 + 0x88) * 0xc + (int)*(short *)(param_2 + 0x88)) * 4 +
                 *(int *)(param_2 + 0x8c) + 0x14));
  }
  return;
}

/* JP: 0x00485b00  CmdWolfBoutStamp::~CmdWolfBoutStamp()   [@24@__dt__16CmdWolfBoutStampFv]  size=0x8 */
undefined4 * _24___dt__16CmdWolfBoutStampFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdWolfBoutStamp;
    *param_1 = 0x408fc4;
    param_1[3] = 0x408fd0;
    if (param_1[0x78] != 0) {
      __destroy_new_array(param_1[0x78],0x2661a0);
    }
    __dt__10ScrollMarkFv(param_1 + 0x79,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x6c,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00485b10  CmdWolfBoutStamp::~CmdWolfBoutStamp()   [@36@__dt__16CmdWolfBoutStampFv]  size=0x8 */
undefined4 * _36___dt__16CmdWolfBoutStampFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdWolfBoutStamp;
    param_1[-3] = 0x408fc4;
    *param_1 = 0x408fd0;
    if (param_1[0x75] != 0) {
      __destroy_new_array(param_1[0x75],0x2661a0);
    }
    __dt__10ScrollMarkFv(param_1 + 0x76,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x69,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x59,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
