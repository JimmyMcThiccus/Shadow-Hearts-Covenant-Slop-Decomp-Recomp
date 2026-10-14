/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboKeyCommand   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboKeyCommand.md).
 */

/* JP: 0x00489210  CmdComboKeyCommand::CmdComboKeyCommand()   [__ct__18CmdComboKeyCommandFv]  size=0x94 */
int __ct__18CmdComboKeyCommandFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdComboKeyCommand;
  *(undefined4 *)(param_1 + 0x18) = 0x4090b4;
  *(undefined4 *)(param_1 + 0x24) = 0x4090c0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,5);
  return param_1;
}

/* JP: 0x004892b0  CmdComboKeyCommand::~CmdComboKeyCommand()   [__dt__18CmdComboKeyCommandFv]  size=0xc4 */
int __dt__18CmdComboKeyCommandFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdComboKeyCommand;
    *(undefined4 *)(param_1 + 0x18) = 0x4090b4;
    *(undefined4 *)(param_1 + 0x24) = 0x4090c0;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00489380  CmdComboKeyCommand::CreateScene(CmdComboKey*)   [CreateScene__18CmdComboKeyCommandFP11CmdComboKey]  size=0x14c */
void CreateScene__18CmdComboKeyCommandFP11CmdComboKey(int param_1,undefined4 param_2)

{
  ulong uVar1;
  int iVar2;
  short sVar3;
  float fVar4;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  uStack_24 = 0.0;
  iVar2 = param_1 + 0xf4;
  for (sVar3 = 0; sVar3 < 5; sVar3 = sVar3 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(0,uStack_24);
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
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x004894d0  CmdComboKeyCommand::UpdateScene(CmdComboKey*, short, short)   [UpdateScene__18CmdComboKeyCommandFP11CmdComboKeyss]  size=0x2b0 */
void UpdateScene__18CmdComboKeyCommandFP11CmdComboKeyss
               (int param_1,int param_2,short param_3,short param_4)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  puVar8 = (undefined4 *)(*(int *)(param_2 + 0xcac) + param_3 * 0xc);
  bVar1 = *(byte *)(param_2 + 0xcbc);
  iVar4 = *(int *)(param_2 + 0x28);
  puVar7 = (undefined4 *)(iVar4 + 0x10);
  iVar5 = param_1 + 0xf4;
  bVar2 = *(byte *)((int)puVar8 + 10);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  ClearPlace__10MenuWindowFv(param_1);
  if (param_4 != 0) {
    *(undefined2 *)(param_1 + 0x10a) = 0xffff;
    *(undefined2 *)(param_1 + 0x116) = 0xffff;
    SetMessage__8MenuTextFPcUiUcUc(iVar5,*(undefined4 *)(iVar4 + 0x40),*(byte *)(param_1 + 0x14c) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar5,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
    EnableFontItem__8FontItemFv(iVar5);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
    iVar5 = param_1 + 0x174;
  }
  for (sVar6 = 0; sVar6 < 4; sVar6 = sVar6 + 1) {
    sVar3 = *(short *)(puVar7 + 2);
    if ((byte)(bVar1 & bVar2 & (byte)(1 << ((int)sVar3 & 0x1fU))) != 0) {
      if (*(short *)((int)puVar7 + 10) == 0) {
        SetMessage__8MenuTextFPcUiUcUc(iVar5,*puVar7,*(byte *)(iVar5 + 0x58) & 7,0,1);
      }
      else {
        SetMessage__8MenuTextFPcUiUcUc(iVar5,*puVar8,*(byte *)(iVar5 + 0x58) & 7,0,1);
      }
      *(short *)(iVar5 + 0x16) = sVar3;
      *(short *)(iVar5 + 0x22) = sVar6;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar5,((ulong)*(byte *)(iVar5 + 0x58) & 0xf) >> 3,0);
      EnableFontItem__8FontItemFv(iVar5);
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
      iVar5 = iVar5 + 0x80;
    }
    puVar7 = puVar7 + 3;
  }
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  return;
}

/* JP: 0x00489780  CmdComboKeyCommand::Select(CmdComboKey*, MenuPlace*, MenuPlace*)   [Select__18CmdComboKeyCommandFP11CmdComboKeyP9MenuPlaceP9MenuPlace]  size=0x110 */
void Select__18CmdComboKeyCommandFP11CmdComboKeyP9MenuPlaceP9MenuPlace
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(param_4,0);
  }
  if (param_3 != 0) {
    uVar1 = *(ushort *)(param_3 + 0x22);
    SetCSA__8FontItemFUc(param_3,1);
    if ((short)uVar1 < 0) {
      uVar1 = 4;
    }
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 100),
               *(undefined4 *)((uint)uVar1 * 0xc + *(int *)(param_2 + 0x28) + 0x14));
  }
  return;
}

/* JP: 0x00489890  CmdComboKeyCommand::~CmdComboKeyCommand()   [@24@__dt__18CmdComboKeyCommandFv]  size=0x8 */
undefined4 * _24___dt__18CmdComboKeyCommandFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdComboKeyCommand;
    *param_1 = 0x4090b4;
    param_1[3] = 0x4090c0;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x004898a0  CmdComboKeyCommand::~CmdComboKeyCommand()   [@36@__dt__18CmdComboKeyCommandFv]  size=0x8 */
undefined4 * _36___dt__18CmdComboKeyCommandFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdComboKeyCommand;
    param_1[-3] = 0x4090b4;
    *param_1 = 0x4090c0;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
