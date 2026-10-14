/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdWindow   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdWindow.md).
 */

/* JP: 0x0044f2d0  CmdWindow::CmdWindow()   [__ct__9CmdWindowFv]  size=0x5c */
int __ct__9CmdWindowFv(int param_1)

{
  __ct__10MenuWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdWindow;
  *(undefined4 *)(param_1 + 0x18) = 0x408054;
  *(undefined4 *)(param_1 + 0x24) = 0x408060;
  return param_1;
}

/* JP: 0x0044f330  CmdWindow::~CmdWindow()   [__dt__9CmdWindowFv]  size=0x94 */
int __dt__9CmdWindowFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdWindow;
    *(undefined4 *)(param_1 + 0x18) = 0x408054;
    *(undefined4 *)(param_1 + 0x24) = 0x408060;
    __dt__10MenuWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044f3d0  CmdWindow::DelayDelete()   [DelayDelete__9CmdWindowFv]  size=0x34 */
void DelayDelete__9CmdWindowFv(undefined4 param_1)

{
  ReleaseOT__7MenuObjFv(param_1);
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x0044f410  CmdWindow::Select(CmdNote*, MenuScene*, MenuText*, MenuText*)   [Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText]  size=0x110 */
void Select__9CmdWindowFP7CmdNoteP9MenuSceneP8MenuTextP8MenuText
               (undefined8 param_1,int param_2,int param_3,int param_4,int param_5)

{
  if ((param_5 != 0) && ((long)((ulong)*(byte *)(param_5 + 0x21) << 0x3c) < 0)) {
    SetCSA__8FontItemFUc(param_5,0);
  }
  if (param_4 != 0) {
    if ((long)((ulong)*(byte *)(param_4 + 0x21) << 0x3c) < 0) {
      SetCSA__8FontItemFUc(param_4,1);
    }
    if (param_2 != 0) {
      SetExplanation__7CmdNoteFPCce
                (param_2,*(undefined4 *)
                          ((uint)*(ushort *)(param_4 + 0x22) * 0xc + *(int *)(param_3 + 0x28) + 0x14
                          ));
    }
  }
  return;
}

/* JP: 0x0044f520  CmdWindow::SetClutGoods(CmdGoods*, short)   [SetClutGoods__9CmdWindowFP8CmdGoodss]  size=0x184 */
void SetClutGoods__9CmdWindowFP8CmdGoodss(undefined8 param_1,uint param_2,short param_3)

{
  ulong uVar1;
  undefined4 uStack_20;
  
  for (uStack_20 = param_2; uStack_20 < param_2 + param_3 * 0x150; uStack_20 = uStack_20 + 0x150) {
    SetCSA__8FontItemFUc(uStack_20 + 0x50,0);
    *(undefined1 *)(uStack_20 + 0xac) = 0;
    uVar1 = (ulong)*(byte *)(uStack_20 + 0x61) & 0xfffffffffffffffd | 2;
    *(char *)(uStack_20 + 0x61) = (char)uVar1;
    *(byte *)(uStack_20 + 0x60) =
         *(byte *)(uStack_20 + 0x60) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(uStack_20 + 0xce) = 0;
    SetCSA__8FontItemFUc(uStack_20 + 0x50,0);
    SetCSA__8FontItemFUc(uStack_20 + 0xd0,0);
    *(undefined1 *)(uStack_20 + 300) = 0;
    uVar1 = (ulong)*(byte *)(uStack_20 + 0xe1) & 0xfffffffffffffffd | 2;
    *(char *)(uStack_20 + 0xe1) = (char)uVar1;
    *(byte *)(uStack_20 + 0xe0) =
         *(byte *)(uStack_20 + 0xe0) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(uStack_20 + 0x14e) = 0;
    SetCSA__8FontItemFUc(uStack_20 + 0xd0,0);
  }
  return;
}

/* JP: 0x0044f6b0  CmdWindow::~CmdWindow()   [@24@__dt__9CmdWindowFv]  size=0x8 */
undefined4 * _24___dt__9CmdWindowFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__9CmdWindow;
    *param_1 = 0x408054;
    param_1[3] = 0x408060;
    __dt__10MenuWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0044f6c0  CmdWindow::~CmdWindow()   [@36@__dt__9CmdWindowFv]  size=0x8 */
undefined4 * _36___dt__9CmdWindowFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__9CmdWindow;
    param_1[-3] = 0x408054;
    *param_1 = 0x408060;
    __dt__10MenuWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
