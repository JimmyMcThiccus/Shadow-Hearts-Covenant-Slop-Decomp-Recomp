/*
 * BtlBonus.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 10 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0034c810 size 0x15c  BtlBonus::BtlBonus(v)
 *      mangled: __ct__8BtlBonusFv */
int __ct__8BtlBonusFv(int param_1)

{
  u32 uVar1;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv((VIF1Prim *)(param_1 + 0x18));
  *(u32 *)(param_1 + 0x2c) = 0;
  *(u32 *)(param_1 + 0x30) = 0;
  *(u8 **)(param_1 + 0x34) = __vt__17DelayDeleteObject;
  *(u8 **)(param_1 + 0x14) = __vt__8BtlBonus;
  *(u32 *)(param_1 + 0x28) = 0x406e10;
  *(u32 *)(param_1 + 0x34) = 0x406e20;
  __ct__8FontDrawFv(param_1 + 0x8c);
  __ct__10MenuWindowFv((MenuWindow *)(param_1 + 0xcc));
  ourBtlBonus__8BtlBonus = param_1;
  *(u32 *)(param_1 + 0x38) = 0;
  *(u16 *)(param_1 + 0x3c) = 0;
  *(u16 *)(param_1 + 0x3e) = 0;
  uVar1 = GetTimer__7SysToolFv();
  *(u32 *)(param_1 + 0x40) = uVar1;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u32 *)(param_1 + 0x18) = 0;
  *(u16 *)(param_1 + 0x80) = 0;
  *(u16 *)(param_1 + 0x82) = 0;
  *(u32 *)(param_1 + 0x180) = 0;
  *(u32 *)(param_1 + 0x188) = 0;
  *(u32 *)(param_1 + 0x184) = 0;
  *(u32 *)(param_1 + 0x18c) = 0;
  *(u32 *)(param_1 + 400) = 0;
  *(u16 *)(param_1 + 0x194) = 0;
  *(u16 *)(param_1 + 0x196) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---- 0x0034c9f0 size 0x274  BtlBonus::~BtlBonus(v)
 *      mangled: __dt__8BtlBonusFv */
int __dt__8BtlBonusFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__8BtlBonus;
    *(u32 *)(param_1 + 0x28) = 0x406e10;
    *(u32 *)(param_1 + 0x34) = 0x406e20;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(u32 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(u32 *)(param_1 + 0x1c));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3e) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0x8c));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3c) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0xcc));
    }
    if (((ulong)*(ushort *)(param_1 + 0x80) & 0xfff) >> 4 != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x180),0x273e20);
    }
    if (*(int *)(param_1 + 0x188) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x188),0x2661a0);
    }
    if (*(int *)(param_1 + 0x184) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x184),0x277890);
    }
    if (*(int *)(param_1 + 0x18c) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x18c),0x2766d0);
    }
    if (*(int *)(param_1 + 400) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 400),0x28d070);
    }
    ourBtlBonus__8BtlBonus = 0;
    if (param_1 != -0x80) {
      __dt__10MenuWindowFv((MenuWindow *)(param_1 + 0xcc));
      __dt__8FontDrawFv(param_1 + 0x8c,0xffffffffffffffff);
    }
    if (param_1 != -0x2c) {
      *(u8 **)(param_1 + 0x34) = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1 + 0x18,0);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0034cc70 size 0x824  BtlBonus::Polling(v)
 *      mangled: Polling__8BtlBonusFv */
u32 Polling__8BtlBonusFv(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  VIF1Prim *pVVar5;
  uint uVar6;
  float fVar7;
  
  iVar2 = ourBtlSocket__9BtlSocket;
  iVar3 = GetActive__4CPadFi(0);
  if ((*(ushort *)((&m_pCoreArray__4CPad)[*(int *)(iVar3 + 4)] + 0x6c) & 0x2000) != 0) {
    *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfb | 4;
  }
  iVar3 = GetTimer__7SysToolFv();
  fVar7 = (float)(uint)(iVar3 - *(int *)(param_1 + 0x40)) * 0.001;
  *(int *)(param_1 + 0x40) = iVar3;
  WinSequence__8BtlBonusFv(param_1);
  sVar1 = *(short *)(param_1 + 0x3c);
  if (sVar1 == 4) {
    *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x7c) - fVar7 * 2.0;
    if (*(float *)(param_1 + 0x7c) <= 0.0) {
      if ((*(byte *)(param_1 + 0x80) & 1) != 0) {
        ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + 0x8c));
      }
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfe;
      if ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3d) < 0) {
        ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + 0xcc));
      }
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfb;
      if ((long)((ulong)*(byte *)(param_1 + 0x38) << 0x3e) < 0) {
        pVVar5 = (VIF1Prim *)0x0;
        if (param_1 != 0) {
          pVVar5 = (VIF1Prim *)(param_1 + 0x18);
        }
        ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,pVVar5);
      }
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar2 = *(int *)(param_1 + 0x180);
    for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
      if ((*(byte *)(iVar2 + iVar3 * 0x80 + 0x12) & 1) != 0) {
        fVar7 = *(float *)(param_1 + 0x7c) * 128.0;
        if (fVar7 < 2.1474836e+09) {
          uVar6 = (uint)fVar7;
        }
        else {
          uVar6 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
        }
        iVar4 = iVar2 + iVar3 * 0x80;
        (**(code **)(*(int *)(iVar4 + 8) + 0x2c))(iVar4,uVar6);
      }
    }
  }
  else if (sVar1 == 3) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + fVar7;
    if ((4.0 <= *(float *)(param_1 + 100)) || ((long)((ulong)*(byte *)(param_1 + 0x38) << 0x3d) < 0)
       ) {
      *(u16 *)(param_1 + 0x3c) = 4;
      *(u16 *)(param_1 + 0x3e) = 0;
      SetMode__8BtlFaderFsf7_rgba32(0x3f800000,3,0);
    }
  }
  else if (sVar1 == 2) {
    if ((*(float *)(param_1 + 100) != 0.0) &&
       (-1 < (long)((ulong)*(byte *)(param_1 + 0x38) << 0x3d))) {
      *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - fVar7;
      if (0.0 < *(float *)(param_1 + 100)) {
        return 0;
      }
      *(u32 *)(param_1 + 100) = 0;
    }
    if (*(int *)(param_1 + 0x44) < (int)(uint)*(ushort *)(iVar2 + 0x50c)) {
      *(ushort *)(param_1 + 0x38) =
           *(ushort *)(param_1 + 0x38) & 0xfe07 |
           (ushort)(((uint)(((ulong)*(ushort *)(param_1 + 0x38) << 0x37) >> 0x3a) |
                    1 << ((int)*(short *)(param_1 + 0x194) & 0x1fU) & 0x3fU) << 3);
      *(short *)(param_1 + 0x194) = *(short *)(param_1 + 0x194) + 1;
      *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
      *(u32 *)(param_1 + 100) = 0x3e800000;
      WinCreate__8BtlBonusFv(param_1);
      if (-1 < (long)((ulong)*(byte *)(param_1 + 0x38) << 0x3d)) {
        PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x3002,1,0);
      }
    }
    else if (*(int *)(param_1 + 0x44) == 0) {
      *(short *)(param_1 + 0x194) = *(short *)(param_1 + 0x194) + 1;
      *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
      *(u32 *)(param_1 + 100) = 0x3e800000;
    }
    else {
      *(u16 *)(param_1 + 0x3c) = 3;
      *(u16 *)(param_1 + 0x3e) = 0;
      *(u32 *)(param_1 + 100) = 0;
    }
  }
  else if (sVar1 == 1) {
    *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x7c) + fVar7 * 2.0;
    if ((1.0 <= *(float *)(param_1 + 0x7c)) ||
       ((long)((ulong)*(byte *)(param_1 + 0x38) << 0x3d) < 0)) {
      *(u16 *)(param_1 + 0x3c) = 2;
      *(u16 *)(param_1 + 0x3e) = 0;
      *(u32 *)(param_1 + 0x44) = 0;
      *(u32 *)(param_1 + 100) = 0x3e800000;
      *(u32 *)(param_1 + 0x7c) = 0x3f800000;
    }
    iVar2 = *(int *)(param_1 + 0x180);
    for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
      if ((*(byte *)(iVar2 + iVar3 * 0x80 + 0x12) & 1) != 0) {
        fVar7 = *(float *)(param_1 + 0x7c) * 128.0;
        if (fVar7 < 2.1474836e+09) {
          uVar6 = (uint)fVar7;
        }
        else {
          uVar6 = (int)(fVar7 - 2.1474836e+09) | 0x80000000;
        }
        iVar4 = iVar2 + iVar3 * 0x80;
        (**(code **)(*(int *)(iVar4 + 8) + 0x2c))(iVar4,uVar6);
      }
    }
  }
  else if (sVar1 == 0) {
    if ((*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\0') &&
       (*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\0')) {
      *(u8 *)(ourBtlSocket__9BtlSocket + 0x600) = 1;
    }
    if (*(char *)(ourBtlSocket__9BtlSocket + 0x600) == '\x04') {
      pVVar5 = (VIF1Prim *)0x0;
      if (param_1 != 0) {
        pVVar5 = (VIF1Prim *)(param_1 + 0x18);
      }
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0xc,pVVar5);
      *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfd | 2;
      *(u16 *)(param_1 + 0x3c) = 1;
      *(u16 *)(param_1 + 0x3e) = 0;
      *(u8 **)(param_1 + 0x74) = &_BATTLE_bss_size;
      *(u32 *)(param_1 + 0x78) = 0xe0;
      *(u32 *)(param_1 + 0x7c) = 0;
      WinCreate__8BtlBonusFv(param_1);
    }
  }
  return 0;
}

/* ---- 0x0034d4a0 size 0xad44  BtlBonus::MakePacket(v)
 *      mangled: MakePacket__8BtlBonusFv */
void MakePacket__8BtlBonusFv(int param_1)

{
  bool bVar1;
  u8 auVar2 [16];
  u8 in_zero_qw [16];
  u32 uVar3;
  uint uVar4;
  u64 uVar5;
  ulong uVar6;
  long lVar7;
  u64 extraout_v0_udw;
  u8 auVar8 [16];
  u64 extraout_v0_udw_00;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  u32 in_a1_udw;
  u32 in_register_0000005c;
  u32 *puVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  
  iVar12 = ourBtlSocket__9BtlSocket;
  pbVar9 = (byte *)(ourBtlSocket__9BtlSocket + 0x16c);
  bVar1 = (*(byte *)(param_1 + 0x38) & 1) == 0;
  uVar4 = (uint)bVar1;
  if (*(int *)(param_1 + uVar4 * 4 + 0x18) == 0) {
    if ((*pbVar9 & 3) == 0) {
      uVar3 = __nwa__FUi(0xb00);
      *(u32 *)(param_1 + uVar4 * 4 + 0x18) = uVar3;
      puVar14 = *(u32 **)(param_1 + (uint)bVar1 * 4 + 0x18);
      iVar10 = 0;
    }
    else {
      uVar3 = __nwa__FUi(0xc00);
      *(u32 *)(param_1 + uVar4 * 4 + 0x18) = uVar3;
      in_a1_udw = (u32)extraout_v0_udw;
      in_register_0000005c = (u32)((ulong)extraout_v0_udw >> 0x20);
      puVar14 = *(u32 **)(param_1 + uVar4 * 4 + 0x18);
      *puVar14 = 0x50000000;
      puVar14[1] = *(u32 *)
                    (*(int *)(ourBtlSocket__9BtlSocket + 0x60c) +
                     (uint)*(ushort *)(*(int *)(ourBtlSocket__9BtlSocket + 0x60c) + 10) * 4 + 0xc);
      puVar14[2] = 0;
      puVar14[3] = 0;
      puVar14[4] = &DAT_1000000e;
      puVar14[5] = 0;
      puVar14[6] = 0;
      puVar14[7] = 0x5000000e;
      *(u64 *)(puVar14 + 8) = 0x6000000000000001;
      *(u64 *)(puVar14 + 10) = 0x68eeee;
      *(u64 *)(puVar14 + 0xc) = 1;
      *(u64 *)(puVar14 + 0xe) = 0x3f;
      *(u64 *)(puVar14 + 0x10) = 0x3003;
      *(u64 *)(puVar14 + 0x12) = 0x47;
      *(u64 *)(puVar14 + 0x14) = 0x44;
      *(u64 *)(puVar14 + 0x16) = 0x42;
      *(u64 *)(puVar14 + 0x18) = 0;
      *(u64 *)(puVar14 + 0x1a) = 0x14;
      *(u64 *)(puVar14 + 0x1c) = 5;
      *(u64 *)(puVar14 + 0x1e) = 0;
      uVar5 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x60c),1);
      *(u64 *)(puVar14 + 0x20) = uVar5;
      *(u64 *)(puVar14 + 0x22) = 0;
      *(u64 *)(puVar14 + 0x24) = 0x4400000000000001;
      *(u64 *)(puVar14 + 0x26) = 0x4c10;
      *(u64 *)(puVar14 + 0x28) = 0x46;
      *(u64 *)(puVar14 + 0x2c) = 0x71006f00;
      *(u64 *)(puVar14 + 0x2e) = 0x8f009100;
      *(u64 *)(puVar14 + 0x30) = 0x6400000000008001;
      *(u64 *)(puVar14 + 0x32) = 0x43c310;
      *(u64 *)(puVar14 + 0x34) = 0x156;
      *(u64 *)(puVar14 + 0x38) = 0;
      *(u64 *)(puVar14 + 0x3a) = 0x72007000;
      *(u64 *)(puVar14 + 0x3c) = 0x1c102010;
      *(u64 *)(puVar14 + 0x3e) = 0x8e109010;
      iVar10 = 0x10;
    }
    puVar14[iVar10 * 4] = &DAT_10000009;
    puVar14[iVar10 * 4 + 1] = 0;
    puVar14[iVar10 * 4 + 2] = &DAT_11000000;
    puVar14[iVar10 * 4 + 3] = 0x50000009;
    *(u64 *)(puVar14 + (iVar10 + 1) * 4) = 0x2000000000000001;
    *(u64 *)(puVar14 + (iVar10 + 1) * 4 + 2) = 0xee;
    *(u64 *)(puVar14 + (iVar10 + 2) * 4) = 0x3003;
    *(u64 *)(puVar14 + (iVar10 + 2) * 4 + 2) = 0x47;
    *(u64 *)(puVar14 + (iVar10 + 3) * 4) = 0x44;
    *(u64 *)(puVar14 + (iVar10 + 3) * 4 + 2) = 0x42;
    auVar2._8_4_ = in_a1_udw;
    auVar2._0_8_ = 0xa400000000008001;
    auVar2._12_4_ = in_register_0000005c;
    auVar8 = _pcpyld(in_zero_qw,auVar2);
    *(long *)(puVar14 + (iVar10 + 4) * 4) = auVar8._0_8_;
    *(u64 *)(puVar14 + (iVar10 + 4) * 4 + 2) = 0x4141c1c1f0;
    *(u64 *)(puVar14 + (iVar10 + 5) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 5) * 4 + 2) = 0;
    iVar11 = iVar10 + 10;
    puVar14[iVar11 * 4] = 0x50000000;
    puVar14[iVar11 * 4 + 1] =
         *(u32 *)
          (*(int *)(ourBtlSocket__9BtlSocket + 0x614) +
           (uint)*(ushort *)(*(int *)(ourBtlSocket__9BtlSocket + 0x614) + 10) * 4 + 0xc);
    puVar14[iVar11 * 4 + 2] = 0;
    puVar14[iVar11 * 4 + 3] = 0;
    puVar14[(iVar10 + 0xb) * 4] = &UNK_10000022;
    puVar14[(iVar10 + 0xb) * 4 + 1] = 0;
    puVar14[(iVar10 + 0xb) * 4 + 2] = 0;
    puVar14[(iVar10 + 0xb) * 4 + 3] = 0x50000022;
    *(u64 *)(puVar14 + (iVar10 + 0xc) * 4) = 0x4000000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0xc) * 4 + 2) = 0x68ee;
    *(u64 *)(puVar14 + (iVar10 + 0xd) * 4) = 1;
    *(u64 *)(puVar14 + (iVar10 + 0xd) * 4 + 2) = 0x3f;
    *(u64 *)(puVar14 + (iVar10 + 0xe) * 4) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0xe) * 4 + 2) = 0x14;
    *(u64 *)(puVar14 + (iVar10 + 0xf) * 4) = 5;
    *(u64 *)(puVar14 + (iVar10 + 0xf) * 4 + 2) = 0;
    uVar5 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x614),1);
    *(u64 *)(puVar14 + (iVar10 + 0x10) * 4) = uVar5;
    *(u64 *)(puVar14 + (iVar10 + 0x10) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x11) * 4) = 0x2400000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x11) * 4 + 2) = 0x10;
    *(u64 *)(puVar14 + (iVar10 + 0x12) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x13) * 4) = 0x440000000000800d;
    *(u64 *)(puVar14 + (iVar10 + 0x13) * 4 + 2) = 0x43c3;
    *(u64 *)(puVar14 + (iVar10 + 0x14) * 4) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x15) * 4) = 0x1d00580;
    *(u64 *)(puVar14 + (iVar10 + 0x16) * 4) = 0x580;
    *(u64 *)(puVar14 + (iVar10 + 0x17) * 4) = 0x1d00000;
    *(u64 *)(puVar14 + (iVar10 + 0x18) * 4) = 0x4600020;
    *(u64 *)(puVar14 + (iVar10 + 0x19) * 4) = 0x4d00260;
    *(u64 *)(puVar14 + (iVar10 + 0x1a) * 4) = 0x4600020;
    *(u64 *)(puVar14 + (iVar10 + 0x1b) * 4) = 0x4d00260;
    *(u64 *)(puVar14 + (iVar10 + 0x1c) * 4) = 0x4d00020;
    *(u64 *)(puVar14 + (iVar10 + 0x1d) * 4) = 0x4600260;
    *(u64 *)(puVar14 + (iVar10 + 0x1e) * 4) = 0x1d00000;
    *(u64 *)(puVar14 + (iVar10 + 0x1f) * 4) = 0x3800300;
    *(u64 *)(puVar14 + (iVar10 + 0x20) * 4) = 0x1d00300;
    *(u64 *)(puVar14 + (iVar10 + 0x21) * 4) = 0x3800000;
    *(u64 *)(puVar14 + (iVar10 + 0x22) * 4) = 0x3800000;
    *(u64 *)(puVar14 + (iVar10 + 0x23) * 4) = 0x46001a0;
    *(u64 *)(puVar14 + (iVar10 + 0x24) * 4) = 0x38001a0;
    *(u64 *)(puVar14 + (iVar10 + 0x25) * 4) = 0x4600000;
    *(u64 *)(puVar14 + (iVar10 + 0x26) * 4) = 0x4f00000;
    *(u64 *)(puVar14 + (iVar10 + 0x27) * 4) = 0x65000e0;
    *(u64 *)(puVar14 + (iVar10 + 0x28) * 4) = 0x4f000e0;
    *(u64 *)(puVar14 + (iVar10 + 0x29) * 4) = 0x6500000;
    *(u64 *)(puVar14 + (iVar10 + 0x2a) * 4) = 0x1d00300;
    *(u64 *)(puVar14 + (iVar10 + 0x2b) * 4) = 0x5c005a0;
    *(u64 *)(puVar14 + (iVar10 + 0x2c) * 4) = 0x1d005a0;
    *(u64 *)(puVar14 + (iVar10 + 0x2d) * 4) = 0x5c00300;
    iVar11 = iVar10 + 0x2e;
    puVar14[iVar11 * 4] = 0x50000000;
    puVar14[iVar11 * 4 + 1] =
         *(u32 *)
          (*(int *)(ourBtlSocket__9BtlSocket + 0x618) +
           (uint)*(ushort *)(*(int *)(ourBtlSocket__9BtlSocket + 0x618) + 10) * 4 + 0xc);
    puVar14[iVar11 * 4 + 2] = 0;
    puVar14[iVar11 * 4 + 3] = 0;
    puVar14[(iVar10 + 0x2f) * 4] = &UNK_1000000f;
    puVar14[(iVar10 + 0x2f) * 4 + 1] = 0;
    puVar14[(iVar10 + 0x2f) * 4 + 2] = 0;
    puVar14[(iVar10 + 0x2f) * 4 + 3] = 0x5000000f;
    *(u64 *)(puVar14 + (iVar10 + 0x30) * 4) = 0x3000000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x30) * 4 + 2) = 0x6ee;
    *(u64 *)(puVar14 + (iVar10 + 0x31) * 4) = 1;
    *(u64 *)(puVar14 + (iVar10 + 0x31) * 4 + 2) = 0x3f;
    uVar6 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x618),1);
    *(ulong *)(puVar14 + (iVar10 + 0x32) * 4) = uVar6 & 0xfffffffc0fffff | 0x2000000001300000;
    *(u64 *)(puVar14 + (iVar10 + 0x32) * 4 + 2) = 0x16;
    *(ulong *)(puVar14 + (iVar10 + 0x33) * 4) = uVar6 & 0xffffffffffffff | 0x600000000000000;
    *(u64 *)(puVar14 + (iVar10 + 0x33) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x34) * 4) = 0x6400000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x34) * 4 + 2) = 0x43c310;
    *(u64 *)(puVar14 + (iVar10 + 0x35) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x36) * 4) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x37) * 4) = 0x17008e0;
    *(u64 *)(puVar14 + (iVar10 + 0x38) * 4) = 0x2000000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x38) * 4 + 2) = 0x6e;
    *(ulong *)(puVar14 + (iVar10 + 0x39) * 4) = uVar6 & 0xfffffffc0fffff | 0x2000000001300000;
    *(u64 *)(puVar14 + (iVar10 + 0x39) * 4 + 2) = 0x16;
    *(ulong *)(puVar14 + (iVar10 + 0x3a) * 4) = uVar6 & 0xffffffffffffff | 0x600000000000000;
    *(u64 *)(puVar14 + (iVar10 + 0x3a) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x3b) * 4) = 0x6400000000008001;
    *(u64 *)(puVar14 + (iVar10 + 0x3b) * 4 + 2) = 0x43c310;
    *(u64 *)(puVar14 + (iVar10 + 0x3c) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x3d) * 4) = 0x1800000;
    *(u64 *)(puVar14 + (iVar10 + 0x3e) * 4) = 0x2f005d0;
    iVar11 = iVar10 + 0x3f;
    puVar14[iVar11 * 4] = &DAT_10000031;
    puVar14[iVar11 * 4 + 1] = 0;
    puVar14[iVar11 * 4 + 2] = 0;
    puVar14[iVar11 * 4 + 3] = 0x50000031;
    auVar8._8_4_ = (int)extraout_v0_udw_00;
    auVar8._0_8_ = 0xc400000000008008;
    auVar8._12_4_ = (int)((ulong)extraout_v0_udw_00 >> 0x20);
    auVar8 = _pcpyld(in_zero_qw,auVar8);
    *(long *)(puVar14 + (iVar10 + 0x40) * 4) = auVar8._0_8_;
    *(u64 *)(puVar14 + (iVar10 + 0x40) * 4 + 2) = 0x44144441cc10;
    *(u64 *)(puVar14 + (iVar10 + 0x41) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x46) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x47) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x4c) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x4d) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x52) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x53) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x58) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x59) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x5e) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x5f) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 100) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x65) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x6a) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x6b) * 4) = 0x4c;
    *(u64 *)(puVar14 + (iVar10 + 0x70) * 4 + 2) = 0;
    iVar11 = iVar10 + 0x71;
    puVar14[iVar11 * 4] = 0x50000000;
    puVar14[iVar11 * 4 + 1] =
         *(u32 *)
          (*(int *)(ourBtlSocket__9BtlSocket + 0x61c) +
           (uint)*(ushort *)(*(int *)(ourBtlSocket__9BtlSocket + 0x61c) + 10) * 4 + 0xc);
    puVar14[iVar11 * 4 + 2] = 0;
    puVar14[iVar11 * 4 + 3] = 0;
    puVar14[(iVar10 + 0x72) * 4] = 0x6000003d;
    puVar14[(iVar10 + 0x72) * 4 + 1] = 0;
    puVar14[(iVar10 + 0x72) * 4 + 2] = 0;
    puVar14[(iVar10 + 0x72) * 4 + 3] = 0x5000003d;
    *(u64 *)(puVar14 + (iVar10 + 0x73) * 4) = 0x2000000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x73) * 4 + 2) = 0x6e;
    *(u64 *)(puVar14 + (iVar10 + 0x74) * 4) = 1;
    *(u64 *)(puVar14 + (iVar10 + 0x74) * 4 + 2) = 0x3f;
    uVar5 = GetTex0__6JRCTexFb(*(u32 *)(ourBtlSocket__9BtlSocket + 0x61c),1);
    *(u64 *)(puVar14 + (iVar10 + 0x75) * 4) = uVar5;
    *(u64 *)(puVar14 + (iVar10 + 0x75) * 4 + 2) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x76) * 4) = 0x6400000000000004;
    *(u64 *)(puVar14 + (iVar10 + 0x76) * 4 + 2) = 0x43c310;
    *(u64 *)(puVar14 + (iVar10 + 0x77) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x78) * 4) = 0;
    *(u64 *)(puVar14 + (iVar10 + 0x79) * 4) = 0x1900290;
    *(u64 *)(puVar14 + (iVar10 + 0x7a) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x7b) * 4) = 0x290;
    *(u64 *)(puVar14 + (iVar10 + 0x7c) * 4) = 0x16005d0;
    *(u64 *)(puVar14 + (iVar10 + 0x7d) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x7e) * 4) = 0x5d0;
    *(u64 *)(puVar14 + (iVar10 + 0x7f) * 4) = 0x16008d0;
    *(u64 *)(puVar14 + (iVar10 + 0x80) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x81) * 4) = 0x8d0;
    *(u64 *)(puVar14 + (iVar10 + 0x82) * 4) = 0x1600bc0;
    *(u64 *)(puVar14 + (iVar10 + 0x83) * 4) = 0x2400000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x83) * 4 + 2) = 0x10;
    *(u64 *)(puVar14 + (iVar10 + 0x84) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x85) * 4) = 0x4400000000000006;
    *(u64 *)(puVar14 + (iVar10 + 0x85) * 4 + 2) = 0x43c3;
    *(u64 *)(puVar14 + (iVar10 + 0x92) * 4) = 0x2400000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0x92) * 4 + 2) = 0x10;
    *(u64 *)(puVar14 + (iVar10 + 0x93) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0x94) * 4) = 0x4400000000000006;
    *(u64 *)(puVar14 + (iVar10 + 0x94) * 4 + 2) = 0x43c3;
    *(u64 *)(puVar14 + (iVar10 + 0xa1) * 4) = 0x2400000000000001;
    *(u64 *)(puVar14 + (iVar10 + 0xa1) * 4 + 2) = 0x10;
    *(u64 *)(puVar14 + (iVar10 + 0xa2) * 4) = 0x156;
    *(u64 *)(puVar14 + (iVar10 + 0xa3) * 4) = 0x4400000000008006;
    *(u64 *)(puVar14 + (iVar10 + 0xa3) * 4 + 2) = 0x43c3;
  }
  iVar10 = *(int *)(param_1 + (uint)bVar1 * 4 + 0x18);
  iVar13 = 0;
  iVar11 = (uint)*(ushort *)(iVar12 + 0x50c) * 0x18;
  if ((uint)*(ushort *)(iVar12 + 0x50c) * 3 != 0) {
    iVar11 = iVar11 + 0x25;
  }
  fVar17 = (float)(iVar11 + 0x10);
  fVar15 = (float)(iVar11 + 0xc1);
  fVar18 = (float)*(int *)(param_1 + 0x78) - fVar15 / 2.0;
  fVar16 = (float)(*(int *)(param_1 + 0x74) + -0xc4);
  if ((*pbVar9 & 3) != 0) {
    *(u64 *)(iVar10 + 0xa8) = 0x80000000;
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + 0xd8) = CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x808080;
    iVar13 = 0x10;
  }
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 76.8);
  *(ulong *)(iVar10 + (iVar13 + 6) * 0x10) = lVar7 << 0x18 | 0x4e4141;
  uVar6 = __fixunssfdi((fVar16 + 1792.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 6) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar5 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 76.8);
  *(ulong *)(iVar10 + (iVar13 + 7) * 0x10) =
       CONCAT44((int)((ulong)uVar5 >> 8),(int)uVar5 << 0x18) | 0xa080a;
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar15) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 7) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 76.8);
  *(ulong *)(iVar10 + (iVar13 + 8) * 0x10) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x4e4141;
  lVar7 = __fixunssfdi((fVar18 + 1824.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 392.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 8) * 0x10 + 8) = lVar7 << 0x10 | uVar6;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 76.8);
  *(ulong *)(iVar10 + (iVar13 + 9) * 0x10) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0xa080a;
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 392.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar15) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 9) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x12) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x808080;
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 109.0) * 16.0);
  lVar7 = __fixunssfdi(((fVar18 + 1824.0) - 17.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x14) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 197.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 12.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x15) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 195.0) * 16.0);
  lVar7 = __fixunssfdi(((fVar18 + 1824.0) - 17.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x16) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 283.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 12.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x17) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 26.0) * 16.0);
  lVar7 = __fixunssfdi(((fVar18 + 1824.0) - 5.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x18) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 111.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 2.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x19) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  lVar7 = __fixunssfdi(((fVar18 + 1824.0) - 5.0) * 16.0);
  uVar6 = __fixunssfdi((((fVar16 + 1792.0 + 392.0) - 110.0) + 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1a) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) | uVar6;
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + 2.0) * 16.0);
  uVar6 = __fixunssfdi((((fVar16 + 1792.0 + 392.0) - 25.0) - 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1b) * 0x10 + 8) =
       CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) | uVar6;
  lVar7 = __fixunssfdi(((fVar18 + 1824.0 + fVar15) - 2.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 26.0 + 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1c) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi((((fVar16 + 1792.0 + 392.0) - 25.0) - 2.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar15 + 5.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1d) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  uVar6 = __fixunssfdi(((fVar16 + 1792.0) - 21.0) * 16.0 - 8.0);
  uVar5 = __fixunssfdi(((fVar18 + 1824.0) - 12.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1e) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 27.0) * 16.0 - 8.0);
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + 15.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x1f) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  lVar7 = __fixunssfdi(((fVar18 + 1824.0) - 12.0) * 16.0);
  uVar6 = __fixunssfdi(((fVar16 + 1792.0 + 392.0) - 27.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x20) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) | uVar6;
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + 15.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 392.0 + 21.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x21) * 0x10 + 8) =
       CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) | uVar6;
  uVar6 = __fixunssfdi(((fVar16 + 1792.0) - 21.0) * 16.0 - 8.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 13.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x22) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 5.0) * 16.0 - 8.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 27.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x23) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 13.0) * 16.0);
  uVar6 = __fixunssfdi(((fVar16 + 1792.0 + 392.0) - 5.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x24) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) | uVar6;
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 27.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 392.0 + 21.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x25) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) | uVar6;
  uVar6 = __fixunssfdi(((fVar16 + 1792.0) - 12.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 26.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x26) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  lVar7 = __fixunssfdi((((fVar18 + 1824.0 + fVar15) - 49.0) - 1.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 2.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x27) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + 26.0) * 16.0);
  uVar6 = __fixunssfdi((((fVar16 + 1792.0 + 392.0) - 2.0) - 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x28) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) | uVar6;
  uVar6 = __fixunssfdi(((fVar16 + 1792.0 + 392.0 + 12.0) - 1.0) * 16.0);
  lVar7 = __fixunssfdi((((fVar18 + 1824.0 + fVar15) - 49.0) - 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x29) * 0x10 + 8) = uVar6 | lVar7 << 0x10;
  uVar5 = __fixunssfdi(((fVar18 + 1824.0 + fVar15) - 51.0) * 16.0);
  uVar6 = __fixunssfdi((((fVar16 + 1792.0) - 15.0) + 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x2a) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar15 + 12.0) * 16.0);
  uVar6 = __fixunssfdi((fVar16 + 1792.0 + 27.0 + 1.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x2b) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  uVar6 = __fixunssfdi((((fVar16 + 1792.0 + 392.0) - 27.0) - 1.0) * 16.0);
  lVar7 = __fixunssfdi(((fVar18 + 1824.0 + fVar15) - 51.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x2c) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  uVar6 = __fixunssfdi(((fVar16 + 1792.0 + 392.0 + 15.0) - 1.0) * 16.0);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar15 + 12.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x2d) * 0x10 + 8) =
       uVar6 | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x35) * 0x10 + 8) = lVar7 << 0x18 | 0x808080;
  if (*(short *)(iVar12 + 0x50c) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x36) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x37) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x36) * 0x10 + 8) =
         (long)((iVar11 + 0x6b9) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 23.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x37) * 0x10 + 8) =
         (long)((iVar11 + 0x747) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x3c) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x808080;
  iVar11 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x3d) * 0x10 + 8) =
       (long)((iVar11 + 0x6d1) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar11 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 23.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0x3e) * 0x10 + 8) = (long)((iVar11 + 0x72e) * 0x10) | lVar7 << 0x10;
  *(u64 *)(iVar10 + (iVar13 + 0x41) * 0x10 + 8) = 0x967d82;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x43) * 0x10) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  *(u64 *)(iVar10 + (iVar13 + 0x45) * 0x10 + 8) = 0x967d82;
  if (*(short *)(iVar12 + 0x50c) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x42) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x42) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x43) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x44) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x44) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x45) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x46) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x46) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 28.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x42) * 0x10) =
         (long)((iVar11 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 32.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x42) * 0x10 + 8) =
         (long)((iVar11 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 28.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x43) * 0x10 + 8) = (long)((iVar11 + 0x69c) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 32.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x44) * 0x10) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 28.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x44) * 0x10 + 8) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 32.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x45) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 28.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x46) * 0x10) =
         (long)((iVar11 + 0x7a8) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 32.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x46) * 0x10 + 8) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10
    ;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x47) * 0x10 + 8) = 0x967d82;
  if (((uint)(((ulong)*(ushort *)(param_1 + 0x38) << 0x37) >> 0x3a) & 1) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x49) * 0x10) = 0x967d82;
  }
  else {
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x49) * 0x10) =
         CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x4b) * 0x10 + 8) = 0x967d82;
  if (*(short *)(iVar12 + 0x50c) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x48) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x48) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x49) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4a) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4a) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4b) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4c) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4c) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 54.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x48) * 0x10) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 56.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x48) * 0x10 + 8) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 54.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x49) * 0x10 + 8) = (long)((iVar11 + 0x69c) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 56.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4a) * 0x10) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 54.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4a) * 0x10 + 8) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 56.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4b) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 54.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4c) * 0x10) =
         (long)((iVar11 + 0x7a8) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 56.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4c) * 0x10 + 8) =
         (long)((iVar11 + 0x7a8) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  }
  *(u64 *)(iVar10 + (iVar13 + 0x4d) * 0x10 + 8) = 0x967d82;
  if (((uint)(((ulong)*(ushort *)(param_1 + 0x38) << 0x37) >> 0x3a) & 2) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x4f) * 0x10) = 0x967d82;
  }
  else {
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x4f) * 0x10) =
         CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x51) * 0x10 + 8) = 0x967d82;
  if (*(ushort *)(iVar12 + 0x50c) < 2) {
    *(u64 *)(iVar10 + (iVar13 + 0x4e) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4e) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x4f) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x50) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x50) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x51) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x52) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x52) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 78.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x4e) * 0x10) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 80.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x4e) * 0x10 + 8) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 78.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x4f) * 0x10 + 8) = (long)((iVar11 + 0x69c) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 80.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x50) * 0x10) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 78.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x50) * 0x10 + 8) = (long)((iVar11 + 0x764) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 80.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x51) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 78.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x52) * 0x10) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 80.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x52) * 0x10 + 8) =
         (long)((iVar11 + 0x7a8) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  *(u64 *)(iVar10 + (iVar13 + 0x53) * 0x10 + 8) = 0x967d82;
  if (((uint)(((ulong)*(ushort *)(param_1 + 0x38) << 0x37) >> 0x3a) & 4) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x55) * 0x10) = 0x967d82;
  }
  else {
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x55) * 0x10) =
         CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x57) * 0x10 + 8) = 0x967d82;
  if (*(ushort *)(iVar12 + 0x50c) < 3) {
    *(u64 *)(iVar10 + (iVar13 + 0x54) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x54) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x55) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x56) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x56) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x57) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x58) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x58) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 102.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x54) * 0x10) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 104.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x54) * 0x10 + 8) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10
    ;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 102.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x55) * 0x10 + 8) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 104.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x56) * 0x10) =
         (long)((iVar11 + 0x69c) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 102.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x56) * 0x10 + 8) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 104.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x57) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 102.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x58) * 0x10) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 104.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x58) * 0x10 + 8) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10
    ;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x59) * 0x10 + 8) = 0x967d82;
  if ((*(ushort *)(param_1 + 0x38) & 0x40) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x5b) * 0x10) = 0x967d82;
  }
  else {
    uVar5 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5b) * 0x10) =
         CONCAT44((int)((ulong)uVar5 >> 8),(int)uVar5 << 0x18) | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x5d) * 0x10 + 8) = 0x967d82;
  if (*(ushort *)(iVar12 + 0x50c) < 4) {
    *(u64 *)(iVar10 + (iVar13 + 0x5a) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5a) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5b) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5c) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5c) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5d) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5e) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x5e) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 126.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x5a) * 0x10) = (long)((iVar11 + 0x658) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 128.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5a) * 0x10 + 8) =
         (long)((iVar11 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 126.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5b) * 0x10 + 8) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 128.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x5c) * 0x10) = (long)((iVar11 + 0x69c) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 126.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5c) * 0x10 + 8) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 128.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5d) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 126.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5e) * 0x10) =
         (long)((iVar11 + 0x7a8) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar11 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 128.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x5e) * 0x10 + 8) =
         (long)((iVar11 + 0x7a8) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  *(u64 *)(iVar10 + (iVar13 + 0x5f) * 0x10 + 8) = 0x967d82;
  if ((((ulong)*(ushort *)(param_1 + 0x38) & 0x1ff) >> 3 & 0x10) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x61) * 0x10) = 0x967d82;
  }
  else {
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x61) * 0x10) = lVar7 << 0x18 | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 99) * 0x10 + 8) = 0x967d82;
  if (*(ushort *)(iVar12 + 0x50c) < 5) {
    *(u64 *)(iVar10 + (iVar13 + 0x60) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x60) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x61) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x62) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x62) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 99) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 100) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 100) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 150.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x60) * 0x10) =
         (long)((iVar11 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 152.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x60) * 0x10 + 8) =
         (long)((iVar11 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 150.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x61) * 0x10 + 8) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 152.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x62) * 0x10) =
         (long)((iVar11 + 0x69c) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 150.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x62) * 0x10 + 8) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 152.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 99) * 0x10) =
         (long)((iVar11 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 150.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 100) * 0x10) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 152.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 100) * 0x10 + 8) = (long)((iVar11 + 0x7a8) * 0x10) | lVar7 << 0x10;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x65) * 0x10 + 8) = 0x967d82;
  if (((uint)(((ulong)*(ushort *)(param_1 + 0x38) << 0x37) >> 0x3a) & 0x20) == 0) {
    *(u64 *)(iVar10 + (iVar13 + 0x67) * 0x10) = 0x967d82;
  }
  else {
    lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
    *(ulong *)(iVar10 + (iVar13 + 0x67) * 0x10) =
         CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  }
  *(u64 *)(iVar10 + (iVar13 + 0x69) * 0x10 + 8) = 0x967d82;
  if (*(ushort *)(iVar12 + 0x50c) < 6) {
    *(u64 *)(iVar10 + (iVar13 + 0x66) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x66) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x67) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x68) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x68) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x69) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x6a) * 0x10) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x6a) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 174.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x66) * 0x10) = (long)((iVar12 + 0x658) * 0x10) | lVar7 << 0x10;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 176.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x66) * 0x10 + 8) =
         (long)((iVar12 + 0x658) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 174.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x67) * 0x10 + 8) = (long)((iVar12 + 0x69c) * 0x10) | lVar7 << 0x10
    ;
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 176.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x68) * 0x10) =
         (long)((iVar12 + 0x69c) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 174.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x68) * 0x10 + 8) =
         (long)((iVar12 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 176.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x69) * 0x10) =
         (long)((iVar12 + 0x764) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 174.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x6a) * 0x10) =
         (long)((iVar12 + 0x7a8) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    uVar4 = (*(int *)(param_1 + 0x74) + 0x7a8) * 0x10;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + 16.0 + 176.0) * 16.0);
    iVar12 = iVar10 + (iVar13 + 0x6a) * 0x10;
    *(uint *)(iVar12 + 8) = uVar4 | (uint)(lVar7 << 0x10);
    *(uint *)(iVar12 + 0xc) = (int)uVar4 >> 0x1f | (uint)((ulong)lVar7 >> 0x10);
  }
  *(u64 *)(iVar10 + (iVar13 + 0x6b) * 0x10 + 8) = 0x967d82;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x6d) * 0x10) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x967d82;
  *(u64 *)(iVar10 + (iVar13 + 0x6f) * 0x10 + 8) = 0x967d82;
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 27.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0x6c) * 0x10) = (long)((iVar12 + 0x658) * 0x10) | lVar7 << 0x10;
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 31.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x6c) * 0x10 + 8) =
       (long)((iVar12 + 0x658) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 27.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x6d) * 0x10 + 8) =
       (long)((iVar12 + 0x69c) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 31.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0x6e) * 0x10) = (long)((iVar12 + 0x69c) * 0x10) | lVar7 << 0x10;
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 27.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x6e) * 0x10 + 8) =
       (long)((iVar12 + 0x764) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 31.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0x6f) * 0x10) = (long)((iVar12 + 0x764) * 0x10) | lVar7 << 0x10;
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 27.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x70) * 0x10) =
       (long)((iVar12 + 0x7a8) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = *(int *)(param_1 + 0x74);
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 31.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x70) * 0x10 + 8) =
       (long)((iVar12 + 0x7a8) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  uVar5 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x77) * 0x10 + 8) =
       CONCAT44((int)((ulong)uVar5 >> 8),(int)uVar5 << 0x18) | 0x4b3f41;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x7a) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x4b3f41;
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x7d) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x4b3f41;
  if (((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) & 7) >> 2 == 0) {
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x78) * 0x10 + 8) = (long)((iVar12 + 0x688) * 0x10) | lVar7 << 0x10
    ;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 62.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x79) * 0x10 + 8) =
         (long)((iVar12 + 0x6b1) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x7b) * 0x10 + 8) =
         (long)((iVar12 + 0x700) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x7c) * 0x10 + 8) =
         (long)((iVar12 + 0x734) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    *(u64 *)(iVar10 + (iVar13 + 0x7e) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x7f) * 0x10 + 8) = 0x71006f00;
  }
  else {
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x78) * 0x10 + 8) =
         (long)((iVar12 + 0x648) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 62.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x79) * 0x10 + 8) =
         (long)((iVar12 + 0x671) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x7b) * 0x10 + 8) =
         (long)((iVar12 + 0x6c0) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x7c) * 0x10 + 8) =
         (long)((iVar12 + 0x6f4) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x7e) * 0x10 + 8) = (long)((iVar12 + 0x743) * 0x10) | lVar7 << 0x10
    ;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x7f) * 0x10 + 8) =
         (long)((iVar12 + 0x773) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  }
  uVar5 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x80) * 0x10 + 8) =
       CONCAT44((int)((ulong)uVar5 >> 8),(int)uVar5 << 0x18) | 0x4b3f41;
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x81) * 0x10 + 8) =
       (long)((iVar12 + 0x648) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = *(int *)(param_1 + 0x74);
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 81.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x82) * 0x10 + 8) =
       (long)((iVar12 + 0x677) * 0x10) | CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  iVar12 = 0;
  if (((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) & 7) >> 2 == 0) {
    iVar12 = 0x40;
  }
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x84) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x555555;
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) < 100000) {
    *(u64 *)(iVar10 + (iVar13 + 0x86) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x87) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) / 100000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x86) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x86) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x671 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x87) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x87) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x67e + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) < 10000) {
    *(u64 *)(iVar10 + (iVar13 + 0x88) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x89) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) / 10000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x88) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x88) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x67c + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x89) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x89) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x689 + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) < 1000) {
    *(u64 *)(iVar10 + (iVar13 + 0x8a) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x8b) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) / 1000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x8a) * 0x10) = (ulong)(uVar4 * 0xd0 | 0x1900000);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x8a) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x687 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x8b) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x8b) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x694 + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) < 100) {
    *(u64 *)(iVar10 + (iVar13 + 0x8c) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x8d) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) / 100) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x8c) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x8c) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x692 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x8d) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x8d) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x69f + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) < 10) {
    *(u64 *)(iVar10 + (iVar13 + 0x8e) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x8f) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x290) / 10) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x8e) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x8e) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x69d + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x8f) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x8f) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x6aa + iVar12) * 0x10);
  }
  iVar11 = *(int *)(ourBtlSocket__9BtlSocket + 0x290) % 10;
  *(ulong *)(iVar10 + (iVar13 + 0x90) * 0x10) = (long)(iVar11 * 0xd0) | 0x1900000;
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x90) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
       (long)((*(int *)(param_1 + 0x74) + 0x6a8 + iVar12) * 0x10);
  *(ulong *)(iVar10 + (iVar13 + 0x91) * 0x10) = (long)((iVar11 * 0xd + 0xd) * 0x10) | 0x2f00000;
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0x91) * 0x10 + 8) =
       lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x6b5 + iVar12) * 0x10);
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0x93) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x555555;
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) < 100000) {
    *(u64 *)(iVar10 + (iVar13 + 0x95) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x96) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) / 100000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x95) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x95) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x6f4 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x96) * 0x10) = (ulong)((uVar4 * 0xd + 0xd) * 0x10 | 0x2f00000);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x96) * 0x10 + 8) =
         CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
         (long)((*(int *)(param_1 + 0x74) + 0x701 + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) < 10000) {
    *(u64 *)(iVar10 + (iVar13 + 0x97) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x98) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) / 10000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x97) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x97) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x6ff + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x98) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x98) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x70c + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) < 1000) {
    *(u64 *)(iVar10 + (iVar13 + 0x99) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x9a) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) / 1000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x99) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x99) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x70a + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x9a) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x9a) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x717 + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) < 100) {
    *(u64 *)(iVar10 + (iVar13 + 0x9b) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x9c) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) / 100) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x9b) * 0x10) = (ulong)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x9b) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x715 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x9c) * 0x10) = (ulong)((uVar4 * 0xd + 0xd) * 0x10 | 0x2f00000);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0x9c) * 0x10 + 8) =
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10)) |
         (long)((*(int *)(param_1 + 0x74) + 0x722 + iVar12) * 0x10);
  }
  if (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) < 10) {
    *(u64 *)(iVar10 + (iVar13 + 0x9d) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0x9e) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x294) / 10) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0x9d) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x9d) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x720 + iVar12) * 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0x9e) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0x9e) * 0x10 + 8) =
         lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x72d + iVar12) * 0x10);
  }
  iVar11 = *(int *)(ourBtlSocket__9BtlSocket + 0x294) % 10;
  *(ulong *)(iVar10 + (iVar13 + 0x9f) * 0x10) = (long)(iVar11 * 0xd0) | 0x1900000;
  uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
  *(ulong *)(iVar10 + (iVar13 + 0x9f) * 0x10 + 8) =
       CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10) |
       (long)((*(int *)(param_1 + 0x74) + 0x72b + iVar12) * 0x10);
  *(ulong *)(iVar10 + (iVar13 + 0xa0) * 0x10) = (long)((iVar11 * 0xd + 0xd) * 0x10) | 0x2f00000;
  lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
  *(long *)(iVar10 + (iVar13 + 0xa0) * 0x10 + 8) =
       lVar7 << 0x10 | (long)((*(int *)(param_1 + 0x74) + 0x738 + iVar12) * 0x10);
  lVar7 = __fixunssfdi(*(float *)(param_1 + 0x7c) * 128.0);
  *(ulong *)(iVar10 + (iVar13 + 0xa2) * 0x10 + 8) =
       CONCAT44((int)((ulong)lVar7 >> 8),(int)(lVar7 << 0x18)) | 0x555555;
  if ((*(uint *)(ourBtlSocket__9BtlSocket + 0x298) < 100000) ||
     (-1 < (long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
    *(u64 *)(iVar10 + (iVar13 + 0xa4) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xa5) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x298) / 100000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xa4) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xa4) * 0x10 + 8) =
         (long)((iVar12 + 0x773) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0xa5) * 0x10) = (ulong)((uVar4 * 0xd + 0xd) * 0x10 | 0x2f00000);
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xa5) * 0x10 + 8) =
         (long)((iVar12 + 0x780) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  if ((*(uint *)(ourBtlSocket__9BtlSocket + 0x298) < 10000) ||
     (((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) & 7) >> 2 == 0)) {
    *(u64 *)(iVar10 + (iVar13 + 0xa6) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xa7) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x298) / 10000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xa6) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0xa6) * 0x10 + 8) = (long)((iVar12 + 0x77e) * 0x10) | lVar7 << 0x10
    ;
    *(ulong *)(iVar10 + (iVar13 + 0xa7) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(long *)(iVar10 + (iVar13 + 0xa7) * 0x10 + 8) = (long)((iVar12 + 0x78b) * 0x10) | lVar7 << 0x10
    ;
  }
  if ((*(uint *)(ourBtlSocket__9BtlSocket + 0x298) < 1000) ||
     (-1 < (long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
    *(u64 *)(iVar10 + (iVar13 + 0xa8) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xa9) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x298) / 1000) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xa8) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xa8) * 0x10 + 8) =
         (long)((iVar12 + 0x789) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    *(ulong *)(iVar10 + (iVar13 + 0xa9) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xa9) * 0x10 + 8) =
         (long)((iVar12 + 0x796) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  }
  if ((*(uint *)(ourBtlSocket__9BtlSocket + 0x298) < 100) ||
     (-1 < (long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
    *(u64 *)(iVar10 + (iVar13 + 0xaa) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xab) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x298) / 100) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xaa) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xaa) * 0x10 + 8) =
         (long)((iVar12 + 0x794) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    *(ulong *)(iVar10 + (iVar13 + 0xab) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xab) * 0x10 + 8) =
         (long)((iVar12 + 0x7a1) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  if ((*(uint *)(ourBtlSocket__9BtlSocket + 0x298) < 10) ||
     (-1 < (long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d))) {
    *(u64 *)(iVar10 + (iVar13 + 0xac) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xad) * 0x10 + 8) = 0x71006f00;
  }
  else {
    uVar4 = (*(uint *)(ourBtlSocket__9BtlSocket + 0x298) / 10) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xac) * 0x10) = (long)(int)(uVar4 * 0xd0) | 0x1900000;
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xac) * 0x10 + 8) =
         (long)((iVar12 + 0x79f) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
    *(ulong *)(iVar10 + (iVar13 + 0xad) * 0x10) =
         (long)(int)((uVar4 * 0xd + 0xd) * 0x10) | 0x2f00000;
    iVar12 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xad) * 0x10 + 8) =
         (long)((iVar12 + 0x7ac) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
  }
  if ((long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) << 0x3d) < 0) {
    iVar12 = *(int *)(ourBtlSocket__9BtlSocket + 0x298) % 10;
    *(ulong *)(iVar10 + (iVar13 + 0xae) * 0x10) = (long)(iVar12 * 0xd0) | 0x1900000;
    iVar11 = *(int *)(param_1 + 0x74);
    lVar7 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 37.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xae) * 0x10 + 8) =
         (long)((iVar11 + 0x7aa) * 0x10) |
         CONCAT44((int)((ulong)lVar7 >> 0x10),(int)(lVar7 << 0x10));
    *(ulong *)(iVar10 + (iVar13 + 0xaf) * 0x10) = (long)((iVar12 * 0xd + 0xd) * 0x10) | 0x2f00000;
    iVar12 = *(int *)(param_1 + 0x74);
    uVar5 = __fixunssfdi((fVar18 + 1824.0 + fVar17 + 59.0) * 16.0);
    *(ulong *)(iVar10 + (iVar13 + 0xaf) * 0x10 + 8) =
         (long)((iVar12 + 0x7b7) * 0x10) | CONCAT44((int)((ulong)uVar5 >> 0x10),(int)uVar5 << 0x10);
  }
  else {
    *(u64 *)(iVar10 + (iVar13 + 0xae) * 0x10 + 8) = 0x71006f00;
    *(u64 *)(iVar10 + (iVar13 + 0xaf) * 0x10 + 8) = 0x71006f00;
  }
  *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfe | bVar1;
  return;
}

/* ---- 0x003581f0 size 0x338  BtlBonus::WinSequence(v)
 *      mangled: WinSequence__8BtlBonusFv */
void WinSequence__8BtlBonusFv(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x82);
  if (sVar1 == 0xc) {
    if (*(short *)(param_1 + 0x84) == 1) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0x8c));
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfd;
      Release__7MenuObjFv((MenuObj *)(param_1 + 0xcc));
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xf7;
      if (((ulong)*(ushort *)(param_1 + 0x80) & 0xfff) >> 4 != 0) {
        __destroy_new_array(*(u32 *)(param_1 + 0x180),0x273e20);
        *(u32 *)(param_1 + 0x180) = 0;
      }
      *(ushort *)(param_1 + 0x80) = *(ushort *)(param_1 + 0x80) & 0xf00f;
      if (*(int *)(param_1 + 0x188) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + 0x188),0x2661a0);
        *(u32 *)(param_1 + 0x188) = 0;
      }
      if (*(int *)(param_1 + 0x184) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + 0x184),0x277890);
      }
      *(u32 *)(param_1 + 0x184) = 0;
      if (*(int *)(param_1 + 0x18c) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + 0x18c),0x2766d0);
      }
      *(u32 *)(param_1 + 0x18c) = 0;
      if (*(int *)(param_1 + 400) != 0) {
        __destroy_new_array(*(u32 *)(param_1 + 400),0x28d070);
      }
      *(u32 *)(param_1 + 400) = 0;
      *(u16 *)(param_1 + 0x82) = 0;
      *(u16 *)(param_1 + 0x84) = 0;
    }
    else if ((*(short *)(param_1 + 0x84) == 0) && (*(char *)(param_1 + 0x174) == '\0')) {
      if ((*(byte *)(param_1 + 0x80) & 1) != 0) {
        ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + 0x8c));
      }
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfe;
      if ((long)((ulong)*(byte *)(param_1 + 0x80) << 0x3d) < 0) {
        ReleaseOT__7MenuObjFv((MenuObj *)(param_1 + 0xcc));
      }
      *(byte *)(param_1 + 0x80) = *(byte *)(param_1 + 0x80) & 0xfb;
      *(u16 *)(param_1 + 0x84) = 1;
    }
  }
  else if (((sVar1 != 2) && (sVar1 == 1)) && (*(char *)(param_1 + 0x174) == '\x01')) {
    *(u16 *)(param_1 + 0x82) = 2;
    *(u16 *)(param_1 + 0x84) = 0;
  }
  return;
}

/* ---- 0x00358530 size 0x1468  BtlBonus::WinCreate(v)
 *      mangled: WinCreate__8BtlBonusFv */
void WinCreate__8BtlBonusFv(int param_1)

{
  short sVar1;
  u32 uVar2;
  void *pvVar3;
  u64 uVar4;
  short sVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  long lVar13;
  int iVar14;
  char acStack_50 [36];
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iVar6 = ourBtlSocket__9BtlSocket;
  iVar11 = ourBtlSocket__9BtlSocket + 0x16c;
  iStack_10 = param_1;
  if (*(short *)(param_1 + 0x82) == 0) {
    *(u16 *)(param_1 + 0x82) = 2;
    *(u16 *)(param_1 + 0x84) = 0;
    *(u32 *)(param_1 + 0x88) = 0;
    Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(param_1 + 0x8c,0x2c,0x200,0x100,1,0,0);
    *(byte *)(iStack_10 + 0x80) = *(byte *)(iStack_10 + 0x80) & 0xfd | 2;
    *(u16 *)(iStack_10 + 0xa0) = 1;
    AddPriority__12MenuObjTableFP7MenuObj
              ((MenuObjTable *)(iStack_10 + 0xe4),(MenuObj *)(iStack_10 + 0x8c));
    *(u16 *)(iStack_10 + 0xe0) = 8;
    AddOT__7MenuObjFv((MenuObj *)(iStack_10 + 0xcc));
    *(byte *)(iStack_10 + 0x80) = *(byte *)(iStack_10 + 0x80) & 0xfb | 4;
    Create__10MenuWindowFUcUcffff((MenuWindow *)(iStack_10 + 0xcc),0,1,0.0,0.0,512.0,448.0);
    *(byte *)(iStack_10 + 0x80) = *(byte *)(iStack_10 + 0x80) & 0xf7 | 8;
    if (((ulong)*(ushort *)(iStack_10 + 0x80) & 0xfff) >> 4 == 0) {
      uVar4 = __nwa__FUi(0x1010);
      uVar2 = __construct_new_array(uVar4,0x27bfd0,0x27c030,0x80,0x20);
      *(u32 *)(iStack_10 + 0x180) = uVar2;
      *(ushort *)(iStack_10 + 0x80) = *(ushort *)(iStack_10 + 0x80) & 0xf00f | 0x10;
    }
    iVar14 = *(int *)(iStack_10 + 0x180);
    iVar7 = 0;
    for (iVar10 = 0; iVar10 < 6; iVar10 = iVar10 + 1) {
      Create__8MenuTextFUcUc((MenuText *)(iVar14 + iVar7 * 0x80),1,2);
      *(u16 *)(iVar14 + iVar7 * 0x80 + 0x14) = 2;
      *(u8 *)(iVar14 + iVar7 * 0x80 + 0x5a) = 1;
      *(u8 *)(iVar14 + iVar7 * 0x80 + 0x5b) = 0;
      *(u16 *)(iVar14 + iVar7 * 0x80 + 0x1c) = 0;
      *(short *)(iVar14 + iVar7 * 0x80 + 0x1e) = (short)iVar10;
      iVar8 = iVar14 + iVar7 * 0x80;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_10 + 0xcc),(MenuPlace *)(iVar14 + iVar7 * 0x80));
      iVar8 = iVar7 + 1;
      Create__8MenuTextFUcUc((MenuText *)(iVar14 + iVar8 * 0x80),1,2);
      *(u16 *)(iVar14 + iVar8 * 0x80 + 0x14) = 2;
      *(u8 *)(iVar14 + iVar8 * 0x80 + 0x5a) = 1;
      *(u8 *)(iVar14 + iVar8 * 0x80 + 0x5b) = 0;
      *(u16 *)(iVar14 + iVar8 * 0x80 + 0x1c) = 1;
      *(short *)(iVar14 + iVar8 * 0x80 + 0x1e) = (short)iVar10;
      iVar12 = iVar14 + iVar8 * 0x80;
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_10 + 0xcc),(MenuPlace *)(iVar14 + iVar8 * 0x80));
      iVar7 = iVar7 + 2;
    }
    for (uVar9 = 0; (int)uVar9 < 10; uVar9 = uVar9 + 1) {
      Create__8MenuTextFUcUc((MenuText *)(iVar14 + iVar7 * 0x80),1,2);
      *(u16 *)(iVar14 + iVar7 * 0x80 + 0x14) = 2;
      sVar5 = (short)((int)uVar9 >> 1);
      if ((uVar9 & 1) == 0) {
        *(u16 *)(iVar14 + iVar7 * 0x80 + 0x1c) = 0;
        sVar1 = sVar5;
        if ((int)uVar9 < 0) {
          sVar1 = (short)((int)(uVar9 + 1) >> 1);
        }
        *(short *)(iVar14 + iVar7 * 0x80 + 0x1e) = sVar1 + 6;
      }
      else {
        *(u16 *)(iVar14 + iVar7 * 0x80 + 0x1c) = 2;
        sVar1 = sVar5;
        if ((int)uVar9 < 0) {
          sVar1 = (short)((int)(uVar9 + 1) >> 1);
        }
        *(short *)(iVar14 + iVar7 * 0x80 + 0x1e) = sVar1 + 6;
      }
      *(u8 *)(iVar14 + iVar7 * 0x80 + 0x5a) = 1;
      *(u8 *)(iVar14 + iVar7 * 0x80 + 0x5b) = 0;
      iVar10 = iVar14 + iVar7 * 0x80;
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_10 + 0xcc),(MenuPlace *)(iVar14 + iVar7 * 0x80));
      iVar10 = iVar14 + iVar7 * 0x80;
      (**(code **)(*(int *)(iVar10 + 8) + 0x2c))(iVar10,0);
      iVar10 = iVar7 + 1;
      Create__8MenuTextFUcUc((MenuText *)(iVar14 + iVar10 * 0x80),1,2);
      *(u16 *)(iVar14 + iVar10 * 0x80 + 0x14) = 2;
      if ((uVar9 & 1) == 0) {
        *(u16 *)(iVar14 + iVar10 * 0x80 + 0x1c) = 1;
        if ((int)uVar9 < 0) {
          sVar5 = (short)((int)(uVar9 + 1) >> 1);
        }
        *(short *)(iVar14 + iVar10 * 0x80 + 0x1e) = sVar5 + 6;
      }
      else {
        *(u16 *)(iVar14 + iVar10 * 0x80 + 0x1c) = 3;
        if ((int)uVar9 < 0) {
          sVar5 = (short)((int)(uVar9 + 1) >> 1);
        }
        *(short *)(iVar14 + iVar10 * 0x80 + 0x1e) = sVar5 + 6;
      }
      *(u8 *)(iVar14 + iVar10 * 0x80 + 0x5a) = 1;
      *(u8 *)(iVar14 + iVar10 * 0x80 + 0x5b) = 0;
      iVar8 = iVar14 + iVar10 * 0x80;
      uVar4 = 0xfffffffffffffffe;
      *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
      AddPlace__10MenuWindowFP9MenuPlace
                ((MenuWindow *)(iStack_10 + 0xcc),(MenuPlace *)(iVar14 + iVar10 * 0x80));
      iVar10 = iVar14 + iVar10 * 0x80;
      (**(code **)(*(int *)(iVar10 + 8) + 0x2c))(iVar10,0,uVar4);
      iVar7 = iVar7 + 2;
    }
  }
  else {
    ClearImage__8FontDrawFv(param_1 + 0x8c);
  }
  iVar14 = (uint)*(ushort *)(iVar6 + 0x50c) * 0x18;
  if ((uint)*(ushort *)(iVar6 + 0x50c) * 3 != 0) {
    iVar14 = iVar14 + 0x25;
  }
  fStack_18 = 16.0;
  fStack_1c = (float)(iVar14 + 0x10);
  fStack_20 = (float)(iVar14 + 0xc1);
  fStack_24 = (float)*(int *)(iStack_10 + 0x78) - fStack_20 / 2.0;
  iVar14 = *(int *)(iStack_10 + 0x180);
  iVar7 = 0;
  if (*(short *)(iVar6 + 0x50c) == 0) {
    lVar13 = 0;
  }
  else {
    lVar13 = 0;
    while (lVar13 < *(short *)(iStack_10 + 0x194)) {
      iVar12 = (int)lVar13;
      SetMessage__8MenuTextFPcUiUcUc
                ((MenuText *)(iVar14 + iVar7 * 0x80),(void *)(iStack_10 + iVar12 * 0x20 + 0x198),0,0
                 ,1);
      (**(code **)(*(int *)(iVar14 + iVar7 * 0x80 + 8) + 0x24))
                ((float)*(int *)(iStack_10 + 0x74) - 168.0,
                 fStack_24 + fStack_18 + 32.0 + (float)(iVar12 * 0x18));
      iVar10 = iVar14 + iVar7 * 0x80;
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x8c,iVar14 + iVar7 * 0x80,1,0)
      ;
      iVar8 = iVar7 + 1;
      SetMessage__8MenuTextFPcUiUcUc
                ((MenuText *)(iVar14 + iVar8 * 0x80),(void *)(iStack_10 + iVar12 * 0x20 + 600),0,0,1
                );
      iVar10 = iVar14 + iVar8 * 0x80;
      *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe | 1;
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x8c,iVar14 + iVar8 * 0x80,1,0)
      ;
      fStack_28 = *(float *)(iVar14 + iVar8 * 0x80 + 0x2c);
      fStack_14 = fStack_28;
      (**(code **)(*(int *)(iVar14 + iVar8 * 0x80 + 8) + 0x24))
                (((float)*(int *)(iStack_10 + 0x74) + 168.0) - fStack_28,
                 fStack_24 + fStack_18 + 32.0 + (float)(iVar12 * 0x18));
      iVar7 = iVar7 + 2;
      lVar13 = (long)(iVar12 + 1);
    }
  }
  for (; lVar13 < 6; lVar13 = (long)((int)lVar13 + 1)) {
    iVar10 = iVar14 + iVar7 * 0x80;
    *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
    iVar10 = iVar14 + (iVar7 + 1) * 0x80;
    *(byte *)(iVar10 + 0x12) = *(byte *)(iVar10 + 0x12) & 0xfe;
    iVar7 = iVar7 + 2;
  }
  for (uVar9 = 0; (int)uVar9 < (int)(uint)*(byte *)(iVar6 + 0x16e); uVar9 = uVar9 + 1) {
    iVar10 = (int)uVar9 >> 1;
    if ((uVar9 & 1) == 0) {
      iVar8 = iVar10;
      if ((int)uVar9 < 0) {
        iVar8 = (int)(uVar9 + 1) >> 1;
      }
      (**(code **)(*(int *)(iVar14 + iVar7 * 0x80 + 8) + 0x24))
                ((float)*(int *)(iStack_10 + 0x74) - 136.0,
                 fStack_24 + fStack_1c + 60.0 + (float)(iVar8 * 0x16));
    }
    else {
      iVar8 = iVar10;
      if ((int)uVar9 < 0) {
        iVar8 = (int)(uVar9 + 1) >> 1;
      }
      (**(code **)(*(int *)(iVar14 + iVar7 * 0x80 + 8) + 0x24))
                (((float)*(int *)(iStack_10 + 0x74) - 136.0) + 168.0,
                 fStack_24 + fStack_1c + 60.0 + (float)(iVar8 * 0x16));
    }
    if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 100) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (9,*(u16 *)(iVar11 + uVar9 * 2 + 4),0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 200) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (6,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 100,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 300) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (7,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 200,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 400) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (8,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 300,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 500) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (0xd,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 400,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 600) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (0x11,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 500,0xffffffffffffffff)
      ;
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 700) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (0xb,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 600,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 800) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (0x10,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 700,0xffffffffffffffff)
      ;
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    else if ((899 < *(ushort *)(iVar11 + uVar9 * 2 + 4)) &&
            (*(ushort *)(iVar11 + uVar9 * 2 + 4) < 1000)) {
      pvVar3 = (void *)GetRegDat__9RegDatApiFiii
                                 (10,*(ushort *)(iVar11 + uVar9 * 2 + 4) - 900,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),pvVar3,0,0,1);
    }
    iVar8 = iVar14 + iVar7 * 0x80;
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe | 1;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x8c,iVar14 + iVar7 * 0x80,1,0);
    iVar8 = iVar7 + 1;
    sprintf(acStack_50,(char *)&_6697,(ulong)*(byte *)(iVar11 + uVar9 + 0xc4));
    SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar8 * 0x80),acStack_50,0,0,1);
    iVar12 = iVar14 + iVar8 * 0x80;
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe | 1;
    uVar4 = OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_
                      (iStack_10 + 0x8c,iVar14 + iVar8 * 0x80,0,0);
    fStack_2c = *(float *)(iVar14 + iVar8 * 0x80 + 0x2c);
    fStack_14 = fStack_2c;
    if ((uVar9 & 1) == 0) {
      iVar12 = 2;
      if ((int)uVar9 < 0) {
        iVar12 = uVar9 + 1;
        iVar10 = iVar12 >> 1;
      }
      iVar8 = iVar14 + iVar8 * 0x80;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))
                ((((float)*(int *)(iStack_10 + 0x74) - 136.0) + 152.0) - fStack_2c,
                 fStack_24 + fStack_1c + 60.0 + (float)(iVar10 * 0x16),iVar8,iVar12);
    }
    else {
      if ((int)uVar9 < 0) {
        iVar10 = (int)(uVar9 + 1) >> 1;
      }
      iVar8 = iVar14 + iVar8 * 0x80;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))
                ((((float)*(int *)(iStack_10 + 0x74) - 136.0) + 320.0) - fStack_2c,
                 fStack_24 + fStack_1c + 60.0 + (float)(iVar10 * 0x16),iVar8,uVar4);
    }
    iVar7 = iVar7 + 2;
  }
  if (*(char *)(iVar6 + 0x16e) == '\0') {
    (**(code **)(*(int *)(iVar14 + iVar7 * 0x80 + 8) + 0x24))
              ((float)*(int *)(iStack_10 + 0x74) - 136.0,fStack_24 + fStack_1c + 60.0 + 0.0);
    SetMessage__8MenuTextFPcUiUcUc((MenuText *)(iVar14 + iVar7 * 0x80),*(void **)BtlMes,0,0,1);
    iVar6 = iVar14 + iVar7 * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x8c,iVar14 + iVar7 * 0x80,1,0);
    iVar6 = iVar14 + (iVar7 + 1) * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar7 = iVar7 + 2;
    uVar9 = 1;
  }
  for (; (int)uVar9 < 10; uVar9 = uVar9 + 1) {
    iVar6 = iVar14 + iVar7 * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar6 = iVar14 + (iVar7 + 1) * 0x80;
    *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe;
    iVar7 = iVar7 + 2;
  }
  return;
}

/* ---- 0x003717e0 size 0x44  BtlBonus::getPacket(v)
 *      mangled: getPacket__8BtlBonusFv */
u32 getPacket__8BtlBonusFv(int param_1)

{
  MakePacket__8BtlBonusFv(param_1);
  return *(u32 *)(param_1 + (*(byte *)(param_1 + 0x38) & 1) * 4 + 0x18);
}

/* ---- 0x00371830 size 0x8  BtlBonus::@24@getPacket(v)
 *      mangled: @24@getPacket__8BtlBonusFv */
u32 _24_getPacket__8BtlBonusFv(int param_1)

{
  MakePacket__8BtlBonusFv(param_1 + -0x18);
  return *(u32 *)(param_1 + -0x18 + (*(byte *)(param_1 + 0x20) & 1) * 4 + 0x18);
}

/* ---- 0x00371840 size 0x8  BtlBonus::@24@__dt(v)
 *      mangled: @24@__dt__8BtlBonusFv */
int * _24___dt__8BtlBonusFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = (int)__vt__8BtlBonus;
    param_1[4] = 0x406e10;
    param_1[7] = 0x406e20;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x1a) << 0x3e) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0x1d));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x1a) << 0x3c) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0x2d));
    }
    if (((ulong)*(ushort *)(param_1 + 0x1a) & 0xfff) >> 4 != 0) {
      __destroy_new_array(param_1[0x5a],0x273e20);
    }
    if (param_1[0x5c] != 0) {
      __destroy_new_array(param_1[0x5c],0x2661a0);
    }
    if (param_1[0x5b] != 0) {
      __destroy_new_array(param_1[0x5b],0x277890);
    }
    if (param_1[0x5d] != 0) {
      __destroy_new_array(param_1[0x5d],0x2766d0);
    }
    if (param_1[0x5e] != 0) {
      __destroy_new_array(param_1[0x5e],0x28d070);
    }
    ourBtlBonus__8BtlBonus = 0;
    if (piVar1 != (int *)0xffffff80) {
      __dt__10MenuWindowFv((MenuWindow *)(param_1 + 0x2d));
      __dt__8FontDrawFv(param_1 + 0x1d,0xffffffffffffffff);
    }
    if (piVar1 != (int *)0xffffffd4) {
      param_1[7] = (int)__vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1,0);
    __dt__7CPolObjFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

/* ---- 0x00371850 size 0x8  BtlBonus::@44@__dt(v)
 *      mangled: @44@__dt__8BtlBonusFv */
int _44___dt__8BtlBonusFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -0x18) = __vt__8BtlBonus;
    *(u32 *)(param_1 + -4) = 0x406e10;
    *(u32 *)(param_1 + 8) = 0x406e20;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x10));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x54) << 0x3e) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0x60));
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x54) << 0x3c) < 0) {
      Release__7MenuObjFv((MenuObj *)(param_1 + 0xa0));
    }
    if (((ulong)*(ushort *)(param_1 + 0x54) & 0xfff) >> 4 != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x154),0x273e20);
    }
    if (*(int *)(param_1 + 0x15c) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x15c),0x2661a0);
    }
    if (*(int *)(param_1 + 0x158) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x158),0x277890);
    }
    if (*(int *)(param_1 + 0x160) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x160),0x2766d0);
    }
    if (*(int *)(param_1 + 0x164) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x164),0x28d070);
    }
    ourBtlBonus__8BtlBonus = 0;
    if (iVar1 != -0x80) {
      __dt__10MenuWindowFv((MenuWindow *)(param_1 + 0xa0));
      __dt__8FontDrawFv(param_1 + 0x60,0xffffffffffffffff);
    }
    if (iVar1 != -0x2c) {
      *(u8 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1 + -0x14,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

