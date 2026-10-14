/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusion   functions: 31
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusion.md).
 */

/* JP: 0x0046ee40  CmdFusion::CmdFusion()   [__ct__9CmdFusionFv]  size=0x8c */
int __ct__9CmdFusionFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdFusion;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  return param_1;
}

/* JP: 0x0046eed0  CmdFusion::~CmdFusion()   [__dt__9CmdFusionFv]  size=0x74 */
int __dt__9CmdFusionFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdFusion;
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0046ef50  CmdFusion::GetReady()   [GetReady__9CmdFusionFv]  size=0x2fc */
undefined4 GetReady__9CmdFusionFv(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  
  iVar2 = *(int *)(param_1 + 0x10) + 0x28;
  *(undefined4 *)(param_1 + 0x94) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  uVar1 = GetRegCnt__9RegDatApiFii(0x2c,0xffffffffffffffff);
  *(undefined2 *)(param_1 + 0xa8) = uVar1;
  iVar3 = Find__13MenuDataTableFs(iVar2,0x1a);
  *(undefined2 *)(param_1 + 0xaa) = *(undefined2 *)(iVar3 + 4);
  *(int *)(param_1 + 0xac) = iVar3 + 0x10;
  iVar2 = Find__13MenuDataTableFs(iVar2,0x2f);
  *(int *)(param_1 + 0xb0) = iVar2 + 0x10;
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x68);
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x90);
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0xf);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  lVar5 = __nw__FUi(0x1c8);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__11CmdSubTitleFv(lVar5);
  }
  *(undefined4 *)(param_1 + 0x68) = uVar4;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x68),
                  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 100),0);
  Create__11CmdSubTitleFi(*(undefined4 *)(param_1 + 0x68),1);
  UpdateTitle__9CmdFusionFs(param_1,0x15);
  UpdateList__9CmdFusionFs(param_1,1);
  UpdateFence__9CmdFusionFv(param_1);
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xdf | 0x20;
  return 1;
}

/* JP: 0x0046f250  CmdFusion::Run()   [Run__9CmdFusionFv]  size=0x118 */
undefined4 Run__9CmdFusionFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if ((((long)((ulong)*(byte *)(*(int *)(param_1 + 0x9c) + 0x46) << 0x3e) < 0) &&
      ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x8000) != 0)) &&
     (*(int *)(*(int *)(param_1 + 0x9c) + 0x18) != 0)) {
    SetAction__13MenuModelPackFv(*(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x18));
  }
  lVar2 = __ptmf_test(param_1 + 0x5c);
  if ((lVar2 == 0) || (lVar2 = __ptmf_scall(param_1), lVar2 != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x0046f370  CmdFusion::SafeDelayDelete()   [SafeDelayDelete__9CmdFusionFv]  size=0xb4 */
void SafeDelayDelete__9CmdFusionFv(int param_1)

{
  (**(code **)(*(int *)(*(int *)(param_1 + 0x68) + 8) + 0xc))();
  (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
  if (*(int *)(param_1 + 0x6c) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
  }
  if (*(int *)(param_1 + 0x74) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
  }
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x0046f430  CmdFusion::Close()   [Close__9CmdFusionFv]  size=0xac */
void Close__9CmdFusionFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x78);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x74);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x68);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  return;
}

/* JP: 0x0046f4e0  CmdFusion::Update(short)   [Update__9CmdFusionFs]  size=0x10 */
void Update__9CmdFusionFs(void)

{
  return;
}

/* JP: 0x0046f4f0  CmdFusion::ReadyScene()   [ReadyScene__9CmdFusionFv]  size=0x1d8 */
undefined4 ReadyScene__9CmdFusionFv(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_1 + 0x21) = 0;
  *(undefined2 *)(param_1 + 0xbc) = 0xffff;
  iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x8c);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  lVar4 = __nw__FUi(0x154);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__10CmdSubMenuFv(lVar4);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar3;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x6c),
                  *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 0x58),0);
  CreateScene__10CmdSubMenuFsP9MSDSystem
            (*(undefined4 *)(param_1 + 0x6c),3,*(int *)(param_1 + 0x28) + 0x10);
  uVar5 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x78),0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
  Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
            (*(undefined4 *)(param_1 + 0x78),param_1,uVar5,0,1);
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  *(undefined1 *)(param_1 + 0x21) = 0;
  puVar2 = PTR_Enter__9CmdFusionFv_0050d7b0;
  uVar3 = DAT_0050d7ac;
  *(undefined4 *)(param_1 + 0x5c) = _6382;
  *(undefined4 *)(param_1 + 0x60) = uVar3;
  *(undefined **)(param_1 + 100) = puVar2;
  return 2;
}

/* JP: 0x0046f6d0  CmdFusion::UpdateList(short)   [UpdateList__9CmdFusionFs]  size=0xfc */
void UpdateList__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x78) == 0) {
    lVar3 = __nw__FUi(500);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__13CmdFusionListFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x78) = uVar2;
    CreateScene__13CmdFusionListFP9CmdFusion(*(undefined4 *)(param_1 + 0x78),param_1);
  }
  UpdateScene__13CmdFusionListFP9CmdFusion(*(undefined4 *)(param_1 + 0x78),param_1);
  *(byte *)(*(int *)(param_1 + 0x78) + 0x12) = *(byte *)(*(int *)(param_1 + 0x78) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x78);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x0046f7d0  CmdFusion::UpdateFence()   [UpdateFence__9CmdFusionFv]  size=0x138 */
void UpdateFence__9CmdFusionFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined1 auStack_70 [96];
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_70);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_70,*(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x58) + 0x54) + 0x88),0);
  lVar3 = __nw__FUi(0x178);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__8CmdFenceFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x74) = uVar2;
  CreateFence__8CmdFenceFP9MenuScenePUc
            (*(undefined4 *)(iStack_10 + 0x74),auStack_70,
             *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x58) + 0x54) + 0x1c));
  SetTitle__8CmdFenceFP9MenuScenes(*(undefined4 *)(iStack_10 + 0x74),auStack_70,3);
  iVar1 = *(int *)(iStack_10 + 0x74);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  __dt__9MenuSceneFv(auStack_70,0xffffffffffffffff);
  return;
}

/* JP: 0x0046f910  CmdFusion::UpdateTitle(short)   [UpdateTitle__9CmdFusionFs]  size=0x7c */
void UpdateTitle__9CmdFusionFs(int param_1,undefined2 param_2)

{
  int iVar1;
  
  Reset__11CmdSubTitleFv(*(undefined4 *)(param_1 + 0x68));
  SetTitle__11CmdSubTitleFii(*(undefined4 *)(param_1 + 0x68),0,param_2);
  iVar1 = *(int *)(param_1 + 0x68);
  Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  return;
}

/* JP: 0x0046f990  CmdFusion::UpdateParameter(short)   [UpdateParameter__9CmdFusionFs]  size=0xfc */
void UpdateParameter__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x7c) == 0) {
    lVar3 = __nw__FUi(0x6c4);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdFusionParameterFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x7c) = uVar2;
    CreateScene__18CmdFusionParameterFP9CmdFusion(*(undefined4 *)(param_1 + 0x7c),param_1);
  }
  UpdateScene__18CmdFusionParameterFP9CmdFusion(*(undefined4 *)(param_1 + 0x7c),param_1);
  *(byte *)(*(int *)(param_1 + 0x7c) + 0x12) = *(byte *)(*(int *)(param_1 + 0x7c) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x7c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x0046fa90  CmdFusion::UpdateStatus(short)   [UpdateStatus__9CmdFusionFs]  size=0x10c */
void UpdateStatus__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x80) == 0) {
    lVar3 = __nw__FUi(0x934);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__15CmdFusionStatusFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    CreateScene__15CmdFusionStatusFP9CmdFusion(*(undefined4 *)(param_1 + 0x80),param_1);
  }
  UpdateScene__15CmdFusionStatusFP9CmdFusion(*(undefined4 *)(param_1 + 0x80),param_1);
  *(byte *)(*(int *)(param_1 + 0x80) + 0x12) = *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x80);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    UpdateTitle__9CmdFusionFs(param_1,0x16);
  }
  return;
}

/* JP: 0x0046fba0  CmdFusion::UpdateSkillList(short)   [UpdateSkillList__9CmdFusionFs]  size=0x10c */
void UpdateSkillList__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x84) == 0) {
    lVar3 = __nw__FUi(0xa24);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdFusionSkillListFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x84) = uVar2;
    CreateScene__18CmdFusionSkillListFP9CmdFusion(*(undefined4 *)(param_1 + 0x84),param_1);
  }
  UpdateScene__18CmdFusionSkillListFP9CmdFusion(*(undefined4 *)(param_1 + 0x84),param_1);
  *(byte *)(*(int *)(param_1 + 0x84) + 0x12) = *(byte *)(*(int *)(param_1 + 0x84) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x84);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    UpdateTitle__9CmdFusionFs(param_1,0x17);
  }
  return;
}

/* JP: 0x0046fcb0  CmdFusion::UpdateCharge(short)   [UpdateCharge__9CmdFusionFs]  size=0x10c */
void UpdateCharge__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x88) == 0) {
    lVar3 = __nw__FUi(0x3a8);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__15CmdFusionChargeFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x88) = uVar2;
    CreateScene__15CmdFusionChargeFP9CmdFusion(*(undefined4 *)(param_1 + 0x88),param_1);
  }
  UpdateScene__15CmdFusionChargeFP9CmdFusion(*(undefined4 *)(param_1 + 0x88),param_1);
  *(byte *)(*(int *)(param_1 + 0x88) + 0x12) = *(byte *)(*(int *)(param_1 + 0x88) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x88);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    UpdateTitle__9CmdFusionFs(param_1,0x18);
  }
  return;
}

/* JP: 0x0046fdc0  CmdFusion::UpdateSoulEnergy(short)   [UpdateSoulEnergy__9CmdFusionFs]  size=0x184 */
void UpdateSoulEnergy__9CmdFusionFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x90) == 0) {
    lVar3 = __nw__FUi(0x3f0);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__13CmdSoulEnergyFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x90) = uVar2;
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x90),
                    *(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x7c),0);
    *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x10) = *(undefined4 *)(param_1 + 0x10);
  }
  SetMeter__13CmdSoulEnergyFUi(*(undefined4 *)(param_1 + 0x90),
                  **(undefined2 **)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4));
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x90);
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  }
  return;
}

/* JP: 0x0046ff50  CmdFusion::SetFusionMonster(short)   [SetFusionMonster__9CmdFusionFs]  size=0x4ec */
void SetFusionMonster__9CmdFusionFs(int param_1,short param_2)

{
  undefined2 uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  
  if (param_2 != *(short *)(param_1 + 0xbc)) {
    iVar6 = *(int *)(param_1 + 0xac) + param_2 * 0x54;
    piVar2 = *(int **)(*(int *)(param_1 + 0x58) + 0x70);
    *(short *)(param_1 + 0xbc) = param_2;
    iVar3 = GetRegDat__9RegDatApiFiii(0x2c,param_2,0xffffffffffffffff);
    *(int *)(param_1 + 0xb8) = iVar3;
    uVar4 = GetRegDat__9RegDatApiFiii(4,param_2,0xffffffffffffffff);
    *(undefined4 *)(param_1 + 0xb4) = uVar4;
    iVar5 = GetRegCnt__9RegDatApiFii(0x2d,param_2);
    *(int *)(param_1 + 0xc0) = iVar5 + -1;
    *(float *)(param_1 + 0xc4) =
         (float)*(uint *)(*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) + param_2 * 4 +
                         0xd50);
    uVar1 = *(undefined2 *)(iVar3 + 2);
    Reset__16MenuModelManegerFv(*(undefined4 *)(param_1 + 0x9c));
    *(undefined2 *)(*(int *)(param_1 + 0x9c) + 0x68) = uVar1;
    uVar4 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x20);
    iVar5 = *(int *)(param_1 + 0x9c);
    *(undefined2 *)(iVar5 + 0x3c) = uVar1;
    *(undefined4 *)(iVar5 + 0x24) = uVar4;
    uVar4 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x28);
    iVar5 = *(int *)(param_1 + 0x9c);
    *(undefined2 *)(iVar5 + 0x3e) = uVar1;
    *(undefined4 *)(iVar5 + 0x28) = uVar4;
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x10);
    iVar5 = *(int *)(param_1 + 0x9c);
    *(undefined2 *)(iVar5 + 0x40) = *(undefined2 *)(iVar6 + 0x50);
    *(undefined4 *)(iVar5 + 0x2c) = uVar4;
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x18);
    iVar5 = *(int *)(param_1 + 0x9c);
    *(short *)(iVar5 + 0x42) = (short)*(char *)(iVar6 + 0x52);
    *(undefined4 *)(iVar5 + 0x30) = uVar4;
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x20);
    iVar5 = *(int *)(param_1 + 0x9c);
    *(short *)(iVar5 + 0x44) = (short)*(char *)(iVar6 + 0x52);
    *(undefined4 *)(iVar5 + 0x34) = uVar4;
    if ((long)((ulong)*(byte *)(iVar3 + 4) << 0x39) < 0) {
      uVar4 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x30);
      iVar5 = *(int *)(param_1 + 0x9c);
      *(undefined2 *)(iVar5 + 0x38) = 0;
      *(undefined4 *)(iVar5 + 0x1c) = uVar4;
    }
    Access__16MenuModelManegerFv(*(undefined4 *)(param_1 + 0x9c));
    iVar5 = *(int *)(*(int *)(param_1 + 0x9c) + 0x18);
    *(byte *)(iVar5 + 0x66) = (byte)(((ulong)*(byte *)(*piVar2 + 0x58) << 0x3a) >> 0x3d);
    *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(param_1 + 0xb0);
    *(int *)(iVar5 + 0x14) = *(int *)(param_1 + 0xb0) + 0x10;
    *(int *)(iVar5 + 0x18) = *(int *)(param_1 + 0xb0) + 0x38;
    SetCamera__7CmdMenuFP13MenuDataModel(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(iVar6 + 8))
    ;
    Create__10CmdElementFUc(*(undefined4 *)(param_1 + 0x98),*(byte *)(iVar3 + 4) & 7);
    if (*(int *)(param_1 + 0x90) == 0) {
      Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x98));
    }
    DisableFontItem__8FontItemFv(*(int *)(*(int *)(param_1 + 0x6c) + 0x14c) + 0x100);
  }
  return;
}

/* JP: 0x00470440  CmdFusion::SetExplanation()   [SetExplanation__9CmdFusionFv]  size=0x160 */
void SetExplanation__9CmdFusionFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(param_1 + 0x70);
  memset(iVar2 + 0x5c,0,0x10);
  uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  puVar4 = (undefined4 *)(*(int *)(param_1 + 0xac) + (uint)uVar1 * 0x54);
  *(ushort *)(iVar2 + 0x5c) = uVar1;
  uVar3 = GetRegDat__9RegDatApiFiii(4,uVar1,0xffffffffffffffff);
  *(undefined4 *)(iVar2 + 0x60) = uVar3;
  *(undefined4 *)(iVar2 + 100) = *puVar4;
  *(undefined4 **)(iVar2 + 0x68) = puVar4 + 1;
  SetExplanation__7CmdNoteFPCce
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
             *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x38));
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x70));
  return;
}

/* JP: 0x004705a0  CmdFusion::SetButtonReport(int)   [SetButtonReport__9CmdFusionFi]  size=0x110 */
void SetButtonReport__9CmdFusionFi(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xa4);
  ClearReport__15CmdButtonReportFv(iVar1);
  if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x9c) + 0x46) << 0x3e) < 0) {
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),0xc);
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),7);
  }
  if (param_2 == 2) {
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),3);
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),2);
  }
  else if (param_2 != 0) {
    SetReport__15CmdButtonReportFii(iVar1,*(undefined1 *)(iVar1 + 0x20),4);
  }
  return;
}

/* JP: 0x004706b0  CmdFusion::GetNextExp(short)   [GetNextExp__9CmdFusionFs]  size=0x138 */
int GetNextExp__9CmdFusionFs(int param_1,short param_2)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  
  sVar2 = *(short *)(param_1 + 0xbc);
  bVar1 = *(byte *)(*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) + (int)sVar2 + 0xd94);
  iVar5 = 0;
  for (sVar4 = 0; sVar4 < (short)(param_2 + (ushort)bVar1); sVar4 = sVar4 + 1) {
    iVar3 = GetRegDat__9RegDatApiFiii(0x2d,sVar2,sVar4);
    iVar5 = iVar5 + (uint)*(ushort *)(iVar3 + 0xe);
  }
  return iVar5;
}

/* JP: 0x004707f0  CmdFusion::IsMaxLevel()   [IsMaxLevel__9CmdFusionFv]  size=0xc4 */
bool IsMaxLevel__9CmdFusionFv(int param_1)

{
  return *(uint *)(param_1 + 0xc0) ==
         (uint)*(byte *)(*(int *)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) +
                         (int)*(short *)(param_1 + 0xbc) + 0xd94);
}

/* JP: 0x004708c0  CmdFusion::Enter()   [Enter__9CmdFusionFv]  size=0x184 */
undefined8 Enter__9CmdFusionFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    UpdateScene__10CmdSubMenuFs(*(undefined4 *)(param_1 + 0x6c),0);
    DisableFontItem__8FontItemFv(*(int *)(*(int *)(param_1 + 0x6c) + 0x14c) + 0x100);
    SetButtonReport__9CmdFusionFi(param_1,1);
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0xa4));
    *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) = *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xef;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x6c) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x6c) + 0x100) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar3 = PTR_SelectList__9CmdFusionFv_0050d7c0;
      uVar2 = DAT_0050d7bc;
      *(undefined4 *)(param_1 + 0x5c) = _6827;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00470a50  CmdFusion::Exit()   [Exit__9CmdFusionFv]  size=0x23c */
undefined4 Exit__9CmdFusionFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    if ((*(char *)(*(int *)(param_1 + 0x6c) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x6c) + 0x100) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x6c) = 0;
      UpdateMenu__10CmdPrivateFs(*(undefined4 *)(param_1 + 0x58),1);
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x8c);
    if ((*(char *)(iVar1 + 0xa8) == '\x01') || (*(char *)(iVar1 + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xef | 0x10;
      Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                (*(undefined4 *)(param_1 + 0x78),param_1,0,
                 *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),1);
      Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x78),0,0);
      return 1;
    }
  }
  return 0;
}

/* JP: 0x00470c90  CmdFusion::SelectList()   [SelectList__9CmdFusionFv]  size=0x610 */
undefined8 SelectList__9CmdFusionFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      if ((uVar1 & 0x1000) == 0) {
        iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar2 != iVar4) {
          Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                    (*(undefined4 *)(param_1 + 0x78),param_1,iVar4,iVar2,1);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),0,0,0);
        }
      }
      else {
        lVar6 = __nw__FUi(0x52c);
        uVar5 = 0;
        if (lVar6 != 0) {
          uVar5 = __ct__10CmdExplainFv(lVar6);
        }
        *(undefined4 *)(param_1 + 0x70) = uVar5;
        Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x70),
                        *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 0x34),0);
        SetInfo__10CmdExplainFP4MenusUcUc
                  (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x10),
                   *(undefined2 *)(*(int *)(param_1 + 0x78) + 0xae),0xc,1);
        *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
        iVar2 = *(int *)(param_1 + 0x78);
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
        iVar2 = *(int *)(param_1 + 0x74);
        Close__10MenuWindowFUci(iVar2,((ulong)*(byte *)(iVar2 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x14));
        iVar2 = *(int *)(param_1 + 0x68);
        Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
        iVar2 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
        Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
        puVar3 = PTR_ShiftExplain__9CmdFusionFv_0050d7f0;
        uVar5 = DAT_0050d7ec;
        *(undefined4 *)(param_1 + 0x5c) = _6905;
        *(undefined4 *)(param_1 + 0x60) = uVar5;
        *(undefined **)(param_1 + 100) = puVar3;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),2,0,0);
      }
    }
    else {
      iVar2 = *(int *)(param_1 + 0x6c);
      Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
      Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x9c),0);
      puVar3 = PTR_Exit__9CmdFusionFv_0050d7e0;
      uVar5 = DAT_0050d7dc;
      *(undefined4 *)(param_1 + 0x5c) = _6899;
      *(undefined4 *)(param_1 + 0x60) = uVar5;
      *(undefined **)(param_1 + 100) = puVar3;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),3,0,0);
    }
  }
  else {
    iVar4 = GetPlace__10MenuWindowFss(*(int *)(param_1 + 0x6c) + 0x58,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar4);
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace(*(undefined4 *)(param_1 + 0x6c),0,iVar4,0);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
               *(undefined4 *)
                ((uint)*(ushort *)(iVar4 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14));
    iVar4 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
    iVar4 = *(int *)(param_1 + 0x74);
    Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
    iVar4 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar4 + 0x58,((ulong)*(byte *)(iVar4 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar4 + 0x8c) + 0x14));
    iVar4 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
    Close__10MenuWindowFUci(iVar4 + 0x58,((ulong)*(byte *)(iVar4 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar4 + 0x8c) + 0x14));
    Select__6CursorFP9MenuPlace(*(int *)(param_1 + 0x78) + 0xf8,iVar2);
    SetButtonReport__9CmdFusionFi(param_1,0);
    puVar3 = PTR_ShiftMenu__9CmdFusionFv_0050d7d0;
    uVar5 = DAT_0050d7cc;
    *(undefined4 *)(param_1 + 0x5c) = _6894;
    *(undefined4 *)(param_1 + 0x60) = uVar5;
    *(undefined **)(param_1 + 100) = puVar3;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),2,0,0);
  }
  return 0;
}

/* JP: 0x004712a0  CmdFusion::SelectMenu()   [SelectMenu__9CmdFusionFv]  size=0xb10 */
undefined8 SelectMenu__9CmdFusionFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined *puVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  long lVar10;
  undefined2 uVar11;
  
  if ((*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\0')) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  if (bVar4) {
    uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
    iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    sVar1 = *(short *)(iVar3 + 0x1e);
    if (((uVar2 & 0x2000) == 0) || (sVar1 == 0)) {
      if ((uVar2 & 0x4000) == 0) {
        iVar7 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar3 == iVar7) {
          if (1 < *(short *)(*(int *)(param_1 + 0x78) + 0xae)) {
            iVar7 = *(int *)(*(int *)(param_1 + 0x78) + 0x1e4);
            iVar8 = (int)sVar1;
            if (sVar1 < 0) {
              iVar8 = iVar8 + 1;
            }
            uVar11 = (undefined2)(iVar8 >> 1);
            if ((uVar2 & 0x480) == 0) {
              if ((uVar2 & 0x820) != 0) {
                MoveCursor__13CmdFusionListFis(*(undefined4 *)(param_1 + 0x78),2,uVar11);
              }
            }
            else {
              MoveCursor__13CmdFusionListFis(*(undefined4 *)(param_1 + 0x78),1,uVar11);
            }
            iVar8 = *(int *)(*(int *)(param_1 + 0x78) + 0x1e4);
            if (iVar7 != iVar8) {
              Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                        (*(undefined4 *)(param_1 + 0x78),param_1,iVar8,iVar7,0);
              Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                        (*(undefined4 *)(param_1 + 0x6c),0,iVar3,0);
              SetExplanation__7CmdNoteFPCce
                        (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                         *(undefined4 *)
                          ((uint)*(ushort *)(iVar3 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14))
              ;
              UpdateParameter__9CmdFusionFs(param_1,1);
              if (sVar1 == 2) {
                UpdateCharge__9CmdFusionFs(param_1,1);
              }
              else if (sVar1 == 1) {
                UpdateSkillList__9CmdFusionFs(param_1,1);
              }
              else if (sVar1 == 0) {
                UpdateStatus__9CmdFusionFs(param_1,1);
              }
              PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),6,0,0);
            }
          }
        }
        else {
          sVar1 = *(short *)(iVar3 + 0x1e);
          if (sVar1 == 2) {
            (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0xc))();
            *(undefined4 *)(param_1 + 0x88) = 0;
            (**(code **)(*(int *)(*(int *)(param_1 + 0x90) + 8) + 0xc))();
            *(undefined4 *)(param_1 + 0x90) = 0;
            Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x98));
          }
          else if (sVar1 == 1) {
            (**(code **)(*(int *)(*(int *)(param_1 + 0x84) + 8) + 0xc))();
            *(undefined4 *)(param_1 + 0x84) = 0;
          }
          else if (sVar1 == 0) {
            (**(code **)(*(int *)(*(int *)(param_1 + 0x80) + 8) + 0xc))();
            *(undefined4 *)(param_1 + 0x80) = 0;
          }
          sVar1 = *(short *)(iVar7 + 0x1e);
          if (sVar1 == 2) {
            UpdateCharge__9CmdFusionFs(param_1,1);
            UpdateSoulEnergy__9CmdFusionFs(param_1,1);
            *(byte *)(*(int *)(param_1 + 0x98) + 0x6a) =
                 *(byte *)(*(int *)(param_1 + 0x98) + 0x6a) & 0xfe;
          }
          else if (sVar1 == 1) {
            UpdateSkillList__9CmdFusionFs(param_1,1);
          }
          else if (sVar1 == 0) {
            UpdateStatus__9CmdFusionFs(param_1,1);
          }
          Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                    (*(undefined4 *)(param_1 + 0x6c),0,iVar7,iVar3);
          SetExplanation__7CmdNoteFPCce
                    (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                     *(undefined4 *)
                      ((uint)*(ushort *)(iVar7 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14));
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),0,0,0);
        }
      }
      else {
        iVar7 = *(int *)(param_1 + 0x68);
        Close__10MenuWindowFUci(iVar7 + 0x58,((ulong)*(byte *)(iVar7 + 0x108) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar7 + 0x8c) + 0x14));
        iVar7 = *(int *)(param_1 + 0x7c);
        Close__10MenuWindowFUci(iVar7,((ulong)*(byte *)(iVar7 + 0xb0) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar7 + 0x34) + 0x14));
        sVar1 = *(short *)(iVar3 + 0x1e);
        if (sVar1 == 2) {
          iVar3 = *(int *)(param_1 + 0x88);
          Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
          iVar3 = *(int *)(param_1 + 0x90);
          Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
        }
        else if (sVar1 == 1) {
          iVar3 = *(int *)(param_1 + 0x84);
          Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
        }
        else if (sVar1 == 0) {
          iVar3 = *(int *)(param_1 + 0x80);
          Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
        }
        SetButtonReport__9CmdFusionFi(param_1,1);
        puVar5 = PTR_ShiftList__9CmdFusionFv_0050d820;
        uVar6 = DAT_0050d81c;
        *(undefined4 *)(param_1 + 0x5c) = _7049;
        *(undefined4 *)(param_1 + 0x60) = uVar6;
        *(undefined **)(param_1 + 100) = puVar5;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),3,0,0);
      }
    }
    else {
      if (sVar1 == 2) {
        lVar10 = IsMaxLevel__9CmdFusionFv(param_1);
        if ((lVar10 == 0) && (**(short **)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4) != 0)) {
          *(byte *)(*(int *)(param_1 + 0x9c) + 0x46) =
               *(byte *)(*(int *)(param_1 + 0x9c) + 0x46) & 0xfd;
          *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
               *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
          SetExplanation__7CmdNoteFPCce
                    (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                     *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x34));
          puVar5 = PTR_SoulCharge__9CmdFusionFv_0050d810;
          uVar6 = DAT_0050d80c;
          *(undefined4 *)(param_1 + 0x5c) = _7037;
          *(undefined4 *)(param_1 + 0x60) = uVar6;
          *(undefined **)(param_1 + 100) = puVar5;
          lVar10 = __nw__FUi(0x188);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__16CmdFusionLevelupFv(lVar10);
          }
          *(undefined4 *)(param_1 + 0x8c) = uVar6;
          CreateScene__16CmdFusionLevelupFP9CmdFusion(*(undefined4 *)(param_1 + 0x8c),param_1);
          SetButtonReport__9CmdFusionFi(param_1,2);
        }
      }
      else if (sVar1 == 1) {
        uVar9 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x84),0,0);
        Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar9);
        Select__18CmdFusionSkillListFP9CmdFusionP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(param_1 + 0x84),param_1,uVar9,0);
        puVar5 = PTR_SelectSkill__9CmdFusionFv_0050d800;
        uVar6 = DAT_0050d7fc;
        *(undefined4 *)(param_1 + 0x5c) = _7030;
        *(undefined4 *)(param_1 + 0x60) = uVar6;
        *(undefined **)(param_1 + 100) = puVar5;
      }
      if (*(int *)(*(int *)(param_1 + 0x7c) + 0x44) != 0) {
        iVar3 = *(int *)(*(int *)(param_1 + 0x7c) + 0x44);
        *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xfe;
      }
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),2,0,0);
    }
  }
  return 0;
}

/* JP: 0x00471db0  CmdFusion::SelectSkill()   [SelectSkill__9CmdFusionFv]  size=0x298 */
undefined8 SelectSkill__9CmdFusionFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x4000) == 0) {
    iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar3 != iVar4) {
      Select__18CmdFusionSkillListFP9CmdFusionP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x84),param_1,iVar4,iVar3);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),0,0,0);
    }
  }
  else {
    Select__18CmdFusionSkillListFP9CmdFusionP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(param_1 + 0x84),param_1,0,iVar3);
    iVar3 = GetPlace__10MenuWindowFss(*(int *)(param_1 + 0x6c) + 0x58,0,1);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar3);
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace(*(undefined4 *)(param_1 + 0x6c),0,iVar3,0);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
               *(undefined4 *)
                ((uint)*(ushort *)(iVar3 + 0x22) * 0xc + *(int *)(param_1 + 0x28) + 0x14));
    if (*(int *)(*(int *)(param_1 + 0x7c) + 0x44) != 0) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x7c) + 0x44);
      *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xfe | 1;
    }
    puVar2 = PTR_SelectMenu__9CmdFusionFv_0050d830;
    uVar1 = DAT_0050d82c;
    *(undefined4 *)(param_1 + 0x5c) = _7239;
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined **)(param_1 + 100) = puVar2;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),3,0,0);
  }
  return 0;
}

/* JP: 0x00472050  CmdFusion::SoulCharge()   [SoulCharge__9CmdFusionFv]  size=0xb28 */
/* WARNING: Removing unreachable block (ram,0x00472370) */
/* WARNING: Removing unreachable block (ram,0x00472408) */

undefined8 SoulCharge__9CmdFusionFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined4 uVar12;
  long lVar13;
  float fVar14;
  uint uVar15;
  uint uVar16;
  float fStack_3c;
  
  iVar8 = GetActive__4CPadFi(0);
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  uVar9 = (uint)**(ushort **)(*(int *)(*(int *)(param_1 + 0x58) + 0x5c) + 4);
  iVar3 = *(int *)(param_1 + 0x9c);
  iVar4 = *(int *)(iVar3 + 0x18);
  cVar7 = *(char *)(param_1 + 0x21);
  if (cVar7 == '\0') {
    if (*(short *)(iVar3 + 0x6a) == 3) {
      lVar13 = __nw__FUi(0x1bc);
      uVar12 = 0;
      if (lVar13 != 0) {
        uVar12 = __ct__13MenuModelAuraFv(lVar13);
      }
      *(undefined4 *)(param_1 + 0xa0) = uVar12;
      CreateAura__13MenuModelAuraFP16MenuModelManegerP12MenuAuraData
                (*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0x9c),
                 *(int *)(param_1 + 0xac) + *(short *)(param_1 + 0xbc) * 0x54 + 0xc);
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (cVar7 == '\x01') {
    if (((*(char *)(*(int *)(param_1 + 0xa0) + 0x1b8) == '\0') || ((uVar2 & 0x2000) == 0)) ||
       ((long)((ulong)*(byte *)(iVar4 + 0x6b) << 0x3e) < 0)) {
      if ((((uVar2 & 0x4000) != 0) || (lVar13 = IsMaxLevel__9CmdFusionFv(param_1), lVar13 != 0)) ||
         (uVar9 == 0)) {
        (**(code **)(*(int *)(*(int *)(param_1 + 0x8c) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x8c) = 0;
        Standby__13MenuModelAuraFUc(*(undefined4 *)(param_1 + 0xa0),1);
        *(undefined4 *)(param_1 + 0xa0) = 0;
        *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
        *(byte *)(iVar3 + 0x46) = *(byte *)(iVar3 + 0x46) & 0xfd | 2;
        SetExplanation__7CmdNoteFPCce
                  (*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                   *(undefined4 *)
                    ((uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x22) * 0xc +
                     *(int *)(param_1 + 0x28) + 0x14));
        if (*(int *)(*(int *)(param_1 + 0x7c) + 0x44) != 0) {
          iVar3 = *(int *)(*(int *)(param_1 + 0x7c) + 0x44);
          *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xfe | 1;
        }
        SetButtonReport__9CmdFusionFi(param_1,0);
        puVar6 = PTR_SelectMenu__9CmdFusionFv_0050d840;
        uVar12 = DAT_0050d83c;
        *(undefined4 *)(param_1 + 0x5c) = _7345;
        *(undefined4 *)(param_1 + 0x60) = uVar12;
        *(undefined **)(param_1 + 100) = puVar6;
        *(undefined1 *)(param_1 + 0x21) = 0;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x94),3,0,0);
      }
    }
    else {
      uVar12 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0xd8);
      SetMotion__13MenuModelPackFPCcUcUc(iVar4,uVar12,1,0);
      BootEffect__13MenuModelPackFPCci(iVar4,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0xf0),0);
      *(undefined1 *)(iVar4 + 0x6a) = 0;
      Boot__13MenuModelAuraFv(*(undefined4 *)(param_1 + 0xa0));
      iVar3 = *(int *)(*(int *)(param_1 + 0xa0) + 0x18);
      SetMotion__13MenuModelPackFPCcUcUc(iVar3,uVar12,1,0);
      *(undefined1 *)(iVar3 + 0x6a) = 0;
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (cVar7 == '\x02') {
    if (*(char *)(iVar4 + 0x6a) != '\0') {
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (cVar7 == '\x03') {
    uVar12 = *(undefined4 *)(*(int *)(param_1 + 0xa0) + 0x18);
    if (((*(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar8 + 4) * 4) + 0x6a) & 0x2000) ==
         0) || (uVar9 == 0)) {
      uVar12 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0xf8);
      SetMotion__13MenuModelPackFPCcUcUc(iVar4,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0xe0),0,1);
      *(undefined4 *)(iVar4 + 0x1c) = uVar12;
      Close__13MenuModelAuraFv(*(undefined4 *)(param_1 + 0xa0));
      CloseEffect__13MenuModelAuraFv(*(undefined4 *)(param_1 + 0xa0));
      *(undefined1 *)(param_1 + 0x21) = 1;
    }
    else {
      sVar1 = *(short *)(param_1 + 0xbc);
      iVar3 = *(int *)(*(int *)(param_1 + 0x58) + 0x5c);
      uVar10 = GetNextExp__9CmdFusionFs(param_1,1);
      iVar8 = *(int *)(param_1 + 0xac) + sVar1 * 0x54;
      fVar14 = *(float *)(param_1 + 0xc4);
      if (fVar14 < 2.1474836e+09) {
        uVar15 = (uint)fVar14;
      }
      else {
        uVar15 = (int)(fVar14 - 2.1474836e+09) | 0x80000000;
      }
      iVar11 = GetRegDat__9RegDatApiFiii(0x2d,sVar1,*(undefined1 *)(*(int *)(iVar3 + 4) + (int)sVar1 + 0xd94))
      ;
      fStack_3c = (float)*(ushort *)(iVar11 + 0xe) / 180.0;
      if (fStack_3c < 2.1474836e+09) {
        uVar16 = (uint)fStack_3c;
      }
      else {
        uVar16 = (int)(fStack_3c - 2.1474836e+09) | 0x80000000;
      }
      if (uVar9 < uVar16) {
        fStack_3c = (float)uVar9;
      }
      *(float *)(param_1 + 0xc4) = *(float *)(param_1 + 0xc4) + fStack_3c;
      fVar14 = *(float *)(param_1 + 0xc4);
      if (fVar14 < 2.1474836e+09) {
        uVar16 = (uint)fVar14;
      }
      else {
        uVar16 = (int)(fVar14 - 2.1474836e+09) | 0x80000000;
      }
      iVar11 = uVar16 - uVar15;
      uVar15 = uVar16;
      if (uVar10 <= uVar16) {
        iVar11 = iVar11 - (uVar16 - uVar10);
        *(float *)(param_1 + 0xc4) = (float)uVar10;
        uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0xe8);
        SetMotion__13MenuModelPackFPCcUcUc(iVar4,uVar5,0,1);
        SetMotion__13MenuModelPackFPCcUcUc(uVar12,uVar5,0,1);
        CloseEffect__13MenuModelAuraFv(*(undefined4 *)(param_1 + 0xa0));
        iVar4 = *(int *)(param_1 + 0x8c);
        Open__10MenuWindowFUci(iVar4,*(byte *)(iVar4 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x10));
        *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
        uVar15 = uVar10;
      }
      for (cVar7 = *(char *)(iVar8 + 0x48); cVar7 < *(char *)(iVar8 + 0x49); cVar7 = cVar7 + '\x01')
      {
        *(uint *)(*(int *)(iVar3 + 4) + (short)cVar7 * 4 + 0xd50) = uVar15;
        *(char *)(*(int *)(iVar3 + 4) + (int)(short)cVar7 + 0xd94) =
             (uVar10 <= uVar16) + *(char *)(*(int *)(iVar3 + 4) + (int)(short)cVar7 + 0xd94);
      }
      **(undefined2 **)(iVar3 + 4) = (short)(uVar9 - iVar11);
      SetMeter__13CmdSoulEnergyFUi(*(undefined4 *)(param_1 + 0x90),uVar9 - iVar11);
      UpdateParameter__9CmdFusionFs(param_1,0);
      UpdateCharge__9CmdFusionFs(param_1,0);
    }
  }
  else if ((cVar7 == '\x04') && (-1 < (long)((ulong)*(byte *)(iVar4 + 0x6b) << 0x3e))) {
    Close__13MenuModelAuraFv(*(undefined4 *)(param_1 + 0xa0));
    iVar3 = *(int *)(param_1 + 0x8c);
    Close__10MenuWindowFUci(iVar3,((ulong)*(byte *)(iVar3 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x14));
    ResetEffect__13MenuModelPackFv(iVar4);
    *(undefined1 *)(param_1 + 0x21) = 1;
  }
  return 0;
}

/* JP: 0x00472b80  CmdFusion::ShiftList()   [ShiftList__9CmdFusionFv]  size=0x3a0 */
undefined8 ShiftList__9CmdFusionFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    if ((*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x7c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x7c) = 0;
      if (*(int *)(param_1 + 0x80) != 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x80));
        (**(code **)(*(int *)(*(int *)(param_1 + 0x80) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x80) = 0;
      }
      if (*(int *)(param_1 + 0x84) != 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x84));
        (**(code **)(*(int *)(*(int *)(param_1 + 0x84) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x84) = 0;
      }
      if (*(int *)(param_1 + 0x88) != 0) {
        (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x88) = 0;
        (**(code **)(*(int *)(*(int *)(param_1 + 0x90) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x90) = 0;
        Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x98));
      }
      FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x78));
      iVar1 = *(int *)(param_1 + 0x78);
      Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
      UpdateTitle__9CmdFusionFs(param_1,0x15);
      UpdateFence__9CmdFusionFv(param_1);
      iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
      Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x6c),0,0,
                 *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec));
      uVar5 = GetPlace__10MenuWindowFs(*(undefined4 *)(param_1 + 0x78),*(undefined2 *)(param_1 + 0xbc));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                (*(undefined4 *)(param_1 + 0x78),param_1,uVar5,0,1);
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectList__9CmdFusionFv_0050d850;
      uVar3 = DAT_0050d84c;
      *(undefined4 *)(param_1 + 0x5c) = _7483;
      *(undefined4 *)(param_1 + 0x60) = uVar3;
      *(undefined **)(param_1 + 100) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x00472f20  CmdFusion::ShiftMenu()   [ShiftMenu__9CmdFusionFv]  size=0x1a4 */
undefined8 ShiftMenu__9CmdFusionFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      UpdateParameter__9CmdFusionFs(param_1,1);
      UpdateStatus__9CmdFusionFs(param_1,1);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x74) = 0;
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x7c) + 0xa8) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar3 = PTR_SelectMenu__9CmdFusionFv_0050d860;
      uVar2 = DAT_0050d85c;
      *(undefined4 *)(param_1 + 0x5c) = _7536;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x004730d0  CmdFusion::ShiftExplain()   [ShiftExplain__9CmdFusionFv]  size=0x164 */
undefined8 ShiftExplain__9CmdFusionFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  puVar3 = PTR_SelectList__9CmdFusionFv_0050d880;
  uVar2 = DAT_0050d87c;
  if ((*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x78) + 0xa8) == '\0') {
      UpdateTitle__9CmdFusionFs(param_1,0x14);
      SetExplanation__9CmdFusionFv(param_1);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x74) = 0;
      puVar3 = PTR_ExecExplain__9CmdFusionFv_0050d870;
      uVar2 = DAT_0050d86c;
      *(undefined4 *)(param_1 + 0x5c) = _7564;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
    else {
      *(undefined4 *)(param_1 + 0x5c) = _7567;
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined **)(param_1 + 100) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00473240  CmdFusion::ExecExplain()   [ExecExplain__9CmdFusionFv]  size=0x370 */
undefined8 ExecExplain__9CmdFusionFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long lVar4;
  
  lVar4 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0x70),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if (lVar4 != 0) {
    if ((int)lVar4 == 4) {
      if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x70) + 0x525) << 0x3d) < 0) {
        Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                  (*(undefined4 *)(param_1 + 0x78),param_1,
                   *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0,1);
        FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x78));
        iVar1 = *(int *)(param_1 + 0x78);
        Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
        UpdateFence__9CmdFusionFv(param_1);
        *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x78) + 0x104) = 0x8000;
        iVar1 = *(int *)(*(int *)(param_1 + 0x58) + 0x78);
        Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                        *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
        UpdateTitle__9CmdFusionFs(param_1,0x15);
        QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
        ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
        *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
        (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
        puVar3 = PTR_ShiftExplain__9CmdFusionFv_0050d890;
        uVar2 = DAT_0050d88c;
        *(undefined4 *)(param_1 + 0x5c) = _7597;
        *(undefined4 *)(param_1 + 0x60) = uVar2;
        *(undefined **)(param_1 + 100) = puVar3;
      }
      else {
        uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
        MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),
                        (int)(uint)(*(byte *)(*(int *)(param_1 + 0x70) + 0x524) >> 4) >> 2);
        Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
                  (*(undefined4 *)(param_1 + 0x78),param_1,
                   *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),uVar2,0);
        SetExplanation__9CmdFusionFv(param_1);
      }
    }
    else if (((int)lVar4 == 3) &&
            ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x70) + 0x525) << 0x3d) < 0)) {
      iVar1 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    }
  }
  return 0;
}
