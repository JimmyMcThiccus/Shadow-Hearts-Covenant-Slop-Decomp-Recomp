/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: MenuElement   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/MenuElement.md).
 */

/* JP: 0x00444f80  MenuElement::MenuElement()   [__ct__11MenuElementFv]  size=0x128 */
int __ct__11MenuElementFv(int param_1)

{
  __ct__9MenuPlaceFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11MenuElement;
  __construct_array(param_1 + 0x40,0x2676b0,0x2677a0,0x40,2);
  __construct_array(param_1 + 0xc0,0x2676b0,0x2677a0,0x40,2);
  __construct_array(param_1 + 0x140,0x2676b0,0x2677a0,0x40,2);
  __ct__11SendOnLocalFv(param_1 + 0x1c0);
  __ct__11SendOnLocalFv(param_1 + 0x1f0);
  __ct__11SendOnLocalFv(param_1 + 0x220);
  __ct__10MenuSpriteFv(param_1 + 0x250);
  __ct__11MenuPolygonFv(param_1 + 0x2b0);
  __ct__10MenuSpriteFv(param_1 + 0x334);
  (**(code **)(*(int *)(param_1 + 8) + 0x20))();
  return param_1;
}

/* JP: 0x004450b0  MenuElement::~MenuElement()   [__dt__11MenuElementFv]  size=0x15c */
int __dt__11MenuElementFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11MenuElement;
    (**(code **)(*(int *)(param_1 + 8) + 0x1c))();
    __dt__10MenuSpriteFv(param_1 + 0x334,0xffffffffffffffff);
    __dt__11MenuPolygonFv(param_1 + 0x2b0,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x250,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x220,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x1f0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x1c0,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x140,0x2677a0,0x40,2);
    __destroy_arr(param_1 + 0xc0,0x2677a0,0x40,2);
    __destroy_arr(param_1 + 0x40,0x2677a0,0x40,2);
    __dt__9MenuPlaceFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00445210  MenuElement::Create(unsigned char*, BufMemory*)   [Create__11MenuElementFPUcP9BufMemory]  size=0x994 */
/* WARNING: Removing unreachable block (ram,0x00445a34) */
/* WARNING: Removing unreachable block (ram,0x00445954) */
/* WARNING: Removing unreachable block (ram,0x00445870) */
/* WARNING: Removing unreachable block (ram,0x004458ac) */
/* WARNING: Removing unreachable block (ram,0x00445990) */
/* WARNING: Removing unreachable block (ram,0x00445a6c) */

undefined4 Create__11MenuElementFPUcP9BufMemory(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  ulong uVar5;
  int iVar6;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x395) << 0x3d) < 0) {
    (**(code **)(*(int *)(param_1 + 8) + 0xc))();
    uVar1 = 1;
  }
  else {
    *(byte *)(param_1 + 0x395) =
         *(byte *)(param_1 + 0x395) & 0xef |
         (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x395) & 0x1f) >> 4) ^ 1) << 4);
    iVar2 = param_1 + (int)((long)((ulong)*(byte *)(param_1 + 0x395) << 0x3b) >> 0x3f) * -0x40;
    iVar6 = param_1 + (int)((long)((ulong)*(byte *)(param_1 + 0x395) << 0x3b) >> 0x3f) * -0x40;
    iVar3 = param_1 + (int)((long)((ulong)*(byte *)(param_1 + 0x395) << 0x3b) >> 0x3f) * -0x40;
    uVar4 = GetFileEntry(param_2,0);
    Create__11MenuTextureFPUc6GS_PSMUii(iVar2 + 0x40,uVar4,0x30,0,0);
    uVar4 = GetFileEntry(param_2,1);
    Create__11MenuTextureFPUc6GS_PSMUii(iVar6 + 0xc0,uVar4,0x30,0,0);
    uVar4 = GetFileEntry(param_2,2);
    Create__11MenuTextureFPUc6GS_PSMUii(iVar3 + 0x140,uVar4,0x30,0,0);
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1c0,iVar2 + 0x58,*(undefined4 *)(iVar2 + 0x54),1,0xffffffffffffffff)
    ;
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1f0,iVar6 + 0xd8,*(undefined4 *)(iVar6 + 0xd4),1,0xffffffffffffffff)
    ;
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x220,iVar3 + 0x158,*(undefined4 *)(iVar3 + 0x154),1,
                    0xffffffffffffffff);
    if (-1 < (long)((ulong)*(byte *)(param_1 + 0x12) << 0x3b)) {
      *(byte *)(param_1 + 0x233) = *(byte *)(param_1 + 0x233) & 0xfb | 4;
      uVar5 = (ulong)*(byte *)(param_1 + 0x231) & 0xfffffffffffffffd | 2;
      *(char *)(param_1 + 0x231) = (char)uVar5;
      *(byte *)(param_1 + 0x230) =
           *(byte *)(param_1 + 0x230) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
      Create__10MenuSpriteFUc(param_1 + 0x250,1);
      *(byte *)(param_1 + 0x271) = *(byte *)(param_1 + 0x271) & 0xbf | 0x40;
      uVar5 = (ulong)*(byte *)(param_1 + 0x261) & 0xfffffffffffffffd | 2;
      *(char *)(param_1 + 0x261) = (char)uVar5;
      *(byte *)(param_1 + 0x260) =
           *(byte *)(param_1 + 0x260) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
      Create__10MenuSpriteFUc(param_1 + 0x334,1);
      *(byte *)(param_1 + 0x355) = *(byte *)(param_1 + 0x355) & 0xbf | 0x40;
      uVar5 = (ulong)*(byte *)(param_1 + 0x345) & 0xfffffffffffffffd | 2;
      *(char *)(param_1 + 0x345) = (char)uVar5;
      *(byte *)(param_1 + 0x344) =
           *(byte *)(param_1 + 0x344) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
      Create__11MenuPolygonFUcUc(param_1 + 0x2b0,1,1);
      (**(code **)(*(int *)(param_1 + 0x2b8) + 0x24))
                (0x41500000,
                 (float)(int)(((uint)*(ushort *)
                                      (*(int *)(param_1 + (int)((long)((ulong)*(byte *)(param_1 +
                                                                                       0x395) <<
                                                                      0x3b) >> 0x3f) * -0x40 + 0x50)
                                      + 2) -
                              (uint)*(ushort *)
                                     (*(int *)(param_1 + (int)((long)((ulong)*(byte *)(param_1 +
                                                                                      0x395) << 0x3b
                                                                     ) >> 0x3f) * -0x40 + 0xd0) + 2)
                              ) + 0xf));
      *(undefined1 *)(param_1 + 0x2ff) = 0;
      uVar5 = (ulong)*(byte *)(param_1 + 0x2c1) & 0xffffffffffffffef | 0x10;
      *(char *)(param_1 + 0x2c1) = (char)uVar5;
      *(byte *)(param_1 + 0x2c0) =
           *(byte *)(param_1 + 0x2c0) & 0xef | (byte)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
      *(undefined1 *)(param_1 + 0x327) = 0x26;
      uVar5 = (ulong)*(byte *)(param_1 + 0x2c1) & 0xffffffffffffffef | 0x10;
      *(char *)(param_1 + 0x2c1) = (char)uVar5;
      *(byte *)(param_1 + 0x2c0) =
           *(byte *)(param_1 + 0x2c0) & 0xef | (byte)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
      *(undefined1 *)(param_1 + 0x32b) = 0;
      uVar5 = (ulong)*(byte *)(param_1 + 0x2c1) & 0xffffffffffffffef | 0x10;
      *(char *)(param_1 + 0x2c1) = (char)uVar5;
      *(byte *)(param_1 + 0x2c0) =
           *(byte *)(param_1 + 0x2c0) & 0xef | (byte)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
      *(undefined1 *)(param_1 + 0x32f) = 0x26;
      uVar5 = (ulong)*(byte *)(param_1 + 0x2c1) & 0xffffffffffffffef | 0x10;
      *(char *)(param_1 + 0x2c1) = (char)uVar5;
      *(byte *)(param_1 + 0x2c0) =
           *(byte *)(param_1 + 0x2c0) & 0xef | (byte)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
      SetBlink__8MenuItemFUcUc(param_1 + 0x334,0x20,0x60);
      *(byte *)(param_1 + 0x12) = *(byte *)(param_1 + 0x12) & 0xef | 0x10;
    }
    (**(code **)(*(int *)(param_1 + 600) + 0x28))
              ((float)**(ushort **)(iVar2 + 0x50),(float)*(ushort *)(*(int *)(iVar2 + 0x50) + 2));
    SetUV__10MenuSpriteFUsUsUsUs(param_1 + 0x250,0,0,**(undefined2 **)(iVar2 + 0x50),
                    *(undefined2 *)(*(int *)(iVar2 + 0x50) + 2));
    (**(code **)(*(int *)(param_1 + 0x33c) + 0x28))
              ((float)**(ushort **)(iVar3 + 0x150),(float)*(ushort *)(*(int *)(iVar3 + 0x150) + 2));
    SetUV__10MenuSpriteFUsUsUsUs(param_1 + 0x334,0,0,**(undefined2 **)(iVar3 + 0x150),
                    *(undefined2 *)(*(int *)(iVar3 + 0x150) + 2));
    (**(code **)(*(int *)(param_1 + 0x2b8) + 0x28))
              ((float)**(ushort **)(iVar6 + 0xd0),(float)*(ushort *)(*(int *)(iVar6 + 0xd0) + 2));
    SetUV__11MenuPolygonFUsUsUsUs(param_1 + 0x2b0,0,0,**(undefined2 **)(iVar6 + 0xd0),
                    *(undefined2 *)(*(int *)(iVar6 + 0xd0) + 2));
    *(undefined4 *)(param_1 + 0x3c) = param_3;
    *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xfe;
    *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) | 0x3f;
    *(byte *)(param_1 + 0x11) = *(byte *)(param_1 + 0x11) | 0x3f;
    uVar5 = (ulong)*(byte *)(param_1 + 0x11) & 0xffffffffffffff7f | 0x80;
    *(char *)(param_1 + 0x11) = (char)uVar5;
    *(byte *)(param_1 + 0x10) =
         *(byte *)(param_1 + 0x10) & 0x7f | (byte)((uint)((uVar5 << 0x38) >> 0x3f) << 7);
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x00445bb0  MenuElement::Polling()   [Polling__11MenuElementFv]  size=0x34 */
void Polling__11MenuElementFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x33c) + 0x10))();
  return;
}

/* JP: 0x00445bf0  MenuElement::Update(int, int, unsigned short)   [Update__11MenuElementFiiUs]  size=0x260 */
void Update__11MenuElementFiiUs
               (int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  byte bVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(param_1 + (m_Env__8VIF1Prim & 1) + 0x10);
  if (*(char *)((m_Env__8VIF1Prim & 1) + param_1 + 0x1d0) != '\0') {
    (**(code **)(*(int *)(param_1 + 0x1c8) + 0x14))(param_1 + 0x1c0,0,0,0);
  }
  if (*(char *)((m_Env__8VIF1Prim & 1) + param_1 + 0x230) != '\0') {
    (**(code **)(*(int *)(param_1 + 0x228) + 0x14))(param_1 + 0x220,0,0,0);
  }
  if (*(char *)((m_Env__8VIF1Prim & 1) + param_1 + 0x200) != '\0') {
    (**(code **)(*(int *)(param_1 + 0x1f8) + 0x14))(param_1 + 0x1f0,0,0,0);
  }
  bVar1 = *pbVar2;
  *(byte *)(param_1 + 0x260) = *(byte *)(param_1 + 0x260) | bVar1;
  *(byte *)(param_1 + 0x261) = *(byte *)(param_1 + 0x261) | bVar1;
  (**(code **)(*(int *)(param_1 + 600) + 0x14))(param_1 + 0x250,param_2,param_3,param_4);
  bVar1 = *pbVar2;
  *(byte *)(param_1 + 0x344) = *(byte *)(param_1 + 0x344) | bVar1;
  *(byte *)(param_1 + 0x345) = *(byte *)(param_1 + 0x345) | bVar1;
  (**(code **)(*(int *)(param_1 + 0x33c) + 0x14))(param_1 + 0x334,param_2,param_3,param_4);
  bVar1 = *pbVar2;
  *(byte *)(param_1 + 0x2c0) = *(byte *)(param_1 + 0x2c0) | bVar1;
  *(byte *)(param_1 + 0x2c1) = *(byte *)(param_1 + 0x2c1) | bVar1;
  (**(code **)(*(int *)(param_1 + 0x2b8) + 0x14))(param_1 + 0x2b0,param_2,param_3,param_4);
  *pbVar2 = *pbVar2 & 0x80;
  return;
}

/* JP: 0x00445e50  MenuElement::Connect(_QWD*)   [Connect__11MenuElementFP4_QWD]  size=0xfc */
undefined4 Connect__11MenuElementFP4_QWD(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uStack_10;
  
  uVar1 = (**(code **)(*(int *)(param_1 + 0x1f8) + 0x18))(param_1 + 0x1f0,param_2);
  uVar1 = (**(code **)(*(int *)(param_1 + 0x2b8) + 0x18))(param_1 + 0x2b0,uVar1);
  uVar1 = (**(code **)(*(int *)(param_1 + 0x1c8) + 0x18))(param_1 + 0x1c0,uVar1);
  uStack_10 = (**(code **)(*(int *)(param_1 + 600) + 0x18))(param_1 + 0x250,uVar1);
  if ((long)((ulong)*(byte *)(param_1 + 0x395) << 0x3c) < 0) {
    uVar1 = (**(code **)(*(int *)(param_1 + 0x228) + 0x18))(param_1 + 0x220,uStack_10);
    uStack_10 = (**(code **)(*(int *)(param_1 + 0x33c) + 0x18))(param_1 + 0x334,uVar1);
  }
  return uStack_10;
}

/* JP: 0x00445f50  MenuElement::Destroy()   [Destroy__11MenuElementFv]  size=0x118 */
void Destroy__11MenuElementFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1);
  if (*(int *)(param_1 + 0x3c) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x3c),1);
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  Release__11MenuTextureFv(param_1 + 0x40);
  Release__11MenuTextureFv(param_1 + 0x80);
  Release__11MenuTextureFv(param_1 + 0x140);
  Release__11MenuTextureFv(param_1 + 0x180);
  Release__11MenuTextureFv(param_1 + 0xc0);
  Release__11MenuTextureFv(param_1 + 0x100);
  Release__7MenuObjFv(param_1 + 0x1c0);
  Release__7MenuObjFv(param_1 + 0x220);
  Release__7MenuObjFv(param_1 + 0x1f0);
  Release__7MenuObjFv(param_1 + 0x250);
  Release__7MenuObjFv(param_1 + 0x334);
  Release__7MenuObjFv(param_1 + 0x2b0);
  return;
}

/* JP: 0x00446070  MenuElement::Clear()   [Clear__11MenuElementFv]  size=0x1b8 */
void Clear__11MenuElementFv(int param_1)

{
  Clear__9MenuPlaceFv(param_1);
  (**(code **)(*(int *)(param_1 + 0x1c8) + 0x20))();
  (**(code **)(*(int *)(param_1 + 0x228) + 0x20))();
  (**(code **)(*(int *)(param_1 + 0x1f8) + 0x20))();
  (**(code **)(*(int *)(param_1 + 600) + 0x20))();
  (**(code **)(*(int *)(param_1 + 0x33c) + 0x20))();
  (**(code **)(*(int *)(param_1 + 0x2b8) + 0x20))();
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(byte *)(param_1 + 0x394) = *(byte *)(param_1 + 0x394) & 0xf;
  *(byte *)(param_1 + 0x394) = *(byte *)(param_1 + 0x394) & 0xf0;
  *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xfb;
  *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xfd;
  *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xfe;
  *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xef;
  *(byte *)(param_1 + 0x395) = *(byte *)(param_1 + 0x395) & 0xf7 | 8;
  return;
}

/* JP: 0x00446230  MenuElement::SetOwner(MenuWindow*)   [SetOwner__11MenuElementFP10MenuWindow]  size=0x74 */
void SetOwner__11MenuElementFP10MenuWindow(int param_1,undefined4 param_2)

{
  (**(code **)(*(int *)(param_1 + 600) + 0x38))(param_1 + 0x250,param_2);
  (**(code **)(*(int *)(param_1 + 0x33c) + 0x38))(param_1 + 0x334,param_2);
  (**(code **)(*(int *)(param_1 + 0x2b8) + 0x38))(param_1 + 0x2b0,param_2);
  return;
}
