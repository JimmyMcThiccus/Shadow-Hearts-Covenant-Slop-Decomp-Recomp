/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSort   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSort.md).
 */

/* JP: 0x00466490  CmdSort::CmdSort()   [__ct__7CmdSortFv]  size=0x64 */
int __ct__7CmdSortFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__7CmdSort;
  __ct__10MenuWindowFv(param_1 + 0x5c);
  __ct__8FontDrawFv(param_1 + 0x110);
  *(undefined4 *)(param_1 + 0x150) = 0;
  return param_1;
}

/* JP: 0x00466500  CmdSort::~CmdSort()   [__dt__7CmdSortFv]  size=0xcc */
int __dt__7CmdSortFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__7CmdSort;
    if (*(int *)(param_1 + 0x150) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x150),0x27c030);
      *(undefined4 *)(param_1 + 0x150) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004665d0  CmdSort::GetReady()   [GetReady__7CmdSortFv]  size=0x3ac */
undefined4 GetReady__7CmdSortFv(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  short sVar5;
  undefined2 uVar6;
  float fStack_18;
  
  iVar1 = *(int *)(param_1 + 0x10);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x110);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x74,param_1 + 0x110);
  if (*(int *)(param_1 + 0x28) == 0) {
    uVar6 = 0;
  }
  else {
    uVar6 = (undefined2)*(undefined4 *)(*(int *)(param_1 + 0x28) + 8);
  }
  *(undefined2 *)(param_1 + 0x158) = uVar6;
  sVar5 = *(short *)(param_1 + 0x158);
  uVar4 = __nwa__FUi(sVar5 * 0x80 + 0x10);
  iVar2 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,sVar5);
  *(int *)(param_1 + 0x150) = iVar2;
  puVar3 = (undefined4 *)(*(int *)(param_1 + 0x28) + 0x10);
  *(undefined4 **)(param_1 + 0x154) = puVar3;
  fStack_18 = 0.0;
  for (sVar5 = 0; sVar5 < *(short *)(param_1 + 0x158); sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_1,0,iVar2);
    *(short *)(iVar2 + 0x16) = sVar5;
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar5;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(*(undefined4 *)(iVar2 + 0x24),fStack_18);
    SetMessage__8MenuTextFPcUiUcUc(iVar2,*puVar3,*(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x110,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,iVar2);
    fStack_18 = fStack_18 + *(float *)(iVar2 + 0x30);
    iVar2 = iVar2 + 0x80;
    puVar3 = puVar3 + 3;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x5c);
  AddOT__7MenuObjFv(param_1 + 0x5c);
  Open__10MenuWindowFUci(param_1 + 0x5c,*(byte *)(param_1 + 0x10c) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x10));
  *(int *)(param_1 + 0x18) = iVar1 + 0x3a0;
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),
                  *(int *)(param_1 + 0x150) + *(short *)(param_1 + 0x15a) * 0x80);
  Select__7CmdSortFss(param_1,*(undefined2 *)(param_1 + 0x15a),0xffffffffffffffff);
  SetExplanation__7CmdNoteFPCce
            (iVar1 + 0x4e0,
             *(undefined4 *)
              (*(int *)(param_1 + 0x154) +
               *(short *)(*(int *)(param_1 + 0x150) + *(short *)(param_1 + 0x15a) * 0x80 + 0x16) *
               0xc + 4));
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  *(undefined1 *)(param_1 + 0x20) = 3;
  return 1;
}

/* JP: 0x00466980  CmdSort::Run()   [Run__7CmdSortFv]  size=0x40c */
undefined4 Run__7CmdSortFv(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  cVar1 = *(char *)(param_1 + 0x20);
  if (cVar1 == '\x04') {
    if ((*(char *)(param_1 + 0x104) == '\x01') || (*(char *)(param_1 + 0x104) == '\0')) {
      bVar5 = true;
    }
    else {
      bVar5 = false;
    }
    if (bVar5) {
      ReleaseOT__7MenuObjFv(param_1 + 0x5c);
      return 1;
    }
  }
  else if (cVar1 == '\r') {
    Close__10MenuWindowFUci(param_1 + 0x5c,((ulong)*(byte *)(param_1 + 0x10c) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x14));
    *(undefined1 *)(param_1 + 0x20) = 4;
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x15c));
  }
  else if (cVar1 == '\x03') {
    if ((*(char *)(param_1 + 0x104) == '\x01') || (*(char *)(param_1 + 0x104) == '\0')) {
      bVar5 = true;
    }
    else {
      bVar5 = false;
    }
    if (bVar5) {
      *(undefined1 *)(param_1 + 0x20) = 0xf;
    }
  }
  else if (cVar1 == '\x0f') {
    if ((uVar2 & 0x2000) != 0) {
      Select__7CmdSortFss(param_1,*(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16),
                          *(undefined2 *)(param_1 + 0x15a));
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
      return 1;
    }
    if ((uVar2 & 0xc000) != 0) {
      *(undefined1 *)(param_1 + 0x20) = 0xd;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
      return 1;
    }
    iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    if ((uVar2 & 0x10) == 0) {
      if ((uVar2 & 0x40) != 0) {
        MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),2);
      }
    }
    else {
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),1);
    }
    iVar4 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    if (iVar4 != iVar3) {
      SetExplanation__7CmdNoteFPCce
                (*(int *)(param_1 + 0x10) + 0x4e0,
                 *(undefined4 *)(*(int *)(param_1 + 0x154) + *(short *)(iVar4 + 0x16) * 0xc + 4));
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  return 0;
}

/* JP: 0x00466d90  CmdSort::Select(short, short)   [Select__7CmdSortFss]  size=0x94 */
void Select__7CmdSortFss(int param_1,short param_2,short param_3)

{
  if (-1 < param_3) {
    SetCSA__8FontItemFUc(*(int *)(param_1 + 0x150) + param_3 * 0x80,0);
  }
  SetCSA__8FontItemFUc(*(int *)(param_1 + 0x150) + param_2 * 0x80,1);
  *(short *)(param_1 + 0x15a) = param_2;
  return;
}
