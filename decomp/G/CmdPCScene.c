/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPCScene   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPCScene.md).
 */

/* JP: 0x0048b540  CmdPCScene::CmdPCScene()   [__ct__10CmdPCSceneFv]  size=0x44 */
int __ct__10CmdPCSceneFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdPCScene;
  *(undefined4 *)(param_1 + 0x78) = 0;
  return param_1;
}

/* JP: 0x0048b590  CmdPCScene::~CmdPCScene()   [__dt__10CmdPCSceneFv]  size=0x9c */
int __dt__10CmdPCSceneFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdPCScene;
    if (*(int *)(param_1 + 0x78) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
    }
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048b630  CmdPCScene::Update(short)   [Update__10CmdPCSceneFs]  size=0x10 */
void Update__10CmdPCSceneFs(void)

{
  return;
}

/* JP: 0x0048b640  CmdPCScene::CreatePCInfo(unsigned char*)   [CreatePCInfo__10CmdPCSceneFPUc]  size=0x198 */
void CreatePCInfo__10CmdPCSceneFPUc(int param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x18) = iVar2 + 0x3a0;
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x5c) = iVar2 + 0xb8;
  *(int *)(param_1 + 0x60) = iVar2 + 0x780;
  *(int *)(param_1 + 100) = iVar2 + 0x4e0;
  *(int *)(param_1 + 0x68) = iVar2 + 0xa60;
  *(int *)(param_1 + 0x6c) = iVar2 + 0x10f0;
  sVar1 = *(short *)(iVar2 + 0x44);
  *(undefined4 *)(param_1 + 0x74) = param_2;
  *(short *)(*(int *)(param_1 + 0x18) + 0x16) = sVar1;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(*(int *)(param_1 + 0x5c) + sVar1 * 4 + 0x10);
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,0,0);
  *(byte *)(*(int *)(param_1 + 0x78) + 0x6a) = *(byte *)(*(int *)(param_1 + 0x78) + 0x6a) & 0xfe;
  return;
}

/* JP: 0x0048b7e0  CmdPCScene::UpdatePCInfo(short, CmdPCStatus*)   [UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus]  size=0x12c */
void UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(int param_1,short param_2,int param_3)

{
  int iVar1;
  int iVar2;
  long lVar3;
  int iStack_10;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iStack_10 = param_3;
  if (param_3 == 0) {
    iStack_10 = iVar1 + 8;
  }
  iVar2 = *(int *)(param_1 + 0x78);
  if (iVar2 == 0) {
    lVar3 = __nw__FUi(0xaa4);
    iVar2 = 0;
    if (lVar3 != 0) {
      iVar2 = __ct__9CmdPCInfoFv(lVar3);
    }
    *(int *)(param_1 + 0x78) = iVar2;
    *(undefined4 *)(iVar2 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    Initialize__9MenuSceneFPUcP9BufMemory(iVar2,*(undefined4 *)(param_1 + 0x74),0);
  }
  UpdateScene__9CmdPCInfoFP5CmdPCP11CmdPCStatus(iVar2,iVar1,iStack_10);
  *(byte *)(iVar2 + 0x6a) = *(byte *)(iVar2 + 0x6a) & 0xfe | 1;
  if (param_2 != 0) {
    Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
  }
  return;
}

/* JP: 0x0048b910  CmdPCScene::ChengePC()   [ChengePC__10CmdPCSceneFv]  size=0x2bc */
undefined4 ChengePC__10CmdPCSceneFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  short sVar6;
  
  if (((*(byte *)(param_1 + 0x23) & 1) == 0) || (*(byte *)(param_1 + 0x23) >> 6 == 0)) {
    uVar4 = 0;
  }
  else {
    uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
    iVar2 = *(int *)(param_1 + 0x5c);
    iVar3 = *(int *)(param_1 + 0x18);
    sVar5 = *(short *)(*(int *)(param_1 + 0x18) + 0x16);
    if ((uVar1 & 0x480) == 0) {
      if ((uVar1 & 0x820) == 0) {
        return 0;
      }
      sVar6 = 1;
    }
    else {
      sVar6 = -1;
    }
    do {
      sVar5 = sVar5 + sVar6;
      if (sVar5 < 0) {
        sVar5 = *(short *)(iVar2 + 0xe) + -1;
      }
      else if (*(short *)(iVar2 + 0xe) <= sVar5) {
        sVar5 = 0;
      }
      if (sVar5 == *(short *)(iVar3 + 0x16)) {
        return 0;
      }
    } while (*(char *)(*(int *)(*(int *)(iVar2 + sVar5 * 4 + 0x10) + 0x34) +
                      (int)*(short *)(iVar3 + 0x32)) == -1);
    *(short *)(iVar3 + 0x16) = sVar5;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar2 + sVar5 * 4 + 0x10);
    (**(code **)(*(int *)(param_1 + 8) + 0x28))(param_1,1);
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),6,0,0);
    uVar4 = 1;
  }
  return uVar4;
}

/* JP: 0x0048bbd0  CmdPCScene::SetChengePCMode(unsigned char)   [SetChengePCMode__10CmdPCSceneFUc]  size=0xac */
void SetChengePCMode__10CmdPCSceneFUc(int param_1,byte param_2)

{
  int iVar1;
  undefined1 uStack_10;
  
  uStack_10 = param_2;
  if ((*(byte *)(param_1 + 0x23) & 1) == 0) {
    uStack_10 = 0;
  }
  iVar1 = *(int *)(param_1 + 0x78);
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x9c) != 0)) {
    *(byte *)(*(int *)(iVar1 + 0x9c) + 0x12) =
         *(byte *)(*(int *)(iVar1 + 0x9c) + 0x12) & 0xfe | uStack_10 & 1;
  }
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0x3f | uStack_10 << 6;
  return;
}

/* JP: 0x0048bc80  CmdPCScene::GetLayerCount(short)   [GetLayerCount__10CmdPCSceneFs]  size=0xf0 */
short GetLayerCount__10CmdPCSceneFs(int param_1,short param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  uint uVar4;
  
  sVar2 = 0;
  uVar3 = *(int *)(param_1 + 0x5c) + 0x30;
  sVar1 = *(short *)(*(int *)(param_1 + 0x5c) + 0xe);
  uVar4 = uVar3 + (sVar1 * 0x12 + (int)sVar1) * 4;
  for (; uVar3 < uVar4; uVar3 = uVar3 + 0x4c) {
    if (*(char *)(*(int *)(uVar3 + 0x34) + (int)param_2) != -1) {
      sVar2 = sVar2 + 1;
    }
  }
  return sVar2;
}
