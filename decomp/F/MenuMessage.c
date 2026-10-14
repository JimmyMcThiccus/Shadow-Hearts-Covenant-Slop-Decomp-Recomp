/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0027d490  __ct__11MenuMessageFv  size 0x60
// MenuMessage::MenuMessage()
int __ct__11MenuMessageFv(MenuMessage *this)
{
  __ct__14PluralFontItemFv(this);
  this->vptr = __vt__11MenuMessage;
  this->packet = 0x405444;
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x0027d4f0  __dt__11MenuMessageFv  size 0x94
// MenuMessage::~MenuMessage()
int __dt__11MenuMessageFv(MenuMessage *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__11MenuMessage;
    this->packet = 0x405444;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__14PluralFontItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0027d590  Create__11MenuMessageFUsUc  size 0xe8
// MenuMessage::Create(unsigned short, unsigned char)
void Create__11MenuMessageFUsUc(MenuMessage *this,short param_2,char param_3)
{
  u32 uVar1;
  long lVar2;
  if (param_3 == '\x04') {
    this->qwc = param_2 * 6 + 8;
    lVar2 = __nw__FUi(0x30);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__11SendOnLocalFv(lVar2);
    }
    this->kbd_icon = uVar1;
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
              (this->kbd_icon,0x421870,DAT_0042186c,1,0xffffffffffffffff);
  }
  Create__14PluralFontItemFUsUc(this,param_2,param_3);
  return;
}

// JP: 0x0027d680  ClearMessage__11MenuMessageFv  size 0xac
// MenuMessage::ClearMessage()
void ClearMessage__11MenuMessageFv(MenuMessage *this)
{
  this->n_chars = 0;
  this->cur_char = 0;
  this->n_lines = 0;
  this->n_visible = 0;
  this->fade_from = 0;
  this->n_macro = 0;
  this->cur_macro = 0;
  this->n_rects = 0;
  this->char_timer = 0;
  this->cursor_x = 0;
  this->cursor_y = 0;
  this->line_no = 0;
  Destroy__8MenuIconFv(this + 0x68);
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  return;
}

// JP: 0x0027d730  Return__11MenuMessageFv  size 0x78
// MenuMessage::Return()
void Return__11MenuMessageFv(MenuMessage *this)
{
  u8 auStack_20 [2];
  short sStack_1e;
  int iStack_10;
  iStack_10 = this;
  GetOrderInfo__8FontItemFP9OrderInfo(this,auStack_20);
  *(u16 *)(iStack_10 + 0x82) = 0;
  *(u16 *)(iStack_10 + 0x84) =
       *(short *)(iStack_10 + 0x84) + sStack_1e + (u16)*(u8 *)(iStack_10 + 0x59);
  *(short *)(iStack_10 + 0x86) = *(short *)(iStack_10 + 0x86) + 1;
  return;
}

// JP: 0x0027d7b0  Start__11MenuMessageFv  size 0x184
// MenuMessage::Start()
void Start__11MenuMessageFv(MenuMessage *this)
{
  ulong uVar1;
  if (((ulong)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x274) & 0x3f) >> 4 != 3)
  {
    this->cur_char = 0;
    this->n_visible = 0;
    this->fade_from = 0;
    this->cur_macro = 0;
    this->char_timer = 0;
    TraceSetRendering__12MenuObjTableFUc(this + 0x68,0);
    this->state = 9;
    uVar1 = (ulong)this->dirty1 & 0xfffffffffffffffb | 4;
    this->dirty1 = (char)uVar1;
    this->dirty0 =
         this->dirty0 & 0xfb | (u8)((uint)((uVar1 << 0x3d) >> 0x3f) << 2);
    uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
    this->dirty1 = (char)uVar1;
    this->dirty0 =
         this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
    uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
    this->dirty1 = (char)uVar1;
    this->dirty0 =
         this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
    SetMacro__11MenuMessageFUs(this,0);
  }
  return;
}

// JP: 0x0027d940  Finish__11MenuMessageFv  size 0x228
// MenuMessage::Finish()
void Finish__11MenuMessageFv(MenuMessage *this)
{
  u16 uVar1;
  u16 uVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  uint uVar6;
  iVar3 = GetFontPacket__14PluralFontItemCFUc(this,0);
  uVar1 = this->fade_from;
  iVar4 = GetFontPacket__14PluralFontItemCFUc(this,0);
  uVar2 = this->n_chars;
  this->fade_from = this->n_chars;
  this->cur_char = this->n_chars;
  this->n_visible = this->n_lines;
  this->cur_macro = this->n_macro;
  for (uVar6 = iVar3 + (uint)uVar1 * 0x30; uVar6 < iVar4 + (uint)uVar2 * 0x30; uVar6 = uVar6 + 0x30)
  {
    *(u8 *)(uVar6 + 0x17) = 0x80;
  }
  Finish__8MenuIconFv(this + 0x68);
  if ((long)((ulong)this->fflags3 << 0x3c) < 0) {
    SetDefault__11MenuMessageFv(this);
  }
  this->state = 1;
  uVar5 = (ulong)this->dirty1 & 0xfffffffffffffffb | 4;
  this->dirty1 = (char)uVar5;
  this->dirty0 =
       this->dirty0 & 0xfb | (u8)((uint)((uVar5 << 0x3d) >> 0x3f) << 2);
  uVar5 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar5;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar5 << 0x3c) >> 0x3f) << 3);
  uVar5 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar5;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x0027db70  SetOrderData__11MenuMessageFUssssUs  size 0x1b4
// MenuMessage::SetOrderData(unsigned short, short, short, short, unsigned short)
void SetOrderData__11MenuMessageFUssssUs
               (MenuMessage *this,short param_2,u16 param_3,u16 param_4,u16 param_5,
               short param_6)
{
  int iVar1;
  GetFontPacket__14PluralFontItemCFUc(this,0);
  this->n_chars = this->n_chars + param_2;
  this->cursor_x = param_3;
  this->cursor_y = param_4;
  this->line_no = param_5;
  this->n_macro = this->n_macro + param_6;
  if ((long)((ulong)this->fflags3 << 0x3c) < 0) {
    iVar1 = GetFontPacket__14PluralFontItemCFUc(this,1);
    iVar1 = iVar1 + (uint)this->n_macro * 0x30;
    *(u16 *)(iVar1 + 0x14) = 6;
    *(u16 *)(iVar1 + 0x16) = this->n_chars;
    this->n_macro = this->n_macro + 1;
  }
  if (((ulong)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x274) & 0x3f) >> 4 == 3)
  {
    Finish__11MenuMessageFv(this);
  }
  else {
    SetMacro__11MenuMessageFUs(this,this->cur_char);
  }
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  return;
}

// JP: 0x0027dd30  SetMessageData__11MenuMessageFPcP8DrawRect  size 0x258
// MenuMessage::SetMessageData(char*, DrawRect*)
void SetMessageData__11MenuMessageFPcP8DrawRect(MenuMessage *this,u64 param_2,float *param_3)
{
  int iVar1;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  iVar1 = GetFontPacket__14PluralFontItemCFUc(this,1);
  iVar1 = iVar1 + (uint)this->n_rects * 0x30;
  fStack_40 = (float)(int)this->x;
  fStack_3c = (float)(int)this->y;
  fStack_38 = (float)(int)(this->x + this->w);
  fStack_34 = (float)(int)(this->y + this->h);
  if (*param_3 < fStack_40) {
    fStack_40 = *param_3;
  }
  if (param_3[1] < fStack_3c) {
    fStack_3c = param_3[1];
  }
  if (fStack_38 < param_3[2]) {
    fStack_38 = param_3[2];
  }
  if (fStack_34 < param_3[3]) {
    fStack_34 = param_3[3];
  }
  this->w = fStack_38 - fStack_40;
  this->h = fStack_34 - fStack_3c;
  *(short *)(iVar1 + 4) = (short)(int)*param_3;
  *(short *)(iVar1 + 6) = (short)(int)param_3[1];
  *(short *)(iVar1 + 0xc) = (short)(int)(param_3[2] - *param_3);
  *(short *)(iVar1 + 0xe) = (short)(int)(param_3[3] - param_3[1]);
  this->n_rects = this->n_rects + 1;
  return;
}

// JP: 0x0027df90  SetMacro__11MenuMessageFUs  size 0x160
// MenuMessage::SetMacro(unsigned short)
u32 SetMacro__11MenuMessageFUs(MenuMessage *this,short param_2)
{
  short sVar1;
  int iVar2;
  iVar2 = GetFontPacket__14PluralFontItemCFUc(this,1);
  iVar2 = iVar2 + (uint)this->cur_macro * 0x30;
  do {
    if ((this->n_macro <= this->cur_macro) ||
       (*(short *)(iVar2 + 0x16) != param_2)) {
      return 0;
    }
    sVar1 = *(short *)(iVar2 + 0x14);
    if (sVar1 == 6) {
      SetDefault__11MenuMessageFv(this);
    }
    else if (sVar1 == 5) {
      this->char_interval = (short)*(u32 *)(iVar2 + 0x24);
    }
    else if (((sVar1 == 4) || (sVar1 == 3)) || (sVar1 == 1)) {
      this->state = 10;
      return 1;
    }
    this->cur_macro = this->cur_macro + 1;
    iVar2 = iVar2 + 0x30;
  } while( true );
}

// JP: 0x0027e0f0  GetRect__11MenuMessageFUsP8DrawRect  size 0x108
// MenuMessage::GetRect(unsigned short, DrawRect*)
bool GetRect__11MenuMessageFUsP8DrawRect(MenuMessage *this,u16 param_2,float *param_3)
{
  bool bVar1;
  int iVar2;
  bVar1 = param_2 <= this->n_rects;
  if (bVar1) {
    iVar2 = GetFontPacket__14PluralFontItemCFUc(this,1);
    iVar2 = iVar2 + (uint)param_2 * 0x30;
    *param_3 = (float)(int)*(short *)(iVar2 + 4) + this->x;
    param_3[1] = (float)(int)*(short *)(iVar2 + 6) + this->y;
    param_3[2] = (float)(int)*(short *)(iVar2 + 0xc);
    param_3[3] = (float)(int)*(short *)(iVar2 + 0xe);
  }
  return bVar1;
}

// JP: 0x0027e200  SetDefault__11MenuMessageFv  size 0xa0
// MenuMessage::SetDefault()
void SetDefault__11MenuMessageFv(MenuMessage *this)
{
  ulong uVar1;
  uVar1 = ((ulong)*(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x274) & 0x3f) >> 4;
  if (uVar1 == 2) {
    this->char_interval = 0x32;
  }
  else if (uVar1 == 0) {
    this->char_interval = 200;
  }
  else {
    this->char_interval = 100;
  }
  this->fade_rate = 0x83126f;
  return;
}

// JP: 0x0027e2a0  Polling__11MenuMessageFv  size 0x58c
// MenuMessage::Polling()
void Polling__11MenuMessageFv(MenuMessage *this)
{
  short sVar1;
  int iVar2;
  long lVar3;
  u64 uVar4;
  ulong uVar5;
  int iVar6;
  u16 uVar7;
  u16 uVar8;
  if (this->state == '\n') {
    this->char_timer = this->char_timer + (short)sm_iPassTime__7MenuObj;
    iVar2 = GetFontPacket__14PluralFontItemCFUc(this,1);
    if ((ulong)(long)*(int *)(iVar2 + (uint)this->cur_macro * 0x30 + 0x24) <=
        (ulong)(long)this->char_timer) {
      this->state = 9;
      iVar2 = GetFontPacket__14PluralFontItemCFUc(this,1);
      this->char_timer =
           this->char_timer -
           (short)*(u32 *)(iVar2 + (uint)this->cur_macro * 0x30 + 0x24);
      sVar1 = this->cur_char + 1;
      this->cur_char = sVar1;
      SetMacro__11MenuMessageFUs(this,sVar1);
    }
  }
  else if ((this->state == '\t') &&
          (this->cur_char < this->n_chars)) {
    this->char_timer = this->char_timer + (short)sm_iPassTime__7MenuObj;
    if (this->char_interval <= this->char_timer) {
      uVar5 = (ulong)this->dirty1 & 0xfffffffffffffffb | 4;
      this->dirty1 = (char)uVar5;
      this->dirty0 =
           this->dirty0 & 0xfb | (u8)((uint)((uVar5 << 0x3d) >> 0x3f) << 2);
      uVar5 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
      this->dirty1 = (char)uVar5;
      this->dirty0 =
           this->dirty0 & 0xf7 | (u8)((uint)((uVar5 << 0x3c) >> 0x3f) << 3);
      uVar5 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
      this->dirty1 = (char)uVar5;
      this->dirty0 =
           this->dirty0 & 0xef | (u8)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
    }
    while (this->char_interval <= this->char_timer) {
      iVar2 = GetFontPacket__14PluralFontItemCFUc(this,0);
      iVar2 = iVar2 + (uint)this->cur_char * 0x30;
      *(u8 *)(iVar2 + 0x17) = 0;
      *(u32 *)(iVar2 + 0x24) = this->fade_rate;
      this->cur_char = this->cur_char + 1;
      this->char_timer = this->char_timer - this->char_interval;
      if (*(char *)(iVar2 + 0xc) != '\0') {
        this->n_visible = this->n_visible + 1;
      }
      lVar3 = SetMacro__11MenuMessageFUs(this,this->cur_char);
      if ((lVar3 != 0) || (this->n_chars <= this->cur_char)) break;
    }
  }
  if (this->fade_from < this->cur_char) {
    iVar2 = GetFontPacket__14PluralFontItemCFUc(this,0);
    iVar2 = iVar2 + (uint)this->fade_from * 0x30;
    uVar8 = this->cur_char;
    for (uVar7 = this->fade_from; uVar7 < this->cur_char; uVar7 = uVar7 + 1
        ) {
      *(char *)(iVar2 + 0x17) =
           *(char *)(iVar2 + 0x17) +
           (char)((uint)(*(int *)(iVar2 + 0x24) * sm_iPassTime__7MenuObj) >> 0x18);
      if (*(u8 *)(iVar2 + 0x17) < 0x80) {
        if (uVar7 < uVar8) {
          uVar8 = uVar7;
        }
      }
      else {
        *(u8 *)(iVar2 + 0x17) = 0x80;
      }
      if (*(char *)(iVar2 + 0xc) == '\0') {
        uVar4 = FindObj__12MenuObjTableFs(this + 0x68,uVar7);
        iVar6 = (int)uVar4;
        VCALL(iVar6, 0x2c /*SetAlpha*/)(uVar4,*(u8 *)(iVar2 + 0x17));
        *(u8 *)(iVar6 + 0x12) = *(u8 *)(iVar6 + 0x12) & 0xfe | 1;
      }
      iVar2 = iVar2 + 0x30;
    }
    this->fade_from = uVar8;
    uVar5 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
    this->dirty1 = (char)uVar5;
    this->dirty0 =
         this->dirty0 & 0xef | (u8)((uint)((uVar5 << 0x3b) >> 0x3f) << 4);
  }
  return;
}

// JP: 0x0027e830  Update__11MenuMessageFiiUs  size 0x9cc
// MenuMessage::Update(int, int, unsigned short)
void Update__11MenuMessageFiiUs(MenuMessage *this,int param_2,short param_3,u16 param_4)
{
  u8 bVar1;
  short sVar2;
  short sVar3;
  u32 *puVar4;
  u16 uVar5;
  u64 *puVar6;
  u8 auVar7 [16];
  u8 auVar8 [16];
  u8 uVar9;
  u8 *puVar10;
  int iVar11;
  u64 uVar12;
  ulong uVar13;
  u16 uVar14;
  u8 *puVar15;
  u8 *pbVar16;
  u64 in_v1_udw;
  u8 auVar17 [16];
  u8 auVar18 [16];
  u8 auVar19 [16];
  u8 auVar20 [16];
  char cVar21;
  u64 in_a0_udw;
  u8 auVar22 [16];
  u8 auVar23 [16];
  u64 in_a2_udw;
  u8 *puVar24;
  u64 *puVar25;
  u32 *puVar26;
  int iVar27;
  ulong *puVar28;
  ulong *puVar29;
  ulong uVar30;
  u32 *puStack_6c;
  u16 uStack_4c;
  cVar21 = (char)this;
  if ((this->fflags2 & 7) == 4) {
    uVar5 = (u16)m_Env__8VIF1Prim;
    uVar14 = uVar5 & 1;
    puVar10 = (u8 *)GetFontPacket__14PluralFontItemCFUc(cVar21,uVar5 & 1);
    iVar11 = GetFontPacket__14PluralFontItemCFUc(cVar21,0);
    puVar15 = puVar10 + (uint)this->n_visible * 0x30;
    puVar4 = *(u32 **)((short)uVar14 * 4 + this + 0x40);
    pbVar16 = (u8 *)(this + (uVar5 & 0xffff0001) + 0x10);
    param_2 = param_2 + (int)this->x * 0x10;
    param_3 = param_3 + (short)(int)this->y * 0x10;
    bVar1 = this->a;
    TraceAddUpdate__12MenuObjTableFUc(cVar21 + 'h',*pbVar16);
    TraceUpdate__12MenuObjTableFiiUs
              (cVar21 + 'h',param_2,param_3,(short)((uint)bVar1 * 0x100 * (uint)param_4 >> 0xf));
    if ((long)((ulong)*pbVar16 << 0x3c) < 0) {
      puVar29 = (ulong *)(puVar4 + 0xe);
      iVar27 = iVar11;
      for (puVar24 = puVar10; puVar24 < puVar15; puVar24 = puVar24 + 0x30) {
        for (; *(char *)(iVar27 + 0xc) == '\0'; iVar27 = iVar27 + 0x30) {
        }
        *(short *)(puVar24 + 0x18) = (short)param_2 + *(short *)(iVar27 + 4) * 0x10;
        *(short *)(puVar24 + 0x1a) = param_3 + *(short *)(iVar27 + 6) * 0x10;
        auVar17._8_8_ = in_v1_udw;
        auVar17._0_8_ = 0xffffffffffffffff;
        auVar7._8_8_ = in_a2_udw;
        auVar7._0_8_ = 0xffffffff;
        auVar18 = _pcpyld(auVar17,auVar7);
        auVar19._8_8_ = auVar18._8_8_;
        *(ulong *)(puVar24 + 0x18) = *(ulong *)(puVar24 + 0x18) & auVar18._0_8_ | 0x100000000;
        *(u16 *)(puVar24 + 0x28) =
             *(short *)(puVar24 + 0x18) + (u16)*(u8 *)(iVar27 + 0xc) * 0x10;
        *(u16 *)(puVar24 + 0x2a) =
             *(short *)(puVar24 + 0x1a) + (u16)*(u8 *)(iVar27 + 0xd) * 0x10;
        auVar19._0_8_ = 0xffffffffffffffff;
        auVar18._8_8_ = in_a0_udw;
        auVar18._0_8_ = 0xffffffff;
        auVar18 = _pcpyld(auVar19,auVar18);
        *(ulong *)(puVar24 + 0x28) = *(ulong *)(puVar24 + 0x28) & auVar18._0_8_ | 0x100000000;
        *(u16 *)puVar29 = *(u16 *)(puVar24 + 0x18);
        *(u16 *)((int)puVar29 + 2) = *(u16 *)(puVar24 + 0x1a);
        auVar20._8_8_ = auVar19._8_8_;
        auVar20._0_8_ = 0xffffffffffffffff;
        auVar22._8_8_ = auVar18._8_8_;
        auVar22._0_8_ = 0xffffffff;
        auVar18 = _pcpyld(auVar20,auVar22);
        in_v1_udw = auVar18._8_8_;
        *puVar29 = *puVar29 & auVar18._0_8_ | 0x100000000;
        puVar28 = puVar29 + 2;
        *(u16 *)puVar28 = *(short *)(puVar24 + 0x28) + (this->shadow_x + 1) * 0x10;
        *(u16 *)((int)puVar29 + 0x12) = *(u16 *)(puVar24 + 0x2a);
        auVar23._8_8_ = auVar22._8_8_;
        auVar23._0_8_ = 0xffffffff;
        auVar8._8_8_ = in_a2_udw;
        auVar8._0_8_ = 0xffffffffffffffff;
        auVar18 = _pcpyld(auVar8,auVar23);
        *puVar28 = *puVar28 & auVar18._0_8_ | 0x100000000;
        puVar29 = puVar29 + 6;
        iVar27 = iVar27 + 0x30;
      }
    }
    if ((long)((ulong)*pbVar16 << 0x3b) < 0) {
      uStack_4c = 0x8000;
      if ((long)((ulong)this->pflags << 0x3a) < 0) {
        uStack_4c = param_4;
      }
      puStack_6c = puVar4 + 10;
      for (; puVar10 < puVar15; puVar10 = puVar10 + 0x30) {
        for (; *(char *)(iVar11 + 0xc) == '\0'; iVar11 = iVar11 + 0x30) {
        }
        *puVar10 = this->r;
        puVar10[1] = this->g;
        puVar10[2] = this->b;
        uVar9 = (u8)((uint)*(u8 *)(iVar11 + 0x17) * (uint)uStack_4c >> 0xf);
        *(u8 *)((int)puStack_6c + 3) = uVar9;
        puVar10[3] = uVar9;
        iVar11 = iVar11 + 0x30;
        puStack_6c = puStack_6c + 0xc;
      }
    }
    if ((long)((ulong)*pbVar16 << 0x39) < 0) {
      SetUV__14PluralFontItemFss(cVar21,uVar14 ^ 1,uVar14);
    }
    puVar26 = puVar4 + ((uint)this->stride * 2 + (uint)this->stride +
                       2) * 4;
    if ((*pbVar16 & 1) != 0) {
      puVar26[1] = puVar4 + (this->qwc - 1) * 4;
      *(u64 *)(puVar4 + 6) = 0x53d310;
      *(u64 *)(puVar26 + 4) = 0x10ab400000000002;
      *(u64 *)(puVar26 + 6) = 0xe;
      *(u64 *)(puVar26 + 0x12) = 0x53d3f1;
      *(u64 *)(puVar26 + 10) = 0x16;
      *(u64 *)(puVar26 + 0xe) = 6;
      if ((this->fflags2 & 7) == 4) {
        puVar25 = (u64 *)(puVar4 + 8);
        puVar6 = puVar25 + ((uint)this->n_lines * 2 +
                           (uint)this->n_lines) * 2;
        sVar2 = *DAT_00421868;
        sVar3 = DAT_00421868[1];
        for (; puVar25 < puVar6; puVar25 = puVar25 + 6) {
          *puVar25 = 0x156;
          *(u8 *)((int)puVar25 + 10) = 0x80;
          *(u8 *)((int)puVar25 + 9) = 0x80;
          *(u8 *)(puVar25 + 1) = 0x80;
          *(u16 *)((int)puVar25 + 0x12) = 0;
          *(u16 *)(puVar25 + 2) = 0;
          *(short *)(puVar25 + 4) = sVar2 << 4;
          *(short *)((int)puVar25 + 0x22) = sVar3 << 4;
        }
      }
    }
    if ((long)((ulong)*pbVar16 << 0x3d) < 0) {
      if (this->n_visible == 0) {
        *puVar4 = 0x20000000;
        puVar4[1] = puVar4 + (this->qwc - 1) * 4;
        puVar4[3] = 0;
      }
      else {
        *puVar4 = &UNK_20000001 +
                  (uint)this->n_visible * 2 + (uint)this->n_visible;
        puVar4[1] = puVar26;
        puVar4[3] = (uint)this->n_visible * 2 + (uint)this->n_visible +
                    0x50000001;
        *puVar26 = &UNK_20000004 + (uint)this->n_visible * 3;
        puVar26[3] = (uint)this->n_visible * 2 + (uint)this->n_visible +
                     0x50000004;
        *(ulong *)(puVar4 + 4) = (ulong)this->n_visible | 0x6400000000000000;
        *(ulong *)(puVar26 + 0x10) =
             CONCAT44(0x4000000,(uint)(this->n_visible | 0x8000)) | 0x6000000000000000;
      }
    }
    if ((this->font_draw != 0) && ((long)((ulong)*pbVar16 << 0x3e) < 0)) {
      uVar12 = GetTex2__10ClutRasterCF6GS_PSMUcUc
                         ((char)*(u32 *)(this->font_draw + 0x30),0x1b,0,1);
      *(u64 *)(puVar26 + 8) = uVar12;
      iVar11 = this->font_draw;
      uVar30 = *(ulong *)(*(int *)(iVar11 + 0x2c) +
                         (int)((long)((ulong)*(u8 *)(iVar11 + 0x3e) << 0x3e) >> 0x3f) * -0x20);
      uVar13 = GetClutFlag__10ClutRasterFUcUc
                         ((char)*(u32 *)(iVar11 + 0x30),this->csa,0);
      *(ulong *)(puVar26 + 0xc) = uVar30 & 0x7ffffffff | uVar13;
    }
    if (this->kbd_icon != 0) {
      if (*(char *)(this->kbd_icon + (uint)(m_Env__8VIF1Prim & 1) + 0x10) != '\0') {
        VCALL(this->kbd_icon, 0x14 /*Update*/)
                  ((char)this->kbd_icon,param_2,param_3,0);
      }
    }
    *pbVar16 = *pbVar16 & 0x80;
  }
  else {
    Update__14PluralFontItemFiiUs(cVar21,param_2,param_3,param_4);
  }
  return;
}

// JP: 0x0027f200  Connect__11MenuMessageFP4_QWD  size 0xbc
// MenuMessage::Connect(_QWD*)
void Connect__11MenuMessageFP4_QWD(MenuMessage *this,u32 param_2)
{
  u32 uStack_10;
  uStack_10 = param_2;
  if (this->attached != 0) {
    uStack_10 = VCALL(this->attached, 0x18 /*Connect*/)
                          (this->attached,param_2);
  }
  if (this->n_visible != 0) {
    if (this->kbd_icon != 0) {
      uStack_10 = VCALL(this->kbd_icon, 0x18 /*Connect*/)
                            (this->kbd_icon,uStack_10);
    }
    uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x3c,uStack_10);
  }
  TraceConnect__12MenuObjTableFP4_QWD(this + 0x68,uStack_10);
  return;
}

// JP: 0x0027f2c0  Destroy__11MenuMessageFv  size 0x74
// MenuMessage::Destroy()
void Destroy__11MenuMessageFv(MenuMessage *this)
{
  int iVar1;
  Destroy__8FontItemFv(this);
  if (this->kbd_icon != 0) {
    iVar1 = this->kbd_icon;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
    this->kbd_icon = 0;
  }
  return;
}

// JP: 0x0027f340  Clear__11MenuMessageFv  size 0x8c
// MenuMessage::Clear()
void Clear__11MenuMessageFv(MenuMessage *this)
{
  Clear__14PluralFontItemFv(this);
  this->cur_macro = 0;
  this->n_macro = 0;
  this->fade_from = 0;
  this->char_timer = 0;
  this->line_no = 0;
  this->cursor_y = 0;
  this->cursor_x = 0;
  this->kbd_icon = 0;
  SetDefault__11MenuMessageFv(this);
  return;
}

// JP: 0x0027f3d0  GetLastPosition__11MenuMessageFPsPs  size 0x110
// MenuMessage::GetLastPosition(short*, short*)
u16 GetLastPosition__11MenuMessageFPsPs(MenuMessage *this,short *param_2,short *param_3)
{
  int iVar1;
  *param_2 = (short)(int)this->x;
  *param_3 = (short)(int)this->y;
  if (this->cur_char != 0) {
    iVar1 = GetFontPacket__14PluralFontItemCFUc(this,0);
    iVar1 = iVar1 + (this->cur_char - 1) * 0x30;
    *param_2 = *param_2 +
               (u16)this->shadow_x +
               *(short *)(iVar1 + 4) + (u16)*(u8 *)(iVar1 + 0xc);
    *param_3 = *param_3 + *(short *)(iVar1 + 6);
  }
  return this->cur_char;
}

// JP: 0x0027f4e0  @60@__dt__11MenuMessageFv  size 0x8
// @60@__dt__11MenuMessageFv
u32 * _60___dt__11MenuMessageFv(MenuMessage *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__11MenuMessage;
    *this = 0x405444;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__14PluralFontItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
