/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: MenuModelAuraRegister   functions: 3
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/MenuModelAuraRegister.md).
 */

/* JP: 0x00498fe0  MenuModelAuraRegister::MenuModelAuraRegister()   [__ct__21MenuModelAuraRegisterFv]  size=0x1a4 */
undefined4 * __ct__21MenuModelAuraRegisterFv(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  __ct__8VIF1PrimFv(param_1);
  param_1[4] = &__vt__21MenuModelAuraRegister;
  uVar2 = __nwa__FUi(0x90);
  *param_1 = uVar2;
  memset(*param_1,0,0x90);
  puVar1 = (undefined4 *)*param_1;
  *puVar1 = 0x10000007;
  puVar1[3] = 0x50000007;
  *(undefined8 *)(puVar1 + 4) = 0x1000000000000003;
  *(undefined8 *)(puVar1 + 6) = 0xe;
  *(undefined8 *)(puVar1 + 8) = 0x80150;
  *(undefined8 *)(puVar1 + 10) = 0x4c;
  *(undefined8 *)(puVar1 + 0xc) = *(undefined8 *)(camera__4CApp + 0x60);
  *(byte *)(puVar1 + 0xd) = *(byte *)(puVar1 + 0xd) & 0xfe | 1;
  *(undefined8 *)(puVar1 + 0x10) = 0x3000c;
  *(undefined8 *)(puVar1 + 0x12) = 0x47;
  *(undefined8 *)(puVar1 + 0x14) = 0x4400000000008001;
  *(undefined8 *)(puVar1 + 0x16) = 0x5d10;
  *(undefined8 *)(puVar1 + 0x18) = 0x106;
  *(undefined1 *)((int)puVar1 + 0x6b) = 0;
  *(undefined1 *)((int)puVar1 + 0x6a) = 0;
  *(undefined1 *)((int)puVar1 + 0x69) = 0;
  *(undefined1 *)(puVar1 + 0x1a) = 0;
  *(undefined2 *)(puVar1 + 0x1c) = 0;
  *(undefined2 *)((int)puVar1 + 0x72) = 0;
  puVar1[0x1d] = 1;
  *(undefined2 *)(puVar1 + 0x1e) = 0x9000;
  *(undefined2 *)((int)puVar1 + 0x7a) = 0x8e00;
  puVar1[0x1f] = 1;
  puVar1[0x20] = 0x60000000;
  return param_1;
}

/* JP: 0x00499190  MenuModelAuraRegister::~MenuModelAuraRegister()   [__dt__21MenuModelAuraRegisterFv]  size=0x84 */
undefined4 * __dt__21MenuModelAuraRegisterFv(undefined4 *param_1,short param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    param_1[4] = &__vt__21MenuModelAuraRegister;
    __dla__FPv(*param_1);
    __dt__8VIF1PrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00499220  MenuModelAuraRegister::getPacket()   [getPacket__21MenuModelAuraRegisterFv]  size=0x1c */
undefined4 getPacket__21MenuModelAuraRegisterFv(undefined4 *param_1)

{
  return *param_1;
}
