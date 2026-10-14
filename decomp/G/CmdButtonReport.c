/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdButtonReport   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdButtonReport.md).
 */

/* JP: 0x0043de70  CmdButtonReport::CmdButtonReport()   [__ct__15CmdButtonReportFv]  size=0x94 */
int __ct__15CmdButtonReportFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdButtonReport;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__11SendOnLocalFv(param_1 + 0x10c);
  __ct__8FontDrawFv(param_1 + 0x13c);
  __construct_array(param_1 + 0x17c,0x43dfa0,0x43df10,0x140,4);
  return param_1;
}

/* JP: 0x0043dff0  CmdButtonReport::~CmdButtonReport()   [__dt__15CmdButtonReportFv]  size=0xcc */
int __dt__15CmdButtonReportFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdButtonReport;
    __destroy_arr(param_1 + 0x17c,0x43df10,0x140,4);
    __dt__8FontDrawFv(param_1 + 0x13c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x10c,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0043e0c0  CmdButtonReport::GetReady()   [GetReady__15CmdButtonReportFv]  size=0x2b0 */
undefined4 GetReady__15CmdButtonReportFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uStack_14;
  
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x10c,0x421670,uRam0042166c,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x120) = *(short *)(*(int *)(param_1 + 0x3c) + 0x12) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x10c);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x13c);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x13c);
  uStack_14 = 0.0;
  for (iVar4 = 3; -1 < iVar4; iVar4 = iVar4 + -1) {
    *(undefined4 *)(param_1 + iVar4 * 4 + 0x67c) = 0;
    iVar1 = param_1 + iVar4 * 0x140;
    iVar2 = param_1 + iVar4 * 0x140;
    iVar3 = param_1 + iVar4 * 0x140;
    SetData__9MenuSceneFUsP10MenuSprite(param_1,0,iVar1 + 0x17c);
    SetData__9MenuSceneFUsP10MenuSprite(param_1,1,iVar2 + 0x1dc);
    SetData__9MenuSceneFUsP8MenuText(param_1,0,iVar3 + 0x23c);
    (**(code **)(*(int *)(iVar1 + 0x184) + 0x24))(*(undefined4 *)(iVar1 + 0x1a0),uStack_14);
    (**(code **)(*(int *)(iVar2 + 0x1e4) + 0x24))(*(undefined4 *)(iVar2 + 0x200),uStack_14);
    (**(code **)(*(int *)(iVar3 + 0x244) + 0x24))(*(undefined4 *)(iVar3 + 0x260),uStack_14);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar1 + 0x17c);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar2 + 0x1dc);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar3 + 0x23c);
    uStack_14 = uStack_14 + *(float *)(iVar1 + 0x1ac);
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  AddOT__7MenuObjFv(param_1 + 0x58);
  return 1;
}

/* JP: 0x0043e370  CmdButtonReport::Release()   [Release__15CmdButtonReportFv]  size=0xb4 */
void Release__15CmdButtonReportFv(int param_1)

{
  uint uVar1;
  
  Release__9MenuSceneFv(param_1);
  Release__7MenuObjFv(param_1 + 0x10c);
  Release__7MenuObjFv(param_1 + 0x13c);
  Release__7MenuObjFv(param_1 + 0x58);
  for (uVar1 = param_1 + 0x17c; uVar1 < param_1 + 0x67cU; uVar1 = uVar1 + 0x140) {
    Release__7MenuObjFv(uVar1);
    Release__7MenuObjFv(uVar1 + 0x60);
    Release__7MenuObjFv(uVar1 + 0xc0);
  }
  return;
}

/* JP: 0x0043e430  CmdButtonReport::ClearReport()   [ClearReport__15CmdButtonReportFv]  size=0x170 */
void ClearReport__15CmdButtonReportFv(int param_1)

{
  uint uVar1;
  float *pfVar2;
  
  ClearImage__8FontDrawFv(param_1 + 0x13c);
  pfVar2 = (float *)(param_1 + 0x67c);
  for (uVar1 = param_1 + 0x17c; uVar1 < param_1 + 0x67cU; uVar1 = uVar1 + 0x140) {
    *(byte *)(uVar1 + 0x12) = *(byte *)(uVar1 + 0x12) & 0xfe;
    *(byte *)(uVar1 + 0x72) = *(byte *)(uVar1 + 0x72) & 0xfe;
    *(byte *)(uVar1 + 0xd2) = *(byte *)(uVar1 + 0xd2) & 0xfe;
    (**(code **)(*(int *)(uVar1 + 8) + 0x24))
              (*(float *)(uVar1 + 0x24) - *pfVar2,*(undefined4 *)(uVar1 + 0x28));
    (**(code **)(*(int *)(uVar1 + 0x68) + 0x24))
              (*(float *)(uVar1 + 0x84) - *pfVar2,*(undefined4 *)(uVar1 + 0x88));
    (**(code **)(*(int *)(uVar1 + 200) + 0x24))
              (*(float *)(uVar1 + 0xe4) - *pfVar2,*(undefined4 *)(uVar1 + 0xe8));
    *pfVar2 = 0.0;
    pfVar2 = pfVar2 + 1;
  }
  *(undefined1 *)(param_1 + 0x20) = 0;
  return;
}

/* JP: 0x0043e5a0  CmdButtonReport::SetReport(int, int)   [SetReport__15CmdButtonReportFii]  size=0x26c */
void SetReport__15CmdButtonReportFii(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  undefined1 uStack_34;
  char cStack_33;
  
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  iVar2 = param_1 + param_2 * 0x140;
  cStack_33 = -1;
  switch(param_3) {
  case 0:
  case 1:
  case 2:
    uStack_34 = (undefined1)*(undefined2 *)(iVar1 + 0x26e);
    break;
  case 3:
    uStack_34 = (undefined1)*(undefined2 *)(iVar1 + 0x270);
    break;
  case 4:
  case 5:
  case 0xf:
  case 0x11:
    uStack_34 = (undefined1)*(undefined2 *)(iVar1 + 0x26c);
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0x10:
    uStack_34 = (undefined1)*(undefined2 *)(iVar1 + 0x272);
    break;
  case 0xb:
    uStack_34 = 3;
    break;
  case 0xc:
    uStack_34 = 2;
    break;
  case 0xd:
    uStack_34 = 9;
    cStack_33 = '\b';
    break;
  case 0xe:
    uStack_34 = 5;
    cStack_33 = '\a';
    break;
  default:
    goto switchD_0043e620_default;
  }
  SetIcon__10MenuCommonFcP10MenuSprite(uStack_34,iVar2 + 0x17c);
  *(byte *)(iVar2 + 0x18e) = *(byte *)(iVar2 + 0x18e) & 0xfe | 1;
  if (-1 < cStack_33) {
    SetIcon__10MenuCommonFcP10MenuSprite(cStack_33,iVar2 + 0x1dc);
    *(byte *)(iVar2 + 0x1ee) = *(byte *)(iVar2 + 0x1ee) & 0xfe | 1;
  }
  SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x23c,
                  *(undefined4 *)((param_3 & 0xffff) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                  *(byte *)(iVar2 + 0x294) & 7,0,0);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x13c,iVar2 + 0x23c,((ulong)*(byte *)(iVar2 + 0x294) & 0xf) >> 3,0);
  *(byte *)(iVar2 + 0x24e) = *(byte *)(iVar2 + 0x24e) & 0xfe | 1;
  *(char *)(param_1 + 0x20) = *(char *)(param_1 + 0x20) + '\x01';
switchD_0043e620_default:
  return;
}

/* JP: 0x0043e810  CmdButtonReport::Open()   [Open__15CmdButtonReportFv]  size=0x98 */
void Open__15CmdButtonReportFv(int param_1)

{
  SetPosition__10MenuWindowFff((float)(int)*(short *)(*(int *)(param_1 + 0x34) + 0x14),
                  (float)(int)*(short *)(*(int *)(param_1 + 0x34) + 0x16),param_1 + 0x58);
  Open__10MenuWindowFUci(param_1 + 0x58,*(byte *)(param_1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x10));
  return;
}

/* JP: 0x0043e8b0  CmdButtonReport::SetOffset(float)   [SetOffset__15CmdButtonReportFf]  size=0x144 */
void SetOffset__15CmdButtonReportFf(float param_1,int param_2)

{
  int iVar1;
  
  if (*(float *)(param_2 + *(char *)(param_2 + 0x20) * 4 + 0x67c) == 0.0) {
    iVar1 = param_2 + *(char *)(param_2 + 0x20) * 0x140;
    (**(code **)(*(int *)(iVar1 + 0x184) + 0x24))
              (param_1 + *(float *)(iVar1 + 0x1a0),*(undefined4 *)(iVar1 + 0x1a4));
    (**(code **)(*(int *)(iVar1 + 0x1e4) + 0x24))
              (param_1 + *(float *)(iVar1 + 0x200),*(undefined4 *)(iVar1 + 0x204));
    (**(code **)(*(int *)(iVar1 + 0x244) + 0x24))
              (param_1 + *(float *)(iVar1 + 0x260),*(undefined4 *)(iVar1 + 0x264));
    *(float *)(param_2 + *(char *)(param_2 + 0x20) * 4 + 0x67c) = param_1;
  }
  return;
}
