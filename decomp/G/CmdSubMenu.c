/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSubMenu   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSubMenu.md).
 */

/* JP: 0x0047ad00  CmdSubMenu::CmdSubMenu()   [__ct__10CmdSubMenuFv]  size=0x64 */
int __ct__10CmdSubMenuFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdSubMenu;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__8FontDrawFv(param_1 + 0x10c);
  *(undefined4 *)(param_1 + 0x14c) = 0;
  return param_1;
}

/* JP: 0x0047ad70  CmdSubMenu::~CmdSubMenu()   [__dt__10CmdSubMenuFv]  size=0xc4 */
int __dt__10CmdSubMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdSubMenu;
    if (*(int *)(param_1 + 0x14c) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x14c),0x27c030);
    }
    __dt__8FontDrawFv(param_1 + 0x10c,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047ae40  CmdSubMenu::DelayDelete()   [DelayDelete__10CmdSubMenuFv]  size=0x38 */
void DelayDelete__10CmdSubMenuFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x58);
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x0047ae80  CmdSubMenu::CreateScene(short, MSDSystem*)   [CreateScene__10CmdSubMenuFsP9MSDSystem]  size=0x144 */
void CreateScene__10CmdSubMenuFsP9MSDSystem(int param_1,short param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  short sVar4;
  
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x10c);
  uVar2 = __nwa__FUi(param_2 * 0x80 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x27bfd0,0x27c030,0x80,param_2);
  *(undefined4 *)(param_1 + 0x14c) = uVar1;
  iVar3 = *(int *)(param_1 + 0x14c);
  for (sVar4 = 0; sVar4 < param_2; sVar4 = sVar4 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_1,0,iVar3);
    *(undefined2 *)(iVar3 + 0x1c) = 0;
    *(short *)(iVar3 + 0x1e) = sVar4;
    iVar3 = iVar3 + 0x80;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  AddOT__7MenuObjFv(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x150) = param_3;
  return;
}

/* JP: 0x0047afd0  CmdSubMenu::UpdateScene(short)   [UpdateScene__10CmdSubMenuFs]  size=0x248 */
void UpdateScene__10CmdSubMenuFs(int param_1,short param_2)

{
  short sVar1;
  ulong uVar2;
  int iVar3;
  undefined4 *puVar4;
  short sVar5;
  float fVar6;
  float fStack_24;
  
  iVar3 = *(int *)(param_1 + 0x150) + param_2 * 0xc;
  sVar5 = *(short *)(iVar3 + 8);
  sVar1 = *(short *)(iVar3 + 10);
  puVar4 = (undefined4 *)(*(int *)(param_1 + 0x150) + sVar5 * 0xc);
  ClearPlace__10MenuWindowFv(param_1 + 0x58);
  ClearImage__8FontDrawFv(param_1 + 0x10c);
  fStack_24 = 0.0;
  iVar3 = *(int *)(param_1 + 0x14c);
  for (; sVar5 < sVar1; sVar5 = sVar5 + 1) {
    if ((*(byte *)(iVar3 + 0x12) & 1) != 0) {
      *(short *)(iVar3 + 0x22) = sVar5;
      SetCSA__8FontItemFUc(iVar3,0);
      (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,fStack_24);
      SetMessage__8MenuTextFPcUiUcUc(iVar3,*puVar4,*(byte *)(iVar3 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x10c,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
      uVar2 = GetRealHeight__8FontItemCFv(iVar3);
      if ((long)uVar2 < 0) {
        fVar6 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fVar6 = (float)(int)uVar2;
      }
      fStack_24 = fStack_24 + fVar6;
      AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar3);
    }
    iVar3 = iVar3 + 0x80;
    puVar4 = puVar4 + 3;
  }
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x10c);
  Open__10MenuWindowFUci(param_1 + 0x58,*(byte *)(param_1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x10));
  return;
}

/* JP: 0x0047b220  CmdSubMenu::Select(CmdNote*, MenuPlace*, MenuPlace*)   [Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace]  size=0xb4 */
void Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(param_4,0);
  }
  if ((param_3 != 0) && (SetCSA__8FontItemFUc(param_3,1), param_2 != 0)) {
    SetExplanation__7CmdNoteFPCce
              (param_2,*(undefined4 *)
                        (*(int *)(param_1 + 0x150) + *(short *)(param_3 + 0x22) * 0xc + 4));
  }
  return;
}
