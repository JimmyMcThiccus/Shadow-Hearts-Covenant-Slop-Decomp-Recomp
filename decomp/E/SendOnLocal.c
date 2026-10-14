/*
 * SendOnLocal.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 12 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00277820 size 0x70  SendOnLocal::SendOnLocal(v)
 *      mangled: __ct__11SendOnLocalFv */
MenuObj * __ct__11SendOnLocalFv(MenuObj *param_1)

{
  __ct__7MenuObjFv(param_1);
  __ct__10MenuPacketFv((MenuPacket *)(param_1 + 1));
  param_1->pVptr = __vt__11SendOnLocal;
  param_1[1].pLink_prev = (void *)0x405284;
  (**(code **)((int)param_1->pVptr + 0x20))();
  return param_1;
}

/* ---- 0x00277890 size 0xac  SendOnLocal::~SendOnLocal(v)
 *      mangled: __dt__11SendOnLocalFv */
MenuObj * __dt__11SendOnLocalFv(MenuObj *param_1,short param_2)

{
  if (param_1 != (MenuObj *)0x0) {
    param_1->pVptr = __vt__11SendOnLocal;
    param_1[1].pLink_prev = (void *)0x405284;
    (**(code **)((int)param_1->pVptr + 0x1c))();
    __dt__10MenuPacketFv((MenuPacket *)(param_1 + 1));
    __dt__7MenuObjFv(param_1);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00277940 size 0x190  SendOnLocal::Create(P12RasterPacketP10ClutRasterbi)
 *      mangled: Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi */
u32
Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
          (int param_1,u32 param_2,u32 param_3,byte param_4,uint param_5)

{
  ulong uVar1;
  
  if ((*(byte *)(param_1 + 0x26) & 1) == 0) {
    if (param_4 == 0) {
      CreatePacket__10MenuPacketFUs((MenuPacket *)(param_1 + 0x18),3);
    }
    else {
      CreatePacket__10MenuPacketFUs((MenuPacket *)(param_1 + 0x18),8);
    }
  }
  else if (((ulong)*(byte *)(param_1 + 0x26) & 0x7f) >> 6 != (ulong)param_4) {
    return 0;
  }
  uVar1 = (ulong)*(byte *)(param_1 + 0x26) & 0xffffffffffffffbf | (long)(int)((param_4 & 1) << 6);
  *(char *)(param_1 + 0x26) = (char)uVar1;
  if (((long)(uVar1 << 0x39) < 0) && (-1 < (int)param_5)) {
    *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xdf | 0x20;
    *(ushort *)(param_1 + 0x12) =
         *(ushort *)(param_1 + 0x12) & 0xfc3f | (ushort)((param_5 & 0xf) << 6);
  }
  *(u32 *)(param_1 + 0x28) = param_2;
  *(u32 *)(param_1 + 0x2c) = param_3;
  *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) | 0x3f;
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x3f;
  return 1;
}

/* ---- 0x00277ad0 size 0x164  SendOnLocal::Create(P4_QWDUl)
 *      mangled: Create__11SendOnLocalFP4_QWDUl */
void * Create__11SendOnLocalFP4_QWDUl(int param_1,u32 param_2,u64 param_3)

{
  u32 *puVar1;
  void *pvVar2;
  int iVar3;
  
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1,0,0,1,0xffffffffffffffff);
  *(u8 *)(param_1 + 0x10) = 0;
  *(u8 *)(param_1 + 0x11) = 0;
  iVar3 = param_1 + (m_Env__8VIF1Prim & 1);
  *(byte *)(iVar3 + 0x10) = *(byte *)(iVar3 + 0x10) & 0xfd | 2;
  (**(code **)(*(int *)(param_1 + 8) + 0x14))(param_1,0,0,0);
  puVar1 = *(u32 **)(param_1 + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
  *puVar1 = 0x50000000;
  puVar1[1] = param_2;
  puVar1[4] = 0x10000000;
  SetTextureRegister__11SendOnLocalFUlUl(param_1,6,param_3);
  pvVar2 = memcpy(*(void **)(param_1 + (m_Env__8VIF1Prim & 1 ^ 1) * 4 + 0x1c),
                  *(void **)(param_1 + (m_Env__8VIF1Prim & 1) * 4 + 0x1c),
                  (long)(int)((*(ushort *)(param_1 + 0x24) - 1) * 0x10));
  *(ushort *)(param_1 + 0x26) = *(ushort *)(param_1 + 0x26) & 0xf87f | 0x80;
  return pvVar2;
}

/* ---- 0x00277c40 size 0x8c  SendOnLocal::UpdatePacket(v)
 *      mangled: UpdatePacket__11SendOnLocalFv */
void * UpdatePacket__11SendOnLocalFv(int param_1)

{
  void *pvVar1;
  
  (**(code **)(*(int *)(param_1 + 8) + 0x14))(param_1,0,0,0);
  pvVar1 = memcpy(*(void **)(param_1 + (m_Env__8VIF1Prim & 1 ^ 1) * 4 + 0x1c),
                  *(void **)(param_1 + (m_Env__8VIF1Prim & 1) * 4 + 0x1c),
                  (long)(int)((*(ushort *)(param_1 + 0x24) - 1) * 0x10));
  return pvVar1;
}

/* ---- 0x00277cd0 size 0x6c  SendOnLocal::SetTextureRegister(UlUl)
 *      mangled: SetTextureRegister__11SendOnLocalFUlUl */
void SetTextureRegister__11SendOnLocalFUlUl(int param_1,u64 param_2,u64 param_3)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x26) << 0x39) < 0) {
    *(u64 *)(*(int *)(param_1 + 0x20) + 0x58) = param_2;
    *(u64 *)(*(int *)(param_1 + 0x1c) + 0x58) = param_2;
    *(u64 *)(*(int *)(param_1 + 0x20) + 0x50) = param_3;
    *(u64 *)(*(int *)(param_1 + 0x1c) + 0x50) = param_3;
  }
  return;
}

/* ---- 0x00277d40 size 0x100  SendOnLocal::GetTex0(v)
 *      mangled: GetTex0__11SendOnLocalFv */
ulong GetTex0__11SendOnLocalFv(int param_1)

{
  ulong uVar1;
  ulong uVar2;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    uVar1 = *(ulong *)(*(int *)(param_1 + 0x1c) + 0x50);
  }
  else if (*(int *)(param_1 + 0x2c) == 0) {
    uVar1 = **(ulong **)(param_1 + 0x28) & 0x7ffffffff;
  }
  else {
    uVar2 = **(ulong **)(param_1 + 0x28);
    uVar1 = GetClutFlag__10ClutRasterFUcUc(*(u32 *)(param_1 + 0x2c),0,1);
    uVar1 = uVar2 & 0x7ffffffff | uVar1;
  }
  return uVar1;
}

/* ---- 0x00277e40 size 0x2d4  SendOnLocal::Update(iiUs)
 *      mangled: Update__11SendOnLocalFiiUs */
void Update__11SendOnLocalFiiUs(int param_1)

{
  u32 *puVar1;
  u64 uVar2;
  ulong uVar3;
  byte *pbVar4;
  ulong uVar5;
  
  if (((ulong)*(ushort *)(param_1 + 0x26) & 0x7ff) >> 7 == 0) {
    puVar1 = *(u32 **)(param_1 + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
    pbVar4 = (byte *)(param_1 + (m_Env__8VIF1Prim & 1) + 0x10);
    if ((long)((ulong)*pbVar4 << 0x3d) < 0) {
      *puVar1 = 0x50000000;
      puVar1[1] = *(u32 *)(*(int *)(param_1 + 0x28) + 0x1c);
      if (*(int *)(param_1 + 0x2c) == 0) {
        puVar1[4] = 0x10000000;
        puVar1[5] = 0;
      }
      else {
        puVar1[4] = 0x50000000;
        puVar1[5] = *(u32 *)(*(int *)(param_1 + 0x2c) + 0x24);
      }
    }
    if (((long)((ulong)*pbVar4 << 0x3e) < 0) &&
       ((long)((ulong)*(byte *)(param_1 + 0x26) << 0x39) < 0)) {
      puVar1[8] = &DAT_10000004;
      puVar1[10] = 0x13000000;
      puVar1[0xb] = 0x50000004;
      *(u64 *)(puVar1 + 0xc) = 0x3000000000008001;
      *(u64 *)(puVar1 + 0xe) = 0xeee;
      *(u64 *)(puVar1 + 0x12) = 0x3f;
      if ((long)((ulong)*(byte *)(param_1 + 0x12) << 0x3a) < 0) {
        uVar2 = GetTex2__10ClutRasterCF6GS_PSMUcUc(*(u32 *)(param_1 + 0x2c),0x1b,0,1);
        *(u64 *)(puVar1 + 0x14) = uVar2;
        *(u64 *)(puVar1 + 0x16) = 7;
        uVar5 = **(ulong **)(param_1 + 0x28);
        uVar3 = GetClutFlag__10ClutRasterFUcUc
                          (*(u32 *)(param_1 + 0x2c),
                           ((ulong)*(ushort *)(param_1 + 0x12) & 0x3ff) >> 6,0);
        *(ulong *)(puVar1 + 0x18) = uVar5 & 0x7ffffffff | uVar3;
        *(u64 *)(puVar1 + 0x1a) = 6;
      }
      else {
        uVar2 = GetTex0__11SendOnLocalFv(param_1);
        *(u64 *)(puVar1 + 0x14) = uVar2;
        *(u64 *)(puVar1 + 0x16) = 6;
        if ((long)((ulong)*(byte *)(param_1 + 0x13) << 0x3d) < 0) {
          *(u64 *)(puVar1 + 0x18) = 0x48;
        }
        else {
          *(u64 *)(puVar1 + 0x18) = 0x44;
        }
        *(u64 *)(puVar1 + 0x1a) = 0x42;
      }
    }
    *pbVar4 = *pbVar4 & 0x80;
  }
  return;
}

/* ---- 0x00278120 size 0x34  SendOnLocal::Connect(P4_QWD)
 *      mangled: Connect__11SendOnLocalFP4_QWD */
int Connect__11SendOnLocalFP4_QWD(int param_1,void *param_2)

{
  int iVar1;
  
  iVar1 = ConnectPacket__10MenuPacketFP4_QWD((MenuPacket *)(param_1 + 0x18),param_2);
  return iVar1;
}

/* ---- 0x00278160 size 0x2c  SendOnLocal::Destroy(v)
 *      mangled: Destroy__11SendOnLocalFv */
void Destroy__11SendOnLocalFv(int param_1)

{
  DestroyPacket__10MenuPacketFv((MenuPacket *)(param_1 + 0x18));
  return;
}

/* ---- 0x00278190 size 0x48  SendOnLocal::Clear(v)
 *      mangled: Clear__11SendOnLocalFv */
void Clear__11SendOnLocalFv(MenuObj *param_1)

{
  Clear__7MenuObjFv(param_1);
  ClearPacket__10MenuPacketFv((MenuPacket *)(param_1 + 1));
  param_1[1].bDirty0 = 0;
  param_1[1].bDirty1 = 0;
  param_1[1].bFlags = 0;
  param_1[1].field_0x13 = 0;
  param_1[1].nPriority = 0;
  param_1[1].nId = 0;
  return;
}

/* ---- 0x002781e0 size 0x8  SendOnLocal::@24@__dt(v)
 *      mangled: @24@__dt__11SendOnLocalFv */
void ** _24___dt__11SendOnLocalFv(MenuPacket *param_1,short param_2)

{
  void **this;
  
  this = &param_1[-2].pPkt1;
  if (this != (void **)0x0) {
    param_1[-1].pVptr = __vt__11SendOnLocal;
    param_1->pVptr = (void *)0x405284;
    (**(code **)((int)param_1[-1].pVptr + 0x1c))();
    __dt__10MenuPacketFv(param_1);
    __dt__7MenuObjFv((MenuObj *)this);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

