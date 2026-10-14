/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CBalIcon   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CBalIcon.md).
 */

/* JP: 0x004cc7c0  CBalIcon::CBalIcon()   [__ct__8CBalIconFv]  size=0x54 */
int __ct__8CBalIconFv(int param_1)

{
  __ct__17DelayDeleteObjectFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CBalIcon;
  clear__Q28CBalIcon6_flagsFv(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0xc) = 0;
  return param_1;
}

/* JP: 0x004cc840  CBalIcon::~CBalIcon()   [__dt__8CBalIconFv]  size=0x74 */
int __dt__8CBalIconFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CBalIcon;
    __dt__17DelayDeleteObjectFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004cc8c0  CBalIcon::Delete()   [Delete__8CBalIconFv]  size=0x3c */
void Delete__8CBalIconFv(int param_1)

{
  Release__8CBalIconFv(param_1);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x004cc900  CBalIcon::Release()   [Release__8CBalIconFv]  size=0x58 */
void Release__8CBalIconFv(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    Delete__9FldSpriteFv(*(undefined4 *)(param_1 + 0xc));
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  clear__Q28CBalIcon6_flagsFv(param_1 + 0x10);
  return;
}

/* JP: 0x004cc960  CBalIcon::SetPat(int, int)   [SetPat__8CBalIconFii]  size=0x2b8 */
void SetPat__8CBalIconFii(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  undefined1 auStack_40 [8];
  float fStack_38;
  float fStack_34;
  int iStack_30;
  int iStack_20;
  
  iVar5 = param_2;
  if (param_2 == 1) {
    iVar5 = 2;
  }
  if (param_2 == 2) {
    iVar5 = 1;
  }
  iStack_30 = param_1;
  iStack_20 = param_2;
  sprintf(auStack_40,0x556260,iVar5);
  uVar2 = FindDTCInfo__FPCc(auStack_40);
  if (*(int *)(iStack_30 + 0xc) != 0) {
    Release__8CBalIconFv(iStack_30);
  }
  lVar3 = __nw__FUi(0x10);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__9BufMemoryFv(lVar3);
  }
  uVar1 = GetDTCExSize__FP8_DTCINFO(uVar2);
  SetBuffer__9BufMemoryFUlPUc(uVar4,uVar1,(int)uVar2 + 0x10);
  lVar3 = __nw__FUi(0xd0);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__9FldSpriteFv(lVar3);
  }
  *(undefined4 *)(iStack_30 + 0xc) = uVar1;
  Create__9FldSpriteFP9BufMemoryib(*(undefined4 *)(iStack_30 + 0xc),uVar4,0,0);
  SetFilter__9FldSpriteFi(*(undefined4 *)(iStack_30 + 0xc),1);
  *(char *)(iStack_30 + 0x12) = (char)iStack_20;
  *(byte *)(iStack_30 + 0x10) = *(byte *)(iStack_30 + 0x10) & 0xfd | 2;
  *(undefined1 *)(iStack_30 + 0x13) = 2;
  fStack_34 = *(float *)(*(int *)(iStack_30 + 0xc) + 0x40);
  fStack_38 = *(float *)(*(int *)(iStack_30 + 0xc) + 0x44);
  SetTexPos__8P2SpriteFff(0x3f000000,0x3f000000,*(int *)(iStack_30 + 0xc) + 0x18);
  SetTexSize__8P2SpriteFff(fStack_34 - 1.0,fStack_38 - 1.0,*(int *)(iStack_30 + 0xc) + 0x18);
  fStack_34 = *(float *)(*(int *)(iStack_30 + 0xc) + 0x30);
  fStack_38 = *(float *)(*(int *)(iStack_30 + 0xc) + 0x34);
  SetSize__8P2SpriteFff(fStack_34 * 0.8,fStack_38,*(int *)(iStack_30 + 0xc) + 0x18);
  Set3D__9FldSpriteFi(*(undefined4 *)(iStack_30 + 0xc),1);
  SetHotSpot__8P2SpriteFff(0x40e00000,0x423c0000,*(int *)(iStack_30 + 0xc) + 0x18);
  return;
}

/* JP: 0x004cce50  CBalIcon::Dsp()   [Dsp__8CBalIconFv]  size=0x34 */
void Dsp__8CBalIconFv(int param_1)

{
  Dsp__9FldSpriteFii(*(undefined4 *)(param_1 + 0xc),0,0);
  return;
}

/* JP: 0x004cce90  CBalIcon::Clr()   [Clr__8CBalIconFv]  size=0x38 */
void Clr__8CBalIconFv(int param_1)

{
  Clr__9FldSpriteFiib(*(undefined4 *)(param_1 + 0xc),0,0,1);
  return;
}

/* JP: 0x004cced0  CBalIcon::SetCenter(FVector*)   [SetCenter__8CBalIconFP7FVector]  size=0x13c */
void SetCenter__8CBalIconFP7FVector(int param_1,undefined4 param_2)

{
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x10) << 0x3d)) {
    Dsp__8CBalIconFv(param_1);
    *(byte *)(iStack_20 + 0x10) = *(byte *)(iStack_20 + 0x10) & 0xfb | 4;
  }
  __ct__7FVectorFv(auStack_30);
  if ((long)((ulong)*(byte *)(iStack_20 + 0x10) << 0x3e) < 0) {
    *(byte *)(iStack_20 + 0x10) = *(byte *)(iStack_20 + 0x10) & 0xfd;
    __as__7FVectorFRC7FVector(auStack_30,uStack_10);
  }
  else {
    __ml__7FVectorCFf(0x3f19999a,auStack_40,*(int *)(iStack_20 + 0xc) + 0xc0);
    __as__7FVectorFRC7FVector(auStack_30,auStack_40);
    __ml__7FVectorCFf(0x3ecccccd,auStack_50,uStack_10);
    __apl__7FVectorFRC7FVector(auStack_30,auStack_50);
  }
  SetPos__9FldSpriteFP7FVector(*(undefined4 *)(iStack_20 + 0xc),auStack_30);
  return;
}

/* JP: 0x004cd010  CBalIcon::AddTime(float)   [AddTime__8CBalIconFf]  size=0xb24 */
void AddTime__8CBalIconFf(float param_1,int param_2)

{
  char cVar1;
  long lVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 uStack_44;
  
  if (*(char *)(param_2 + 0x13) == '\0') goto LAB_004cdaf8;
  cVar1 = *(char *)(param_2 + 0x12);
  if (cVar1 == '\t') {
    cVar1 = *(char *)(param_2 + 0x13);
    if (cVar1 == '\x06') {
      uStack_44 = 0.0;
      param_1 = *(float *)(param_2 + 0x18) + param_1;
      *(float *)(param_2 + 0x18) = param_1;
      if (0.6 <= param_1) {
        *(undefined1 *)(param_2 + 0x13) = 2;
      }
    }
    else if (cVar1 == '\x05') {
LAB_004cd9a8:
      *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) - param_1 * 0.9;
      if (*(float *)(param_2 + 0x14) <= 0.0) {
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        *(undefined4 *)(param_2 + 0x18) = 0;
      }
      fVar4 = (float)cosf(*(float *)(param_2 + 0x14) * 1.570796);
      uStack_44 = 1.0 - fVar4;
    }
    else if (cVar1 == '\x04') {
      uStack_44 = 1.0;
      fVar4 = *(float *)(param_2 + 0x18) + param_1;
      *(float *)(param_2 + 0x18) = fVar4;
      if (0.2 <= fVar4) {
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        goto LAB_004cd9a8;
      }
    }
    else {
      if (cVar1 != '\x03') {
        if (cVar1 != '\x02') goto LAB_004cda90;
        *(undefined4 *)(param_2 + 0x14) = 0;
        *(undefined4 *)(param_2 + 0x18) = 0;
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
      }
      *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 0.6;
      if (1.0 <= *(float *)(param_2 + 0x14)) {
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        *(undefined4 *)(param_2 + 0x14) = 0x3f800000;
        *(undefined4 *)(param_2 + 0x18) = 0;
      }
      uStack_44 = (float)sinf(*(float *)(param_2 + 0x14) * 1.570796);
    }
LAB_004cda90:
    SetOffset__9FldSpriteFff(0,uStack_44 * -6.0,*(undefined4 *)(param_2 + 0xc));
    fVar4 = uStack_44 * 0.3 + 0.7;
    SetScale__8P2SpriteFff(fVar4,fVar4,*(int *)(param_2 + 0xc) + 0x18);
    goto LAB_004cdaf8;
  }
  if (cVar1 == '\x05') {
    if (*(char *)(param_2 + 0x13) != '\x03') {
      if (*(char *)(param_2 + 0x13) != '\x02') goto LAB_004cdaf8;
      *(undefined4 *)(param_2 + 0x14) = 0x40400000;
      *(undefined4 *)(param_2 + 0x18) = 0;
      *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
    }
    *(float *)(param_2 + 0x18) = *(float *)(param_2 + 0x18) + param_1 * *(float *)(param_2 + 0x14);
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 0.5;
    if (4.0 <= *(float *)(param_2 + 0x18)) {
      *(undefined4 *)(param_2 + 0x18) = 0x40800000;
      *(undefined1 *)(param_2 + 0x13) = 0;
    }
    uVar3 = GetRad((*(float *)(param_2 + 0x18) - (float)(int)*(float *)(param_2 + 0x18)) *
                            360.0);
    fVar4 = (4.0 - *(float *)(param_2 + 0x18)) * 2.0;
    fVar5 = (float)cosf(uVar3);
    fVar6 = (float)sinf(uVar3);
    SetOffset__9FldSpriteFff
              (fVar4 * fVar5,fVar4 * fVar6 * 0.5 - fVar4 * 2.0,*(undefined4 *)(param_2 + 0xc));
    goto LAB_004cdaf8;
  }
  if (cVar1 != '\x04') {
    if (cVar1 != '\x03') {
      if (cVar1 == '\x01') {
        if (*(char *)(param_2 + 0x13) != '\x03') {
          if (*(char *)(param_2 + 0x13) != '\x02') goto LAB_004cdaf8;
          *(undefined4 *)(param_2 + 0x14) = 0;
          *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        }
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 4.0;
        if (1.0 <= *(float *)(param_2 + 0x14)) {
          *(undefined1 *)(param_2 + 0x13) = 0;
          *(undefined4 *)(param_2 + 0x14) = 0x3f800000;
        }
        uVar3 = sinf(*(float *)(param_2 + 0x14) * 1.570796);
        SetScale__8P2SpriteFff(uVar3,uVar3,*(int *)(param_2 + 0xc) + 0x18);
        goto LAB_004cdaf8;
      }
      if (cVar1 != '\0') goto LAB_004cdaf8;
      cVar1 = *(char *)(param_2 + 0x13);
      if (cVar1 == '\x04') {
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) - param_1 * 5.0;
        if (*(float *)(param_2 + 0x14) <= 1.0) {
          *(undefined1 *)(param_2 + 0x13) = 0;
          *(undefined4 *)(param_2 + 0x14) = 0x3f800000;
        }
      }
      else {
        if (cVar1 != '\x03') {
          if (cVar1 != '\x02') goto LAB_004cd1b0;
          *(undefined4 *)(param_2 + 0x14) = 0;
          *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        }
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 15.0;
        if (1.3 <= *(float *)(param_2 + 0x14)) {
          *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
          *(undefined4 *)(param_2 + 0x14) = 0x3fa66666;
        }
      }
LAB_004cd1b0:
      SetScale__8P2SpriteFff
                (*(undefined4 *)(param_2 + 0x14),*(undefined4 *)(param_2 + 0x14),
                 *(int *)(param_2 + 0xc) + 0x18);
      goto LAB_004cdaf8;
    }
    cVar1 = *(char *)(param_2 + 0x13);
    if (cVar1 == '\x06') {
LAB_004cd440:
      *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) - param_1 * 5.0;
      if (*(float *)(param_2 + 0x14) <= 0.0) {
        *(undefined1 *)(param_2 + 0x13) = 0;
        *(undefined4 *)(param_2 + 0x14) = 0;
      }
    }
    else if (cVar1 == '\x05') {
      fVar4 = *(float *)(param_2 + 0x18) + param_1;
      *(float *)(param_2 + 0x18) = fVar4;
      if (0.02 <= fVar4) {
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        goto LAB_004cd440;
      }
    }
    else {
      if (cVar1 != '\x04') {
        if (cVar1 != '\x03') {
          if (cVar1 != '\x02') goto LAB_004cd490;
          *(undefined4 *)(param_2 + 0x14) = 0;
          *(undefined4 *)(param_2 + 0x18) = 0;
          *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        }
        fVar4 = *(float *)(param_2 + 0x18) + param_1;
        *(float *)(param_2 + 0x18) = fVar4;
        if (fVar4 < 0.04) goto LAB_004cd490;
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
      }
      *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 12.0;
      if (1.0 <= *(float *)(param_2 + 0x14)) {
        *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
        *(undefined4 *)(param_2 + 0x14) = 0x3f800000;
        *(undefined4 *)(param_2 + 0x18) = 0;
      }
    }
LAB_004cd490:
    fVar4 = (float)sinf(*(float *)(param_2 + 0x14) * 1.570796);
    fVar4 = fVar4 * 0.3 + 1.0;
    SetScale__8P2SpriteFff(fVar4,fVar4,*(int *)(param_2 + 0xc) + 0x18);
    goto LAB_004cdaf8;
  }
  cVar1 = *(char *)(param_2 + 0x13);
  if (cVar1 == '\x04') {
LAB_004cd5a0:
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + param_1 * 0.9;
    if (1.0 <= *(float *)(param_2 + 0x14)) {
      *(undefined1 *)(param_2 + 0x13) = 0;
      *(undefined4 *)(param_2 + 0x14) = 0x3f800000;
    }
  }
  else if (cVar1 == '\x03') {
LAB_004cd560:
    fVar4 = *(float *)(param_2 + 0x18) + param_1;
    *(float *)(param_2 + 0x18) = fVar4;
    if (0.1 <= fVar4) {
      *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
      goto LAB_004cd5a0;
    }
  }
  else if (cVar1 == '\x02') {
    *(undefined4 *)(param_2 + 0x14) = 0;
    *(undefined4 *)(param_2 + 0x18) = 0;
    *(char *)(param_2 + 0x13) = *(char *)(param_2 + 0x13) + '\x01';
    goto LAB_004cd560;
  }
  fVar4 = (float)sinf(*(float *)(param_2 + 0x14) * 1.570796);
  SetOffset__9FldSpriteFff(0,(1.0 - fVar4) * -12.0,*(undefined4 *)(param_2 + 0xc));
LAB_004cdaf8:
  lVar2 = isDsp__9FldSpriteFv(*(undefined4 *)(param_2 + 0xc));
  if (lVar2 != 0) {
    Update__9FldSpriteFv(*(undefined4 *)(param_2 + 0xc));
  }
  return;
}
