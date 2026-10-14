/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: MenuModelAuraPacket   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/MenuModelAuraPacket.md).
 */

/* JP: 0x00499240  MenuModelAuraPacket::MenuModelAuraPacket()   [__ct__19MenuModelAuraPacketFv]  size=0x4c */
undefined4 * __ct__19MenuModelAuraPacketFv(undefined4 *param_1)

{
  __ct__8VIF1PrimFv(param_1);
  param_1[4] = &__vt__19MenuModelAuraPacket;
  *(undefined2 *)(param_1 + 5) = 0;
  *param_1 = 0;
  return param_1;
}

/* JP: 0x00499290  MenuModelAuraPacket::~MenuModelAuraPacket()   [__dt__19MenuModelAuraPacketFv]  size=0x9c */
int * __dt__19MenuModelAuraPacketFv(int *param_1,short param_2)

{
  if (param_1 != (int *)0x0) {
    param_1[4] = (int)&__vt__19MenuModelAuraPacket;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
      *param_1 = 0;
    }
    __dt__8VIF1PrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00499330  MenuModelAuraPacket::Create(short, unsigned char)   [Create__19MenuModelAuraPacketFsUc]  size=0x3b8 */
void Create__19MenuModelAuraPacketFsUc(int *param_1,short param_2,undefined1 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  *(short *)((int)param_1 + 0x16) = param_2;
  iVar5 = param_2 * 2 + 0x11;
  iVar3 = __nwa__FUi(iVar5 * 0x20);
  *param_1 = iVar3;
  param_1[1] = *param_1 + iVar5 * 0x10;
  memset(*param_1,0,iVar5 * 0x20);
  puVar1 = (undefined4 *)*param_1;
  *puVar1 = 0x10000001;
  puVar1[3] = 0x50000001;
  *(undefined8 *)(puVar1 + 4) = 0x1000000000008001;
  *(undefined8 *)(puVar1 + 6) = 0xe;
  puVar1[8] = 0x30000001;
  puVar1[9] = camera__4CApp + 0x50;
  puVar1[0xb] = 0x50000001;
  puVar1[0xc] = 0x50000000;
  puVar1[0xd] = camera__4CApp + 0x1c0;
  puVar1[0x10] = 0x10000008;
  puVar1[0x13] = 0x50000008;
  *(undefined8 *)(puVar1 + 0x14) = 0x1000000000000005;
  *(undefined8 *)(puVar1 + 0x16) = 0xe;
  *(undefined8 *)(puVar1 + 0x18) = *(undefined8 *)(camera__4CApp + 0x60);
  *(byte *)(puVar1 + 0x19) = *(byte *)(puVar1 + 0x19) & 0xfe | 1;
  *(undefined8 *)(puVar1 + 0x1c) = 0x3000c;
  *(undefined8 *)(puVar1 + 0x1e) = 0x47;
  *(undefined8 *)(puVar1 + 0x20) = 0x48;
  *(undefined8 *)(puVar1 + 0x22) = 0x42;
  *(undefined8 *)(puVar1 + 0x24) = 5;
  *(undefined8 *)(puVar1 + 0x26) = 8;
  iVar3 = GetCoefficient__Fi(0x200);
  uVar2 = sm_freeBlock__7MenuObj | 0x20000;
  iVar4 = GetCoefficient__Fi(0x1c0);
  *(ulong *)(puVar1 + 0x28) =
       CONCAT44((int)((ulong)((long)iVar3 << 0x1a) >> 0x20),uVar2 | (uint)((long)iVar3 << 0x1a)) |
       (long)iVar4 << 0x1e | 0x400000000;
  *(undefined8 *)(puVar1 + 0x2a) = 6;
  *(undefined8 *)(puVar1 + 0x2c) = 0x2400000000000001;
  *(undefined8 *)(puVar1 + 0x2e) = 0x10;
  *(undefined8 *)(puVar1 + 0x30) = 0x156;
  *(undefined1 *)((int)puVar1 + 0xca) = 0x60;
  *(undefined1 *)((int)puVar1 + 0xc9) = 0x60;
  *(undefined1 *)(puVar1 + 0x32) = 0x60;
  *(undefined1 *)((int)puVar1 + 0xcb) = param_3;
  puVar1[0x34] = param_2 * 2 + 0x30000001;
  puVar1[0x37] = param_2 * 2 + 0x50000001;
  puVar1[0x38] = 0x50000000;
  puVar1[0x39] = camera__4CApp + 0x1c0;
  puVar1[0x3c] = 0x60000000;
  *(ulong *)(puVar1 + 0x40) = (long)param_2 | 0x4400000000008000;
  *(undefined8 *)(puVar1 + 0x42) = 0x53d3;
  memcpy(param_1[1],*param_1,iVar5 * 0x10);
  *(int *)(*param_1 + 0xd4) = *param_1 + 0x100;
  *(int *)(param_1[1] + 0xd4) = param_1[1] + 0x100;
  return;
}

/* JP: 0x004996f0  MenuModelAuraPacket::SetAura(_QWD*, int, int)   [SetAura__19MenuModelAuraPacketFP4_QWDii]  size=0xd8 */
undefined2 *
SetAura__19MenuModelAuraPacketFP4_QWDii
          (undefined8 param_1,undefined2 *param_2,short param_3,short param_4)

{
  *param_2 = 0;
  param_2[1] = 0;
  param_2[4] = (param_3 + 0x700) * 0x10;
  param_2[5] = (param_4 + 0x720) * 0x10;
  *(undefined4 *)(param_2 + 6) = 1;
  param_2[8] = 0x2000;
  param_2[9] = 0x1c00;
  param_2[0xc] = (param_3 + 0x900) * 0x10;
  param_2[0xd] = (param_4 + 0x8e0) * 0x10;
  *(undefined4 *)(param_2 + 0xe) = 1;
  return param_2 + 0x10;
}

/* JP: 0x004997d0  MenuModelAuraPacket::Run()   [Run__19MenuModelAuraPacketFv]  size=0x4c */
void Run__19MenuModelAuraPacketFv(int param_1)

{
  *(short *)(param_1 + 0x14) = *(short *)(param_1 + 0x14) + 1;
  if (8 < *(short *)(param_1 + 0x14)) {
    *(undefined2 *)(param_1 + 0x14) = 0;
  }
  return;
}

/* JP: 0x00499820  MenuModelAuraPacket::getPacket()   [getPacket__19MenuModelAuraPacketFv]  size=0x1c8 */
undefined4 getPacket__19MenuModelAuraPacketFv(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar5 = *(int *)(param_1 + (m_Env__8VIF1Prim & 1) * 4) + 0x110;
  sVar1 = *(short *)(param_1 + 0x16);
  if (sVar1 < 4) {
    SetAura__19MenuModelAuraPacketFP4_QWDii(param_1,iVar5,0,0);
  }
  else {
    iVar2 = (int)*(short *)(param_1 + 0x14);
    if (*(short *)(param_1 + 0x14) < 0) {
      iVar2 = iVar2 + 1;
    }
    iVar8 = 0;
    iVar7 = 1;
    iVar3 = (int)sVar1;
    if (sVar1 < 0) {
      iVar3 = iVar3 + 3;
    }
    for (; iVar8 < iVar3 >> 2; iVar8 = iVar8 + 1) {
      iVar6 = (iVar2 >> 1) + iVar7;
      if (7 < iVar6) {
        iVar6 = iVar6 + -8;
      }
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      uVar4 = SetAura__19MenuModelAuraPacketFP4_QWDii(param_1,iVar5,iVar6,0);
      uVar4 = SetAura__19MenuModelAuraPacketFP4_QWDii(param_1,uVar4,-iVar6,0);
      uVar4 = SetAura__19MenuModelAuraPacketFP4_QWDii(param_1,uVar4,0,-iVar6);
      iVar5 = SetAura__19MenuModelAuraPacketFP4_QWDii(param_1,uVar4,0,iVar6);
      iVar7 = iVar7 + 3;
    }
  }
  return *(undefined4 *)(param_1 + (m_Env__8VIF1Prim & 1) * 4);
}
