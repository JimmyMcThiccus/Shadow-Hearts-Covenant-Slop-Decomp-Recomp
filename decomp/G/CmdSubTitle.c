/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSubTitle   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSubTitle.md).
 */

/* JP: 0x00478050  CmdSubTitle::CmdSubTitle()   [__ct__11CmdSubTitleFv]  size=0x84 */
int __ct__11CmdSubTitleFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CmdSubTitle;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__11MenuTextureFv(param_1 + 0x110);
  __ct__11SendOnLocalFv(param_1 + 0x150);
  __ct__8FontDrawFv(param_1 + 0x180);
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  return param_1;
}

/* JP: 0x004780e0  CmdSubTitle::~CmdSubTitle()   [__dt__11CmdSubTitleFv]  size=0xec */
int __dt__11CmdSubTitleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CmdSubTitle;
    if (*(int *)(param_1 + 0x1c0) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x1c0),0x4781d0);
    }
    __dt__8FontDrawFv(param_1 + 0x180,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00478270  CmdSubTitle::DelayDelete()   [DelayDelete__11CmdSubTitleFv]  size=0x38 */
void DelayDelete__11CmdSubTitleFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x58);
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x004782b0  CmdSubTitle::Create(int)   [Create__11CmdSubTitleFi]  size=0x260 */
void Create__11CmdSubTitleFi(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = __nwa__FUi(param_2 * 0x1f0 + 0x10);
  uVar1 = __construct_new_array(uVar3,0x478510,0x4781d0,0x1f0,param_2);
  *(undefined4 *)(param_1 + 0x1c0) = uVar1;
  uVar4 = *(uint *)(param_1 + 0x1c0);
  uVar2 = uVar4 + param_2 * 0x1f0;
  for (; uVar4 < uVar2; uVar4 = uVar4 + 0x1f0) {
    SetData__9MenuSceneFUsP8MenuText(param_1,0,uVar4 + 0x170);
    AddPlace__9MenuGroupFP9MenuPlace(uVar4,uVar4 + 0x170);
    for (uVar5 = 0; (int)uVar5 < 3; uVar5 = uVar5 + 1) {
      SetData__9MenuSceneFUsP10MenuSprite(param_1,uVar5 & 0xffff,uVar4 + uVar5 * 0x60 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(uVar4,uVar4 + uVar5 * 0x60 + 0x50);
    }
  }
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x110,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x150,param_1 + 0x128,*(undefined4 *)(param_1 + 0x124),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x164) = *(short *)(*(int *)(param_1 + 0x1c0) + 100) + -1;
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x180);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  AddOT__7MenuObjFv(param_1 + 0x58);
  return;
}

/* JP: 0x00478580  CmdSubTitle::Reset()   [Reset__11CmdSubTitleFv]  size=0x6c */
void Reset__11CmdSubTitleFv(int param_1)

{
  ClearPlace__10MenuWindowFv(param_1 + 0x58);
  ClearImage__8FontDrawFv(param_1 + 0x180);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x180);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x150);
  return;
}

/* JP: 0x004785f0  CmdSubTitle::SetTitle(int, int)   [SetTitle__11CmdSubTitleFii]  size=0x24c */
/* WARNING: Removing unreachable block (ram,0x0047870c) */
/* WARNING: Removing unreachable block (ram,0x00478748) */

void SetTitle__11CmdSubTitleFii(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(param_1 + 0x1c0) + param_2 * 0x1f0;
  iVar1 = (param_3 & 0xffff) * 8 + *(int *)(param_1 + 0x24);
  iVar5 = (uint)(ushort)(*(short *)(iVar1 + 0x16) * 3) * 0x20 + *(int *)(param_1 + 0x3c) + 0x10;
  iVar3 = iVar2 + 0x50;
  for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
    (**(code **)(*(int *)(iVar3 + 8) + 0x24))
              ((float)(int)*(short *)(iVar5 + 4),(float)(int)*(short *)(iVar5 + 6));
    (**(code **)(*(int *)(iVar3 + 8) + 0x28))
              ((float)*(ushort *)(iVar5 + 8),(float)*(ushort *)(iVar5 + 10));
    iVar5 = iVar5 + 0x20;
    iVar3 = iVar3 + 0x60;
  }
  SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x170,*(undefined4 *)(iVar1 + 0x10),*(byte *)(iVar2 + 0x1c8) & 7,0,0);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x180,iVar2 + 0x170,((ulong)*(byte *)(iVar2 + 0x1c8) & 0xf) >> 3,0);
  SetData__9MenuSceneFUsP9MenuGroup(param_1,*(undefined2 *)(iVar1 + 0x14),iVar2);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar2);
  return;
}
