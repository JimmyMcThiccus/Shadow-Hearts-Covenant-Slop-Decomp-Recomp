/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboKeyGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboKeyGoods.md).
 */

/* JP: 0x00489f90  CmdComboKeyGoods::CmdComboKeyGoods()   [__ct__16CmdComboKeyGoodsFv]  size=0x84 */
int __ct__16CmdComboKeyGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdComboKeyGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x409134;
  *(undefined4 *)(param_1 + 0x24) = 0x409140;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xe4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x0048a020  CmdComboKeyGoods::~CmdComboKeyGoods()   [__dt__16CmdComboKeyGoodsFv]  size=0xe4 */
int __dt__16CmdComboKeyGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdComboKeyGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x409134;
    *(undefined4 *)(param_1 + 0x24) = 0x409140;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x488700);
    }
    __dt__8FontDrawFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048a110  CmdComboKeyGoods::CreateScene(CmdComboKey*)   [CreateScene__16CmdComboKeyGoodsFP11CmdComboKey]  size=0x2b8 */
void CreateScene__16CmdComboKeyGoodsFP11CmdComboKey(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  undefined8 uVar3;
  short sVar4;
  float fStack_28;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xe4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xe4);
  sVar1 = *(short *)(param_2 + 0xcb6);
  uVar3 = __nwa__FUi((sVar1 * 0x70 - (int)sVar1) * 4 + 0x10);
  iVar2 = __construct_new_array(uVar3,0x4887a0,0x488700,0x1bc,sVar1);
  *(int *)(param_1 + 0x124) = iVar2;
  fStack_28 = 0.0;
  for (sVar4 = 0; sVar4 < sVar1; sVar4 = sVar4 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,3,iVar2 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,4,iVar2 + 0xd0);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,5,iVar2 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar4;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(0,fStack_28);
    fStack_28 = fStack_28 + *(float *)(iVar2 + 0x30);
    iVar2 = iVar2 + 0x1bc;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb4,0x4216f0,uRam004216ec,1,6);
  *(short *)(param_1 + 200) = *(short *)(*(int *)(param_1 + 0x124) + 0x164) + -1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0x124) + 0x1bc);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,3,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0048a3d0  CmdComboKeyGoods::UpdateScene(CmdComboKey*, short)   [UpdateScene__16CmdComboKeyGoodsFP11CmdComboKeys]  size=0x40c */
void UpdateScene__16CmdComboKeyGoodsFP11CmdComboKeys(int param_1,int param_2,short param_3)

{
  short sVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  char *pcVar5;
  char cVar6;
  undefined1 auStack_58 [12];
  undefined4 uStack_4c;
  int iStack_44;
  undefined4 uStack_40;
  char cStack_3c;
  char cStack_3b;
  short sStack_3a;
  short sStack_38;
  short sStack_36;
  short sStack_34;
  short sStack_32;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  ClearPlace__10MenuWindowFv(param_1);
  iStack_44 = *(int *)(iStack_30 + 0x44);
  *(byte *)(iStack_44 + 0x12) = *(byte *)(iStack_44 + 0x12) & 0xfe;
  if (-1 < sStack_10) {
    sVar1 = *(short *)(iStack_20 + 0xcb8);
    uStack_4c = *(undefined4 *)(iStack_20 + 0xcb0);
    iVar2 = *(int *)(iStack_20 + 0x5c);
    uStack_40 = uStack_4c;
    sStack_38 = sVar1;
    sStack_32 = GetComboKeyCount__8CmdPartyFss(iVar2,sStack_10,sVar1);
    pcVar5 = (char *)(*(int *)(iVar2 + 4) + sVar1 * 0x10 + 0xf44 +
                     (*(short *)(iStack_20 + 0x136) + -1) * 4);
    cStack_3c = (char)sStack_10;
    iVar4 = *(int *)(iStack_30 + 0x124);
    for (sStack_3a = 0; sStack_3a < sStack_32; sStack_3a = sStack_3a + 1) {
      lVar3 = GetComboKeyData__8CmdPartyFsP15SHORTCUTCommandPcP15CmdComboKeyData
                        (iVar2,sVar1,&cStack_3c,uStack_40,iVar4 + 0x1b0);
      if (lVar3 != 0) {
        if (sStack_10 == 1) {
          memcpy(auStack_58,iVar4 + 0x1b0,0xc);
          for (cVar6 = '\0'; cVar6 < '\x04'; cVar6 = cVar6 + '\x01') {
            if (((cStack_3c != *pcVar5) || (sStack_3a != *(short *)(pcVar5 + 2))) ||
               (cStack_3b != cVar6)) {
              memcpy(iVar4 + 0x1b0,auStack_58,0xc);
              *(short *)(iVar4 + 0x1ba) = (short)cVar6;
              SetComboKeyGoods__11CmdComboKeyFsP16CmdGoodsComboKey(iStack_20,sStack_10,iVar4);
              sStack_34 = sStack_3a;
              *(short *)(iVar4 + 0x16) = sStack_3a;
              AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar4);
              iVar4 = iVar4 + 0x1bc;
            }
          }
        }
        else if ((cStack_3c != *pcVar5) || (sStack_3a != *(short *)(pcVar5 + 2))) {
          SetComboKeyGoods__11CmdComboKeyFsP16CmdGoodsComboKey(iStack_20,sStack_10,iVar4);
          sStack_36 = sStack_3a;
          *(short *)(iVar4 + 0x16) = sStack_3a;
          AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar4);
          iVar4 = iVar4 + 0x1bc;
        }
      }
    }
    AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xe4);
    AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xb4);
    *(int *)(*(int *)(iStack_30 + 0x40) + 0x38) = iStack_30 + 0xe4;
    SetScroll__10MenuWindowFss(iStack_30,0,0);
    *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) =
         *(byte *)(*(int *)(iStack_30 + 0x44) + 0x12) & 0xfe | 1;
  }
  return;
}

/* JP: 0x0048a7e0  CmdComboKeyGoods::Select(CmdComboKey*, MenuPlace*, MenuPlace*)   [Select__16CmdComboKeyGoodsFP11CmdComboKeyP9MenuPlaceP9MenuPlace]  size=0x130 */
void Select__16CmdComboKeyGoodsFP11CmdComboKeyP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_4 != 0) {
    iVar1 = *(int *)(param_1 + 0x124) +
            (*(short *)(param_4 + 0x1e) * 0x70 - (int)*(short *)(param_4 + 0x1e)) * 4;
    SetCSA__8FontItemFUc(iVar1 + 0x50,0);
    SetCSA__8FontItemFUc(iVar1 + 0xd0,0);
  }
  if (param_3 != 0) {
    iVar1 = *(int *)(param_1 + 0x124) +
            (*(short *)(param_3 + 0x1e) * 0x70 - (int)*(short *)(param_3 + 0x1e)) * 4;
    SetCSA__8FontItemFUc(iVar1 + 0x50,1);
    SetCSA__8FontItemFUc(iVar1 + 0xd0,1);
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_2 + 100),*(undefined4 *)(iVar1 + 0x1b4));
  }
  return;
}

/* JP: 0x0048a910  CmdComboKeyGoods::~CmdComboKeyGoods()   [@24@__dt__16CmdComboKeyGoodsFv]  size=0x8 */
undefined4 * _24___dt__16CmdComboKeyGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdComboKeyGoods;
    *param_1 = 0x409134;
    param_1[3] = 0x409140;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x488700);
    }
    __dt__8FontDrawFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0048a920  CmdComboKeyGoods::~CmdComboKeyGoods()   [@36@__dt__16CmdComboKeyGoodsFv]  size=0x8 */
undefined4 * _36___dt__16CmdComboKeyGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdComboKeyGoods;
    param_1[-3] = 0x409134;
    *param_1 = 0x409140;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x488700);
    }
    __dt__8FontDrawFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
