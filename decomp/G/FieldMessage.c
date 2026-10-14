/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FieldMessage   functions: 22
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FieldMessage.md).
 */

/* JP: 0x004a0d80  FieldMessage::FieldMessage()   [__ct__12FieldMessageFv]  size=0x44 */
int __ct__12FieldMessageFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__12FieldMessage;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return param_1;
}

/* JP: 0x004a0dd0  FieldMessage::~FieldMessage()   [__dt__12FieldMessageFv]  size=0x7c */
int __dt__12FieldMessageFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__12FieldMessage;
    DestroyWindow__12FieldMessageFv(param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004a0e50  FieldMessage::CreateWindow(short, unsigned char, unsigned char, unsigned char, short)   [CreateWindow__12FieldMessageFsUcUcUcs]  size=0x338 */
undefined4
CreateWindow__12FieldMessageFsUcUcUcs
          (int param_1,undefined8 param_2,char param_3,undefined1 param_4,undefined1 param_5,
          undefined2 param_6)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (iRam0042159c < 1) {
    uVar2 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x18) == 0) {
      lVar3 = __nw__FUi(0x380);
      iVar1 = 0;
      if (lVar3 != 0) {
        iVar1 = __ct__16FieldMessageDataFv(lVar3);
      }
      *(undefined1 **)(iVar1 + 0xc) = &sm_menuRender__7MenuObj;
      *(byte *)(iVar1 + 0x37d) = *(byte *)(iVar1 + 0x37d) & 0xfb;
      *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0xef;
      Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster(iVar1 + 0xc4,0x1b,0x1fc,0xe8,1,0,0);
      *(undefined2 *)(iVar1 + 0xd8) = 0;
      (**(code **)(*(int *)(iVar1 + 0x10c) + 0x60))(iVar1 + 0x104,param_6,param_5);
      *(undefined2 *)(iVar1 + 0x118) = 1;
      *(int *)(iVar1 + 0x158) = iVar1 + 0xc4;
      SetFontNumber__8FontItemFUc(iVar1 + 0x104,param_4);
      *(undefined1 *)(iVar1 + 0x15e) = 0;
      *(undefined1 *)(iVar1 + 0x15f) = 1;
      Start__11MenuMessageFv(iVar1 + 0x104);
      Create__7KeyWaitFv(iVar1 + 0x19c);
      *(undefined2 *)(iVar1 + 0x1ba) = 1;
      *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfd;
      *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfe;
      *(undefined2 *)(iVar1 + 0x1bc) = 0x6000;
      Create__10MenuWindowFUcUcffff(0,0,0,0,iVar1 + 0x10,param_3,1);
      CreateScroll__10MenuWindowFUissffUc(0,0,iVar1 + 0x10,0,0,0,0xf);
      *(undefined2 *)(iVar1 + 0x24) = 0;
      *(int *)(iVar1 + 0x58) = iVar1 + 0x19c;
      *(int *)(iVar1 + 0x1b4) = iVar1 + 0x10;
      AddPlace__10MenuWindowFP9MenuPlace(iVar1 + 0x10,iVar1 + 0x104);
      AddPriority__12MenuObjTableFP7MenuObj(iVar1 + 0x28,iVar1 + 0xc4);
      AddOT__7MenuObjFv(iVar1 + 0x10);
      if (param_3 == '\x03') {
        *(byte *)(iVar1 + 0x163) = *(byte *)(iVar1 + 0x163) & 0xfb;
      }
      Create__6CursorFUcUcUcUc(iVar1 + 0x278,0,2,8,1);
      *(undefined1 *)(iVar1 + 0x371) = 0xdc;
      Select__6CursorFP9MenuPlace(iVar1 + 0x278,iVar1 + 0x104);
      Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
      *(int *)(param_1 + 0x18) = iVar1;
    }
    *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x37a) = 0;
    *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x374) = 0;
    *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x376) = 0;
    *(byte *)(*(int *)(param_1 + 0x18) + 0x22) = *(byte *)(*(int *)(param_1 + 0x18) + 0x22) & 0xfe;
    SetSize__12FieldMessageFss(param_1,0x1e,3);
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a1190  FieldMessage::DestroyWindow()   [DestroyWindow__12FieldMessageFv]  size=0xbc */
void DestroyWindow__12FieldMessageFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 != 0) {
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x10);
    ClearPlace__10MenuWindowFv(iVar1 + 0x10);
    *(undefined4 *)(iVar1 + 0x364) = 0;
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x278);
    if ((long)((ulong)*(byte *)(iVar1 + 0x37d) << 0x3d) < 0) {
      Dispose__10MenuRenderFv(*(undefined4 *)(iVar1 + 0xc));
    }
    (**(code **)(*(int *)(iVar1 + 8) + 0xc))();
    *(undefined4 *)(param_1 + 0x18) = 0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* JP: 0x004a1250  FieldMessage::ChengeLayer(int)   [ChengeLayer__12FieldMessageFi]  size=0x140 */
undefined4 ChengeLayer__12FieldMessageFi(int param_1,undefined4 param_2)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if ((long)((ulong)*(byte *)(iVar1 + 0x37d) << 0x3d) < 0) {
    ChengeLayer__10MenuRenderFi(*(undefined4 *)(iVar1 + 0xc),param_2);
  }
  else {
    lVar2 = __nw__FUi(0x3c);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = __ct__10MenuRenderFv(lVar2);
    }
    Create__10MenuRenderFv(uVar3);
    Entry__10MenuRenderFi(uVar3,param_2);
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x10);
    iVar4 = (int)uVar3;
    AddPriority__12MenuObjTableFP7MenuObj(iVar4 + 0x2c,iVar1 + 0x10);
    if ((long)((ulong)*(byte *)(iVar1 + 0x28a) << 0x3d) < 0) {
      RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x278);
      AddPriority__12MenuObjTableFP7MenuObj(iVar4 + 0x2c,iVar1 + 0x278);
    }
    *(int *)(iVar1 + 0xc) = iVar4;
    *(byte *)(iVar1 + 0x37d) = *(byte *)(iVar1 + 0x37d) & 0xfb | 4;
  }
  return 1;
}

/* JP: 0x004a1390  FieldMessage::OpenWindow(unsigned char, int)   [OpenWindow__12FieldMessageFUci]  size=0x12c */
undefined2 OpenWindow__12FieldMessageFUci(int param_1,byte param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (((ulong)*(ushort *)(iVar1 + 0xc0) & 0x1ff) >> 6 == 3) {
    *(byte *)(iVar1 + 0xc0) = *(byte *)(iVar1 + 0xc0) & 0xf8 | param_2 & 7;
    *(undefined4 *)(iVar1 + 0xa4) = param_3;
    uVar2 = 0;
  }
  else {
    *(byte *)(iVar1 + 0x28a) = *(byte *)(iVar1 + 0x28a) & 0xfe;
    *(undefined2 *)(iVar1 + 0x1ba) = 1;
    *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfd;
    *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfe;
    *(undefined2 *)(iVar1 + 0x37a) = 3;
    uVar2 = Open__10MenuWindowFUci(iVar1 + 0x10,param_2,param_3);
  }
  return uVar2;
}

/* JP: 0x004a14c0  FieldMessage::CloseWindow(unsigned char, int)   [CloseWindow__12FieldMessageFUci]  size=0xb4 */
undefined2 CloseWindow__12FieldMessageFUci(int param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  *(byte *)(iVar1 + 0x28a) = *(byte *)(iVar1 + 0x28a) & 0xfe;
  *(undefined2 *)(iVar1 + 0x1ba) = 1;
  *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfd;
  *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfe;
  *(undefined2 *)(iVar1 + 0x37a) = 4;
  uVar2 = Close__10MenuWindowFUci(iVar1 + 0x10,param_2,param_3);
  return uVar2;
}

/* JP: 0x004a1580  FieldMessage::OpenMessage(char*)   [OpenMessage__12FieldMessageFPc]  size=0x1bc */
undefined4 OpenMessage__12FieldMessageFPc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x18);
  lVar3 = Order__8FontDrawFP11MenuMessagePc(*(undefined4 *)(iVar1 + 0x158),iVar1 + 0x104,param_2);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    iVar4 = iVar1 + 0x10;
    if ((*(short *)(iVar1 + 0x37a) == 1) && (-1 < (long)((ulong)*(byte *)(iVar1 + 0x37c) << 0x3a)))
    {
      *(undefined2 *)(iVar1 + 0x37a) = 9;
    }
    if (((ulong)*(ushort *)(iVar1 + 0xc0) & 0x1ff) >> 6 == 3) {
      SetSize__10MenuWindowFff(*(undefined4 *)(iVar1 + 0x130),*(undefined4 *)(iVar1 + 0x134),iVar4);
      SetPosition__10MenuWindowFff(256.0 - *(float *)(iVar1 + 0x7c) * 0.5,*(undefined4 *)(iVar1 + 0x78),iVar4);
      if ((*(byte *)(iVar1 + 0x22) & 1) == 0) {
        Open__10MenuWindowFUci(iVar4,*(byte *)(iVar1 + 0xc0) & 7,*(undefined4 *)(iVar1 + 0xa4));
      }
    }
    if (*(char *)(iVar1 + 0x124) == '\x01') {
      *(undefined1 *)(iVar1 + 0x124) = 9;
    }
    *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0xdf;
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a1740  FieldMessage::ClearMessage()   [ClearMessage__12FieldMessageFv]  size=0x178 */
void ClearMessage__12FieldMessageFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  ClearMessage__11MenuMessageFv(iVar1 + 0x104);
  Start__11MenuMessageFv(iVar1 + 0x104);
  ClearImage__8FontDrawFv(iVar1 + 0xc4);
  *(undefined4 *)(*(int *)(iVar1 + 0x50) + 0x38) = 0;
  SetScroll__10MenuWindowFss(iVar1 + 0x10,0,0);
  *(byte *)(iVar1 + 0x1be) = *(byte *)(iVar1 + 0x1be) & 0xbf;
  *(undefined2 *)(iVar1 + 0x1ba) = 1;
  *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfd;
  *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfe;
  *(undefined2 *)(iVar1 + 0x378) = 0;
  *(byte *)(iVar1 + 0x37d) = *(byte *)(iVar1 + 0x37d) & 0xfc;
  *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0x3f;
  *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0xdf;
  RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x278);
  if ((*(short *)(iVar1 + 0x37a) != 3) || (*(short *)(iVar1 + 0x37a) != 4)) {
    *(undefined2 *)(iVar1 + 0x37a) = 1;
  }
  *(undefined2 *)(iVar1 + 0x376) = 0;
  return;
}

/* JP: 0x004a18c0  FieldMessage::EnableKeyWait(short)   [EnableKeyWait__12FieldMessageFs]  size=0x94 */
void EnableKeyWait__12FieldMessageFs(int param_1,byte param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  *(byte *)(iVar1 + 0x1be) = *(byte *)(iVar1 + 0x1be) & 0xbf | 0x40;
  *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0xf0 | param_2 & 0xf;
  if (*(short *)(iVar1 + 0x37a) == 1) {
    StartKeyWait__12FieldMessageFv(param_1);
  }
  return;
}

/* JP: 0x004a1960  FieldMessage::SetSelectMessage(char*)   [SetSelectMessage__12FieldMessageFPc]  size=0xac */
undefined4 SetSelectMessage__12FieldMessageFPc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 0x18);
  lVar3 = OpenMessage__12FieldMessageFPc(param_1,param_2);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    if (-1 < (long)((ulong)*(byte *)(iVar1 + 0x37c) << 0x3b)) {
      Return__11MenuMessageFv(iVar1 + 0x104);
    }
    *(undefined1 *)(iVar1 + 0x124) = 1;
    *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0xdf | 0x20;
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a1a10  FieldMessage::StartSelect(short)   [StartSelect__12FieldMessageFs]  size=0x174 */
undefined4 StartSelect__12FieldMessageFs(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  iVar1 = *(int *)(param_1 + 0x18);
  lVar3 = SetCursor__12FieldMessageFs(param_1,param_2);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    QuickMove__6CursorFv(iVar1 + 0x278);
    ClearAfter__6CursorFv(iVar1 + 0x278);
    *(undefined4 *)(iVar1 + 0x36c) = 0;
    SetVertex__6CursorFv(iVar1 + 0x278);
    *(undefined2 *)(iVar1 + 0x378) = param_2;
    *(byte *)(iVar1 + 0x37d) = *(byte *)(iVar1 + 0x37d) & 0xfc;
    *(byte *)(iVar1 + 0x37c) = *(byte *)(iVar1 + 0x37c) & 0x3f;
    if ((*(short *)(iVar1 + 0x37a) == 1) || (*(char *)(iVar1 + 0x124) == '\x01')) {
      *(undefined2 *)(iVar1 + 0x37a) = 0xf;
      *(byte *)(iVar1 + 0x28a) = *(byte *)(iVar1 + 0x28a) & 0xfe | 1;
    }
    Finish__11MenuMessageFv(iVar1 + 0x104);
    AddPriority__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0xc) + 0x2c,iVar1 + 0x278);
    iVar1 = GetActive__4CPadFi(0);
    *(undefined4 *)(iVar1 + 8) = @4403;
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a1b90  FieldMessage::SetPosition(float, float)   [SetPosition__12FieldMessageFff]  size=0xa8 */
void SetPosition__12FieldMessageFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_3 + 0x18);
  if (((ulong)*(ushort *)(iVar1 + 0xc0) & 0x1ff) >> 6 == 3) {
    SetPosition__10MenuWindowFff(*(undefined4 *)(iVar1 + 0x74),param_2,iVar1 + 0x10);
  }
  else {
    SetPosition__10MenuWindowFff(param_1,param_2,iVar1 + 0x10);
  }
  return;
}

/* JP: 0x004a1c40  FieldMessage::SetSize(short, short)   [SetSize__12FieldMessageFss]  size=0x130 */
void SetSize__12FieldMessageFss(int param_1,short param_2,short param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  ulong uVar4;
  float fVar5;
  
  iVar1 = *(int *)(param_1 + 0x18);
  uVar2 = GetRealWidth__8FontItemCFv(iVar1 + 0x104);
  uVar3 = GetRealHeight__8FontItemCFv(iVar1 + 0x104);
  SetSize__10MenuWindowFff((float)(int)((int)param_2 * (uVar2 & 0xff)),
                  (float)(int)((int)param_3 * (uVar3 & 0xff)),iVar1 + 0x10);
  uVar4 = GetRealHeight__8FontItemCFv(iVar1 + 0x104);
  if ((long)uVar4 < 0) {
    fVar5 = (float)(uVar4 & 0xffffffff);
  }
  else {
    fVar5 = (float)(int)uVar4;
  }
  *(undefined4 *)(*(int *)(iVar1 + 0x50) + 0x1c) = *(undefined4 *)(iVar1 + 0x7c);
  *(float *)(*(int *)(iVar1 + 0x50) + 0x20) = fVar5;
  *(undefined2 *)(*(int *)(iVar1 + 0x50) + 0x18) = 0;
  *(short *)(*(int *)(iVar1 + 0x50) + 0x1a) = param_3;
  *(short *)(iVar1 + 0x374) = param_3;
  return;
}

/* JP: 0x004a1d70  FieldMessage::StartKeyWait()   [StartKeyWait__12FieldMessageFv]  size=0x8c */
void StartKeyWait__12FieldMessageFv(int param_1)

{
  int iVar1;
  ulong uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  SetPosition__7KeyWaitFi(iVar1 + 0x19c,1);
  *(undefined2 *)(iVar1 + 0x37a) = 0xe;
  *(undefined2 *)(iVar1 + 0x1ba) = 10;
  uVar2 = (ulong)*(byte *)(iVar1 + 0x1ae) & 0xfffffffffffffffd | 2;
  *(char *)(iVar1 + 0x1ae) = (char)uVar2;
  *(byte *)(iVar1 + 0x1ae) = *(byte *)(iVar1 + 0x1ae) & 0xfe | (byte)((uVar2 << 0x3e) >> 0x3f);
  return;
}

/* JP: 0x004a1e00  FieldMessage::SetCursor(short)   [SetCursor__12FieldMessageFs]  size=0xc4 */
undefined4 SetCursor__12FieldMessageFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  short sStack_10;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if ((param_2 < 0) ||
     (iStack_20 = param_1, sStack_10 = param_2,
     lVar3 = GetRect__11MenuMessageFUsP8DrawRect(iVar1 + 0x104,param_2,&fStack_30), lVar3 == 0)) {
    uVar2 = 0;
  }
  else {
    SetTarget__6CursorFP8DrawRect(iVar1 + 0x278,&fStack_30);
    fStack_28 = fStack_30 + fStack_28;
    fStack_24 = fStack_2c + fStack_24;
    Scroll__10MenuWindowFP8DrawRect(iVar1 + 0x10,&fStack_30);
    *(short *)(iVar1 + 0x378) = sStack_10;
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a1ed0  FieldMessage::Polling()   [Polling__12FieldMessageFv]  size=0xb58 */
undefined8 Polling__12FieldMessageFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  bool bVar6;
  int iVar7;
  long lVar8;
  byte bVar9;
  short unaff_s1_lo;
  short sStack_1c;
  short sStack_18;
  short sStack_16;
  
  iVar5 = *(int *)(param_1 + 0x18);
  iVar7 = GetActive__4CPadFi(0);
  uVar2 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar7 + 4) * 4) + 0x6a);
  uVar3 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar7 + 4) * 4) + 0x6c);
  uVar4 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar7 + 4) * 4) + 0x70);
  sVar1 = *(short *)(iVar5 + 0x37a);
  if (sVar1 == 0xe) {
    if ((char)*(undefined2 *)(iVar5 + 0x1ba) == '\r') {
      *(undefined2 *)(iVar5 + 0x37a) = 1;
    }
  }
  else if (sVar1 == 4) {
    if ((*(char *)(iVar5 + 0xb8) == '\x01') || (*(char *)(iVar5 + 0xb8) == '\0')) {
      bVar6 = true;
    }
    else {
      bVar6 = false;
    }
    if (bVar6) {
      *(undefined2 *)(iVar5 + 0x37a) = 0;
    }
  }
  else if (sVar1 == 3) {
    if ((*(char *)(iVar5 + 0xb8) == '\x01') || (*(char *)(iVar5 + 0xb8) == '\0')) {
      bVar6 = true;
    }
    else {
      bVar6 = false;
    }
    if (bVar6) {
      lVar8 = (ulong)*(byte *)(iVar5 + 0x37c) << 0x3a;
      if (lVar8 < 0) {
        *(undefined2 *)(iVar5 + 0x37a) = 0xf;
        *(byte *)(iVar5 + 0x28a) = *(byte *)(iVar5 + 0x28a) & 0xfe | 1;
      }
      else if (-1 < lVar8) {
        *(undefined2 *)(iVar5 + 0x37a) = 9;
      }
    }
  }
  else if (sVar1 == 0xf) {
    bVar9 = *(byte *)(iVar5 + 0x37c) >> 6;
    if (bVar9 == 2) {
      if ((uVar2 & 0x2000) == 0) {
        *(undefined2 *)(iVar5 + 0x37a) = 1;
        *(byte *)(iVar5 + 0x37c) = *(byte *)(iVar5 + 0x37c) & 0xdf;
        PlaySE__9MenuSoundFUiUcP8_SeParam(sm_pSound__7MenuObj,2,0,0);
        *(undefined4 *)(iVar7 + 8) = @4499;
      }
    }
    else if (bVar9 == 1) {
      if ((uVar3 & 0x2000) != 0) {
        *(byte *)(iVar5 + 0x37c) =
             *(byte *)(iVar5 + 0x37c) & 0x3f |
             (byte)(((uint)(((ulong)*(byte *)(iVar5 + 0x37c) << 0x38) >> 0x3e) + 1 & 3) << 6);
      }
    }
    else if ((bVar9 == 0) && ((uVar2 & 0x2000) == 0)) {
      *(byte *)(iVar5 + 0x37c) =
           *(byte *)(iVar5 + 0x37c) & 0x3f |
           (byte)(((uint)(((ulong)*(byte *)(iVar5 + 0x37c) << 0x38) >> 0x3e) + 1 & 3) << 6);
    }
    if ((long)((ulong)*(byte *)(iVar5 + 0x373) << 0x3a) < 0) {
      bVar9 = *(byte *)(iVar5 + 0x37d) & 3;
      if (bVar9 == 2) {
        if ((uVar2 & 0x4000) == 0) {
          *(undefined2 *)(iVar5 + 0x37a) = 1;
          *(undefined2 *)(iVar5 + 0x378) = 0xffff;
          *(byte *)(iVar5 + 0x37c) = *(byte *)(iVar5 + 0x37c) & 0xdf;
          PlaySE__9MenuSoundFUiUcP8_SeParam(sm_pSound__7MenuObj,3,0,0);
          *(undefined4 *)(iVar7 + 8) = @4512;
        }
      }
      else if (bVar9 == 1) {
        if ((uVar3 & 0x4000) != 0) {
          *(byte *)(iVar5 + 0x37d) =
               *(byte *)(iVar5 + 0x37d) & 0xfc | (*(byte *)(iVar5 + 0x37d) & 3) + 1 & 3;
        }
      }
      else if (((*(byte *)(iVar5 + 0x37d) & 3) == 0) && ((uVar2 & 0x4000) == 0)) {
        *(byte *)(iVar5 + 0x37d) =
             *(byte *)(iVar5 + 0x37d) & 0xfc | (*(byte *)(iVar5 + 0x37d) & 3) + 1 & 3;
      }
    }
    if ((long)((ulong)*(byte *)(iVar5 + 0x37c) << 0x3b) < 0) {
      if (((ulong)*(byte *)(iVar5 + 0x37c) & 0x1f) >> 4 == 1) {
        if ((uVar4 & 0x80) == 0) {
          if ((uVar4 & 0x20) == 0) {
            return 0;
          }
          unaff_s1_lo = *(short *)(iVar5 + 0x378) + 1;
          if (unaff_s1_lo < 0) {
            unaff_s1_lo = *(short *)(*(int *)(param_1 + 0x18) + 0x180) + -1;
          }
          else if (*(short *)(*(int *)(param_1 + 0x18) + 0x180) <= unaff_s1_lo) {
            unaff_s1_lo = 0;
          }
        }
        else {
          unaff_s1_lo = *(short *)(iVar5 + 0x378) + -1;
          if (unaff_s1_lo < 0) {
            unaff_s1_lo = *(short *)(*(int *)(param_1 + 0x18) + 0x180) + -1;
          }
          else if (*(short *)(*(int *)(param_1 + 0x18) + 0x180) <= unaff_s1_lo) {
            unaff_s1_lo = 0;
          }
        }
      }
    }
    else if ((uVar4 & 0x10) == 0) {
      if ((uVar4 & 0x40) == 0) {
        return 0;
      }
      unaff_s1_lo = *(short *)(iVar5 + 0x378) + 1;
      if (unaff_s1_lo < 0) {
        unaff_s1_lo = *(short *)(*(int *)(param_1 + 0x18) + 0x180) + -1;
      }
      else if (*(short *)(*(int *)(param_1 + 0x18) + 0x180) <= unaff_s1_lo) {
        sStack_1c = 0;
        unaff_s1_lo = sStack_1c;
      }
    }
    else {
      unaff_s1_lo = *(short *)(iVar5 + 0x378) + -1;
      if (unaff_s1_lo < 0) {
        unaff_s1_lo = *(short *)(*(int *)(param_1 + 0x18) + 0x180) + -1;
      }
      else if (*(short *)(*(int *)(param_1 + 0x18) + 0x180) <= unaff_s1_lo) {
        sStack_18 = 0;
        unaff_s1_lo = sStack_18;
      }
    }
    if (unaff_s1_lo != *(short *)(iVar5 + 0x378)) {
      SetCursor__12FieldMessageFs(param_1,unaff_s1_lo);
      *(short *)(iVar5 + 0x378) = unaff_s1_lo;
      PlaySE__9MenuSoundFUiUcP8_SeParam(sm_pSound__7MenuObj,0,0,0);
    }
  }
  else if (sVar1 == 9) {
    if (((long)((ulong)*(byte *)(iVar5 + 0x1be) << 0x39) < 0) && ((uVar3 & 0x6000) != 0)) {
      Finish__11MenuMessageFv(iVar5 + 0x104);
    }
    if (*(short *)(iVar5 + 0x17e) == 0) {
      sStack_16 = 0;
    }
    else {
      iVar7 = GetFontPacket__14PluralFontItemCFUc(iVar5 + 0x104,0);
      sStack_16 = *(short *)(iVar7 + (uint)*(ushort *)(iVar5 + 0x17e) * 0x30 + -0x22);
    }
    if ((long)sStack_16 < (long)((int)*(short *)(iVar5 + 0x376) + (int)*(short *)(iVar5 + 0x374))) {
      if (sStack_16 < *(short *)(iVar5 + 0x376)) {
        *(short *)(iVar5 + 0x376) = sStack_16;
        Scroll__10MenuWindowFss(iVar5 + 0x10,0,*(undefined2 *)(iVar5 + 0x376));
      }
    }
    else {
      *(short *)(iVar5 + 0x376) = sStack_16 - (*(short *)(iVar5 + 0x374) + -1);
      Scroll__10MenuWindowFss(iVar5 + 0x10,0,*(undefined2 *)(iVar5 + 0x376));
    }
    if (*(ushort *)(iVar5 + 0x17a) <= *(ushort *)(iVar5 + 0x184)) {
      if ((long)((ulong)*(byte *)(iVar5 + 0x1be) << 0x39) < 0) {
        StartKeyWait__12FieldMessageFv(param_1);
      }
      else {
        *(undefined2 *)(iVar5 + 0x37a) = 1;
      }
    }
  }
  return 0;
}

/* JP: 0x004b5220  FieldMessage::SetVariable(unsigned char)   [SetVariable__12FieldMessageFUc]  size=0x38 */
void SetVariable__12FieldMessageFUc(int param_1,undefined1 param_2)

{
  SetVariable__8FontItemFUc(*(int *)(param_1 + 0x18) + 0x104,param_2);
  return;
}

/* JP: 0x004b55e0  FieldMessage::GetState   [GetState__12FieldMessageCFv]  size=0x20 */
undefined2 GetState__12FieldMessageCFv(int param_1)

{
  return *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x37a);
}

/* JP: 0x004b6170  FieldMessage::SetCancel(unsigned char)   [SetCancel__12FieldMessageFUc]  size=0x38 */
void SetCancel__12FieldMessageFUc(int param_1,undefined1 param_2)

{
  SetCancel__6CursorFUc(*(int *)(param_1 + 0x18) + 0x278,param_2);
  return;
}

/* JP: 0x004b61f0  FieldMessage::SetSelectMode(unsigned char)   [SetSelectMode__12FieldMessageFUc]  size=0x40 */
void SetSelectMode__12FieldMessageFUc(int param_1,byte param_2)

{
  *(byte *)(*(int *)(param_1 + 0x18) + 0x37c) =
       *(byte *)(*(int *)(param_1 + 0x18) + 0x37c) & 0xef | (param_2 & 1) << 4;
  return;
}

/* JP: 0x004b64a0  FieldMessage::GetResult   [GetResult__12FieldMessageCFv]  size=0x20 */
undefined2 GetResult__12FieldMessageCFv(int param_1)

{
  return *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x378);
}
