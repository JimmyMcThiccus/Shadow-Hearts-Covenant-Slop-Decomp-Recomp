/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdEquipment   functions: 21
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdEquipment.md).
 */

/* JP: 0x0044b820  CmdEquipment::CmdEquipment()   [__ct__12CmdEquipmentFv]  size=0x84 */
int __ct__12CmdEquipmentFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdEquipment;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined1 *)(param_1 + 0xa4) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  return param_1;
}

/* JP: 0x0044b8b0  CmdEquipment::~CmdEquipment()   [__dt__12CmdEquipmentFv]  size=0x18c */
int __dt__12CmdEquipmentFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdEquipment;
    if (*(int *)(param_1 + 0x88) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x8c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x8c) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x90) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x90) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x94) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x94) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x98) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x98) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x9c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x9c) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0xa0) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0xa0) + 8) + 0xc))();
    }
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044ba40  CmdEquipment::GetReady()   [GetReady__12CmdEquipmentFv]  size=0x3fc */
undefined4 GetReady__12CmdEquipmentFv(int param_1)

{
  undefined *puVar1;
  ushort uVar2;
  short sVar3;
  undefined4 uVar4;
  long lVar5;
  short sVar6;
  undefined1 auStack_b0 [96];
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  int iStack_14;
  int iStack_10;
  
  iStack_14 = *(int *)(param_1 + 0x10);
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_b0);
  for (uVar2 = 1; (short)uVar2 < 6; uVar2 = uVar2 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar2 * 0xc + *(int *)(iStack_10 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(iStack_10,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c));
  sVar3 = 8;
  sVar6 = 0;
  while( true ) {
    if (2 < sVar6) break;
    iStack_28 = iStack_14 + 0x28;
    uVar4 = Find__13MenuDataTableFs(iStack_28,sVar3);
    *(undefined4 *)(iStack_10 + sVar6 * 4 + 0xa8) = uVar4;
    *(int *)(iStack_10 + sVar6 * 4 + 0xb4) = *(int *)(iStack_10 + sVar6 * 4 + 0xa8) + 0x10;
    sVar6 = sVar6 + 1;
    sVar3 = sVar3 + 1;
  }
  iStack_2c = *(int *)(iStack_10 + 0x5c);
  iStack_34 = *(int *)(iStack_2c + 8) + 0x80;
  *(int *)(iStack_10 + 0xc0) = iStack_34;
  iStack_38 = *(int *)(iStack_10 + 0x5c);
  iStack_40 = *(int *)(iStack_38 + 8) + 0xe0;
  *(int *)(iStack_10 + 0xc4) = iStack_40;
  iStack_44 = *(int *)(iStack_10 + 0x5c);
  iStack_4c = *(int *)(iStack_44 + 8) + 0x110;
  *(int *)(iStack_10 + 200) = iStack_4c;
  *(undefined2 *)(*(int *)(iStack_10 + 0x18) + 0x32) = 0;
  iStack_48 = iStack_4c;
  iStack_3c = iStack_40;
  iStack_30 = iStack_34;
  iStack_24 = iStack_44;
  iStack_20 = iStack_38;
  iStack_1c = iStack_2c;
  sVar3 = GetLayerCount__10CmdPCSceneFs(iStack_10,0);
  if (sVar3 < 2) {
    *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(iStack_10,0);
  lVar5 = __nw__FUi(0x154);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__10CmdSubMenuFv(lVar5);
  }
  *(undefined4 *)(iStack_10 + 0x88) = uVar4;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(iStack_10 + 0x88),
                  *(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28),0);
  iStack_50 = *(int *)(iStack_10 + 0x28) + 0x10;
  CreateScene__10CmdSubMenuFsP9MSDSystem(*(undefined4 *)(iStack_10 + 0x88),2,iStack_50);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_b0,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x4c),0);
  lVar5 = __nw__FUi(0x178);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__8CmdFenceFv(lVar5);
  }
  *(undefined4 *)(iStack_10 + 0x90) = uVar4;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x90),auStack_b0,0);
  *(undefined1 *)(iStack_10 + 0xa5) = 1;
  puVar1 = PTR_Enter__12CmdEquipmentFv_0050d3c0;
  uVar4 = DAT_0050d3bc;
  *(undefined4 *)(iStack_10 + 0x7c) = _5381;
  *(undefined4 *)(iStack_10 + 0x80) = uVar4;
  *(undefined **)(iStack_10 + 0x84) = puVar1;
  uStack_18 = 1;
  __dt__9MenuSceneFv(auStack_b0,0xffffffffffffffff);
  return uStack_18;
}

/* JP: 0x0044be40  CmdEquipment::Run()   [Run__12CmdEquipmentFv]  size=0x104 */
undefined4 Run__12CmdEquipmentFv(int param_1)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = ChengePC__10CmdPCSceneFv(param_1);
  if (lVar2 == 0) {
    if (*(int *)(param_1 + 0x78) != 0) {
      if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (!bVar1) {
        *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48) = 0;
      }
    }
    lVar2 = __ptmf_test(param_1 + 0x7c);
    if ((lVar2 != 0) && (lVar2 = __ptmf_scall(param_1), lVar2 == 0)) {
      return 0;
    }
  }
  return 1;
}

/* JP: 0x0044bf50  CmdEquipment::Update(short)   [Update__12CmdEquipmentFs]  size=0x1cc */
void Update__12CmdEquipmentFs(int param_1,undefined2 param_2)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  
  sVar2 = -1;
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,param_2,0);
  UpdateStatus__12CmdEquipmentFsP11CmdPCStatus(param_1,param_2,0);
  if (*(int *)(param_1 + 0x94) != 0) {
    UpdateSlot__12CmdEquipmentFss(param_1,param_2,0);
  }
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if (iVar1 != 0) {
    sVar2 = *(short *)(iVar1 + 0x16);
  }
  if (*(int *)(param_1 + 0x98) != 0) {
    UpdateGoods__12CmdEquipmentFscc(param_1,param_2,*(undefined1 *)(param_1 + 0xa4),(char)sVar2);
  }
  if ((*(int *)(param_1 + 0xcc) != 0) && (iVar1 != 0)) {
    if (sVar2 < 0) {
      uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x28) + 0x44);
    }
    else {
      uVar3 = GetRegDat__9RegDatApiFiii(*(char *)(param_1 + 0xa4) + 0x17,sVar2,0xffffffffffffffff);
    }
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 100),uVar3);
    SetButtonReport__12CmdEquipmentFss(param_1,0,sVar2);
  }
  return;
}

/* JP: 0x0044c120  CmdEquipment::UpdateSlot(short, short)   [UpdateSlot__12CmdEquipmentFss]  size=0x258 */
void UpdateSlot__12CmdEquipmentFss(int param_1,short param_2,short param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  short sVar4;
  
  if (*(int *)(param_1 + 0x94) == 0) {
    lVar3 = __nw__FUi(0x714);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__16CmdEquipmentSlotFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x94) = uVar2;
    CreateScene__16CmdEquipmentSlotFP12CmdEquipment(*(undefined4 *)(param_1 + 0x94),param_1);
    lVar3 = __nw__FUi(0x1c8);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__11CmdSubTitleFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x8c),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34)
                    ,0);
    Create__11CmdSubTitleFi(*(undefined4 *)(param_1 + 0x8c),3);
  }
  UpdateScene__16CmdEquipmentSlotFP12CmdEquipment(*(undefined4 *)(param_1 + 0x94),param_1);
  Reset__11CmdSubTitleFv(*(undefined4 *)(param_1 + 0x8c));
  for (sVar4 = 0; sVar4 < 3; sVar4 = sVar4 + 1) {
    SetTitle__11CmdSubTitleFii(*(undefined4 *)(param_1 + 0x8c),sVar4,sVar4);
  }
  if (param_2 == 0) {
    *(byte *)(*(int *)(param_1 + 0x94) + 0x12) =
         *(byte *)(*(int *)(param_1 + 0x94) + 0x12) & 0xfe | 1;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x94);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  *(byte *)(*(int *)(param_1 + 0x8c) + 0x6a) = *(byte *)(*(int *)(param_1 + 0x8c) + 0x6a) & 0xfe | 1
  ;
  if (param_3 != 0) {
    iVar1 = *(int *)(param_1 + 0x8c);
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  }
  return;
}

/* JP: 0x0044c380  CmdEquipment::UpdateStatus(short, CmdPCStatus*)   [UpdateStatus__12CmdEquipmentFsP11CmdPCStatus]  size=0x140 */
void UpdateStatus__12CmdEquipmentFsP11CmdPCStatus(int param_1,short param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined4 uStack_10;
  
  uStack_10 = param_3;
  if (param_3 == 0) {
    uStack_10 = *(int *)(param_1 + 0x70) + 8;
  }
  if (*(int *)(param_1 + 0x9c) == 0) {
    lVar3 = __nw__FUi(0xb34);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__18CmdEquipmentStatusFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x9c) = uVar2;
    CreateScene__18CmdEquipmentStatusFP12CmdEquipment(*(undefined4 *)(param_1 + 0x9c),param_1);
  }
  UpdateScene__18CmdEquipmentStatusFP12CmdEquipmentP11CmdPCStatus
            (*(undefined4 *)(param_1 + 0x9c),param_1,uStack_10);
  *(byte *)(*(int *)(param_1 + 0x9c) + 0x12) = *(byte *)(*(int *)(param_1 + 0x9c) + 0x12) & 0xfe | 1
  ;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_1 + 0x9c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x0044c4c0  CmdEquipment::UpdateGoods(short, char, char)   [UpdateGoods__12CmdEquipmentFscc]  size=0x1b4 */
void UpdateGoods__12CmdEquipmentFscc(int param_1,short param_2,char param_3,char param_4)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  uVar5 = 1;
  if (*(int *)(param_1 + 0x98) == 0) {
    lVar3 = __nw__FUi(300);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__17CmdEquipmentGoodsFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x98) = uVar2;
    uVar4 = GetPropertyMax__12CmdEquipmentFv(param_1);
    CreateScene__17CmdEquipmentGoodsFP12CmdEquipmentUs
              (*(undefined4 *)(param_1 + 0x98),param_1,uVar4);
  }
  if ((param_3 == '\x02') && (-1 < param_4)) {
    uVar5 = 0xffffffffffffffff;
  }
  lVar3 = SetProperty__12CmdEquipmentFcUs(param_1,param_3,0);
  if ((lVar3 == 0) && ((short)uVar5 == 1)) {
    uVar5 = 0;
  }
  UpdateScene__17CmdEquipmentGoodsFP12CmdEquipments(*(undefined4 *)(param_1 + 0x98),param_1,uVar5);
  if (param_2 == 0) {
    *(byte *)(*(int *)(param_1 + 0x98) + 0x12) =
         *(byte *)(*(int *)(param_1 + 0x98) + 0x12) & 0xfe | 1;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x98);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x0044c680  CmdEquipment::SetProperty(char, unsigned short)   [SetProperty__12CmdEquipmentFcUs]  size=0x410 */
short SetProperty__12CmdEquipmentFcUs(int param_1,char param_2,ushort param_3)

{
  byte bVar1;
  short sVar2;
  ushort uVar3;
  int *piVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  long lVar10;
  int iVar11;
  uint uVar12;
  ushort *unaff_s4_lo;
  int unaff_s7_lo;
  short sVar13;
  ushort uStack_3a;
  ushort uStack_10;
  
  iVar9 = 0;
  *(char *)(param_1 + 0xa4) = param_2;
  piVar4 = *(int **)(param_1 + 0x70);
  bVar1 = *(byte *)(*piVar4 + 0x59);
  iVar11 = *(int *)(param_1 + param_2 * 4 + 0xb4);
  sVar2 = *(short *)(*(int *)(param_1 + param_2 * 4 + 0xa8) + 4);
  uVar5 = *(uint *)(*(int *)(param_1 + param_2 * 4 + 0xa8) + 8);
  iVar7 = GetRegDat__9RegDatApiFiii(0x31,0,0xffffffffffffffff);
  iVar8 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uStack_10 = param_3;
  if (param_3 == 0) {
    uStack_10 = (ushort)(1 << (*(byte *)(*piVar4 + 2) & 0x1f));
    iVar9 = *piVar4 + (int)param_2 + 0x2d;
  }
  if (param_2 == '\x02') {
    unaff_s7_lo = 0x16;
    unaff_s4_lo = (ushort *)(iVar8 + 4);
    uStack_3a = *(ushort *)(iVar7 + *(char *)(*piVar4 + 0x2e) * 0x18 + 0x16);
  }
  else if (param_2 == '\x01') {
    unaff_s7_lo = 0xc;
    unaff_s4_lo = (ushort *)(iVar7 + 4);
  }
  else if (param_2 == '\0') {
    unaff_s7_lo = 0x1a;
    iVar7 = GetRegDat__9RegDatApiFiii(0x30,0,0xffffffffffffffff);
    unaff_s4_lo = (ushort *)(iVar7 + 6);
  }
  sVar13 = 0;
  uVar12 = 0;
  do {
    if ((uVar5 & 0xffff) <= uVar12) {
      return sVar13;
    }
    *(undefined1 *)(iVar11 + 9) = 0;
    cVar6 = GetPropertyCount__12CmdEquipmentFc(param_1,(char)uVar12);
    if (((cVar6 != '\0') && ((*unaff_s4_lo & uStack_10) != 0)) &&
       ((*(byte *)(iVar11 + 10) & bVar1 & 1) == 0)) {
      if (iVar9 != 0) {
        lVar10 = 0;
        while (((lVar10 < sVar2 && (iVar7 = (int)lVar10, (char)uVar12 != *(char *)(iVar9 + iVar7)))
               && ((param_2 != '\x02' ||
                   ((uVar3 = *(ushort *)(iVar8 + uVar12 * 0x2c + 0x2a), (uVar3 & uStack_3a) == 0 &&
                    ((uVar3 & *(ushort *)
                               (iVar8 + (*(char *)(iVar9 + iVar7) * 10 +
                                        (int)*(char *)(iVar9 + iVar7)) * 4 + 0x2a)) == 0))))))) {
          lVar10 = (long)(iVar7 + 1);
        }
        if (lVar10 != sVar2) goto LAB_0044ca28;
      }
      *(undefined1 *)(iVar11 + 9) = 1;
      sVar13 = sVar13 + 1;
    }
LAB_0044ca28:
    uVar12 = uVar12 + 1 & 0xffff;
    iVar11 = iVar11 + 0xc;
    unaff_s4_lo = unaff_s4_lo + unaff_s7_lo;
  } while( true );
}

/* JP: 0x0044ca90  CmdEquipment::GetPropertyMax()   [GetPropertyMax__12CmdEquipmentFv]  size=0xc4 */
uint GetPropertyMax__12CmdEquipmentFv(int param_1)

{
  uint uVar1;
  
  if ((*(uint *)(*(int *)(param_1 + 0xa8) + 8) < *(uint *)(*(int *)(param_1 + 0xac) + 8)) ||
     (*(uint *)(*(int *)(param_1 + 0xa8) + 8) < *(uint *)(*(int *)(param_1 + 0xb0) + 8))) {
    if (*(uint *)(*(int *)(param_1 + 0xac) + 8) < *(uint *)(*(int *)(param_1 + 0xb0) + 8)) {
      uVar1 = *(uint *)(*(int *)(param_1 + 0xb0) + 8) & 0xffff;
    }
    else {
      uVar1 = *(uint *)(*(int *)(param_1 + 0xac) + 8) & 0xffff;
    }
  }
  else {
    uVar1 = *(uint *)(*(int *)(param_1 + 0xa8) + 8) & 0xffff;
  }
  return uVar1;
}

/* JP: 0x0044cb60  CmdEquipment::GetPropertyCount(char)   [GetPropertyCount__12CmdEquipmentFc]  size=0x1fc */
char GetPropertyCount__12CmdEquipmentFc(int param_1,char param_2)

{
  short sVar1;
  char cVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  
  cVar2 = '\0';
  if (*(char *)(param_1 + 0xa5) != '\0') {
    piVar3 = (int *)(*(int *)(param_1 + 0x5c) + 0x30);
    sVar1 = *(short *)(*(int *)(param_1 + 0x5c) + 0xe);
    piVar4 = piVar3 + sVar1 * 0x12 + (int)sVar1;
    for (; piVar3 < piVar4; piVar3 = piVar3 + 0x13) {
      for (uVar5 = 0;
          uVar5 < *(ushort *)(*(int *)(param_1 + *(char *)(param_1 + 0xa4) * 4 + 0xa8) + 4);
          uVar5 = uVar5 + 1 & 0xffff) {
        if (param_2 == *(char *)(*piVar3 + (int)*(char *)(param_1 + 0xa4) + 0x2d + uVar5)) {
          cVar2 = cVar2 + '\x01';
        }
      }
    }
  }
  return *(char *)(*(int *)(param_1 + *(char *)(param_1 + 0xa4) * 4 + 0xc0) + (int)param_2) - cVar2;
}

/* JP: 0x0044cd60  CmdEquipment::StartExplain(short)   [StartExplain__12CmdEquipmentFs]  size=0x3fc */
undefined4 StartExplain__12CmdEquipmentFs(int param_1,short param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined2 uStack_22;
  
  uStack_22 = 0;
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if (*(short *)(iVar1 + 0x16) < 0) {
    uVar3 = 0;
  }
  else {
    lVar4 = __nw__FUi(0x52c);
    uVar5 = 0;
    if (lVar4 != 0) {
      uVar5 = __ct__10CmdExplainFv(lVar4);
    }
    *(int *)(param_1 + 0xa0) = (int)uVar5;
    if (param_2 != 0) {
      Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x98),param_1,0,iVar1);
      uStack_22 = *(undefined2 *)(*(int *)(param_1 + 0x98) + 0x128);
    }
    Initialize__9MenuSceneFPUcP9BufMemory(uVar5,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x40),0);
    SetInfo__10CmdExplainFP4MenusUcUc(uVar5,*(undefined4 *)(param_1 + 0x10),uStack_22,3,0);
    SetIcon__10CmdExplainFP11MenuTexture(uVar5,0x421698);
    SetImage__10CmdExplainFPcss
              (uVar5,*(undefined4 *)
                      ((uint)(ushort)(short)*(char *)(param_1 + 0xa4) * 8 + *(int *)(param_1 + 0x24)
                      + 0x10),1,0);
    SetChengePCMode__10CmdPCSceneFUc(param_1,0);
    *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 100),
               *(undefined4 *)
                ((uint)(ushort)((short)*(char *)(param_1 + 0xa4) + 4) * 0xc +
                 *(int *)(param_1 + 0x28) + 0x14));
    iVar1 = *(int *)(param_1 + 0x8c);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x90);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x9c);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x94);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x98);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(short *)(*(int *)(param_1 + 0x98) + 0xae) = param_2;
    puVar2 = PTR_ShiftExplain__12CmdEquipmentFv_0050d3d0;
    uVar3 = DAT_0050d3cc;
    *(undefined4 *)(param_1 + 0x7c) = _5744;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar2;
    uVar3 = 1;
  }
  return uVar3;
}

/* JP: 0x0044d160  CmdEquipment::SetExplanation()   [SetExplanation__12CmdEquipmentFv]  size=0x14c */
void SetExplanation__12CmdEquipmentFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(param_1 + 0xa0);
  memset(iVar2 + 0x5c,0,0x10);
  uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  puVar4 = (undefined4 *)
           (*(int *)(param_1 + *(char *)(param_1 + 0xa4) * 4 + 0xb4) + (uint)uVar1 * 0xc);
  *(ushort *)(iVar2 + 0x5c) = uVar1;
  *(undefined1 *)(iVar2 + 0x5e) = *(undefined1 *)(puVar4 + 2);
  uVar3 = GetRegDat__9RegDatApiFiii(*(char *)(param_1 + 0xa4) + 6,uVar1,0xffffffffffffffff);
  *(undefined4 *)(iVar2 + 0x60) = uVar3;
  *(undefined4 *)(iVar2 + 100) = *puVar4;
  *(undefined4 **)(iVar2 + 0x68) = puVar4 + 1;
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0xa0));
  return;
}

/* JP: 0x0044d2b0  CmdEquipment::SetButtonReport(short, short)   [SetButtonReport__12CmdEquipmentFss]  size=0xb0 */
void SetButtonReport__12CmdEquipmentFss(int param_1,short param_2,short param_3)

{
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
  if (param_2 != 0) {
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),0xd);
  }
  if (-1 < param_3) {
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),4);
  }
  return;
}

/* JP: 0x0044d360  CmdEquipment::Enter()   [Enter__12CmdEquipmentFv]  size=0x2bc */
undefined8 Enter__12CmdEquipmentFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    UpdateSlot__12CmdEquipmentFss(param_1,1,1);
    UpdateStatus__12CmdEquipmentFsP11CmdPCStatus(param_1,1,0);
    UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,1,0);
    UpdateGoods__12CmdEquipmentFscc(param_1,1,0,0xffffffffffffffff);
    iVar1 = *(int *)(param_1 + 0x90);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    UpdateScene__10CmdSubMenuFs(*(undefined4 *)(param_1 + 0x88),0);
    uVar6 = GetPlace__10MenuWindowFss(*(int *)(param_1 + 0x88) + 0x58,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 100),uVar6,0);
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0xc)
    ;
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x60));
    uVar5 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar5;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x94) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x94) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectMenu__12CmdEquipmentFv_0050d3e0;
      uVar3 = DAT_0050d3dc;
      *(undefined4 *)(param_1 + 0x7c) = _5864;
      *(undefined4 *)(param_1 + 0x80) = uVar3;
      *(undefined **)(param_1 + 0x84) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x0044d620  CmdEquipment::Exit()   [Exit__12CmdEquipmentFv]  size=0x2c0 */
undefined8 Exit__12CmdEquipmentFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,4);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x9c);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x60);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x88);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x8c);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x90);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x98);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x94);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x0044d8e0  CmdEquipment::SelectMenu()   [SelectMenu__12CmdEquipmentFv]  size=0x68c */
undefined8 SelectMenu__12CmdEquipmentFv(int param_1)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  long lVar10;
  char *pcVar11;
  short sVar12;
  short sVar13;
  char unaff_s7_lo;
  ushort auStack_10024 [32730];
  ushort auStack_24 [4];
  short sStack_1c;
  ushort uStack_1a;
  ushort uStack_18;
  short sStack_16;
  short sStack_14;
  byte bStack_12;
  byte bStack_11;
  int iStack_10;
  
  uStack_1a = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uStack_18 = uStack_1a;
  iStack_10 = param_1;
  if ((uStack_1a & 0x2000) == 0) {
    if ((uStack_1a & 0x4000) == 0) {
      iVar7 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar3 != iVar7) {
        Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(iStack_10 + 0x88),*(undefined4 *)(iStack_10 + 100),iVar7,iVar3);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),0,0,0);
      }
    }
    else {
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar6 = PTR_Exit__12CmdEquipmentFv_0050d400;
      uVar5 = DAT_0050d3fc;
      *(undefined4 *)(iStack_10 + 0x7c) = _5994;
      *(undefined4 *)(iStack_10 + 0x80) = uVar5;
      *(undefined **)(iStack_10 + 0x84) = puVar6;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),3,0,0);
    }
  }
  else {
    sStack_1c = *(short *)(iVar3 + 0x1e);
    if (sStack_1c == 1) {
      piVar4 = *(int **)(param_1 + 0x70);
      bStack_12 = *(byte *)(*piVar4 + 0x59) & 1;
      sStack_16 = (short)*(char *)(param_1 + 0xa4);
      iVar3 = *(int *)(param_1 + 0xbc);
      bStack_11 = bStack_12;
      TakeOffEquipment__5CmdPCFv(piVar4);
      *(undefined1 *)(iStack_10 + 0xa4) = 0;
      for (pcVar11 = *(char **)(piVar4[1] + 0x18); -1 < *pcVar11; pcVar11 = pcVar11 + 1) {
        lVar10 = GetPropertyCount__12CmdEquipmentFc(iStack_10,*pcVar11);
        if (lVar10 != 0) {
          *(char *)(*piVar4 + 0x2d) = *pcVar11;
          break;
        }
      }
      *(undefined1 *)(iStack_10 + 0xa4) = 1;
      for (pcVar11 = *(char **)(piVar4[1] + 0x1c); -1 < *pcVar11; pcVar11 = pcVar11 + 1) {
        lVar10 = GetPropertyCount__12CmdEquipmentFc(iStack_10,*pcVar11);
        if (lVar10 != 0) {
          *(char *)(*piVar4 + 0x2e) = *pcVar11;
          unaff_s7_lo = *pcVar11;
          break;
        }
      }
      iVar7 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
      sStack_14 = *(short *)(*(int *)(iStack_10 + 0xb0) + 4);
      iVar8 = GetRegDat__9RegDatApiFiii(0x31,unaff_s7_lo,0xffffffffffffffff);
      uVar1 = *(ushort *)(iVar8 + 0x16);
      sVar12 = 0;
      *(undefined1 *)(iStack_10 + 0xa4) = 2;
      for (pcVar11 = *(char **)(piVar4[1] + 0x20); -1 < *pcVar11; pcVar11 = pcVar11 + 1) {
        lVar10 = GetPropertyCount__12CmdEquipmentFc(iStack_10,*pcVar11);
        if ((lVar10 != 0) && ((bStack_11 & *(byte *)(iVar3 + *pcVar11 * 0xc + 10)) == 0)) {
          uVar2 = *(ushort *)(iVar7 + (*pcVar11 * 10 + (int)*pcVar11) * 4 + 0x2a);
          sVar13 = 0;
          while ((sVar13 < sVar12 && ((uVar2 & auStack_24[sVar13]) == 0))) {
            sVar13 = sVar13 + 1;
          }
          if (((uVar1 & uVar2) == 0) && (sVar13 == sVar12)) {
            *(char *)(*piVar4 + (int)sVar12 + 0x2f) = *pcVar11;
            auStack_24[sVar12] = uVar2;
            sVar12 = sVar12 + 1;
            if (sVar12 == sStack_14) break;
          }
        }
      }
      *(char *)(iStack_10 + 0xa4) = (char)sStack_16;
      GetRealStatus__5CmdPCFP11CmdPCStatus(piVar4,piVar4 + 2);
      (**(code **)(*(int *)(iStack_10 + 8) + 0x28))(iStack_10,0);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),0x1004,0,0);
    }
    else {
      if (sStack_1c == 0) {
        uVar9 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x94),0,0);
        Select__6CursorFP9MenuPlace(*(undefined4 *)(iStack_10 + 0x18),uVar9);
        Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(iStack_10 + 0x94),iStack_10,uVar9,0);
        auStack_24[3] = *(undefined2 *)((int)uVar9 + 0x16);
        SetButtonReport__12CmdEquipmentFss(iStack_10,0,auStack_24[3]);
        Open__15CmdButtonReportFv(*(undefined4 *)(iStack_10 + 0x68));
        puVar6 = PTR_SelectSlot__12CmdEquipmentFv_0050d3f0;
        uVar5 = DAT_0050d3ec;
        *(undefined4 *)(iStack_10 + 0x7c) = _5942;
        *(undefined4 *)(iStack_10 + 0x80) = uVar5;
        *(undefined **)(iStack_10 + 0x84) = puVar6;
        *(undefined4 *)(iStack_10 + 0xcc) = 1;
      }
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_10 + 0x58),2,0,0);
    }
  }
  return 0;
}

/* JP: 0x0044df70  CmdEquipment::SelectSlot()   [SelectSlot__12CmdEquipmentFv]  size=0x490 */
undefined8 SelectSlot__12CmdEquipmentFv(int param_1)

{
  ushort uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      if ((uVar1 & 0x1000) == 0) {
        iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar3 != iVar4) {
          UpdateGoods__12CmdEquipmentFscc
                    (param_1,1,(char)*(undefined2 *)(iVar4 + 0x22),
                     (char)*(undefined2 *)(iVar4 + 0x16));
          Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
                    (*(undefined4 *)(param_1 + 0x94),param_1,iVar4,iVar3);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
        }
      }
      else {
        StartExplain__12CmdEquipmentFs(param_1,0);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
      }
    }
    else {
      Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x94),param_1,0,iVar3);
      iVar3 = GetPlace__10MenuWindowFss(*(int *)(param_1 + 0x88) + 0x58,0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar3);
      Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x88),*(undefined4 *)(param_1 + 100),iVar3,0);
      if ((long)*(char *)(param_1 + 0xa4) != (long)*(short *)(iVar3 + 0x22)) {
        UpdateGoods__12CmdEquipmentFscc(param_1,0,0,1);
      }
      iVar3 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
      *(undefined4 *)(param_1 + 0xcc) = 0;
      puVar2 = PTR_SelectMenu__12CmdEquipmentFv_0050d420;
      uVar7 = DAT_0050d41c;
      *(undefined4 *)(param_1 + 0x7c) = _6054;
      *(undefined4 *)(param_1 + 0x80) = uVar7;
      *(undefined **)(param_1 + 0x84) = puVar2;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
    }
  }
  else {
    uVar7 = 4;
    if (*(short *)(*(int *)(param_1 + 0x98) + 0x12a) != 0) {
      *(undefined2 *)(*(int *)(param_1 + 0x94) + 0x16) = *(undefined2 *)(iVar3 + 0x1e);
      UpdateGoods__12CmdEquipmentFscc
                (param_1,0,(char)*(undefined2 *)(iVar3 + 0x22),(char)*(undefined2 *)(iVar3 + 0x16));
      uVar5 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x98),0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x98),param_1,uVar5,0);
      if (*(int *)(*(int *)(param_1 + 0x98) + 0x44) == 0) {
        uVar6 = 0;
      }
      else {
        uVar6 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x98) + 0xb2) & 0x3ff) >> 2;
      }
      SetButtonReport__12CmdEquipmentFss(param_1,uVar6,*(undefined2 *)((int)uVar5 + 0x16));
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar2 = PTR_SelectEquipment__12CmdEquipmentFv_0050d410;
      uVar7 = DAT_0050d40c;
      *(undefined4 *)(param_1 + 0x7c) = _6047;
      *(undefined4 *)(param_1 + 0x80) = uVar7;
      *(undefined **)(param_1 + 0x84) = puVar2;
      uVar7 = 2;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar7,0,0);
  }
  return 0;
}

/* JP: 0x0044e400  CmdEquipment::SelectEquipment()   [SelectEquipment__12CmdEquipmentFv]  size=0x3d0 */
undefined8 SelectEquipment__12CmdEquipmentFv(int param_1)

{
  ushort uVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  int iVar8;
  undefined4 uVar9;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar8 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if (((uVar1 & 0x2000) == 0) && ((uVar1 & 0x4000) == 0)) {
    if ((uVar1 & 0x1000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar8 != iVar5) {
        Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x98),param_1,iVar5,iVar8);
        if (*(int *)(*(int *)(param_1 + 0x98) + 0x44) == 0) {
          uVar7 = 0;
        }
        else {
          uVar7 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x98) + 0xb2) & 0x3ff) >> 2;
        }
        SetButtonReport__12CmdEquipmentFss(param_1,uVar7,*(undefined2 *)(iVar5 + 0x16));
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      StartExplain__12CmdEquipmentFs(param_1,1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
    }
  }
  else {
    uVar9 = 3;
    if ((uVar1 & 0x2000) != 0) {
      piVar2 = *(int **)(param_1 + 0x70);
      *(char *)(*piVar2 + (int)*(short *)(*(int *)(param_1 + 0x94) + 0x16) + 0x2d) =
           (char)*(undefined2 *)(iVar8 + 0x16);
      FlushParameter__5CmdPCFP8ECResult(piVar2,0);
      UpdateSlot__12CmdEquipmentFss(param_1,0,0);
      uVar9 = 0x1004;
    }
    Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x98),param_1,0,iVar8);
    uVar6 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x94),0,
                            *(undefined2 *)(*(int *)(param_1 + 0x94) + 0x16));
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x94),param_1,uVar6,0);
    iVar8 = (int)uVar6;
    UpdateGoods__12CmdEquipmentFscc
              (param_1,0,(char)*(undefined2 *)(iVar8 + 0x22),(char)*(undefined2 *)(iVar8 + 0x16));
    UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,0,0);
    UpdateStatus__12CmdEquipmentFsP11CmdPCStatus(param_1,0,0);
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    SetButtonReport__12CmdEquipmentFss(param_1,0,*(undefined2 *)(iVar8 + 0x16));
    puVar4 = PTR_SelectSlot__12CmdEquipmentFv_0050d430;
    uVar3 = DAT_0050d42c;
    *(undefined4 *)(param_1 + 0x7c) = _6133;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar9,0,0);
  }
  return 0;
}

/* JP: 0x0044e7d0  CmdEquipment::ShiftExplain()   [ShiftExplain__12CmdEquipmentFv]  size=0x198 */
undefined8 ShiftExplain__12CmdEquipmentFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  undefined *puVar5;
  
  puVar5 = PTR_SelectSlot__12CmdEquipmentFv_0050d460;
  uVar4 = DAT_0050d45c;
  puVar3 = PTR_SelectEquipment__12CmdEquipmentFv_0050d450;
  uVar2 = DAT_0050d44c;
  if ((*(char *)(*(int *)(param_1 + 0x98) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x98) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x98) + 0xa8) == '\0') {
      SetExplanation__12CmdEquipmentFv(param_1);
      puVar3 = PTR_ExecExplain__12CmdEquipmentFv_0050d440;
      uVar2 = DAT_0050d43c;
      *(undefined4 *)(param_1 + 0x7c) = _6198;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    else if (*(short *)(*(int *)(param_1 + 0x98) + 0xae) == 0) {
      *(undefined4 *)(param_1 + 0x7c) = _6206;
      *(undefined4 *)(param_1 + 0x80) = uVar4;
      *(undefined **)(param_1 + 0x84) = puVar5;
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    }
    else {
      *(undefined4 *)(param_1 + 0x7c) = _6203;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x0044e970  CmdEquipment::ExecExplain()   [ExecExplain__12CmdEquipmentFv]  size=0x3b0 */
undefined8 ExecExplain__12CmdEquipmentFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  byte bVar4;
  long lVar5;
  
  lVar5 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0xa0),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if ((lVar5 != 0) && ((int)lVar5 == 4)) {
    if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0xa0) + 0x525) << 0x3d) < 0) {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      if (*(short *)(*(int *)(param_1 + 0x98) + 0xae) == 0) {
        Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x94),param_1,uVar1,0);
      }
      else {
        FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x98));
        Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x98),param_1,uVar1,0);
      }
      QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
      iVar2 = *(int *)(param_1 + 0x8c);
      Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
      iVar2 = *(int *)(param_1 + 0x90);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
      iVar2 = *(int *)(param_1 + 0x78);
      Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
      iVar2 = *(int *)(param_1 + 0x9c);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      iVar2 = *(int *)(param_1 + 0x94);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      iVar2 = *(int *)(param_1 + 0x98);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      (**(code **)(*(int *)(*(int *)(param_1 + 0xa0) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0xa0) = 0;
      puVar3 = PTR_ShiftExplain__12CmdEquipmentFv_0050d470;
      uVar1 = DAT_0050d46c;
      *(undefined4 *)(param_1 + 0x7c) = _6239;
      *(undefined4 *)(param_1 + 0x80) = uVar1;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
    else {
      bVar4 = *(byte *)(*(int *)(param_1 + 0xa0) + 0x524) >> 4;
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),bVar4);
      if (*(short *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16) < 0) {
        MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),bVar4);
      }
      SetExplanation__12CmdEquipmentFv(param_1);
    }
  }
  return 0;
}
