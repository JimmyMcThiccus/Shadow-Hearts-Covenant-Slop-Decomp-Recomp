/*
 * BtlFader.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 14 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00371870 size 0x280  BtlFader::BtlFader(v)
 *      mangled: __ct__8BtlFaderFv */
int __ct__8BtlFaderFv(int param_1)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  VIF1Prim *prim;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv((VIF1Prim *)(param_1 + 0x18));
  *(u32 *)(param_1 + 0x2c) = 0;
  *(u32 *)(param_1 + 0x30) = 0;
  *(u8 **)(param_1 + 0x34) = __vt__17DelayDeleteObject;
  *(u8 **)(param_1 + 0x14) = __vt__8BtlFader;
  *(u32 *)(param_1 + 0x28) = 0x406e50;
  *(u32 *)(param_1 + 0x34) = 0x406e60;
  ourBF__8BtlFader = param_1;
  *(u32 *)(param_1 + 0x38) = 0;
  uVar3 = GetTimer__7SysToolFv();
  *(u32 *)(param_1 + 0x44) = uVar3;
  *(u16 *)(param_1 + 0x3c) = 0;
  *(u8 *)(param_1 + 0x40) = 0;
  *(u8 *)(param_1 + 0x41) = 0;
  *(u8 *)(param_1 + 0x42) = 0;
  *(u8 *)(param_1 + 0x43) = 0;
  *(u32 *)(param_1 + 0x58) = 0xd;
  uVar3 = __nwa__FUi(0x80);
  *(u32 *)(param_1 + 0x18) = uVar3;
  uVar3 = __nwa__FUi(0x80);
  *(u32 *)(param_1 + 0x1c) = uVar3;
  puVar1 = *(u32 **)(param_1 + 0x18);
  puVar2 = *(u32 **)(param_1 + 0x1c);
  *puVar2 = 0x60000006;
  *puVar1 = 0x60000006;
  puVar2[1] = 0;
  puVar1[1] = 0;
  puVar2[2] = &DAT_11000000;
  puVar1[2] = &DAT_11000000;
  puVar2[3] = 0x50000006;
  puVar1[3] = 0x50000006;
  *(u64 *)(puVar2 + 4) = 0x2000000000000001;
  *(u64 *)(puVar1 + 4) = 0x2000000000000001;
  *(u64 *)(puVar2 + 6) = 0xee;
  *(u64 *)(puVar1 + 6) = 0xee;
  *(u64 *)(puVar2 + 8) = 0x3001;
  *(u64 *)(puVar1 + 8) = 0x3001;
  *(u64 *)(puVar2 + 10) = 0x47;
  *(u64 *)(puVar1 + 10) = 0x47;
  *(u64 *)(puVar2 + 0xc) = 0x44;
  *(u64 *)(puVar1 + 0xc) = 0x44;
  *(u64 *)(param_1 + 0x50) = 0x44;
  *(u64 *)(puVar2 + 0xe) = 0x42;
  *(u64 *)(puVar1 + 0xe) = 0x42;
  *(u64 *)(puVar2 + 0x10) = 0x4400000000008001;
  *(u64 *)(puVar1 + 0x10) = 0x4400000000008001;
  *(u64 *)(puVar2 + 0x12) = 0x4c10;
  *(u64 *)(puVar1 + 0x12) = 0x4c10;
  *(u64 *)(puVar2 + 0x14) = 0x46;
  *(u64 *)(puVar1 + 0x14) = 0x46;
  *(u64 *)(puVar2 + 0x18) = 0x71006f00;
  *(u64 *)(puVar1 + 0x18) = 0x71006f00;
  *(u64 *)(puVar2 + 0x1a) = 0x8f009100;
  *(u64 *)(puVar1 + 0x1a) = 0x8f009100;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  prim = (VIF1Prim *)0x0;
  if (param_1 != 0) {
    prim = (VIF1Prim *)(param_1 + 0x18);
  }
  AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,*(int *)(param_1 + 0x58),prim);
  return param_1;
}

/* ---- 0x00371af0 size 0xf4  BtlFader::~BtlFader(v)
 *      mangled: __dt__8BtlFaderFv */
int __dt__8BtlFaderFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__8BtlFader;
    *(u32 *)(param_1 + 0x28) = 0x406e50;
    *(u32 *)(param_1 + 0x34) = 0x406e60;
    __dla__FPv(*(u32 *)(param_1 + 0x18));
    __dla__FPv(*(u32 *)(param_1 + 0x1c));
    ourBF__8BtlFader = 0;
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

/* ---- 0x00371bf0 size 0x84  BtlFader::Destruct(v)
 *      mangled: Destruct__8BtlFaderFv */
void Destruct__8BtlFaderFv(void)

{
  VIF1Prim *prim;
  
  if (ourBF__8BtlFader != 0) {
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,ourBF__8BtlFader);
    prim = (VIF1Prim *)0x0;
    if (ourBF__8BtlFader != 0) {
      prim = (VIF1Prim *)(ourBF__8BtlFader + 0x18);
    }
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    (**(code **)(*(int *)(ourBF__8BtlFader + 0x34) + 0xc))();
    ourBF__8BtlFader = 0;
  }
  return;
}

/* ---- 0x00371c80 size 0x2e0  BtlFader::Polling(v)
 *      mangled: Polling__8BtlFaderFv */
u64 Polling__8BtlFaderFv(int param_1)

{
  short sVar1;
  int iVar2;
  u8 uVar3;
  float fVar4;
  float fStack_18;
  
  iVar2 = GetTimer__7SysToolFv();
  fVar4 = (float)(uint)(iVar2 - *(int *)(param_1 + 0x44)) * 0.001;
  *(int *)(param_1 + 0x44) = iVar2;
  sVar1 = *(short *)(param_1 + 0x3c);
  if (sVar1 == 3) {
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fVar4;
    fStack_18 = (*(float *)(param_1 + 0x48) / *(float *)(param_1 + 0x4c)) * 128.0;
    if (fStack_18 < 0.0) {
      fStack_18 = 0.0;
    }
    if (128.0 <= fStack_18) {
      fStack_18 = 128.0;
      *(u16 *)(param_1 + 0x3c) = 1;
    }
    if (fStack_18 < 2.1474836e+09) {
      uVar3 = (u8)(int)fStack_18;
    }
    else {
      uVar3 = (u8)(int)(fStack_18 - 2.1474836e+09);
    }
    *(u8 *)(param_1 + 0x43) = uVar3;
  }
  else if (sVar1 == 2) {
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fVar4;
    fStack_18 = 128.0 - (*(float *)(param_1 + 0x48) / *(float *)(param_1 + 0x4c)) * 128.0;
    if (fStack_18 < 0.0) {
      fStack_18 = 0.0;
      *(u16 *)(param_1 + 0x3c) = 0;
    }
    if (128.0 <= fStack_18) {
      fStack_18 = 128.0;
    }
    if (fStack_18 < 2.1474836e+09) {
      uVar3 = (u8)(int)fStack_18;
    }
    else {
      uVar3 = (u8)(int)(fStack_18 - 2.1474836e+09);
    }
    *(u8 *)(param_1 + 0x43) = uVar3;
  }
  else if (sVar1 == 1) {
    *(u8 *)(param_1 + 0x43) = 0x80;
  }
  else if (sVar1 == 0) {
    *(u8 *)(param_1 + 0x43) = 0;
  }
  return 0;
}

/* ---- 0x00371f60 size 0xcc  BtlFader::MakePacket(v)
 *      mangled: MakePacket__8BtlFaderFv */
void MakePacket__8BtlFaderFv(int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = (*(byte *)(param_1 + 0x38) & 1) == 0;
  iVar2 = *(int *)(param_1 + (uint)bVar1 * 4 + 0x18);
  *(u64 *)(iVar2 + 0x30) = *(u64 *)(param_1 + 0x50);
  *(ulong *)(iVar2 + 0x58) = (ulong)*(uint *)(param_1 + 0x40);
  *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfe | bVar1;
  return;
}

/* ---- 0x00372030 size 0x80  BtlFader::SetMode(sf7_rgba32)
 *      mangled: SetMode__8BtlFaderFsf7_rgba32 */
void SetMode__8BtlFaderFsf7_rgba32(u32 param_1,u16 param_2,u32 param_3)

{
  long lVar1;
  
  if ((ourBF__8BtlFader == 0) && (lVar1 = __nw__FUi(0x60), lVar1 != 0)) {
    __ct__8BtlFaderFv(lVar1);
  }
  SetColor__8BtlFaderF7_rgba32(param_3);
  SetMode2__8BtlFaderFsf(param_1,param_2);
  return;
}

/* ---- 0x003720b0 size 0x1dc  BtlFader::SetMode2(sf)
 *      mangled: SetMode2__8BtlFaderFsf */
void SetMode2__8BtlFaderFsf(u32 param_1,u16 param_2)

{
  short sVar1;
  long lVar2;
  
  if ((ourBF__8BtlFader == 0) && (lVar2 = __nw__FUi(0x60), lVar2 != 0)) {
    __ct__8BtlFaderFv(lVar2);
  }
  *(u16 *)(ourBF__8BtlFader + 0x3c) = param_2;
  *(u16 *)(ourBF__8BtlFader + 0x3e) = 0;
  *(u32 *)(ourBF__8BtlFader + 0x48) = 0;
  *(u32 *)(ourBF__8BtlFader + 0x4c) = param_1;
  sVar1 = *(short *)(ourBF__8BtlFader + 0x3c);
  if (sVar1 == 3) {
    *(float *)(ourBF__8BtlFader + 0x48) =
         ((float)*(byte *)(ourBF__8BtlFader + 0x43) * *(float *)(ourBF__8BtlFader + 0x4c)) / 128.0;
  }
  else if (sVar1 == 2) {
    *(float *)(ourBF__8BtlFader + 0x48) =
         ((128.0 - (float)*(byte *)(ourBF__8BtlFader + 0x43)) * *(float *)(ourBF__8BtlFader + 0x4c))
         / 128.0;
  }
  else if (sVar1 == 1) {
    *(u8 *)(ourBF__8BtlFader + 0x43) = 0x80;
  }
  else if (sVar1 == 0) {
    *(u8 *)(ourBF__8BtlFader + 0x43) = 0;
  }
  return;
}

/* ---- 0x00372290 size 0x68  BtlFader::SetAlphaMode(Ul)
 *      mangled: SetAlphaMode__8BtlFaderFUl */
void SetAlphaMode__8BtlFaderFUl(u64 param_1)

{
  long lVar1;
  
  if ((ourBF__8BtlFader == 0) && (lVar1 = __nw__FUi(0x60), lVar1 != 0)) {
    __ct__8BtlFaderFv(lVar1);
  }
  *(u64 *)(ourBF__8BtlFader + 0x50) = param_1;
  return;
}

/* ---- 0x00372300 size 0x30  BtlFader::GetFaderMode(v)
 *      mangled: GetFaderMode__8BtlFaderFv */
u16 GetFaderMode__8BtlFaderFv(void)

{
  u16 uVar1;
  
  if (ourBF__8BtlFader == 0) {
    uVar1 = 0xffff;
  }
  else {
    uVar1 = *(u16 *)(ourBF__8BtlFader + 0x3c);
  }
  return uVar1;
}

/* ---- 0x00372330 size 0x44  BtlFader::SetColor(7_rgba32)
 *      mangled: SetColor__8BtlFaderF7_rgba32 */
void SetColor__8BtlFaderF7_rgba32(u32 param_1)

{
  u8 uStack_10;
  u8 uStack_f;
  u8 uStack_e;
  
  if (ourBF__8BtlFader != 0) {
    uStack_10 = (u8)param_1;
    *(u8 *)(ourBF__8BtlFader + 0x40) = uStack_10;
    uStack_f = (u8)((uint)param_1 >> 8);
    *(u8 *)(ourBF__8BtlFader + 0x41) = uStack_f;
    uStack_e = (u8)((uint)param_1 >> 0x10);
    *(u8 *)(ourBF__8BtlFader + 0x42) = uStack_e;
  }
  return;
}

/* ---- 0x00372380 size 0x44  BtlFader::getPacket(v)
 *      mangled: getPacket__8BtlFaderFv */
u32 getPacket__8BtlFaderFv(int param_1)

{
  MakePacket__8BtlFaderFv(param_1);
  return *(u32 *)(param_1 + (*(byte *)(param_1 + 0x38) & 1) * 4 + 0x18);
}

/* ---- 0x003723d0 size 0x8  BtlFader::@24@getPacket(v)
 *      mangled: @24@getPacket__8BtlFaderFv */
u32 _24_getPacket__8BtlFaderFv(int param_1)

{
  MakePacket__8BtlFaderFv(param_1 + -0x18);
  return *(u32 *)(param_1 + -0x18 + (*(byte *)(param_1 + 0x20) & 1) * 4 + 0x18);
}

/* ---- 0x003723e0 size 0x8  BtlFader::@24@__dt(v)
 *      mangled: @24@__dt__8BtlFaderFv */
u32 * _24___dt__8BtlFaderFv(u32 *param_1,short param_2)

{
  u32 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (u32 *)0x0) {
    param_1[-1] = __vt__8BtlFader;
    param_1[4] = 0x406e50;
    param_1[7] = 0x406e60;
    __dla__FPv(*param_1);
    __dla__FPv(param_1[1]);
    ourBF__8BtlFader = 0;
    if (puVar1 != (u32 *)0xffffffd4) {
      param_1[7] = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1,0);
    __dt__7CPolObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* ---- 0x003723f0 size 0x8  BtlFader::@44@__dt(v)
 *      mangled: @44@__dt__8BtlFaderFv */
int _44___dt__8BtlFaderFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -0x18) = __vt__8BtlFader;
    *(u32 *)(param_1 + -4) = 0x406e50;
    *(u32 *)(param_1 + 8) = 0x406e60;
    __dla__FPv(*(u32 *)(param_1 + -0x14));
    __dla__FPv(*(u32 *)(param_1 + -0x10));
    ourBF__8BtlFader = 0;
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

