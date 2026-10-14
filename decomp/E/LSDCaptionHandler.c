/*
 * LSDCaptionHandler.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 10 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0028a5c0 size 0x44  LSDCaptionHandler::LSDCaptionHandler(v)
 *      mangled: __ct__17LSDCaptionHandlerFv */
int __ct__17LSDCaptionHandlerFv(int param_1)

{
  __ct__16LSDDeviceHandlerFv(param_1);
  *(u8 **)(param_1 + 0x10) = __vt__17LSDCaptionHandler;
  *(u32 *)(param_1 + 0x14) = 0;
  return param_1;
}

/* ---- 0x0028a610 size 0x74  LSDCaptionHandler::~LSDCaptionHandler(v)
 *      mangled: __dt__17LSDCaptionHandlerFv */
int __dt__17LSDCaptionHandlerFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x10) = __vt__17LSDCaptionHandler;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0028a690 size 0x44  LSDCaptionHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__17LSDCaptionHandlerFP12_LSDTrackHdr */
bool CheckData__17LSDCaptionHandlerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x44544253;
}

/* ---- 0x0028a6e0 size 0x128  LSDCaptionHandler::Open(P10RingBuffer)
 *      mangled: Open__17LSDCaptionHandlerFP10RingBuffer */
u32 * Open__17LSDCaptionHandlerFP10RingBuffer(int param_1,u32 param_2)

{
  int iVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  u32 *puVar5;
  
  lVar4 = __nw__FUi(0x270);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__14LSDCaptionDataFv(lVar4);
  }
  *(u32 *)(param_1 + 0x14) = uVar3;
  iVar1 = *(int *)(param_1 + 0x14);
  puVar5 = (u32 *)(iVar1 + 0xc);
  iVar2 = *(int *)(param_1 + 0x14);
  getReadData__10RingBufferFPvUlUl(param_2,(u32 *)(iVar2 + 0x1c),0x20,0);
  *puVar5 = *(u32 *)(iVar2 + 0x1c);
  *(int *)(iVar1 + 0x14) = param_1;
  *(int *)(iVar1 + 0x18) = param_1;
  if (*(short *)(iVar2 + 0x2e) == 0) {
    lVar4 = __nw__FUi(0x10);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__9BufMemoryFUlUi(lVar4,*(int *)(iVar2 + 0x34) << 4,0x80);
    }
    *(u32 *)(*(int *)(param_1 + 0x14) + 0x3c) = uVar3;
  }
  else {
    puVar5 = (u32 *)0x0;
  }
  return puVar5;
}

/* ---- 0x0028a810 size 0x46c  LSDCaptionHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__17LSDCaptionHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__17LSDCaptionHandlerFP10_LSDHANDLEP10RingBuffer
              (int param_1,u64 param_2,int *param_3)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  u64 uVar7;
  FontItem *pFVar8;
  MenuWindow *this;
  uint uVar9;
  int *piVar10;
  FontItem *pFVar11;
  int iVar12;
  
  if (param_3[4] == 0) {
    iVar12 = 0;
  }
  else {
    iVar12 = *param_3;
  }
  getReadData__10RingBufferFPvUlUl
            (param_3,*(u32 *)(*(int *)(*(int *)(param_1 + 0x14) + 0x3c) + 4),
             *(int *)(iVar12 + 8) << 4,0x10);
  psVar3 = *(short **)(*(int *)(*(int *)(param_1 + 0x14) + 0x3c) + 4);
  *(short **)(*(int *)(param_1 + 0x14) + 0x40) = psVar3;
  *(int *)(psVar3 + 10) = (int)psVar3 + *(int *)(psVar3 + 10);
  *(int *)(psVar3 + 0xc) = (int)psVar3 + *(int *)(psVar3 + 0xc);
  sVar1 = *psVar3;
  iVar4 = *(int *)(psVar3 + 10);
  piVar10 = *(int **)(psVar3 + 0xc);
  sVar2 = psVar3[1];
  iVar5 = *(int *)(psVar3 + 0xc);
  iVar6 = *(int *)(param_1 + 0x14);
  this = (MenuWindow *)(iVar6 + 0x48);
  for (uVar9 = *(uint *)(psVar3 + 10); uVar9 < (uint)(iVar4 + sVar1 * 0x20); uVar9 = uVar9 + 0x20) {
    *(int *)(uVar9 + 4) = *(int *)(uVar9 + 4) + (int)psVar3;
    if (*(int *)(uVar9 + 0xc) != 0) {
      *(int *)(uVar9 + 0xc) = *(int *)(uVar9 + 0xc) + (int)psVar3;
    }
  }
  for (; piVar10 < (int *)(iVar5 + sVar2 * 0x10); piVar10 = piVar10 + 4) {
    *piVar10 = *piVar10 + (int)psVar3;
  }
  CreateFont__4FontFiPUc(2,(int)psVar3 + *(int *)(psVar3 + 6));
  if (*(int *)(psVar3 + 8) != 0) {
    CreateFont__4FontFiPUc(3,(int)psVar3 + *(int *)(psVar3 + 8));
  }
  Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster
            (*(int *)(param_1 + 0x14) + 0xfc,0x2c,0x280,0x200,0,0,0);
  AddPriority__12MenuObjTableFP7MenuObj
            ((MenuObjTable *)(iVar6 + 0x60),(MenuObj *)(*(int *)(param_1 + 0x14) + 0xfc));
  iVar4 = *(int *)(param_1 + 0x14);
  for (pFVar8 = (FontItem *)(iVar4 + 0x13c); pFVar8 < (FontItem *)(iVar4 + 0x26c);
      pFVar8 = (FontItem *)((int)&pFVar8[1].flH + 1)) {
    (**(code **)((int)pFVar8->pVptr + 0x60))(pFVar8,psVar3[2],(char)psVar3[5]);
    pFVar8->nPriority = 1;
    SetFontNumber__8FontItemFUc(pFVar8,2);
    AddPlace__10MenuWindowFP9MenuPlace(this,(MenuPlace *)pFVar8);
  }
  if (psVar3[4] != 0) {
    sVar1 = psVar3[4];
    uVar7 = __nwa__FUi((sVar1 * 0x12 + (int)sVar1) * 8 + 0x10);
    pFVar8 = (FontItem *)__construct_new_array(uVar7,0x27d490,0x27d4f0,0x98,sVar1);
    *(FontItem **)(*(int *)(param_1 + 0x14) + 0x26c) = pFVar8;
    pFVar11 = (FontItem *)((int)pFVar8 + (psVar3[4] * 0x12 + (int)psVar3[4]) * 8);
    for (; pFVar8 < pFVar11; pFVar8 = (FontItem *)((int)&pFVar8[1].flH + 1)) {
      (**(code **)((int)pFVar8->pVptr + 0x60))(pFVar8,psVar3[3],*(u8 *)((int)psVar3 + 0xb));
      pFVar8->nPriority = 1;
      SetFontNumber__8FontItemFUc(pFVar8,3);
      AddPlace__10MenuWindowFP9MenuPlace(this,(MenuPlace *)pFVar8);
    }
  }
  *(byte *)(iVar6 + 0xf8) = *(byte *)(iVar6 + 0xf8) & 0xf8;
  *(byte *)(iVar6 + 0xf8) = *(byte *)(iVar6 + 0xf8) & 199;
  Create__10MenuWindowFUcUcffff(this,0,0,0.0,0.0,512.0,448.0);
  *(byte *)(iVar6 + 0x5a) = *(byte *)(iVar6 + 0x5a) & 0xfe;
  AddOT__7MenuObjFv((MenuObj *)this);
  return *(int *)(iVar12 + 8) * 0x10 + 0x10;
}

/* ---- 0x0028ac80 size 0x36c  LSDCaptionHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__17LSDCaptionHandlerFP10_LSDHANDLEiff */
void Event__17LSDCaptionHandlerFP10_LSDHANDLEiff(float param_1,int param_2)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  if ((*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x275) & 3) == 0) {
    iVar2 = *(int *)(param_2 + 0x14);
    if ((*(int *)(*(int *)(param_2 + 0x14) + 0x44) != 0) &&
       (*(float *)(*(int *)(*(int *)(param_2 + 0x14) + 0x44) + 0x18) <= param_1)) {
      Close__10MenuWindowFUci
                ((MenuWindow *)(iVar2 + 0x48),
                 (byte)(((ulong)*(byte *)(iVar2 + 0xf8) << 0x3a) >> 0x3d),
                 (int)*(short *)(*(int *)(*(int *)(param_2 + 0x14) + 0x40) + 0x1e));
      *(u32 *)(*(int *)(param_2 + 0x14) + 0x44) = 0;
    }
    if (*(int *)(*(int *)(param_2 + 0x14) + 0x44) == 0) {
      uVar4 = *(uint *)(*(int *)(*(int *)(param_2 + 0x14) + 0x40) + 0x14);
      uVar3 = uVar4 + **(short **)(*(int *)(param_2 + 0x14) + 0x40) * 0x20;
      for (; uVar4 < uVar3; uVar4 = uVar4 + 0x20) {
        if ((*(float *)(uVar4 + 0x14) <= param_1) && (param_1 < *(float *)(uVar4 + 0x18))) {
          iVar5 = *(int *)(param_2 + 0x14);
          *(uint *)(*(int *)(param_2 + 0x14) + 0x44) = uVar4;
          ClearImage__8FontDrawFv(iVar5 + 0xfc);
          iVar5 = *(int *)(param_2 + 0x14) + 0x13c;
          for (iVar7 = 0; iVar7 < 2; iVar7 = iVar7 + 1) {
            *(byte *)(iVar5 + 0x12) = *(byte *)(iVar5 + 0x12) & 0xfe;
            if (*(int *)(uVar4 + iVar7 * 8 + 4) != 0) {
              SetWords__17LSDCaptionHandlerFP11MenuMessageP12LSDWordsDataP12LSDWordsInfo
                        (param_2,iVar5,uVar4 + iVar7 * 8 + 4,uVar4);
            }
            iVar5 = iVar5 + 0x98;
          }
          if (*(int *)(*(int *)(param_2 + 0x14) + 0x26c) != 0) {
            uVar6 = *(int *)(*(int *)(*(int *)(param_2 + 0x14) + 0x40) + 0x18) +
                    *(short *)(uVar4 + 0x1c) * 0x10;
            uVar8 = uVar6 + *(short *)(uVar4 + 0x1e) * 0x10;
            uVar4 = *(uint *)(*(int *)(param_2 + 0x14) + 0x26c);
            sVar1 = *(short *)(*(int *)(*(int *)(param_2 + 0x14) + 0x40) + 8);
            uVar3 = uVar4 + (sVar1 * 0x12 + (int)sVar1) * 8;
            for (; uVar6 < uVar8; uVar6 = uVar6 + 0x10) {
              SetWords__17LSDCaptionHandlerFP11MenuMessageP12LSDWordsDataP12LSDWordsInfo
                        (param_2,uVar4,uVar6,uVar6 + 8);
              uVar4 = uVar4 + 0x98;
            }
            for (; uVar4 < uVar3; uVar4 = uVar4 + 0x98) {
              *(byte *)(uVar4 + 0x12) = *(byte *)(uVar4 + 0x12) & 0xfe;
            }
          }
          Open__10MenuWindowFUci
                    ((MenuWindow *)(iVar2 + 0x48),*(byte *)(iVar2 + 0xf8) & 7,
                     (int)*(short *)(*(int *)(*(int *)(param_2 + 0x14) + 0x40) + 0x1c));
          return;
        }
      }
    }
  }
  return;
}

/* ---- 0x0028aff0 size 0x6c  LSDCaptionHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__17LSDCaptionHandlerFP10_LSDHANDLE */
u32 Close__17LSDCaptionHandlerFP10_LSDHANDLE(int param_1)

{
  ReleaseOT__7MenuObjFv((MenuObj *)(*(int *)(param_1 + 0x14) + 0x48));
  (**(code **)(*(int *)(*(int *)(param_1 + 0x14) + 8) + 0xc))();
  *(u32 *)(param_1 + 0x14) = 0;
  ClearFont__4FontFi(3);
  ClearFont__4FontFi(2);
  return 1;
}

/* ---- 0x0028b060 size 0x1a8  LSDCaptionHandler::SetWords(P11MenuMessageP12LSDWordsDataP12LSDWordsInfo)
 *      mangled: SetWords__17LSDCaptionHandlerFP11MenuMessageP12LSDWordsDataP12LSDWordsInfo */
void SetWords__17LSDCaptionHandlerFP11MenuMessageP12LSDWordsDataP12LSDWordsInfo
               (int param_1,MenuMessage *param_2,u32 *param_3,byte *param_4)

{
  byte bVar1;
  
  (**(code **)((int)param_2->pVptr + 0x24))
            ((float)(int)*(short *)(param_3 + 1),(float)(int)*(short *)((int)param_3 + 6));
  param_2->bFflags =
       param_2->bFflags & 0xf7 | (byte)((uint)(((ulong)param_4[2] << 0x38) >> 0x3f) << 3);
  bVar1 = param_4[1];
  param_2->bShadow_x = *param_4;
  param_2->bShadow_y = bVar1;
  bVar1 = param_4[2];
  param_2->bFflags2 =
       param_2->bFflags2 & 0xbf | (byte)((uint)(((ulong)param_4[2] << 0x39) >> 0x3f) << 6);
  param_2->bFflags2 = param_2->bFflags2 & 199 | (byte)((uint)(((ulong)bVar1 << 0x3a) >> 0x3d) << 3);
  ClearMessage__11MenuMessageFv(param_2);
  Order__8FontDrawFP11MenuMessagePc(*(int *)(param_1 + 0x14) + 0xfc,param_2,*param_3);
  Finish__11MenuMessageFv(param_2);
  param_2->bFlags = param_2->bFlags & 0xfe | 1;
  return;
}

/* ---- 0x0028b210 size 0xa8  LSDCaptionData::LSDCaptionData(v)
 *      mangled: __ct__14LSDCaptionDataFv */
u32 * __ct__14LSDCaptionDataFv(u32 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = __vt__17DelayDeleteObject;
  param_1[2] = __vt__14LSDCaptionData;
  param_1[0x11] = 0;
  __ct__10MenuWindowFv((MenuWindow *)(param_1 + 0x12));
  __ct__8FontDrawFv(param_1 + 0x3f);
  __construct_array(param_1 + 0x4f,0x27d490,0x27d4f0,0x98,2);
  param_1[0x9b] = 0;
  return param_1;
}

/* ---- 0x0028b2c0 size 0x10c  LSDCaptionData::~LSDCaptionData(v)
 *      mangled: __dt__14LSDCaptionDataFv */
int __dt__14LSDCaptionDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 8) = __vt__14LSDCaptionData;
    if (*(int *)(param_1 + 0x26c) != 0) {
      __destroy_new_array(*(u32 *)(param_1 + 0x26c),0x27d4f0);
    }
    __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x3c),1);
    __destroy_arr(param_1 + 0x13c,0x27d4f0,0x98,2);
    __dt__8FontDrawFv(param_1 + 0xfc,0xffffffffffffffff);
    __dt__10MenuWindowFv((MenuWindow *)(param_1 + 0x48));
    if (param_1 != 0) {
      *(u8 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

