/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdNote   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdNote.md).
 */

/* JP: 0x00437970  CmdNote::CmdNote()   [__ct__7CmdNoteFv]  size=0x9c */
int __ct__7CmdNoteFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__7CmdNote;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__11MenuTextureFv(param_1 + 0x110);
  __ct__11SendOnLocalFv(param_1 + 0x150);
  __ct__10MenuSpriteFv(param_1 + 0x180);
  __ct__8FontDrawFv(param_1 + 0x1e0);
  __ct__8MenuTextFv(param_1 + 0x220);
  return param_1;
}

/* JP: 0x00437a10  CmdNote::~CmdNote()   [__dt__7CmdNoteFv]  size=0xec */
int __dt__7CmdNoteFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__7CmdNote;
    __dt__8MenuTextFv(param_1 + 0x220,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x1e0,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x180,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00437b00  CmdNote::GetReady()   [GetReady__7CmdNoteFv]  size=0x168 */
undefined4 GetReady__7CmdNoteFv(int param_1)

{
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x110,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x150,param_1 + 0x128,*(undefined4 *)(param_1 + 0x124),1,
                  0xffffffffffffffff);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x180);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x1e0);
  SetData__9MenuSceneFUsP8MenuText(param_1,0,param_1 + 0x220);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x150);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x180);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x1e0);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x220);
  AddOT__7MenuObjFv(param_1 + 0x58);
  return 1;
}

/* JP: 0x00437c70  CmdNote::Release()   [Release__7CmdNoteFv]  size=0xa8 */
void Release__7CmdNoteFv(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0xc),1);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  Release__11MenuTextureFv(param_1 + 0x110);
  Release__7MenuObjFv(param_1 + 0x150);
  Release__7MenuObjFv(param_1 + 0x180);
  Release__7MenuObjFv(param_1 + 0x1e0);
  Release__7MenuObjFv(param_1 + 0x220);
  Release__7MenuObjFv(param_1 + 0x58);
  return;
}

/* JP: 0x00437d20  SetExplanation__7CmdNoteFPCce   [SetExplanation__7CmdNoteFPCce]  size=0x12c */
/* WARNING: Removing unreachable block (ram,0x00437d7c) */

void SetExplanation__7CmdNoteFPCce
               (int param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  long lVar1;
  undefined1 auStack_250 [512];
  int iStack_50;
  undefined4 uStack_40;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  undefined8 uStack_10;
  undefined8 uStack_8;
  
  iStack_50 = param_1;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_28 = param_4;
  uStack_20 = param_5;
  uStack_18 = param_6;
  uStack_10 = param_7;
  uStack_8 = param_8;
  lVar1 = strstr(param_2,0x5557a0);
  if (lVar1 == 0) {
    vsprintf(auStack_250,uStack_40,&uStack_30);
  }
  else {
    strcpy(auStack_250,uStack_40);
  }
  ClearImage__8FontDrawFv(iStack_50 + 0x1e0);
  SetMessage__8MenuTextFPcUiUcUc(iStack_50 + 0x220,auStack_250,*(byte *)(iStack_50 + 0x278) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x1e0,iStack_50 + 0x220,
                  ((ulong)*(byte *)(iStack_50 + 0x278) & 0xf) >> 3,0);
  return;
}
