/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00279320  ReadScene__9MenuSceneFiP9BufMemoryiPcPv  size 0x7c
// MenuScene::ReadScene(int, BufMemory*, int, char*, void*)
void ReadScene__9MenuSceneFiP9BufMemoryiPcPv
               (u64 param_1,u32 param_2,u32 param_3,u64 param_4,
               int this)
{
  u64 uVar1;
  uVar1 = VCALL(this, 0x10 /*Polling*/)(this,param_2,param_3);
  Convert__13MenuDataTableFPUci(uVar1,0);
  Initialize__9MenuSceneFPUcP9BufMemory(this,uVar1,param_2);
  return;
}

// JP: 0x002793a0  __ct__9MenuSceneFv  size 0xac
// MenuScene::MenuScene()
u32 * __ct__9MenuSceneFv(MenuScene *this)
{
  *this = 0;
  this[1] = 0;
  this[2] = __vt__17DelayDeleteObject;
  this[2] = __vt__9MenuScene;
  this[3] = 0;
  this[4] = 0;
  this[5] = 0;
  this->f_7 /*u16 **/ = 0;
  this->vptr = 0;
  *(u8 *)((int)this + 0x21) = 0;
  *(u8 *)((int)this + 0x22) = 0;
  *(u8 *)((int)this + 0x23) = 1;
  memset(this + 9,0,0x34);
  return this;
}

// JP: 0x00279450  __dt__9MenuSceneFv  size 0x94
// MenuScene::~MenuScene()
int __dt__9MenuSceneFv(MenuScene *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__9MenuScene;
    VCALL(this, 0x18 /*Connect*/)();
    if (this != 0) {
      this->vptr = __vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002794f0  OrderFile__9MenuSceneFPCcP4Menu  size 0x7c
// MenuScene::OrderFile(const char*, Menu*)
void OrderFile__9MenuSceneFPCcP4Menu(MenuScene *this,u32 param_2,u32 menu)
{
  char acStack_130 [256];
  int iStack_30;
  u32 uStack_20;
  u32 uStack_10;
  this->menu = menu;
  iStack_30 = this;
  uStack_20 = param_2;
  uStack_10 = menu;
  sprintf(acStack_130,(char *)&_3659,pDataPath__7SysTool,param_2);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,acStack_130,0x279320,0,iStack_30,0);
  return;
}

// JP: 0x00279570  Initialize__9MenuSceneFPUcP9BufMemory  size 0xd4
// MenuScene::Initialize(unsigned char*, BufMemory*)
bool Initialize__9MenuSceneFPUcP9BufMemory(MenuScene *this,short *param_2,u32 param_3)
{
  long lVar1;
  for (; *(short **)(this + *param_2 * 4 + 0x24) = param_2, *(int *)(param_2 + 6) != 0;
      param_2 = (short *)((int)param_2 + *(int *)(param_2 + 6))) {
  }
  this->heap = param_3;
  this->sflags = this->sflags & 0xef | 0x10;
  lVar1 = VCALL(this, 0x14 /*Update*/)();
  if (lVar1 == 0) {
    this->heap = 0;
  }
  return lVar1 == 0;
}

// JP: 0x00279650  MoveVertical__9MenuSceneFi  size 0x178
// MenuScene::MoveVertical(int)
u32 MoveVertical__9MenuSceneFi(MenuScene *this,int param_2)
{
  u16 uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  uVar1 = this->menu->keys;
  iVar2 = this->cursor;
  if ((uVar1 & 0x10) == 0) {
    if ((uVar1 & 0x40) == 0) {
      if (param_2 != 0) {
        iVar3 = *(int *)(*(int *)(iVar2 + 0xec) + 0x18);
        if (*(int *)(iVar3 + 0x44) == 0) {
          uVar4 = 0;
        }
        else {
          uVar4 = ((ulong)*(u16 *)(iVar3 + 0xb2) & 0x3ff) >> 2;
        }
        if (uVar4 != 0) {
          if ((uVar1 & 0x100) == 0) {
            if ((uVar1 & 0x200) != 0) {
              SkipCursor__6CursorFi(iVar2,2);
            }
          }
          else {
            SkipCursor__6CursorFi(iVar2,1);
          }
        }
      }
    }
    else {
      MoveCursor__6CursorFi(iVar2,2);
    }
  }
  else {
    MoveCursor__6CursorFi(iVar2,1);
  }
  return *(u32 *)(iVar2 + 0xec);
}

// JP: 0x002797d0  FindAttachFile__9MenuSceneCFs  size 0xb0
// MenuScene::FindAttachFile(short) const
uint FindAttachFile__9MenuSceneCFs(MenuScene *this,short param_2)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  iVar1 = this->tab_attach;
  if (iVar1 != 0) {
    uVar2 = iVar1 + 0x10;
    uVar3 = uVar2 + *(int *)(iVar1 + 8) * 0xc;
    for (; uVar2 < uVar3; uVar2 = uVar2 + 0xc) {
      if (*(short *)(uVar2 + 4) == param_2) {
        return uVar2;
      }
    }
  }
  return 0;
}

// JP: 0x00279880  SetData__9MenuSceneFUsP8FontDraw  size 0xbc
// MenuScene::SetData(unsigned short, FontDraw*)
u32 SetData__9MenuSceneFUsP8FontDraw(int param_1,u16 param_2,int this)
{
  int iVar1;
  iVar1 = (uint)param_2 * 0x10 + *(int *)(param_1 + 0x2c);
  this->f_16 /*u16 **/ = *(u16 *)(iVar1 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar1 + 0x12);
  Create__8FontDrawF6GS_PSMUsUsUcUiP10ClutRaster
            (this,*(u16 *)(iVar1 + 0x14),*(u16 *)(iVar1 + 0x18),
             *(u16 *)(iVar1 + 0x1a),*(u8 *)(iVar1 + 0x16) & 1,*(u32 *)(iVar1 + 0x1c)
             ,0);
  return 1;
}

// JP: 0x00279940  SetData__9MenuSceneFUsP6Cursor  size 0x1bc
// MenuScene::SetData(unsigned short, Cursor*)
u32 SetData__9MenuSceneFUsP6Cursor(int param_1,u16 param_2,int this)
{
  short sVar1;
  int iVar2;
  ulong uVar3;
  iVar2 = (uint)param_2 * 0xc + *(int *)(param_1 + 0x30);
  this->f_16 /*u16 **/ = *(u16 *)(iVar2 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar2 + 0x12);
  Create__6CursorFUcUcUcUc
            (this,*(u8 *)(iVar2 + 0x18) & 7,((ulong)*(u8 *)(iVar2 + 0x18) & 0x1f) >> 3,
             ((ulong)*(u16 *)(iVar2 + 0x18) & 0x3ff) >> 6,
             ((ulong)*(u8 *)(iVar2 + 0x18) & 0x3f) >> 5);
  this->f_b2 /*u16 **/ =
       this->f_b2 /*u16 **/ & 0xfc3f |
       (u16)((int)(((ulong)*(u8 *)(iVar2 + 0x19) & 0x3f) >> 2) << 6);
  uVar3 = (ulong)this->f_b1 /*u8 **/ & 0xfffffffffffffffd | 2;
  this->f_b1 /*char **/ = (char)uVar3;
  this->f_b0 /*u8 **/ =
       this->f_b0 /*u8 **/ & 0xfd | (u8)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
  sVar1 = *(short *)(iVar2 + 0x16);
  *this->f_d8 /*float **/ = (float)(int)*(short *)(iVar2 + 0x14);
  *(float *)(this->f_d8 /*int **/ + 4) = (float)(int)sVar1;
  SetBackObject__6CursorFUc(this,((ulong)*(u8 *)(iVar2 + 0x19) & 0x7f) >> 6);
  return 1;
}

// JP: 0x00279b00  SetData__9MenuSceneFUsP10MenuWindow  size 0x384
// MenuScene::SetData(unsigned short, MenuWindow*)
/* WARNING: Removing unreachable block (ram,0x00279c98) */
/* WARNING: Removing unreachable block (ram,0x00279cd4) */
u32 SetData__9MenuSceneFUsP10MenuWindow(int param_1,u16 param_2,int this)
{
  u8 bVar1;
  u8 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  u64 uVar6;
  u32 uVar7;
  u32 uVar8;
  iVar5 = (uint)param_2 * 0x1c + *(int *)(param_1 + 0x34);
  this->tab_window = (u16 *)(iVar5 + 0x10);
  this->f_16 /*u16 **/ = *(u16 *)(iVar5 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar5 + 0x12);
  this->f_b0 /*u8 **/ = this->f_b0 /*u8 **/ & 0xf8 | *(u8 *)(iVar5 + 0x28) & 7;
  this->f_b0 /*u8 **/ =
       this->f_b0 /*u8 **/ & 199 |
       (u8)(((ulong)*(u8 *)(iVar5 + 0x28) << 0x3a) >> 0x3d) << 3;
  bVar1 = *(u8 *)(iVar5 + 0x29);
  this->f_b1 /*u8 **/ =
       this->f_b1 /*u8 **/ & 0xf7 |
       (u8)(((ulong)*(u8 *)(iVar5 + 0x29) << 0x3c) >> 0x3f) << 3;
  this->f_b1 /*u8 **/ =
       this->f_b1 /*u8 **/ & 0xef | (u8)(((ulong)bVar1 << 0x3b) >> 0x3f) << 4;
  Create__10MenuWindowFUcUcffff
            ((float)(int)*(short *)(iVar5 + 0x14),(float)(int)*(short *)(iVar5 + 0x16),
             (float)*(u16 *)(iVar5 + 0x18),(float)*(u16 *)(iVar5 + 0x1a),this,
             ((ulong)*(u16 *)(iVar5 + 0x28) & 0x1ff) >> 6,
             ((ulong)*(u8 *)(iVar5 + 0x29) & 7) >> 1);
  if ((long)((ulong)*(u8 *)(iVar5 + 0x29) << 0x39) < 0) {
    uVar2 = *(u8 *)(iVar5 + 0x2a);
    sVar3 = *(short *)(iVar5 + 0x1e);
    sVar4 = *(short *)(iVar5 + 0x1c);
    if (this->tab_group != 0) {
      uVar7 = *(u32 *)(this->tab_group + 0x30);
      uVar8 = *(u32 *)(this->tab_group + 0x2c);
      uVar6 = VCALL(this->tab_group, 0x48 /*GetAllotCount*/)();
      CreateScroll__10MenuWindowFUissffUc(uVar8,uVar7,this,uVar6,sVar4,sVar3,uVar2);
      SetSize__10MenuWindowFff
                ((float)(int)sVar4 * *(float *)(this->tab_group + 0x2c),
                 (float)(int)sVar3 * *(float *)(this->tab_group + 0x30),this);
    }
  }
  this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xfe;
  return 1;
}

// JP: 0x00279e90  SetData__9MenuSceneFUsP9MenuGroup  size 0x1f8
// MenuScene::SetData(unsigned short, MenuGroup*)
u32 SetData__9MenuSceneFUsP9MenuGroup(int param_1,u16 param_2,int this)
{
  u16 uVar1;
  int iVar2;
  ulong uVar3;
  iVar2 = (uint)param_2 * 0x18 + *(int *)(param_1 + 0x38);
  this->f_16 /*u16 **/ = *(u16 *)(iVar2 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar2 + 0x12);
  this->s22 = *(u16 *)(iVar2 + 0x20);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar2 + 0x14),(float)(int)*(short *)(iVar2 + 0x16));
  uVar1 = *(u16 *)(iVar2 + 0x1a);
  this->scene_id = *(u16 *)(iVar2 + 0x18);
  this->f_1e /*u16 **/ = uVar1;
  this->tab_text2 = *(u16 *)(iVar2 + 0x22);
  uVar3 = (ulong)this->f_11 /*u8 **/ & 0xffffffffffffffef | 0x10;
  this->f_11 /*char **/ = (char)uVar3;
  this->menu =
       this->menu & 0xef | (u8)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
  this->f_21 /*u8 **/ = this->f_21 /*u8 **/ & 0xfd | (*(u8 *)(iVar2 + 0x24) & 1) << 1;
  if (*(char *)(iVar2 + 0x25) != '\0') {
    VCALL(this, 0x28 /*SetSize*/)
              ((float)(int)*(short *)(iVar2 + 0x1c),(float)(int)*(short *)(iVar2 + 0x1e));
  }
  return 1;
}

// JP: 0x0027a090  SetData__9MenuSceneFUsP10MenuSprite  size 0x308
// MenuScene::SetData(unsigned short, MenuSprite*)
/* WARNING: Removing unreachable block (ram,0x0027a230) */
/* WARNING: Removing unreachable block (ram,0x0027a26c) */
u32 SetData__9MenuSceneFUsP10MenuSprite(int param_1,u16 param_2,int this)
{
  u16 uVar1;
  int iVar2;
  ulong uVar3;
  iVar2 = (uint)param_2 * 0x20 + *(int *)(param_1 + 0x3c);
  Create__10MenuSpriteFUc(this,((ulong)*(u8 *)(iVar2 + 0x22) & 3) >> 1);
  this->f_16 /*u16 **/ = *(u16 *)(iVar2 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar2 + 0x12);
  uVar1 = *(u16 *)(iVar2 + 0x1e);
  this->scene_id = *(u16 *)(iVar2 + 0x1c);
  this->f_1e /*u16 **/ = uVar1;
  this->s22 = *(u16 *)(iVar2 + 0x20);
  this->f_21 /*u8 **/ = this->f_21 /*u8 **/ & 0xbf | (*(u8 *)(iVar2 + 0x22) & 1) << 6;
  uVar3 = (ulong)this->f_11 /*u8 **/ & 0xfffffffffffffffd | 2;
  this->f_11 /*char **/ = (char)uVar3;
  this->menu =
       this->menu & 0xfd | (u8)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar2 + 0x14),(float)(int)*(short *)(iVar2 + 0x16));
  VCALL(this, 0x28 /*SetSize*/)
            ((float)*(u16 *)(iVar2 + 0x18),(float)*(u16 *)(iVar2 + 0x1a));
  VCALL(this, 0x30 /*SetColor*/)
            (this,*(u8 *)(iVar2 + 0x24),*(u8 *)(iVar2 + 0x25),
             *(u8 *)(iVar2 + 0x26));
  VCALL(this, 0x2c /*SetAlpha*/)(this,*(u8 *)(iVar2 + 0x27));
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xfd |
       (u8)((uint)(((ulong)*(u8 *)(iVar2 + 0x22) << 0x3d) >> 0x3f) << 1);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar2 + 0x22) << 0x3c) >> 0x3f) << 4);
  if ((*(u8 *)(iVar2 + 0x22) & 1) != 0) {
    SetUV__10MenuSpriteFUsUsUsUs
              (this,*(u16 *)(iVar2 + 0x28),*(u16 *)(iVar2 + 0x2c),
               *(u16 *)(iVar2 + 0x2a),*(u16 *)(iVar2 + 0x2e));
  }
  return 1;
}

// JP: 0x0027a3a0  SetData__9MenuSceneFUsP11MenuPolygon  size 0x308
// MenuScene::SetData(unsigned short, MenuPolygon*)
u32 SetData__9MenuSceneFUsP11MenuPolygon(int param_1,u16 param_2,int this)
{
  u8 uVar1;
  u16 uVar2;
  int iVar3;
  ulong uVar4;
  int iVar5;
  u16 *puVar6;
  iVar3 = (uint)param_2 * 0x3c + *(int *)(param_1 + 0x40);
  puVar6 = (u16 *)(iVar3 + 0x10);
  Create__11MenuPolygonFUcUc
            (this,*(u8 *)(iVar3 + 0x1a) & 1,((ulong)*(u8 *)(iVar3 + 0x1a) & 3) >> 1);
  this->f_16 /*u16 **/ = *puVar6;
  this->f_14 /*u16 **/ = *(u16 *)(iVar3 + 0x12);
  uVar2 = *(u16 *)(iVar3 + 0x16);
  this->scene_id = *(u16 *)(iVar3 + 0x14);
  this->f_1e /*u16 **/ = uVar2;
  this->s22 = *(u16 *)(iVar3 + 0x18);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xfd |
       (u8)((uint)(((ulong)*(u8 *)(iVar3 + 0x1a) << 0x3d) >> 0x3f) << 1);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar3 + 0x1a) << 0x3c) >> 0x3f) << 4);
  for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
    SetVertex__11MenuPolygonFiffb
              ((float)(int)(short)puVar6[iVar5 + 6],(float)(int)(short)puVar6[iVar5 + 10],this,
               iVar5,1);
    SetColor__11MenuPolygonFiUcUcUc
              (this,iVar5,*(u8 *)((int)puVar6 + iVar5 + 0x1c),
               *(u8 *)((int)puVar6 + iVar5 + 0x20),
               *(u8 *)((int)puVar6 + iVar5 + 0x24));
    uVar1 = *(u8 *)((int)puVar6 + iVar5 + 0x28);
    if (iVar5 == 0) {
      this->f_4f /*u8 **/ = uVar1;
    }
    else {
      *(u8 *)(this + (iVar5 + -1) * 4 + 0x77) = uVar1;
    }
    uVar4 = (ulong)this->f_11 /*u8 **/ & 0xffffffffffffffef | 0x10;
    this->f_11 /*char **/ = (char)uVar4;
    this->menu =
         this->menu & 0xef | (u8)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  }
  if ((*(u8 *)(iVar3 + 0x1a) & 1) != 0) {
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      uVar2 = puVar6[iVar3 + 0x1a];
      *(u16 *)(this->f_80 /*int **/ + iVar3 * 4) = puVar6[iVar3 + 0x16];
      *(u16 *)(this->f_80 /*int **/ + iVar3 * 4 + 2) = uVar2;
    }
  }
  return 1;
}

// JP: 0x0027a6b0  SetData__9MenuSceneFUsP8MenuText  size 0x388
// MenuScene::SetData(unsigned short, MenuText*)
u32 SetData__9MenuSceneFUsP8MenuText(int param_1,u16 param_2,int this)
{
  u8 uVar1;
  u8 bVar2;
  u16 uVar3;
  u16 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  ulong uVar8;
  iVar6 = (uint)param_2 * 0x1c + *(int *)(param_1 + 0x44);
  Create__8MenuTextFUcUc(this,*(u8 *)(iVar6 + 0x2b) & 1,*(u8 *)(iVar6 + 0x2a) & 7);
  this->f_16 /*u16 **/ = *(u16 *)(iVar6 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar6 + 0x12);
  uVar3 = *(u16 *)(iVar6 + 0x1a);
  this->scene_id = *(u16 *)(iVar6 + 0x18);
  this->f_1e /*u16 **/ = uVar3;
  this->s22 = *(u16 *)(iVar6 + 0x1c);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar6 + 0x14),(float)(int)*(short *)(iVar6 + 0x16));
  VCALL(this, 0x30 /*SetColor*/)
            (this,*(u8 *)(iVar6 + 0x20),*(u8 *)(iVar6 + 0x21),
             *(u8 *)(iVar6 + 0x22));
  VCALL(this, 0x2c /*SetAlpha*/)(this,*(u8 *)(iVar6 + 0x23));
  SetFontNumber__8FontItemFUc(this,*(u16 *)(iVar6 + 0x24) & 0xff);
  uVar4 = *(u16 *)(iVar6 + 0x26);
  iVar7 = (int)(short)uVar4;
  if ((short)uVar4 < 0) {
    iVar7 = iVar7 + 0xf;
  }
  SetCSA__8FontItemFUc(this,iVar7 >> 4 & 0xff);
  cVar5 = (char)(uVar4 & 0xf);
  if (((short)uVar4 < 0) && ((uVar4 & 0xf) != 0)) {
    cVar5 = cVar5 + -0x10;
  }
  this->f_5c /*char **/ = cVar5;
  uVar8 = (ulong)this->f_11 /*u8 **/ & 0xfffffffffffffffd | 2;
  this->f_11 /*char **/ = (char)uVar8;
  this->menu =
       this->menu & 0xfd | (u8)((uint)((uVar8 << 0x3e) >> 0x3f) << 1);
  this->f_58 /*u8 **/ = this->f_58 /*u8 **/ & 0xf7 | (*(u8 *)(iVar6 + 0x2a) >> 7) << 3
  ;
  uVar1 = *(u8 *)(iVar6 + 0x29);
  this->f_5a /*u8 **/ = *(u8 *)(iVar6 + 0x28);
  this->f_5b /*u8 **/ = uVar1;
  bVar2 = *(u8 *)(iVar6 + 0x2a);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 0xbf |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2a) << 0x39) >> 0x3f) << 6);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 199 | (u8)((uint)(((ulong)bVar2 << 0x3a) >> 0x3d) << 3);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xfd |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3e) >> 0x3f) << 1);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3d) >> 0x3f) << 4);
  this->f_58 /*u8 **/ =
       this->f_58 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3c) >> 0x3f) << 4);
  return 1;
}

// JP: 0x0027aa40  SetData__9MenuSceneFUsP11MenuMessage  size 0x3a8
// MenuScene::SetData(unsigned short, MenuMessage*)
u32 SetData__9MenuSceneFUsP11MenuMessage(int param_1,u16 param_2,int this)
{
  u8 uVar1;
  u8 bVar2;
  u16 uVar3;
  u16 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  ulong uVar8;
  iVar6 = (uint)param_2 * 0x20 + *(int *)(param_1 + 0x48);
  VCALL(this, 0x60 /*slot_60*/)
            (this,*(u16 *)(iVar6 + 0x2c),*(u8 *)(iVar6 + 0x2a) & 7);
  this->f_16 /*u16 **/ = *(u16 *)(iVar6 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar6 + 0x12);
  uVar3 = *(u16 *)(iVar6 + 0x1a);
  this->scene_id = *(u16 *)(iVar6 + 0x18);
  this->f_1e /*u16 **/ = uVar3;
  this->s22 = *(u16 *)(iVar6 + 0x1c);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar6 + 0x14),(float)(int)*(short *)(iVar6 + 0x16));
  VCALL(this, 0x30 /*SetColor*/)
            (this,*(u8 *)(iVar6 + 0x20),*(u8 *)(iVar6 + 0x21),
             *(u8 *)(iVar6 + 0x22));
  VCALL(this, 0x2c /*SetAlpha*/)(this,*(u8 *)(iVar6 + 0x23));
  SetFontNumber__8FontItemFUc(this,*(u16 *)(iVar6 + 0x24) & 0xff);
  uVar4 = *(u16 *)(iVar6 + 0x26);
  iVar7 = (int)(short)uVar4;
  if ((short)uVar4 < 0) {
    iVar7 = iVar7 + 0xf;
  }
  SetCSA__8FontItemFUc(this,iVar7 >> 4 & 0xff);
  cVar5 = (char)(uVar4 & 0xf);
  if (((short)uVar4 < 0) && ((uVar4 & 0xf) != 0)) {
    cVar5 = cVar5 + -0x10;
  }
  this->f_5c /*char **/ = cVar5;
  uVar8 = (ulong)this->f_11 /*u8 **/ & 0xfffffffffffffffd | 2;
  this->f_11 /*char **/ = (char)uVar8;
  this->menu =
       this->menu & 0xfd | (u8)((uint)((uVar8 << 0x3e) >> 0x3f) << 1);
  this->f_58 /*u8 **/ = this->f_58 /*u8 **/ & 0xf7 | (*(u8 *)(iVar6 + 0x2a) >> 7) << 3
  ;
  uVar1 = *(u8 *)(iVar6 + 0x29);
  this->f_5a /*u8 **/ = *(u8 *)(iVar6 + 0x28);
  this->f_5b /*u8 **/ = uVar1;
  bVar2 = *(u8 *)(iVar6 + 0x2a);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 0xbf |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2a) << 0x39) >> 0x3f) << 6);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 199 | (u8)((uint)(((ulong)bVar2 << 0x3a) >> 0x3d) << 3);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xfd |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3e) >> 0x3f) << 1);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3d) >> 0x3f) << 4);
  this->f_5f /*u8 **/ = this->f_5f /*u8 **/ & 0xf7;
  this->f_58 /*u8 **/ =
       this->f_58 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar6 + 0x2b) << 0x3c) >> 0x3f) << 4);
  return 1;
}

// JP: 0x0027adf0  SetData__9MenuSceneFUsP8MenuFont  size 0x280
// MenuScene::SetData(unsigned short, MenuFont*)
u32 SetData__9MenuSceneFUsP8MenuFont(int param_1,u16 param_2,int this)
{
  u8 uVar1;
  u8 bVar2;
  u16 uVar3;
  int iVar4;
  iVar4 = (uint)param_2 * 0x1c + *(int *)(param_1 + 0x4c);
  CreateFont__8MenuFontFiUsUc
            (this,*(u16 *)(iVar4 + 0x24),*(u16 *)(iVar4 + 0x1e),
             *(u8 *)(iVar4 + 0x2a) & 7);
  this->f_16 /*u16 **/ = *(u16 *)(iVar4 + 0x10);
  this->f_14 /*u16 **/ = *(u16 *)(iVar4 + 0x12);
  uVar3 = *(u16 *)(iVar4 + 0x1a);
  this->scene_id = *(u16 *)(iVar4 + 0x18);
  this->f_1e /*u16 **/ = uVar3;
  this->s22 = *(u16 *)(iVar4 + 0x1c);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar4 + 0x14),(float)(int)*(short *)(iVar4 + 0x16));
  VCALL(this, 0x30 /*SetColor*/)
            (this,*(u8 *)(iVar4 + 0x20),*(u8 *)(iVar4 + 0x21),
             *(u8 *)(iVar4 + 0x22));
  VCALL(this, 0x2c /*SetAlpha*/)(this,*(u8 *)(iVar4 + 0x23));
  SetCSA__8FontItemFUc(this,*(u16 *)(iVar4 + 0x26) & 0xff);
  uVar1 = *(u8 *)(iVar4 + 0x29);
  this->f_5a /*u8 **/ = *(u8 *)(iVar4 + 0x28);
  this->f_5b /*u8 **/ = uVar1;
  bVar2 = *(u8 *)(iVar4 + 0x2a);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 0xbf |
       (u8)((uint)(((ulong)*(u8 *)(iVar4 + 0x2a) << 0x39) >> 0x3f) << 6);
  this->f_5e /*u8 **/ =
       this->f_5e /*u8 **/ & 199 | (u8)((uint)(((ulong)bVar2 << 0x3a) >> 0x3d) << 3);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xfd |
       (u8)((uint)(((ulong)*(u8 *)(iVar4 + 0x2b) << 0x3e) >> 0x3f) << 1);
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar4 + 0x2b) << 0x3d) >> 0x3f) << 4);
  return 1;
}

// JP: 0x0027b070  SetData__9MenuSceneFUsP14MenuFontItalic  size 0x1d4
// MenuScene::SetData(unsigned short, MenuFontItalic*)
u32 SetData__9MenuSceneFUsP14MenuFontItalic(int param_1,u16 param_2,int this)
{
  u16 uVar1;
  int iVar2;
  iVar2 = (uint)param_2 * 0x18 + *(int *)(param_1 + 0x50);
  CreateItalic__14MenuFontItalicFPc(this,*(u32 *)(iVar2 + 0x10));
  this->f_16 /*u16 **/ = *(u16 *)(iVar2 + 0x14);
  this->f_14 /*u16 **/ = *(u16 *)(iVar2 + 0x16);
  uVar1 = *(u16 *)(iVar2 + 0x1e);
  this->scene_id = *(u16 *)(iVar2 + 0x1c);
  this->f_1e /*u16 **/ = uVar1;
  this->s22 = *(u16 *)(iVar2 + 0x20);
  VCALL(this, 0x24 /*SetPosition*/)
            ((float)(int)*(short *)(iVar2 + 0x18),(float)(int)*(short *)(iVar2 + 0x1a));
  VCALL(this, 0x30 /*SetColor*/)
            (this,*(u8 *)(iVar2 + 0x24),*(u8 *)(iVar2 + 0x25),
             *(u8 *)(iVar2 + 0x26));
  VCALL(this, 0x2c /*SetAlpha*/)(this,*(u8 *)(iVar2 + 0x27));
  this->f_21 /*u8 **/ = this->f_21 /*u8 **/ & 0xfd | (*(u8 *)(iVar2 + 0x22) & 1) << 1;
  this->f_21 /*u8 **/ =
       this->f_21 /*u8 **/ & 0xef |
       (u8)((uint)(((ulong)*(u8 *)(iVar2 + 0x22) << 0x3e) >> 0x3f) << 4);
  return 1;
}

// JP: 0x0027b250  GetRealHeap__9MenuSceneFP9BufMemoryi  size 0x1c
// MenuScene::GetRealHeap(BufMemory*, int)
u32 GetRealHeap__9MenuSceneFP9BufMemoryi(u64 param_1,int this)
{
  return this->link_next;
}

// JP: 0x0027b270  GetReady__9MenuSceneFv  size 0x14
// MenuScene::GetReady()
u32 GetReady__9MenuSceneFv(void)
{
  return 1;
}

// JP: 0x0027b290  Release__9MenuSceneFv  size 0x54
// MenuScene::Release()
void Release__9MenuSceneFv(MenuScene *this)
{
  if (this->heap != 0) {
    __dt__9BufMemoryFv(this->heap,1);
    this->heap = 0;
  }
  this->sflags = 1;
  return;
}

// JP: 0x0027b2f0  Run__9MenuSceneFv  size 0x14
// MenuScene::Run()
u64 Run__9MenuSceneFv(void)
{
  return 0;
}

// JP: 0x0027b310  Shutdown__9MenuSceneFv  size 0x10
// MenuScene::Shutdown()
void Shutdown__9MenuSceneFv(void)
{
  return;
}

// JP: 0x0027b320  Restore__9MenuSceneFv  size 0x10
// MenuScene::Restore()
void Restore__9MenuSceneFv(void)
{
  return;
}
