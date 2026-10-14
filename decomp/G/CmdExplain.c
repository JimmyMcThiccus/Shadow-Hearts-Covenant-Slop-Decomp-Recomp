/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdExplain   functions: 14
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdExplain.md).
 */

/* JP: 0x0043ea00  CmdExplain::CmdExplain()   [__ct__10CmdExplainFv]  size=0x1b8 */
int __ct__10CmdExplainFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdExplain;
  __ct__10MenuWindowFv(param_1 + 0x6c);
  __ct__7KeyWaitFv(param_1 + 0x120);
  __ct__8FontDrawFv(param_1 + 0x1fc);
  __ct__11MenuMessageFv(param_1 + 0x23c);
  __ct__8FontDrawFv(param_1 + 0x2d4);
  __ct__8MenuTextFv(param_1 + 0x314);
  __ct__8MenuTextFv(param_1 + 0x394);
  __construct_array(param_1 + 0x414,0x276640,0x2766d0,0x84,2);
  *(undefined4 *)(param_1 + 0x51c) = 0;
  *(undefined4 *)(param_1 + 0x520) = 0;
  *(undefined2 *)(param_1 + 0x526) = 0x1000;
  *(undefined1 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x21) = 0;
  *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xfd;
  *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xfb;
  *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf;
  *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf0;
  *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xf7 | 8;
  return param_1;
}

/* JP: 0x0043ebc0  CmdExplain::~CmdExplain()   [__dt__10CmdExplainFv]  size=0x1ec */
int __dt__10CmdExplainFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdExplain;
    if (*(int *)(param_1 + 0x520) != 0) {
      iVar1 = *(int *)(param_1 + 0x520);
      if (iVar1 != 0) {
        __dt__10MenuSpriteFv(iVar1 + 0x128,0xffffffffffffffff);
        __dt__11SendOnLocalFv(iVar1 + 0xf8,0xffffffffffffffff);
        __dt__11MenuTextureFv(iVar1 + 0xb8,0xffffffffffffffff);
        __dt__10MenuWindowFv(iVar1,0xffffffffffffffff);
        __dl__FPv(iVar1);
      }
    }
    if (*(int *)(param_1 + 0x51c) != 0) {
      iVar1 = *(int *)(param_1 + 0x51c);
      if (iVar1 != 0) {
        __dt__10MenuSpriteFv(iVar1 + 0x30,0xffffffffffffffff);
        __dt__11SendOnLocalFv(iVar1,0xffffffffffffffff);
        __dl__FPv(iVar1);
      }
    }
    __destroy_arr(param_1 + 0x414,0x2766d0,0x84,2);
    __dt__8MenuTextFv(param_1 + 0x394,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x314,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x2d4,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x23c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x1fc,0xffffffffffffffff);
    __dt__7KeyWaitFv(param_1 + 0x120,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x6c,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0043edb0  CmdExplain::GetReady()   [GetReady__10CmdExplainFv]  size=0x1b8 */
undefined4 GetReady__10CmdExplainFv(int param_1)

{
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x1fc);
  SetData__9MenuSceneFUsP8FontDraw(param_1,1,param_1 + 0x2d4);
  SetData__9MenuSceneFUsP11MenuMessage(param_1,0,param_1 + 0x23c);
  SetData__9MenuSceneFUsP8MenuText(param_1,0,param_1 + 0x314);
  SetData__9MenuSceneFUsP8MenuText(param_1,1,param_1 + 0x394);
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,0,param_1 + 0x414);
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,1,param_1 + 0x498);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x6c);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x84,param_1 + 0x1fc);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x84,param_1 + 0x2d4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,param_1 + 0x23c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,param_1 + 0x314);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,param_1 + 0x394);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,param_1 + 0x414);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,param_1 + 0x498);
  Create__7KeyWaitFv(param_1 + 0x120);
  *(int *)(param_1 + 0xb4) = param_1 + 0x120;
  *(int *)(param_1 + 0x138) = param_1 + 0x6c;
  return 1;
}

/* JP: 0x0043ef70  CmdExplain::DelayDelete()   [DelayDelete__10CmdExplainFv]  size=0x5c */
void DelayDelete__10CmdExplainFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x6c);
  if (*(int *)(param_1 + 0x520) != 0) {
    ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x520));
  }
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x0043efd0  CmdExplain::SetInfo(Menu*, short, unsigned char, unsigned char)   [SetInfo__10CmdExplainFP4MenusUcUc]  size=0x100 */
void SetInfo__10CmdExplainFP4MenusUcUc
               (int param_1,undefined4 param_2,short param_3,byte param_4,byte param_5)

{
  if (1 < param_3) {
    CreateScrollMark__10MenuWindowFUc(param_1 + 0x6c,param_4);
    *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xfd | 2;
  }
  *(undefined4 *)(param_1 + 0x10) = param_2;
  *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf0 | param_4 & 0xf;
  *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xef | (param_5 & 1) << 4;
  *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xfb;
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  return;
}

/* JP: 0x0043f0d0  CmdExplain::SetIcon(MenuTexture*)   [SetIcon__10CmdExplainFP11MenuTexture]  size=0x148 */
void SetIcon__10CmdExplainFP11MenuTexture(int param_1,int param_2)

{
  int iVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x90);
  if (lVar2 != 0) {
    __ct__11SendOnLocalFv(lVar2);
    __ct__10MenuSpriteFv((int)lVar2 + 0x30);
  }
  *(int *)(param_1 + 0x51c) = (int)lVar2;
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,*(int *)(param_1 + 0x51c) + 0x30);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(*(undefined4 *)(param_1 + 0x51c),param_2 + 0x18,*(undefined4 *)(param_2 + 0x14),1,
                  0xffffffffffffffff);
  iVar1 = *(int *)(param_1 + 0x51c);
  *(undefined4 *)(iVar1 + 0x8c) = *(undefined4 *)(param_1 + 0x51c);
  *(byte *)(iVar1 + 0x42) = *(byte *)(iVar1 + 0x42) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x6c,*(int *)(param_1 + 0x51c) + 0x30);
  return;
}

/* JP: 0x0043f220  CmdExplain::SetImage(char*, short, short)   [SetImage__10CmdExplainFPcss]  size=0x1b8 */
void SetImage__10CmdExplainFPcss(int param_1,undefined4 param_2,undefined2 param_3,short param_4)

{
  long lVar1;
  int iVar2;
  
  DestroyImage__10CmdExplainFv(param_1);
  lVar1 = __nw__FUi(0x188);
  iVar2 = (int)lVar1;
  if (lVar1 != 0) {
    __ct__10MenuWindowFv(lVar1);
    __ct__11MenuTextureFv(iVar2 + 0xb8);
    __ct__11SendOnLocalFv(iVar2 + 0xf8);
    __ct__10MenuSpriteFv(iVar2 + 0x128);
  }
  *(int *)(param_1 + 0x520) = iVar2;
  *(undefined4 *)(*(int *)(param_1 + 0x520) + 0xb4) = param_2;
  SetData__9MenuSceneFUsP10MenuSprite(param_1,param_3,*(int *)(param_1 + 0x520) + 0x128);
  iVar2 = *(int *)(param_1 + 0x520);
  *(int *)(iVar2 + 0x184) = *(int *)(param_1 + 0x520) + 0xf8;
  *(byte *)(iVar2 + 0x13a) = *(byte *)(iVar2 + 0x13a) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(*(undefined4 *)(param_1 + 0x520),*(int *)(param_1 + 0x520) + 0x128);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,param_4,*(undefined4 *)(param_1 + 0x520));
  if (param_4 == 0) {
    *(short *)(*(int *)(param_1 + 0x520) + 0x14) = *(short *)(param_1 + 0x80) + -1;
  }
  return;
}

/* JP: 0x0043f3e0  CmdExplain::DestroyImage()   [DestroyImage__10CmdExplainFv]  size=0xac */
void DestroyImage__10CmdExplainFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x520) != 0) {
    ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x520));
    iVar1 = *(int *)(param_1 + 0x520);
    if (iVar1 != 0) {
      __dt__10MenuSpriteFv(iVar1 + 0x128,0xffffffffffffffff);
      __dt__11SendOnLocalFv(iVar1 + 0xf8,0xffffffffffffffff);
      __dt__11MenuTextureFv(iVar1 + 0xb8,0xffffffffffffffff);
      __dt__10MenuWindowFv(iVar1,0xffffffffffffffff);
      __dl__FPv(iVar1);
    }
    *(undefined4 *)(param_1 + 0x520) = 0;
  }
  return;
}

/* JP: 0x0043f490  CmdExplain::Exec(unsigned short)   [Exec__10CmdExplainFUs]  size=0x7f4 */
undefined4 Exec__10CmdExplainFUs(int param_1,ushort param_2)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  long lVar4;
  ulong uVar5;
  short sStack_24;
  short sStack_22;
  int iStack_20;
  ushort uStack_10;
  
  cVar1 = *(char *)(param_1 + 0x20);
  iStack_20 = param_1;
  uStack_10 = param_2;
  if (cVar1 == '\x02') {
    cVar1 = *(char *)(param_1 + 0x21);
    if (cVar1 == '\x02') {
      *(undefined1 *)(param_1 + 0x25c) = 1;
      *(undefined1 *)(param_1 + 0x20) = 0;
      *(undefined1 *)(param_1 + 0x21) = 0;
      return 4;
    }
    if (cVar1 == '\x01') {
      if ((*(char *)(param_1 + 0x114) == '\x01') || (*(char *)(param_1 + 0x114) == '\0')) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
      if ((bVar3) &&
         ((*(int *)(param_1 + 0x520) == 0 ||
          (-1 < (long)((ulong)*(byte *)(*(int *)(param_1 + 0x520) + 0xf2) << 0x3d))))) {
        ReleaseOT__7MenuObjFv(param_1 + 0x6c);
        if (*(int *)(iStack_20 + 0x520) != 0) {
          ReleaseOT__7MenuObjFv(*(undefined4 *)(iStack_20 + 0x520));
        }
        *(char *)(iStack_20 + 0x21) = *(char *)(iStack_20 + 0x21) + '\x01';
      }
    }
    else if (cVar1 == '\0') {
      Close__10MenuWindowFUci(param_1 + 0x6c,((ulong)*(byte *)(param_1 + 0x11c) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(param_1 + 0xa0) + 0x14));
      if (*(int *)(iStack_20 + 0x520) != 0) {
        iVar2 = *(int *)(iStack_20 + 0x520);
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
      }
      *(char *)(iStack_20 + 0x21) = *(char *)(iStack_20 + 0x21) + '\x01';
      return 3;
    }
  }
  else if (cVar1 == '\x01') {
    cVar1 = *(char *)(param_1 + 0x21);
    if (cVar1 == '\x03') {
      Start__11MenuMessageFv(param_1 + 0x23c);
      *(undefined1 *)(iStack_20 + 0x20) = 3;
      *(undefined1 *)(iStack_20 + 0x21) = 0;
      return 2;
    }
    if (cVar1 == '\x01') {
LAB_0043fa10:
      Open__10MenuWindowFUci(iStack_20 + 0x6c,*(byte *)(iStack_20 + 0x11c) & 7,
                      *(undefined4 *)(*(int *)(iStack_20 + 0xa0) + 0x10));
      *(undefined1 *)(iStack_20 + 0x21) = 2;
      return 1;
    }
    if (cVar1 == '\0') {
      if ((*(byte *)(*(int *)(param_1 + 0x520) + 0xf2) & 1) != 0) {
        Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(*(int *)(param_1 + 0x520) + 0xf8,*(int *)(param_1 + 0x520) + 0xd0,
                        *(undefined4 *)(*(int *)(param_1 + 0x520) + 0xcc),1,0xffffffffffffffff);
        iVar2 = *(int *)(iStack_20 + 0x520);
        Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
        goto LAB_0043fa10;
      }
    }
    else if (cVar1 == '\x02') {
      if ((*(char *)(param_1 + 0x114) == '\x01') || (*(char *)(param_1 + 0x114) == '\0')) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
      if (bVar3) {
        *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
      }
    }
  }
  else if (cVar1 == '\x03') {
    if ((param_2 & 0x2000) == 0) {
      if ((param_2 & (*(ushort *)(param_1 + 0x526) | 0x4000)) == 0) {
        if ((long)((ulong)*(byte *)(param_1 + 0x525) << 0x3e) < 0) {
          if ((*(byte *)(param_1 + 0x524) & 0xf) == 3) {
            if ((param_2 & 0x410) == 0) {
              if ((param_2 & 0x840) != 0) {
                *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf | 0x20;
              }
            }
            else {
              *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf | 0x10;
            }
          }
          else if ((param_2 & 0x480) == 0) {
            if ((param_2 & 0x820) != 0) {
              *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf | 0x80;
            }
          }
          else {
            *(byte *)(param_1 + 0x524) = *(byte *)(param_1 + 0x524) & 0xf | 0x40;
          }
          if (*(byte *)(param_1 + 0x524) >> 4 != 0) {
            *(undefined1 *)(param_1 + 0x20) = 2;
            PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),6,0,0);
            return 5;
          }
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x20) = 2;
        *(byte *)(param_1 + 0x525) = *(byte *)(param_1 + 0x525) & 0xfb | 4;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
      }
    }
    else {
      Finish__11MenuMessageFv(param_1 + 0x23c);
    }
    if (*(ushort *)(iStack_20 + 0x2b2) <= *(ushort *)(iStack_20 + 700)) {
      if ((*(byte *)(iStack_20 + 0x132) & 1) == 0) {
        lVar4 = SendPage__10CmdExplainFv(iStack_20);
        if (lVar4 != 0) {
          GetLastPosition__11MenuMessageFPsPs(iStack_20 + 0x23c,&sStack_22,&sStack_24);
          (**(code **)(*(int *)(iStack_20 + 0x17c) + 0x24))
                    ((float)(sStack_22 + 2),(float)(int)sStack_24);
          *(undefined2 *)(iStack_20 + 0x13e) = 10;
          uVar5 = (ulong)*(byte *)(iStack_20 + 0x132) & 0xfffffffffffffffd | 2;
          *(char *)(iStack_20 + 0x132) = (char)uVar5;
          *(byte *)(iStack_20 + 0x132) =
               *(byte *)(iStack_20 + 0x132) & 0xfe | (byte)((uVar5 << 0x3e) >> 0x3f);
        }
      }
      else if ((char)*(undefined2 *)(iStack_20 + 0x13e) == '\r') {
        SetExplanation__10CmdExplainFPc
                  (iStack_20,
                   *(undefined4 *)(*(int *)(iStack_20 + 0x68) + *(char *)(iStack_20 + 0x528) * 4));
        Start__11MenuMessageFv(iStack_20 + 0x23c);
      }
    }
  }
  return 0;
}

/* JP: 0x0043fc90  CmdExplain::Open()   [Open__10CmdExplainFv]  size=0x3cc */
void Open__10CmdExplainFv(int param_1)

{
  undefined1 auStack_50 [64];
  int iStack_10;
  
  iStack_10 = param_1;
  ClearImage__8FontDrawFv(param_1 + 0x2d4);
  *(byte *)(iStack_10 + 0x326) = *(byte *)(iStack_10 + 0x326) & 0xfe;
  *(byte *)(iStack_10 + 0x3a6) = *(byte *)(iStack_10 + 0x3a6) & 0xfe;
  *(undefined1 *)(iStack_10 + 0x21) = 1;
  if (*(int *)(iStack_10 + 0x60) != 0) {
    SetMessage__8MenuTextFPcUiUcUc(iStack_10 + 0x314,*(undefined4 *)(iStack_10 + 0x60),
                    *(byte *)(iStack_10 + 0x36c) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x2d4,iStack_10 + 0x314,
                    ((ulong)*(byte *)(iStack_10 + 0x36c) & 0xf) >> 3,0);
    *(byte *)(iStack_10 + 0x326) = *(byte *)(iStack_10 + 0x326) & 0xfe | 1;
    if (((long)((ulong)*(byte *)(iStack_10 + 0x525) << 0x3b) < 0) &&
       (*(int *)(iStack_10 + 0xb0) != 0)) {
      SetArea__10ScrollMarkFUcffff(*(undefined4 *)(iStack_10 + 0x338),*(undefined4 *)(iStack_10 + 0x33c),
                      *(undefined4 *)(iStack_10 + 0x340),*(undefined4 *)(iStack_10 + 0x344),
                      *(int *)(iStack_10 + 0xb0),*(byte *)(*(int *)(iStack_10 + 0xb0) + 0x83) & 0xf)
      ;
    }
  }
  if (*(int *)(iStack_10 + 100) != 0) {
    SetMessage__8MenuTextFPcUiUcUc(iStack_10 + 0x394,*(undefined4 *)(iStack_10 + 100),
                    *(byte *)(iStack_10 + 0x3ec) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x2d4,iStack_10 + 0x394,
                    ((ulong)*(byte *)(iStack_10 + 0x3ec) & 0xf) >> 3,0);
    *(byte *)(iStack_10 + 0x3a6) = *(byte *)(iStack_10 + 0x3a6) & 0xfe | 1;
  }
  Reset__10CmdExplainFv(iStack_10);
  *(undefined1 *)(iStack_10 + 0x25c) = 1;
  if (*(int *)(iStack_10 + 0x51c) != 0) {
    SetIcon__10MenuCommonFcP10MenuSprite(*(undefined1 *)(iStack_10 + 0x5e),*(int *)(iStack_10 + 0x51c) + 0x30);
  }
  if ((*(int *)(iStack_10 + 0x520) != 0) &&
     (*(byte *)(*(int *)(iStack_10 + 0x520) + 0x13a) =
           *(byte *)(*(int *)(iStack_10 + 0x520) + 0x13a) & 0xfe,
     (long)((ulong)*(byte *)(iStack_10 + 0x525) << 0x3c) < 0)) {
    sprintf(auStack_50,*(undefined4 *)(*(int *)(iStack_10 + 0x520) + 0xb4),
                    *(undefined2 *)(iStack_10 + 0x5c));
    OrderFile__11MenuTextureFPCc6GS_PSMUii(*(int *)(iStack_10 + 0x520) + 0xb8,auStack_50,0x30,0,0);
    *(byte *)(*(int *)(iStack_10 + 0x520) + 0x13a) =
         *(byte *)(*(int *)(iStack_10 + 0x520) + 0x13a) & 0xfe | 1;
    *(undefined1 *)(iStack_10 + 0x21) = 0;
  }
  *(undefined1 *)(iStack_10 + 0x20) = 1;
  *(byte *)(iStack_10 + 0x524) = *(byte *)(iStack_10 + 0x524) & 0xf;
  if ((-1 < (long)((ulong)*(byte *)(iStack_10 + 0x7e) << 0x3d)) &&
     (AddOT__7MenuObjFv(iStack_10 + 0x6c), *(int *)(iStack_10 + 0x520) != 0)) {
    AddOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0x520));
  }
  return;
}

/* JP: 0x00440060  CmdExplain::Close()   [Close__10CmdExplainFv]  size=0x44 */
void Close__10CmdExplainFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x7e) << 0x3d) < 0) {
    *(undefined1 *)(param_1 + 0x20) = 2;
    *(undefined1 *)(param_1 + 0x21) = 0;
  }
  return;
}

/* JP: 0x004400b0  CmdExplain::Reset()   [Reset__10CmdExplainFv]  size=0xc8 */
void Reset__10CmdExplainFv(int param_1)

{
  long lVar1;
  
  *(undefined2 *)(param_1 + 0x13e) = 1;
  *(byte *)(param_1 + 0x132) = *(byte *)(param_1 + 0x132) & 0xfd;
  *(byte *)(param_1 + 0x132) = *(byte *)(param_1 + 0x132) & 0xfe;
  *(undefined1 *)(param_1 + 0x528) = 4;
  lVar1 = SendPage__10CmdExplainFv(param_1);
  if (lVar1 == 0) {
    *(undefined1 *)(param_1 + 0x528) = 0;
  }
  SetExplanation__10CmdExplainFPc
            (param_1,*(undefined4 *)(*(int *)(param_1 + 0x68) + *(char *)(param_1 + 0x528) * 4));
  return;
}

/* JP: 0x00440180  CmdExplain::SendPage()   [SendPage__10CmdExplainFv]  size=0xb4 */
undefined4 SendPage__10CmdExplainFv(int param_1)

{
  if (-1 < *(char *)(param_1 + 0x528)) {
    *(char *)(param_1 + 0x528) = *(char *)(param_1 + 0x528) + -1;
    while (-1 < *(char *)(param_1 + 0x528)) {
      if (((uint)*(byte *)(param_1 + 0x5f) & 1 << ((int)*(char *)(param_1 + 0x528) & 0x1fU)) != 0) {
        return 1;
      }
      *(char *)(param_1 + 0x528) = *(char *)(param_1 + 0x528) + -1;
    }
  }
  return 0;
}

/* JP: 0x00440240  CmdExplain::SetExplanation(char*)   [SetExplanation__10CmdExplainFPc]  size=0xac */
void SetExplanation__10CmdExplainFPc(int param_1,undefined4 param_2)

{
  ClearImage__8FontDrawFv(param_1 + 0x1fc);
  ClearMessage__11MenuMessageFv(param_1 + 0x23c);
  *(undefined2 *)(param_1 + 0x13e) = 1;
  *(byte *)(param_1 + 0x132) = *(byte *)(param_1 + 0x132) & 0xfd;
  *(byte *)(param_1 + 0x132) = *(byte *)(param_1 + 0x132) & 0xfe;
  Order__8FontDrawFP11MenuMessagePc(param_1 + 0x1fc,param_1 + 0x23c,param_2);
  return;
}
