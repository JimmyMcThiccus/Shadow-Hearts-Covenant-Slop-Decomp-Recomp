/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FaceImage   functions: 11
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FaceImage.md).
 */

/* JP: 0x004a0440  FaceImage::FaceImage()   [__ct__9FaceImageFv]  size=0x10c */
int __ct__9FaceImageFv(int param_1)

{
  int iVar1;
  long lVar2;
  
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__9FaceImage;
  lVar2 = __nw__FUi(0x184);
  iVar1 = 0;
  if (lVar2 != 0) {
    iVar1 = __ct__13FaceImageDataFv(lVar2);
  }
  *(int *)(param_1 + 0x18) = iVar1;
  *(undefined1 *)(iVar1 + 0xc) = 0;
  *(undefined1 *)(iVar1 + 0xd) = 1;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  Create__11MenuPolygonFUcUc(iVar1 + 0xfc,1,1);
  *(undefined2 *)(iVar1 + 0x110) = 1;
  AddPlace__10MenuWindowFP9MenuPlace(iVar1 + 0x18,iVar1 + 0xfc);
  AddPriority__12MenuObjTableFP7MenuObj(iVar1 + 0x30,iVar1 + 0xcc);
  Create__10MenuWindowFUcUcffff(0,0,0,0,iVar1 + 0x18,0,0);
  *(undefined2 *)(iVar1 + 0x2c) = 0x10;
  *(undefined1 **)(iVar1 + 0x180) = &sm_menuRender__7MenuObj;
  *(undefined2 *)(iVar1 + 0xe) = 0;
  return param_1;
}

/* JP: 0x004a0550  FaceImage::~FaceImage()   [__dt__9FaceImageFv]  size=0xc0 */
int __dt__9FaceImageFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__9FaceImage;
    iVar1 = *(int *)(param_1 + 0x18);
    Release__9FaceImageFv(param_1);
    if (*(short *)(iVar1 + 0xe) != 0) {
      Dispose__10MenuRenderFv(*(undefined4 *)(iVar1 + 0x180));
    }
    (**(code **)(*(int *)(iVar1 + 8) + 0xc))();
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004a0610  FaceImage::Create(int)   [Create__9FaceImageFi]  size=0xb8 */
undefined4 Create__9FaceImageFi(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (*(int *)(iVar1 + 0x14) != 0) {
    Release__9FaceImageFv(param_1);
  }
  uVar2 = GetHandle__11FileManegerFib(sm_pFace__7MenuObj,param_2,0);
  *(undefined4 *)(iVar1 + 0x14) = uVar2;
  if (*(int *)(*(int *)(iVar1 + 0x14) + 0x14) == 0) {
    *(undefined1 *)(iVar1 + 0xc) = 2;
  }
  else {
    CreateImage__9FaceImageFv(param_1);
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return 1;
}

/* JP: 0x004a06d0  FaceImage::Release()   [Release__9FaceImageFv]  size=0x58 */
void Release__9FaceImageFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0x180) + 0x2c,iVar1 + 0x18);
  Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  *(undefined4 *)(iVar1 + 0x14) = 0;
  return;
}

/* JP: 0x004a0730  FaceImage::Open(unsigned char, int)   [Open__9FaceImageFUci]  size=0xbc */
undefined4 Open__9FaceImageFUci(int param_1,byte param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (*(char *)(iVar1 + 0xc) == '\0') {
    uVar2 = 0;
  }
  else {
    *(byte *)(iVar1 + 200) = *(byte *)(iVar1 + 200) & 0xf8 | param_2 & 7;
    *(undefined4 *)(iVar1 + 0x10) = param_3;
    if (*(char *)(iVar1 + 0xc) == '\x01') {
      ShiftState__9FaceImageFs(param_1,3);
    }
    else {
      *(undefined1 *)(iVar1 + 0xd) = 3;
    }
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a07f0  FaceImage::Close(unsigned char, int)   [Close__9FaceImageFUci]  size=0xbc */
undefined4 Close__9FaceImageFUci(int param_1,byte param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (*(char *)(iVar1 + 0xc) == '\0') {
    uVar2 = 0;
  }
  else {
    *(byte *)(iVar1 + 200) = *(byte *)(iVar1 + 200) & 199 | (param_2 & 7) << 3;
    *(undefined4 *)(iVar1 + 0x10) = param_3;
    if (*(char *)(iVar1 + 0xc) == '\x01') {
      ShiftState__9FaceImageFs(param_1,4);
    }
    else {
      *(undefined1 *)(iVar1 + 0xd) = 4;
    }
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004a08b0  FaceImage::Polling()   [Polling__9FaceImageFv]  size=0x108 */
undefined8 Polling__9FaceImageFv(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *(int *)(param_1 + 0x18);
  cVar1 = *(char *)(iVar2 + 0xc);
  if ((cVar1 == '\x04') || (cVar1 == '\x03')) {
    if ((*(char *)(iVar2 + 0xc0) == '\x01') || (*(char *)(iVar2 + 0xc0) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      ShiftState__9FaceImageFs(param_1,*(undefined1 *)(iVar2 + 0xd));
    }
  }
  else if ((cVar1 == '\x02') && (*(int *)(*(int *)(iVar2 + 0x14) + 0x14) != 0)) {
    CreateImage__9FaceImageFv(param_1);
  }
  return 0;
}

/* JP: 0x004a09c0  FaceImage::CreateImage()   [CreateImage__9FaceImageFv]  size=0x114 */
void CreateImage__9FaceImageFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iVar1 + 0xcc,*(int *)(iVar1 + 0x14) + 0x38,
                  *(undefined4 *)(*(int *)(iVar1 + 0x14) + 0x34),1,0xffffffffffffffff);
  SetUV__11MenuPolygonFUsUsUsUs(iVar1 + 0xfc,0,0,0x66,0x80);
  (**(code **)(*(int *)(iVar1 + 0x104) + 0x28))(0x42cc0000,0x43000000);
  *(byte *)(iVar1 + 0x2a) = *(byte *)(iVar1 + 0x2a) & 0xfe;
  AddPriority__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0x180) + 0x2c,iVar1 + 0x18);
  ShiftState__9FaceImageFs(param_1,*(undefined1 *)(iVar1 + 0xd));
  return;
}

/* JP: 0x004a0ae0  FaceImage::ShiftState(short)   [ShiftState__9FaceImageFs]  size=0xcc */
void ShiftState__9FaceImageFs(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (param_2 == 4) {
    Close__10MenuWindowFUci(iVar1 + 0x18,((ulong)*(byte *)(iVar1 + 200) & 0x3f) >> 3,
                    *(undefined4 *)(iVar1 + 0x10));
  }
  else if (param_2 == 3) {
    Open__10MenuWindowFUci(iVar1 + 0x18,*(byte *)(iVar1 + 200) & 7,*(undefined4 *)(iVar1 + 0x10));
  }
  *(char *)(iVar1 + 0xc) = (char)param_2;
  *(undefined1 *)(iVar1 + 0xd) = 1;
  return;
}

/* JP: 0x004b5a50  FaceImage::SetSize(float, float)   [SetSize__9FaceImageFff]  size=0x64 */
void SetSize__9FaceImageFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*(int *)(*(int *)(param_3 + 0x18) + 0x104) + 0x28))(param_1,param_2);
  SetSize__10MenuWindowFff(param_1,param_2,*(int *)(param_3 + 0x18) + 0x18);
  return;
}

/* JP: 0x004b5bc0  FaceImage::SetPosition(float, float)   [SetPosition__9FaceImageFff]  size=0x40 */
void SetPosition__9FaceImageFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  SetPosition__10MenuWindowFff(param_1,param_2,*(int *)(param_3 + 0x18) + 0x18);
  return;
}
