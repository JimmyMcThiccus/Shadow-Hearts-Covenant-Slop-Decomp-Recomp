/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: worldMapPoint   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/worldMapPoint.md).
 */

/* JP: 0x0050cc90  worldMapPoint::worldMapPoint()   [__ct__13worldMapPointFv]  size=0x58 */
int __ct__13worldMapPointFv(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0x19; iVar1 = iVar1 + 1) {
    *(undefined4 *)(param_1 + iVar1 * 4 + 0x1c) = 0;
  }
  *(undefined4 *)(param_1 + 4) = 0;
  return param_1;
}

/* JP: 0x0050ccf0  worldMapPoint::~worldMapPoint()   [__dt__13worldMapPointFv]  size=0xc0 */
int __dt__13worldMapPointFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    for (iVar1 = 0; iVar1 < 0x19; iVar1 = iVar1 + 1) {
      if (*(int *)(param_1 + iVar1 * 4 + 0x1c) != 0) {
        DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0x1c));
        *(undefined4 *)(param_1 + iVar1 * 4 + 0x1c) = 0;
      }
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0050cdb0  worldMapPoint::initialize(primLayer*, int, worldMap::SUBMAP_DATA*, int)   [initialize__13worldMapPointFP9primLayeriPQ28worldMap11SUBMAP_DATAi]  size=0x234 */
void initialize__13worldMapPointFP9primLayeriPQ28worldMap11SUBMAP_DATAi
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *(undefined4 *)(param_1 + 4) = param_3;
  *(undefined4 *)(param_1 + 0xc) = param_4;
  *(undefined4 *)(param_1 + 8) = param_5;
  for (iVar3 = 0; iVar3 < *(int *)(param_1 + 4); iVar3 = iVar3 + 1) {
    lVar2 = __nw__FUi(0x150);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primSpriteFb(lVar2,1);
    }
    *(undefined4 *)(param_1 + iVar3 * 4 + 0x1c) = uVar1;
    setDisp__10primPacketFP9primLayeriffff(0,0,0x3f800000,0x3f800000,*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),
                    *(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 8));
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),0x10,1,0x20,0x10);
    setSize__10primPacketFii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),0x10,0x10);
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),2);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),0x7f,0x7f,0x7f,0x40);
    if (*(char *)(*(int *)(param_1 + 0xc) + iVar3 * 0x50 + 0x4b) == '\x03') {
      setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),2);
    }
    else {
      setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c),1);
    }
    setPos__10primPacketFff(0,0,*(undefined4 *)(param_1 + iVar3 * 4 + 0x1c));
  }
  return;
}

/* JP: 0x0050cff0  worldMapPoint::setPos(float, float)   [setPos__13worldMapPointFff]  size=0xe8 */
void setPos__13worldMapPointFff(float param_1,float param_2,int param_3)

{
  int iVar1;
  
  *(float *)(param_3 + 0x10) = param_1;
  *(float *)(param_3 + 0x14) = param_2;
  for (iVar1 = 0; iVar1 < *(int *)(param_3 + 4); iVar1 = iVar1 + 1) {
    setPos__10primPacketFff(param_1 + (float)(int)*(short *)(*(int *)(param_3 + 0xc) + iVar1 * 0x50 + 0x4c),
                    param_2 + (float)(int)*(short *)(*(int *)(param_3 + 0xc) + iVar1 * 0x50 + 0x4e),
                    *(undefined4 *)(param_3 + iVar1 * 4 + 0x1c));
  }
  return;
}
