/*
 * KeyWait.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 9 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x002808a0 size 0x80  KeyWait::KeyWait(v)
 *      mangled: __ct__7KeyWaitFv */
MenuObj * __ct__7KeyWaitFv(MenuObj *param_1)

{
  __ct__7MenuObjFv(param_1);
  param_1->pVptr = __vt__7KeyWait;
  __ct__11SendOnLocalFv(&param_1[1].pNext);
  __ct__10MenuSpriteFv((MenuSprite *)&param_1[3].pNext);
  __ct__12MenuRegisterFv(&param_1[7].pNext);
  (**(code **)((int)param_1->pVptr + 0x20))();
  return param_1;
}

/* ---- 0x00280920 size 0xc4  KeyWait::~KeyWait(v)
 *      mangled: __dt__7KeyWaitFv */
MenuObj * __dt__7KeyWaitFv(MenuObj *param_1,short param_2)

{
  if (param_1 != (MenuObj *)0x0) {
    param_1->pVptr = __vt__7KeyWait;
    (**(code **)((int)param_1->pVptr + 0x1c))();
    __dt__12MenuRegisterFv(&param_1[7].pNext,0xffffffffffffffff);
    __dt__10MenuSpriteFv((MenuSprite *)&param_1[3].pNext);
    __dt__11SendOnLocalFv(&param_1[1].pNext,0xffffffffffffffff);
    __dt__7MenuObjFv(param_1);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x002809f0 size 0xfc  KeyWait::Create(v)
 *      mangled: Create__7KeyWaitFv */
void Create__7KeyWaitFv(int param_1)

{
  SetData__9MenuSceneFUsP10MenuSprite
            ((MenuScene *)&sm_common__7MenuObj,0x1d,(MenuSprite *)(param_1 + 0x54));
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (param_1 + 0x24,0x421970,DAT_0042196c,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(param_1 + 0x24);
  *(int *)(param_1 + 0xb0) = param_1 + 0x24;
  *(byte *)(param_1 + 0x66) = *(byte *)(param_1 + 0x66) & 0xdf;
  CreatePacket__10MenuPacketFUs((MenuPacket *)(param_1 + 0xcc),4);
  SetRegister__12MenuRegisterFiUlUl(param_1 + 0xb4,0,0x42,0x44);
  *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) | 0x3f;
  *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x3f;
  return;
}

/* ---- 0x00280af0 size 0xf8  KeyWait::SetPosition(i)
 *      mangled: SetPosition__7KeyWaitFi */
void SetPosition__7KeyWaitFi(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  if (param_2 == 1) {
    fVar1 = *(float *)(param_1 + 0x84);
    fVar2 = *(float *)(*(int *)(param_1 + 0x18) + 0x70);
    fVar3 = fVar2;
    GetTargetY__10MenuWindowCFv(*(MenuWindow **)(param_1 + 0x18));
    fVar4 = *(float *)(param_1 + 0x80);
    fVar5 = *(float *)(*(int *)(param_1 + 0x18) + 0x6c);
    fVar6 = fVar5;
    GetTargetX__10MenuWindowCFv(*(MenuWindow **)(param_1 + 0x18));
    (**(code **)(*(int *)(param_1 + 0x5c) + 0x24))((fVar5 - fVar4) - fVar6,(fVar2 - fVar1) - fVar3);
  }
  return;
}

/* ---- 0x00280bf0 size 0x1c0  KeyWait::Polling(v)
 *      mangled: Polling__7KeyWaitFv */
void Polling__7KeyWaitFv(int param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = *(short *)(param_1 + 0x1e);
  if (sVar1 == 10) {
    *(u16 *)(param_1 + 0x1e) = 0xb;
  }
  else if (sVar1 == 0xc) {
    iVar2 = GetActive__4CPadFi(((ulong)*(byte *)(param_1 + 0x22) & 0x3f) >> 5);
    if ((*(ushort *)(param_1 + 0x20) &
        *(ushort *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6e)) != 0) {
      *(u16 *)(param_1 + 0x1e) = 0xd;
    }
  }
  else if ((sVar1 == 0xb) &&
          (iVar2 = GetActive__4CPadFi(((ulong)*(byte *)(param_1 + 0x22) & 0x3f) >> 5),
          (*(ushort *)(param_1 + 0x20) &
          *(ushort *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6c)) != 0)) {
    *(u16 *)(param_1 + 0x1e) = 0xc;
  }
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + (short)sm_iPassTime__7MenuObj;
  if (0x3c0 < *(short *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -0x780;
  }
  return;
}

/* ---- 0x00280db0 size 0x17c  KeyWait::Update(iiUs)
 *      mangled: Update__7KeyWaitFiiUs */
void Update__7KeyWaitFiiUs(int param_1,u32 param_2,u32 param_3,u16 param_4)

{
  byte bVar1;
  short sVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + (m_Env__8VIF1Prim & 1) + 0x10);
  sVar2 = *(short *)(param_1 + 0x1c) / 10;
  if (sVar2 < 0) {
    sVar2 = -sVar2;
  }
  (**(code **)(*(int *)(param_1 + 0x5c) + 0x2c))(param_1 + 0x54,0x80 - ((int)sVar2 & 0xffU) & 0xff);
  (**(code **)(*(int *)(param_1 + 0x5c) + 0x14))(param_1 + 0x54,param_2,param_3,param_4);
  bVar1 = *pbVar3;
  *(byte *)(param_1 + 0xc4) = *(byte *)(param_1 + 0xc4) | bVar1;
  *(byte *)(param_1 + 0xc5) = *(byte *)(param_1 + 0xc5) | bVar1;
  (**(code **)(*(int *)(param_1 + 0xbc) + 0x14))(param_1 + 0xb4,param_2,param_3,param_4);
  *pbVar3 = *pbVar3 & 0x80;
  return;
}

/* ---- 0x00280f30 size 0x54  KeyWait::Connect(P4_QWD)
 *      mangled: Connect__7KeyWaitFP4_QWD */
int Connect__7KeyWaitFP4_QWD(int param_1,u32 param_2)

{
  void *p2;
  int iVar1;
  
  p2 = (void *)(**(code **)(*(int *)(param_1 + 0x5c) + 0x18))(param_1 + 0x54,param_2);
  iVar1 = ConnectPacket__10MenuPacketFP4_QWD((MenuPacket *)(param_1 + 0xcc),p2);
  return iVar1;
}

/* ---- 0x00280f90 size 0x64  KeyWait::Destroy(v)
 *      mangled: Destroy__7KeyWaitFv */
void Destroy__7KeyWaitFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x5c) + 0x1c))();
  (**(code **)(*(int *)(param_1 + 0x2c) + 0x1c))();
  (**(code **)(*(int *)(param_1 + 0xbc) + 0x1c))();
  return;
}

/* ---- 0x00281000 size 0xe4  KeyWait::Clear(v)
 *      mangled: Clear__7KeyWaitFv */
void Clear__7KeyWaitFv(MenuObj *param_1)

{
  ulong uVar1;
  
  Clear__7MenuObjFv(param_1);
  (**(code **)(*(int *)&param_1[3].nPriority + 0x20))();
  (**(code **)(*(int *)&param_1[1].nPriority + 0x20))();
  (**(code **)(*(int *)&param_1[7].nPriority + 0x20))();
  *(u16 *)&param_1[1].pLink_next = 0;
  *(u16 *)((int)&param_1[1].pLink_next + 2) = 0;
  *(u16 *)&param_1[1].pVptr = 0x2000;
  *(u16 *)((int)&param_1[1].pVptr + 2) = 1;
  uVar1 = (ulong)param_1->bDirty1 & 0xffffffffffffff7f | 0x80;
  param_1->bDirty1 = (byte)uVar1;
  param_1->bDirty0 = param_1->bDirty0 & 0x7f | (byte)((uint)((uVar1 << 0x38) >> 0x3f) << 7);
  return;
}

