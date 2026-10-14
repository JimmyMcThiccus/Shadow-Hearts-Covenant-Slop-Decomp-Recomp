/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingMessage   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingMessage.md).
 */

/* JP: 0x0046e710  CmdRingMessage::CmdRingMessage()   [__ct__14CmdRingMessageFv]  size=0xa4 */
int __ct__14CmdRingMessageFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdRingMessage;
  __ct__6CursorFv(param_1 + 0x5c);
  __ct__10MenuWindowFv(param_1 + 0x158);
  __ct__8FontDrawFv(param_1 + 0x20c);
  __ct__11MenuMessageFv(param_1 + 0x24c);
  __construct_array(param_1 + 0x2e4,0x27bfd0,0x27c030,0x80,2);
  return param_1;
}

/* JP: 0x0046e7c0  CmdRingMessage::~CmdRingMessage()   [__dt__14CmdRingMessageFv]  size=0xe4 */
int __dt__14CmdRingMessageFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdRingMessage;
    __destroy_arr(param_1 + 0x2e4,0x27c030,0x80,2);
    __dt__11MenuMessageFv(param_1 + 0x24c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x20c,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x158,0xffffffffffffffff);
    __dt__6CursorFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0046e8b0  CmdRingMessage::GetReady()   [GetReady__14CmdRingMessageFv]  size=0x130 */
undefined4 GetReady__14CmdRingMessageFv(int param_1)

{
  SetData__9MenuSceneFUsP6Cursor(param_1,0,param_1 + 0x5c);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x20c);
  SetData__9MenuSceneFUsP11MenuMessage(param_1,0,param_1 + 0x24c);
  SetData__9MenuSceneFUsP8MenuText(param_1,0,param_1 + 0x2e4);
  SetData__9MenuSceneFUsP8MenuText(param_1,1,param_1 + 0x364);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x158);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x158,param_1 + 0x24c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x158,param_1 + 0x2e4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x158,param_1 + 0x364);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x170,param_1 + 0x20c);
  AddOT__7MenuObjFv(param_1 + 0x5c);
  AddOT__7MenuObjFv(param_1 + 0x158);
  return 1;
}

/* JP: 0x0046e9e0  CmdRingMessage::Run()   [Run__14CmdRingMessageFv]  size=0x238 */
undefined8 Run__14CmdRingMessageFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(param_1 + 0x148);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x40) != 0) {
        MoveCursor__6CursorFi(param_1 + 0x5c,2);
      }
    }
    else {
      MoveCursor__6CursorFi(param_1 + 0x5c,1);
    }
    if (*(int *)(param_1 + 0x148) != iVar2) {
      SetCSA__8FontItemFUc(*(int *)(param_1 + 0x148),1);
      SetCSA__8FontItemFUc(iVar2,0);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  else {
    if ((*(char *)(param_1 + 0x200) == '\x01') || (*(char *)(param_1 + 0x200) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      *(char *)(*(int *)(param_1 + 0x10) + 0x4c) = (char)*(undefined2 *)(iVar2 + 0x16);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))
                (*(int *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x1e));
      RemoveScene__4MenuFP9MenuScene(*(undefined4 *)(param_1 + 0x10),param_1);
      ReleaseOT__7MenuObjFv(param_1 + 0x5c);
      ReleaseOT__7MenuObjFv(param_1 + 0x158);
      (**(code **)(*(int *)(param_1 + 8) + 0xc))();
    }
  }
  return 0;
}

/* JP: 0x0046ec20  CmdRingMessage::StartMessage(short, char*)   [StartMessage__14CmdRingMessageFsPc]  size=0x218 */
void StartMessage__14CmdRingMessageFsPc(int param_1,undefined2 param_2,undefined4 param_3)

{
  Order__8FontDrawFP11MenuMessagePc(param_1 + 0x20c,param_1 + 0x24c,param_3);
  Finish__11MenuMessageFv(param_1 + 0x24c);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x2e4,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x10),
                  *(byte *)(param_1 + 0x33c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x20c,param_1 + 0x2e4,((ulong)*(byte *)(param_1 + 0x33c) & 0xf) >> 3,0);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x364,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x18),
                  *(byte *)(param_1 + 0x3bc) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x20c,param_1 + 0x364,((ulong)*(byte *)(param_1 + 0x3bc) & 0xf) >> 3,0);
  SetCSA__8FontItemFUc(param_1 + 0x364,1);
  Select__6CursorFP9MenuPlace(param_1 + 0x5c,param_1 + 0x364);
  QuickMove__6CursorFv(param_1 + 0x5c);
  *(undefined2 *)(param_1 + 0x1e) = param_2;
  Open__10MenuWindowFUci(param_1 + 0x158,*(byte *)(param_1 + 0x208) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x18c) + 0x10));
  AddScene__4MenuFP9MenuScene(*(undefined4 *)(param_1 + 0x10),param_1);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))
            (*(int *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x1c));
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  return;
}
