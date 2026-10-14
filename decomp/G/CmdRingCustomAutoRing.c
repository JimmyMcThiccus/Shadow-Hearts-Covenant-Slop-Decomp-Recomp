/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomAutoRing   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomAutoRing.md).
 */

/* JP: 0x0049fc30  CmdRingCustomAutoRing::CmdRingCustomAutoRing()   [__ct__21CmdRingCustomAutoRingFv]  size=0x94 */
int __ct__21CmdRingCustomAutoRingFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__21CmdRingCustomAutoRing;
  *(undefined4 *)(param_1 + 0x18) = 0x4095c4;
  *(undefined4 *)(param_1 + 0x24) = 0x4095d0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,2);
  return param_1;
}

/* JP: 0x0049fcd0  CmdRingCustomAutoRing::~CmdRingCustomAutoRing()   [__dt__21CmdRingCustomAutoRingFv]  size=0xc4 */
int __dt__21CmdRingCustomAutoRingFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__21CmdRingCustomAutoRing;
    *(undefined4 *)(param_1 + 0x18) = 0x4095c4;
    *(undefined4 *)(param_1 + 0x24) = 0x4095d0;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0049fda0  CmdRingCustomAutoRing::CreateScene(CmdRingCustom*)   [CreateScene__21CmdRingCustomAutoRingFP13CmdRingCustom]  size=0x234 */
void CreateScene__21CmdRingCustomAutoRingFP13CmdRingCustom(int param_1,int param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0xc,param_1 + 0xf4);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,
                  *(undefined4 *)
                   ((uint)*(ushort *)(param_1 + 0x116) * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                  *(byte *)(param_1 + 0x14c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0xd,param_1 + 0x174);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x174,
                  *(undefined4 *)
                   ((uint)*(ushort *)(param_1 + 0x196) * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                  *(byte *)(param_1 + 0x1cc) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0x174,((ulong)*(byte *)(param_1 + 0x1cc) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x174);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,3,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0049ffe0  CmdRingCustomAutoRing::UpdateScene(CmdRingCustom*)   [UpdateScene__21CmdRingCustomAutoRingFP13CmdRingCustom]  size=0xe8 */
void UpdateScene__21CmdRingCustomAutoRingFP13CmdRingCustom(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(**(int **)(param_2 + 0x70) + 0x59);
  *(undefined2 *)(param_1 + (uVar2 & 1) * 0x80 + 0x172) = 0;
  SetCSA__8FontItemFUc(param_1 + (uVar2 & 1) * 0x80 + 0xf4,0);
  *(uint *)(param_1 + 500) = param_1 + (uVar2 & 1 ^ 1) * 0x80 + 0xf4;
  iVar1 = *(int *)(param_1 + 500);
  *(undefined2 *)(iVar1 + 0x7e) = 1;
  SetCSA__8FontItemFUc(iVar1,1);
  return;
}

/* JP: 0x004a00d0  CmdRingCustomAutoRing::Select(CmdRingCustom*, MenuText*, MenuText*, short)   [Select__21CmdRingCustomAutoRingFP13CmdRingCustomP8MenuTextP8MenuTexts]  size=0x15c */
void Select__21CmdRingCustomAutoRingFP13CmdRingCustomP8MenuTextP8MenuTexts
               (undefined8 param_1,int param_2,int param_3,int param_4,short param_5)

{
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(param_4,*(ushort *)(param_4 + 0x7e) & 0xff);
  }
  if (param_3 != 0) {
    SetCSA__8FontItemFUc(param_3,1);
    if (param_5 != 0) {
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_2 + 100),
                 *(undefined4 *)
                  ((uint)*(ushort *)(param_3 + 0x22) * 0xc + *(int *)(param_2 + 0x28) + 0x14));
    }
    *(byte *)(**(int **)(param_2 + 0x70) + 0x59) =
         *(byte *)(**(int **)(param_2 + 0x70) + 0x59) & 0xfe |
         (byte)*(undefined2 *)(param_3 + 0x16) & 1;
  }
  return;
}

/* JP: 0x004a0230  CmdRingCustomAutoRing::~CmdRingCustomAutoRing()   [@24@__dt__21CmdRingCustomAutoRingFv]  size=0x8 */
undefined4 * _24___dt__21CmdRingCustomAutoRingFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__21CmdRingCustomAutoRing;
    *param_1 = 0x4095c4;
    param_1[3] = 0x4095d0;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x004a0240  CmdRingCustomAutoRing::~CmdRingCustomAutoRing()   [@36@__dt__21CmdRingCustomAutoRingFv]  size=0x8 */
undefined4 * _36___dt__21CmdRingCustomAutoRingFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__21CmdRingCustomAutoRing;
    param_1[-3] = 0x4095c4;
    *param_1 = 0x4095d0;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
