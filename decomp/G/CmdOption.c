/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdOption   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdOption.md).
 */

/* JP: 0x00446be0  CmdOption::CmdOption()   [__ct__9CmdOptionFv]  size=0x1b4 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__9CmdOptionFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdOption;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __construct_array(param_1 + 0x68,0x270370,0x2703e0,0xfc,8);
  __ct__10MenuWindowFv(param_1 + 0x848);
  __ct__10MenuWindowFv(param_1 + 0x8fc);
  __ct__8FontDrawFv(param_1 + 0x9b0);
  __ct__8FontDrawFv(param_1 + 0x9f0);
  __construct_array(param_1 + 0xa30,0x27bfd0,0x27c030,0x80,10);
  __construct_array(param_1 + 0xf30,0x446e20,0x446da0,0xe0,0x14);
  __ct__7MenuBarFv(param_1 + 0x20b0);
  __construct_array(param_1 + 0x2118,0x266140,0x2661a0,0x60,10);
  __ct__11MenuTextureFv(param_1 + 0x24e0);
  __ct__11MenuTextureFv(param_1 + 0x2520);
  __ct__11MenuTextureFv(param_1 + 0x2560);
  __ct__11SendOnLocalFv(param_1 + 0x25a0);
  __ct__11SendOnLocalFv(param_1 + 0x25d0);
  __ct__11SendOnLocalFv(param_1 + 0x2600);
  return param_1;
}

/* JP: 0x00446e60  CmdOption::~CmdOption()   [__dt__9CmdOptionFv]  size=0x1cc */
int __dt__9CmdOptionFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdOption;
    __dt__11SendOnLocalFv(param_1 + 0x2600,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x25d0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x25a0,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x2560,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x2520,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x24e0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x2118,0x2661a0,0x60,10);
    __dt__7MenuBarFv(param_1 + 0x20b0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xf30,0x446da0,0xe0,0x14);
    __destroy_arr(param_1 + 0xa30,0x27c030,0x80,10);
    __dt__8FontDrawFv(param_1 + 0x9f0,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x9b0,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x8fc,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x848,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x68,0x2703e0,0xfc,8);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00447030  CmdOption::GetReady()   [GetReady__9CmdOptionFv]  size=0xb20 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 GetReady__9CmdOptionFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  ushort uVar9;
  ushort uVar10;
  short sVar11;
  ushort uVar12;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  int iStack_b4;
  undefined4 uStack_b0;
  undefined4 *puStack_ac;
  int iStack_a8;
  undefined4 uStack_a4;
  undefined4 *puStack_a0;
  int iStack_9c;
  undefined4 uStack_98;
  undefined4 *puStack_94;
  float fStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 *puStack_74;
  undefined4 *puStack_70;
  undefined4 *puStack_6c;
  undefined4 uStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  ushort *puStack_40;
  float fStack_3c;
  float fStack_38;
  int iStack_34;
  int iStack_30;
  short sStack_2a;
  short sStack_28;
  short sStack_26;
  short sStack_24;
  short sStack_22;
  short sStack_20;
  short sStack_1e;
  ushort uStack_1c;
  ushort uStack_1a;
  ushort uStack_18;
  ushort uStack_16;
  ushort uStack_14;
  ushort uStack_12;
  int iStack_10;
  
  uStack_d0 = (undefined4)__4937;
  uStack_cc = (undefined4)((ulong)__4937 >> 0x20);
  uStack_c8 = DAT_0050d2f8;
  uStack_c4 = DAT_0050d2fc;
  uStack_c0 = DAT_0050d300;
  iStack_30 = *(int *)(param_1 + 0x10);
  iStack_54 = iStack_30 + 0xb8;
  iStack_58 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x26c;
  *(int *)(param_1 + 0x2638) = iStack_58;
  iStack_5c = iStack_30 + 0x348;
  iStack_64 = iStack_30 + 0x3a0;
  *(int *)(param_1 + 0x18) = iStack_64;
  uStack_68 = sm_pSound__7MenuObj;
  *(undefined4 *)(param_1 + 100) = sm_pSound__7MenuObj;
  iStack_60 = iStack_64;
  iStack_44 = iStack_5c;
  iStack_34 = iStack_54;
  iStack_10 = param_1;
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x9b0);
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,1,iStack_10 + 0x9f0);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x860,iStack_10 + 0x9b0);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x914,iStack_10 + 0x9f0);
  uStack_14 = 0xfffe;
  *(undefined2 *)(iStack_10 + 0x24da) = 0;
  iVar8 = iStack_10 + 0xa30;
  iVar7 = iStack_10 + 0xf30;
  puStack_40 = (ushort *)(*(int *)(iStack_10 + 0x2638) + 8);
  uVar12 = 1;
  sVar6 = 0;
  fStack_38 = 0.0;
  for (uVar10 = 0; (short)uVar10 < 10; uVar10 = uVar10 + 1) {
    iVar3 = (uint)uVar10 * 0xc + *(int *)(iStack_10 + 0x28);
    puVar4 = (undefined4 *)(iVar3 + 0x10);
    sVar11 = *(short *)(iVar3 + 0x18);
    puStack_6c = puVar4;
    if ((uStack_14 & uVar12) != 0) {
      SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar8);
      *(ushort *)(iVar8 + 0x16) = uVar10;
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(ushort *)(iVar8 + 0x1e) = uVar10;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_38);
      uStack_48 = *puVar4;
      SetMessage__8MenuTextFPcUiUcUc(iVar8,uStack_48,*(byte *)(iVar8 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x9b0,iVar8,((ulong)*(byte *)(iVar8 + 0x58) & 0xf) >> 3,0);
      AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x848,iVar8);
      if (sVar11 != 0) {
        uStack_1c = *(ushort *)(iVar3 + 0x18);
        iVar3 = (uint)uStack_1c * 0xc + *(int *)(iStack_10 + 0x28);
        puVar4 = (undefined4 *)(iVar3 + 0x10);
        uStack_12 = *(ushort *)(iVar3 + 0x18) & 0xf;
        fStack_3c = 0.0;
        puStack_74 = puVar4;
        puStack_70 = puVar4;
        for (uVar9 = 0; (short)uVar9 < (short)uStack_12; uVar9 = uVar9 + 1) {
          uStack_16 = *(short *)(puVar4 + 2) >> 4 & 0xf;
          uStack_18 = *(short *)(puVar4 + 2) >> 9 & 1;
          uStack_1a = (ushort)((int)(uint)*puStack_40 >> (((int)sVar6 & 0xfU) << 1)) & 3;
          SetData__9MenuSceneFUsP10MenuSprite(iStack_10,uStack_16,iVar7);
          fStack_78 = *(float *)(iVar7 + 0x28);
          (**(code **)(*(int *)(iVar7 + 8) + 0x24))(fStack_3c,fStack_38 + fStack_78);
          AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x8fc,iVar7);
          SetData__9MenuSceneFUsP8MenuText(iStack_10,uStack_18,iVar7 + 0x60);
          *(short *)(iVar7 + 0x76) = sVar11;
          *(ushort *)(iVar7 + 0x7c) = uVar9;
          *(ushort *)(iVar7 + 0x7e) = uVar10;
          uStack_4c = *puVar4;
          SetMessage__8MenuTextFPcUiUcUc(iVar7 + 0x60,uStack_4c,*(byte *)(iVar7 + 0xb8) & 7,0,1);
          OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x9f0,iVar7 + 0x60,((ulong)*(byte *)(iVar7 + 0xb8) & 0xf) >> 3
                          ,0);
          fStack_7c = *(float *)(iVar7 + 0x8c);
          fStack_80 = *(float *)(iVar7 + 0x2c);
          (**(code **)(*(int *)(iVar7 + 0x68) + 0x24))
                    (fStack_3c + (fStack_80 - fStack_7c) / 2.0,fStack_38);
          AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x8fc,iVar7 + 0x60);
          if (uStack_1a == uVar9) {
            Select__6CursorFP9MenuPlace(iStack_10 + *(short *)(iStack_10 + 0x24da) * 0xfc + 0x68,iVar7 + 0x60);
            SetCSA__8FontItemFUc(iVar7 + 0x60,1);
          }
          if ((uVar10 == 2) && (uVar9 == 2)) {
            DisableFontItem__8FontItemFv(iVar7 + 0x60);
          }
          fStack_84 = *(float *)(iVar7 + 0x2c);
          fStack_3c = fStack_3c + fStack_84 + 2.0;
          iVar7 = iVar7 + 0xe0;
          sVar11 = sVar11 + 1;
          puVar4 = puVar4 + 3;
        }
        iVar3 = iStack_10 + *(short *)(iStack_10 + 0x24da) * 0xfc;
        iStack_50 = iVar3 + 0x68;
        *(ushort *)(iVar3 + 0x7e) = uVar10;
        *(byte *)(iVar8 + 0x21) = *(byte *)(iVar8 + 0x21) & 0x7f | 0x80;
        sStack_1e = *(short *)(iStack_10 + 0x24da);
        *(short *)(iStack_10 + 0x24da) = sStack_1e + 1;
        *(short *)(iVar8 + 0x22) = sStack_1e;
      }
      iVar8 = iVar8 + 0x80;
    }
    if (sVar11 != 0) {
      sVar6 = sVar6 + 1;
    }
    uVar12 = uVar12 << 1;
    fStack_38 = fStack_38 + 30.0;
  }
  SetData__9MenuSceneFUsP10MenuSprite(iStack_10,8,iStack_10 + 0x20b0);
  SetBar__7MenuBarFv(iStack_10 + 0x20b0);
  SetRange__7MenuBarFii(iStack_10 + 0x20b0,*(undefined1 *)(*(int *)(iStack_10 + 0x2638) + 0xc),10);
  AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x8fc,iStack_10 + 0x20b0);
  fStack_3c = 0.0;
  iVar7 = iStack_10 + 0x2118;
  for (sVar6 = 0; sVar6 < 10; sVar6 = sVar6 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(iStack_10,*(undefined2 *)((int)&uStack_d0 + sVar6 * 2),iVar7);
    uStack_88 = *(undefined4 *)(iVar7 + 0x28);
    fStack_8c = *(float *)(iVar7 + 0x24);
    (**(code **)(*(int *)(iVar7 + 8) + 0x24))(fStack_3c + fStack_8c,uStack_88);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x8fc,iVar7);
    fStack_90 = *(float *)(iVar7 + 0x2c);
    fStack_3c = fStack_3c + fStack_90;
    iVar7 = iVar7 + 0x60;
  }
  puStack_94 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c);
  Create__11MenuTextureFPUc6GS_PSMUii(iStack_10 + 0x24e0,*puStack_94,0x30,0,0);
  uStack_98 = *(undefined4 *)(iStack_10 + 0x24f4);
  iStack_9c = iStack_10 + 0x24f8;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_10 + 0x25a0,iStack_9c,uStack_98,1,0xffffffffffffffff);
  sStack_26 = *(short *)(iStack_10 + 0x20c4);
  sStack_20 = sStack_26 + -1;
  *(short *)(iStack_10 + 0x25b4) = sStack_20;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x914,iStack_10 + 0x25a0);
  puStack_a0 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x34);
  Create__11MenuTextureFPUc6GS_PSMUii(iStack_10 + 0x2520,*puStack_a0,0x30,0,0);
  uStack_a4 = *(undefined4 *)(iStack_10 + 0x2534);
  iStack_a8 = iStack_10 + 0x2538;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_10 + 0x25d0,iStack_a8,uStack_a4,1,0xffffffffffffffff);
  sStack_28 = *(short *)(iStack_10 + 0x212c);
  sStack_22 = sStack_28 + -1;
  *(short *)(iStack_10 + 0x25e4) = sStack_22;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x914,iStack_10 + 0x25d0);
  puStack_ac = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28);
  Create__11MenuTextureFPUc6GS_PSMUii(iStack_10 + 0x2560,*puStack_ac,0x30,0,0);
  uStack_b0 = *(undefined4 *)(iStack_10 + 0x2574);
  iStack_b4 = iStack_10 + 0x2578;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_10 + 0x2600,iStack_b4,uStack_b0,1,0xffffffffffffffff);
  sStack_2a = *(short *)(iStack_10 + 0xf44);
  sStack_24 = sStack_2a + -1;
  *(short *)(iStack_10 + 0x2614) = sStack_24;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x914,iStack_10 + 0x2600);
  DisableFontItem__8FontItemFv(iStack_10 + 0xc30);
  DisableFontItem__8FontItemFv(iStack_10 + 0xe30);
  if ((*(byte *)(*(int *)(iStack_34 + 4) + 3) & 1) == 0) {
    DisableFontItem__8FontItemFv(iStack_10 + 0xdb0);
  }
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_10 + 0x848);
  uVar5 = SetData__9MenuSceneFUsP10MenuWindow(iStack_10,1,iStack_10 + 0x8fc);
  AddOT__7MenuObjFv(iStack_10 + 0x848,uVar5);
  AddOT__7MenuObjFv(iStack_10 + 0x8fc);
  puVar2 = PTR_Enter__9CmdOptionFv_0050d310;
  uVar1 = DAT_0050d30c;
  *(undefined4 *)(iStack_10 + 0x58) = _4970;
  *(undefined4 *)(iStack_10 + 0x5c) = uVar1;
  *(undefined **)(iStack_10 + 0x60) = puVar2;
  *(undefined2 *)(iStack_10 + 0x24d8) = 0;
  return 1;
}

/* JP: 0x00447b50  CmdOption::Run()   [Run__9CmdOptionFv]  size=0x5c */
undefined8 Run__9CmdOptionFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x58);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x00447bb0  CmdOption::Enter()   [Enter__9CmdOptionFv]  size=0x374 */
undefined4 Enter__9CmdOptionFv(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined1 uVar6;
  long lVar7;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(char *)(param_1 + 0x21) == '\0') {
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),param_1 + 0xa30);
    *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) = *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xfb;
    SetCSA__8FontItemFUc(param_1 + 0xa30,1);
    SetNote__9CmdOptionFv(param_1);
    if (-1 < (long)((ulong)*(byte *)(*(int *)(param_1 + 0x18) + 0x12) << 0x3d)) {
      AddOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x18));
      QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    }
    Open__10MenuWindowFUci(param_1 + 0x848,*(byte *)(param_1 + 0x8f8) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x87c) + 0x10));
    Open__10MenuWindowFUci(param_1 + 0x8fc,*(byte *)(param_1 + 0x9ac) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x930) + 0x10));
    SetTitle__11CmdTitleLogFPUci(iVar1 + 0x780,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),8);
    Open__11CmdTitleLogFv(iVar1 + 0x780);
    lVar7 = GetScene__4MenuFs(*(undefined4 *)(param_1 + 0x10),0);
    if ((lVar7 != 0) && (*(char *)(*(int *)((int)lVar7 + 100) + 0xa8) == '\0')) {
      iVar2 = *(int *)((int)lVar7 + 100);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
    }
    uVar6 = CreateBackGround__7CmdMenuFs(iVar1,9);
    *(undefined1 *)(param_1 + 0x20) = uVar6;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x8f0) == '\x01') || (*(char *)(param_1 + 0x8f0) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(iVar1,1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xfb | 4;
      puVar5 = PTR_Exec__9CmdOptionFv_0050d320;
      uVar4 = DAT_0050d31c;
      *(undefined4 *)(param_1 + 0x58) = _5086;
      *(undefined4 *)(param_1 + 0x5c) = uVar4;
      *(undefined **)(param_1 + 0x60) = puVar5;
      *(undefined1 *)(param_1 + 0x21) = 0;
      return 1;
    }
  }
  return 0;
}

/* JP: 0x00447f30  CmdOption::Exit()   [Exit__9CmdOptionFv]  size=0x490 */
undefined8 Exit__9CmdOptionFv(int param_1)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  bool bVar4;
  uint uVar5;
  uint uVar6;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x24d8),0,0x13);
    Close__10MenuWindowFUci(param_1 + 0x848,((ulong)*(byte *)(param_1 + 0x8f8) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x87c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x8fc,((ulong)*(byte *)(param_1 + 0x9ac) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x930) + 0x14));
    iVar2 = *(int *)(param_1 + 0x10);
    Close__10MenuWindowFUci(iVar2 + 0x7d8,((ulong)*(byte *)(iVar2 + 0x888) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar2 + 0x80c) + 0x14));
    uVar6 = param_1 + 0x68;
    uVar5 = uVar6 + *(short *)(param_1 + 0x24da) * 0xfc;
    for (; uVar6 < uVar5; uVar6 = uVar6 + 0xfc) {
      sVar1 = *(short *)(*(int *)(uVar6 + 0xec) + 0x1c);
      bVar3 = (byte)sVar1;
      switch(*(undefined2 *)(uVar6 + 0x16)) {
      case 1:
        *(byte *)(*(int *)(param_1 + 0x2638) + 8) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 8) & 0xfc | bVar3 & 3;
        break;
      case 2:
        *(byte *)(*(int *)(param_1 + 0x2638) + 8) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 8) & 0xf3 | (byte)(((int)sVar1 & 3U) << 2);
        break;
      case 4:
        *(byte *)(*(int *)(param_1 + 0x2638) + 8) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 8) & 0xcf | (byte)(((int)sVar1 & 3U) << 4);
        break;
      case 5:
        *(byte *)(*(int *)(param_1 + 0x2638) + 8) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 8) & 0x3f | (byte)(((int)sVar1 & 3U) << 6);
        break;
      case 6:
        *(byte *)(*(int *)(param_1 + 0x2638) + 9) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 9) & 0xfc | bVar3 & 3;
        break;
      case 7:
        *(byte *)(*(int *)(param_1 + 0x2638) + 9) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 9) & 0xf3 | (byte)(((int)sVar1 & 3U) << 2);
        break;
      case 8:
        *(byte *)(*(int *)(param_1 + 0x2638) + 9) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 9) & 0xcf | (byte)(((int)sVar1 & 3U) << 4);
        *(byte *)(*(int *)(param_1 + 0x2638) + 10) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 10) & 0xfc | (bVar3 ^ 1) & 3;
        break;
      case 9:
        *(byte *)(*(int *)(param_1 + 0x2638) + 9) =
             *(byte *)(*(int *)(param_1 + 0x2638) + 9) & 0x3f | (byte)(((int)sVar1 & 3U) << 6);
      }
    }
    UpdateVibration__15SaveMenuSectionFv();
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x8f0) == '\x01') || (*(char *)(param_1 + 0x8f0) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      ReleaseOT__7MenuObjFv(param_1 + 0x848);
      ReleaseOT__7MenuObjFv(param_1 + 0x8fc);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))
                (*(int *)(param_1 + 0x10),*(undefined2 *)(param_1 + 0x24d8));
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x004483c0  CmdOption::Exec()   [Exec__9CmdOptionFv]  size=0x5d8 */
/* WARNING: Removing unreachable block (ram,0x004486f8) */

undefined8 Exec__9CmdOptionFv(int param_1)

{
  char cVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  long lVar8;
  char cVar9;
  
  puVar6 = PTR_Exit__9CmdOptionFv_0050d340;
  uVar5 = DAT_0050d33c;
  uVar3 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar4 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  sVar2 = *(short *)(iVar4 + 0x16);
  if (((uVar3 & 0x2000) == 0) || (sVar2 != 0)) {
    if ((uVar3 & 0x4000) == 0) {
      iVar7 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar4 == iVar7) {
        if (sVar2 == 3) {
          cVar1 = *(char *)(*(int *)(param_1 + 0x2638) + 0xc);
          if ((uVar3 & 0x20) == 0) {
            cVar9 = cVar1;
            if (((uVar3 & 0x80) != 0) && (cVar9 = cVar1 + -1, cVar1 == '\x01')) {
              cVar9 = '\x01';
            }
          }
          else {
            cVar9 = cVar1 + '\x01';
            if (10 < (byte)(cVar1 + 1U)) {
              cVar9 = '\n';
            }
          }
          if (cVar1 != cVar9) {
            SetRange__7MenuBarFii(param_1 + 0x20b0,cVar9,10);
            *(char *)(*(int *)(param_1 + 0x2638) + 0xc) = cVar9;
            SetBright__4CAppFf((float)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x278) * 0.03 + 0.7,
                            app__4CApp);
            PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),1,0,0);
          }
        }
        else if ((long)((ulong)*(byte *)(iVar4 + 0x21) << 0x38) < 0) {
          iVar7 = param_1 + *(short *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x22) * 0xfc;
          iVar4 = *(int *)(iVar7 + 0x154);
          if ((uVar3 & 0x20) == 0) {
            if ((uVar3 & 0x80) != 0) {
              MoveCursor__6CursorFi(iVar7 + 0x68,4);
            }
          }
          else {
            MoveCursor__6CursorFi(iVar7 + 0x68,8);
          }
          iVar7 = *(int *)(iVar7 + 0x154);
          if (iVar4 != iVar7) {
            if (iVar4 != 0) {
              SetCSA__8FontItemFUc(iVar4,0);
            }
            if (iVar7 != 0) {
              SetCSA__8FontItemFUc(iVar7,1);
            }
            SetExplanation__7CmdNoteFPCce
                      (*(int *)(param_1 + 0x10) + 0x4e0,
                       *(undefined4 *)
                        ((uint)*(ushort *)(iVar7 + 0x16) * 0xc + *(int *)(param_1 + 0x28) + 0x14));
            if (sVar2 == 2) {
              *(byte *)(*(int *)(param_1 + 0x2638) + 8) =
                   *(byte *)(*(int *)(param_1 + 0x2638) + 8) & 0xf3 |
                   (byte)(((int)*(short *)(iVar7 + 0x1c) & 3U) << 2);
              UpdateSoundOut__15SaveMenuSectionFv();
            }
            PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),1,0,0);
          }
        }
      }
      else {
        if (iVar4 != 0) {
          SetCSA__8FontItemFUc(iVar4,0);
        }
        if (iVar7 != 0) {
          SetCSA__8FontItemFUc(iVar7,1);
        }
        SetNote__9CmdOptionFv(param_1);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5204;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar6;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    lVar8 = GetScene__4MenuFs(*(undefined4 *)(param_1 + 0x10),0);
    if (lVar8 != 0) {
      iVar4 = *(int *)((int)lVar8 + 100);
      Close__10MenuWindowFUci(iVar4,((ulong)*(byte *)(iVar4 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x14));
    }
    *(undefined2 *)(param_1 + 0x24d8) = 0x11;
    puVar6 = PTR_Exit__9CmdOptionFv_0050d330;
    uVar5 = DAT_0050d32c;
    *(undefined4 *)(param_1 + 0x58) = _5199;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined **)(param_1 + 0x60) = puVar6;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x004489a0  CmdOption::SetNote()   [SetNote__9CmdOptionFv]  size=0x19c */
void SetNote__9CmdOptionFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x10) + 0x4e0;
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((long)((ulong)*(byte *)(iVar1 + 0x21) << 0x38) < 0) {
    SetExplanation__7CmdNoteFPCce
              (iVar2,*(undefined4 *)
                      ((uint)*(ushort *)
                              (*(int *)(param_1 + *(short *)(iVar1 + 0x22) * 0xfc + 0x154) + 0x16) *
                       0xc + *(int *)(param_1 + 0x28) + 0x14));
  }
  else {
    SetExplanation__7CmdNoteFPCce
              (iVar2,*(undefined4 *)
                      ((uint)*(ushort *)(iVar1 + 0x16) * 0xc + *(int *)(param_1 + 0x28) + 0x14));
  }
  return;
}
