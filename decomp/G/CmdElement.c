/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdElement   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdElement.md).
 */

/* JP: 0x004462b0  CmdElement::CmdElement()   [__ct__10CmdElementFv]  size=0xdc */
int __ct__10CmdElementFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdElement;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__11MenuTextureFv(param_1 + 0x110);
  __ct__11MenuTextureFv(param_1 + 0x150);
  __ct__11SendOnLocalFv(param_1 + 400);
  __ct__11SendOnLocalFv(param_1 + 0x1c0);
  __ct__11MenuElementFv(param_1 + 0x1f0);
  __ct__10MenuSpriteFv(param_1 + 0x588);
  __construct_array(param_1 + 0x5e8,0x266140,0x2661a0,0x60,2);
  *(undefined4 *)(param_1 + 0x6a8) = 0;
  return param_1;
}

/* JP: 0x00446390  CmdElement::~CmdElement()   [__dt__10CmdElementFv]  size=0x11c */
int __dt__10CmdElementFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdElement;
    __destroy_arr(param_1 + 0x5e8,0x2661a0,0x60,2);
    __dt__10MenuSpriteFv(param_1 + 0x588,0xffffffffffffffff);
    __dt__11MenuElementFv(param_1 + 0x1f0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x1c0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 400,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004464b0  CmdElement::GetReady()   [GetReady__10CmdElementFv]  size=0x2d8 */
undefined4 GetReady__10CmdElementFv(int param_1)

{
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x588);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,1,param_1 + 0x5e8);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,2,param_1 + 0x648);
  SetBlink__8MenuItemFUcUc(param_1 + 0x588,0x20,0);
  SetBlink__8MenuItemFUcUc(param_1 + 0x648,0x20,0);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x150,*(undefined4 *)(*(int *)(param_1 + 0x54) + 100),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x110,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x70),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1c0,param_1 + 0x168,*(undefined4 *)(param_1 + 0x164),1,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 400,param_1 + 0x128,*(undefined4 *)(param_1 + 0x124),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x1d4) = *(short *)(param_1 + 0x59c) + -1;
  *(short *)(param_1 + 0x1a4) = *(short *)(param_1 + 0x5fc) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x1c0);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 400);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x588);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x5e8);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x648);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x1f0);
  (**(code **)(*(int *)(param_1 + 0x1f8) + 0x38))(param_1 + 0x1f0,param_1 + 0x58);
  AddOT__7MenuObjFv(param_1 + 0x58);
  return 1;
}

/* JP: 0x00446790  CmdElement::Release()   [Release__10CmdElementFv]  size=0x48 */
void Release__10CmdElementFv(int param_1)

{
  Release__9MenuSceneFv(param_1);
  Release__7MenuObjFv(param_1 + 0x58);
  Release__7MenuObjFv(param_1 + 0x1f0);
  return;
}

/* JP: 0x004467e0  CmdElement::Create(unsigned char)   [Create__10CmdElementFUc]  size=0x9c */
void Create__10CmdElementFUc(int param_1,byte param_2)

{
  Create__11MenuElementFPUcP9BufMemory
            (param_1 + 0x1f0,*(undefined4 *)((uint)param_2 * 0xc + *(int *)(param_1 + 0x54) + 0x10),
             0);
  SetInfo__10CmdElementFUcP11SendOnLocalP10MenuSpriteP10MenuSprite
            (param_1,param_2,param_1 + 0x1c0,param_1 + 0x588,param_1 + 0x648);
  *(undefined1 *)(param_1 + 0x22) = 1;
  return;
}

/* JP: 0x00446880  CmdElement::SetInfo(unsigned char, SendOnLocal*, MenuSprite*, MenuSprite*)   [SetInfo__10CmdElementFUcP11SendOnLocalP10MenuSpriteP10MenuSprite]  size=0x1d8 */
/* WARNING: Removing unreachable block (ram,0x004469c8) */
/* WARNING: Removing unreachable block (ram,0x004469d0) */

void SetInfo__10CmdElementFUcP11SendOnLocalP10MenuSpriteP10MenuSprite
               (int param_1,byte param_2,int param_3,undefined4 param_4,int param_5)

{
  short sVar1;
  ulong uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  *(ushort *)(param_3 + 0x12) = *(ushort *)(param_3 + 0x12) & 0xfc3f | (param_2 & 0xf) << 6;
  uVar2 = (ulong)*(byte *)(param_3 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(param_3 + 0x11) = (char)uVar2;
  *(byte *)(param_3 + 0x10) =
       *(byte *)(param_3 + 0x10) & 0xfd | (byte)((uint)((uVar2 << 0x3e) >> 0x3f) << 1);
  iVar4 = *(int *)(param_1 + 0x3c);
  sVar1 = *(short *)(iVar4 + 0x2a) * (ushort)param_2;
  SetUV__10MenuSpriteFUsUsUsUs(param_4,*(short *)(iVar4 + 0x28) + sVar1,*(undefined2 *)(iVar4 + 0x2c),
                  *(short *)(iVar4 + 0x2a) + sVar1,*(undefined2 *)(iVar4 + 0x2e));
  iVar4 = (uint)param_2 * 0x10 + 0xf;
  if ((param_2 & 1) == 0) {
    iVar4 = (uint)param_2 * 0x10 + 0x17;
  }
  puVar3 = (undefined1 *)(**(int **)(param_1 + 0x164) + iVar4 * 4);
  (**(code **)(*(int *)(param_5 + 8) + 0x30))(param_5,*puVar3,puVar3[1],puVar3[2]);
  *(undefined1 **)(param_1 + 0x6a8) = puVar3;
  return;
}

/* JP: 0x00446a60  CmdElement::ReCreate(unsigned char)   [ReCreate__10CmdElementFUc]  size=0x90 */
void ReCreate__10CmdElementFUc(int param_1,undefined1 param_2)

{
  Create__10CmdElementFUc(param_1,param_2);
  if (*(char *)(param_1 + 0x100) == '\0') {
    Open__10CmdElementFv(param_1);
  }
  return;
}

/* JP: 0x00446af0  CmdElement::Open()   [Open__10CmdElementFv]  size=0x60 */
void Open__10CmdElementFv(int param_1)

{
  if (*(char *)(param_1 + 0x22) != '\0') {
    *(undefined2 *)(param_1 + 0x104) = 0x8000;
    Open__10MenuWindowFUci(param_1 + 0x58,*(byte *)(param_1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x10));
  }
  return;
}

/* JP: 0x00446b50  CmdElement::Close()   [Close__10CmdElementFv]  size=0x8c */
void Close__10CmdElementFv(int param_1)

{
  if (*(char *)(param_1 + 0x100) != '\0') {
    Close__10MenuWindowFUci(param_1 + 0x58,((ulong)*(byte *)(param_1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x14));
  }
  return;
}
