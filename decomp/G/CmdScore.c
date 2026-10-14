/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdScore   functions: 13
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdScore.md).
 */

/* JP: 0x00474c10  CmdScore::CmdScore()   [__ct__8CmdScoreFv]  size=0x9c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__8CmdScoreFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdScore;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__13CmdScoreTitleFv(param_1 + 0xa4);
  __ct__10MenuWindowFv(param_1 + 0x218);
  *(undefined4 *)(param_1 + 0x2cc) = 0;
  *(undefined4 *)(param_1 + 0x2d0) = 0;
  *(undefined4 *)(param_1 + 0x2d4) = 0;
  return param_1;
}

/* JP: 0x00474cb0  CmdScore::~CmdScore()   [__dt__8CmdScoreFv]  size=0x9c */
int __dt__8CmdScoreFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdScore;
    __dt__10MenuWindowFv(param_1 + 0x218,0xffffffffffffffff);
    __dt__13CmdScoreTitleFv(param_1 + 0xa4,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00474d50  CmdScore::GetReady()   [GetReady__8CmdScoreFv]  size=0xc0 */
undefined4 GetReady__8CmdScoreFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  *(undefined4 *)(param_1 + 100) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x10) + 0x780;
  *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x10) + 0x4e0;
  SetData__9MenuSceneFUsP10MenuWindow(param_1,2,param_1 + 0x218);
  CreateScene__13CmdScoreTitleFP8CmdScore(param_1 + 0xa4,param_1);
  puVar2 = PTR_Enter__8CmdScoreFv_0050d8a0;
  uVar1 = DAT_0050d89c;
  *(undefined4 *)(param_1 + 0x58) = _4957;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined **)(param_1 + 0x60) = puVar2;
  return 1;
}

/* JP: 0x00474e10  CmdScore::Run()   [Run__8CmdScoreFv]  size=0x5c */
undefined8 Run__8CmdScoreFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x58);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x00474e70  CmdScore::Update()   [Update__8CmdScoreFv]  size=0x1a4 */
void Update__8CmdScoreFv(int param_1)

{
  int iVar1;
  
  iVar1 = (uint)*(ushort *)(param_1 + 0x2d8) * 0xc + *(int *)(param_1 + 0x28);
  UpdateScene__13CmdScoreTitleFP8CmdScorePc(param_1 + 0xa4,param_1,*(undefined4 *)(iVar1 + 0x10));
  Open__10MenuWindowFUci(param_1 + 0xa4,*(byte *)(param_1 + 0x154) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xd8) + 0x10));
  if (*(short *)(param_1 + 0x2d8) != 1) {
    if (*(short *)(param_1 + 0x2d8) != 0) goto LAB_00474f68;
    UpdateRank__8CmdScoreFv(param_1);
  }
  UpdateData__8CmdScoreFs(param_1,*(undefined2 *)(iVar1 + 0x18));
LAB_00474f68:
  if (*(short *)(param_1 + 0x2d8) == 0) {
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(iVar1 + 0x14),
               *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x2d0) + 0xf8) + 4),
               **(undefined4 **)(*(int *)(param_1 + 0x2d0) + 0xf8));
  }
  else {
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(iVar1 + 0x14));
  }
  return;
}

/* JP: 0x00475020  CmdScore::UpdateData(short)   [UpdateData__8CmdScoreFs]  size=0xcc */
void UpdateData__8CmdScoreFs(int param_1,undefined2 param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x2cc) == 0) {
    lVar3 = __nw__FUi(0x1414);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__12CmdScoreDataFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x2cc) = uVar2;
    CreateScene__12CmdScoreDataFP8CmdScore(*(undefined4 *)(param_1 + 0x2cc),param_1);
  }
  UpdateScene__12CmdScoreDataFP8CmdScoress
            (*(undefined4 *)(param_1 + 0x2cc),param_1,param_2,*(undefined2 *)(param_1 + 0x2da));
  iVar1 = *(int *)(param_1 + 0x2cc);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  return;
}

/* JP: 0x004750f0  CmdScore::UpdateRank()   [UpdateRank__8CmdScoreFv]  size=0x110 */
void UpdateRank__8CmdScoreFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  lVar3 = __nw__FUi(0xfc);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__12CmdScoreRankFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x2d0) = uVar2;
  CreateScene__12CmdScoreRankFP8CmdScore(*(undefined4 *)(param_1 + 0x2d0),param_1);
  iVar1 = *(int *)(param_1 + 0x2d0);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  lVar3 = __nw__FUi(0x248);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__17CmdScoreRankFrameFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x2d4) = uVar2;
  CreateScene__17CmdScoreRankFrameFP8CmdScore(*(undefined4 *)(param_1 + 0x2d4),param_1);
  iVar1 = *(int *)(param_1 + 0x2d4);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  return;
}

/* JP: 0x00475200  CmdScore::SetScore(short)   [SetScore__8CmdScoreFs]  size=0x248 */
void SetScore__8CmdScoreFs(int param_1,short param_2)

{
  int *piVar1;
  float afStack_40 [8];
  int iStack_20;
  short sStack_10;
  
  *(int *)(param_1 + 0x70) = *(int *)(*(int *)(param_1 + 0x10) + 0xbc) + 0x1144 + param_2 * 0x400;
  *(int *)(param_1 + 0x74) = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x2cc + param_2 * 0x10;
  iStack_20 = param_1;
  sStack_10 = param_2;
  FieldGetDistance__FPf(afStack_40);
  *(float *)(iStack_20 + 0x78) = afStack_40[sStack_10] * 0.001;
  memset(iStack_20 + 0x7c,0,0x24);
  *(undefined4 *)(iStack_20 + 0xa0) = 0;
  for (piVar1 = (int *)(*(int *)(iStack_20 + 0x70) + 0x44);
      piVar1 < (int *)(*(int *)(iStack_20 + 0x70) + 500); piVar1 = piVar1 + 9) {
    *(int *)(iStack_20 + 0x7c) = *(int *)(iStack_20 + 0x7c) + *piVar1;
    *(int *)(iStack_20 + 0x80) = *(int *)(iStack_20 + 0x80) + piVar1[1];
    *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0x84) + piVar1[2];
    *(int *)(iStack_20 + 0x88) = *(int *)(iStack_20 + 0x88) + piVar1[3];
    *(int *)(iStack_20 + 0x8c) = *(int *)(iStack_20 + 0x8c) + piVar1[4];
    *(int *)(iStack_20 + 0x90) = *(int *)(iStack_20 + 0x90) + piVar1[5];
    *(int *)(iStack_20 + 0x94) = *(int *)(iStack_20 + 0x94) + piVar1[6];
    *(int *)(iStack_20 + 0x98) = *(int *)(iStack_20 + 0x98) + piVar1[7];
    *(int *)(iStack_20 + 0x9c) = *(int *)(iStack_20 + 0x9c) + piVar1[8];
  }
  for (piVar1 = (int *)(*(int *)(iStack_20 + 0x70) + 0x28);
      piVar1 < (int *)(*(int *)(iStack_20 + 0x70) + 0x44); piVar1 = piVar1 + 1) {
    *(int *)(iStack_20 + 0xa0) = *(int *)(iStack_20 + 0xa0) + *piVar1;
  }
  return;
}

/* JP: 0x00475450  CmdScore::GetScore(short, char*, char*)   [GetScore__8CmdScoreFsPcPc]  size=0x3c4 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int GetScore__8CmdScoreFsPcPc(int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  int unaff_s0_lo;
  int aiStack_70 [4];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  int iStack_50;
  int iStack_4c;
  float fStack_44;
  int iStack_40;
  undefined2 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uStack_60 = (int)__5083;
  uStack_5c = (int)((ulong)__5083 >> 0x20);
  uStack_58 = DAT_0050d8b8;
  uStack_54 = DAT_0050d8bc;
  aiStack_70[0] = (int)__5085;
  aiStack_70[1] = (int)((ulong)__5085 >> 0x20);
  aiStack_70[2] = DAT_0050d8c8;
  aiStack_70[3] = DAT_0050d8cc;
  iStack_4c = 0;
  fStack_44 = 0.0;
  switch(param_2) {
  case 0:
    iStack_50 = **(int **)(param_1 + 0x70);
    break;
  case 1:
  case 2:
    iStack_50 = *(int *)(param_1 + 0x90);
    iStack_4c = *(int *)(param_1 + 0x88);
    unaff_s0_lo = 0;
    break;
  case 3:
  case 4:
    iStack_50 = *(int *)(param_1 + 0x94);
    iStack_4c = *(int *)(param_1 + 0x8c);
    unaff_s0_lo = 1;
    break;
  case 5:
  case 6:
    iStack_50 = *(int *)(param_1 + 0x9c);
    iStack_4c = *(int *)(param_1 + 0x98);
    unaff_s0_lo = 2;
    break;
  case 7:
  case 8:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x74) + 4);
    iStack_4c = **(int **)(param_1 + 0x74);
    unaff_s0_lo = 3;
    break;
  case 9:
    fStack_44 = *(float *)(param_1 + 0x78);
    break;
  case 10:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 4);
    break;
  case 0xb:
    iStack_50 = *(int *)(param_1 + 0x80);
    break;
  case 0xc:
    iStack_50 = *(int *)(param_1 + 0x84);
    break;
  case 0xd:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 0x1c);
    break;
  case 0xe:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 0xc);
    break;
  case 0xf:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 8);
    break;
  case 0x10:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 0x18);
    break;
  case 0x11:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 0x14);
    break;
  case 0x12:
    iStack_50 = *(int *)(*(int *)(param_1 + 0x70) + 0x20);
    break;
  case 0x13:
    iStack_50 = *(int *)(param_1 + 0xa0);
  }
  if (iStack_4c != 0) {
    fStack_44 = ((float)iStack_50 / (float)iStack_4c) * 100.0;
  }
  switch(param_2) {
  case 0:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    sprintf(param_4,param_3,iStack_50);
    break;
  case 1:
  case 3:
  case 5:
  case 7:
    if (iStack_50 < aiStack_70[unaff_s0_lo]) {
      fStack_44 = fStack_44 * ((float)iStack_4c / 400.0 + 0.5);
    }
    sprintf(param_4,param_3,iStack_50,iStack_4c);
    iStack_50 = (int)fStack_44;
    break;
  case 2:
  case 4:
  case 6:
  case 8:
  case 9:
    uVar1 = fptodp(fStack_44);
    sprintf(uStack_10,uStack_20,uVar1);
    iStack_50 = (int)fStack_44;
    break;
  default:
    iStack_50 = 0;
  }
  return iStack_50;
}

/* JP: 0x00475820  CmdScore::GetComment(short, int)   [GetComment__8CmdScoreFsi]  size=0xd8 */
undefined4 GetComment__8CmdScoreFsi(int param_1,undefined2 param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  iVar1 = Find__13MenuDataTableFs(*(int *)(param_1 + 0x10) + 0x28,param_2);
  puVar2 = (undefined4 *)(iVar1 + 0x10);
  puVar3 = puVar2 + *(int *)(iVar1 + 8) * 2;
  while( true ) {
    if (puVar3 <= puVar2) {
      return 0;
    }
    if (((int)puVar2[1] < 0) || (param_3 < (int)puVar2[1])) break;
    puVar2 = puVar2 + 2;
  }
  return *puVar2;
}

/* JP: 0x00475900  CmdScore::Enter()   [Enter__8CmdScoreFv]  size=0x228 */
undefined8 Enter__8CmdScoreFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  iVar1 = *(int *)(param_1 + 0x10);
  if (*(char *)(param_1 + 0x21) == '\0') {
    *(undefined2 *)(param_1 + 0x2d8) = 0;
    *(undefined2 *)(param_1 + 0x2da) = 0;
    SetScore__8CmdScoreFs(param_1,*(undefined2 *)(param_1 + 0x2d8));
    Update__8CmdScoreFv(param_1);
    Open__10MenuWindowFUci(param_1 + 0x218,*(byte *)(param_1 + 0x2c8) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x24c) + 0x10));
    AddOT__7MenuObjFv(param_1 + 0x218);
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),6);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x68));
    iVar1 = *(int *)(iVar1 + 0xb0);
    Close__10MenuWindowFUci(iVar1 + 0x5c,((ulong)*(byte *)(iVar1 + 0x10c) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x90) + 0x14));
    *(byte *)(*(int *)(param_1 + 0x6c) + 0x192) = *(byte *)(*(int *)(param_1 + 0x6c) + 0x192) & 0xfe
    ;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x2cc) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x2cc) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      DestroyBackGround__7CmdMenuFs(iVar1,1);
      puVar4 = PTR_Exec__8CmdScoreFv_0050d8d8;
      uVar3 = DAT_0050d8d4;
      *(undefined4 *)(param_1 + 0x58) = _5170;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x00475b30  CmdScore::Exit()   [Exit__8CmdScoreFv]  size=0x364 */
undefined8 Exit__8CmdScoreFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0,0,0x10);
    Close__10MenuWindowFUci(param_1 + 0x218,((ulong)*(byte *)(param_1 + 0x2c8) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x24c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0xa4,((ulong)*(byte *)(param_1 + 0x154) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xd8) + 0x14));
    if (*(int *)(param_1 + 0x2cc) != 0) {
      iVar1 = *(int *)(param_1 + 0x2cc);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    }
    if (*(int *)(param_1 + 0x2d0) != 0) {
      iVar1 = *(int *)(param_1 + 0x2d0);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
      iVar1 = *(int *)(param_1 + 0x2d4);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    }
    iVar1 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x14c) == '\x01') || (*(char *)(param_1 + 0x14c) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0x218);
      ReleaseOT__7MenuObjFv(param_1 + 0xa4);
      if (*(int *)(param_1 + 0x2cc) != 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x2cc));
        (**(code **)(*(int *)(*(int *)(param_1 + 0x2cc) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x2cc) = 0;
      }
      if (*(int *)(param_1 + 0x2d0) != 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x2d0));
        (**(code **)(*(int *)(*(int *)(param_1 + 0x2d0) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x2d0) = 0;
      }
      if (*(int *)(param_1 + 0x2d4) != 0) {
        ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x2d4));
        (**(code **)(*(int *)(*(int *)(param_1 + 0x2d4) + 8) + 0xc))();
        *(undefined4 *)(param_1 + 0x2d4) = 0;
      }
      *(byte *)(*(int *)(param_1 + 0x6c) + 0x192) =
           *(byte *)(*(int *)(param_1 + 0x6c) + 0x192) & 0xfe | 1;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00475ea0  CmdScore::Exec()   [Exec__8CmdScoreFv]  size=0xac */
undefined8 Exec__8CmdScoreFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  puVar2 = PTR_Exit__8CmdScoreFv_0050d8e8;
  uVar1 = DAT_0050d8e4;
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x4000) != 0) {
    *(undefined4 *)(param_1 + 0x58) = _5245;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined **)(param_1 + 0x60) = puVar2;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
  }
  return 0;
}
