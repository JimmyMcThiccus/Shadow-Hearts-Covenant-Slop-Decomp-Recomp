/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003ab510  __ct__17openingBattleDemoFv  size 0x78
// openingBattleDemo::openingBattleDemo()
int __ct__17openingBattleDemoFv(openingBattleDemo *this)
{
  __ct__7CPolObjFv(this);
  this->f_14 /*u8 **/ = __vt__17openingBattleDemo;
  this->go = 0;
  this->btl_done = 0;
  this->finished = 0;
  this->not_skipped = 1;
  this->banner = 0;
  this->p38 = 0;
  this->p3c = 0;
  return this;
}

// JP: 0x003ab590  __dt__17openingBattleDemoFv  size 0x84
// openingBattleDemo::~openingBattleDemo()
int __dt__17openingBattleDemoFv(openingBattleDemo *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__17openingBattleDemo;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003ab620  start__17openingBattleDemoFv  size 0x20
// openingBattleDemo::start()
void start__17openingBattleDemoFv(openingBattleDemo *this)
{
  this->go = 1;
  return;
}

// JP: 0x003ab640  initialize__17openingBattleDemoFPUci  size 0x1b4
// openingBattleDemo::initialize(unsigned char*, int)
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void initialize__17openingBattleDemoFPUci(openingBattleDemo *this,u32 param_2,u32 param_3)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  int aiStack_90 [4];
  u32 uStack_80;
  u32 uStack_7c;
  undefined *puStack_78;
  undefined *puStack_74;
  u32 uStack_70;
  u32 uStack_6c;
  u32 uStack_68;
  u32 uStack_64;
  u32 uStack_60;
  u32 uStack_5c;
  u32 uStack_58;
  undefined *puStack_54;
  u32 uStack_50;
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 uStack_40;
  u32 uStack_3c;
  u32 uStack_38;
  u32 uStack_34;
  int iStack_30;
  u32 uStack_20;
  u32 uStack_10;
  iVar1 = m_mons;
  iStack_30 = this;
  uStack_20 = param_2;
  uStack_10 = param_3;
  aiStack_90[0] = (int)__6141;
  aiStack_90[1] = (int)((ulong)__6141 >> 0x20);
  aiStack_90[2] = DAT_003fa558;
  aiStack_90[3] = DAT_003fa55c;
  uStack_80 = (int)_DAT_003fa560;
  uStack_7c = (int)((ulong)_DAT_003fa560 >> 0x20);
  puStack_78 = PTR_003fa568;
  puStack_74 = PTR_003fa56c;
  uStack_70 = (int)_DAT_003fa570;
  uStack_6c = (int)((ulong)_DAT_003fa570 >> 0x20);
  uStack_68 = DAT_003fa578;
  uStack_64 = DAT_003fa57c;
  uStack_60 = (int)_DAT_003fa580;
  uStack_5c = (int)((ulong)_DAT_003fa580 >> 0x20);
  uStack_58 = DAT_003fa588;
  puStack_54 = PTR_003fa58c;
  uStack_50 = (int)_DAT_003fa590;
  uStack_4c = (int)((ulong)_DAT_003fa590 >> 0x20);
  uStack_48 = DAT_003fa598;
  uStack_44 = DAT_003fa59c;
  uStack_40 = (int)_DAT_003fa5a0;
  uStack_3c = (int)((ulong)_DAT_003fa5a0 >> 0x20);
  uStack_38 = DAT_003fa5a8;
  uStack_34 = DAT_003fa5ac;
  piVar2 = aiStack_90 + m_mons * 8;
  this->monset = *piVar2;
  this->battle_no = aiStack_90[iVar1 * 8 + 2];
  this->bgm = aiStack_90[iVar1 * 8 + 3];
  *(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) = 0;
  ClearBattleTeam__15SaveMenuSectionFc(0);
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    if (piVar2[iVar3 + 4] != -1) {
      JoinParty__15SaveMenuSectionFcc((char)piVar2[iVar3 + 4],0);
      JoinBattle__15SaveMenuSectionFccUc((char)piVar2[iVar3 + 4],0,0);
      DemoInitPCParam__10BtlSaveSecFii(piVar2[iVar3 + 4],aiStack_90[iVar1 * 8 + 1]);
    }
  }
  m_mons = m_mons + 1;
  if (2 < m_mons) {
    m_mons = 0;
  }
  *(u32 *)(iStack_30 + 0x1c) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_30,0x80,0);
  *(u32 *)(iStack_30 + 0x40) = uStack_20;
  *(u32 *)(iStack_30 + 0x44) = uStack_10;
  return;
}

// JP: 0x003ab800  Polling__17openingBattleDemoFv  size 0x4c0
// openingBattleDemo::Polling()
u64 Polling__17openingBattleDemoFv(openingBattleDemo *this)
{
  u16 uVar1;
  short sVar2;
  int iVar3;
  u32 uVar4;
  long lVar5;
  u64 uVar6;
  iVar3 = GetActive__4CPadFi(0);
  uVar1 = *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar3 + 4)] + 0x6c);
  iVar3 = this->state;
  if (iVar3 == 4) {
    this->finished = 1;
  }
  else if (iVar3 == 3) {
    BattleEnd__9BtlSocketFv(ourBtlSocket__9BtlSocket);
    if (this->btl_done != '\0') {
      if (this->banner != 0) {
        DelayDeleteRequest__6prim2DFv(this->banner);
        this->banner = 0;
      }
      if (this->p38 != 0) {
        DelayDeleteRequest__6prim2DFv(this->p38);
        this->p38 = 0;
      }
      if (this->p3c != 0) {
        DelayDeleteRequest__6prim2DFv(this->p3c);
        this->p3c = 0;
      }
      this->timer = 0;
      this->state = 4;
    }
  }
  else if (iVar3 == 2) {
    this->timer = this->timer + 1;
    if ((300 < this->timer) && ((uVar1 & 0x2008) != 0)) {
      this->not_skipped = 0;
      this->timer = 0x708;
    }
    if ((this->timer < 0x708) && (sVar2 = GetFaderMode__8BtlFaderFv(), sVar2 == 3)) {
      lVar5 = isFade__8primFadeFv(this->banner + 0x20);
      if (lVar5 == 0) {
        fadeout__8primFadeFi(this->banner + 0x20,0x20);
      }
      this->state = 3;
    }
    if (0x707 < this->timer) {
      lVar5 = isFade__8primFadeFv(this->banner + 0x20);
      if (lVar5 == 0) {
        fadeout__8primFadeFi(this->banner + 0x20,0x20);
      }
      this->state = 3;
    }
  }
  else if (iVar3 == 1) {
    InitBtlSocket__Fv();
    iVar3 = ourBtlSocket__9BtlSocket;
    *(code **)(ourBtlSocket__9BtlSocket + 0x164) = BtlCallBack__17openingBattleDemoFiiPv;
    *(int *)(iVar3 + 0x160) = this;
    *(u8 *)(ourBtlSocket__9BtlSocket + 0x168) = 1;
    *(u32 *)(ourBtlSocket__9BtlSocket + 0x15c) = this->battle_no;
    SetBtlBGMNumber__9BtlSocketFi(ourBtlSocket__9BtlSocket,this->bgm);
    SetPC__9BtlSocketFiPc
              (ourBtlSocket__9BtlSocket,
               *(u8 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x95),
               *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x96);
    uVar6 = GetRegDat__9RegDatApiFiii(0x2f,this->monset,0xffffffffffffffff);
    SetMonsterSet__9BtlSocketFiP9MONSETTbl(ourBtlSocket__9BtlSocket,1,uVar6);
    this->state = 2;
    this->timer = 0;
  }
  else if ((iVar3 == 0) && (this->go != '\0')) {
    lVar5 = __nw__FUi(0x260);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__6prim2DFi(lVar5,0xe);
    }
    this->banner = uVar4;
    *(u32 *)(this->banner + 0x30) = this->tex;
    setDisp__6prim2DFiffff
              (0,0x43a00000,0x3f800000,0x3f800000,this->banner,
               this->layer);
    setUV__6prim2DFiiii(this->banner,1,1,0xd2,0x78);
    setRGBA__6prim2DFiiii(this->banner,0x7f,0x7f,0x7f,0x7f);
    fadein__8primFadeFi(this->banner + 0x20,0x10);
    this->state = 1;
  }
  return 0;
}

// JP: 0x003abcc0  BtlCallBack__17openingBattleDemoFiiPv  size 0x38
// openingBattleDemo::BtlCallBack(int, int, void*)
void BtlCallBack__17openingBattleDemoFiiPv(openingBattleDemo *this,u32 param_2,u32 param_3)
{
  BtlCBFunc__17openingBattleDemoFii(param_3,this,param_2);
  return;
}

// JP: 0x003abd00  BtlCBFunc__17openingBattleDemoFii  size 0x40
// openingBattleDemo::BtlCBFunc(int, int)
u32 BtlCBFunc__17openingBattleDemoFii(openingBattleDemo *this,int param_2)
{
  if (param_2 == 0) {
    this->btl_done = 1;
  }
  return 1;
}
