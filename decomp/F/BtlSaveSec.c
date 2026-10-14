/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00345e60  GetCommonParam__10BtlSaveSecFv  size 0xc
// BtlSaveSec::GetCommonParam()
u32 GetCommonParam__10BtlSaveSecFv(void)
{
  return ourBtlSaveDat__10BtlSaveSec;
}

// JP: 0x0037d990  __ct__10BtlSaveSecFv  size 0x70
// BtlSaveSec::BtlSaveSec()
u64 __ct__10BtlSaveSecFv(BtlSaveSec *this)
{
  __ct__15SaveDataSectionFv();
  ourBtlSaveSec__10BtlSaveSec = (int *)this;
  *ourBtlSaveSec__10BtlSaveSec = (int)__vt__10BtlSaveSec;
  CreateSection__15SaveDataSectionFPCcUiUs(this,0x3ffaf0,0x1d44,0);
  ourBtlSaveDat__10BtlSaveSec = GetSection__15SaveDataSectionFv(ourBtlSaveSec__10BtlSaveSec);
  (**(code **)(*ourBtlSaveSec__10BtlSaveSec + 0xc))();
  return this;
}

// JP: 0x0037da10  __dt__10BtlSaveSecFv  size 0x68
// BtlSaveSec::~BtlSaveSec()
long __dt__10BtlSaveSecFv(BtlSaveSec *this,short param_2)
{
  if (this != 0) {
    *(u32 *)this = __vt__10BtlSaveSec;
    ourBtlSaveSec__10BtlSaveSec = 0;
    ourBtlSaveDat__10BtlSaveSec = 0;
    __dt__15SaveDataSectionFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0037da80  SetDefault__10BtlSaveSecFv  size 0x44
// BtlSaveSec::SetDefault()
void SetDefault__10BtlSaveSecFv(void)
{
  char cVar1;
  memset(ourBtlSaveDat__10BtlSaveSec,0,0x1d44);
  cVar1 = CheckRegDat__9RegDatApiFv();
  if (cVar1 != '\0') {
    SetSceneInit__10BtlSaveSecFib(0,0);
  }
  return;
}

// JP: 0x0037dad0  SetSection__10BtlSaveSecFP19_SaveDataSectionHdrPUc  size 0x10
// BtlSaveSec::SetSection(_SaveDataSectionHdr*, unsigned char*)
void * SetSection__10BtlSaveSecFP19_SaveDataSectionHdrPUc
                 (BtlSaveSec *this,u64 param_2,void *param_3)
{
  void *pvVar1;
  pvVar1 = memcpy(ourBtlSaveDat__10BtlSaveSec,param_3,0x1d44);
  return pvVar1;
}

// JP: 0x0037dae0  CheckVersion__10BtlSaveSecFUs  size 0x30
// BtlSaveSec::CheckVersion(unsigned short)
bool CheckVersion__10BtlSaveSecFUs(BtlSaveSec *this,short param_2)
{
  return param_2 == 0;
}

// JP: 0x0037db10  SetSceneInit__10BtlSaveSecFib  size 0x13d8
// BtlSaveSec::SetSceneInit(int, bool)
/* WARNING: Removing unreachable block (ram,0x0037e2f4) */
/* WARNING: Removing unreachable block (ram,0x0037e2fc) */
/* WARNING: Removing unreachable block (ram,0x0037e7fc) */
/* WARNING: Removing unreachable block (ram,0x0037e804) */
/* WARNING: Removing unreachable block (ram,0x0037de34) */
/* WARNING: Removing unreachable block (ram,0x0037de3c) */
/* WARNING: Removing unreachable block (ram,0x0037ed74) */
/* WARNING: Removing unreachable block (ram,0x0037ed7c) */
void SetSceneInit__10BtlSaveSecFib(BtlSaveSec *this)
{
  char cVar1;
  int iVar2;
  u8 *puVar3;
  int iVar4;
  uint uVar5;
  ulong uVar6;
  int iVar7;
  u8 bVar8;
  uint uVar9;
  int iVar10;
  if (this == 3) {
    memset(ourBtlSaveDat__10BtlSaveSec,0,0x1d44);
    *ourBtlSaveDat__10BtlSaveSec = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) = 0;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 2) = 3;
    SetComboMenuMode__10BtlSaveSecFb(1);
    SetSoulSystemMode__10BtlSaveSecFb(1);
    SetYoahismMode__10BtlSaveSecFb(0);
    InitPCParam__10BtlSaveSecFii(0,3);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x43] = 0x14b4;
    ourBtlSaveDat__10BtlSaveSec[0x47] = 0x1d4c;
    ourBtlSaveDat__10BtlSaveSec[0x48] = 0x1900;
    InitPCParam__10BtlSaveSecFii(1,3);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0xa2] = 0x14b4;
    ourBtlSaveDat__10BtlSaveSec[0xa7] = 6000;
    ourBtlSaveDat__10BtlSaveSec[0xa8] = 0x13ec;
    InitPCParam__10BtlSaveSecFii(5,3);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x222] = 0x1d4c;
    ourBtlSaveDat__10BtlSaveSec[0x223] = 6000;
    ourBtlSaveDat__10BtlSaveSec[0x228] = 0x15e0;
    SetPCModelNum__10BtlSaveSecFii(5,5);
    InitPCParam__10BtlSaveSecFii(6,3);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x282] = 0x1900;
    ourBtlSaveDat__10BtlSaveSec[0x283] = 0x13ec;
    ourBtlSaveDat__10BtlSaveSec[0x287] = 0x15e0;
    ComboSkillFlag__10BtlSaveSec = 8;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x6a6) = 0x802;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x71c) = 3;
    puVar3 = (u8 *)GetRegDat__9RegDatApiFiii(0x3f,3,0xffffffffffffffff);
    iVar4 = GetRegCnt__9RegDatApiFii(0x3f,3);
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        switch(*puVar3) {
        case 1:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x944) = puVar3[1];
          break;
        case 2:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x9c4) = puVar3[1];
          break;
        case 3:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa24) = puVar3[1];
          break;
        case 4:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa54) = puVar3[1];
          break;
        case 5:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037ec8c;
            }
          }
          else {
LAB_0037ec8c:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) | bVar8;
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037ecd0;
            }
          }
          else {
LAB_0037ecd0:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) | bVar8;
          break;
        case 6:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xab8) = puVar3[1];
          break;
        case 7:
          ourBtlSaveDat__10BtlSaveSec[0x6d4] =
               ourBtlSaveDat__10BtlSaveSec[0x6d4] | (u16)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 8:
          *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) =
               *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 9:
          iVar10 = (int)(uint)*(u16 *)(puVar3 + 2) >> 3;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 7));
          break;
        case 10:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037edc4;
            }
          }
          else {
LAB_0037edc4:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) | bVar8;
        }
        iVar7 = iVar7 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar7 < iVar4);
    }
    iVar4 = 0;
    iVar7 = 0;
    do {
      bVar8 = *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0x44);
      if (((bVar8 & 1) != 0) && ((long)((ulong)bVar8 << 0x3e) < 0)) {
        AddEquip__10BtlSaveSecFi(iVar4);
        iVar10 = 0;
        do {
          cVar1 = *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + iVar7 + 0x76);
          uVar6 = (ulong)cVar1;
          uVar5 = (uint)(uVar6 & 7);
          if (-1 < (long)uVar6) {
            if ((long)uVar6 < 0) {
              if ((uVar6 & 7) != 0) {
                uVar5 = uVar5 - 8;
              }
              uVar5 = uVar5 & 0x1f;
            }
            iVar2 = ((int)cVar1 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
            *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar2 + 0xaae) =
                 *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar2 + 0xaae) | (u8)(1 << uVar5);
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < 8);
      }
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + 0xc0;
    } while (iVar4 < 0xc);
    if (sm_pSubstance__15SaveMenuSection != 0) {
      SceneInit__15SaveMenuSectionFi(3);
    }
  }
  else if (this == 2) {
    memset(ourBtlSaveDat__10BtlSaveSec,0,0x1d44);
    *ourBtlSaveDat__10BtlSaveSec = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) = 0;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 2) = 2;
    SetComboMenuMode__10BtlSaveSecFb(1);
    SetSoulSystemMode__10BtlSaveSecFb(1);
    SetYoahismMode__10BtlSaveSecFb(0);
    InitPCParam__10BtlSaveSecFii(0,2);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x44] = 0x170c;
    ourBtlSaveDat__10BtlSaveSec[0x47] = 0x1c84;
    ourBtlSaveDat__10BtlSaveSec[0x48] = 0x1004;
    InitPCParam__10BtlSaveSecFii(2,2);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x102] = 0x170c;
    ourBtlSaveDat__10BtlSaveSec[0x107] = 0x13ec;
    ourBtlSaveDat__10BtlSaveSec[0x108] = 0x1068;
    InitPCParam__10BtlSaveSecFii(5,2);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x222] = 0x1c84;
    ourBtlSaveDat__10BtlSaveSec[0x224] = 0x13ec;
    ourBtlSaveDat__10BtlSaveSec[0x228] = 0x157c;
    SetPCModelNum__10BtlSaveSecFii(5,5);
    InitPCParam__10BtlSaveSecFii(6,2);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x262) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x282] = 0x1004;
    ourBtlSaveDat__10BtlSaveSec[0x284] = 0x1068;
    ourBtlSaveDat__10BtlSaveSec[0x287] = 0x157c;
    ComboSkillFlag__10BtlSaveSec = 4;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x6a6) = 2;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x71c) = 3;
    puVar3 = (u8 *)GetRegDat__9RegDatApiFiii(0x3f,2,0xffffffffffffffff);
    iVar4 = GetRegCnt__9RegDatApiFii(0x3f,2);
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        switch(*puVar3) {
        case 1:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x944) = puVar3[1];
          break;
        case 2:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x9c4) = puVar3[1];
          break;
        case 3:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa24) = puVar3[1];
          break;
        case 4:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa54) = puVar3[1];
          break;
        case 5:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037e714;
            }
          }
          else {
LAB_0037e714:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) | bVar8;
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037e758;
            }
          }
          else {
LAB_0037e758:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) | bVar8;
          break;
        case 6:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xab8) = puVar3[1];
          break;
        case 7:
          ourBtlSaveDat__10BtlSaveSec[0x6d4] =
               ourBtlSaveDat__10BtlSaveSec[0x6d4] | (u16)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 8:
          *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) =
               *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 9:
          iVar10 = (int)(uint)*(u16 *)(puVar3 + 2) >> 3;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 7));
          break;
        case 10:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037e84c;
            }
          }
          else {
LAB_0037e84c:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) | bVar8;
        }
        iVar7 = iVar7 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar7 < iVar4);
    }
    iVar4 = 0;
    iVar7 = 0;
    do {
      bVar8 = *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0x44);
      if (((bVar8 & 1) != 0) && ((long)((ulong)bVar8 << 0x3e) < 0)) {
        AddEquip__10BtlSaveSecFi(iVar4);
        iVar10 = 0;
        do {
          cVar1 = *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + iVar7 + 0x76);
          uVar6 = (ulong)cVar1;
          uVar5 = (uint)(uVar6 & 7);
          if (-1 < (long)uVar6) {
            if ((long)uVar6 < 0) {
              if ((uVar6 & 7) != 0) {
                uVar5 = uVar5 - 8;
              }
              uVar5 = uVar5 & 0x1f;
            }
            iVar2 = ((int)cVar1 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
            *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar2 + 0xaae) =
                 *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar2 + 0xaae) | (u8)(1 << uVar5);
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < 8);
      }
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + 0xc0;
    } while (iVar4 < 0xc);
    if (sm_pSubstance__15SaveMenuSection != 0) {
      SceneInit__15SaveMenuSectionFi(2);
    }
  }
  else if (this == 1) {
    memset(ourBtlSaveDat__10BtlSaveSec,0,0x1d44);
    *ourBtlSaveDat__10BtlSaveSec = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) = 0;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 2) = 1;
    SetComboMenuMode__10BtlSaveSecFb();
    SetSoulSystemMode__10BtlSaveSecFb(1);
    SetYoahismMode__10BtlSaveSecFb(0);
    InitPCParam__10BtlSaveSecFii(0,1);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x22) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x43] = 0x1450;
    ourBtlSaveDat__10BtlSaveSec[0x44] = 0x15e0;
    InitPCParam__10BtlSaveSecFii(1,1);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x82) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0xa2] = 0x1450;
    ourBtlSaveDat__10BtlSaveSec[0xa4] = 0x1194;
    InitPCParam__10BtlSaveSecFii(2,1);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe2) & 0xfd | 2;
    ourBtlSaveDat__10BtlSaveSec[0x102] = 0x15e0;
    ourBtlSaveDat__10BtlSaveSec[0x103] = 0x1194;
    ComboSkillFlag__10BtlSaveSec = 8;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x6a6) = 0x800;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x71c) = 3;
    puVar3 = (u8 *)GetRegDat__9RegDatApiFiii(0x3f,1,0xffffffffffffffff);
    iVar4 = GetRegCnt__9RegDatApiFii(0x3f,1);
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        switch(*puVar3) {
        case 1:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x944) = puVar3[1];
          break;
        case 2:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x9c4) = puVar3[1];
          break;
        case 3:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa24) = puVar3[1];
          break;
        case 4:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa54) = puVar3[1];
          break;
        case 5:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037e254;
            }
          }
          else {
LAB_0037e254:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) | bVar8;
          break;
        case 6:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xab8) = puVar3[1];
          break;
        case 7:
          ourBtlSaveDat__10BtlSaveSec[0x6d4] =
               ourBtlSaveDat__10BtlSaveSec[0x6d4] | (u16)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 8:
          *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) =
               *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 9:
          iVar10 = (int)(uint)*(u16 *)(puVar3 + 2) >> 3;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 7));
          break;
        case 10:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037e344;
            }
          }
          else {
LAB_0037e344:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) | bVar8;
        }
        iVar7 = iVar7 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar7 < iVar4);
    }
    iVar4 = 0;
    iVar7 = 0;
    do {
      bVar8 = *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0x44);
      if (((bVar8 & 1) != 0) && ((long)((ulong)bVar8 << 0x3e) < 0)) {
        AddEquip__10BtlSaveSecFi(iVar4);
      }
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + 0xc0;
    } while (iVar4 < 0xc);
    if (sm_pSubstance__15SaveMenuSection != 0) {
      SceneInit__15SaveMenuSectionFi(1);
    }
  }
  else if (this == 0) {
    memset(ourBtlSaveDat__10BtlSaveSec,0,0x1d44);
    *ourBtlSaveDat__10BtlSaveSec = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) = 0;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 2) = 0;
    SetComboMenuMode__10BtlSaveSecFb(0);
    SetSoulSystemMode__10BtlSaveSecFb(0);
    SetYoahismMode__10BtlSaveSecFb(0);
    InitPCParam__10BtlSaveSecFii(5,0);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x202) & 0xfd | 2;
    InitPCParam__10BtlSaveSecFii(0xb,0);
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x442) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x442) & 0xfe | 1;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x442) =
         *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x442) & 0xfd | 2;
    *(u32 *)(ourBtlSaveDat__10BtlSaveSec + 0x71c) = 3;
    puVar3 = (u8 *)GetRegDat__9RegDatApiFiii(0x3f,0,0xffffffffffffffff);
    iVar4 = GetRegCnt__9RegDatApiFii(0x3f,0);
    iVar7 = 0;
    if (0 < iVar4) {
      do {
        switch(*puVar3) {
        case 1:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x944) = puVar3[1];
          break;
        case 2:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0x9c4) = puVar3[1];
          break;
        case 3:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa24) = puVar3[1];
          break;
        case 4:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xa54) = puVar3[1];
          break;
        case 5:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037dd4c;
            }
          }
          else {
LAB_0037dd4c:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaa4) | bVar8;
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037dd90;
            }
          }
          else {
LAB_0037dd90:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xaae) | bVar8;
          break;
        case 6:
          *(u8 *)
           ((int)ourBtlSaveDat__10BtlSaveSec +
           (uint)*(u16 *)(puVar3 + 2) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200
           + 0xab8) = puVar3[1];
          break;
        case 7:
          ourBtlSaveDat__10BtlSaveSec[0x6d4] =
               ourBtlSaveDat__10BtlSaveSec[0x6d4] | (u16)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 8:
          *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) =
               *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0x6d7) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 0x1f));
          break;
        case 9:
          iVar10 = (int)(uint)*(u16 *)(puVar3 + 2) >> 3;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0xdab) |
               (u8)(1 << (*(u16 *)(puVar3 + 2) & 7));
          break;
        case 10:
          uVar9 = (uint)*(u16 *)(puVar3 + 2);
          uVar5 = uVar9 & 7;
          if ((int)uVar9 < 0) {
            bVar8 = (u8)(1 << uVar5);
            if ((*(u16 *)(puVar3 + 2) & 7) != 0) {
              uVar5 = uVar5 - 8;
              goto LAB_0037de84;
            }
          }
          else {
LAB_0037de84:
            bVar8 = (u8)(1 << (uVar5 & 0x1f));
          }
          iVar10 = ((int)uVar9 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
          *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) =
               *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar10 + 0x984) | bVar8;
        }
        iVar7 = iVar7 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar7 < iVar4);
    }
    AddEquip__10BtlSaveSecFi(5);
    iVar4 = 0;
    do {
      cVar1 = *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar4 + 0x436);
      uVar6 = (ulong)cVar1;
      uVar5 = (uint)(uVar6 & 7);
      if (-1 < (long)uVar6) {
        bVar8 = (u8)(1 << uVar5);
        if ((long)uVar6 < 0) {
          if ((uVar6 & 7) != 0) {
            uVar5 = uVar5 - 8;
          }
          bVar8 = (u8)(1 << (uVar5 & 0x1f));
        }
        iVar7 = ((int)cVar1 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
        *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0xaae) =
             *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0xaae) | bVar8;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    AddEquip__10BtlSaveSecFi(0xb);
    iVar4 = 0;
    do {
      cVar1 = *(char *)((int)ourBtlSaveDat__10BtlSaveSec + iVar4 + 0x8b6);
      uVar6 = (ulong)cVar1;
      uVar5 = (uint)(uVar6 & 7);
      if (-1 < (long)uVar6) {
        if ((long)uVar6 < 0) {
          if ((uVar6 & 7) != 0) {
            uVar5 = uVar5 - 8;
          }
          uVar5 = uVar5 & 0x1f;
        }
        iVar7 = ((int)cVar1 >> 3) + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 1) * 0x200;
        *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0xaae) =
             *(u8 *)((int)ourBtlSaveDat__10BtlSaveSec + iVar7 + 0xaae) | (u8)(1 << uVar5);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    if (sm_pSubstance__15SaveMenuSection != 0) {
      SceneInit__15SaveMenuSectionFi(0);
    }
  }
  return;
}

// JP: 0x0037eef0  SetYoahismMode__10BtlSaveSecFb  size 0x24
// BtlSaveSec::SetYoahismMode(bool)
void SetYoahismMode__10BtlSaveSecFb(BtlSaveSec *this)
{
  *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) =
       *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) & 0xfb | (this & 1) << 2;
  return;
}

// JP: 0x0037ef20  SetSoulSystemMode__10BtlSaveSecFb  size 0x24
// BtlSaveSec::SetSoulSystemMode(bool)
void SetSoulSystemMode__10BtlSaveSecFb(BtlSaveSec *this)
{
  *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 3) =
       *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 3) & 0xfb | (this & 1) << 2;
  return;
}

// JP: 0x0037ef50  SetComboMenuMode__10BtlSaveSecFb  size 0x20
// BtlSaveSec::SetComboMenuMode(bool)
void SetComboMenuMode__10BtlSaveSecFb(BtlSaveSec *this)
{
  *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 3) =
       *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 3) & 0xfe | this & 1;
  return;
}

// JP: 0x0037ef70  AddEquip__10BtlSaveSecFi  size 0x138
// BtlSaveSec::AddEquip(int)
void AddEquip__10BtlSaveSecFi(BtlSaveSec *this)
{
  char cVar1;
  uint uVar2;
  u8 bVar3;
  int iVar4;
  int iVar5;
  ulong uVar6;
  this = this * 0xc0;
  cVar1 = *(char *)(this + ourBtlSaveDat__10BtlSaveSec + 0x71);
  if (-1 < cVar1) {
    iVar4 = (int)cVar1 +
            (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(char *)(iVar4 + 0x9c4) = *(char *)(iVar4 + 0x9c4) + '\x01';
  }
  cVar1 = *(char *)(this + ourBtlSaveDat__10BtlSaveSec + 0x72);
  if (-1 < cVar1) {
    iVar4 = (int)cVar1 +
            (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(char *)(iVar4 + 0xa24) = *(char *)(iVar4 + 0xa24) + '\x01';
  }
  iVar4 = 0;
  do {
    cVar1 = *(char *)(this + ourBtlSaveDat__10BtlSaveSec + iVar4 + 0x73);
    if (-1 < cVar1) {
      iVar5 = ourBtlSaveDat__10BtlSaveSec + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200
              + (int)cVar1;
      *(char *)(iVar5 + 0xa54) = *(char *)(iVar5 + 0xa54) + '\x01';
    }
    iVar4 = iVar4 + 1;
    iVar5 = 0;
  } while (iVar4 < 3);
  do {
    cVar1 = *(char *)(this + ourBtlSaveDat__10BtlSaveSec + iVar5 + 0x76);
    uVar6 = (ulong)cVar1;
    uVar2 = (uint)(uVar6 & 7);
    if (-1 < (long)uVar6) {
      bVar3 = (u8)(1 << uVar2);
      if ((long)uVar6 < 0) {
        if ((uVar6 & 7) != 0) {
          uVar2 = uVar2 - 8;
        }
        bVar3 = (u8)(1 << (uVar2 & 0x1f));
      }
      iVar4 = ourBtlSaveDat__10BtlSaveSec + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200
              + ((int)cVar1 >> 3);
      *(u8 *)(iVar4 + 0xaa4) = *(u8 *)(iVar4 + 0xaa4) | bVar3;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 8);
  return;
}

// JP: 0x0037f0b0  InitPCParam__10BtlSaveSecFii  size 0x548
// BtlSaveSec::InitPCParam(int, int)
void InitPCParam__10BtlSaveSecFii(BtlSaveSec *this,u64 param_2)
{
  u16 uVar1;
  int iVar2;
  u16 *puVar3;
  char *__src;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  u8 *puVar8;
  u8 *__s;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  __s = (u8 *)(iVar2 + 0x44);
  memset(__s,0,0xc0);
  puVar3 = (u16 *)GetRegDat__9RegDatApiFiii((int)param_2 + 0x26,this,0xffffffffffffffff);
  *__s = *__s & 0xe3 | (*(u8 *)((int)puVar3 + 7) & 7) << 2;
  *__s = *__s & 0x1f | (u8)((uint)(((ulong)*(u8 *)((int)puVar3 + 7) << 0x3a) >> 0x3d) << 5);
  *(char *)(iVar2 + 0x46) = (char)*puVar3;
  uVar1 = puVar3[2];
  *(u16 *)(iVar2 + 0x4c) = uVar1;
  *(u16 *)(iVar2 + 0x4a) = uVar1;
  *(u16 *)(iVar2 + 0x48) = uVar1;
  __src = (char *)GetRegDat__9RegDatApiFiii(param_2,this,0xffffffffffffffff);
  strcpy((char *)(iVar2 + 0x4e),__src);
  iVar5 = 0;
  *(u8 *)(iVar2 + 0x71) = *(u8 *)(puVar3 + 4);
  *(u8 *)(iVar2 + 0x72) = *(u8 *)((int)puVar3 + 9);
  *(u8 *)(iVar2 + 0x73) = *(u8 *)(puVar3 + 5);
  *(u8 *)(iVar2 + 0x74) = *(u8 *)((int)puVar3 + 0xb);
  *(u8 *)(iVar2 + 0x75) = *(u8 *)(puVar3 + 6);
  *(u8 *)(iVar2 + 0x76) = *(u8 *)((int)puVar3 + 0xd);
  *(u8 *)(iVar2 + 0x77) = *(u8 *)(puVar3 + 7);
  *(u8 *)(iVar2 + 0x78) = *(u8 *)((int)puVar3 + 0xf);
  *(u8 *)(iVar2 + 0x79) = *(u8 *)(puVar3 + 8);
  *(u8 *)(iVar2 + 0x7a) = *(u8 *)((int)puVar3 + 0x11);
  *(u8 *)(iVar2 + 0x7b) = *(u8 *)(puVar3 + 9);
  *(u8 *)(iVar2 + 0x7c) = *(u8 *)((int)puVar3 + 0x13);
  *(u8 *)(iVar2 + 0x7d) = *(u8 *)(puVar3 + 10);
  *(short *)(iVar2 + 0x7e) = (short)*(u32 *)(puVar3 + 0xc);
  do {
    __s[0x40] = 0;
    __s[0x41] = 0;
    __s[0x42] = 0;
    __s[0x43] = 0;
    iVar5 = iVar5 + 6;
    __s[0x44] = 0;
    __s[0x45] = 0;
    __s[0x46] = 0;
    __s[0x47] = 0;
    __s[0x48] = 0;
    __s[0x49] = 0;
    __s[0x4a] = 0;
    __s[0x4b] = 0;
    __s = __s + 0xc;
  } while (iVar5 < 0xc);
  *(u8 *)(iVar2 + 0x9c) = *(u8 *)(iVar2 + 0x9c) & 0xf8 | *(u8 *)((int)puVar3 + 0x15) & 7;
  *(u8 *)(iVar2 + 0x9c) = *(u8 *)(iVar2 + 0x9c) & 199 | (*(u8 *)((int)puVar3 + 0x15) & 7) << 3
  ;
  *(u8 *)(iVar2 + 0xa8) = 0xff;
  PCLevelInit__10BtlSaveSecFii(this,*(u8 *)(puVar3 + 3));
  iVar5 = ourBtlSaveDat__10BtlSaveSec;
  iVar4 = (int)this * 0x10;
  iVar6 = ourBtlSaveDat__10BtlSaveSec + 0xf44;
  puVar8 = (u8 *)(iVar6 + iVar4);
  *puVar8 = 0;
  *(u16 *)(puVar8 + 2) = 0xffff;
  puVar8[1] = 0;
  if ((this == 9) || (this == 10)) {
    *(u8 *)(iVar4 + iVar6 + 4) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 5) = 0xff;
  }
  else {
    puVar8[4] = 0;
    puVar8[5] = 1;
  }
  iVar7 = iVar4 + iVar6;
  *(u16 *)(iVar7 + 6) = 0xffff;
  if ((this == 8) || (this == 10)) {
    *(u8 *)(iVar4 + iVar6 + 8) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 9) = 0xff;
  }
  else {
    *(u8 *)(iVar7 + 8) = 0;
    *(u8 *)(iVar7 + 9) = 2;
  }
  iVar7 = iVar4 + iVar6;
  *(u16 *)(iVar7 + 10) = 0xffff;
  if ((this == 8) || (this == 9)) {
    *(u8 *)(iVar4 + iVar6 + 0xc) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 0xd) = 0xff;
  }
  else {
    *(u8 *)(iVar7 + 0xc) = 0;
    *(u8 *)(iVar7 + 0xd) = 3;
  }
  *(u16 *)(iVar4 + iVar6 + 0xe) = 0xffff;
  if (this == 0) {
    iVar5 = 0;
    iVar4 = 0;
    do {
      *(u8 *)(iVar6 + 0xc0) = 0;
      *(u16 *)(iVar6 + 0xc2) = 0xffff;
      *(u8 *)(iVar6 + 0xc1) = 0;
      *(u8 *)(iVar6 + 0xc4) = 0;
      *(u16 *)(iVar6 + 0xc6) = 0xffff;
      *(u8 *)(iVar6 + 0xc5) = 1;
      *(u8 *)(iVar6 + 200) = 0;
      *(u16 *)(iVar6 + 0xca) = 0xffff;
      *(u8 *)(iVar6 + 0xc9) = 2;
      *(u8 *)(iVar6 + 0xcc) = 0;
      *(u16 *)(iVar6 + 0xce) = 0xffff;
      *(u8 *)(iVar6 + 0xcd) = 3;
      iVar6 = iVar6 + 0x10;
      *(u32 *)(ourBtlSaveDat__10BtlSaveSec + iVar4 + 0xd50) = 0;
      iVar4 = iVar4 + 4;
      iVar7 = ourBtlSaveDat__10BtlSaveSec + iVar5;
      iVar5 = iVar5 + 1;
      *(u8 *)(iVar7 + 0xd94) = 1;
    } while (iVar5 < 0xf);
  }
  else if (this == 6) {
    *(u8 *)(iVar5 + 0x1114) = 0;
    *(u16 *)(iVar5 + 0x1116) = 0xffff;
    *(u8 *)(iVar5 + 0x1115) = 0;
    *(u8 *)(iVar5 + 0x1118) = 0;
    *(u16 *)(iVar5 + 0x111a) = 0xffff;
    *(u8 *)(iVar5 + 0x1119) = 1;
    *(u8 *)(iVar5 + 0x111c) = 0;
    *(u16 *)(iVar5 + 0x111e) = 0xffff;
    *(u8 *)(iVar5 + 0x111d) = 2;
    *(u8 *)(iVar5 + 0x1120) = 0;
    *(u16 *)(iVar5 + 0x1122) = 0xffff;
    *(u8 *)(iVar5 + 0x1121) = 3;
  }
  else {
    iVar5 = iVar5 + 0x1034;
    if (this == 7) {
      iVar4 = 0xf;
      iVar6 = 0x3c;
      do {
        *(u8 *)(iVar5 + 0xc0) = 0;
        *(u16 *)(iVar5 + 0xc2) = 0xffff;
        *(u8 *)(iVar5 + 0xc1) = 0;
        *(u8 *)(iVar5 + 0xc4) = 0;
        *(u16 *)(iVar5 + 0xc6) = 0xffff;
        *(u8 *)(iVar5 + 0xc5) = 1;
        *(u8 *)(iVar5 + 200) = 0;
        *(u16 *)(iVar5 + 0xca) = 0xffff;
        *(u8 *)(iVar5 + 0xc9) = 2;
        *(u8 *)(iVar5 + 0xcc) = 0;
        *(u16 *)(iVar5 + 0xce) = 0xffff;
        *(u8 *)(iVar5 + 0xcd) = 3;
        iVar5 = iVar5 + 0x10;
        *(u32 *)(ourBtlSaveDat__10BtlSaveSec + iVar6 + 0xd50) = 0;
        iVar6 = iVar6 + 4;
        iVar7 = ourBtlSaveDat__10BtlSaveSec + iVar4;
        iVar4 = iVar4 + 1;
        *(u8 *)(iVar7 + 0xd94) = 1;
      } while (iVar4 < 0x11);
    }
  }
  if (this == 6) {
    *(char *)(ourBtlSaveDat__10BtlSaveSec + 0xe37) = (char)*(u16 *)(iVar2 + 0x7e);
  }
  else if (this == 5) {
    *(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 0;
    *(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) = *(u16 *)(iVar2 + 0x7e);
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 1) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 2) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 4) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 2;
    }
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 8) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x10) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x20) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 2;
    }
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x40) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x80) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x100) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 2;
    }
  }
  return;
}

// JP: 0x0037f600  DemoInitPCParam__10BtlSaveSecFii  size 0x548
// BtlSaveSec::DemoInitPCParam(int, int)
void DemoInitPCParam__10BtlSaveSecFii(long param_1,int this)
{
  u16 uVar1;
  int iVar2;
  u16 *puVar3;
  char *__src;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  u8 *puVar8;
  u8 *__s;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)param_1 * 0xc0;
  __s = (u8 *)(iVar2 + 0x44);
  memset(__s,0,0xc0);
  puVar3 = (u16 *)GetRegDat__9RegDatApiFiii(this + 0x41,param_1,0xffffffffffffffff);
  *__s = *__s & 0xe3 | (*(u8 *)((int)puVar3 + 7) & 7) << 2;
  *__s = *__s & 0x1f | (u8)((uint)(((ulong)*(u8 *)((int)puVar3 + 7) << 0x3a) >> 0x3d) << 5);
  *(char *)(iVar2 + 0x46) = (char)*puVar3;
  uVar1 = puVar3[2];
  *(u16 *)(iVar2 + 0x4c) = uVar1;
  *(u16 *)(iVar2 + 0x4a) = uVar1;
  *(u16 *)(iVar2 + 0x48) = uVar1;
  __src = (char *)GetRegDat__9RegDatApiFiii(this + 0x13,param_1,0xffffffffffffffff);
  strcpy((char *)(iVar2 + 0x4e),__src);
  iVar5 = 0;
  *(u8 *)(iVar2 + 0x71) = *(u8 *)(puVar3 + 4);
  *(u8 *)(iVar2 + 0x72) = *(u8 *)((int)puVar3 + 9);
  *(u8 *)(iVar2 + 0x73) = *(u8 *)(puVar3 + 5);
  *(u8 *)(iVar2 + 0x74) = *(u8 *)((int)puVar3 + 0xb);
  *(u8 *)(iVar2 + 0x75) = *(u8 *)(puVar3 + 6);
  *(u8 *)(iVar2 + 0x76) = *(u8 *)((int)puVar3 + 0xd);
  *(u8 *)(iVar2 + 0x77) = *(u8 *)(puVar3 + 7);
  *(u8 *)(iVar2 + 0x78) = *(u8 *)((int)puVar3 + 0xf);
  *(u8 *)(iVar2 + 0x79) = *(u8 *)(puVar3 + 8);
  *(u8 *)(iVar2 + 0x7a) = *(u8 *)((int)puVar3 + 0x11);
  *(u8 *)(iVar2 + 0x7b) = *(u8 *)(puVar3 + 9);
  *(u8 *)(iVar2 + 0x7c) = *(u8 *)((int)puVar3 + 0x13);
  *(u8 *)(iVar2 + 0x7d) = *(u8 *)(puVar3 + 10);
  *(short *)(iVar2 + 0x7e) = (short)*(u32 *)(puVar3 + 0xc);
  do {
    __s[0x40] = 0;
    __s[0x41] = 0;
    __s[0x42] = 0;
    __s[0x43] = 0;
    iVar5 = iVar5 + 6;
    __s[0x44] = 0;
    __s[0x45] = 0;
    __s[0x46] = 0;
    __s[0x47] = 0;
    __s[0x48] = 0;
    __s[0x49] = 0;
    __s[0x4a] = 0;
    __s[0x4b] = 0;
    __s = __s + 0xc;
  } while (iVar5 < 0xc);
  *(u8 *)(iVar2 + 0x9c) = *(u8 *)(iVar2 + 0x9c) & 0xf8 | *(u8 *)((int)puVar3 + 0x15) & 7;
  *(u8 *)(iVar2 + 0x9c) = *(u8 *)(iVar2 + 0x9c) & 199 | (*(u8 *)((int)puVar3 + 0x15) & 7) << 3
  ;
  *(u8 *)(iVar2 + 0xa8) = 0xff;
  PCLevelInit__10BtlSaveSecFii(param_1,*(u8 *)(puVar3 + 3));
  iVar5 = ourBtlSaveDat__10BtlSaveSec;
  iVar4 = (int)param_1 * 0x10;
  iVar6 = ourBtlSaveDat__10BtlSaveSec + 0xf44;
  puVar8 = (u8 *)(iVar6 + iVar4);
  *puVar8 = 0;
  *(u16 *)(puVar8 + 2) = 0xffff;
  puVar8[1] = 0;
  if ((param_1 == 9) || (param_1 == 10)) {
    *(u8 *)(iVar4 + iVar6 + 4) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 5) = 0xff;
  }
  else {
    puVar8[4] = 0;
    puVar8[5] = 1;
  }
  iVar7 = iVar4 + iVar6;
  *(u16 *)(iVar7 + 6) = 0xffff;
  if ((param_1 == 8) || (param_1 == 10)) {
    *(u8 *)(iVar4 + iVar6 + 8) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 9) = 0xff;
  }
  else {
    *(u8 *)(iVar7 + 8) = 0;
    *(u8 *)(iVar7 + 9) = 2;
  }
  iVar7 = iVar4 + iVar6;
  *(u16 *)(iVar7 + 10) = 0xffff;
  if ((param_1 == 8) || (param_1 == 9)) {
    *(u8 *)(iVar4 + iVar6 + 0xc) = 0xff;
    *(u8 *)(iVar4 + iVar6 + 0xd) = 0xff;
  }
  else {
    *(u8 *)(iVar7 + 0xc) = 0;
    *(u8 *)(iVar7 + 0xd) = 3;
  }
  *(u16 *)(iVar4 + iVar6 + 0xe) = 0xffff;
  if (param_1 == 0) {
    iVar5 = 0;
    iVar4 = 0;
    do {
      *(u8 *)(iVar6 + 0xc0) = 0;
      *(u16 *)(iVar6 + 0xc2) = 0xffff;
      *(u8 *)(iVar6 + 0xc1) = 0;
      *(u8 *)(iVar6 + 0xc4) = 0;
      *(u16 *)(iVar6 + 0xc6) = 0xffff;
      *(u8 *)(iVar6 + 0xc5) = 1;
      *(u8 *)(iVar6 + 200) = 0;
      *(u16 *)(iVar6 + 0xca) = 0xffff;
      *(u8 *)(iVar6 + 0xc9) = 2;
      *(u8 *)(iVar6 + 0xcc) = 0;
      *(u16 *)(iVar6 + 0xce) = 0xffff;
      *(u8 *)(iVar6 + 0xcd) = 3;
      iVar6 = iVar6 + 0x10;
      *(u32 *)(ourBtlSaveDat__10BtlSaveSec + iVar4 + 0xd50) = 0;
      iVar4 = iVar4 + 4;
      iVar7 = ourBtlSaveDat__10BtlSaveSec + iVar5;
      iVar5 = iVar5 + 1;
      *(u8 *)(iVar7 + 0xd94) = 1;
    } while (iVar5 < 0xf);
  }
  else if (param_1 == 6) {
    *(u8 *)(iVar5 + 0x1114) = 0;
    *(u16 *)(iVar5 + 0x1116) = 0xffff;
    *(u8 *)(iVar5 + 0x1115) = 0;
    *(u8 *)(iVar5 + 0x1118) = 0;
    *(u16 *)(iVar5 + 0x111a) = 0xffff;
    *(u8 *)(iVar5 + 0x1119) = 1;
    *(u8 *)(iVar5 + 0x111c) = 0;
    *(u16 *)(iVar5 + 0x111e) = 0xffff;
    *(u8 *)(iVar5 + 0x111d) = 2;
    *(u8 *)(iVar5 + 0x1120) = 0;
    *(u16 *)(iVar5 + 0x1122) = 0xffff;
    *(u8 *)(iVar5 + 0x1121) = 3;
  }
  else {
    iVar5 = iVar5 + 0x1034;
    if (param_1 == 7) {
      iVar4 = 0xf;
      iVar6 = 0x3c;
      do {
        *(u8 *)(iVar5 + 0xc0) = 0;
        *(u16 *)(iVar5 + 0xc2) = 0xffff;
        *(u8 *)(iVar5 + 0xc1) = 0;
        *(u8 *)(iVar5 + 0xc4) = 0;
        *(u16 *)(iVar5 + 0xc6) = 0xffff;
        *(u8 *)(iVar5 + 0xc5) = 1;
        *(u8 *)(iVar5 + 200) = 0;
        *(u16 *)(iVar5 + 0xca) = 0xffff;
        *(u8 *)(iVar5 + 0xc9) = 2;
        *(u8 *)(iVar5 + 0xcc) = 0;
        *(u16 *)(iVar5 + 0xce) = 0xffff;
        *(u8 *)(iVar5 + 0xcd) = 3;
        iVar5 = iVar5 + 0x10;
        *(u32 *)(ourBtlSaveDat__10BtlSaveSec + iVar6 + 0xd50) = 0;
        iVar6 = iVar6 + 4;
        iVar7 = ourBtlSaveDat__10BtlSaveSec + iVar4;
        iVar4 = iVar4 + 1;
        *(u8 *)(iVar7 + 0xd94) = 1;
      } while (iVar4 < 0x11);
    }
  }
  if (param_1 == 6) {
    *(char *)(ourBtlSaveDat__10BtlSaveSec + 0xe37) = (char)*(u16 *)(iVar2 + 0x7e);
  }
  else if (param_1 == 5) {
    *(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 0;
    *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 0;
    *(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) = *(u16 *)(iVar2 + 0x7e);
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 1) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 2) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 4) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe34) = 2;
    }
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 8) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x10) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x20) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe35) = 2;
    }
    if ((((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x40) != 0) &&
        ((*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x80) != 0)) &&
       (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 1,
       (*(u16 *)(ourBtlSaveDat__10BtlSaveSec + 0xe32) & 0x100) != 0)) {
      *(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xe36) = 2;
    }
  }
  return;
}

// JP: 0x0037fb50  PCLevelInit__10BtlSaveSecFii  size 0x158
// BtlSaveSec::PCLevelInit(int, int)
void PCLevelInit__10BtlSaveSecFii(BtlSaveSec *this,int param_2)
{
  u8 uVar1;
  u16 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  iVar5 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  if ((this == 7) && ((long)((ulong)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) << 0x3c) < 0))
  {
    iVar4 = GetRegDat__9RegDatApiFiii(0x2a,0xc,0xffffffffffffffff);
  }
  else {
    iVar4 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  }
  iVar7 = 0;
  iVar6 = 1;
  if (((int)this - 8U < 2) || (iVar3 = iVar4, this == 10)) {
    param_2 = 0x32;
    iVar6 = 1;
    iVar7 = 0;
  }
  else {
    for (; iVar6 < param_2; iVar6 = iVar6 + 1) {
      iVar7 = iVar7 + *(int *)(iVar3 + 0xc);
      iVar3 = iVar3 + 0x10;
    }
  }
  *(char *)(iVar5 + 0x47) = (char)param_2;
  iVar4 = iVar6 * 0x10 + iVar4;
  uVar2 = *(u16 *)(iVar4 + -0x10);
  *(u16 *)(iVar5 + 0x62) = uVar2;
  *(u16 *)(iVar5 + 0x60) = uVar2;
  uVar2 = *(u16 *)(iVar4 + -0xe);
  *(u16 *)(iVar5 + 0x66) = uVar2;
  *(u16 *)(iVar5 + 100) = uVar2;
  uVar1 = *(u8 *)(iVar4 + -0xc);
  *(u8 *)(iVar5 + 0x69) = uVar1;
  *(u8 *)(iVar5 + 0x68) = uVar1;
  *(u8 *)(iVar5 + 0x6a) = *(u8 *)(iVar4 + -0xb);
  *(u8 *)(iVar5 + 0x6b) = *(u8 *)(iVar4 + -10);
  *(u8 *)(iVar5 + 0x6c) = *(u8 *)(iVar4 + -8);
  *(u8 *)(iVar5 + 0x6d) = *(u8 *)(iVar4 + -7);
  *(u8 *)(iVar5 + 0x6e) = *(u8 *)(iVar4 + -9);
  *(u8 *)(iVar5 + 0x6f) = *(u8 *)(iVar4 + -6);
  *(u8 *)(iVar5 + 0x70) = *(u8 *)(iVar4 + -5);
  *(int *)(iVar5 + 0x80) = iVar7;
  return;
}

// JP: 0x0037fcb0  PCLevelSet__10BtlSaveSecFi  size 0x3fc
// BtlSaveSec::PCLevelSet(int)
int PCLevelSet__10BtlSaveSecFi(BtlSaveSec *this)
{
  char cVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  char cVar10;
  char cVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  uint uVar15;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  if (((int)this - 8U < 2) || (this == 10)) {
    iVar3 = 0;
  }
  else {
    uVar9 = 0;
    uVar15 = 0;
    iVar7 = iVar3;
    do {
      uVar15 = uVar15 + 1;
      uVar9 = uVar9 + *(int *)(iVar7 + 0xc);
      iVar7 = iVar7 + 0x10;
      if (*(uint *)(iVar2 + 0x80) < uVar9) break;
    } while ((int)uVar15 < 99);
    if (*(u8 *)(iVar2 + 0x47) == uVar15) {
      iVar3 = 0;
    }
    else {
      iVar7 = (uint)*(u8 *)(iVar2 + 0x47) * 0x10 + iVar3;
      iVar3 = uVar15 * 0x10 + iVar3;
      sVar14 = (*(short *)(iVar2 + 0x60) - *(short *)(iVar7 + -0x10)) + *(short *)(iVar3 + -0x10);
      sVar13 = (*(short *)(iVar2 + 100) - *(short *)(iVar7 + -0xe)) + *(short *)(iVar3 + -0xe);
      sVar12 = ((u16)*(u8 *)(iVar2 + 0x68) - (u16)*(u8 *)(iVar7 + -0xc)) +
               (u16)*(u8 *)(iVar3 + -0xc);
      cVar11 = (*(char *)(iVar2 + 0x6a) - *(char *)(iVar7 + -0xb)) + *(char *)(iVar3 + -0xb);
      cVar10 = (*(char *)(iVar2 + 0x6b) - *(char *)(iVar7 + -10)) + *(char *)(iVar3 + -10);
      cVar8 = (*(char *)(iVar2 + 0x6c) - *(char *)(iVar7 + -8)) + *(char *)(iVar3 + -8);
      cVar6 = (*(char *)(iVar2 + 0x6d) - *(char *)(iVar7 + -7)) + *(char *)(iVar3 + -7);
      cVar5 = (*(char *)(iVar2 + 0x6e) - *(char *)(iVar7 + -9)) + *(char *)(iVar3 + -9);
      cVar4 = (*(char *)(iVar2 + 0x6f) - *(char *)(iVar7 + -6)) + *(char *)(iVar3 + -6);
      cVar1 = (*(char *)(iVar2 + 0x70) - *(char *)(iVar7 + -5)) + *(char *)(iVar3 + -5);
      if (sVar14 < 1) {
        sVar14 = 1;
      }
      if (999 < sVar14) {
        sVar14 = 999;
      }
      if (sVar13 < 1) {
        sVar13 = 1;
      }
      if (999 < sVar13) {
        sVar13 = 999;
      }
      if (sVar12 < 1) {
        sVar12 = 1;
      }
      if (99 < sVar12) {
        sVar12 = 99;
      }
      if (cVar11 < '\x01') {
        cVar11 = '\x01';
      }
      if ('c' < cVar11) {
        cVar11 = 'c';
      }
      if (cVar10 < '\x01') {
        cVar10 = '\x01';
      }
      if ('c' < cVar10) {
        cVar10 = 'c';
      }
      if (cVar8 < '\x01') {
        cVar8 = '\x01';
      }
      if ('c' < cVar8) {
        cVar8 = 'c';
      }
      if (cVar6 < '\x01') {
        cVar6 = '\x01';
      }
      if ('c' < cVar6) {
        cVar6 = 'c';
      }
      if (cVar5 < '\x01') {
        cVar5 = '\x01';
      }
      if ('c' < cVar5) {
        cVar5 = 'c';
      }
      if (cVar4 < '\x01') {
        cVar4 = '\x01';
      }
      if ('c' < cVar4) {
        cVar4 = 'c';
      }
      if (cVar1 < '\0') {
        cVar1 = '\0';
      }
      if ('c' < cVar1) {
        cVar1 = 'c';
      }
      *(short *)(iVar2 + 0x60) = sVar14;
      *(short *)(iVar2 + 100) = sVar13;
      *(char *)(iVar2 + 0x68) = (char)sVar12;
      *(char *)(iVar2 + 0x6a) = cVar11;
      *(char *)(iVar2 + 0x6b) = cVar10;
      *(char *)(iVar2 + 0x6c) = cVar8;
      *(char *)(iVar2 + 0x6d) = cVar6;
      *(char *)(iVar2 + 0x6e) = cVar5;
      *(char *)(iVar2 + 0x6f) = cVar4;
      *(char *)(iVar2 + 0x70) = cVar1;
      iVar3 = uVar15 - *(u8 *)(iVar2 + 0x47);
      *(u8 *)(iVar2 + 0x47) = *(u8 *)(iVar2 + 0x47) + (char)iVar3;
    }
  }
  return iVar3;
}

// JP: 0x003800b0  PCLevelSet2__10BtlSaveSecFii  size 0x428
// BtlSaveSec::PCLevelSet2(int, int)
int PCLevelSet2__10BtlSaveSecFii(BtlSaveSec *this,uint param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  int iVar8;
  char cVar9;
  char cVar10;
  short sVar11;
  short sVar12;
  short sVar13;
  int iVar14;
  int iVar15;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  if (((int)this - 8U < 2) || (this == 10)) {
    iVar14 = 0;
  }
  else {
    if ((int)param_2 < 1) {
      param_2 = 1;
    }
    if (99 < (int)param_2) {
      param_2 = 99;
    }
    if (*(u8 *)(iVar2 + 0x47) == param_2) {
      iVar14 = 0;
    }
    else {
      iVar15 = 0;
      iVar14 = 0;
      iVar8 = iVar3;
      do {
        iVar14 = iVar14 + 1;
        iVar15 = iVar15 + *(int *)(iVar8 + 0xc);
        iVar8 = iVar8 + 0x10;
      } while (iVar14 < (int)param_2);
      iVar8 = (uint)*(u8 *)(iVar2 + 0x47) * 0x10 + iVar3;
      iVar3 = iVar14 * 0x10 + iVar3;
      sVar13 = (*(short *)(iVar2 + 0x60) - *(short *)(iVar8 + -0x10)) + *(short *)(iVar3 + -0x10);
      sVar12 = (*(short *)(iVar2 + 100) - *(short *)(iVar8 + -0xe)) + *(short *)(iVar3 + -0xe);
      sVar11 = ((u16)*(u8 *)(iVar2 + 0x68) - (u16)*(u8 *)(iVar8 + -0xc)) +
               (u16)*(u8 *)(iVar3 + -0xc);
      cVar10 = (*(char *)(iVar2 + 0x6a) - *(char *)(iVar8 + -0xb)) + *(char *)(iVar3 + -0xb);
      cVar9 = (*(char *)(iVar2 + 0x6b) - *(char *)(iVar8 + -10)) + *(char *)(iVar3 + -10);
      cVar7 = (*(char *)(iVar2 + 0x6c) - *(char *)(iVar8 + -8)) + *(char *)(iVar3 + -8);
      cVar6 = (*(char *)(iVar2 + 0x6d) - *(char *)(iVar8 + -7)) + *(char *)(iVar3 + -7);
      cVar5 = (*(char *)(iVar2 + 0x6e) - *(char *)(iVar8 + -9)) + *(char *)(iVar3 + -9);
      cVar4 = (*(char *)(iVar2 + 0x6f) - *(char *)(iVar8 + -6)) + *(char *)(iVar3 + -6);
      cVar1 = (*(char *)(iVar2 + 0x70) - *(char *)(iVar8 + -5)) + *(char *)(iVar3 + -5);
      if (sVar13 < 1) {
        sVar13 = 1;
      }
      if (999 < sVar13) {
        sVar13 = 999;
      }
      if (sVar12 < 1) {
        sVar12 = 1;
      }
      if (999 < sVar12) {
        sVar12 = 999;
      }
      if (sVar11 < 1) {
        sVar11 = 1;
      }
      if (99 < sVar11) {
        sVar11 = 99;
      }
      if (cVar10 < '\x01') {
        cVar10 = '\x01';
      }
      if ('c' < cVar10) {
        cVar10 = 'c';
      }
      if (cVar9 < '\x01') {
        cVar9 = '\x01';
      }
      if ('c' < cVar9) {
        cVar9 = 'c';
      }
      if (cVar7 < '\x01') {
        cVar7 = '\x01';
      }
      if ('c' < cVar7) {
        cVar7 = 'c';
      }
      if (cVar6 < '\x01') {
        cVar6 = '\x01';
      }
      if ('c' < cVar6) {
        cVar6 = 'c';
      }
      if (cVar5 < '\x01') {
        cVar5 = '\x01';
      }
      if ('c' < cVar5) {
        cVar5 = 'c';
      }
      if (cVar4 < '\x01') {
        cVar4 = '\x01';
      }
      if ('c' < cVar4) {
        cVar4 = 'c';
      }
      if (cVar1 < '\0') {
        cVar1 = '\0';
      }
      if ('c' < cVar1) {
        cVar1 = 'c';
      }
      *(short *)(iVar2 + 0x60) = sVar13;
      *(short *)(iVar2 + 100) = sVar12;
      *(char *)(iVar2 + 0x68) = (char)sVar11;
      *(char *)(iVar2 + 0x6a) = cVar10;
      *(char *)(iVar2 + 0x6b) = cVar9;
      *(char *)(iVar2 + 0x6c) = cVar7;
      *(char *)(iVar2 + 0x6d) = cVar6;
      *(char *)(iVar2 + 0x6e) = cVar5;
      *(char *)(iVar2 + 0x6f) = cVar4;
      *(char *)(iVar2 + 0x70) = cVar1;
      *(int *)(iVar2 + 0x80) = iVar15;
      iVar14 = iVar14 - (uint)*(u8 *)(iVar2 + 0x47);
      *(u8 *)(iVar2 + 0x47) = *(u8 *)(iVar2 + 0x47) + (char)iVar14;
    }
  }
  return iVar14;
}

// JP: 0x003804e0  PCAddInit__10BtlSaveSecFi  size 0x778
// BtlSaveSec::PCAddInit(int)
void PCAddInit__10BtlSaveSecFi(BtlSaveSec *this)
{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  long lVar10;
  u8 bVar11;
  long lVar12;
  ulong uVar13;
  int iVar14;
  int *piVar15;
  long lVar16;
  int *piVar17;
  int iVar18;
  int aiStack_30 [12];
  iVar8 = GetCurrentPartySet__15SaveMenuSectionFv();
  InitPCParam__10BtlSaveSecFii(this,*(u32 *)(ourBtlSaveDat__10BtlSaveSec + 4));
  iVar18 = (int)this * 0xc0;
  *(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar18 + 0x44) =
       *(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar18 + 0x44) & 0xfe | 1;
  *(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar18 + 0x44) =
       *(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar18 + 0x44) & 0xfd | 2;
  cVar7 = *(char *)(iVar8 + 0xf);
  lVar16 = (long)cVar7;
  lVar10 = 0;
  if (0 < lVar16) {
    if (8 < lVar16) {
      piVar15 = aiStack_30;
      do {
        iVar14 = iVar8 + (int)lVar10;
        lVar10 = (long)((int)lVar10 + 8);
        *piVar15 = (int)*(char *)(iVar14 + 0x12);
        piVar15[1] = (int)*(char *)(iVar14 + 0x13);
        piVar15[2] = (int)*(char *)(iVar14 + 0x14);
        piVar15[3] = (int)*(char *)(iVar14 + 0x15);
        piVar15[4] = (int)*(char *)(iVar14 + 0x16);
        piVar15[5] = (int)*(char *)(iVar14 + 0x17);
        piVar15[6] = (int)*(char *)(iVar14 + 0x18);
        piVar15[7] = (int)*(char *)(iVar14 + 0x19);
        piVar15 = piVar15 + 8;
      } while (lVar10 < cVar7 + -8);
    }
    if (lVar10 < lVar16) {
      piVar15 = aiStack_30 + (int)lVar10;
      do {
        iVar14 = (int)lVar10;
        lVar10 = (long)(iVar14 + 1);
        *piVar15 = (int)*(char *)(iVar8 + iVar14 + 0x12);
        piVar15 = piVar15 + 1;
      } while (lVar10 < lVar16);
    }
  }
  lVar10 = 0;
  if (0 < lVar16) {
    piVar15 = aiStack_30;
    do {
      iVar8 = (int)lVar10 + 1;
      lVar12 = (long)iVar8;
      if (lVar12 < lVar16) {
        piVar17 = aiStack_30 + iVar8;
        do {
          iVar8 = *piVar15;
          if (*(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar8 * 0xc0 + 0x47) <
              *(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar17 * 0xc0 + 0x47)) {
            *piVar15 = *piVar17;
            *piVar17 = iVar8;
          }
          lVar12 = (long)((int)lVar12 + 1);
          piVar17 = piVar17 + 1;
        } while (lVar12 < lVar16);
      }
      lVar10 = (long)((int)lVar10 + 1);
      piVar15 = piVar15 + 1;
    } while (lVar10 < lVar16);
  }
  if (4 < lVar16) {
    lVar16 = 4;
  }
  iVar8 = 0;
  lVar10 = 0;
  if (0 < lVar16) {
    if (8 < lVar16) {
      piVar15 = aiStack_30;
      do {
        iVar14 = *piVar15;
        lVar10 = (long)((int)lVar10 + 8);
        piVar17 = piVar15 + 1;
        piVar1 = piVar15 + 2;
        piVar2 = piVar15 + 3;
        piVar3 = piVar15 + 4;
        piVar4 = piVar15 + 5;
        piVar5 = piVar15 + 6;
        piVar6 = piVar15 + 7;
        piVar15 = piVar15 + 8;
        iVar8 = iVar8 + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar14 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar17 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar1 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar2 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar3 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar4 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar5 * 0xc0 + 0x47) * 100 +
                (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + *piVar6 * 0xc0 + 0x47) * 100;
      } while (lVar10 < (int)lVar16 + -8);
    }
    if (lVar10 < lVar16) {
      piVar15 = aiStack_30 + (int)lVar10;
      do {
        iVar14 = *piVar15;
        lVar10 = (long)((int)lVar10 + 1);
        piVar15 = piVar15 + 1;
        iVar8 = iVar8 + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar14 * 0xc0 + 0x47) * 100;
      } while (lVar10 < lVar16);
    }
  }
  if (lVar16 == 0) {
    trap(7);
  }
  iVar8 = (iVar8 / (int)lVar16 + 0x32) / 100;
  if (iVar8 < 1) {
    iVar8 = 1;
  }
  if (99 < iVar8) {
    iVar8 = 99;
  }
  if ((int)(uint)*(u8 *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0x47) < iVar8) {
    PCLevelInit__10BtlSaveSecFii(this);
  }
  cVar7 = *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0x71);
  if (-1 < cVar7) {
    iVar8 = (int)cVar7 +
            (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(char *)(iVar8 + 0x9c4) = *(char *)(iVar8 + 0x9c4) + '\x01';
  }
  cVar7 = *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0x72);
  if (-1 < cVar7) {
    iVar8 = (int)cVar7 +
            (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(char *)(iVar8 + 0xa24) = *(char *)(iVar8 + 0xa24) + '\x01';
  }
  iVar8 = 0;
  do {
    cVar7 = *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + iVar8 + 0x73);
    if (-1 < cVar7) {
      iVar14 = ourBtlSaveDat__10BtlSaveSec +
               (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + (int)cVar7;
      *(char *)(iVar14 + 0xa54) = *(char *)(iVar14 + 0xa54) + '\x01';
    }
    iVar8 = iVar8 + 1;
    iVar14 = 0;
  } while (iVar8 < 3);
  do {
    cVar7 = *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + iVar14 + 0x76);
    uVar13 = (ulong)cVar7;
    uVar9 = (uint)(uVar13 & 7);
    if (-1 < (long)uVar13) {
      bVar11 = (u8)(1 << uVar9);
      if ((long)uVar13 < 0) {
        if ((uVar13 & 7) != 0) {
          uVar9 = uVar9 - 8;
        }
        bVar11 = (u8)(1 << (uVar9 & 0x1f));
      }
      iVar8 = ourBtlSaveDat__10BtlSaveSec + (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200
              + ((int)cVar7 >> 3);
      *(u8 *)(iVar8 + 0xaa4) = *(u8 *)(iVar8 + 0xaa4) | bVar11;
    }
    iVar14 = iVar14 + 1;
  } while (iVar14 < 8);
  uVar13 = (ulong)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + iVar18 + 0x9c);
  if ((uVar13 & 7) < (uVar13 & 0x3f) >> 3) {
    iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(u8 *)(iVar8 + 0xab8) =
         *(char *)(iVar8 + 0xab8) + ((u8)((uVar13 << 0x3a) >> 0x3d) - (char)(uVar13 & 7));
  }
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xab9) =
       *(char *)(iVar8 + 0xab9) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0x9e);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xaba) =
       *(char *)(iVar8 + 0xaba) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa3);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xab9) =
       *(char *)(iVar8 + 0xab9) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0x9f);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xaba) =
       *(char *)(iVar8 + 0xaba) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa4);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xab9) =
       *(char *)(iVar8 + 0xab9) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa0);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xaba) =
       *(char *)(iVar8 + 0xaba) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa5);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xab9) =
       *(char *)(iVar8 + 0xab9) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa1);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xaba) =
       *(char *)(iVar8 + 0xaba) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa6);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xab9) =
       *(char *)(iVar8 + 0xab9) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa2);
  iVar8 = (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
  *(char *)(iVar8 + 0xaba) =
       *(char *)(iVar8 + 0xaba) + *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa7);
  cVar7 = *(char *)(iVar18 + ourBtlSaveDat__10BtlSaveSec + 0xa8);
  if (-1 < cVar7) {
    iVar8 = (int)cVar7 +
            (uint)*(u8 *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + ourBtlSaveDat__10BtlSaveSec;
    *(char *)(iVar8 + 0xab8) = *(char *)(iVar8 + 0xab8) + '\x01';
  }
  return;
}

// JP: 0x00380c80  GetNextExp__10BtlSaveSecFi  size 0xcc
// BtlSaveSec::GetNextExp(int)
int GetNextExp__10BtlSaveSecFi(BtlSaveSec *this)
{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  if (((int)this - 8U < 2) || (this == 10)) {
    iVar2 = -1;
  }
  else {
    uVar1 = *(uint *)(iVar2 + 0x80);
    uVar5 = 0;
    iVar4 = 0;
    do {
      iVar4 = iVar4 + 1;
      uVar5 = uVar5 + *(int *)(iVar3 + 0xc);
      iVar3 = iVar3 + 0x10;
      if (uVar1 < uVar5) break;
    } while (iVar4 < 99);
    iVar2 = -1;
    if (iVar4 < 99) {
      iVar2 = uVar5 - uVar1;
    }
  }
  return iVar2;
}

// JP: 0x00380d50  GetFusMonParam__10BtlSaveSecFi  size 0x8c
// BtlSaveSec::GetFusMonParam(int)
int GetFusMonParam__10BtlSaveSecFi(BtlSaveSec *this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  iVar1 = GetRegDat__9RegDatApiFiii(0x2d,this,0xffffffffffffffff);
  uVar5 = 0;
  iVar4 = 0;
  iVar2 = iVar1;
  do {
    iVar3 = iVar4;
    iVar4 = iVar3 + 1;
    uVar5 = uVar5 + *(u16 *)(iVar2 + 0xe);
    iVar2 = iVar2 + 0x10;
    if (*(uint *)(ourBtlSaveDat__10BtlSaveSec + (int)this * 4 + 0xd50) < uVar5) break;
  } while (iVar4 < 10);
  *(char *)((int)this + ourBtlSaveDat__10BtlSaveSec + 0xd94) = (char)iVar4;
  return iVar1 + iVar3 * 0x10;
}

// JP: 0x00380de0  GetPCParam__10BtlSaveSecFii  size 0x17c
// BtlSaveSec::GetPCParam(int, int)
u64 GetPCParam__10BtlSaveSecFii(BtlSaveSec *this,ulong param_2)
{
  u64 uVar1;
  if (param_2 < 0x13) {
                    /* WARNING: Could not recover jumptable at 0x00380e1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(_7584 + (int)param_2 * 4))
                      (this,(int)param_2,ourBtlSaveDat__10BtlSaveSec + this * 0xc0 + 0x44);
    return uVar1;
  }
  return 0xffffffffffffffff;
}

// JP: 0x00380f60  SetPCParam__10BtlSaveSecFiii  size 0x534
// BtlSaveSec::SetPCParam(int, int, int)
ulong SetPCParam__10BtlSaveSecFiii(BtlSaveSec *this,u64 param_2,long param_3)
{
  u8 bVar1;
  u16 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  ulong uVar7;
  int iVar8;
  u8 uVar9;
  u16 uVar10;
  iVar4 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar5 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  iVar8 = 0;
  do {
    iVar8 = iVar8 + 1;
  } while (iVar8 < (int)(uint)*(u8 *)(iVar4 + 0x47));
  uVar9 = (u8)param_3;
  uVar10 = (u16)param_3;
  switch(param_2) {
  case 0:
    PCLevelSet2__10BtlSaveSecFii(this,param_3);
    uVar7 = (ulong)*(u8 *)(iVar4 + 0x47);
    break;
  case 1:
    *(u16 *)(iVar4 + 0x60) = uVar10;
    uVar2 = *(u16 *)(iVar8 * 0x10 + iVar5 + -0x10);
    if (*(u16 *)(iVar4 + 0x60) < uVar2) {
      *(u16 *)(iVar4 + 0x60) = uVar2;
    }
    uVar7 = GetRealMaxHP__10BtlSaveSecFiPc(this,0);
    break;
  case 2:
    *(u16 *)(iVar4 + 0x62) = uVar10;
    if (*(short *)(iVar4 + 0x62) == 0) {
      *(u16 *)(iVar4 + 0x62) = 1;
    }
    lVar6 = GetRealMaxHP__10BtlSaveSecFiPc(this,0);
    if (lVar6 < (long)(ulong)*(u16 *)(iVar4 + 0x62)) {
      *(short *)(iVar4 + 0x62) = (short)lVar6;
    }
    uVar7 = (ulong)*(u16 *)(iVar4 + 0x62);
    break;
  case 3:
    *(u16 *)(iVar4 + 100) = uVar10;
    uVar2 = *(u16 *)(iVar8 * 0x10 + iVar5 + -0xe);
    if (*(u16 *)(iVar4 + 100) < uVar2) {
      *(u16 *)(iVar4 + 100) = uVar2;
    }
    uVar7 = GetRealMaxMP__10BtlSaveSecFiPc(this,0);
    break;
  case 4:
    *(u16 *)(iVar4 + 0x66) = uVar10;
    if (*(short *)(iVar4 + 0x66) == 0) {
      *(u16 *)(iVar4 + 0x66) = 1;
    }
    lVar6 = GetRealMaxMP__10BtlSaveSecFiPc(this,0);
    if (lVar6 < (long)(ulong)*(u16 *)(iVar4 + 0x66)) {
      *(short *)(iVar4 + 0x66) = (short)lVar6;
    }
    uVar7 = (ulong)*(u16 *)(iVar4 + 0x66);
    break;
  case 5:
    *(u8 *)(iVar4 + 0x68) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -0xc);
    if (*(u8 *)(iVar4 + 0x68) < bVar1) {
      *(u8 *)(iVar4 + 0x68) = bVar1;
    }
    uVar7 = GetRealMaxSP__10BtlSaveSecFiPc(this,0);
    break;
  case 6:
    *(u8 *)(iVar4 + 0x69) = uVar9;
    if (*(char *)(iVar4 + 0x69) < '\x01') {
      *(u8 *)(iVar4 + 0x69) = 1;
    }
    cVar3 = GetRealMaxSP__10BtlSaveSecFiPc(this,0);
    if (cVar3 < *(char *)(iVar4 + 0x69)) {
      *(char *)(iVar4 + 0x69) = cVar3;
    }
    uVar7 = (ulong)*(char *)(iVar4 + 0x69);
    break;
  case 7:
    *(u8 *)(iVar4 + 0x6a) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -0xb);
    if (*(u8 *)(iVar4 + 0x6a) < bVar1) {
      *(u8 *)(iVar4 + 0x6a) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6a)) {
      *(u8 *)(iVar4 + 0x6a) = 99;
    }
    uVar7 = GetRealStr__10BtlSaveSecFiPc(this,0);
    break;
  case 8:
    *(u8 *)(iVar4 + 0x6b) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -10);
    if (*(u8 *)(iVar4 + 0x6b) < bVar1) {
      *(u8 *)(iVar4 + 0x6b) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6b)) {
      *(u8 *)(iVar4 + 0x6b) = 99;
    }
    uVar7 = GetRealVit__10BtlSaveSecFiPc(this,0);
    break;
  case 9:
    *(u8 *)(iVar4 + 0x6c) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -8);
    if (*(u8 *)(iVar4 + 0x6c) < bVar1) {
      *(u8 *)(iVar4 + 0x6c) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6c)) {
      *(u8 *)(iVar4 + 0x6c) = 99;
    }
    uVar7 = GetRealInt__10BtlSaveSecFiPc(this,0);
    break;
  case 10:
    *(u8 *)(iVar4 + 0x6d) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -7);
    if (*(u8 *)(iVar4 + 0x6d) < bVar1) {
      *(u8 *)(iVar4 + 0x6d) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6d)) {
      *(u8 *)(iVar4 + 0x6d) = 99;
    }
    uVar7 = GetRealPow__10BtlSaveSecFiPc(this,0);
    break;
  case 0xb:
    *(u8 *)(iVar4 + 0x6e) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -9);
    if (*(u8 *)(iVar4 + 0x6e) < bVar1) {
      *(u8 *)(iVar4 + 0x6e) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6e)) {
      *(u8 *)(iVar4 + 0x6e) = 99;
    }
    uVar7 = GetRealAgl__10BtlSaveSecFiPc(this,0);
    break;
  case 0xc:
    *(u8 *)(iVar4 + 0x6f) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -6);
    if (*(u8 *)(iVar4 + 0x6f) < bVar1) {
      *(u8 *)(iVar4 + 0x6f) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x6f)) {
      *(u8 *)(iVar4 + 0x6f) = 99;
    }
    uVar7 = GetRealLuc__10BtlSaveSecFiPc(this,0);
    break;
  case 0xd:
    *(u8 *)(iVar4 + 0x70) = uVar9;
    bVar1 = *(u8 *)(iVar8 * 0x10 + iVar5 + -5);
    if (*(u8 *)(iVar4 + 0x70) < bVar1) {
      *(u8 *)(iVar4 + 0x70) = bVar1;
    }
    if (99 < *(u8 *)(iVar4 + 0x70)) {
      *(u8 *)(iVar4 + 0x70) = 99;
    }
    uVar7 = (ulong)*(u8 *)(iVar4 + 0x70);
    break;
  case 0xe:
    uVar7 = GetRealPAtk__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0xf:
    uVar7 = GetRealSAtk__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x10:
    uVar7 = GetRealPDef__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x11:
    uVar7 = GetRealSDef__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x12:
    if (param_3 < 0) {
      param_3 = 0;
    }
    *(int *)(iVar4 + 0x80) = (int)param_3;
    PCLevelSet__10BtlSaveSecFi(this);
    uVar7 = (ulong)*(int *)(iVar4 + 0x80);
    break;
  default:
    uVar7 = 0xffffffffffffffff;
  }
  return uVar7;
}

// JP: 0x003814a0  AddPCParam__10BtlSaveSecFiii  size 0x5a4
// BtlSaveSec::AddPCParam(int, int, int)
ulong AddPCParam__10BtlSaveSecFiii(BtlSaveSec *this,u64 param_2,int param_3)
{
  u8 bVar1;
  u16 uVar2;
  short sVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  ulong uVar8;
  int iVar9;
  iVar5 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar6 = GetRegDat__9RegDatApiFiii(0x2a,this,0xffffffffffffffff);
  iVar9 = 0;
  do {
    iVar9 = iVar9 + 1;
  } while (iVar9 < (int)(uint)*(u8 *)(iVar5 + 0x47));
  cVar4 = (char)param_3;
  sVar3 = (short)param_3;
  switch(param_2) {
  case 0:
    PCLevelSet2__10BtlSaveSecFii(this,param_3 + (uint)*(u8 *)(iVar5 + 0x47));
    uVar8 = (ulong)*(u8 *)(iVar5 + 0x47);
    break;
  case 1:
    *(short *)(iVar5 + 0x60) = *(short *)(iVar5 + 0x60) + sVar3;
    uVar2 = *(u16 *)(iVar9 * 0x10 + iVar6 + -0x10);
    if (*(u16 *)(iVar5 + 0x60) < uVar2) {
      *(u16 *)(iVar5 + 0x60) = uVar2;
    }
    uVar8 = GetRealMaxHP__10BtlSaveSecFiPc(this,0);
    break;
  case 2:
    *(short *)(iVar5 + 0x62) = *(short *)(iVar5 + 0x62) + sVar3;
    if (*(short *)(iVar5 + 0x62) == 0) {
      *(u16 *)(iVar5 + 0x62) = 1;
    }
    lVar7 = GetRealMaxHP__10BtlSaveSecFiPc(this,0);
    if (lVar7 < (long)(ulong)*(u16 *)(iVar5 + 0x62)) {
      *(short *)(iVar5 + 0x62) = (short)lVar7;
    }
    uVar8 = (ulong)*(u16 *)(iVar5 + 0x62);
    break;
  case 3:
    *(short *)(iVar5 + 100) = *(short *)(iVar5 + 100) + sVar3;
    uVar2 = *(u16 *)(iVar9 * 0x10 + iVar6 + -0xe);
    if (*(u16 *)(iVar5 + 100) < uVar2) {
      *(u16 *)(iVar5 + 100) = uVar2;
    }
    uVar8 = GetRealMaxMP__10BtlSaveSecFiPc(this,0);
    break;
  case 4:
    *(short *)(iVar5 + 0x66) = *(short *)(iVar5 + 0x66) + sVar3;
    if (*(short *)(iVar5 + 0x66) == 0) {
      *(u16 *)(iVar5 + 0x66) = 1;
    }
    lVar7 = GetRealMaxMP__10BtlSaveSecFiPc(this,0);
    if (lVar7 < (long)(ulong)*(u16 *)(iVar5 + 0x66)) {
      *(short *)(iVar5 + 0x66) = (short)lVar7;
    }
    uVar8 = (ulong)*(u16 *)(iVar5 + 0x66);
    break;
  case 5:
    *(char *)(iVar5 + 0x68) = *(char *)(iVar5 + 0x68) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -0xc);
    if (*(u8 *)(iVar5 + 0x68) < bVar1) {
      *(u8 *)(iVar5 + 0x68) = bVar1;
    }
    uVar8 = GetRealMaxSP__10BtlSaveSecFiPc(this,0);
    break;
  case 6:
    *(char *)(iVar5 + 0x69) = *(char *)(iVar5 + 0x69) + cVar4;
    if (*(char *)(iVar5 + 0x69) < '\x01') {
      *(u8 *)(iVar5 + 0x69) = 1;
    }
    cVar4 = GetRealMaxSP__10BtlSaveSecFiPc(this,0);
    if (cVar4 < *(char *)(iVar5 + 0x69)) {
      *(char *)(iVar5 + 0x69) = cVar4;
    }
    uVar8 = (ulong)*(char *)(iVar5 + 0x69);
    break;
  case 7:
    *(char *)(iVar5 + 0x6a) = *(char *)(iVar5 + 0x6a) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -0xb);
    if (*(u8 *)(iVar5 + 0x6a) < bVar1) {
      *(u8 *)(iVar5 + 0x6a) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6a)) {
      *(u8 *)(iVar5 + 0x6a) = 99;
    }
    uVar8 = GetRealStr__10BtlSaveSecFiPc(this,0);
    break;
  case 8:
    *(char *)(iVar5 + 0x6b) = *(char *)(iVar5 + 0x6b) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -10);
    if (*(u8 *)(iVar5 + 0x6b) < bVar1) {
      *(u8 *)(iVar5 + 0x6b) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6b)) {
      *(u8 *)(iVar5 + 0x6b) = 99;
    }
    uVar8 = GetRealVit__10BtlSaveSecFiPc(this,0);
    break;
  case 9:
    *(char *)(iVar5 + 0x6c) = *(char *)(iVar5 + 0x6c) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -8);
    if (*(u8 *)(iVar5 + 0x6c) < bVar1) {
      *(u8 *)(iVar5 + 0x6c) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6c)) {
      *(u8 *)(iVar5 + 0x6c) = 99;
    }
    uVar8 = GetRealInt__10BtlSaveSecFiPc(this,0);
    break;
  case 10:
    *(char *)(iVar5 + 0x6d) = *(char *)(iVar5 + 0x6d) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -7);
    if (*(u8 *)(iVar5 + 0x6d) < bVar1) {
      *(u8 *)(iVar5 + 0x6d) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6d)) {
      *(u8 *)(iVar5 + 0x6d) = 99;
    }
    uVar8 = GetRealPow__10BtlSaveSecFiPc(this,0);
    break;
  case 0xb:
    *(char *)(iVar5 + 0x6e) = *(char *)(iVar5 + 0x6e) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -9);
    if (*(u8 *)(iVar5 + 0x6e) < bVar1) {
      *(u8 *)(iVar5 + 0x6e) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6e)) {
      *(u8 *)(iVar5 + 0x6e) = 99;
    }
    uVar8 = GetRealAgl__10BtlSaveSecFiPc(this,0);
    break;
  case 0xc:
    *(char *)(iVar5 + 0x6f) = *(char *)(iVar5 + 0x6f) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -6);
    if (*(u8 *)(iVar5 + 0x6f) < bVar1) {
      *(u8 *)(iVar5 + 0x6f) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x6f)) {
      *(u8 *)(iVar5 + 0x6f) = 99;
    }
    uVar8 = GetRealLuc__10BtlSaveSecFiPc(this,0);
    break;
  case 0xd:
    *(char *)(iVar5 + 0x70) = *(char *)(iVar5 + 0x70) + cVar4;
    bVar1 = *(u8 *)(iVar9 * 0x10 + iVar6 + -5);
    if (*(u8 *)(iVar5 + 0x70) < bVar1) {
      *(u8 *)(iVar5 + 0x70) = bVar1;
    }
    if (99 < *(u8 *)(iVar5 + 0x70)) {
      *(u8 *)(iVar5 + 0x70) = 99;
    }
    uVar8 = (ulong)*(u8 *)(iVar5 + 0x70);
    break;
  case 0xe:
    uVar8 = GetRealPAtk__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0xf:
    uVar8 = GetRealSAtk__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x10:
    uVar8 = GetRealPDef__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x11:
    uVar8 = GetRealSDef__10BtlSaveSecFiPcPc(this,0,0);
    break;
  case 0x12:
    *(int *)(iVar5 + 0x80) = *(int *)(iVar5 + 0x80) + param_3;
    PCLevelSet__10BtlSaveSecFi(this);
    uVar8 = (ulong)*(int *)(iVar5 + 0x80);
    break;
  default:
    uVar8 = 0xffffffffffffffff;
  }
  return uVar8;
}

// JP: 0x00381a50  GetRealMaxHP__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealMaxHP(int, char*)
int GetRealMaxHP__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u16 *)(iVar2 + 0x60);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\f') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (999 < iVar2) {
    iVar2 = 999;
  }
  return iVar2;
}

// JP: 0x00381c80  GetRealMaxMP__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealMaxMP(int, char*)
int GetRealMaxMP__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u16 *)(iVar2 + 100);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\r') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (999 < iVar2) {
    iVar2 = 999;
  }
  return iVar2;
}

// JP: 0x00381eb0  GetRealMaxSP__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealMaxSP(int, char*)
int GetRealMaxSP__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x68);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x0e') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x003820e0  GetRealStr__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealStr(int, char*)
int GetRealStr__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6a);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x0f') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x00382310  GetRealVit__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealVit(int, char*)
int GetRealVit__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6b);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x10') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x00382540  GetRealInt__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealInt(int, char*)
int GetRealInt__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6c);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x11') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x00382770  GetRealPow__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealPow(int, char*)
int GetRealPow__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6d);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x12') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x003829a0  GetRealAgl__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealAgl(int, char*)
int GetRealAgl__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6e);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x13') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x00382bd0  GetRealLuc__10BtlSaveSecFiPc  size 0x224
// BtlSaveSec::GetRealLuc(int, char*)
int GetRealLuc__10BtlSaveSecFiPc(BtlSaveSec *this,char *param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u8 *puVar5;
  int iVar6;
  uint uVar7;
  u8 auStack_120 [288];
  iVar6 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  uVar7 = (uint)*(u8 *)(iVar2 + 0x6f);
  iVar4 = 0;
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x73);
  }
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,auStack_120,0);
  }
  cVar1 = param_2[1];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  cVar1 = param_2[2];
  if (-1 < cVar1) {
    iVar2 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + (cVar1 * 10 + (int)cVar1) * 4 + 0x10,
                       auStack_120 + iVar4 * 0xc,0);
    iVar4 = iVar4 + iVar2;
  }
  iVar2 = 0;
  if (0 < iVar4) {
    puVar5 = auStack_120;
    do {
      if (puVar5[4] == '\x14') {
        if ((long)((ulong)(u8)puVar5[1] << 0x3e) < 0) {
          iVar6 = iVar6 + *(int *)(puVar5 + 8);
        }
        else {
          uVar7 = uVar7 + *(int *)(puVar5 + 8);
        }
      }
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0xc;
    } while (iVar2 < iVar4);
  }
  iVar2 = (int)(uVar7 * iVar6 + 0x32) / 100;
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  if (99 < iVar2) {
    iVar2 = 99;
  }
  return iVar2;
}

// JP: 0x00382e00  GetRealPAtk__10BtlSaveSecFiPcPc  size 0x29c
// BtlSaveSec::GetRealPAtk(int, char*, char*)
int GetRealPAtk__10BtlSaveSecFiPcPc(BtlSaveSec *this,char *param_2,char *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  u8 *puVar6;
  int iVar7;
  u8 auStack_120 [288];
  iVar7 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x30,0,0xffffffffffffffff);
  iVar4 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x71);
  }
  if (param_3 == (char *)0x0) {
    param_3 = (char *)(iVar2 + 0x73);
  }
  iVar2 = GetRealStr__10BtlSaveSecFiPc(this,param_3);
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar2 = iVar2 + *(short *)((cVar1 * 0xc + (int)cVar1) * 4 + iVar3 + 8);
  }
  cVar1 = *param_3;
  iVar3 = 0;
  if (-1 < cVar1) {
    iVar3 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar3 + 6);
    iVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + 0x10,auStack_120,0);
  }
  cVar1 = param_3[1];
  if (-1 < cVar1) {
    iVar5 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar5 + 6);
    iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar5 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar5;
  }
  cVar1 = param_3[2];
  if (-1 < cVar1) {
    iVar4 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar4 + 6);
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar4 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar4;
  }
  iVar4 = 0;
  if (0 < iVar3) {
    puVar6 = auStack_120;
    do {
      if (puVar6[4] == '\x17') {
        if ((long)((ulong)(u8)puVar6[1] << 0x3e) < 0) {
          iVar7 = iVar7 + *(int *)(puVar6 + 8);
        }
        else {
          iVar2 = iVar2 + *(int *)(puVar6 + 8);
        }
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 0xc;
    } while (iVar4 < iVar3);
  }
  iVar2 = (iVar2 * iVar7 + 0x32) / 100;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (0x7fff < iVar2) {
    iVar2 = 0x7fff;
  }
  return iVar2;
}

// JP: 0x003830a0  GetRealSAtk__10BtlSaveSecFiPcPc  size 0x29c
// BtlSaveSec::GetRealSAtk(int, char*, char*)
int GetRealSAtk__10BtlSaveSecFiPcPc(BtlSaveSec *this,char *param_2,char *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  u8 *puVar6;
  int iVar7;
  u8 auStack_120 [288];
  iVar7 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x30,0,0xffffffffffffffff);
  iVar4 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x71);
  }
  if (param_3 == (char *)0x0) {
    param_3 = (char *)(iVar2 + 0x73);
  }
  iVar2 = GetRealInt__10BtlSaveSecFiPc(this,param_3);
  cVar1 = *param_2;
  if (-1 < cVar1) {
    iVar2 = iVar2 + *(short *)((cVar1 * 0xc + (int)cVar1) * 4 + iVar3 + 10);
  }
  cVar1 = *param_3;
  iVar3 = 0;
  if (-1 < cVar1) {
    iVar3 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar3 + 8);
    iVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + 0x10,auStack_120,0);
  }
  cVar1 = param_3[1];
  if (-1 < cVar1) {
    iVar5 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar5 + 8);
    iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar5 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar5;
  }
  cVar1 = param_3[2];
  if (-1 < cVar1) {
    iVar4 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar4 + 8);
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar4 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar4;
  }
  iVar4 = 0;
  if (0 < iVar3) {
    puVar6 = auStack_120;
    do {
      if (puVar6[4] == '\x18') {
        if ((long)((ulong)(u8)puVar6[1] << 0x3e) < 0) {
          iVar7 = iVar7 + *(int *)(puVar6 + 8);
        }
        else {
          iVar2 = iVar2 + *(int *)(puVar6 + 8);
        }
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 0xc;
    } while (iVar4 < iVar3);
  }
  iVar2 = (iVar2 * iVar7 + 0x32) / 100;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (0x7fff < iVar2) {
    iVar2 = 0x7fff;
  }
  return iVar2;
}

// JP: 0x00383340  GetRealPDef__10BtlSaveSecFiPcPc  size 0x294
// BtlSaveSec::GetRealPDef(int, char*, char*)
int GetRealPDef__10BtlSaveSecFiPcPc(BtlSaveSec *this,char *param_2,char *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  u8 *puVar6;
  int iVar7;
  u8 auStack_120 [288];
  iVar7 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x31,0,0xffffffffffffffff);
  iVar4 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x72);
  }
  if (param_3 == (char *)0x0) {
    param_3 = (char *)(iVar2 + 0x73);
  }
  iVar2 = GetRealVit__10BtlSaveSecFiPc(this,param_3);
  if (-1 < *param_2) {
    iVar2 = iVar2 + *(short *)(*param_2 * 0x18 + iVar3 + 6);
  }
  cVar1 = *param_3;
  iVar3 = 0;
  if (-1 < cVar1) {
    iVar3 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar3 + 10);
    iVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + 0x10,auStack_120,0);
  }
  cVar1 = param_3[1];
  if (-1 < cVar1) {
    iVar5 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar5 + 10);
    iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar5 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar5;
  }
  cVar1 = param_3[2];
  if (-1 < cVar1) {
    iVar4 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar4 + 10);
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar4 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar4;
  }
  iVar4 = 0;
  if (0 < iVar3) {
    puVar6 = auStack_120;
    do {
      if (puVar6[4] == '\x19') {
        if ((long)((ulong)(u8)puVar6[1] << 0x3e) < 0) {
          iVar7 = iVar7 + *(int *)(puVar6 + 8);
        }
        else {
          iVar2 = iVar2 + *(int *)(puVar6 + 8);
        }
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 0xc;
    } while (iVar4 < iVar3);
  }
  iVar2 = (iVar2 * iVar7 + 0x32) / 100;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (0x7fff < iVar2) {
    iVar2 = 0x7fff;
  }
  return iVar2;
}

// JP: 0x003835e0  GetRealSDef__10BtlSaveSecFiPcPc  size 0x294
// BtlSaveSec::GetRealSDef(int, char*, char*)
int GetRealSDef__10BtlSaveSecFiPcPc(BtlSaveSec *this,char *param_2,char *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  u8 *puVar6;
  int iVar7;
  u8 auStack_120 [288];
  iVar7 = 100;
  iVar2 = ourBtlSaveDat__10BtlSaveSec + (int)this * 0xc0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x31,0,0xffffffffffffffff);
  iVar4 = GetRegDat__9RegDatApiFiii(0x32,0,0xffffffffffffffff);
  if (param_2 == (char *)0x0) {
    param_2 = (char *)(iVar2 + 0x72);
  }
  if (param_3 == (char *)0x0) {
    param_3 = (char *)(iVar2 + 0x73);
  }
  iVar2 = GetRealPow__10BtlSaveSecFiPc(this,param_3);
  if (-1 < *param_2) {
    iVar2 = iVar2 + *(short *)(*param_2 * 0x18 + iVar3 + 8);
  }
  cVar1 = *param_3;
  iVar3 = 0;
  if (-1 < cVar1) {
    iVar3 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar3 + 0xc);
    iVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar3 + 0x10,auStack_120,0);
  }
  cVar1 = param_3[1];
  if (-1 < cVar1) {
    iVar5 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar5 + 0xc);
    iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar5 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar5;
  }
  cVar1 = param_3[2];
  if (-1 < cVar1) {
    iVar4 = (cVar1 * 10 + (int)cVar1) * 4 + iVar4;
    iVar2 = iVar2 + *(short *)(iVar4 + 0xc);
    iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam
                      (this,7,cVar1,iVar4 + 0x10,auStack_120 + iVar3 * 0xc,0);
    iVar3 = iVar3 + iVar4;
  }
  iVar4 = 0;
  if (0 < iVar3) {
    puVar6 = auStack_120;
    do {
      if (puVar6[4] == '\x1a') {
        if ((long)((ulong)(u8)puVar6[1] << 0x3e) < 0) {
          iVar7 = iVar7 + *(int *)(puVar6 + 8);
        }
        else {
          iVar2 = iVar2 + *(int *)(puVar6 + 8);
        }
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 0xc;
    } while (iVar4 < iVar3);
  }
  iVar2 = (iVar2 * iVar7 + 0x32) / 100;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  if (0x7fff < iVar2) {
    iVar2 = 0x7fff;
  }
  return iVar2;
}

// JP: 0x00383880  SetPCModelNum__10BtlSaveSecFii  size 0x24
// BtlSaveSec::SetPCModelNum(int, int)
void SetPCModelNum__10BtlSaveSecFii(BtlSaveSec *this,u16 param_2)
{
  int iVar1;
  iVar1 = ourBtlSaveDat__10BtlSaveSec + this * 0xc0;
  *(u16 *)(iVar1 + 0x4c) = param_2;
  *(u16 *)(iVar1 + 0x4a) = param_2;
  *(u16 *)(iVar1 + 0x48) = param_2;
  return;
}

// JP: 0x003838b0  SetYoahism__10BtlSaveSecFi  size 0x2f0
// BtlSaveSec::SetYoahism(int)
/* WARNING: Removing unreachable block (ram,0x0038396c) */
/* WARNING: Removing unreachable block (ram,0x0038398c) */
void SetYoahism__10BtlSaveSecFi(BtlSaveSec *this)
{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  iVar6 = 0x12;
  iVar5 = 0x1e;
  bVar2 = false;
  cVar1 = *(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f3);
  uVar7 = *(uint *)(ourBtlSaveDat__10BtlSaveSec + 0xe38);
  if (((cVar1 == 'B') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'B')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'B')) {
    bVar2 = true;
  }
  bVar3 = false;
  if (((cVar1 == 'C') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'C')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'C')) {
    bVar3 = true;
  }
  if (((cVar1 == 'D') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'D')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'D')) {
    bVar3 = true;
    bVar2 = true;
  }
  if (bVar2) {
    iVar6 = 9;
  }
  if (bVar3) {
    iVar5 = 0xf;
  }
  if (this == 3) {
    while( true ) {
      if (iVar6 == 0) {
        trap(7);
      }
      if (iVar5 == 0) {
        trap(7);
      }
      iVar8 = ((int)uVar7 / iVar6) * iVar6 - uVar7;
      iVar4 = ((int)uVar7 / iVar5) * iVar5 - uVar7;
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if ((iVar8 < 2) && (iVar4 < 2)) break;
      uVar7 = uVar7 + 1;
    }
  }
  else if (this == 2) {
    while( true ) {
      if (iVar6 == 0) {
        trap(7);
      }
      if (iVar5 == 0) {
        trap(7);
      }
      iVar8 = ((int)uVar7 / iVar6) * iVar6 - uVar7;
      iVar4 = ((int)uVar7 / iVar5) * iVar5 - uVar7;
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if ((1 < iVar8) && (iVar4 < 2)) break;
      uVar7 = uVar7 + 1;
    }
  }
  else if (this == 1) {
    while( true ) {
      if (iVar6 == 0) {
        trap(7);
      }
      if (iVar5 == 0) {
        trap(7);
      }
      iVar8 = ((int)uVar7 / iVar6) * iVar6 - uVar7;
      iVar4 = ((int)uVar7 / iVar5) * iVar5 - uVar7;
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if ((iVar8 < 2) && (1 < iVar4)) break;
      uVar7 = uVar7 + 1;
    }
  }
  else if (this == 0) {
    while( true ) {
      if (iVar6 == 0) {
        trap(7);
      }
      if (iVar5 == 0) {
        trap(7);
      }
      iVar8 = ((int)uVar7 / iVar6) * iVar6 - uVar7;
      iVar4 = ((int)uVar7 / iVar5) * iVar5 - uVar7;
      if (iVar8 < 0) {
        iVar8 = -iVar8;
      }
      if (iVar4 < 0) {
        iVar4 = -iVar4;
      }
      if ((1 < iVar8) && (1 < iVar4)) break;
      uVar7 = uVar7 + 1;
    }
  }
  if (0x438 < uVar7) {
    uVar7 = uVar7 - 0x438;
  }
  *(uint *)(ourBtlSaveDat__10BtlSaveSec + 0xe38) = uVar7;
  return;
}

// JP: 0x00383ba0  GetYoahism__10BtlSaveSecFv  size 0x198
// BtlSaveSec::GetYoahism()
/* WARNING: Removing unreachable block (ram,0x00383c54) */
/* WARNING: Removing unreachable block (ram,0x00383c74) */
u32 GetYoahism__10BtlSaveSecFv(void)
{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  u32 uVar5;
  int iVar6;
  int iVar7;
  iVar6 = 0x12;
  iVar7 = 0x1e;
  cVar1 = *(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f3);
  iVar4 = *(int *)(ourBtlSaveDat__10BtlSaveSec + 0xe38);
  bVar2 = false;
  if (((cVar1 == 'B') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'B')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'B')) {
    bVar2 = true;
  }
  bVar3 = false;
  if (((cVar1 == 'C') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'C')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'C')) {
    bVar3 = true;
  }
  if (((cVar1 == 'D') || (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f4) == 'D')) ||
     (*(char *)(ourBtlSaveDat__10BtlSaveSec + 0x4f5) == 'D')) {
    bVar3 = true;
    bVar2 = true;
  }
  if (bVar2) {
    iVar6 = 9;
  }
  if (bVar3) {
    iVar7 = 0xf;
  }
  if (iVar6 == 0) {
    trap(7);
  }
  if (iVar7 == 0) {
    trap(7);
  }
  iVar6 = (iVar4 / iVar6) * iVar6 - iVar4;
  iVar4 = (iVar4 / iVar7) * iVar7 - iVar4;
  if (iVar6 < 0) {
    iVar6 = -iVar6;
  }
  if (iVar4 < 0) {
    iVar4 = -iVar4;
  }
  if ((iVar6 < 2) || (iVar4 < 2)) {
    if ((iVar6 < 2) && (1 < iVar4)) {
      uVar5 = 1;
    }
    else if ((iVar6 < 2) || (uVar5 = 2, 1 < iVar4)) {
      uVar5 = 3;
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}
