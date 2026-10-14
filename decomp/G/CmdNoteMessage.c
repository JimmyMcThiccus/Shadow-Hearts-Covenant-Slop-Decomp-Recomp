/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdNoteMessage   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdNoteMessage.md).
 */

/* JP: 0x00483150  CmdNoteMessage::CmdNoteMessage()   [__ct__14CmdNoteMessageFv]  size=0x9c */
int __ct__14CmdNoteMessageFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdNoteMessage;
  *(undefined4 *)(param_1 + 0x18) = 0x408f44;
  *(undefined4 *)(param_1 + 0x24) = 0x408f50;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8MenuTextFv(param_1 + 0xf4);
  __ct__10MenuSpriteFv(param_1 + 0x174);
  __ct__7KeyWaitFv(param_1 + 0x1d4);
  return param_1;
}

/* JP: 0x004831f0  CmdNoteMessage::~CmdNoteMessage()   [__dt__14CmdNoteMessageFv]  size=0xe4 */
int __dt__14CmdNoteMessageFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdNoteMessage;
    *(undefined4 *)(param_1 + 0x18) = 0x408f44;
    *(undefined4 *)(param_1 + 0x24) = 0x408f50;
    __dt__7KeyWaitFv(param_1 + 0x1d4,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x174,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004832e0  CmdNoteMessage::CreateScene(MenuScene*, char*, int)   [CreateScene__14CmdNoteMessageFP9MenuScenePci]  size=0x1f8 */
void CreateScene__14CmdNoteMessageFP9MenuScenePci
               (int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  float fVar1;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0xf4);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,param_3,*(byte *)(param_1 + 0x14c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  Create__7KeyWaitFv(param_1 + 0x1d4);
  *(int *)(param_1 + 0x48) = param_1 + 0x1d4;
  *(int *)(param_1 + 0x1ec) = param_1;
  fVar1 = *(float *)(param_1 + 0x120) + *(float *)(param_1 + 0x254);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  SetPosition__10MenuWindowFff(*(float *)(param_1 + 100) - fVar1 * 0.5,*(undefined4 *)(param_1 + 0x68),param_1);
  SetSize__10MenuWindowFff(fVar1,*(undefined4 *)(param_1 + 0x124),param_1);
  AddOT__7MenuObjFv(param_1);
  SetPosition__7KeyWaitFi(param_1 + 0x1d4,1);
  if (param_4 != 0) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x174);
    AddOT__7MenuObjFv(param_1 + 0x174);
  }
  return;
}

/* JP: 0x004834e0  CmdNoteMessage::Run(unsigned short)   [Run__14CmdNoteMessageFUs]  size=0xc8 */
undefined2 Run__14CmdNoteMessageFUs(int param_1,ushort param_2)

{
  bool bVar1;
  
  if (*(short *)(param_1 + 0xae) == 0) {
    if ((*(char *)(param_1 + 0xa8) == '\x01') || (*(char *)(param_1 + 0xa8) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && ((param_2 & 0x6000) != 0)) {
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) + 1;
    }
  }
  return *(undefined2 *)(param_1 + 0xae);
}

/* JP: 0x004835b0  CmdNoteMessage::DelayDelete()   [DelayDelete__14CmdNoteMessageFv]  size=0x44 */
void DelayDelete__14CmdNoteMessageFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x174);
  ReleaseOT__7MenuObjFv(param_1);
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x00483600  CmdNoteMessage::~CmdNoteMessage()   [@24@__dt__14CmdNoteMessageFv]  size=0x8 */
undefined4 * _24___dt__14CmdNoteMessageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdNoteMessage;
    *param_1 = 0x408f44;
    param_1[3] = 0x408f50;
    __dt__7KeyWaitFv(param_1 + 0x6f,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x57,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00483610  CmdNoteMessage::~CmdNoteMessage()   [@36@__dt__14CmdNoteMessageFv]  size=0x8 */
undefined4 * _36___dt__14CmdNoteMessageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdNoteMessage;
    param_1[-3] = 0x408f44;
    *param_1 = 0x408f50;
    __dt__7KeyWaitFv(param_1 + 0x6c,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
