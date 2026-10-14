/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomHitArea   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomHitArea.md).
 */

/* JP: 0x0046b880  CmdRingCustomHitArea::CmdRingCustomHitArea()   [__ct__20CmdRingCustomHitAreaFv]  size=0xac */
int __ct__20CmdRingCustomHitAreaFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__20CmdRingCustomHitArea;
  *(undefined4 *)(param_1 + 0x18) = 0x4088c4;
  *(undefined4 *)(param_1 + 0x24) = 0x4088d0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x454640,0x450670,0x150,10);
  __ct__10ScrollMarkFv(param_1 + 0xe14);
  *(undefined4 *)(param_1 + 0xe98) = 0;
  return param_1;
}

/* JP: 0x0046b930  CmdRingCustomHitArea::~CmdRingCustomHitArea()   [__dt__20CmdRingCustomHitAreaFv]  size=0xdc */
int __dt__20CmdRingCustomHitAreaFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__20CmdRingCustomHitArea;
    *(undefined4 *)(param_1 + 0x18) = 0x4088c4;
    *(undefined4 *)(param_1 + 0x24) = 0x4088d0;
    __dt__10ScrollMarkFv(param_1 + 0xe14,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xf4,0x450670,0x150,10);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0046ba10  CmdRingCustomHitArea::CreateScene(CmdRingCustom*)   [CreateScene__20CmdRingCustomHitAreaFP13CmdRingCustom]  size=0x24c */
void CreateScene__20CmdRingCustomHitAreaFP13CmdRingCustom(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort uVar4;
  
  iVar3 = param_1 + 0xf4;
  for (uVar4 = 0; (short)uVar4 < 10; uVar4 = uVar4 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar3 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar3 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0xd0);
    SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,
                    *(undefined4 *)
                     (((int)(short)uVar4 + 5U & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                    *(byte *)(iVar3 + 0xa8) & 7,0,0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar3);
    iVar2 = (int)(short)uVar4;
    if ((short)uVar4 < 0) {
      iVar2 = iVar2 + 1;
    }
    *(short *)(iVar3 + 0x16) = (short)(iVar2 >> 1);
    uVar1 = uVar4 & 1;
    if (((short)uVar4 < 0) && (uVar1 != 0)) {
      uVar1 = uVar1 - 2;
    }
    *(ushort *)(iVar3 + 0x22) = uVar1;
    iVar3 = iVar3 + 0x150;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  Create__10ScrollMarkFUcP10MenuWindowUc(param_1 + 0xe14,0xc,param_1,1);
  *(undefined2 *)(param_1 + 0x110) = 0;
  *(undefined2 *)(param_1 + 0x112) = 1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xb4;
  SetScroll__10MenuWindowFss(param_1,0,0);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0046bc60  CmdRingCustomHitArea::UpdateScene(CmdRingCustom*)   [UpdateScene__20CmdRingCustomHitAreaFP13CmdRingCustom]  size=0x450 */
void UpdateScene__20CmdRingCustomHitAreaFP13CmdRingCustom(int param_1,int param_2)

{
  bool bVar1;
  short sVar2;
  ushort uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  short sVar8;
  uint uVar9;
  undefined1 auStack_50 [8];
  float fStack_48;
  undefined4 uStack_44;
  float fStack_40;
  undefined4 uStack_3c;
  byte *pbStack_38;
  byte *pbStack_34;
  int *piStack_30;
  float fStack_2c;
  ushort uStack_28;
  ushort uStack_26;
  ushort uStack_24;
  byte bStack_22;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  piStack_30 = *(int **)(param_2 + 0x70);
  pbVar4 = (byte *)(*piStack_30 + 0x5a);
  pbVar5 = (byte *)(*piStack_30 + 0x5f);
  uStack_26 = (ushort)(((ulong)*(byte *)(*piStack_30 + 0x58) << 0x3a) >> 0x3d);
  uVar9 = (uint)uStack_26;
  uStack_28 = (ushort)(((ulong)*(byte *)(*piStack_30 + 0x58) << 0x3a) >> 0x3d);
  *(undefined4 *)(param_1 + 0xe98) = 0;
  bStack_21 = *(byte *)(*piStack_30 + 0x58) >> 6;
  uStack_24 = uStack_28;
  if (bStack_21 == 3) {
    uStack_24 = 1;
    *(undefined4 *)(param_1 + 0xe98) = 1;
    *(undefined2 *)(param_1 + 0xe9c) = 0;
    *(undefined2 *)(param_1 + 0xe9c) = 0;
  }
  bStack_22 = *(byte *)(*piStack_30 + 0x58) >> 6;
  bVar1 = bStack_22 != 1;
  pbStack_38 = pbVar5;
  pbStack_34 = pbVar4;
  iStack_20 = param_1;
  iStack_10 = param_2;
  ClearPlace__10MenuWindowFv(param_1);
  fStack_2c = 0.0;
  sVar8 = 0;
  iVar6 = iStack_20 + 0xf4;
  for (uVar7 = 0; uVar7 < uStack_24; uVar7 = uVar7 + 1 & 0xffff) {
    uVar3 = (ushort)*pbVar4;
    if (*(int *)(iStack_20 + 0xe98) != 0) {
      for (uVar7 = 1; uVar7 < uVar9; uVar7 = uVar7 + 1 & 0xffff) {
        uVar3 = uVar3 + pbVar4[uVar7];
      }
    }
    uStack_3c = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x48);
    sprintf(auStack_50,uStack_3c,uVar3);
    SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0xd0,auStack_50,*(byte *)(iVar6 + 0x128) & 7,1,0);
    *(undefined2 *)(iVar6 + 0x1c) = 0;
    *(short *)(iVar6 + 0x1e) = sVar8;
    (**(code **)(*(int *)(iVar6 + 8) + 0x24))(0,fStack_2c);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar6);
    fStack_40 = *(float *)(iVar6 + 0x30);
    fStack_2c = fStack_2c + fStack_40;
    sVar2 = sVar8 + 1;
    if (bVar1) {
      uVar3 = (ushort)*pbVar5;
      if (*(int *)(iStack_20 + 0xe98) != 0) {
        for (uVar7 = 1; uVar7 < uVar9; uVar7 = uVar7 + 1 & 0xffff) {
          uVar3 = uVar3 + pbVar5[uVar7];
        }
      }
      uStack_44 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x48);
      sprintf(auStack_50,uStack_44,uVar3);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x220,auStack_50,*(byte *)(iVar6 + 0x278) & 7,1,0);
      *(undefined2 *)(iVar6 + 0x16c) = 0;
      *(short *)(iVar6 + 0x16e) = sVar8 + 1;
      (**(code **)(*(int *)(iVar6 + 0x158) + 0x24))(0,fStack_2c);
      AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar6 + 0x150);
      fStack_48 = *(float *)(iVar6 + 0x180);
      fStack_2c = fStack_2c + fStack_48;
      sVar2 = sVar8 + 2;
    }
    sVar8 = sVar2;
    iVar6 = iVar6 + 0x2a0;
    pbVar4 = pbVar4 + 1;
    pbVar5 = pbVar5 + 1;
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xe14);
  *(byte *)(iStack_20 + 0xe26) = *(byte *)(iStack_20 + 0xe26) & 0xfe;
  *(int *)(*(int *)(iStack_20 + 0x40) + 0x38) = iStack_20 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_20,0,0);
  return;
}

/* JP: 0x0046c0b0  CmdRingCustomHitArea::Select(CmdRingCustom*, MenuPlace*, MenuPlace*)   [Select__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaceP9MenuPlace]  size=0x2dc */
void Select__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  short sVar5;
  
  uVar2 = *(undefined4 *)(param_2 + 0x88);
  if (param_4 != 0) {
    sVar5 = *(short *)(param_4 + 0x16);
    iVar4 = param_1 + (sVar5 * 2 + (int)*(short *)(param_4 + 0x22)) * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x144,0);
    SetCSA__8FontItemFUc(iVar4 + 0x1c4,0);
    if (*(int *)(param_1 + 0xe98) != 0) {
      sVar5 = -1;
    }
    SetAreaBlink__5JRingFiii(uVar2,sVar5,0,0);
    *(byte *)(param_1 + 0xe26) = *(byte *)(param_1 + 0xe26) & 0xfe;
  }
  if (param_3 != 0) {
    sVar5 = *(short *)(param_3 + 0x16);
    sVar1 = *(short *)(param_3 + 0x22);
    sVar3 = sVar1 + sVar5 * 2;
    iVar4 = param_1 + sVar3 * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x144,1);
    SetCSA__8FontItemFUc(iVar4 + 0x1c4,1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 100),
               *(undefined4 *)(((int)sVar3 + 5U & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x14));
    Custom__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaces(param_1,param_2,param_3,0);
    *(byte *)(param_1 + 0xe26) = *(byte *)(param_1 + 0xe26) & 0xfe | 1;
    if (*(int *)(param_1 + 0xe98) != 0) {
      sVar5 = -1;
    }
    SetAreaBlink__5JRingFiii(uVar2,sVar5,sVar1 + 1,0);
  }
  return;
}

/* JP: 0x0046c390  CmdRingCustomHitArea::Custom(CmdRingCustom*, MenuPlace*, short)   [Custom__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaces]  size=0x6f4 */
void Custom__20CmdRingCustomHitAreaFP13CmdRingCustomP9MenuPlaces
               (int param_1,int param_2,int param_3,short param_4)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  long lVar5;
  ulong uVar6;
  short sVar7;
  byte *pbVar8;
  short sVar9;
  short sVar10;
  ushort uVar11;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fStack_9c;
  undefined1 auStack_88 [8];
  float fStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  byte *pbStack_74;
  byte *pbStack_70;
  undefined4 uStack_6c;
  int *piStack_68;
  undefined4 uStack_64;
  int iStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  ushort uStack_52;
  short sStack_50;
  short sStack_4e;
  ushort uStack_4c;
  ushort uStack_4a;
  ushort uStack_48;
  short sStack_46;
  byte bStack_43;
  byte bStack_42;
  byte bStack_41;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  bStack_42 = 0;
  uStack_64 = *(undefined4 *)(param_2 + 0x5c);
  piVar2 = *(int **)(param_2 + 0x70);
  uStack_6c = *(undefined4 *)(param_2 + 0x88);
  sStack_4e = *(short *)(param_3 + 0x16);
  sVar1 = *(short *)(param_3 + 0x22);
  uVar11 = (ushort)(((ulong)*(byte *)(*piVar2 + 0x58) << 0x3a) >> 0x3d);
  iVar3 = param_1 + ((int)sVar1 + sStack_4e * 2) * 0x150;
  pbStack_70 = (byte *)(*piVar2 + 0x5a);
  pbVar4 = pbStack_70;
  if (sVar1 != 0) {
    pbVar4 = (byte *)(*piVar2 + 0x5f);
    pbStack_74 = pbVar4;
  }
  piStack_68 = piVar2;
  uStack_5c = uStack_6c;
  uStack_58 = uStack_64;
  uStack_52 = uVar11;
  sStack_50 = sVar1;
  sStack_46 = sStack_4e;
  iStack_40 = param_1;
  iStack_30 = param_2;
  iStack_20 = param_3;
  sStack_10 = param_4;
  uStack_48 = GetRestRingItem__8CmdPartyFs(uStack_64,sVar1 + 1);
  uStack_48 = uStack_48 & 0xff;
  if (*(int *)(iStack_40 + 0xe98) == 0) {
    uVar11 = 1;
    uStack_4c = (ushort)pbVar4[sStack_46];
    sVar7 = sStack_46;
  }
  else {
    sVar7 = *(short *)(iStack_40 + sVar1 * 2 + 0xe9c);
    uStack_4c = 0;
    pbVar8 = pbVar4;
    for (sVar10 = 0; sVar10 < (short)uVar11; sVar10 = sVar10 + 1) {
      uStack_4c = uStack_4c + *pbVar8;
      pbVar8 = pbVar8 + 1;
    }
  }
  sVar10 = sVar7;
  for (sVar9 = 0; sVar9 < (short)uVar11; sVar9 = sVar9 + 1) {
    pbVar8 = pbVar4 + sVar10;
    bStack_41 = *pbVar8;
    if (sStack_10 != 0) {
      if (sStack_10 < 0) {
        uStack_4a = (ushort)*pbVar8;
      }
      else {
        uStack_4a = uStack_48;
      }
      if (uStack_4a != 0) {
        *pbVar8 = *pbVar8 + (char)sStack_10;
        lVar5 = CustomJudgmentRing__5CmdPCFP5JRingi(piVar2,uStack_5c,0);
        if (lVar5 == 0) {
          *pbVar8 = *pbVar8 - (char)sStack_10;
        }
        else {
          uStack_48 = uStack_48 - sStack_10;
        }
      }
    }
    sVar10 = sVar10 + sStack_10;
    if (sVar10 < (short)uVar11) {
      if (sVar10 < 0) {
        sVar10 = uVar11 - 1;
      }
    }
    else {
      sVar10 = 0;
    }
    if (bStack_41 != *pbVar8) {
      uStack_78 = *(undefined4 *)(*(int *)(iStack_30 + 0x24) + 0x48);
      sprintf(auStack_88,uStack_78,(int)(short)uStack_4c + (int)sStack_10);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x1c4,auStack_88,*(byte *)(iVar3 + 0x21c) & 7,1,0);
      AllotPacket__10MenuWindowFv(iStack_40);
      break;
    }
  }
  *(short *)(iStack_40 + sVar1 * 2 + 0xe9c) = sVar10;
  sVar10 = sVar7;
  for (sVar9 = 0; sVar9 < (short)uVar11; sVar9 = sVar9 + 1) {
    if (pbVar4[sVar10] != 0) {
      bStack_42 = bStack_42 | 4;
      break;
    }
    sVar10 = sVar10 + 1;
    if ((short)uVar11 <= sVar10) {
      sVar10 = 0;
    }
  }
  if (uStack_48 != 0) {
    for (sVar10 = 0; sVar10 < (short)uVar11; sVar10 = sVar10 + 1) {
      pbVar8 = pbVar4 + sVar7;
      *pbVar8 = *pbVar8 + 1;
      iStack_60 = CustomJudgmentRing__5CmdPCFP5JRingi(piVar2,uStack_5c,1);
      *pbVar8 = *pbVar8 - 1;
      if (iStack_60 != 0) {
        bStack_42 = bStack_42 | 8;
        break;
      }
      sVar7 = sVar7 + 1;
      if ((short)uVar11 <= sVar7) {
        sVar7 = 0;
      }
    }
  }
  uVar12 = *(undefined4 *)(iVar3 + 0x1e8);
  fStack_80 = *(float *)(iVar3 + 0x11c);
  fVar13 = fStack_9c + fStack_80;
  uStack_7c = uVar12;
  uVar6 = GetRealHeight__8FontItemCFv(iVar3 + 0x1c4);
  if ((long)uVar6 < 0) {
    fVar14 = (float)(uVar6 & 0xffffffff);
  }
  else {
    fVar14 = (float)(int)uVar6;
  }
  SetMark__10ScrollMarkFUc(iStack_40 + 0xe14,bStack_42);
  bStack_43 = *(byte *)(iStack_40 + 0xe97) & 0xf;
  SetArea__10ScrollMarkFUcffff(uVar12,fVar13,0x42000000,fVar14,iStack_40 + 0xe14,bStack_43);
  if (*(int *)(iStack_40 + 0xe98) != 0) {
    sStack_46 = -1;
  }
  SetAreaBlink__5JRingFiii(uStack_5c,sStack_46,sVar1 + 1,0);
  return;
}

/* JP: 0x0046ca90  CmdRingCustomHitArea::~CmdRingCustomHitArea()   [@24@__dt__20CmdRingCustomHitAreaFv]  size=0x8 */
undefined4 * _24___dt__20CmdRingCustomHitAreaFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__20CmdRingCustomHitArea;
    *param_1 = 0x4088c4;
    param_1[3] = 0x4088d0;
    __dt__10ScrollMarkFv(param_1 + 0x37f,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x37,0x450670,0x150,10);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0046caa0  CmdRingCustomHitArea::~CmdRingCustomHitArea()   [@36@__dt__20CmdRingCustomHitAreaFv]  size=0x8 */
undefined4 * _36___dt__20CmdRingCustomHitAreaFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__20CmdRingCustomHitArea;
    param_1[-3] = 0x4088c4;
    *param_1 = 0x4088d0;
    __dt__10ScrollMarkFv(param_1 + 0x37c,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x34,0x450670,0x150,10);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
