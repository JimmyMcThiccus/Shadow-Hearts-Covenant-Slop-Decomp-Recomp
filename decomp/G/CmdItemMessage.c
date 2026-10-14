/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdItemMessage   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdItemMessage.md).
 */

/* JP: 0x0045e1e0  CmdItemMessage::CmdItemMessage()   [__ct__14CmdItemMessageFv]  size=0x8c */
int __ct__14CmdItemMessageFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdItemMessage;
  *(undefined4 *)(param_1 + 0x18) = 0x408644;
  *(undefined4 *)(param_1 + 0x24) = 0x408650;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11MenuMessageFv(param_1 + 0xf4);
  __ct__7KeyWaitFv(param_1 + 0x18c);
  return param_1;
}

/* JP: 0x0045e270  CmdItemMessage::~CmdItemMessage()   [__dt__14CmdItemMessageFv]  size=0xcc */
int __dt__14CmdItemMessageFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdItemMessage;
    *(undefined4 *)(param_1 + 0x18) = 0x408644;
    *(undefined4 *)(param_1 + 0x24) = 0x408650;
    __dt__7KeyWaitFv(param_1 + 0x18c,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045e340  CmdItemMessage::CreateScene(CmdItem*)   [CreateScene__14CmdItemMessageFP7CmdItem]  size=0x16c */
void CreateScene__14CmdItemMessageFP7CmdItem(int param_1,int param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP11MenuMessage(param_2,0,param_1 + 0xf4);
  Order__8FontDrawFP11MenuMessagePc(param_1 + 0xb4,param_1 + 0xf4,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x10));
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  Create__7KeyWaitFv(param_1 + 0x18c);
  *(int *)(param_1 + 0x48) = param_1 + 0x18c;
  *(int *)(param_1 + 0x1a4) = param_1;
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  SetSize__10MenuWindowFff(*(float *)(param_1 + 0x120) + *(float *)(param_1 + 0x20c),
                  *(undefined4 *)(param_1 + 0x124),param_1);
  AddOT__7MenuObjFv(param_1);
  SetPosition__7KeyWaitFi(param_1 + 0x18c,1);
  *(byte *)(param_1 + 0x19e) = *(byte *)(param_1 + 0x19e) & 0xfe;
  return;
}

/* JP: 0x0045e4b0  CmdItemMessage::Run(unsigned short)   [Run__14CmdItemMessageFUs]  size=0x1a8 */
undefined4 Run__14CmdItemMessageFUs(int param_1,ushort param_2)

{
  short sVar1;
  ulong uVar2;
  
  sVar1 = *(short *)(param_1 + 0xae);
  if (sVar1 == 2) {
    if ((char)*(undefined2 *)(param_1 + 0x1aa) == '\r') {
      return 1;
    }
  }
  else {
    if (sVar1 != 1) {
      if (sVar1 != 0) {
        return 0;
      }
      Start__11MenuMessageFv(param_1 + 0xf4);
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) + 1;
    }
    if ((param_2 & 0x2000) != 0) {
      Finish__11MenuMessageFv(param_1 + 0xf4);
    }
    if (*(ushort *)(param_1 + 0x16a) <= *(ushort *)(param_1 + 0x174)) {
      *(undefined2 *)(param_1 + 0x1aa) = 10;
      uVar2 = (ulong)*(byte *)(param_1 + 0x19e) & 0xfffffffffffffffd | 2;
      *(char *)(param_1 + 0x19e) = (char)uVar2;
      *(byte *)(param_1 + 0x19e) =
           *(byte *)(param_1 + 0x19e) & 0xfe | (byte)((uVar2 << 0x3e) >> 0x3f);
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) + 1;
    }
  }
  return 0;
}

/* JP: 0x0045e660  CmdItemMessage::~CmdItemMessage()   [@24@__dt__14CmdItemMessageFv]  size=0x8 */
undefined4 * _24___dt__14CmdItemMessageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdItemMessage;
    *param_1 = 0x408644;
    param_1[3] = 0x408650;
    __dt__7KeyWaitFv(param_1 + 0x5d,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0045e670  CmdItemMessage::~CmdItemMessage()   [@36@__dt__14CmdItemMessageFv]  size=0x8 */
undefined4 * _36___dt__14CmdItemMessageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdItemMessage;
    param_1[-3] = 0x408644;
    *param_1 = 0x408650;
    __dt__7KeyWaitFv(param_1 + 0x5a,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
