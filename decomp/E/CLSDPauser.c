/*
 * CLSDPauser.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 8 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003ca7c0 size 0x54  CLSDPauser::CLSDPauser(v)
 *      mangled: __ct__10CLSDPauserFv */
int __ct__10CLSDPauserFv(int param_1)

{
  __ct__7CPauserFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__10CLSDPauser;
  *(u32 *)(param_1 + 0x20) = 0x407740;
  *(u32 *)(param_1 + 0xb8) = 0;
  return param_1;
}

/* ---- 0x003ca820 size 0x84  CLSDPauser::~CLSDPauser(v)
 *      mangled: __dt__10CLSDPauserFv */
int __dt__10CLSDPauserFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__10CLSDPauser;
    *(u32 *)(param_1 + 0x20) = 0x407740;
    __dt__7CPauserFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003ca8b0 size 0x4f4  CLSDPauser::Polling(v)
 *      mangled: Polling__10CLSDPauserFv */
u64 Polling__10CLSDPauserFv(int param_1)

{
  short sVar1;
  int iVar2;
  long lVar3;
  u64 uVar4;
  u64 uVar5;
  int iVar6;
  
  sVar1 = *(short *)(param_1 + 0x24);
  if (sVar1 != 0x20) {
    if (sVar1 != 0x10) {
      if (sVar1 == 1) {
        (**(code **)(*(int *)(*(int *)(param_1 + 0xb8) + 0x14) + 0xc))();
        if (*(byte *)(param_1 + 0xb0) < 0x40) {
          *(char *)(param_1 + 0xb0) = *(char *)(param_1 + 0xb0) + '\b';
        }
        else {
          *(u16 *)(param_1 + 0x24) = 0x10;
        }
      }
      else {
        if (sVar1 != 0) {
          return 0;
        }
        lVar3 = IsReadyField__7MenuObjFv();
        if (lVar3 != 0) {
          Pause__9LSDPlayerFv(sys__9LSDPlayer);
          Create__5P2PktFii(param_1 + 0x28,7,1);
          *(byte *)(param_1 + 0x44) = *(byte *)(param_1 + 0x44) & 0x83 | 0x38;
          Dsp__5P2PktFv((P2Pkt *)(param_1 + 0x28));
          lVar3 = __nw__FUi(0x1c);
          uVar4 = 0;
          if (lVar3 != 0) {
            uVar4 = __ct__12FieldMessageFv(lVar3);
          }
          CreateWindow__12FieldMessageFsUcUcUcs(uVar4,0,6,0,2,0x80);
          ClearMessage__12FieldMessageFv(uVar4);
          iVar6 = (int)uVar4;
          *(byte *)(*(int *)(iVar6 + 0x18) + 0x15c) =
               *(byte *)(*(int *)(iVar6 + 0x18) + 0x15c) & 0xf7;
          uVar5 = GetRegDat__9RegDatApiFiii(0x25,0,0xffffffffffffffff);
          ReplaceLF__FPc(uVar5);
          iVar2 = GetStrLength__FPCc(uVar5);
          SetSize__12FieldMessageFss(uVar4,(short)iVar2,2);
          SetPosition__12FieldMessageFff((float)(iVar2 * -8 + 0x100),0x43400000,uVar4);
          OpenWindow__12FieldMessageFUci(uVar4,0,0);
          ChengeLayer__12FieldMessageFi(uVar4,0xf);
          OpenMessage__12FieldMessageFPc(uVar4,uVar5);
          Finish__11MenuMessageFv((MenuMessage *)(*(int *)(iVar6 + 0x18) + 0x104));
          *(int *)(param_1 + 0xb8) = iVar6;
          *(u16 *)(param_1 + 0x24) = 1;
          *(u8 *)(param_1 + 0xb0) = 0;
          (**(code **)(*(int *)(param_1 + 0x14) + 0x28))();
          Pause__4SdrvFUi(sys__4Sdrv,0);
          if (sys__8CVibeMan != 0) {
            SetMute__8CVibeManFi(sys__8CVibeMan,1);
          }
        }
      }
LAB_003cad58:
      (**(code **)(*(int *)(param_1 + 0x14) + 0x28))();
      return 0;
    }
    iVar2 = GetActive__4CPadFi(0);
    if ((*(ushort *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6c) & 0x1000) == 0) {
      lVar3 = CheckUnPause__6CPauseFUiUi
                        (*(u32 *)(app__4CApp + 0x78),
                         *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6a),0);
      if (lVar3 == 0) goto LAB_003cad58;
      Pause__4SdrvFUi(sys__4Sdrv,1);
      if (sys__8CVibeMan != 0) {
        SetMute__8CVibeManFi(sys__8CVibeMan,0);
      }
      Release__9LSDPlayerFv(sys__9LSDPlayer);
    }
    else {
      if (sys__8CVibeMan != 0) {
        SetMute__8CVibeManFi(sys__8CVibeMan,0);
      }
      FieldBreakMCES__Fv();
    }
    *(u16 *)(param_1 + 0x24) = 0x20;
  }
  Clr__5P2PktFv((P2Pkt *)(param_1 + 0x28));
  DestroyWindow__12FieldMessageFv(*(u32 *)(param_1 + 0xb8));
  iVar2 = *(int *)(param_1 + 0xb8);
  if (iVar2 != 0) {
    (**(code **)(*(int *)(iVar2 + 0x14) + 8))(iVar2,1);
  }
  *(u32 *)(param_1 + 0xb8) = 0;
  iVar2 = m_pBright__4CApp;
  *(u32 *)(m_pBright__4CApp + 0x2c) = 0;
  *(u32 *)(iVar2 + 0x30) = 0;
  if (*(char *)(param_1 + 0xb3) != '\0') {
    Release__6P2ClutFv();
  }
  Unpause__4CAppFv(app__4CApp);
  *(u16 *)(param_1 + 0x24) = 0xff;
  sys__7CPauser = 0;
  (**(code **)(*(int *)(param_1 + 0x14) + 0x24))();
  return 0;
}

/* ---- 0x003cadb0 size 0x14  CLSDPauser::DrawA(v)
 *      mangled: DrawA__10CLSDPauserFv */
u64 DrawA__10CLSDPauserFv(void)

{
  return 0;
}

/* ---- 0x003cadd0 size 0x124  CLSDPauser::MakePacket(v)
 *      mangled: MakePacket__10CLSDPauserFv */
void * MakePacket__10CLSDPauserFv(int param_1)

{
  short sVar1;
  void *__dest;
  void *pvVar2;
  uint uVar3;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x44) << 0x3e) < 0) {
    uVar3 = m_Env__8VIF1Prim & 1;
  }
  else {
    uVar3 = 0;
  }
  *(u16 *)(uVar3 * 2 + param_1 + 0x48) = 0;
  __dest = (void *)AddCnt__5P2PktFi(param_1 + 0x28,6);
  pvVar2 = memcpy(__dest,MaskData,0x60);
  *(uint *)((int)__dest + 0x48) = (uint)*(byte *)(param_1 + 0xb0) << 0x18;
  sVar1 = m_scrw__4CApp;
  *(short *)((int)__dest + 0x50) = (0x800 - m_scrw__4CApp) * 0x10;
  *(short *)((int)__dest + 0x52) = (0x800 - sVar1) * 0x10;
  *(short *)((int)__dest + 0x58) = (sVar1 + 0x800) * 0x10;
  *(short *)((int)__dest + 0x5a) = (sVar1 + 0x800) * 0x10;
  return pvVar2;
}

/* ---- 0x003caf00 size 0x30  CLSDPauser::DelayDelete(v)
 *      mangled: DelayDelete__10CLSDPauserFv */
void DelayDelete__10CLSDPauserFv(u32 param_1)

{
  DelayDelete__7CPauserFv(param_1);
  FieldExitPauseMCES__Fv();
  return;
}

/* ---- 0x003caf50 size 0x8  CLSDPauser::@24@DelayDelete(v)
 *      mangled: @24@DelayDelete__10CLSDPauserFv */
void _24_DelayDelete__10CLSDPauserFv(int param_1)

{
  DelayDelete__7CPauserFv(param_1 + -0x18);
  FieldExitPauseMCES__Fv();
  return;
}

/* ---- 0x003caf60 size 0x8  CLSDPauser::@24@__dt(v)
 *      mangled: @24@__dt__10CLSDPauserFv */
int _24___dt__10CLSDPauserFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__10CLSDPauser;
    *(u32 *)(param_1 + 8) = 0x407740;
    __dt__7CPauserFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

