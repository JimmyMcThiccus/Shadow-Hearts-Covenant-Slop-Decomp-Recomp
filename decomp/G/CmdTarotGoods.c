/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTarotGoods   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTarotGoods.md).
 */

/* JP: 0x00455ce0  CmdTarotGoods::CmdTarotGoods()   [__ct__13CmdTarotGoodsFv]  size=0x84 */
int __ct__13CmdTarotGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdTarotGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x408314;
  *(undefined4 *)(param_1 + 0x24) = 0x408320;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xe4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x00455d70  CmdTarotGoods::~CmdTarotGoods()   [__dt__13CmdTarotGoodsFv]  size=0xec */
int __dt__13CmdTarotGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdTarotGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x408314;
    *(undefined4 *)(param_1 + 0x24) = 0x408320;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x455e60);
      *(undefined4 *)(param_1 + 0x124) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00455ef0  CmdTarotGoods::CreateScene(CmdTarot*)   [CreateScene__13CmdTarotGoodsFP8CmdTarot]  size=0x318 */
void CreateScene__13CmdTarotGoodsFP8CmdTarot(int param_1,int param_2)

{
  undefined2 uVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uStack_28;
  
  uVar2 = *(ushort *)(param_2 + 0x312);
  uVar3 = *(uint *)(*(int *)(*(int *)(*(int *)(param_2 + 0x58) + 0x5c) + 4) + 0xdab);
  uVar5 = __nwa__FUi(((uint)uVar2 * 0x12 + (uint)uVar2) * 0x10 + 0x10);
  uVar4 = __construct_new_array(uVar5,0x456210,0x455e60,0x130,(uint)uVar2);
  *(undefined4 *)(param_1 + 0x124) = uVar4;
  iVar6 = *(int *)(param_1 + 0x124);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  uStack_28 = 0.0;
  *(undefined2 *)(param_1 + 0xae) = 0;
  for (uVar7 = 0; uVar7 < uVar2; uVar7 = uVar7 + 1 & 0xffff) {
    if ((uVar3 & 1 << (uVar7 & 0x1f)) != 0) {
      SetData__9MenuSceneFUsP10MenuSprite(param_2,1,iVar6 + 0x50);
      SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(iVar6 + 0x72),iVar6 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0xb0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0x50);
      SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar6);
      *(short *)(iVar6 + 0x16) = (short)uVar7;
      uVar1 = *(undefined2 *)(param_1 + 0xae);
      *(undefined2 *)(iVar6 + 0x1c) = 0;
      *(undefined2 *)(iVar6 + 0x1e) = uVar1;
      (**(code **)(*(int *)(iVar6 + 8) + 0x24))(*(undefined4 *)(iVar6 + 0x24),uStack_28);
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar6);
      uStack_28 = uStack_28 + *(float *)(iVar6 + 0x30);
      iVar6 = iVar6 + 0x130;
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) + 1;
    }
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xe4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xe4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xe4;
  SetScroll__10MenuWindowFss(param_1,0,0);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00456260  CmdTarotGoods::Select(CmdTarot*, MenuGroup*, MenuGroup*)   [Select__13CmdTarotGoodsFP8CmdTarotP9MenuGroupP9MenuGroup]  size=0x10c */
void Select__13CmdTarotGoodsFP8CmdTarotP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  if ((param_4 != 0) && ((long)((ulong)*(byte *)(param_4 + 0x21) << 0x3c) < 0)) {
    uVar2 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar2,0);
  }
  if (param_3 != 0) {
    uVar2 = FindPlace__9MenuGroupFs(param_3,10);
    SetCSA__8FontItemFUc(uVar2,1);
    uVar1 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 100);
    uVar2 = GetRegDat__9RegDatApiFiii(0x1a,*(undefined2 *)(param_3 + 0x16),0xffffffffffffffff);
    SetExplanation__7CmdNoteFPCce(uVar1,uVar2);
  }
  return;
}

/* JP: 0x00456370  CmdTarotGoods::~CmdTarotGoods()   [@24@__dt__13CmdTarotGoodsFv]  size=0x8 */
undefined4 * _24___dt__13CmdTarotGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdTarotGoods;
    *param_1 = 0x408314;
    param_1[3] = 0x408320;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x455e60);
      param_1[0x43] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00456380  CmdTarotGoods::~CmdTarotGoods()   [@36@__dt__13CmdTarotGoodsFv]  size=0x8 */
undefined4 * _36___dt__13CmdTarotGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdTarotGoods;
    param_1[-3] = 0x408314;
    *param_1 = 0x408320;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x455e60);
      param_1[0x40] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
