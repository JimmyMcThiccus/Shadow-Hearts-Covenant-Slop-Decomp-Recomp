/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTitleLog   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTitleLog.md).
 */

/* JP: 0x00442470  CmdTitleLog::CmdTitleLog()   [__ct__11CmdTitleLogFv]  size=0xb4 */
int __ct__11CmdTitleLogFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CmdTitleLog;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __construct_array(param_1 + 0x110,0x2676b0,0x2677a0,0x40,2);
  __ct__11SendOnLocalFv(param_1 + 400);
  __ct__10MenuSpriteFv(param_1 + 0x1c0);
  __ct__8FontDrawFv(param_1 + 0x220);
  __ct__8MenuTextFv(param_1 + 0x260);
  return param_1;
}

/* JP: 0x00442530  CmdTitleLog::~CmdTitleLog()   [__dt__11CmdTitleLogFv]  size=0xf4 */
int __dt__11CmdTitleLogFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CmdTitleLog;
    __dt__8MenuTextFv(param_1 + 0x260,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x220,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x1c0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 400,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x110,0x2677a0,0x40,2);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00442630  CmdTitleLog::GetReady()   [GetReady__11CmdTitleLogFv]  size=0x110 */
undefined4 GetReady__11CmdTitleLogFv(int param_1)

{
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x1c0);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x220);
  SetData__9MenuSceneFUsP8MenuText(param_1,0,param_1 + 0x260);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  *(int *)(param_1 + 0x21c) = param_1 + 400;
  *(byte *)(param_1 + 0x1d2) = *(byte *)(param_1 + 0x1d2) & 0xdf;
  *(undefined2 *)(param_1 + 0x1a6) = 0;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x1c0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x260);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x220);
  AddOT__7MenuObjFv(param_1 + 0x58);
  return 1;
}

/* JP: 0x00442740  CmdTitleLog::Release()   [Release__11CmdTitleLogFv]  size=0xb8 */
void Release__11CmdTitleLogFv(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0xc),1);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  Release__11MenuTextureFv(param_1 + 0x110);
  Release__11MenuTextureFv(param_1 + 0x150);
  Release__7MenuObjFv(param_1 + 400);
  Release__7MenuObjFv(param_1 + 0x1c0);
  Release__7MenuObjFv(param_1 + 0x220);
  Release__7MenuObjFv(param_1 + 0x260);
  Release__7MenuObjFv(param_1 + 0x58);
  return;
}

/* JP: 0x00442800  CmdTitleLog::SetTitle(unsigned char*, int)   [SetTitle__11CmdTitleLogFPUci]  size=0x32c */
/* WARNING: Removing unreachable block (ram,0x00442994) */
/* WARNING: Removing unreachable block (ram,0x004429cc) */

undefined4 SetTitle__11CmdTitleLogFPUci(int param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  
  *(ushort *)(param_1 + 0x1a6) = *(ushort *)(param_1 + 0x1a6) ^ 1;
  iVar1 = param_1 + *(short *)(param_1 + 0x1a6) * 0x40;
  Create__11MenuTextureFPUc6GS_PSMUii(iVar1 + 0x110,param_2,0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 400,iVar1 + 0x128,*(undefined4 *)(iVar1 + 0x124),1,0xffffffffffffffff);
  ClearImage__8FontDrawFv(param_1 + 0x220);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x260,
                  *(undefined4 *)((param_3 & 0xffff) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                  *(byte *)(param_1 + 0x2b8) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x220,param_1 + 0x260,((ulong)*(byte *)(param_1 + 0x2b8) & 0xf) >> 3,0);
  (**(code **)(*(int *)(param_1 + 0x1c8) + 0x28))
            ((float)**(ushort **)(iVar1 + 0x120),(float)*(ushort *)(*(int *)(iVar1 + 0x120) + 2));
  SetUV__10MenuSpriteFUsUsUsUs(param_1 + 0x1c0,0,0,**(short **)(iVar1 + 0x120) + -1,
                  *(short *)(*(int *)(iVar1 + 0x120) + 2) + -1);
  (**(code **)(*(int *)(param_1 + 0x268) + 0x24))
            (*(float *)(param_1 + 0x1e4) + *(float *)(param_1 + 0x1ec) + 2.0,
             *(undefined4 *)(param_1 + 0x288));
  SetSize__10MenuWindowFff(*(float *)(param_1 + 0x284) + *(float *)(param_1 + 0x28c),
                  *(undefined4 *)(param_1 + 0x1f0),param_1 + 0x58);
  *(undefined2 *)(param_1 + 0x6e) = 0x1532;
  return 1;
}

/* JP: 0x00442b30  CmdTitleLog::Open()   [Open__11CmdTitleLogFv]  size=0x98 */
void Open__11CmdTitleLogFv(int param_1)

{
  SetPosition__10MenuWindowFff((float)(int)*(short *)(*(int *)(param_1 + 0x34) + 0x14),
                  (float)(int)*(short *)(*(int *)(param_1 + 0x34) + 0x16),param_1 + 0x58);
  Open__10MenuWindowFUci(param_1 + 0x58,*(byte *)(param_1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x10));
  return;
}
