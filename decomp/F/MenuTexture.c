/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002676b0  __ct__11MenuTextureFv  size 0xe4
// MenuTexture::MenuTexture()
u32 * __ct__11MenuTextureFv(MenuTexture *this)
{
  *this = 0;
  this[1] = 0;
  this[2] = __vt__17DelayDeleteObject;
  this[2] = __vt__11MenuTexture;
  this[3] = 0;
  this[4] = 0;
  this[5] = 0;
  __ct__12RasterPacketFv(this + 6);
  this->f_e /*u16 **/ = 0;
  *(u8 *)((int)this + 0x3a) = *(u8 *)((int)this + 0x3a) & 0xfe;
  *(u8 *)((int)this + 0x3a) = *(u8 *)((int)this + 0x3a) & 0xfd;
  *(u8 *)((int)this + 0x3a) = *(u8 *)((int)this + 0x3a) & 0xfb;
  *(u8 *)((int)this + 0x3b) = 0;
  return this;
}

// JP: 0x002677a0  __dt__11MenuTextureFv  size 0xa4
// MenuTexture::~MenuTexture()
int __dt__11MenuTextureFv(MenuTexture *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__11MenuTexture;
    Release__11MenuTextureFv(this);
    __dt__12RasterPacketFv(this + 0x18,0xffffffffffffffff);
    if (this != 0) {
      this->f_8 /*u8 **/ = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00267850  ReadBuffer__11MenuTextureFP9BufMemoryi  size 0xf4
// MenuTexture::ReadBuffer(BufMemory*, int)
u64 ReadBuffer__11MenuTextureFP9BufMemoryi(MenuTexture *this,int param_2,u32 param_3)
{
  Create__11MenuTextureFPUc6GS_PSMUii
            (this,*(u32 *)(param_2 + 4),this->f_1c /*u32 **/,
             this->f_18 /*u32 **/,param_3);
  if ((this->f_c /*int **/ != 0) && ((long)((ulong)this->f_3a /*u8 **/ << 0x3e) < 0)) {
    __dt__9BufMemoryFv(this->f_c /*u32 **/,1);
  }
  this->f_c /*int **/ = param_2;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfd | 2;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfb;
  return 0;
}

// JP: 0x00267950  Create__11MenuTextureFP9BufMemory6GS_PSMUiiUc  size 0xc4
// MenuTexture::Create(BufMemory*, GS_PSM, unsigned int, int, unsigned char)
void Create__11MenuTextureFP9BufMemory6GS_PSMUiiUc
               (MenuTexture *this,int param_2,u32 param_3,u32 param_4,u64 param_5,
               u8 param_6)
{
  Create__11MenuTextureFPUc6GS_PSMUii(this,*(u32 *)(param_2 + 4),param_3,param_4,0);
  if ((this->f_c /*int **/ != 0) && ((long)((ulong)this->f_3a /*u8 **/ << 0x3e) < 0)) {
    __dt__9BufMemoryFv(this->f_c /*u32 **/,1);
  }
  this->f_c /*int **/ = param_2;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfd | (param_6 & 1) << 1;
  return;
}

// JP: 0x00267a20  Create__11MenuTextureFPUc6GS_PSMUii  size 0x1ec
// MenuTexture::Create(unsigned char*, GS_PSM, unsigned int, int)
void Create__11MenuTextureFPUc6GS_PSMUii
               (MenuTexture *this,u32 param_2,int param_3,u32 param_4,u32 param_5)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  u32 uStack_30;
  this->f_10 /*u32 **/ = param_2;
  uStack_30 = param_3;
  if (0x2f < param_3) {
    if (*(char *)(this->f_10 /*int **/ + 4) == '\x04') {
      uStack_30 = 0x2c;
    }
    else {
      uStack_30 = 0x1b;
    }
  }
  SetRaster__12RasterPacketF6GS_PSMUiUiUiUi
            (this + 0x18,uStack_30,*this->f_10 /*u16 **/,
             *(u16 *)(this->f_10 /*int **/ + 2),
             this->f_10 /*int **/ + *(int *)(this->f_10 /*int **/ + 8),param_4);
  this->f_1c /*u8 **/ = this->f_1c /*u8 **/ & 0xfb | 4;
  if (*(char *)(this->f_10 /*int **/ + 5) != '\0') {
    if (this->f_14 /*int **/ == 0) {
      lVar3 = __nw__FUi(0x30);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__10ClutRasterFv(lVar3);
      }
      this->f_14 /*u32 **/ = uVar2;
    }
    iVar1 = this->f_10 /*int **/;
    if (*(short *)(iVar1 + 6) == 0x10) {
      uVar2 = 4;
    }
    else {
      uVar2 = 8;
    }
    Create__10ClutRasterFiUiib
              (this->f_14 /*u32 **/,param_5,iVar1 + *(int *)(iVar1 + 0xc),uVar2,0);
  }
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfe | 1;
  return;
}

// JP: 0x00267c10  Release__11MenuTextureFv  size 0x64
// MenuTexture::Release()
void Release__11MenuTextureFv(MenuTexture *this)
{
  Destroy__12RasterPacketFv(this + 0x18);
  if (this->f_14 /*int **/ != 0) {
    __dt__10ClutRasterFv(this->f_14 /*u32 **/,1);
    this->f_14 /*u32 **/ = 0;
  }
  ReleaseBuffer__11MenuTextureFv(this);
  return;
}

// JP: 0x00267c80  ReleaseBuffer__11MenuTextureFv  size 0xb4
// MenuTexture::ReleaseBuffer()
void ReleaseBuffer__11MenuTextureFv(MenuTexture *this)
{
  if (((long)((ulong)this->f_3a /*u8 **/ << 0x3e) < 0) && (this->f_c /*int **/ != 0)) {
    __dt__9BufMemoryFv(this->f_c /*u32 **/,1);
    this->f_c /*u32 **/ = 0;
  }
  this->f_c /*u32 **/ = 0;
  this->f_10 /*u32 **/ = 0;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfe;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfd;
  this->f_38 /*u16 **/ = 0;
  return;
}

// JP: 0x00267d40  OrderFile__11MenuTextureFPCc6GS_PSMUii  size 0xc0
// MenuTexture::OrderFile(const char*, GS_PSM, unsigned int, int)
void OrderFile__11MenuTextureFPCc6GS_PSMUii
               (MenuTexture *this,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)
{
  u8 auStack_150 [256];
  int iStack_50;
  u32 uStack_40;
  u32 uStack_30;
  u32 uStack_20;
  u32 uStack_10;
  this->f_1c /*u32 **/ = param_3;
  this->f_18 /*u32 **/ = param_4;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfe;
  this->f_3a /*u8 **/ = this->f_3a /*u8 **/ & 0xfb | 4;
  iStack_50 = this;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  uStack_10 = param_5;
  SetPathname__7SysToolFPcPCc(auStack_150,param_2);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,auStack_150,0x267e00,uStack_10,iStack_50,0);
  return;
}

// JP: 0x00267e00  ReadFileFunc__11MenuTextureFiP9BufMemoryiPcPv  size 0x38
// MenuTexture::ReadFileFunc(int, BufMemory*, int, char*, void*)
void ReadFileFunc__11MenuTextureFiP9BufMemoryiPcPv
               (MenuTexture *this,u32 param_2,u64 param_3,u64 param_4,
               u32 param_5)
{
  ReadBuffer__11MenuTextureFP9BufMemoryi(param_5,param_2,this);
  return;
}
