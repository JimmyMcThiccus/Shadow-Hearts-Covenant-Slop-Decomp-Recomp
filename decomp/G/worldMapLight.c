/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: worldMapLight   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/worldMapLight.md).
 */

/* JP: 0x0050be50  worldMapLight::worldMapLight()   [__ct__13worldMapLightFv]  size=0x9c */
int __ct__13worldMapLightFv(int param_1)

{
  int iVar1;
  
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__13worldMapLight;
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    *(undefined4 *)(param_1 + iVar1 * 4 + 100) = 0;
    *(undefined4 *)(param_1 + iVar1 * 4 + 0x74) = 0;
  }
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  return param_1;
}

/* JP: 0x0050bef0  worldMapLight::~worldMapLight()   [__dt__13worldMapLightFv]  size=0x94 */
int __dt__13worldMapLightFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__13worldMapLight;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    mReleasePoint__13worldMapLightFv(param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0050bf90  worldMapLight::initialize(primLayer*, int, int)   [initialize__13worldMapLightFP9primLayerii]  size=0x8c */
void initialize__13worldMapLightFP9primLayerii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  *(undefined4 *)(param_1 + 0x34) = param_3;
  *(undefined4 *)(param_1 + 0x38) = param_4;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 *)(param_1 + 0x30) = 0;
  select__13worldMapLightFv(param_1);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x0050c020  worldMapLight::setDest(float, float)   [setDest__13worldMapLightFff]  size=0xac */
void setDest__13worldMapLightFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  unselect__13worldMapLightFv(param_3);
  *(undefined4 *)(param_3 + 0x54) = 0x18;
  *(undefined4 *)(param_3 + 0x44) = param_1;
  *(undefined4 *)(param_3 + 0x48) = param_2;
  *(float *)(param_3 + 0x4c) = (*(float *)(param_3 + 0x44) - *(float *)(param_3 + 0x3c)) / 24.0;
  *(float *)(param_3 + 0x50) = (*(float *)(param_3 + 0x48) - *(float *)(param_3 + 0x40)) / 24.0;
  return;
}

/* JP: 0x0050c0d0  worldMapLight::setPos(float, float)   [setPos__13worldMapLightFff]  size=0x1a0 */
void setPos__13worldMapLightFff(float param_1,float param_2,int param_3)

{
  int iVar1;
  
  *(float *)(param_3 + 0x3c) = param_1;
  *(float *)(param_3 + 0x40) = param_2;
  if (*(int *)(param_3 + 0x60) != 0) {
    setPos__10primPacketFff(param_1,param_2,*(undefined4 *)(param_3 + 0x60));
    for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
      setPos__10primPacketFff(param_1,param_2,*(undefined4 *)(param_3 + iVar1 * 4 + 100));
    }
    setPos__10primPacketFff(0,(param_2 - 216.0) - 256.0,*(undefined4 *)(param_3 + 0x74));
    setPos__10primPacketFff(0,param_2 + 216.0,*(undefined4 *)(param_3 + 0x78));
    setPos__10primPacketFff((param_1 - 216.0) - 256.0,param_2 - 216.0,*(undefined4 *)(param_3 + 0x7c));
    setPos__10primPacketFff(param_1 + 216.0,param_2 - 216.0,*(undefined4 *)(param_3 + 0x80));
  }
  return;
}

/* JP: 0x0050c270  worldMapLight::select()   [select__13worldMapLightFv]  size=0x4dc */
void select__13worldMapLightFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  *(undefined4 *)(param_1 + 0x18) = 2;
  if (*(int *)(param_1 + 0x60) == 0) {
    lVar2 = __nw__FUi(0x150);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primSpriteFb(lVar2,1);
    }
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    setDisp__10primPacketFP9primLayeriffff(*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(param_1 + 0x40),0x3f800000,
                    0x3f800000,*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(param_1 + 0x5c),
                    *(undefined4 *)(param_1 + 0x34));
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x60),0,0,0x10,0x10);
    setSize__10primPacketFii(*(undefined4 *)(param_1 + 0x60),0x10,0x10);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x60),0x7f,0x7f,0x7f,0x40);
    setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + 0x60),1);
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + 0x60),2);
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      lVar2 = __nw__FUi(0x150);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__10primSpriteFb(lVar2,1);
      }
      *(undefined4 *)(param_1 + iVar3 * 4 + 100) = uVar1;
      setDisp__10primPacketFP9primLayeriffff(*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(param_1 + 0x40),0x3f800000,
                      0x3f800000,*(undefined4 *)(param_1 + iVar3 * 4 + 100),
                      *(undefined4 *)(param_1 + 0x5c),*(undefined4 *)(param_1 + 0x38));
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 100),0x7f,0x7f,0x7f,0x80);
    }
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + 100),4);
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + 0x68),1);
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + 0x6c),3);
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x68),0xd7,1,0,0xd8);
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x6c),1,0xd7,0xd8,0);
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x70),0xd7,0xd7,0,0);
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      lVar2 = __nw__FUi(0x150);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__10primSpriteFb(lVar2,0);
      }
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x74) = uVar1;
      setDisp__10primPacketFP9primLayeriffff(0,0,0x3f800000,0x3f800000,*(undefined4 *)(param_1 + iVar3 * 4 + 0x74),
                      *(undefined4 *)(param_1 + 0x5c),*(undefined4 *)(param_1 + 0x38));
      setSize__10primPacketFii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x74),0x200,0x100);
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x74),0,0,0,0x80);
    }
    setPos__10primPacketFff(0,(*(float *)(param_1 + 0x40) - 216.0) - 256.0,*(undefined4 *)(param_1 + 0x74));
    setPos__10primPacketFff(0,*(float *)(param_1 + 0x40) + 216.0,*(undefined4 *)(param_1 + 0x78));
    setPos__10primPacketFff((*(float *)(param_1 + 0x3c) - 216.0) - 256.0,*(float *)(param_1 + 0x40) - 216.0,
                    *(undefined4 *)(param_1 + 0x7c));
    setSize__10primPacketFii(*(undefined4 *)(param_1 + 0x7c),0x100,0x1b0);
    setPos__10primPacketFff(*(float *)(param_1 + 0x3c) + 216.0,*(float *)(param_1 + 0x40) - 216.0,
                    *(undefined4 *)(param_1 + 0x80));
    setSize__10primPacketFii(*(undefined4 *)(param_1 + 0x80),0x100,0x1b0);
  }
  return;
}

/* JP: 0x0050c750  worldMapLight::unselect()   [unselect__13worldMapLightFv]  size=0x54 */
void unselect__13worldMapLightFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x18) = 3;
  if (0x80 < *(int *)(param_1 + 0x1c)) {
    *(int *)(param_1 + 0x1c) = 0x80 - (*(int *)(param_1 + 0x1c) + -0x80);
  }
  return;
}

/* JP: 0x0050c7b0  worldMapLight::mReleasePoint()   [mReleasePoint__13worldMapLightFv]  size=0xf0 */
void mReleasePoint__13worldMapLightFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x60) != 0) {
    DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x60));
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    if (*(int *)(param_1 + iVar1 * 4 + 100) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + iVar1 * 4 + 100));
      *(undefined4 *)(param_1 + iVar1 * 4 + 100) = 0;
    }
    if (*(int *)(param_1 + iVar1 * 4 + 0x74) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + iVar1 * 4 + 0x74));
      *(undefined4 *)(param_1 + iVar1 * 4 + 0x74) = 0;
    }
  }
  return;
}

/* JP: 0x0050c8a0  worldMapLight::Polling()   [Polling__13worldMapLightFv]  size=0x3f0 */
undefined8 Polling__13worldMapLightFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x60) != 0) {
    if (*(int *)(param_1 + 0x54) != 0) {
      *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + -1;
      if (*(int *)(param_1 + 0x54) == 0) {
        *(undefined4 *)(param_1 + 0x18) = 2;
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x44);
        *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x48);
      }
      else {
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x4c);
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x50);
      }
      setPos__13worldMapLightFff
                (*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(param_1 + 0x40),param_1);
    }
    if (*(int *)(param_1 + 0x18) == 3) {
      if ((0 < *(int *)(param_1 + 0x58)) &&
         (*(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -4, *(int *)(param_1 + 0x58) < 1)) {
        *(undefined4 *)(param_1 + 0x58) = 0;
        *(undefined4 *)(param_1 + 0x1c) = 0;
        *(undefined4 *)(param_1 + 0x18) = 0;
      }
      iVar1 = *(int *)(param_1 + 0x58);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x60),0x7f,0x7f,0x7f,iVar1 >> 2);
      for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
        setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar1 * 4 + 100),0x7f,0x7f,0x7f,
                        0x80 - *(int *)(param_1 + 0x58));
        setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar1 * 4 + 0x74),0,0,0,
                        0x80 - *(int *)(param_1 + 0x58));
      }
    }
    else if (*(int *)(param_1 + 0x18) == 2) {
      if (*(int *)(param_1 + 0x1c) < 0x40) {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 2;
        *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
      }
      else if (*(int *)(param_1 + 0x1c) < 0xc0) {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
        if ((*(uint *)(param_1 + 0x1c) & 3) == 0) {
          *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
        }
      }
      else if (*(int *)(param_1 + 0x1c) < 0x140) {
        *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
        if ((*(uint *)(param_1 + 0x1c) & 3) == 0) {
          *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + -1;
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x1c) = 0x40;
      }
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x60),0x7f,0x7f,0x7f,*(int *)(param_1 + 0x58) << 1);
      for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
        setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar1 * 4 + 100),0x7f,0x7f,0x7f,
                        0x80 - *(int *)(param_1 + 0x58));
        setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + iVar1 * 4 + 0x74),0,0,0,
                        0x80 - *(int *)(param_1 + 0x58));
      }
    }
  }
  return 0;
}
