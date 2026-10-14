/*
 * SdrvEE.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 90 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00372740 size 0x3c  SdrvEE::SetID(ii)
 *      mangled: SetID__6SdrvEEFii */
void SetID__6SdrvEEFii(int param_1,u16 param_2,u16 param_3)

{
  *(u16 *)(param_1 + 0x2c) = param_2;
  *(u16 *)(param_1 + 0x2e) = param_3;
  return;
}

/* ---- 0x003727d0 size 0x5c  SdrvEE::~SdrvEE(v)
 *      mangled: __dt__6SdrvEEFv */
int __dt__6SdrvEEFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (Release__6SdrvEEFv(param_1), 0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}

/* ---- 0x00372cc0 size 0x1c  SdrvEE::StreamGetValue(v)
 *      mangled: StreamGetValue__6SdrvEEFv */
u32 StreamGetValue__6SdrvEEFv(int param_1)

{
  return *(u32 *)(param_1 + 0x16c);
}

/* ---- 0x003733f0 size 0xd4  SdrvEE::CmdTest(v)
 *      mangled: CmdTest__6SdrvEEFv */
u64 CmdTest__6SdrvEEFv(int param_1)

{
  int iVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x58);
  uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
  iVar4 = (int)uVar2;
  *(uint *)(iVar4 + 0xc) = (uint)*(ushort *)(iVar1 + 2) << 0x10 | 0xf;
  *(u32 *)(iVar4 + 0x10) = *(u32 *)(iVar1 + 4);
  *(u32 *)(iVar4 + 0x14) = *(u32 *)(iVar1 + 8);
  *(u32 *)(iVar4 + 0x18) = *(u32 *)(iVar1 + 0xc);
  uVar2 = sceSifSendCmd(*(u16 *)(param_1 + 0x2c),uVar2,0x20,0,0,0);
  do {
    lVar3 = sceSifDmaStat(uVar2);
  } while (-1 < lVar3);
  UpdateReqRp__6SdrvEEFv(param_1);
  return 0;
}

/* ---- 0x003734d0 size 0x34  SdrvEE::SdrvEE(v)
 *      mangled: __ct__6SdrvEEFv */
void * __ct__6SdrvEEFv(void *param_1)

{
  memset(param_1,0,0x39c);
  return param_1;
}

/* ---- 0x00373510 size 0x50  SdrvEE::InitTransReqWk(iiPUi)
 *      mangled: InitTransReqWk__6SdrvEEFiiPUi */
void InitTransReqWk__6SdrvEEFiiPUi(int param_1,int param_2,u8 param_3,u32 param_4)

{
  param_1 = param_1 + param_2 * 8;
  *(u8 *)(param_1 + 6) = param_3;
  *(u32 *)(param_1 + 8) = param_4;
  return;
}

/* ---- 0x00373560 size 0x290  SdrvEE::Init(v)
 *      mangled: Init__6SdrvEEFv */
void * Init__6SdrvEEFv(int param_1)

{
  ushort uVar1;
  void *pvVar2;
  u64 uVar3;
  uint uVar4;
  int iVar5;
  
  uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
  iVar5 = (int)uVar3;
  *(u32 *)(iVar5 + 0xc) = 1;
  *(u16 *)(iVar5 + 0x10) = *(u16 *)(param_1 + 0x2e);
  *(u32 *)(iVar5 + 0x14) = 0x40000;
  *(u8 **)(iVar5 + 0x18) = &logBuf;
  SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0,1);
  *(u16 *)(param_1 + 0x48) = 0x40;
  *(u8 *)(param_1 + 0x3b) = 0x40;
  uVar1 = *(ushort *)(param_1 + 0x48);
  uVar4 = (uint)uVar1;
  iVar5 = uVar4 * 4 + (uVar1 + 0x1f >> 5) + (uVar1 + 1 >> 1) +
          ((uint)*(byte *)(param_1 + 0x3b) * 8 + 0xf >> 2) + 0x60;
  pvVar2 = (void *)__nwa__FUi(iVar5 * 4);
  memset(pvVar2,0,(long)(iVar5 * 4));
  *(void **)(param_1 + 0x3c) = pvVar2;
  pvVar2 = (void *)((int)pvVar2 + (uVar4 + 0x1f >> 5) * 4);
  *(void **)(param_1 + 0x44) = pvVar2;
  pvVar2 = (void *)((int)pvVar2 + (uVar4 + 1 >> 1) * 4);
  *(void **)(param_1 + 0x40) = pvVar2;
  pvVar2 = (void *)((int)pvVar2 + uVar4 * 0x10);
  InitTransReqWk__6SdrvEEFiiPUi(param_1,0,0x10,pvVar2);
  InitTransReqWk__6SdrvEEFiiPUi(param_1,1,8,(int)pvVar2 + 0x100);
  *(int *)(param_1 + 0xdc) = (int)pvVar2 + 0x180;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xf0 | 1;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf | 0x10;
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf0 | 3;
  *(u8 *)(param_1 + 0x16b) = 0x7f;
  *(u8 *)(param_1 + 0x16a) = 0x7f;
  *(u8 *)(param_1 + 0x169) = 0x7f;
  *(u8 *)(param_1 + 0x168) = 0x7f;
  for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
    *(u32 *)(param_1 + iVar5 * 8 + 0xe4) = 0xffffffff;
  }
  memset((void *)(param_1 + 0x17c),0xff,0x200);
  pvVar2 = memset((void *)(param_1 + 0x37c),0xff,0x20);
  return pvVar2;
}

/* ---- 0x003737f0 size 0x48  SdrvEE::Release(v)
 *      mangled: Release__6SdrvEEFv */
void Release__6SdrvEEFv(int param_1)

{
  if (*(int *)(param_1 + 0x3c) != 0) {
    __dla__FPv(*(u32 *)(param_1 + 0x3c));
    *(u32 *)(param_1 + 0x3c) = 0;
  }
  return;
}

/* ---- 0x00373840 size 0xd4  SdrvEE::Reset(v)
 *      mangled: Reset__6SdrvEEFv */
bool Reset__6SdrvEEFv(byte *param_1)

{
  u64 uVar1;
  
  if (*param_1 >> 6 == 0) {
    *param_1 = *param_1 & 0x3f | 0x40;
    param_1[0x5e] = 0;
    uVar1 = GetCmdPkt__6SdrvEEFv(param_1);
    *(u32 *)((int)uVar1 + 0xc) = 0xc;
    SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar1,0,1);
  }
  return *param_1 >> 6 == 1;
}

/* ---- 0x00373920 size 0x44  SdrvEE::GetCmdPkt(v)
 *      mangled: GetCmdPkt__6SdrvEEFv */
u8 * GetCmdPkt__6SdrvEEFv(int param_1)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0x39);
  *(byte *)(param_1 + 0x39) = bVar1 + 1;
  return &CmdPkt + (bVar1 & 7) * 0x30;
}

/* ---- 0x00373970 size 0x2fc  SdrvEE::GetReqS(PUiiUi)
 *      mangled: GetReqS__6SdrvEEFPUiiUi */
u8 * GetReqS__6SdrvEEFPUiiUi(int param_1,uint *param_2,u8 param_3,uint param_4)

{
  uint uVar1;
  ushort uVar2;
  bool bVar3;
  uint unaff_s0_lo;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  u8 *__s;
  uint uVar7;
  u32 uStack_44;
  
  uVar1 = (*(ushort *)(param_1 + 0x4c) + 1) % (uint)*(ushort *)(param_1 + 0x48);
  if (*(ushort *)(param_1 + 0x48) == 0) {
    trap(7);
  }
  if (uVar1 == *(ushort *)(param_1 + 0x4a)) {
    bVar3 = true;
  }
  else {
    uVar4 = (1 << (param_4 & 0x1f)) - 1;
    uVar7 = **(uint **)(param_1 + 0x3c);
    bVar3 = true;
    for (unaff_s0_lo = 0; unaff_s0_lo < *(ushort *)(param_1 + 0x48); unaff_s0_lo = unaff_s0_lo + 1)
    {
      if ((uVar7 & uVar4) == 0) {
        bVar3 = false;
        iVar5 = uVar4 << (unaff_s0_lo & 7);
        pbVar6 = (byte *)(*(int *)(param_1 + 0x3c) + (unaff_s0_lo >> 3));
        *pbVar6 = *pbVar6 | (byte)iVar5;
        pbVar6[1] = pbVar6[1] | (byte)((uint)iVar5 >> 8);
        pbVar6[2] = pbVar6[2] | (byte)((uint)iVar5 >> 0x10);
        pbVar6[3] = pbVar6[3] | (byte)((uint)iVar5 >> 0x18);
        break;
      }
      uVar7 = uVar7 >> 1;
      if ((unaff_s0_lo & 7) == 7) {
        uVar7 = uVar7 | (uint)*(byte *)(*(int *)(param_1 + 0x3c) + (unaff_s0_lo >> 3) + 4) << 0x18;
      }
    }
  }
  if (bVar3) {
    SetLastError__6SdrvEEFi(param_1,0x40);
    *param_2 = 0xffffffff;
    __s = (u8 *)0x0;
  }
  else {
    uVar2 = (ushort)unaff_s0_lo & 0x3ff;
    uStack_44._1_1_ = (byte)(uVar2 >> 8);
    uStack_44._0_2_ = CONCAT11(uStack_44._1_1_ | (byte)((param_4 & 0x3f) << 2),(char)uVar2);
    *(u16 *)(*(int *)(param_1 + 0x44) + (uint)*(ushort *)(param_1 + 0x4c) * 2) =
         (u16)uStack_44;
    if (uVar1 == 0) {
      *(short *)(param_1 + 0x4e) = *(short *)(param_1 + 0x4e) + 1;
    }
    uStack_44._0_2_ = CONCAT11(param_3,(char)*(u16 *)(param_1 + 0x4c));
    uStack_44 = (uint)CONCAT12((char)*(u16 *)(param_1 + 0x4e),(u16)uStack_44);
    *param_2 = uStack_44;
    *(short *)(param_1 + 0x4c) = (short)uVar1;
    __s = (u8 *)(*(int *)(param_1 + 0x40) + unaff_s0_lo * 0x10);
    memset(__s,0,(long)(int)(param_4 << 4));
    *__s = param_3;
    __s[1] = (char)*(u16 *)(param_1 + 0x4e);
  }
  return __s;
}

/* ---- 0x00373c70 size 0x24  SdrvEE::SetLastError(i)
 *      mangled: SetLastError__6SdrvEEFi */
void SetLastError__6SdrvEEFi(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x30) = param_2;
  return;
}

/* ---- 0x00373ca0 size 0x154  SdrvEE::GetTransReq(PUiii)
 *      mangled: GetTransReq__6SdrvEEFPUiii */
uint * GetTransReq__6SdrvEEFPUiii(int param_1,uint *param_2,u8 param_3,int param_4)

{
  uint uVar1;
  byte *pbVar2;
  uint *__s;
  u32 uStack_44;
  
  param_1 = param_1 + param_4 * 8;
  pbVar2 = (byte *)(param_1 + 4);
  uVar1 = (*pbVar2 + 1) % (uint)*(byte *)(param_1 + 6);
  if (*(byte *)(param_1 + 6) == 0) {
    trap(7);
  }
  if (uVar1 == *(byte *)(param_1 + 5)) {
    *param_2 = 0xffffffff;
    __s = (uint *)0x0;
  }
  else {
    if (*pbVar2 == 0) {
      *(char *)(param_1 + 7) = *(char *)(param_1 + 7) + '\x01';
    }
    uStack_44._0_3_ = CONCAT12(*(u8 *)(param_1 + 7),CONCAT11(param_3,*pbVar2));
    uStack_44 = CONCAT13((char)param_4 + '\x01',(undefined3)uStack_44) & 0x3ffffff;
    __s = (uint *)(*(int *)(param_1 + 8) + (uint)*pbVar2 * 0x10);
    *param_2 = uStack_44;
    memset(__s,0,0x10);
    *__s = uStack_44;
    *pbVar2 = (byte)uVar1;
  }
  return __s;
}

/* ---- 0x00373e00 size 0x98  SdrvEE::ChkInternalReq(UiRUi)
 *      mangled: ChkInternalReq__6SdrvEEFUiRUi */
long ChkInternalReq__6SdrvEEFUiRUi(u32 param_1,u32 param_2,u32 *param_3)

{
  u32 uVar1;
  long lVar2;
  
  lVar2 = GetStatus__6SdrvEEFUi(param_1,param_2);
  if (lVar2 == -2) {
    CloseHandle__6SdrvEEFUi(param_1,param_2);
  }
  if (lVar2 == 3) {
    uVar1 = GetOption__6SdrvEEFUi(param_1,param_2);
    *param_3 = uVar1;
    CloseHandle__6SdrvEEFUi(param_1,param_2);
  }
  return lVar2;
}

/* ---- 0x00373ea0 size 0x84  SdrvEE::AutoLoad(PvPv)
 *      mangled: AutoLoad__6SdrvEEFPvPv */
u32 AutoLoad__6SdrvEEFPvPv(u32 param_1,u32 param_2,u32 param_3)

{
  long lVar1;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  lVar1 = GetTransReq__6SdrvEEFPUiii(param_1,&uStack_34,3,0);
  if (lVar1 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_20;
    *(u32 *)((int)lVar1 + 8) = uStack_10;
    InvokeReqHandlerA__6SdrvEEFUii(uStack_30,uStack_34,0);
  }
  return uStack_34;
}

/* ---- 0x00373f30 size 0x14c  SdrvEE::LoadSDH(Pv)
 *      mangled: LoadSDH__6SdrvEEFPv */
u32 LoadSDH__6SdrvEEFPv(u32 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *__s1;
  ulong uVar3;
  u32 uStack_24;
  u32 uStack_20;
  int iStack_10;
  
  uStack_20 = param_1;
  iStack_10 = param_2;
  iVar1 = GetTransReq__6SdrvEEFPUiii(param_1,&uStack_24,4,1);
  *(int *)(iVar1 + 4) = iStack_10;
  uVar3 = (ulong)(int)((*(uint *)(iStack_10 + 8) >> 8) << 4);
  __s1 = (void *)(iStack_10 + (uint)*(byte *)(iStack_10 + 8) * 0x10);
  do {
    if (uVar3 <= (ulong)(long)((int)__s1 - iStack_10)) {
LAB_00374008:
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xff000000 | (uint)((uVar3 << 0x28) >> 0x28)
      ;
      *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xff000000;
      InvokeReqHandlerA__6SdrvEEFUii(uStack_20,uStack_24,1);
      return uStack_24;
    }
    iVar2 = memcmp(__s1,&_1938,2);
    if (iVar2 == 0) {
      uVar3 = (ulong)((int)__s1 - iStack_10);
      goto LAB_00374008;
    }
    __s1 = (void *)((int)__s1 + (uint)*(ushort *)((int)__s1 + 4) * 0x10);
  } while( true );
}

/* ---- 0x00374080 size 0x7c  SdrvEE::ReleaseSDH(Ui)
 *      mangled: ReleaseSDH__6SdrvEEFUi */
u32 ReleaseSDH__6SdrvEEFUi(u32 param_1,u32 param_2)

{
  long lVar1;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  lVar1 = GetTransReq__6SdrvEEFPUiii(param_1,&uStack_24,5,1);
  if (lVar1 == 0) {
    uStack_24 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_10;
    InvokeReqHandlerA__6SdrvEEFUii(uStack_20,uStack_24,1);
  }
  return uStack_24;
}

/* ---- 0x00374100 size 0x7c  SdrvEE::IopFindWaveAddr(Ui)
 *      mangled: IopFindWaveAddr__6SdrvEEFUi */
u32 IopFindWaveAddr__6SdrvEEFUi(u32 param_1,u32 param_2)

{
  long lVar1;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  lVar1 = GetTransReq__6SdrvEEFPUiii(param_1,&uStack_24,6,1);
  if (lVar1 == 0) {
    uStack_24 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_10;
    InvokeReqHandlerA__6SdrvEEFUii(uStack_20,uStack_24,1);
  }
  return uStack_24;
}

/* ---- 0x00374180 size 0xe4  SdrvEE::TransWaveData(UiPUcUi)
 *      mangled: TransWaveData__6SdrvEEFUiPUcUi */
u32
TransWaveData__6SdrvEEFUiPUcUi(u32 param_1,int param_2,u32 param_3,int param_4)

{
  long lVar1;
  int iVar2;
  u32 uStack_44;
  u32 uStack_40;
  int iStack_30;
  u32 uStack_20;
  int iStack_10;
  
  uStack_40 = param_1;
  iStack_30 = param_2;
  uStack_20 = param_3;
  iStack_10 = param_4;
  lVar1 = GetTransReq__6SdrvEEFPUiii(param_1,&uStack_44,7,1);
  if (lVar1 == 0) {
    uStack_44 = 0xffffffff;
  }
  else {
    scePrintf(0x3ff5a0,iStack_30,uStack_20,iStack_10);
    iVar2 = (int)lVar1;
    *(uint *)(iVar2 + 8) =
         *(uint *)(iVar2 + 8) & 0xff000000 | (uint)((ulong)((long)iStack_30 << 0x28) >> 0x28);
    *(u32 *)(iVar2 + 4) = uStack_20;
    *(uint *)(iVar2 + 0xc) =
         *(uint *)(iVar2 + 0xc) & 0xff000000 | (uint)((ulong)((long)iStack_10 << 0x28) >> 0x28);
    InvokeReqHandlerA__6SdrvEEFUii(uStack_40,uStack_44,1);
  }
  return uStack_44;
}

/* ---- 0x00374270 size 0x160  SdrvEE::PlaySE(UiP8_SeParam)
 *      mangled: PlaySE__6SdrvEEFUiP8_SeParam */
u32 PlaySE__6SdrvEEFUiP8_SeParam(u32 param_1,u32 param_2,void *param_3)

{
  bool bVar1;
  long lVar2;
  int iVar3;
  u32 uVar4;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  void *pvStack_10;
  
  bVar1 = false;
  if ((param_3 != (void *)0x0) && ((*(ushort *)((int)param_3 + 6) & 7) != 0)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar4 = 2;
  }
  else {
    uVar4 = 1;
  }
  uStack_30 = param_1;
  uStack_20 = param_2;
  pvStack_10 = param_3;
  lVar2 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_34,9,uVar4);
  if (lVar2 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    iVar3 = (int)lVar2;
    *(u16 *)(iVar3 + 2) = 0;
    *(u32 *)(iVar3 + 4) = uStack_20;
    if (pvStack_10 == (void *)0x0) {
      *(u16 *)(iVar3 + 2) = 0;
      *(u8 *)(iVar3 + 8) = 0x7f;
      *(u8 *)(iVar3 + 9) = 0x40;
      *(u16 *)(iVar3 + 10) = 0;
      *(u16 *)(iVar3 + 0xc) = 1000;
      *(u16 *)(iVar3 + 0xe) = 0;
    }
    else {
      memcpy((void *)(iVar3 + 8),pvStack_10,8);
      if (bVar1) {
        *(u32 *)(iVar3 + 0x10) = *(u32 *)((int)pvStack_10 + 8);
      }
      *(u16 *)(iVar3 + 2) = *(u16 *)((int)pvStack_10 + 6);
    }
    InvokeReqHandler__6SdrvEEFUi(uStack_30,uStack_34);
  }
  return uStack_34;
}

/* ---- 0x003743d0 size 0x7c  SdrvEE::GetSEStat(Ui)
 *      mangled: GetSEStat__6SdrvEEFUi */
u32 GetSEStat__6SdrvEEFUi(u32 param_1,u32 param_2)

{
  long lVar1;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_24,0xb,1);
  if (lVar1 == 0) {
    uStack_24 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_20,uStack_24);
  }
  return uStack_24;
}

/* ---- 0x00374450 size 0x84  SdrvEE::ReleaseSE(Uii)
 *      mangled: ReleaseSE__6SdrvEEFUii */
u32 ReleaseSE__6SdrvEEFUii(u32 param_1,u32 param_2,u32 param_3)

{
  long lVar1;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_34,0xd,1);
  if (lVar1 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_20;
    *(u32 *)((int)lVar1 + 8) = uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_30,uStack_34);
  }
  return uStack_34;
}

/* ---- 0x003744e0 size 0xa4  SdrvEE::iReleaseSE(Ui)
 *      mangled: iReleaseSE__6SdrvEEFUi */
void iReleaseSE__6SdrvEEFUi(int param_1,u32 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0x7f < iVar1) {
      scePrintf(0x3ff5c0);
      return;
    }
    if (*(int *)(param_1 + iVar1 * 4 + 0x17c) == -1) break;
    iVar1 = iVar1 + 1;
  }
  *(u32 *)(param_1 + iVar1 * 4 + 0x17c) = param_2;
  *(char *)(param_1 + 0x3a) = *(char *)(param_1 + 0x3a) + '\x01';
  return;
}

/* ---- 0x00374590 size 0x94  SdrvEE::iReleaseBGM(Ui)
 *      mangled: iReleaseBGM__6SdrvEEFUi */
void iReleaseBGM__6SdrvEEFUi(int param_1,u32 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (7 < iVar1) {
      scePrintf(0x3ff5d0);
      return;
    }
    if (*(int *)(param_1 + iVar1 * 4 + 0x37c) == -1) break;
    iVar1 = iVar1 + 1;
  }
  *(u32 *)(param_1 + iVar1 * 4 + 0x37c) = param_2;
  return;
}

/* ---- 0x00374630 size 0xcc  SdrvEE::DelayReleaseSE(v)
 *      mangled: DelayReleaseSE__6SdrvEEFv */
void DelayReleaseSE__6SdrvEEFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x3a) != '\0') {
    for (iVar2 = 0; iVar2 < 0x80; iVar2 = iVar2 + 1) {
      if ((*(int *)(param_1 + iVar2 * 4 + 0x17c) != -1) &&
         (lVar1 = ReleaseSE__6SdrvEEFUii(param_1,*(u32 *)(param_1 + iVar2 * 4 + 0x17c),0),
         lVar1 != -1)) {
        *(u32 *)(param_1 + iVar2 * 4 + 0x17c) = 0xffffffff;
        *(char *)(param_1 + 0x3a) = *(char *)(param_1 + 0x3a) + -1;
      }
    }
  }
  return;
}

/* ---- 0x00374700 size 0xa8  SdrvEE::DelayReleaseBGM(v)
 *      mangled: DelayReleaseBGM__6SdrvEEFv */
void DelayReleaseBGM__6SdrvEEFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
    if ((*(int *)(param_1 + iVar2 * 4 + 0x37c) != -1) &&
       (lVar1 = ReleaseBGM__6SdrvEEFUii(param_1,*(u32 *)(param_1 + iVar2 * 4 + 0x37c),0),
       lVar1 != -1)) {
      *(u32 *)(param_1 + iVar2 * 4 + 0x37c) = 0xffffffff;
    }
  }
  return;
}

/* ---- 0x003747b0 size 0x1c8  SdrvEE::SetMode(i)
 *      mangled: SetMode__6SdrvEEFi */
u32 SetMode__6SdrvEEFi(int param_1,uint param_2)

{
  byte bVar1;
  long lVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  u32 uStack_24;
  int iStack_20;
  uint uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  lVar2 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_24,2,1);
  if (lVar2 == 0) {
    uStack_24 = 0xffffffff;
  }
  else {
    uVar5 = (int)uStack_10 >> 5 & 1;
    uVar4 = (int)uStack_10 >> 0xc;
    if (((uVar4 & 1) != 0) &&
       (*(byte *)(iStack_20 + 2) = *(byte *)(iStack_20 + 2) & 0xf0 | (byte)uStack_10 & 0xf,
       (uStack_10 & 0xf) == 2)) {
      uVar4 = uVar4 | 8;
      uVar5 = 1;
    }
    if ((uVar4 & 2) != 0) {
      *(byte *)(iStack_20 + 2) =
           *(byte *)(iStack_20 + 2) & 0xf | (byte)(((int)uStack_10 >> 4 & 1U) << 4);
    }
    bVar1 = (byte)(uStack_10 >> 8);
    if ((uVar4 & 4) != 0) {
      *(byte *)(iStack_20 + 3) = *(byte *)(iStack_20 + 3) & 0xf0 | bVar1 & 0xf;
    }
    if ((uVar4 & 8) != 0) {
      *(byte *)(iStack_20 + 3) = *(byte *)(iStack_20 + 3) & 0xf | (byte)(uVar5 << 4);
    }
    iVar3 = (int)lVar2;
    *(u16 *)(iVar3 + 2) = 0;
    *(uint *)(iVar3 + 4) = uVar4;
    *(byte *)(iVar3 + 5) = (byte)uStack_10 & 0xf;
    *(byte *)(iVar3 + 6) = (byte)((int)uStack_10 >> 4) & 1 | (byte)(uVar5 << 4);
    *(byte *)(iVar3 + 7) = bVar1 & 0xf;
    InvokeReqHandler__6SdrvEEFUi(iStack_20,uStack_24);
  }
  return uStack_24;
}

/* ---- 0x00374980 size 0xc4  SdrvEE::SetReverb(iiiii)
 *      mangled: SetReverb__6SdrvEEFiiiii */
u32
SetReverb__6SdrvEEFiiiii
          (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
          u32 param_5,u32 param_6)

{
  long lVar1;
  int iVar2;
  u32 uStack_64;
  u32 uStack_60;
  u32 uStack_50;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_60 = param_1;
  uStack_50 = param_2;
  uStack_40 = param_3;
  uStack_30 = param_4;
  uStack_20 = param_5;
  uStack_10 = param_6;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_64,2,1);
  if (lVar1 == 0) {
    uStack_64 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 2) = 3;
    *(char *)(iVar2 + 4) = (char)uStack_50;
    *(char *)(iVar2 + 5) = (char)uStack_40;
    *(char *)(iVar2 + 6) = (char)uStack_30;
    *(char *)(iVar2 + 7) = (char)uStack_20;
    *(char *)(iVar2 + 8) = (char)uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_60,uStack_64);
  }
  return uStack_64;
}

/* ---- 0x00374a50 size 0xccc  SdrvEE::StreamCtrl(iUiUiUiUi)
 *      mangled: StreamCtrl__6SdrvEEFiUiUiUiUi */
u32
StreamCtrl__6SdrvEEFiUiUiUiUi(int param_1,int param_2,u32 *param_3,int *param_4,uint param_5)

{
  u32 *puVar1;
  u32 uVar2;
  int iVar3;
  long lVar4;
  u64 uVar5;
  void *__s;
  uint uVar6;
  u32 *puVar7;
  uint uVar8;
  uint uStack_94;
  uint uStack_90;
  uint uStack_8c;
  u32 uStack_80;
  int iStack_7c;
  u32 uStack_78;
  int iStack_74;
  u32 uStack_70;
  int *piStack_6c;
  u32 *puStack_68;
  u8 uStack_61;
  int iStack_60;
  int iStack_50;
  u32 *puStack_40;
  int *piStack_30;
  uint uStack_20;
  
  puVar7 = *(u32 **)(param_1 + 0x164);
  puStack_68 = (u32 *)0x0;
  puVar1 = puVar7;
  if (param_2 != 0) {
    while ((puVar7 = puVar1, puVar7 != (u32 *)0x0 && (puVar7 != param_3))) {
      puStack_68 = puVar7;
      puVar1 = (u32 *)*puVar7;
    }
    if (puVar7 == (u32 *)0x0) {
      *(u32 *)(param_1 + 0x16c) = 0xffffffff;
      return 0xffffffff;
    }
  }
  *(u32 *)(param_1 + 0x16c) = 1;
  iStack_60 = param_1;
  iStack_50 = param_2;
  puStack_40 = param_3;
  piStack_30 = param_4;
  uStack_20 = param_5;
  switch(param_2) {
  case 0:
    lVar4 = __nw__FUi(0x40);
    if (lVar4 == 0) {
      return 0xffffffff;
    }
    __s = (void *)lVar4;
    memset(__s,0,0x40);
    *(byte *)((int)__s + 4) = *(byte *)((int)__s + 4) & 0xf0 | 0xf;
    *(byte *)((int)__s + 5) = *(byte *)((int)__s + 5) & 0xfe | (byte)piStack_30 & 1;
    if (*(int *)(iStack_60 + 0x164) == 0) {
      *(void **)(iStack_60 + 0x164) = __s;
    }
    else {
      for (piStack_6c = *(int **)(iStack_60 + 0x164); *piStack_6c != 0;
          piStack_6c = (int *)*piStack_6c) {
      }
      *piStack_6c = (int)__s;
    }
    *(void **)(iStack_60 + 0x16c) = __s;
    break;
  case 1:
    scePrintf(0x3ff5e0,*(byte *)(puVar7 + 1) & 0xf);
    if ((*(byte *)(puVar7 + 1) & 0xf) != 0xf) {
      uVar5 = GetCmdPkt__6SdrvEEFv(iStack_60);
      iVar3 = (int)uVar5;
      *(u32 *)(iVar3 + 0xc) = 0x1507;
      *(u32 **)(iVar3 + 0x10) = puVar7;
      *(ushort *)(iVar3 + 0x14) = *(byte *)(puVar7 + 1) & 0xf;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(iStack_60,uVar5,0,0);
    }
    if (puVar7[4] != 0) {
      if ((long)((ulong)*(byte *)((int)puVar7 + 5) << 0x3c) < 0) {
        __dla__FPv(puVar7[4]);
      }
      else {
        __dla__FPv(puVar7[0xf]);
      }
    }
    if (puStack_68 == (u32 *)0x0) {
      *(u32 *)(iStack_60 + 0x164) = *puVar7;
    }
    else {
      *puStack_68 = *puVar7;
    }
    __dl__FPv(puVar7);
    break;
  case 2:
    iStack_74 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_70,8,1);
    if (iStack_74 != 0) {
      if ((*(byte *)((int)puVar7 + 5) & 1) == 0) {
        *(byte *)(puVar7 + 1) =
             *(byte *)(puVar7 + 1) & 0x7f | (byte)(((int)piStack_30 - 1U & 1) << 7);
        puVar7[9] = 0x800;
      }
      else {
        puVar7[9] = 0x1000;
      }
      *(byte *)(puVar7 + 1) = *(byte *)(puVar7 + 1) & 0xcf | (byte)((uStack_20 & 3) << 4);
      *(u16 *)(iStack_74 + 2) = 2;
      *(u32 **)(iStack_74 + 4) = puStack_40;
      InvokeReqHandler__6SdrvEEFUi(iStack_60,uStack_70);
      return uStack_70;
    }
    return 0xffffffff;
  case 3:
    if ((*(byte *)((int)puVar7 + 5) & 1) == 0) {
      uStack_61 = 8;
    }
    else {
      uStack_61 = 1;
    }
    iStack_7c = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_78,uStack_61,1);
    if (iStack_7c != 0) {
      if ((*(byte *)((int)puVar7 + 5) & 1) != 0) {
        SetResult__6SdrvEEFUiUiUi(iStack_60,uStack_78,1,0);
        UpdateReqRp__6SdrvEEFUi(iStack_60,uStack_78);
        return uStack_78;
      }
      *(short *)((int)puVar7 + 10) = (short)piStack_30;
      *(short *)(puVar7 + 3) = (short)((uint)piStack_30 >> 0x10);
      *(short *)((int)puVar7 + 0xe) = (short)uStack_20;
      *(u16 *)(iStack_7c + 2) = 3;
      *(u32 **)(iStack_7c + 4) = puStack_40;
      InvokeReqHandler__6SdrvEEFUi(iStack_60,uStack_78);
      return uStack_78;
    }
    return 0xffffffff;
  case 4:
    if (param_4 == (int *)0x3) {
      lVar4 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_80,1,1);
      if (lVar4 == 0) {
        return 0xffffffff;
      }
      SetResult__6SdrvEEFUiUiUi
                (iStack_60,uStack_80,1,
                 (uint)puVar7[8] >> (uint)(((ulong)*(byte *)(puVar7 + 1) << 0x38) >> 0x3f));
      UpdateReqRp__6SdrvEEFUi(iStack_60,uStack_80);
      return uStack_80;
    }
    if (param_4 == (int *)0x2) {
      lVar4 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_80,1,1);
      if (lVar4 == 0) {
        return 0xffffffff;
      }
      SetResult__6SdrvEEFUiUiUi(iStack_60,uStack_80,1,0x1fff < (uint)puVar7[8]);
      UpdateReqRp__6SdrvEEFUi(iStack_60,uStack_80);
      return uStack_80;
    }
    if (param_4 == (int *)0x1) {
      lVar4 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_80,8,1);
      if (lVar4 == 0) {
        return 0xffffffff;
      }
      *(u16 *)((int)lVar4 + 2) = 4;
      *(u32 **)((int)lVar4 + 4) = puStack_40;
      InvokeReqHandler__6SdrvEEFUi(iStack_60,uStack_80);
      return uStack_80;
    }
    if (param_4 == (int *)0x0) {
      lVar4 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_80,1,1);
      if (lVar4 == 0) {
        return 0xffffffff;
      }
      SetResult__6SdrvEEFUiUiUi(iStack_60,uStack_80,1,((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1);
      UpdateReqRp__6SdrvEEFUi(iStack_60,uStack_80);
      return uStack_80;
    }
    return uStack_80;
  case 5:
    iVar3 = __nwa__FUi((int)param_4 + ((uint)param_4 >> 10) + 0x30);
    *(int *)(iStack_60 + 0x16c) = iVar3;
    if (iVar3 != 0) {
      puVar7[5] = piStack_30;
      puVar7[4] = iVar3;
      puVar7[0xf] = (int)piStack_30 + iVar3 + 0x30;
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xf7 | 8;
    }
    break;
  case 6:
    if (param_3[4] != 0) {
      if ((long)((ulong)*(byte *)((int)param_3 + 5) << 0x3c) < 0) {
        __dla__FPv(param_3[4]);
      }
      else {
        __dla__FPv(param_3[0xf]);
      }
    }
    param_3[4] = piStack_30;
    param_3[5] = uStack_20;
    *(byte *)((int)param_3 + 5) = *(byte *)((int)param_3 + 5) & 0xf7;
    uVar2 = __nwa__FUi((uStack_20 >> 0xb) << 1);
    param_3[0xf] = uVar2;
    break;
  case 7:
    uVar8 = 0x800;
    if ((*(byte *)((int)puVar7 + 5) & 1) == 1) {
      uVar8 = 0x8000;
    }
    else if ((long)((ulong)*(byte *)(puVar7 + 1) << 0x38) < 0) {
      uVar8 = 0x1000;
    }
    if ((uint)puVar7[7] < (uint)puVar7[6]) {
      uVar6 = (puVar7[6] - puVar7[7]) - uVar8;
      if ((int)uVar6 <= (int)uVar8) {
        uVar6 = 0;
      }
    }
    else {
      uVar6 = puVar7[5] - puVar7[7];
      if (((puVar7[6] == 0) && ((long)((ulong)*(byte *)((int)puVar7 + 5) << 0x3b) < 0)) &&
         (uVar6 = uVar6 - uVar8, (int)uVar6 < (int)uVar8)) {
        uVar6 = 0;
      }
    }
    if (((*(byte *)((int)puVar7 + 5) & 1) == 0) &&
       (uVar6 = uVar6 & ~(uVar8 - 1), (int)uVar8 < (int)uVar6)) {
      uVar6 = uVar8;
    }
    uStack_8c = puVar7[7];
    if ((uint)puVar7[5] <= uStack_8c) {
      uStack_8c = 0;
    }
    uStack_90 = puVar7[4];
    if ((long)((ulong)*(byte *)((int)puVar7 + 5) << 0x3c) < 0) {
      uStack_90 = uStack_90 + 0x3f & 0xffffffc0;
    }
    *param_4 = uStack_90 + uStack_8c;
    *(uint *)(param_1 + 0x16c) = uVar6;
    break;
  case 8:
    uStack_94 = puVar7[7];
    if ((uint)puVar7[5] <= uStack_94) {
      uStack_94 = 0;
    }
    *(short *)(puVar7[0xf] + (uStack_94 >> 0xb) * 2) = (short)param_5;
    puVar7[7] = puVar7[7] + (int)param_4;
    if (param_4 != (int *)0x0) {
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xef | 0x10;
    }
    break;
  case 9:
    *(u32 *)(param_1 + 0x16c) = 0;
    if (((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1 == 0) {
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xf9 | 2;
      if (param_4 == (int *)0x1) {
        iVar3 = GetCmdPkt__6SdrvEEFv(param_1);
        *(u32 *)(iVar3 + 0xc) = 0x1207;
        *(ushort *)(iVar3 + 0x10) = *(byte *)(puVar7 + 1) & 0xf;
        SendCmd__6SdrvEEFP13_SdrvCmdPktExii(iStack_60,iVar3,0,0);
      }
      else {
        *(byte *)(puVar7 + 1) = *(byte *)(puVar7 + 1) & 0xbf | 0x40;
      }
    }
    else {
      *(u32 *)(param_1 + 0x16c) = 2;
    }
    break;
  case 10:
    scePrintf(0x3ff5f0,((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1,param_4);
    if ((((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1 == 1) ||
       (((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1 == 2)) {
      uVar5 = GetCmdPkt__6SdrvEEFv(iStack_60);
      iVar3 = (int)uVar5;
      if (piStack_30 == (int *)0x0) {
        *(u32 *)(iVar3 + 0xc) = 0x1307;
      }
      else if (piStack_30 == (int *)0x1) {
        *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xf9 | 6;
        *(u32 *)(iVar3 + 0xc) = 0x1407;
      }
      else if (piStack_30 == (int *)0x2) {
        *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0x1f | 0x20;
        return 0;
      }
      *(u32 **)(iVar3 + 0x10) = puVar7;
      *(ushort *)(iVar3 + 0x14) = *(byte *)(puVar7 + 1) & 0xf;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(iStack_60,uVar5,0,0);
    }
    break;
  case 0xb:
    if ((((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1 == 1) ||
       (((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1 == 2)) {
      scePrintf(0x3ff610,((ulong)*(byte *)((int)puVar7 + 5) & 7) >> 1,param_4);
      uVar5 = GetCmdPkt__6SdrvEEFv(iStack_60);
      iVar3 = (int)uVar5;
      *(u32 *)(iVar3 + 0xc) = 0xb07;
      *(ushort *)(iVar3 + 0x10) = *(byte *)(puVar7 + 1) & 0xf;
      *(short *)(iVar3 + 0x12) = (short)piStack_30;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(iStack_60,uVar5,0,0);
    }
  }
  return 0;
}

/* ---- 0x00375720 size 0xfc  SdrvEE::Pause(Ui)
 *      mangled: Pause__6SdrvEEFUi */
void Pause__6SdrvEEFUi(byte *param_1,int param_2)

{
  bool bVar1;
  long lVar2;
  
  bVar1 = false;
  if ((param_2 == 0) && (((ulong)*param_1 & 0x3f) >> 4 == 0)) {
    *param_1 = *param_1 & 0xcf | 0x10;
    bVar1 = true;
  }
  else if ((param_2 != 0) && (((ulong)*param_1 & 0x3f) >> 4 == 2)) {
    *param_1 = *param_1 & 0xcf | 0x30;
    bVar1 = true;
  }
  if ((bVar1) && (lVar2 = isInQ__6SdrvEEFv(param_1), lVar2 == 0)) {
    CmdPause__6SdrvEEFv(param_1);
  }
  return;
}

/* ---- 0x00375820 size 0x38  SdrvEE::isInQ(v)
 *      mangled: isInQ__6SdrvEEFv */
bool isInQ__6SdrvEEFv(int param_1)

{
  return *(short *)(param_1 + 0x4a) != *(short *)(param_1 + 0x4c);
}

/* ---- 0x00375860 size 0x104  SdrvEE::PlayBGM(UiiiP9_BgmParam)
 *      mangled: PlayBGM__6SdrvEEFUiiiP9_BgmParam */
u32
PlayBGM__6SdrvEEFUiiiP9_BgmParam
          (u32 param_1,u32 param_2,u32 param_3,u32 param_4,void *param_5
          )

{
  long lVar1;
  int iVar2;
  u8 uStack_70;
  u8 uStack_6f;
  u16 uStack_6c;
  u32 uStack_54;
  u32 uStack_50;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  void *pvStack_10;
  
  uStack_50 = param_1;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  pvStack_10 = param_5;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_54,0xe,2);
  if (lVar1 == 0) {
    uStack_54 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u32 *)(iVar2 + 4) = uStack_40;
    *(short *)(iVar2 + 8) = (short)uStack_30;
    *(short *)(iVar2 + 10) = (short)uStack_20;
    if (pvStack_10 == (void *)0x0) {
      memset(&uStack_70,0,0x10);
      uStack_70 = 0x7f;
      uStack_6f = 0x40;
      uStack_6c = 1000;
      memcpy((void *)(iVar2 + 0x10),&uStack_70,0x10);
    }
    else {
      memcpy((void *)(iVar2 + 0x10),pvStack_10,0x10);
    }
    InvokeReqHandler__6SdrvEEFUi(uStack_50,uStack_54);
  }
  return uStack_54;
}

/* ---- 0x00375970 size 0x9c  SdrvEE::StopBGM(Uiii)
 *      mangled: StopBGM__6SdrvEEFUiii */
u32
StopBGM__6SdrvEEFUiii(u32 param_1,u32 param_2,u32 param_3,u32 param_4)

{
  long lVar1;
  int iVar2;
  u32 uStack_44;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_44,0x11,1);
  if (lVar1 == 0) {
    uStack_44 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 2) = 4;
    *(u32 *)(iVar2 + 4) = uStack_30;
    *(u32 *)(iVar2 + 8) = uStack_20;
    *(u32 *)(iVar2 + 0xc) = uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_40,uStack_44);
  }
  return uStack_44;
}

/* ---- 0x00375a10 size 0x8c  SdrvEE::ReleaseBGM(Uii)
 *      mangled: ReleaseBGM__6SdrvEEFUii */
u32 ReleaseBGM__6SdrvEEFUii(u32 param_1,u32 param_2,u32 param_3)

{
  long lVar1;
  int iVar2;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  uStack_10 = param_3;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_34,0x11,1);
  if (lVar1 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 2) = 5;
    *(u32 *)(iVar2 + 4) = uStack_20;
    *(u32 *)(iVar2 + 8) = uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_30,uStack_34);
  }
  return uStack_34;
}

/* ---- 0x00375aa0 size 0x8c  SdrvEE::SetSEParam(UiP8_SeParam)
 *      mangled: SetSEParam__6SdrvEEFUiP8_SeParam */
u32 SetSEParam__6SdrvEEFUiP8_SeParam(u32 param_1,u32 param_2,void *param_3)

{
  long lVar1;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  void *pvStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  pvStack_10 = param_3;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_34,10,2);
  if (lVar1 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_20;
    memcpy((void *)((int)lVar1 + 0x10),pvStack_10,0x10);
    InvokeReqHandler__6SdrvEEFUi(uStack_30,uStack_34);
  }
  return uStack_34;
}

/* ---- 0x00375b30 size 0xac  SdrvEE::SetSEParam(Uiiii)
 *      mangled: SetSEParam__6SdrvEEFUiiii */
u32
SetSEParam__6SdrvEEFUiiii
          (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
          u32 param_5)

{
  long lVar1;
  int iVar2;
  u32 uStack_54;
  u32 uStack_50;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_50 = param_1;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  uStack_10 = param_5;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_54,10,1);
  if (lVar1 == 0) {
    uStack_54 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 2) = 1;
    *(u32 *)(iVar2 + 4) = uStack_40;
    *(short *)(iVar2 + 8) = (short)uStack_30;
    *(short *)(iVar2 + 10) = (short)uStack_20;
    *(short *)(iVar2 + 0xc) = (short)uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_50,uStack_54);
  }
  return uStack_54;
}

/* ---- 0x00375be0 size 0x8c  SdrvEE::SetBGMParam(UiP9_BgmParam)
 *      mangled: SetBGMParam__6SdrvEEFUiP9_BgmParam */
u32 SetBGMParam__6SdrvEEFUiP9_BgmParam(u32 param_1,u32 param_2,void *param_3)

{
  long lVar1;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_20;
  void *pvStack_10;
  
  uStack_30 = param_1;
  uStack_20 = param_2;
  pvStack_10 = param_3;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_34,0xf,2);
  if (lVar1 == 0) {
    uStack_34 = 0xffffffff;
  }
  else {
    *(u32 *)((int)lVar1 + 4) = uStack_20;
    memcpy((void *)((int)lVar1 + 0x10),pvStack_10,0x10);
    InvokeReqHandler__6SdrvEEFUi(uStack_30,uStack_34);
  }
  return uStack_34;
}

/* ---- 0x00375c70 size 0xac  SdrvEE::SetBGMParam(Uiiii)
 *      mangled: SetBGMParam__6SdrvEEFUiiii */
u32
SetBGMParam__6SdrvEEFUiiii
          (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
          u32 param_5)

{
  long lVar1;
  int iVar2;
  u32 uStack_54;
  u32 uStack_50;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_50 = param_1;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  uStack_10 = param_5;
  lVar1 = GetReqS__6SdrvEEFPUiiUi(param_1,&uStack_54,0xf,1);
  if (lVar1 == 0) {
    uStack_54 = 0xffffffff;
  }
  else {
    iVar2 = (int)lVar1;
    *(u16 *)(iVar2 + 2) = 1;
    *(u32 *)(iVar2 + 4) = uStack_40;
    *(short *)(iVar2 + 8) = (short)uStack_30;
    *(short *)(iVar2 + 10) = (short)uStack_20;
    *(short *)(iVar2 + 0xc) = (short)uStack_10;
    InvokeReqHandler__6SdrvEEFUi(uStack_50,uStack_54);
  }
  return uStack_54;
}

/* ---- 0x00375d20 size 0x12c  SdrvEE::InvokeReqHandler(Ui)
 *      mangled: InvokeReqHandler__6SdrvEEFUi */
uint InvokeReqHandler__6SdrvEEFUi(byte *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  
  lVar4 = isInQ__6SdrvEEFv(param_1);
  if (lVar4 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = GetCurReqHandle__6SdrvEEFi(param_1,0xffffffffffffffff);
    if (param_2 == iVar2) {
      uVar3 = GetHCount__3GsxFv();
      *(u32 *)(param_1 + 0xc0) = uVar3;
      param_1[0xc4] = 1;
      param_1[0xc5] = 0;
      param_1[0xc6] = 0;
      param_1[199] = 0;
      lVar4 = HandleCurReq__6SdrvEEFv(param_1);
      if (lVar4 == 1) {
        *param_1 = *param_1 & 0xfd | 2;
      }
      uVar1 = (uint)(lVar4 != 0);
    }
    else {
      *param_1 = *param_1 & 0xfd | 2;
      uVar1 = 2;
    }
  }
  return uVar1;
}

/* ---- 0x00375e90 size 0x190  SdrvEE::InvokeReqHandlerA(Uii)
 *      mangled: InvokeReqHandlerA__6SdrvEEFUii */
uint InvokeReqHandlerA__6SdrvEEFUii(byte *param_1,int param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  
  lVar4 = isInQ__Q26SdrvEE11_TransReqWkFv(param_1 + param_3 * 8 + 4);
  if (lVar4 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = GetCurReqHandle__6SdrvEEFi(param_1,param_3);
    if (param_2 == iVar2) {
      uVar3 = GetHCount__3GsxFv();
      *(u32 *)(param_1 + 0xc0) = uVar3;
      param_1[0xc4] = 1;
      param_1[0xc5] = 0;
      param_1[0xc6] = 0;
      param_1[199] = 0;
      lVar4 = HandleCurReqA__6SdrvEEFPQ26SdrvEE11_TransReqWk(param_1,param_1 + param_3 * 8 + 4);
      if (lVar4 == 1) {
        *param_1 = *param_1 & 0xf3 |
                   (byte)(((uint)(((ulong)*param_1 << 0x3c) >> 0x3e) | 1 << (param_3 & 0x1f) & 3U)
                         << 2);
      }
      uVar1 = (uint)(lVar4 != 0);
    }
    else {
      *param_1 = *param_1 & 0xf3 |
                 (byte)(((uint)(((ulong)*param_1 << 0x3c) >> 0x3e) | 1 << (param_3 & 0x1f) & 3U) <<
                       2);
      uVar1 = 2;
    }
  }
  return uVar1;
}

/* ---- 0x00376020 size 0x38  isInQ__Q26SdrvEE11_TransReqWkFv
 *      mangled: isInQ__Q26SdrvEE11_TransReqWkFv */
bool isInQ__Q26SdrvEE11_TransReqWkFv(char *param_1)

{
  return param_1[1] != *param_1;
}

/* ---- 0x00376060 size 0x11c  SdrvEE::GetCurReqHandle(i)
 *      mangled: GetCurReqHandle__6SdrvEEFi */
uint GetCurReqHandle__6SdrvEEFi(int param_1,int param_2)

{
  long lVar1;
  u8 *puVar2;
  u32 uStack_24;
  
  if (param_2 < 0) {
    lVar1 = isInQ__6SdrvEEFv(param_1);
    if (lVar1 == 0) {
      uStack_24 = 0xffffffff;
    }
    else {
      puVar2 = (u8 *)
               (*(int *)(param_1 + 0x40) +
               (*(ushort *)(*(int *)(param_1 + 0x44) + (uint)*(ushort *)(param_1 + 0x4a) * 2) &
               0x3ff) * 0x10);
      uStack_24 = (uint)CONCAT12(puVar2[1],CONCAT11(*puVar2,(char)*(u16 *)(param_1 + 0x4a)));
    }
  }
  else {
    param_1 = param_1 + param_2 * 8;
    lVar1 = isInQ__Q26SdrvEE11_TransReqWkFv(param_1 + 4);
    if (lVar1 == 0) {
      uStack_24 = 0xffffffff;
    }
    else {
      uStack_24 = *(uint *)(*(int *)(param_1 + 8) + (uint)*(byte *)(param_1 + 5) * 0x10);
    }
  }
  return uStack_24;
}

/* ---- 0x00376180 size 0x294  SdrvEE::HandleCurReq(v)
 *      mangled: HandleCurReq__6SdrvEEFv */
u64 HandleCurReq__6SdrvEEFv(int param_1)

{
  char cVar1;
  u32 uVar2;
  u64 uVar3;
  
  while( true ) {
    if (*(int *)(param_1 + 0x58) == 0) {
      memset((void *)(param_1 + 0x50),0,0x20);
      uVar2 = GetCurReqHandle__6SdrvEEFi(param_1,0xffffffffffffffff);
      *(u32 *)(param_1 + 0x50) = uVar2;
      *(uint *)(param_1 + 0x58) =
           *(int *)(param_1 + 0x40) +
           (*(ushort *)(*(int *)(param_1 + 0x44) + (uint)*(ushort *)(param_1 + 0x4a) * 2) & 0x3ff) *
           0x10;
    }
    cVar1 = **(char **)(param_1 + 0x58);
    if (cVar1 == '\x14') {
      uVar3 = CmdTest__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\x11') {
      uVar3 = CmdBgm__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\x10') {
      uVar3 = CmdBgmStat__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\x0f') {
      uVar3 = CmdBgmParam__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\x0e') {
      uVar3 = CmdBgmPlay__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\r') {
      uVar3 = CmdSeRelease__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\v') break;
    if (cVar1 == '\n') {
      uVar3 = CmdSeParam__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\t') {
      uVar3 = CmdSePlay__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\b') {
      uVar3 = CmdEEStreaming__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 == '\x02') {
      uVar3 = CmdSetMode__6SdrvEEFv(param_1);
      return uVar3;
    }
    if (cVar1 != '\x01') {
      return 0;
    }
    UpdateReqRp__6SdrvEEFv(param_1);
    if (*(short *)(param_1 + 0x4a) == *(short *)(param_1 + 0x4c)) {
      return 0;
    }
  }
  uVar3 = CmdSeStat__6SdrvEEFv(param_1);
  return uVar3;
}

/* ---- 0x00376420 size 0x144  SdrvEE::HandleCurReqA(PQ26SdrvEE11_TransReqWk)
 *      mangled: HandleCurReqA__6SdrvEEFPQ26SdrvEE11_TransReqWk */
u64 HandleCurReqA__6SdrvEEFPQ26SdrvEE11_TransReqWk(u32 param_1,char *param_2)

{
  u64 uVar1;
  u32 *puVar2;
  char cStack_23;
  
  while( true ) {
    puVar2 = (u32 *)(*(int *)(param_2 + 4) + (uint)(byte)param_2[1] * 0x10);
    cStack_23 = (char)((uint)*puVar2 >> 8);
    if (cStack_23 == '\a') {
      uVar1 = CmdTransWaveData__6SdrvEEFPQ26SdrvEE12_SdrTransReq(param_1,puVar2);
      return uVar1;
    }
    if (cStack_23 == '\x05') {
      uVar1 = CmdReleaseSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq(param_1,puVar2);
      return uVar1;
    }
    if (cStack_23 == '\x04') {
      uVar1 = CmdLoadSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq(param_1,puVar2);
      return uVar1;
    }
    if (cStack_23 == '\x03') break;
    if (cStack_23 != '\x01') {
      return 0;
    }
    UpdateTransReq__6SdrvEEFi(param_1,1);
    if (param_2[1] == *param_2) {
      return 0;
    }
  }
  uVar1 = CmdAutoLoad__6SdrvEEFPQ26SdrvEE13_SdrTransReqA(param_1,puVar2);
  return uVar1;
}

/* ---- 0x00376570 size 0x6c  SdrvEE::CheckTimer(v)
 *      mangled: CheckTimer__6SdrvEEFv */
bool CheckTimer__6SdrvEEFv(int param_1)

{
  bool bVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0xc4) == 0) {
    bVar1 = true;
  }
  else {
    iVar2 = GetHCount__3GsxFv();
    bVar1 = *(uint *)(param_1 + 0xc4) <= (uint)(iVar2 - *(int *)(param_1 + 0xc0));
  }
  return bVar1;
}

/* ---- 0x003765e0 size 0x78  SdhFindBlock(PUcPCcUi)
 *      mangled: SdhFindBlock__FPUcPCcUi */
void * SdhFindBlock__FPUcPCcUi(void *param_1,void *param_2,void *param_3)

{
  int iVar1;
  void *pvStack_30;
  
  pvStack_30 = param_1;
  do {
    iVar1 = memcmp(pvStack_30,param_2,2);
    if (iVar1 == 0) {
      return pvStack_30;
    }
    pvStack_30 = (void *)SdhNextBlock__FPUc(pvStack_30);
  } while (pvStack_30 < param_3);
  return (void *)0x0;
}

/* ---- 0x00376660 size 0x70  SdhNextBlock(PUc)
 *      mangled: SdhNextBlock__FPUc */
void * SdhNextBlock__FPUc(void *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = memcmp(param_1,&_1938,2);
  if (iVar1 == 0) {
    uVar2 = *(uint *)((int)param_1 + 4);
  }
  else {
    uVar2 = (uint)*(ushort *)((int)param_1 + 4);
  }
  return (void *)((int)param_1 + uVar2 * 0x10);
}

/* ---- 0x003766d0 size 0x12c  WaveBankToAddr(Ui)
 *      mangled: WaveBankToAddr__FUi */
uint WaveBankToAddr__FUi(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  u16 *puVar3;
  
  if (param_1 >> 0x1c != 0) {
    uVar2 = param_1 >> 0x18 & 0xf;
    if (param_1 >> 0x1c == 1) {
      if (uVar2 == 8) {
        puVar3 = &Spu2MemB8;
      }
      else {
        puVar3 = *(u16 **)(Spu2MemBTbl + uVar2 * 4);
      }
      param_1 = (uint)(ushort)puVar3[param_1 & 0xf] * 0x100 + 0x8000;
    }
    else {
      uVar1 = Spu2MemB8;
      if (uVar2 != 8) {
        uVar1 = **(ushort **)(Spu2MemBTbl + uVar2 * 4);
      }
      param_1 = (uint)uVar1 * 0x100 + (param_1 & 0xfffff0);
    }
  }
  return param_1;
}

/* ---- 0x00376800 size 0x1a8  SdrvEE::GetWaveBank(Pv)
 *      mangled: GetWaveBank__6SdrvEEFPv */
int GetWaveBank__6SdrvEEFPv(u64 param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar6 = param_2 + (uint)*(byte *)(param_2 + 8) * 0x10;
  uVar5 = param_2 + (*(uint *)(param_2 + 8) >> 8) * 0x10;
  lVar2 = SdhFindBlock__FPUcPCcUi(uVar6,0x3ff590,uVar5);
  if (lVar2 == 0) {
    iVar3 = -1;
  }
  else {
    iVar3 = (int)lVar2;
    uVar1 = *(uint *)(iVar3 + 0xc);
    if (*(int *)(iVar3 + 0xc) == 0) {
      do {
        lVar2 = SdhFindBlock__FPUcPCcUi(uVar6,0x3ff660,uVar5);
        if (lVar2 == 0) {
          return -1;
        }
        iVar4 = (int)lVar2;
        if (((uint)*(ushort *)(iVar4 + 10) == *(uint *)(iVar3 + 8)) && (*(int *)(iVar4 + 0xc) != 0))
        {
          uVar1 = *(uint *)(iVar4 + 0xc);
          goto LAB_00376928;
        }
        uVar6 = SdhNextBlock__FPUc(uVar6);
      } while (uVar6 < uVar5);
      iVar3 = -1;
    }
    else {
LAB_00376928:
      if (uVar1 >> 0x1c == 0) {
        iVar3 = 0;
      }
      else if (uVar1 >> 0x1c == 1) {
        iVar3 = (uVar1 >> 0x14 & 0xf0) + (uVar1 & 0xf);
      }
      else {
        iVar3 = (uVar1 >> 0x14 & 0xf0) + 0xf;
      }
    }
  }
  return iVar3;
}

/* ---- 0x003769b0 size 0xf0  SdrvEE::GetWaveTransAddr(P12_WaveDataHdrPUcUi)
 *      mangled: GetWaveTransAddr__6SdrvEEFP12_WaveDataHdrPUcUi */
u64
GetWaveTransAddr__6SdrvEEFP12_WaveDataHdrPUcUi
          (int param_1,int param_2,uint param_3,u32 param_4)

{
  int iVar1;
  u64 uVar2;
  uint uStack_20;
  
  uStack_20 = param_3;
  if (*(int *)(param_2 + 0xc) == 0) {
    do {
      iVar1 = SdhFindBlock__FPUcPCcUi(uStack_20,0x3ff660,param_4);
      if (iVar1 == 0) break;
      if ((uint)*(ushort *)(iVar1 + 10) == *(uint *)(param_2 + 8)) {
        if (*(int *)(iVar1 + 0xc) != 0) {
          uVar2 = WaveBankToAddr__FUi(*(u32 *)(iVar1 + 0xc));
          return uVar2;
        }
        break;
      }
      uStack_20 = SdhNextBlock__FPUc(iVar1);
    } while (uStack_20 < *(uint *)(param_1 + 100));
    uVar2 = 0;
  }
  else {
    uVar2 = WaveBankToAddr__FUi(*(u32 *)(param_2 + 0xc));
  }
  return uVar2;
}

/* ---- 0x00376aa0 size 0xa8  SdrvEE::SetSeOverlap(UiUi)
 *      mangled: SetSeOverlap__6SdrvEEFUiUi */
void SetSeOverlap__6SdrvEEFUiUi(int param_1,int param_2,u32 param_3)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0xf < iVar1) {
      return;
    }
    if (*(int *)(param_1 + iVar1 * 8 + 0xe4) == -1) break;
    iVar1 = iVar1 + 1;
  }
  *(uint *)(param_1 + iVar1 * 8 + 0xe4) = (uint)((ulong)((long)param_2 << 0x26) >> 0x26);
  *(u32 *)(param_1 + iVar1 * 8 + 0xe8) = param_3;
  return;
}

/* ---- 0x00376b50 size 0xa8  SdrvEE::ClrSeOverlap(Ui)
 *      mangled: ClrSeOverlap__6SdrvEEFUi */
void ClrSeOverlap__6SdrvEEFUi(int param_1,int param_2)

{
  int iVar1;
  char cStack_23;
  
  cStack_23 = (char)((uint)param_2 >> 8);
  if (cStack_23 == '\t') {
    for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
      if (*(uint *)(param_1 + iVar1 * 8 + 0xe4) == (uint)((ulong)((long)param_2 << 0x26) >> 0x26)) {
        *(u32 *)(param_1 + iVar1 * 8 + 0xe4) = 0xffffffff;
        return;
      }
    }
  }
  return;
}

/* ---- 0x00376c00 size 0xec  SdrvEE::ChkSeOverlap(Ui)
 *      mangled: ChkSeOverlap__6SdrvEEFUi */
bool ChkSeOverlap__6SdrvEEFUi(int param_1,int param_2)

{
  long lVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (0xf < iVar2) {
      return false;
    }
    if ((*(int *)(param_1 + iVar2 * 8 + 0xe4) != -1) &&
       (*(int *)(param_1 + iVar2 * 8 + 0xe8) == param_2)) break;
    iVar2 = iVar2 + 1;
  }
  lVar1 = FindResult__6SdrvEEFUi(param_1,*(u32 *)(param_1 + iVar2 * 8 + 0xe4));
  if (lVar1 != 0) {
    *(u32 *)((int)lVar1 + 4) = 0xffffffff;
  }
  *(u32 *)(param_1 + iVar2 * 8 + 0xe4) = 0xffffffff;
  return lVar1 != 0;
}

/* ---- 0x00376cf0 size 0x568  SdrvEE::Receive(P11_SdrvCmdPktP6SdrvEE)
 *      mangled: Receive__6SdrvEEFP11_SdrvCmdPktP6SdrvEE */
void Receive__6SdrvEEFP11_SdrvCmdPktP6SdrvEE(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  size_t __n;
  uint uVar4;
  
  uVar4 = *(uint *)(param_1 + 0xc);
  uVar2 = uVar4 & 0xff;
  if (uVar2 == 0x17) {
    if ((*(uint *)(param_1 + 0xc) >> 8 & 0xff) == 0) {
      __n = strlen(&logBuf);
      memcpy(logWp,&logBuf,__n);
      logWp = logWp + (int)__n;
    }
  }
  else if (uVar2 == 0x10) {
    *(u32 *)(param_2 + 0xd0) = *(u32 *)(param_1 + 0x10);
    *(u32 *)(param_2 + 0xd4) = *(u32 *)(param_1 + 0x14);
    *(u32 *)(param_2 + 0xd8) = *(u32 *)(param_1 + 0x18);
  }
  else if (uVar2 == 0x14) {
    (**(code **)(param_1 + 0x14))
              (uVar4 >> 8,*(u32 *)(param_1 + 0x10),*(u32 *)(param_1 + 0x18));
  }
  else if (uVar2 == 0x13) {
    if ((uVar4 >> 8 & 3) == 1) {
      **(byte **)(param_1 + 0x1c) = **(byte **)(param_1 + 0x1c) | 1;
    }
    else {
      uVar2 = (**(code **)(param_1 + 0x1c))
                        (*(u32 *)(param_1 + 0x10),*(u32 *)(param_1 + 0x14),
                         (int)uVar4 >> 0xc & 0xffff,*(u32 *)(param_1 + 0x18));
      if (uVar2 == 0xffffffff) {
        uVar2 = uVar4 >> 8 & 8 ^ 8;
      }
      if (uVar2 == 0) {
        iReleaseBGM__6SdrvEEFUi(param_2,*(u32 *)(param_1 + 0x14));
      }
    }
  }
  else if (uVar2 == 0x12) {
    if ((*(int *)(param_1 + 0x1c) == *(int *)(param_2 + 0x34)) ||
       (lVar3 = ChkSeOverlap__6SdrvEEFUi(param_2,*(u32 *)(param_1 + 0x18)), lVar3 != 0)) {
      if ((uVar4 >> 0x10 & 8) == 8) {
        iReleaseSE__6SdrvEEFUi(param_2,*(u32 *)(param_1 + 0x18));
      }
      *(u8 *)(param_2 + 0x5e) = 2;
    }
    else if ((uVar4 >> 0x10 & 3) == 1) {
      **(byte **)(param_1 + 0x14) = **(byte **)(param_1 + 0x14) | 1;
    }
    else {
      uVar2 = (**(code **)(param_1 + 0x14))
                        (*(u32 *)(param_1 + 0x10),*(u32 *)(param_1 + 0x18));
      if (uVar2 == 0xffffffff) {
        uVar2 = uVar4 >> 0x10 & 8 ^ 8;
      }
      if (uVar2 == 0) {
        iReleaseSE__6SdrvEEFUi(param_2,*(u32 *)(param_1 + 0x18));
      }
    }
  }
  else if (uVar2 == 0x11) {
    *(u8 *)(param_2 + (uVar4 >> 8) + 0xcc) = 0;
  }
  else if (uVar2 == 2) {
    iVar1 = *(int *)(param_1 + 0x1c);
    if ((uVar4 >> 8 & 0xff) == 0) {
      *(u32 *)(iVar1 + 0x30) = *(u32 *)(param_1 + 0x10);
      *(u32 *)(iVar1 + 0x34) = *(u32 *)(param_1 + 0x18);
      *(u16 *)(iVar1 + 0x38) = *(u16 *)(param_1 + 0x14);
    }
    *(char *)(iVar1 + 6) = *(char *)(iVar1 + 6) + '\x01';
  }
  else if (uVar2 == 4) {
    iVar1 = *(int *)(param_1 + 0x18);
    uVar4 = uVar4 >> 8 & 0xff;
    if (uVar4 == 5) {
      *(uint *)(iVar1 + 8) =
           *(uint *)(iVar1 + 8) & 0xff000000 |
           (uint)((ulong)((long)*(int *)(param_1 + 0x14) << 0x28) >> 0x28);
      *(uint *)(iVar1 + 0xc) =
           *(uint *)(iVar1 + 0xc) & 0xff000000 |
           (uint)((ulong)((long)*(int *)(param_1 + 0x10) << 0x28) >> 0x28);
    }
    else if (uVar4 == 3) {
      *(u32 *)(iVar1 + 4) = *(u32 *)(param_1 + 0x10);
    }
    else if (uVar4 == 2) {
      *(uint *)(iVar1 + 8) =
           *(uint *)(iVar1 + 8) & 0xff000000 |
           (uint)((ulong)((long)*(int *)(param_1 + 0x14) << 0x28) >> 0x28);
    }
    *(char *)(iVar1 + 0xf) = *(char *)(iVar1 + 0xf) + '\x01';
  }
  else if (uVar2 == 1) {
    m_cmdReg = *(int *)(param_1 + 0x10);
    DAT_00422144 = *(u32 *)(param_1 + 0x14);
    DAT_00422148 = *(u32 *)(param_1 + 0x18);
    DAT_0042214c = *(u32 *)(param_1 + 0x1c);
    CheckResType__6SdrvEEFUi(param_2,uVar4 >> 8 & 0xff);
  }
  else if (uVar2 == 0) {
    m_cmdReg = (int)(short)(uVar4 >> 0x10);
    CheckResType__6SdrvEEFUi(param_2,uVar4 >> 8 & 0xff);
  }
  SYNC(0);
  EI();
  return;
}

/* ---- 0x00377260 size 0x64  SdrvEE::UpdateReqRp(Ui)
 *      mangled: UpdateReqRp__6SdrvEEFUi */
void UpdateReqRp__6SdrvEEFUi(u32 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetCurReqHandle__6SdrvEEFi(param_1,0xffffffffffffffff);
  if ((iVar1 != -1) && (iVar1 == param_2)) {
    UpdateReqRp__6SdrvEEFv(param_1);
  }
  return;
}

/* ---- 0x003772d0 size 0x11c  SdrvEE::UpdateReqRp(v)
 *      mangled: UpdateReqRp__6SdrvEEFv */
void UpdateReqRp__6SdrvEEFv(int param_1)

{
  uint uVar1;
  byte *pbVar2;
  ushort *puVar3;
  
  *(u32 *)(param_1 + 0x58) = 0;
  puVar3 = (ushort *)(*(int *)(param_1 + 0x44) + (uint)*(ushort *)(param_1 + 0x4a) * 2);
  uVar1 = (uint)*puVar3;
  if (*(ushort *)(param_1 + 0x48) == 0) {
    trap(7);
  }
  *(short *)(param_1 + 0x4a) =
       (short)((*(ushort *)(param_1 + 0x4a) + 1) % (uint)*(ushort *)(param_1 + 0x48));
  pbVar2 = (byte *)(*(int *)(param_1 + 0x3c) + ((uVar1 & 0x3ff) >> 3));
  uVar1 = ~((1 << ((uint)(((ulong)*(byte *)((int)puVar3 + 1) << 0x38) >> 0x3a) & 0x1f)) + -1 <<
           (uVar1 & 7));
  *pbVar2 = *pbVar2 & (byte)uVar1;
  pbVar2[1] = pbVar2[1] & (byte)(uVar1 >> 8);
  pbVar2[2] = pbVar2[2] & (byte)(uVar1 >> 0x10);
  pbVar2[3] = pbVar2[3] & (byte)(uVar1 >> 0x18);
  return;
}

/* ---- 0x003773f0 size 0x6c  SdrvEE::UpdateTransReq(i)
 *      mangled: UpdateTransReq__6SdrvEEFi */
void UpdateTransReq__6SdrvEEFi(int param_1,int param_2)

{
  param_1 = param_1 + param_2 * 8;
  if (*(byte *)(param_1 + 6) == 0) {
    trap(7);
  }
  *(char *)(param_1 + 5) = (char)((*(byte *)(param_1 + 5) + 1) % (uint)*(byte *)(param_1 + 6));
  return;
}

/* ---- 0x00377460 size 0x98  SdrvEE::CmdSetMode(v)
 *      mangled: CmdSetMode__6SdrvEEFv */
u64 CmdSetMode__6SdrvEEFv(int param_1)

{
  int iVar1;
  u64 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x58);
  uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
  iVar3 = (int)uVar2;
  *(uint *)(iVar3 + 0xc) = (uint)*(ushort *)(iVar1 + 2) * 0x100 + 8;
  *(u32 *)(iVar3 + 0x10) = *(u32 *)(iVar1 + 4);
  *(u32 *)(iVar3 + 0x14) = *(u32 *)(iVar1 + 8);
  *(u32 *)(iVar3 + 0x18) = *(u32 *)(iVar1 + 0xc);
  SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0,1);
  UpdateReqRp__6SdrvEEFv(param_1);
  return 0;
}

/* ---- 0x00377500 size 0x1b8  SdrvEE::CmdLoadSDH(PQ26SdrvEE12_SdrTransReq)
 *      mangled: CmdLoadSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq */
u32 CmdLoadSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq(u32 param_1,u32 *param_2)

{
  char cVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  
  do {
    cVar1 = *(char *)((int)param_2 + 0xf);
    if (cVar1 == '\x04') {
      SetResult__6SdrvEEFUiUiUi(param_1,*param_2,1,param_2[2] & 0xffffff);
      UpdateTransReq__6SdrvEEFi(param_1,1);
      return 0;
    }
    if (cVar1 == '\x02') {
LAB_003775c8:
      uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
      *(u32 *)((int)uVar2 + 0xc) = 3;
      *(u32 **)((int)uVar2 + 0x1c) = param_2;
      *(u8 *)((int)param_2 + 0xf) = 3;
      SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii
                (param_1,uVar2,param_2[1],param_2[2] & 0xffffff,param_2[3] & 0xffffff,0,0);
    }
    else if (cVar1 == '\0') {
      if ((param_2[2] & 0xffffff) != 0) goto LAB_003775c8;
      uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar4 = (int)uVar2;
      *(u32 *)(iVar4 + 0xc) = 2;
      *(uint *)(iVar4 + 0x10) = (uint)((ulong)((long)(int)param_2[3] << 0x28) >> 0x28);
      *(u32 **)(iVar4 + 0x1c) = param_2;
      *(u8 *)((int)param_2 + 0xf) = 1;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0,0);
    }
    lVar3 = CheckTimer__6SdrvEEFv(param_1);
    if (lVar3 != 0) {
      return 1;
    }
  } while( true );
}

/* ---- 0x003776c0 size 0xec  SdrvEE::CmdReleaseSDH(PQ26SdrvEE12_SdrTransReq)
 *      mangled: CmdReleaseSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq */
u32 CmdReleaseSDH__6SdrvEEFPQ26SdrvEE12_SdrTransReq(u32 param_1,int param_2)

{
  u64 uVar1;
  long lVar2;
  int iVar3;
  
  do {
    if (*(char *)(param_2 + 0xf) == '\x02') {
      UpdateTransReq__6SdrvEEFi(param_1,1);
      return 0;
    }
    if (*(char *)(param_2 + 0xf) == '\0') {
      uVar1 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar3 = (int)uVar1;
      *(u32 *)(iVar3 + 0xc) = 4;
      *(u32 *)(iVar3 + 0x10) = 0;
      *(u32 *)(iVar3 + 0x14) = *(u32 *)(param_2 + 4);
      *(int *)(iVar3 + 0x1c) = param_2;
      *(u8 *)(param_2 + 0xf) = 1;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar1,0,0);
    }
    lVar2 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar2 == 0);
  return 1;
}

/* ---- 0x003777b0 size 0x2ac  SdrvEE::CmdTransWaveData(PQ26SdrvEE12_SdrTransReq)
 *      mangled: CmdTransWaveData__6SdrvEEFPQ26SdrvEE12_SdrTransReq */
u32 CmdTransWaveData__6SdrvEEFPQ26SdrvEE12_SdrTransReq(int param_1,u32 *param_2)

{
  char cVar1;
  u32 uVar2;
  u64 uVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  
LAB_003777d0:
  do {
    cVar1 = *(char *)((int)param_2 + 0xf);
    if (cVar1 == '\x03') {
      if (*(char *)(param_1 + *(int *)(param_1 + 200) + 0xcc) == '\0') {
        SetResult__6SdrvEEFUiUiUi(param_1,*param_2,1,0);
        UpdateTransReq__6SdrvEEFi(param_1,1);
      }
      return 0;
    }
    if (cVar1 == '\x02') {
      if ((param_2[3] & 0xffffff) != 0) {
        *(uint *)(param_1 + 200) = *(int *)(param_1 + 200) + 1U & 1;
        *(u8 *)((int)param_2 + 0xf) = 0;
        goto LAB_003777d0;
      }
      *(char *)((int)param_2 + 0xf) = *(char *)((int)param_2 + 0xf) + '\x01';
    }
    else if ((cVar1 == '\0') && (*(char *)(param_1 + *(int *)(param_1 + 200) + 0xcc) == '\0')) {
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar6 = (int)uVar3;
      *(uint *)(iVar6 + 0xc) = *(int *)(param_1 + 200) << 0x10 | 6;
      *(uint *)(iVar6 + 0x10) = (uint)((ulong)((long)(int)param_2[2] << 0x28) >> 0x28);
      *(u32 **)(iVar6 + 0x1c) = param_2;
      uVar5 = param_2[3] & 0xffffff;
      if (*(uint *)(param_1 + 0xd8) < uVar5) {
        uVar5 = *(uint *)(param_1 + 0xd8);
      }
      uVar2 = *(u32 *)(param_1 + *(int *)(param_1 + 200) * 4 + 0xd0);
      *(char *)((int)param_2 + 0xf) = *(char *)((int)param_2 + 0xf) + '\x01';
      *(u8 *)(param_1 + *(int *)(param_1 + 200) + 0xcc) = 1;
      SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii(param_1,uVar3,param_2[1],uVar2,uVar5,0,0);
      param_2[1] = param_2[1] + uVar5;
      param_2[2] = param_2[2] & 0xff000000 |
                   (uint)((ulong)((long)(int)((uint)((ulong)((long)(int)param_2[2] << 0x28) >> 0x28)
                                             + uVar5) << 0x28) >> 0x28);
      param_2[3] = param_2[3] & 0xff000000 |
                   (uint)((ulong)((long)(int)((uint)((ulong)((long)(int)param_2[3] << 0x28) >> 0x28)
                                             - uVar5) << 0x28) >> 0x28);
    }
    lVar4 = CheckTimer__6SdrvEEFv(param_1);
    if (lVar4 != 0) {
      return 1;
    }
  } while( true );
}

/* ---- 0x00377a60 size 0x5cc  SdrvEE::CmdAutoLoad(PQ26SdrvEE13_SdrTransReqA)
 *      mangled: CmdAutoLoad__6SdrvEEFPQ26SdrvEE13_SdrTransReqA */
u32 CmdAutoLoad__6SdrvEEFPQ26SdrvEE13_SdrTransReqA(int param_1,u32 *param_2)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  u32 uVar6;
  u64 uVar7;
  long lVar8;
  int *piVar9;
  int iVar10;
  u8 auStack_40 [4];
  int iStack_3c;
  uint uStack_38;
  int iStack_34;
  int iStack_30;
  uint uStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  u32 *puStack_10;
  
  piVar9 = (int *)(param_1 + 0x14);
  iStack_20 = param_1;
  puStack_10 = param_2;
LAB_00377aa0:
  cVar1 = *(char *)((int)puStack_10 + 0xf);
  if (cVar1 == '\x19') {
LAB_00377f70:
    SetResult__6SdrvEEFUiUiUi(iStack_20,*puStack_10,1,*(u32 *)(param_1 + 0x18));
    UpdateTransReq__6SdrvEEFi(iStack_20,0);
    return 0;
  }
  if (cVar1 == '\t') {
    if (puStack_10[2] == 0) goto LAB_00377f70;
    piVar4 = (int *)puStack_10[2];
    if (*piVar4 == 0x48524453) {
      bVar2 = *(byte *)(piVar4 + 2);
      *(int **)(param_1 + 0x24) = piVar4 + (uint)bVar2 * 4;
      *(int **)(param_1 + 0x1c) = piVar4 + (uint)bVar2 * 4;
      *(int **)(param_1 + 0x20) = piVar4 + ((uint)piVar4[2] >> 8) * 4;
    }
    else {
      iVar10 = puStack_10[2];
      *(int *)(param_1 + 0x24) = iVar10;
      *(int *)(param_1 + 0x1c) = iVar10;
      *(int *)(param_1 + 0x20) = iVar10 + *(int *)(iVar10 + 4) * 0x10;
    }
    *(u8 *)((int)puStack_10 + 0xf) = 0x12;
  }
  else if ((cVar1 == '\x18') || (cVar1 == '\b')) {
LAB_00377ea8:
    uVar6 = SdhNextBlock__FPUc(*(u32 *)(param_1 + 0x24));
    *(u32 *)(param_1 + 0x24) = uVar6;
    *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + -6;
  }
  else if ((cVar1 == '\x16') || (cVar1 == '\x06')) {
    lVar8 = ChkInternalReq__6SdrvEEFUiRUi(iStack_20,*piVar9,auStack_40);
    if (lVar8 == -2) {
LAB_00377fc8:
      SetResult__6SdrvEEFUiUiUi(iStack_20,*puStack_10,1,0xffffffffffffffff);
      UpdateTransReq__6SdrvEEFi(iStack_20,0);
      return 0;
    }
    if (lVar8 == 3) {
      uVar3 = *(uint *)(param_1 + 0x28);
      if ((uVar3 & 1) == 0) goto LAB_00377ea8;
      uVar7 = GetCmdPkt__6SdrvEEFv(iStack_20);
      iVar10 = (int)uVar7;
      *(u32 *)(iVar10 + 0xc) = 0x1010005;
      *(u32 *)(iVar10 + 0x10) = *(u32 *)(*(int *)(param_1 + 0x24) + 8);
      *(uint *)(iVar10 + 0x14) = uVar3 & 0xfffffff0;
      *(u32 *)(iVar10 + 0x18) = *(u32 *)(param_1 + 0x18);
      *(u32 **)(iVar10 + 0x1c) = puStack_10;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(iStack_20,uVar7,0,0);
      *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
    }
  }
  else {
    if ((cVar1 != '\x15') && (cVar1 != '\x05')) {
      if ((cVar1 != '\x14') && (cVar1 != '\x04')) {
        if ((cVar1 == '\x13') || (cVar1 == '\x03')) {
LAB_00377ce0:
          iStack_30 = IopFindWaveAddr__6SdrvEEFUi(iStack_20,*(u32 *)(param_1 + 0x28));
          if (iStack_30 != -1) {
            *piVar9 = iStack_30;
            *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
          }
        }
        else {
          if ((cVar1 != '\x12') && (cVar1 != '\x02')) {
            if (cVar1 == '\x01') {
              iStack_28 = ChkInternalReq__6SdrvEEFUiRUi(iStack_20,*piVar9,param_1 + 0x18);
              if (iStack_28 == -2) goto LAB_00377fc8;
              if (iStack_28 == 3) {
                iVar10 = puStack_10[1];
                iVar5 = iVar10 + (uint)*(byte *)(iVar10 + 8) * 0x10;
                *(int *)(param_1 + 0x24) = iVar5;
                *(int *)(param_1 + 0x1c) = iVar5;
                *(uint *)(param_1 + 0x20) = iVar10 + (*(uint *)(iVar10 + 8) >> 8) * 0x10;
                *(u8 *)((int)puStack_10 + 0xf) = 2;
                goto LAB_00377c38;
              }
            }
            else if ((cVar1 == '\0') &&
                    (iStack_24 = LoadSDH__6SdrvEEFPv(iStack_20,puStack_10[1]), iStack_24 != -1)) {
              *piVar9 = iStack_24;
              *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
            }
            goto LAB_00377fa8;
          }
LAB_00377c38:
          lVar8 = SdhFindBlock__FPUcPCcUi
                            (*(u32 *)(param_1 + 0x24),0x3ff590,
                             *(u32 *)(param_1 + 0x20));
          if (lVar8 == 0) {
            *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\a';
            goto LAB_00377aa0;
          }
          *(int *)(param_1 + 0x24) = (int)lVar8;
          uStack_2c = GetWaveTransAddr__6SdrvEEFP12_WaveDataHdrPUcUi
                                (iStack_20,lVar8,*(u32 *)(param_1 + 0x1c),
                                 *(u32 *)(param_1 + 0x20));
          if (uStack_2c == 0) {
            *(u32 *)(param_1 + 0x28) = *(u32 *)((int)lVar8 + 8);
            *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
            goto LAB_00377ce0;
          }
          *(uint *)(param_1 + 0x28) = uStack_2c | 1;
          *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x03';
        }
        goto LAB_00377fa8;
      }
      iStack_34 = ChkInternalReq__6SdrvEEFUiRUi(iStack_20,*piVar9,param_1 + 0x28);
      if (iStack_34 == -2) goto LAB_00377fc8;
      if (iStack_34 != 3) goto LAB_00377fa8;
      *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
    }
    iVar10 = *(int *)(param_1 + 0x24);
    uStack_38 = *(uint *)(param_1 + 0x28) & 0xfffffff0;
    iStack_3c = TransWaveData__6SdrvEEFUiPUcUi
                          (iStack_20,uStack_38,iVar10 + (uint)*(ushort *)(iVar10 + 2) * 0x10,
                           (*(int *)(iVar10 + 4) - (uint)*(ushort *)(iVar10 + 2)) * 0x10);
    if (iStack_3c != -1) {
      *piVar9 = iStack_3c;
      *(char *)((int)puStack_10 + 0xf) = *(char *)((int)puStack_10 + 0xf) + '\x01';
    }
  }
LAB_00377fa8:
  lVar8 = CheckTimer__6SdrvEEFv(iStack_20);
  if (lVar8 != 0) {
    return 1;
  }
  goto LAB_00377aa0;
}

/* ---- 0x00378030 size 0x1dc  SdrvEE::CmdSePlay(v)
 *      mangled: CmdSePlay__6SdrvEEFv */
u32 CmdSePlay__6SdrvEEFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u64 uVar3;
  long lVar4;
  int iVar5;
  
  do {
    uVar1 = m_cmdReg;
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      iVar2 = SetResult__6SdrvEEFUiUiUi(param_1,*(u32 *)(param_1 + 0x50),1,m_cmdReg);
      if ((uVar1 & 0x80000000) == 0) {
        SetSeOverlap__6SdrvEEFUiUi(param_1,*(u32 *)(param_1 + 0x50),uVar1);
      }
      else {
        *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0x7f | 0x80;
      }
      UpdateReqRp__6SdrvEEFv(param_1);
      *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      iVar2 = *(int *)(param_1 + 0x58);
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar5 = (int)uVar3;
      *(uint *)(iVar5 + 0xc) = (uint)*(ushort *)(iVar2 + 2) << 0x10 | 9;
      *(u32 *)(iVar5 + 0x10) = *(u32 *)(iVar2 + 4);
      *(u32 *)(iVar5 + 0x14) = *(u32 *)(iVar2 + 8);
      *(u32 *)(iVar5 + 0x18) = *(u32 *)(iVar2 + 0xc);
      if ((*(ushort *)(iVar2 + 2) & 7) != 0) {
        *(u32 *)(iVar5 + 0x1c) = *(u32 *)(iVar2 + 0x10);
      }
      *(u32 *)(iVar5 + 0x20) = *(u32 *)(param_1 + 0x34);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0x30,0);
    }
    lVar4 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar4 == 0);
  return 1;
}

/* ---- 0x00378210 size 0x140  SdrvEE::CmdSeParam(v)
 *      mangled: CmdSeParam__6SdrvEEFv */
u32 CmdSeParam__6SdrvEEFv(int param_1)

{
  int iVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  
  do {
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      iVar1 = *(int *)(param_1 + 0x58);
      uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar4 = (int)uVar2;
      *(uint *)(iVar4 + 0xc) = (uint)*(ushort *)(iVar1 + 2) << 0x10 | 0x109;
      *(u32 *)(iVar4 + 0x10) = *(u32 *)(iVar1 + 4);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      if (*(short *)(iVar1 + 2) == 0) {
        memcpy((void *)(iVar4 + 0x20),(void *)(iVar1 + 0x10),0x10);
        SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0x30,0);
      }
      else {
        *(u32 *)(iVar4 + 0x14) = *(u32 *)(iVar1 + 8);
        *(u32 *)(iVar4 + 0x18) = *(u32 *)(iVar1 + 0xc);
        SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0,0);
      }
    }
    lVar3 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar3 == 0);
  return 1;
}

/* ---- 0x00378350 size 0x154  SdrvEE::CmdSeStat(v)
 *      mangled: CmdSeStat__6SdrvEEFv */
u32 CmdSeStat__6SdrvEEFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u64 uVar3;
  long lVar4;
  
  do {
    uVar1 = m_cmdReg;
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      iVar2 = SetResult__6SdrvEEFUiUiUi(param_1,*(u32 *)(param_1 + 0x50),1,m_cmdReg);
      if ((uVar1 & 0x8000) != 0) {
        *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0x7f | 0x80;
      }
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      *(u32 *)((int)uVar3 + 0xc) = 0x209;
      *(u32 *)((int)uVar3 + 0x10) = *(u32 *)(*(int *)(param_1 + 0x58) + 4);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0,0);
    }
    lVar4 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar4 == 0);
  return 1;
}

/* ---- 0x003784b0 size 0x15c  SdrvEE::CmdSeRelease(v)
 *      mangled: CmdSeRelease__6SdrvEEFv */
u32 CmdSeRelease__6SdrvEEFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u64 uVar3;
  long lVar4;
  
  do {
    uVar1 = m_cmdReg;
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      if ((*(int *)(*(int *)(param_1 + 0x58) + 8) != 0) &&
         (iVar2 = SetResult__6SdrvEEFUiUiUi(param_1,*(u32 *)(param_1 + 0x50),1,m_cmdReg),
         (uVar1 & 0x8000) != 0)) {
        *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0x7f | 0x80;
      }
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      *(u32 *)((int)uVar3 + 0xc) = 0x309;
      *(u32 *)((int)uVar3 + 0x10) = *(u32 *)(*(int *)(param_1 + 0x58) + 4);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0,0);
    }
    lVar4 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar4 == 0);
  return 1;
}

/* ---- 0x00378610 size 0x174  SdrvEE::CmdBgmPlay(v)
 *      mangled: CmdBgmPlay__6SdrvEEFv */
u32 CmdBgmPlay__6SdrvEEFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u64 uVar3;
  long lVar4;
  int iVar5;
  
  do {
    uVar1 = m_cmdReg;
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      iVar2 = SetResult__6SdrvEEFUiUiUi(param_1,*(u32 *)(param_1 + 0x50),1,m_cmdReg);
      if ((uVar1 & 0x80000000) != 0) {
        *(byte *)(iVar2 + 3) = *(byte *)(iVar2 + 3) & 0x7f | 0x80;
      }
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar2 = *(int *)(param_1 + 0x58);
      iVar5 = (int)uVar3;
      *(u32 *)(iVar5 + 0xc) = 10;
      *(u32 *)(iVar5 + 0x10) = *(u32 *)(iVar2 + 4);
      *(u32 *)(iVar5 + 0x14) = *(u32 *)(iVar2 + 8);
      memcpy((void *)(iVar5 + 0x20),(void *)(iVar2 + 0x10),0x10);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0x30,0);
    }
    lVar4 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar4 == 0);
  return 1;
}

/* ---- 0x00378790 size 0x140  SdrvEE::CmdBgmParam(v)
 *      mangled: CmdBgmParam__6SdrvEEFv */
u32 CmdBgmParam__6SdrvEEFv(int param_1)

{
  int iVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  
  do {
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar1 = *(int *)(param_1 + 0x58);
      iVar4 = (int)uVar2;
      *(uint *)(iVar4 + 0xc) = (uint)*(ushort *)(iVar1 + 2) << 0x10 | 0x20a;
      *(u32 *)(iVar4 + 0x10) = *(u32 *)(iVar1 + 4);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      if (*(short *)(iVar1 + 2) == 0) {
        memcpy((void *)(iVar4 + 0x20),(void *)(iVar1 + 0x10),0x10);
        SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0x30,0);
      }
      else {
        *(u32 *)(iVar4 + 0x14) = *(u32 *)(iVar1 + 8);
        *(u32 *)(iVar4 + 0x18) = *(u32 *)(iVar1 + 0xc);
        SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0,0);
      }
    }
    lVar3 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar3 == 0);
  return 1;
}

/* ---- 0x003788d0 size 0x14  SdrvEE::CmdBgmStat(v)
 *      mangled: CmdBgmStat__6SdrvEEFv */
u32 CmdBgmStat__6SdrvEEFv(void)

{
  return 1;
}

/* ---- 0x003788f0 size 0x100  SdrvEE::CmdBgm(v)
 *      mangled: CmdBgm__6SdrvEEFv */
u32 CmdBgm__6SdrvEEFv(int param_1)

{
  int iVar1;
  u64 uVar2;
  long lVar3;
  int iVar4;
  
  do {
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar2 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar1 = *(int *)(param_1 + 0x58);
      iVar4 = (int)uVar2;
      *(uint *)(iVar4 + 0xc) = (uint)*(ushort *)(iVar1 + 2) << 8 | 10;
      *(u32 *)(iVar4 + 0x10) = *(u32 *)(iVar1 + 4);
      *(u32 *)(iVar4 + 0x14) = *(u32 *)(iVar1 + 8);
      *(u32 *)(iVar4 + 0x18) = *(u32 *)(iVar1 + 0xc);
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar2,0,0);
    }
    lVar3 = CheckTimer__6SdrvEEFv(param_1);
  } while (lVar3 == 0);
  return 1;
}

/* ---- 0x003789f0 size 0x364  SdrvEE::CheckResType(Ui)
 *      mangled: CheckResType__6SdrvEEFUi */
/* WARNING: Type propagation algorithm not settling */

void CheckResType__6SdrvEEFUi(int param_1,int param_2)

{
  char cVar1;
  u8 *puVar2;
  
  puVar2 = *(u8 **)(param_1 + 0x58);
  if (puVar2 == (u8 *)0x0) {
    scePrintf(0x3ff670,param_2);
    return;
  }
  switch(*puVar2) {
  case 4:
    if (((param_2 == 2) && (*(char *)(param_1 + 0x5e) == '\x01')) ||
       ((param_2 == 3 && (*(char *)(param_1 + 0x5e) == '\x04')))) goto switchD_00378a5c_caseD_6;
    goto LAB_00378d18;
  case 5:
    if ((param_2 != 4) || (*(char *)(param_1 + 0x5e) != '\x01')) {
      if ((param_2 == 4) && (*(char *)(param_1 + 0x5e) == '\x02')) {
        return;
      }
      goto LAB_00378d18;
    }
  default:
    goto switchD_00378a5c_caseD_6;
  case 7:
    if (param_2 != 6) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 8:
    if (param_2 != 0xff) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 9:
    if (param_2 != 0x80) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 10:
    if (param_2 != 0x81) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0xb:
    if (param_2 != 0x82) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0xd:
    if (param_2 != 0x83) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0xe:
    if (param_2 != 0x90) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0xf:
    if (param_2 != 0x91) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0x10:
    if (param_2 != 0x92) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
    break;
  case 0x11:
    if ((param_2 != 0x93) && (param_2 != 0x94)) goto LAB_00378d18;
    cVar1 = *(char *)(param_1 + 0x5e);
  }
  if (cVar1 != '\x01') {
LAB_00378d18:
    scePrintf(0x3ff690,*puVar2,param_2,*(u8 *)(param_1 + 0x5e));
    return;
  }
switchD_00378a5c_caseD_6:
  *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
  return;
}

/* ---- 0x00378d60 size 0x204  SdrvEE::CmdEEStreaming(v)
 *      mangled: CmdEEStreaming__6SdrvEEFv */
u32 CmdEEStreaming__6SdrvEEFv(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  u64 uVar4;
  long lVar5;
  int iVar6;
  
  iVar2 = *(int *)(param_1 + 0x58);
  iVar3 = *(int *)(iVar2 + 4);
  do {
    if (*(char *)(param_1 + 0x5e) == '\x02') {
      SetResult__6SdrvEEFUiUiUi(param_1,*(u32 *)(param_1 + 0x50),1,m_cmdReg);
      if (*(short *)(iVar2 + 2) == 2) {
        *(byte *)(iVar3 + 4) = *(byte *)(iVar3 + 4) & 0xf0 | (byte)DAT_00422144 & 0xf;
      }
      UpdateReqRp__6SdrvEEFv(param_1);
      return 0;
    }
    if (*(char *)(param_1 + 0x5e) == '\0') {
      uVar4 = GetCmdPkt__6SdrvEEFv(param_1);
      iVar6 = (int)uVar4;
      *(uint *)(iVar6 + 0xc) = (uint)*(ushort *)(iVar2 + 2) << 8 | 7;
      sVar1 = *(short *)(iVar2 + 2);
      if (sVar1 == 4) {
LAB_00378e60:
        *(ushort *)(iVar6 + 0x10) = *(byte *)(iVar3 + 4) & 0xf;
      }
      else {
        if (sVar1 == 3) {
          *(u16 *)(iVar6 + 0x14) = *(u16 *)(iVar3 + 10);
          *(u16 *)(iVar6 + 0x16) = *(u16 *)(iVar3 + 0xc);
          *(u16 *)(iVar6 + 0x18) = *(u16 *)(iVar3 + 0xe);
          goto LAB_00378e60;
        }
        if (sVar1 == 2) {
          *(byte *)(iVar6 + 0x10) = *(byte *)(iVar3 + 5) & 1;
          *(byte *)(iVar6 + 0x11) = *(byte *)(iVar3 + 4) >> 7;
          *(code **)(iVar6 + 0x14) = cbStreamNotify__6SdrvEEFUiUiUi;
          *(int *)(iVar6 + 0x18) = iVar3;
        }
      }
      *(char *)(param_1 + 0x5e) = *(char *)(param_1 + 0x5e) + '\x01';
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar4,0,0);
    }
    lVar5 = CheckTimer__6SdrvEEFv(param_1);
    if (lVar5 != 0) {
      return 1;
    }
  } while( true );
}

/* ---- 0x00378f70 size 0xf0  SdrvEE::SetResult(UiUiUi)
 *      mangled: SetResult__6SdrvEEFUiUiUi */
int * SetResult__6SdrvEEFUiUiUi(int param_1,int param_2,byte param_3,int param_4)

{
  int *piVar1;
  uint uVar2;
  
  piVar1 = *(int **)(param_1 + 0xdc);
  uVar2 = 0;
  while( true ) {
    if (*(byte *)(param_1 + 0x3b) <= uVar2) {
      return (int *)0x0;
    }
    if (*piVar1 == 0) break;
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 2;
  }
  *piVar1 = param_2;
  *(byte *)((int)piVar1 + 3) = *(byte *)((int)piVar1 + 3) & 0xc3 | (param_3 & 0xf) << 2;
  *(byte *)((int)piVar1 + 3) = *(byte *)((int)piVar1 + 3) & 0xbf | 0x40;
  piVar1[1] = param_4;
  return piVar1;
}

/* ---- 0x00379060 size 0xa0  SdrvEE::FindResult(Ui)
 *      mangled: FindResult__6SdrvEEFUi */
uint * FindResult__6SdrvEEFUi(int param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = *(uint **)(param_1 + 0xdc);
  uVar2 = 0;
  while( true ) {
    if (*(byte *)(param_1 + 0x3b) <= uVar2) {
      return (uint *)0x0;
    }
    if ((*puVar1 & 0x3ffffff) == param_2) break;
    uVar2 = uVar2 + 1;
    puVar1 = puVar1 + 2;
  }
  return puVar1;
}

/* ---- 0x00379100 size 0x178  SdrvEE::GetStatus(Ui)
 *      mangled: GetStatus__6SdrvEEFUi */
u8 GetStatus__6SdrvEEFUi(u32 param_1,uint param_2)

{
  u8 uVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  
  lVar3 = FindResult__6SdrvEEFUi(param_1,param_2);
  if (lVar3 == 0) {
    iVar4 = (param_2 >> 0x18 & 3) - 1;
    uVar2 = GetCurReqHandle__6SdrvEEFi(param_1,iVar4);
    if ((uVar2 == 0xffffffff) || (uVar2 != param_2)) {
      if (iVar4 < 0) {
        lVar3 = FindRequest__6SdrvEEFUi(param_1,param_2);
      }
      else {
        lVar3 = FindRequestA__6SdrvEEFUi(param_1,param_2);
      }
      uVar1 = lVar3 != 0;
    }
    else {
      uVar1 = 2;
    }
  }
  else if ((long)((ulong)*(byte *)((int)lVar3 + 3) << 0x38) < 0) {
    uVar1 = 0xfe;
  }
  else if ((long)((ulong)*(byte *)((int)lVar3 + 3) << 0x39) < 0) {
    uVar1 = 3;
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

/* ---- 0x00379280 size 0x5c  SdrvEE::GetOption(Ui)
 *      mangled: GetOption__6SdrvEEFUi */
u32 GetOption__6SdrvEEFUi(u32 param_1,u32 param_2)

{
  u32 uVar1;
  long lVar2;
  
  lVar2 = FindResult__6SdrvEEFUi(param_1,param_2);
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(u32 *)((int)lVar2 + 4);
  }
  return uVar1;
}

/* ---- 0x003792e0 size 0x100  SdrvEE::FindRequest(Ui)
 *      mangled: FindRequest__6SdrvEEFUi */
u8 * FindRequest__6SdrvEEFUi(int param_1,uint param_2)

{
  uint uVar1;
  long lVar2;
  u8 *puVar3;
  u32 uStack_24;
  
  lVar2 = isInQ__6SdrvEEFv(param_1);
  if (lVar2 != 0) {
    uVar1 = (uint)*(ushort *)(param_1 + 0x4a);
    while (uVar1 != *(ushort *)(param_1 + 0x4c)) {
      puVar3 = (u8 *)
               (*(int *)(param_1 + 0x40) +
               (*(ushort *)(*(int *)(param_1 + 0x44) + uVar1 * 2) & 0x3ff) * 0x10);
      uStack_24 = (uint)CONCAT12(puVar3[1],CONCAT11(*puVar3,(char)uVar1));
      if (uStack_24 == param_2) {
        return puVar3;
      }
      uVar1 = (int)(uVar1 + 1) % (int)(uint)*(ushort *)(param_1 + 0x48);
      if (*(ushort *)(param_1 + 0x48) == 0) {
        trap(7);
      }
    }
  }
  return (u8 *)0x0;
}

/* ---- 0x003793e0 size 0xe8  SdrvEE::FindRequestA(Ui)
 *      mangled: FindRequestA__6SdrvEEFUi */
uint * FindRequestA__6SdrvEEFUi(int param_1,uint param_2)

{
  uint uVar1;
  long lVar2;
  uint *puVar3;
  
  param_1 = param_1 + ((param_2 >> 0x18 & 3) - 1) * 8;
  lVar2 = isInQ__Q26SdrvEE11_TransReqWkFv((byte *)(param_1 + 4));
  if (lVar2 != 0) {
    uVar1 = (uint)*(byte *)(param_1 + 5);
    while (uVar1 != *(byte *)(param_1 + 4)) {
      puVar3 = (uint *)(*(int *)(param_1 + 8) + uVar1 * 0x10);
      if (*puVar3 == param_2) {
        return puVar3;
      }
      uVar1 = (int)(uVar1 + 1) % (int)(uint)*(byte *)(param_1 + 6);
      if (*(byte *)(param_1 + 6) == 0) {
        trap(7);
      }
    }
  }
  return (uint *)0x0;
}

/* ---- 0x003794d0 size 0x200  SdrvEE::CloseHandle(Ui)
 *      mangled: CloseHandle__6SdrvEEFUi */
u32 CloseHandle__6SdrvEEFUi(u32 param_1,uint param_2)

{
  uint uVar1;
  u32 uVar2;
  long lVar3;
  u32 *puVar4;
  int iVar5;
  char cStack_23;
  
  iVar5 = (param_2 >> 0x18 & 3) - 1;
  lVar3 = FindResult__6SdrvEEFUi(param_1,param_2);
  if (lVar3 == 0) {
    uVar1 = GetCurReqHandle__6SdrvEEFi(param_1,iVar5);
    if ((uVar1 == 0xffffffff) || (uVar1 != param_2)) {
      if (iVar5 < 0) {
        lVar3 = FindRequest__6SdrvEEFUi(param_1,param_2);
        if (lVar3 != 0) {
          InvalidateRequest__6SdrvEEFUi(param_1,param_2);
          return 1;
        }
      }
      else {
        lVar3 = FindRequestA__6SdrvEEFUi(param_1,param_2);
        if (lVar3 != 0) {
          cStack_23 = (char)(param_2 >> 8);
          if (cStack_23 == '\x05') {
            return 1;
          }
          InvalidateRequest__6SdrvEEFUi(param_1,param_2);
          return 1;
        }
      }
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    puVar4 = (u32 *)lVar3;
    if (((long)((ulong)*(byte *)((int)puVar4 + 3) << 0x39) < 0) ||
       ((long)((ulong)*(byte *)((int)puVar4 + 3) << 0x38) < 0)) {
      ClrSeOverlap__6SdrvEEFUi(param_1,param_2);
      *puVar4 = 0;
      uVar1 = GetCurReqHandle__6SdrvEEFi(param_1,iVar5);
      if ((uVar1 != 0xffffffff) && (uVar1 == param_2)) {
        PurgeCurRequest__6SdrvEEFi(param_1,iVar5);
      }
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

/* ---- 0x003796d0 size 0x50  SdrvEE::PurgeCurRequest(i)
 *      mangled: PurgeCurRequest__6SdrvEEFi */
void PurgeCurRequest__6SdrvEEFi(u32 param_1,int param_2)

{
  if (param_2 < 0) {
    UpdateReqRp__6SdrvEEFv(param_1);
  }
  else {
    UpdateTransReq__6SdrvEEFi(param_1,param_2);
  }
  return;
}

/* ---- 0x00379720 size 0xa4  SdrvEE::InvalidateRequest(Ui)
 *      mangled: InvalidateRequest__6SdrvEEFUi */
void InvalidateRequest__6SdrvEEFUi(u32 param_1,uint param_2)

{
  u8 *puVar1;
  u32 *puVar2;
  u32 uStack_24;
  
  if ((int)((param_2 >> 0x18 & 3) - 1) < 0) {
    puVar1 = (u8 *)FindRequest__6SdrvEEFUi(param_1,param_2);
    *puVar1 = 1;
  }
  else {
    puVar2 = (u32 *)FindRequestA__6SdrvEEFUi(param_1,param_2);
    uStack_24._2_2_ = (u16)(param_2 >> 0x10);
    uStack_24._0_2_ = CONCAT11(1,(char)param_2);
    *puVar2 = uStack_24;
  }
  return;
}

/* ---- 0x003797d0 size 0xa0  SdrvEE::CmdPause(v)
 *      mangled: CmdPause__6SdrvEEFv */
void CmdPause__6SdrvEEFv(byte *param_1)

{
  u64 uVar1;
  
  uVar1 = GetCmdPkt__6SdrvEEFv(param_1);
  *(uint *)((int)uVar1 + 0xc) = ((uint)(((ulong)*param_1 << 0x3a) >> 0x3e) & 2) << 7 | 0xb;
  SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar1,0,1);
  *param_1 = *param_1 & 0xcf | (byte)(((uint)(((ulong)*param_1 << 0x3a) >> 0x3e) + 1 & 3) << 4);
  return;
}

/* ---- 0x00379870 size 0x5c  SdrvEE::CmdReset(v)
 *      mangled: CmdReset__6SdrvEEFv */
void CmdReset__6SdrvEEFv(byte *param_1)

{
  if (param_1[0x5e] == 1) {
    *param_1 = *param_1 & 0x3f | 0x80;
    param_1[0x5e] = 2;
  }
  return;
}

/* ---- 0x003798d0 size 0x94  SdrvEE::cbStreamNotify(UiUiUi)
 *      mangled: cbStreamNotify__6SdrvEEFUiUiUi */
void cbStreamNotify__6SdrvEEFUiUiUi(int param_1,u64 param_2,int param_3)

{
  if (param_1 == 1) {
    *(byte *)(param_3 + 5) = *(byte *)(param_3 + 5) & 0xf9 | 2;
  }
  else if (param_1 == 0) {
    *(byte *)(param_3 + 5) = *(byte *)(param_3 + 5) & 0xf9 | 6;
  }
  return;
}

/* ---- 0x00379970 size 0xb4  SdrvEE::SetStreamStop(P14_sdrvEeStrInfo)
 *      mangled: SetStreamStop__6SdrvEEFP14_sdrvEeStrInfo */
void SetStreamStop__6SdrvEEFP14_sdrvEeStrInfo(u32 param_1,int param_2)

{
  u64 uVar1;
  int iVar2;
  
  if (((ulong)*(byte *)(param_2 + 5) & 7) >> 1 == 1) {
    uVar1 = GetCmdPkt__6SdrvEEFv(param_1);
    iVar2 = (int)uVar1;
    *(u32 *)(iVar2 + 0xc) = 0x1307;
    *(int *)(iVar2 + 0x10) = param_2;
    *(ushort *)(iVar2 + 0x14) = *(byte *)(param_2 + 4) & 0xf;
    SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar1,0,0);
    *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) & 0xf9 | 4;
  }
  return;
}

/* ---- 0x00379a30 size 0x65c  SdrvEE::UpdateEEStream(v)
 *      mangled: UpdateEEStream__6SdrvEEFv */
void UpdateEEStream__6SdrvEEFv(int param_1)

{
  char cVar1;
  ushort uVar2;
  u64 uVar3;
  uint uVar4;
  u32 *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iStack_14;
  
  puVar5 = *(u32 **)(param_1 + 0x164);
  do {
    while( true ) {
      if (puVar5 == (u32 *)0x0) {
        return;
      }
      if (((((ulong)*(byte *)((int)puVar5 + 5) & 7) >> 1 != 1) ||
          (-1 < (long)((ulong)*(byte *)((int)puVar5 + 5) << 0x3b))) ||
         (-1 < (long)((ulong)*(byte *)(puVar5 + 1) << 0x39))) break;
      *(byte *)(puVar5 + 1) = *(byte *)(puVar5 + 1) & 0xbf;
      uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
      *(u32 *)((int)uVar3 + 0xc) = 0x1207;
      *(ushort *)((int)uVar3 + 0x10) = *(byte *)(puVar5 + 1) & 0xf;
      SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0,0);
      puVar5 = (u32 *)*puVar5;
    }
    if ((((ulong)*(byte *)((int)puVar5 + 5) & 7) >> 1 < 2) &&
       ((long)((ulong)*(byte *)((int)puVar5 + 5) << 0x3b) < 0)) {
      cVar1 = *(char *)((int)puVar5 + 6);
      if (cVar1 == '\x05') {
        *(u8 *)((int)puVar5 + 6) = 0;
      }
      else if (cVar1 == '\x02') {
        uVar7 = (uint)*(ushort *)(puVar5 + 0xe);
        if (uVar7 == 0) {
          *(u8 *)((int)puVar5 + 6) = 0;
        }
        else {
          uVar4 = (uint)*(ushort *)((int)puVar5 + 0x3a);
          if (uVar4 == 0) {
            if ((uint)puVar5[5] <= (uint)puVar5[6]) {
              if (((ulong)*(byte *)(puVar5 + 1) & 0x3f) >> 4 == 0) {
                SetStreamStop__6SdrvEEFP14_sdrvEeStrInfo(param_1,puVar5);
                goto LAB_0037a048;
              }
              puVar5[6] = 0;
            }
            *(u8 *)((int)puVar5 + 6) = 4;
          }
          else {
            if (uVar4 < uVar7) {
              uVar7 = uVar4;
            }
            if ((*(byte *)((int)puVar5 + 5) & 1) == 0) {
              if (puVar5[0xb] == 0) {
                uVar2 = *(ushort *)(puVar5[0xf] + ((uint)puVar5[6] >> 0xb) * 2);
                puVar5[0xb] = (uint)(uVar2 >> 8);
                puVar5[10] = uVar2 & 0xff;
              }
              if ((uint)(puVar5[0xb] - puVar5[10]) < uVar7) {
                uVar7 = puVar5[0xb] - puVar5[10];
              }
            }
            if (uVar7 == 0) {
              *(u8 *)((int)puVar5 + 6) = 0;
            }
            else {
              *(short *)(puVar5 + 0xe) = (short)uVar7;
              uVar4 = puVar5[4];
              if ((long)((ulong)*(byte *)((int)puVar5 + 5) << 0x3c) < 0) {
                uVar4 = uVar4 + 0x3f & 0xffffffc0;
              }
              iVar8 = uVar4 + puVar5[6] + puVar5[10] * 0x10;
              if ((*(byte *)((int)puVar5 + 5) & 1) == 0) {
                puVar5[10] = puVar5[10] + uVar7;
              }
              *(char *)((int)puVar5 + 6) = *(char *)((int)puVar5 + 6) + '\x01';
              if ((long)((ulong)*(byte *)(puVar5 + 1) << 0x38) < 0) {
                uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
                iVar6 = (int)uVar3;
                *(u32 *)(iVar6 + 0xc) = 0x1107;
                *(u32 **)(iVar6 + 0x10) = puVar5;
                *(uint *)(iVar6 + 0x14) = *(byte *)(puVar5 + 1) & 0xf;
                SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii
                          (param_1,uVar3,iVar8 + puVar5[9],puVar5[0xd],uVar7 << 4,0,0);
              }
              uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
              iVar6 = (int)uVar3;
              *(u32 *)(iVar6 + 0xc) = 0x11107;
              *(u32 **)(iVar6 + 0x10) = puVar5;
              *(uint *)(iVar6 + 0x14) = *(byte *)(puVar5 + 1) & 0xf;
              SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii
                        (param_1,uVar3,iVar8,puVar5[0xc],uVar7 << 4,0,0);
            }
          }
        }
      }
      else if (cVar1 == '\0') {
LAB_00379cd0:
        if (puVar5[6] == puVar5[7]) {
          if (*(byte *)((int)puVar5 + 5) >> 5 != 0) {
            SetStreamStop__6SdrvEEFP14_sdrvEeStrInfo(param_1,puVar5);
          }
        }
        else {
          iVar8 = puVar5[9];
          if ((long)((ulong)*(byte *)(puVar5 + 1) << 0x38) < 0) {
            iVar8 = iVar8 << 1;
          }
          if ((uint)puVar5[6] < (uint)puVar5[7]) {
            uVar7 = puVar5[7] - puVar5[6];
          }
          else {
            uVar7 = puVar5[5] - puVar5[6];
          }
          uVar7 = uVar7 & ~(iVar8 - 1U);
          if (uVar7 != 0) {
            if (0xfffff < (int)uVar7) {
              uVar7 = 0xffff0;
            }
            *(short *)((int)puVar5 + 0x3a) = (short)((int)uVar7 >> 4);
            uVar3 = GetCmdPkt__6SdrvEEFv(param_1);
            iVar8 = (int)uVar3;
            *(u32 *)(iVar8 + 0xc) = 0x1007;
            *(u32 **)(iVar8 + 0x10) = puVar5;
            *(ushort *)(iVar8 + 0x14) = *(byte *)(puVar5 + 1) & 0xf;
            *(char *)((int)puVar5 + 6) = *(char *)((int)puVar5 + 6) + '\x01';
            SendCmd__6SdrvEEFP13_SdrvCmdPktExii(param_1,uVar3,0,0);
          }
        }
      }
      else if (cVar1 == '\x04') {
        if ((*(byte *)((int)puVar5 + 5) & 1) == 0) {
          if ((puVar5[0xb] != 0) && ((uint)puVar5[0xb] <= (uint)puVar5[10])) {
            puVar5[10] = 0;
            iStack_14 = puVar5[9];
            if ((long)((ulong)*(byte *)(puVar5 + 1) << 0x38) < 0) {
              iStack_14 = iStack_14 << 1;
            }
            puVar5[6] = puVar5[6] + iStack_14;
            puVar5[8] = puVar5[8] + puVar5[9];
            puVar5[0xb] = 0;
          }
        }
        else {
          puVar5[6] = puVar5[6] + (uint)*(ushort *)(puVar5 + 0xe) * 0x10;
        }
        *(u8 *)((int)puVar5 + 6) = 0;
        if (((uint)puVar5[5] <= (uint)puVar5[7]) &&
           (((ulong)*(byte *)(puVar5 + 1) & 0x3f) >> 4 == 2)) {
          puVar5[7] = 0;
        }
        if ((uint)puVar5[5] <= (uint)puVar5[6]) {
          if (((ulong)*(byte *)(puVar5 + 1) & 0x3f) >> 4 == 0) {
            SetStreamStop__6SdrvEEFP14_sdrvEeStrInfo(param_1,puVar5);
            goto LAB_0037a048;
          }
          puVar5[6] = 0;
        }
        if (m_syncCount__3Gsx != 1) goto LAB_00379cd0;
        *(u8 *)((int)puVar5 + 6) = 5;
      }
    }
LAB_0037a048:
    puVar5 = (u32 *)*puVar5;
  } while( true );
}

/* ---- 0x0037a090 size 0xc4  SdrvEE::CmdHandler(v)
 *      mangled: CmdHandler__6SdrvEEFv */
void CmdHandler__6SdrvEEFv(byte *param_1)

{
  u32 uVar1;
  long lVar2;
  
  if ((((ulong)*param_1 & 0x3f) >> 4 & 1) != 0) {
    CmdPause__6SdrvEEFv(param_1);
  }
  uVar1 = GetHCount__3GsxFv();
  *(u32 *)(param_1 + 0xc0) = uVar1;
  param_1[0xc4] = 5;
  param_1[0xc5] = 0;
  param_1[0xc6] = 0;
  param_1[199] = 0;
  do {
    lVar2 = isInQ__6SdrvEEFv(param_1);
    if (lVar2 == 0) {
      *param_1 = *param_1 & 0xfd;
      return;
    }
    lVar2 = HandleCurReq__6SdrvEEFv(param_1);
  } while (lVar2 == 0);
  return;
}

/* ---- 0x0037a160 size 0x180  SdrvEE::CmdHandlerA(v)
 *      mangled: CmdHandlerA__6SdrvEEFv */
void CmdHandlerA__6SdrvEEFv(byte *param_1)

{
  u32 uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = GetHCount__3GsxFv();
  *(u32 *)(param_1 + 0xc0) = uVar1;
  param_1[0xc4] = 5;
  param_1[0xc5] = 0;
  param_1[0xc6] = 0;
  param_1[199] = 0;
  uVar5 = 3;
  while( true ) {
    lVar2 = isInQ__Q26SdrvEE11_TransReqWkFv(param_1 + 0xc);
    if (lVar2 == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = 2;
    }
    lVar2 = isInQ__Q26SdrvEE11_TransReqWkFv(param_1 + 4);
    uVar4 = uVar4 | lVar2 != 0;
    *param_1 = *param_1 & 0xf3 | (byte)(uVar4 << 2);
    if ((uVar4 & uVar5) == 0) break;
    for (uVar3 = 0; (int)uVar3 < 2; uVar3 = uVar3 + 1) {
      if (((uVar4 & 1 << (uVar3 & 0x1f)) != 0) &&
         (lVar2 = HandleCurReqA__6SdrvEEFPQ26SdrvEE11_TransReqWk(param_1,param_1 + uVar3 * 8 + 4),
         lVar2 != 0)) {
        uVar5 = uVar5 & ~(1 << (uVar3 & 0x1f));
      }
    }
  }
  return;
}

/* ---- 0x0037a2e0 size 0xb8  SdrvEE::SendCmd(P13_SdrvCmdPktExii)
 *      mangled: SendCmd__6SdrvEEFP13_SdrvCmdPktExii */
long SendCmd__6SdrvEEFP13_SdrvCmdPktExii(int param_1,u32 param_2,int param_3,int param_4)

{
  long lVar1;
  long lVar2;
  u32 uStack_20;
  
  uStack_20 = param_3;
  if (param_3 == 0) {
    uStack_20 = 0x20;
  }
  FlushCache(0);
  do {
    lVar1 = sceSifSendCmd(*(u16 *)(param_1 + 0x2c),param_2,uStack_20,0,0,0);
  } while (lVar1 == 0);
  if (param_4 != 0) {
    do {
      lVar2 = sceSifDmaStat(lVar1);
    } while (-1 < lVar2);
  }
  return lVar1;
}

/* ---- 0x0037a3a0 size 0xc8  SdrvEE::SendCmdS(P13_SdrvCmdPktExUiUiUiii)
 *      mangled: SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii */
long SendCmdS__6SdrvEEFP13_SdrvCmdPktExUiUiUiii
               (int param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5,int param_6,int param_7)

{
  long lVar1;
  long lVar2;
  u32 uStack_20;
  
  uStack_20 = param_6;
  if (param_6 == 0) {
    uStack_20 = 0x20;
  }
  FlushCache(0);
  do {
    lVar1 = sceSifSendCmd(*(u16 *)(param_1 + 0x2c),param_2,uStack_20,param_3,param_4,param_5)
    ;
  } while (lVar1 == 0);
  if (param_7 != 0) {
    do {
      lVar2 = sceSifDmaStat(lVar1);
    } while (-1 < lVar2);
  }
  return lVar1;
}

