/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomGoods.md).
 */

/* JP: 0x0048faf0  CmdRingCustomGoods::CmdRingCustomGoods()   [__ct__18CmdRingCustomGoodsFv]  size=0x94 */
int __ct__18CmdRingCustomGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdRingCustomGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x4092f4;
  *(undefined4 *)(param_1 + 0x24) = 0x409300;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,4);
  return param_1;
}

/* JP: 0x0048fb90  CmdRingCustomGoods::~CmdRingCustomGoods()   [__dt__18CmdRingCustomGoodsFv]  size=0xc4 */
int __dt__18CmdRingCustomGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdRingCustomGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x4092f4;
    *(undefined4 *)(param_1 + 0x24) = 0x409300;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048fc60  CmdRingCustomGoods::CreateScene(CmdRingCustom*)   [CreateScene__18CmdRingCustomGoodsFP13CmdRingCustom]  size=0x13c */
void CreateScene__18CmdRingCustomGoodsFP13CmdRingCustom(int param_1,undefined4 param_2)

{
  ulong uVar1;
  int iVar2;
  short sVar3;
  float fVar4;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xb4);
  iVar2 = param_1 + 0xf4;
  uStack_24 = 0.0;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,5,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(*(undefined4 *)(iVar2 + 0x24),uStack_24);
    uVar1 = GetRealHeight__8FontItemCFv(iVar2);
    if ((long)uVar1 < 0) {
      fVar4 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar4 = (float)(int)uVar1;
    }
    uStack_24 = uStack_24 + fVar4;
    iVar2 = iVar2 + 0x80;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,3,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0048fda0  CmdRingCustomGoods::UpdateScene(CmdRingCustom*)   [UpdateScene__18CmdRingCustomGoodsFP13CmdRingCustom]  size=0x1ec */
void UpdateScene__18CmdRingCustomGoodsFP13CmdRingCustom(int param_1,int param_2)

{
  undefined2 uVar1;
  int *piVar2;
  int iVar3;
  short sVar4;
  
  ClearPlace__10MenuWindowFv(param_1);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  piVar2 = *(int **)(param_2 + 0x70);
  uVar1 = *(undefined2 *)(param_2 + 0x218);
  iVar3 = param_1 + 0xf4;
  for (sVar4 = 0; sVar4 < (char)uVar1; sVar4 = sVar4 + 1) {
    *(short *)(iVar3 + 0x16) = sVar4;
    *(undefined2 *)(iVar3 + 0x7e) = 0;
    SetCSA__8FontItemFUc(iVar3,0);
    SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)(*(int *)(param_2 + 0x210) + sVar4 * 0x10),
                    *(byte *)(iVar3 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    iVar3 = iVar3 + 0x80;
  }
  *(uint *)(param_1 + 0x2f4) = param_1 + (uint)(*(byte *)(*piVar2 + 0x58) >> 6) * 0x80 + 0xf4;
  iVar3 = *(int *)(param_1 + 0x2f4);
  *(undefined2 *)(iVar3 + 0x7e) = 1;
  SetCSA__8FontItemFUc(iVar3,1);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  return;
}

/* JP: 0x0048ff90  CmdRingCustomGoods::Select(CmdRingCustom*, MenuText*, MenuText*, short)   [Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts]  size=0x12c */
void Select__18CmdRingCustomGoodsFP13CmdRingCustomP8MenuTextP8MenuTexts
               (undefined8 param_1,int param_2,int param_3,int param_4,short param_5)

{
  short sVar1;
  
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(param_4,*(ushort *)(param_4 + 0x7e) & 0xff);
  }
  if (param_3 != 0) {
    sVar1 = *(short *)(param_3 + 0x16);
    SetCSA__8FontItemFUc(param_3,1);
    if (param_5 != 0) {
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_2 + 100),
                 *(undefined4 *)(*(int *)(param_2 + 0x210) + sVar1 * 0x10 + 8));
    }
    *(byte *)(**(int **)(param_2 + 0x70) + 0x58) =
         *(byte *)(**(int **)(param_2 + 0x70) + 0x58) & 0x3f | (byte)(((int)sVar1 & 3U) << 6);
  }
  return;
}

/* JP: 0x004900c0  CmdRingCustomGoods::~CmdRingCustomGoods()   [@24@__dt__18CmdRingCustomGoodsFv]  size=0x8 */
undefined4 * _24___dt__18CmdRingCustomGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdRingCustomGoods;
    *param_1 = 0x4092f4;
    param_1[3] = 0x409300;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x004900d0  CmdRingCustomGoods::~CmdRingCustomGoods()   [@36@__dt__18CmdRingCustomGoodsFv]  size=0x8 */
undefined4 * _36___dt__18CmdRingCustomGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdRingCustomGoods;
    param_1[-3] = 0x4092f4;
    *param_1 = 0x409300;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
