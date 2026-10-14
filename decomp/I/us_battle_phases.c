/* Section I -- cleaned Ghidra output of the retail (SH2US_BATTLE.BIN) CBattle::Polling phase handlers and boss-effect functions
 * (0x484630-0x49ccd0).  Analysis output, not compilable source: `this` is CBattle*, chr(this,i) is the BtlChr at this+0xb0+i*0x510
 * (stride 0x510 in US, 0x4f0 in JP); CBattle fields use the names in notes/H/CBattle.md (nPhase +0x28, nStep +0x2a, cActor +0x2c,
 * nCmd0_target +0x44 ...).  Fields not yet named appear as f<hex offset>.
 * Names: EffectFunc/LastBossFunc/CloseBattleUI/__ct__7FVector are JP names confirmed by behaviour; Retail_CBattle_Phase*_ are retail-new
 * (phases 0x0b ring skill, 0x0f-0x12 Berserk antics, 0x15 win, 0x16 lose) -- see notes/I/us_retail_classes.md and notes/I/us_rewritten.md.
 * TarotEffectFunc is the phase-0x0d tarot card effect driver (BtlTarotSelect/BtlTarotEffect in us_battle_tarot.c).
 * Rust: port/crates (battle crate).  Diff notes: notes/I/us_delta.md. */

/* ---- 0x00484630  __ct__7FVectorFv  (size 0x20) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
undefined4 * __ct__7FVectorFv(undefined4 *this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  
  *this = in_zero_lo;
  this[1] = in_zero_hi;
  this[2] = in_zero_udw;
  this[3] = in_register_0000000c;
  return this;
}

/* ---- 0x00484650  EffectFunc__7CBattleFv  (size 0x7a80) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5', '0x6', '0x7', '0x8', '0x9', '0xa', '0xb', '0xc', '0xd', '0x12', '0x13', '0x1e', '0x1f', '0x20', '0x21', '0x22', '0x23', '0x28', '0x29', '0x2a', '0x64', '0x65', '0x67', '0x68']
 *   nPhase targets: ['0x14', '0x17']
 *   bState targets: ['0x7'] */
void EffectFunc__7CBattleFv(undefined8 this)

{
  short sVar1;
  byte bVar2;
  bool bVar3;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar4;
  undefined1 uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  long lVar11;
  undefined8 uVar12;
  int iVar13;
  long lVar14;
  int unaff_s0_lo;
  int unaff_s2_lo;
  uint uVar15;
  uint uVar16;
  int this;
  undefined8 unaff_s6;
  int unaff_s7_lo;
  float fVar18;
  float fVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int aiStack_40 [15];
  int iStack_4;
  
  sVar6 = -1;
  uStack_50 = in_zero_lo;
  uStack_4c = in_zero_hi;
  uStack_48 = in_zero_udw;
  uStack_44 = in_register_0000000c;
  iVar7 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
  iVar8 = GetRegDat__9RegDatApiFiii(0x3e,0,0xffffffffffffffff);
  /* this = this */
  if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
    unaff_s0_lo = Retail_CBattle_GetPAtkTable(this,this->cActor);
  }
  else {
    unaff_s7_lo = GetRegDat__9RegDatApiFiii(0x3c,0x19,0xffffffffffffffff);
  }
  iVar9 = GetRegDat__9RegDatApiFiii(0x45,0,0xffffffffffffffff);
  iVar13 = this->nCmdKind;
  if (iVar13 == 7) {
    unaff_s2_lo = iVar9 + this->nCmd0_target * 0x20;
    unaff_s6 = GetRegDat__9RegDatApiFiii(0xf,this->nCmd0_target,0xffffffffffffffff);
  }
  else if (iVar13 == 3) {
    unaff_s2_lo = unaff_s7_lo + this->nCmd0_target * 0x20;
    unaff_s6 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)(unaff_s2_lo + 2),0xffffffffffffffff);
    sVar6 = *(short *)(unaff_s7_lo + this->nCmd0_target * 0x20 + 0x1c);
  }
  else if (iVar13 == 2) {
    unaff_s2_lo = unaff_s0_lo + this->nCmd0_target * 0x40;
    unaff_s6 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)(unaff_s2_lo + 2),0xffffffffffffffff);
    sVar6 = *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x1c);
  }
  else if (iVar13 == 1) {
    unaff_s2_lo = iVar7 + this->nCmd0_target * 0x30;
    unaff_s6 = GetRegDat__9RegDatApiFiii(6,this->nCmd0_target,0xffffffffffffffff);
  }
  else if (iVar13 == 0) {
    unaff_s2_lo = iVar8 + this->nCmd0_target * 0x44;
    unaff_s6 = GetRegDat__9RegDatApiFiii(0xb,this->nCmd0_target,0xffffffffffffffff);
    sVar6 = *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x1c);
  }
  sVar1 = this->nStep;
  if (sVar1 == 0x69) {
    this->bFlags24 = this->bFlags24 & 0xfe;
    if (this->pBtlResult != 0) {
      Pause__6EffectFb(this->pBtlResult,0);
    }
    this->nStep = 9;
    *(undefined1 *)(this + 0x4866) = 0;
    *(undefined1 *)(this + 0x4867) = 0;
  }
  else if (sVar1 != 0x68) {
    if (sVar1 == 0x67) {
      *(float *)(this + 0x4908) = *(float *)(this + 0x4908) + this->flDeltaT;
      if (0.5 <= *(float *)(this + 0x4908)) {
        this->bFlags24 = this->bFlags24 & 0xfe | 1;
        if (this->pBtlResult != 0) {
          Pause__6EffectFb(this->pBtlResult,1);
        }
        if (*(int *)(this + 0x4624) == 0) {
          lVar11 = __nw__FUi(0xb1c);
          uVar10 = 0;
          if (lVar11 != 0) {
            uVar10 = __ct__7BtlMenuFib(lVar11,0x16,0);
          }
          *(undefined4 *)(this + 0x4624) = uVar10;
        }
        else {
          SetMode__7BtlMenuFib(*(undefined4 *)(this + 0x4624),0x16,0);
        }
        *(undefined2 *)(*(int *)(this + 0x4624) + 0xb00) = 0x10;
        *(undefined1 *)(this + 0x4867) = 0xe;
        this->nStep = 0x68;
      }
    }
    else if (sVar1 == 0x66) {
      SetMode__5JRingFsssss(*(undefined4 *)(this + 0x45d0),5,1,1,4,3);
      *(undefined2 *)(*(int *)(this + 0x45d0) + 0x58c) = 8;
      RingActive__5JRingFv(*(undefined4 *)(this + 0x45d0));
      if (this->nComboCnt != 0) {
        *(byte *)(*(int *)(this + 0x45d0) + 0x42) =
             *(byte *)(*(int *)(this + 0x45d0) + 0x42) & 0x7f | 0x80;
      }
      this->nStep = 3;
      *(undefined1 *)(this + 0x4867) = 0xc;
      *(undefined4 *)(this + 0x4908) = 0;
    }
    else if (sVar1 != 0x65) {
      if (sVar1 == 100) {
        if (*(int *)(this + 0x4624) == 0) {
          lVar11 = __nw__FUi(0xb1c);
          uVar10 = 0;
          if (lVar11 != 0) {
            uVar10 = __ct__7BtlMenuFib(lVar11,0x16,0);
          }
          *(undefined4 *)(this + 0x4624) = uVar10;
        }
        else {
          SetMode__7BtlMenuFib(*(undefined4 *)(this + 0x4624),0x16,0);
        }
        *(undefined2 *)(*(int *)(this + 0x4624) + 0xb00) = 0xb;
        *(undefined1 *)(this + 0x4867) = 0xb;
        this->nStep = 0x65;
      }
      else if (sVar1 == 0x2a) {
        lVar11 = FindMesWin__7BtlMenuFi(this->nMsgHandle);
        if (lVar11 == 0) {
          this->nMsgHandle = 0xffff;
          this->nPhase = 0x14;
          this->nStep = 0;
          this->nCmdKind = 1;
          this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
          this->flTurnPush = 0x40400000;
          if ((((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 0) &&
               ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x50)) ||
              (this->wTurnPendMask == 0)) && (this->nComboCnt == 0)) {
            this->bFlags25 = this->bFlags25 & 0xfb;
          }
        }
      }
      else {
        if (sVar1 != 0x29) {
          if (sVar1 != 0x28) {
            if (sVar1 == 0x23) {
              if (*(short *)(iGpffff8378 + 0x3c) < 1) {
                return;
              }
              this->nPhase = 0x17;
              this->nStep = 0;
              this->bFlags25 = this->bFlags25 & 0xfc | 2;
              this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
              if (-1 < (long)((ulong)this->bFlags24 << 0x3a)) {
                return;
              }
              if (*(int *)(this + 0x98) == 0) {
                return;
              }
              (**(code **)(this + 0x98))(4,0,0,*(undefined4 *)(this + 0x94));
              return;
            }
            if (sVar1 != 0x22) {
              if (sVar1 != 0x21) {
                if (sVar1 == 0x20) {
                  SetFadeOut__11CBtlPAfter2Ff(0x3f800000,iGpffff8618);
                  if (*(char *)(iGpffff836c + 0x18d) == '\x01') {
                    SetBGMParam__6HNMSndFiii(uGpffff8374,0,0x7f,1000);
                  }
                  else {
                    SetBtlBGMFadeOut__6HNMSndFi(uGpffff8374,1000);
                  }
                  MakeResultTrophy__7CBattleFi(this,2);
                  if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
                    *(int *)(iGpffff83b4 + 0x14c0) = *(int *)(iGpffff83b4 + 0x14c0) + 1;
                  }
                  this->nStep = 0x21;
                  this->flTurnPush = 0;
                  if (*(char *)(iGpffff836c + 0x6b0) != '\0') {
                    return;
                  }
                  *(undefined1 *)(iGpffff836c + 0x6b0) = 1;
                  return;
                }
                if (sVar1 != 0x1f) {
                  if (sVar1 != 0x1e) {
                    if (sVar1 == 0x14) {
                      cVar4 = BtlChrReadyCheck__7CBattleFv(this);
                      if (cVar4 == '\0') {
                        return;
                      }
                      cVar4 = AllCSERelease__7CBattleFv(this);
                      if (cVar4 == '\0') {
                        return;
                      }
                      CloseBattleUI__7CBattleFb(this,1);
                      if (chr(this,this->cActor)->bState == '\x11') {
                        chr(this,this->cActor)->bState = 7;
                        chr(this,this->cActor)->bState2 = 1;
                      }
                      iVar7 = this + this->cActor * 0x510;
                      *(byte *)(iVar7 + 0xb5) = *(byte *)(iVar7 + 0xb5) & 0xf7;
                      if ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 1) &&
                         (cVar4 = Retail_CBattle_SetAllChrEffMask(this,1), cVar4 == '\0')) {
                        return;
                      }
                      if (chr(this,this->cActor)->bState != '\a') {
                        return;
                      }
                      if (chr(this,this->cActor)->bState2 != '\x02') {
                        return;
                      }
                      if ((long)((ulong)*(byte *)(*(int *)(this + this->cActor * 0x510
                                                          + 0x14c) + 0x4d0) << 0x3d) < 0) {
                        return;
                      }
                      *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
                      GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                                (this,this->cActor,
                                 this->nCmd1,
                                 ((ulong)*(ushort *)(unaff_s2_lo + 4) & 0x1ff) >> 7,
                                 ((ulong)*(byte *)(unaff_s2_lo + 5) & 0xf) >> 1,
                                 ((ulong)*(byte *)(unaff_s2_lo + 5) & 0x3f) >> 4,unaff_s2_lo + 8,
                                 &iStack_4);
                      if (iStack_4 == 0) {
                        iVar7 = this->nCmdKind;
                        if (iVar7 == 7) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,0,0,8,
                                     this->nCmd0_target,unaff_s2_lo,unaff_s2_lo + 8,
                                     this->cActor);
                        }
                        else if ((iVar7 == 3) || (iVar7 == 2)) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,0,0,1,
                                     this->nCmd0_target,unaff_s2_lo,unaff_s2_lo + 8,
                                     this->cActor);
                        }
                        else if (iVar7 == 0) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,0,0,2,
                                     this->nCmd0_target,unaff_s2_lo,unaff_s2_lo + 8,
                                     this->cActor);
                        }
                        else if (iVar7 == 1) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,0,0,3,
                                     this->nCmd0_target,unaff_s2_lo,unaff_s2_lo + 8,
                                     this->cActor);
                        }
                      }
                      else {
                        iVar7 = this->nCmdKind;
                        if (iVar7 == 7) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,iStack_4
                                     ,aiStack_40,8,this->nCmd0_target,unaff_s2_lo,
                                     unaff_s2_lo + 8,this->cActor);
                        }
                        else if ((iVar7 == 3) || (iVar7 == 2)) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,iStack_4
                                     ,aiStack_40,1,this->nCmd0_target,unaff_s2_lo,
                                     unaff_s2_lo + 8,this->cActor);
                        }
                        else if (iVar7 == 0) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,iStack_4
                                     ,aiStack_40,2,this->nCmd0_target,unaff_s2_lo,
                                     unaff_s2_lo + 8,this->cActor);
                        }
                        else if (iVar7 == 1) {
                          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                    ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,this,iStack_4
                                     ,aiStack_40,3,this->nCmd0_target,unaff_s2_lo,
                                     unaff_s2_lo + 8,this->cActor);
                        }
                        if (((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) {
                          for (iVar7 = 0; iVar7 < iStack_4; iVar7 = iVar7 + 1) {
                            SetSelectChr__13TurnOrderDispFii
                                      (this->pTurnOrderDisp,aiStack_40[iVar7],2);
                          }
                        }
                        else {
                          for (iVar7 = 0; iVar7 < iStack_4; iVar7 = iVar7 + 1) {
                            SetSelectChr__13TurnOrderDispFii
                                      (this->pTurnOrderDisp,aiStack_40[iVar7],1);
                          }
                        }
                      }
                      this->nShortcutTarget = 0xffffffff;
                      uVar10 = SetBtlMessage__7CBattleFiPv(this,0x146,unaff_s6);
                      this->nShortcutTarget = uVar10;
                      *(undefined2 *)(this + 0x45d6) = 0;
                      if (((((this->nCmdKind == 0) || (this->nCmdKind == 2)) ||
                           (this->nCmdKind == 3)) || (this->nCmdKind == 7)) &&
                         (*(short *)(unaff_s2_lo + 0x18) < 1000)) {
                        if (-1 < chr(this,this->cActor)->f4e4) {
                          uVar5 = DataReadEntry__7CBattleFiii
                                            (this,0xc,0x12,
                                             *(undefined2 *)
                                              (this + this->cActor * 0x510 + 0x594));
                          this->cDataId = uVar5;
                        }
                      }
                      else if ((this->nCmdKind == 1) &&
                              (chr(this,this->cActor)->f4bc != 0)) {
                        iVar7 = this + this->cActor * 0x510;
                        *(byte *)(iVar7 + 0xb1) = *(byte *)(iVar7 + 0xb1) & 0xfb | 4;
                      }
                      this->nDataSlot = 0xffffffff;
                      if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x87) {
                        cVar4 = CheckCycleHit__7CBattleFi(this,this->nCmd1);
                        if (cVar4 == '\x01') {
                          uVar15 = rand();
                          uVar16 = uVar15 & 3;
                          if (((int)uVar15 < 0) && (uVar16 != 0)) {
                            uVar16 = uVar16 - 4;
                          }
                          if (uVar16 == 0) {
                            uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x87);
                            this->nDataSlot = uVar10;
                          }
                          else if (uVar16 == 1) {
                            uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfc);
                            this->nDataSlot = uVar10;
                          }
                          else if (uVar16 == 2) {
                            uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfd);
                            this->nDataSlot = uVar10;
                          }
                          else {
                            uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfe);
                            this->nDataSlot = uVar10;
                          }
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xf0);
                          this->nDataSlot = uVar10;
                        }
                      }
                      else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x100) {
                        cVar4 = CheckCycleHit__7CBattleFi(this,this->nCmd1);
                        if (cVar4 == '\x01') {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x100);
                          this->nDataSlot = uVar10;
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x101);
                          this->nDataSlot = uVar10;
                        }
                      }
                      else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x89) {
                        iVar7 = rand();
                        if ((iVar7 % 10000 < 0x1389) ||
                           ((chr(this,this->cActor)->bFlagsB & 1) != 0))
                        {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x89);
                          this->nDataSlot = uVar10;
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xf9);
                          this->nDataSlot = uVar10;
                        }
                      }
                      else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xe5) {
                        if ((*(byte *)(this + 0x4654) & 3) == 1) {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x105);
                          this->nDataSlot = uVar10;
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xe5);
                          this->nDataSlot = uVar10;
                        }
                      }
                      else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xde) {
                        if (((*(byte *)(this + 0x4654) & 3) == 1) ||
                           (cVar4 = Retail_CBattle_CheckAbilitySealed
                                              (this,this->nCmd1),
                           cVar4 != '\x01')) {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x104);
                          this->nDataSlot = uVar10;
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xde);
                          this->nDataSlot = uVar10;
                        }
                      }
                      else if (-1 < *(short *)(unaff_s2_lo + 0x18)) {
                        if (*(short *)(unaff_s2_lo + 0x18) < 1000) {
                          uVar10 = DataReadEntry__7CBattleFiii
                                             (this,0xc,0xb,*(undefined2 *)(unaff_s2_lo + 0x18));
                          this->nDataSlot = uVar10;
                        }
                        else {
                          uVar10 = DataReadEntry__7CBattleFiii
                                             (this,0xc,0xb,*(short *)(unaff_s2_lo + 0x18) + -1000
                                             );
                          this->nDataSlot = uVar10;
                        }
                      }
                      iVar13 = 0;
                      iVar7 = this->nCmdKind;
                      if (iVar7 == 7) {
                        iVar13 = 1;
                      }
                      else if (iVar7 == 3) {
                        iVar13 = 1;
                      }
                      else if (iVar7 == 2) {
                        if ((((0 < *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x22))
                             && (iVar13 = 1,
                                0 < *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x26))
                             ) && (iVar13 = 2,
                                  0 < *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x2a
                                                ))) &&
                           ((iVar13 = 3,
                            0 < *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x2e) &&
                            (iVar13 = 4,
                            0 < *(short *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x32)))))
                        {
                          iVar13 = 5;
                        }
                        iVar13 = iVar13 + 1;
                      }
                      else if (iVar7 == 1) {
                        iVar13 = 1;
                      }
                      else if (iVar7 == 0) {
                        if (((0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x22)) &&
                            (iVar13 = 1,
                            0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x26))) &&
                           ((iVar13 = 2,
                            0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x2a) &&
                            ((iVar13 = 3,
                             0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x2e) &&
                             (iVar13 = 4,
                             0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 + 0x32))))))) {
                          iVar13 = 5;
                        }
                        iVar13 = iVar13 + 1;
                      }
                      *(short *)(this + 0x45d8) = (short)iVar13;
                      *(short *)(this + 0x45da) = (short)iVar13;
                      for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
                        *(undefined1 *)(this + iVar7 + 0x45ec) = 0;
                      }
                      for (uVar15 = 0; (int)uVar15 < iVar13; uVar15 = uVar15 + 1) {
                        uVar16 = uVar15 & 3;
                        if (((int)uVar15 < 0) && (uVar16 != 0)) {
                          uVar16 = uVar16 - 4;
                        }
                        iVar7 = this + ((int)uVar15 >> 2);
                        *(byte *)(iVar7 + 0x45ec) =
                             *(byte *)(iVar7 + 0x45ec) | (byte)(1 << ((uVar16 & 0xf) << 1));
                      }
                      *(undefined4 *)(this + 0x45dc) = 10000;
                      *(undefined4 *)(this + 0x45e0) = 10000;
                      *(undefined4 *)(this + 0x45e4) = 12000;
                      *(undefined4 *)(this + 0x45e8) = 10000;
                      *(byte *)(this + 0x45d6) = *(byte *)(this + 0x45d6) & 0xf9 | 4;
                      *(byte *)(this + 0x45d6) = *(byte *)(this + 0x45d6) & 0xf7 | 8;
                      if (((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x89) &&
                         (*(int *)(this + this->nDataSlot * 0x18 + 0x40c8) == 0x89)) {
                        uVar15 = iVar13 - 1U & 3;
                        if (((int)(iVar13 - 1U) < 0) && (uVar15 != 0)) {
                          uVar15 = uVar15 - 4;
                        }
                        iVar7 = this + (iVar13 + -1 >> 2);
                        *(byte *)(iVar7 + 0x45ec) =
                             *(byte *)(iVar7 + 0x45ec) | (byte)(3 << ((uVar15 & 0xf) << 1));
                        *(byte *)(this + 0x45d6) = *(byte *)(this + 0x45d6) & 0xf9 | 6;
                      }
                      this->nStep = 6;
                      if (((chr(this,this->cActor)->bFlagsB & 1) == 0)
                         && (this->nComboCnt != 0)) {
                        AddFriendship__7CBattleFiis
                                  (this,*(undefined2 *)
                                            (this + this->cActor * 0x510 + 0x120),
                                   *(undefined2 *)
                                    (this + this->cActorB * 0x510 + 0x120),100);
                      }
                      if ((chr(this,this->cActor)->bFlagsB & 1) != 0) {
                        return;
                      }
                      iVar7 = this->nCmdKind;
                      if (((iVar7 == 3) || (iVar7 == 7)) || (iVar7 == 2)) {
                        *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xfd | 2;
                      }
                      else if (iVar7 == 1) {
                        *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xf7 | 8;
                      }
                      else if (iVar7 == 0) {
                        *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xfb | 4;
                      }
                      if (((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) && (-1 < sVar6))
                         && ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x86)) {
                        if (this->wTurnPendMask != 0) {
                          return;
                        }
                        if (this->nComboCnt != 0) {
                          return;
                        }
                      }
                      if (((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50) &&
                         (this->wTurnPendMask != 0)) {
                        return;
                      }
                      *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0x7f;
                      return;
                    }
                    if (sVar1 != 0x13) {
                      if (sVar1 != 0x12) {
                        if (sVar1 == 0xd) {
                          lVar11 = FindMesWin__7BtlMenuFi(this->nShortcutTarget);
                          if (lVar11 != 0) {
                            return;
                          }
                          iVar7 = GetRegCnt__9RegDatApiFii(0x3c,4);
                          *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + 1;
                          while (((*(uint *)(this + 0x58) & 1 << (*(uint *)(this + 0x5c) & 0x1f)
                                  ) == 0 && (*(int *)(this + 0x5c) < iVar7))) {
                            *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + 1;
                          }
                          if (*(int *)(this + 0x5c) < iVar7) {
                            iVar7 = GetRegDat__9RegDatApiFiii(0x3c,4,0xffffffffffffffff);
                            uVar12 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)
                                                        (iVar7 + *(int *)(this + 0x5c) * 0x40 + 2)
                                                     ,0xffffffffffffffff);
                            uVar10 = SetBtlMessage__7CBattleFiPv(this,0x7a,uVar12);
                            this->nShortcutTarget = uVar10;
                            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x1002,1,0);
                            return;
                          }
                          this->nDestIdx = 0;
                          this->nStep = 0x12;
                          return;
                        }
                        if (sVar1 != 0xc) {
                          if (sVar1 != 0xb) {
                            if (sVar1 == 10) {
                              bVar3 = false;
                              if (*(int *)(this + 0x4624) != 0) {
                                if (*(short *)(*(int *)(this + 0x4624) + 0x28) != 0x14) {
                                  *(undefined2 *)(*(int *)(this + 0x4624) + 0x28) = 0x17;
                                  *(undefined2 *)(*(int *)(this + 0x4624) + 0x2a) = 3;
                                }
                                bVar3 = true;
                              }
                              if (bVar3) {
                                return;
                              }
                              if ((this->pBtlResult != 0) &&
                                 (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                                EffectNext__6EffectFv(this->pBtlResult);
                                this->nStep = 0xb;
                                return;
                              }
                              this->nStep = 0xc;
                              return;
                            }
                            if (sVar1 == 9) {
                              if ((*(char *)(this + 0x4866) == '\x01') &&
                                 (*(char *)(this + 0x4867) == '\r')) {
                                this->nStep = 0x67;
                                return;
                              }
                              if ((-1 < (long)((ulong)this->bFlags25 << 0x39)) &&
                                 (-1 < (long)((ulong)this->bFlags25 << 0x38))) {
                                return;
                              }
                              if (((-1 < this->nMsgHandle) &&
                                  (lVar11 = FindMesWin__7BtlMenuFi(this->nMsgHandle)
                                  , lVar11 != 0)) && (*(float *)((int)lVar11 + 0x3c) < 2.0)) {
                                return;
                              }
                              if ((long)((ulong)this->bFlags25 << 0x39) < 0) {
                                iVar7 = this->pBtlResult;
                                if (iVar7 != 0) {
                                  (**(code **)(*(int *)(iVar7 + 0x14) + 8))(iVar7,1);
                                }
                                this->pBtlResult = 0;
                                SetAlphaMode__8BtlFaderFUl(0x44);
                                Retail_CBattle_ReleaseChrWait(this);
                              }
                              if (((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xe5) &&
                                 ((*(byte *)(this + 0x4654) & 3) != 1)) {
                                this->nStep = 0x1e;
                                return;
                              }
                              if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xa8) {
                                this->nStep = 0x28;
                                return;
                              }
                              if (-1 < this->cDataId) {
                                IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
                              }
                              this->nIopHandle = 0xffffffff;
                              this->cDataId = 0xff;
                              if (-1 < this->nShortcutTarget) {
                                SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
                              }
                              if (-1 < this->nMsgHandle) {
                                SetMesWinClose__7BtlMenuFi(this->nMsgHandle);
                              }
                              this->nMsgHandle = 0xffff;
                              bVar3 = false;
                              lVar11 = Retail_CBattle_FindLastBossPart(this,0);
                              if (((this->cActor == lVar11) &&
                                  ((long)((ulong)*(byte *)(this + 0x26) << 0x3c) < 0)) &&
                                 (bVar3 = true,
                                 *(short *)(this + (int)lVar11 * 0x510 + 0x1ac) < 10)) {
                                this->bFlags25 = this->bFlags25 & 0xfb;
                              }
                              if (((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50) || (bVar3)) {
                                this->bFlags25 = this->bFlags25 & 0xef | 0x10;
                                this->bFlags25 = this->bFlags25 & 0xf7 | 8;
                                for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                                  if (((((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                                         ((long)((ulong)chr(this,iVar7)->bFlagsA <<
                                                0x3e) < 0)) &&
                                        (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2
                                                    << 0x3c))) &&
                                       ((0 < chr(this,iVar7)->nHp &&
                                        ((long)((ulong)chr(this,iVar7)->bFlagsA <<
                                               0x3a) < 0)))) &&
                                      ('\x18' < chr(this,iVar7)->bState)) &&
                                     ((chr(this,iVar7)->bState < '+' &&
                                      (chr(this,iVar7)->f458 + 1 ==
                                       *(int *)(this + 0x40))))) {
                                    iVar13 = this + iVar7 * 0x510;
                                    *(byte *)(iVar13 + 0x504) =
                                         *(byte *)(iVar13 + 0x504) & 0xef | 0x10;
                                    chr(this,iVar7)->f458 =
                                         *(undefined4 *)(this + 0x40);
                                    chr(this,iVar7)->f464 =
                                         ((float)chr(this,iVar7)->f460 * 2.0)
                                         / 100.0;
                                    chr(this,iVar7)->f468 = 0;
                                    if (((ulong)chr(this,iVar7)->bFlagsB & 7) >> 1
                                        != 0) {
                                      chr(this,iVar7)->f468 = 0x3dcccccd;
                                    }
                                  }
                                }
                              }
                              if ((-1 < (long)((ulong)this->bFlags25 << 0x3b)) ||
                                 ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0 &&
                                  ((sVar6 < 0 ||
                                   ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x86)))))) {
                                ComboStopOff__Fi(0xffffffffffffffff);
                                if ((this->wTurnPendMask != 0) ||
                                   ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0 &&
                                    ((sVar6 < 0 ||
                                     ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x86)))))) {
                                  this->bFlags25 = this->bFlags25 & 0xf7;
                                }
                                this->cMesWinId2 = 0xff;
                              }
                              if ((chr(this,this->cActor)->bFlagsB & 1)
                                  == 0) {
                                iVar7 = this->nCmdKind;
                                if (iVar7 == 7) {
                                  DecMP__7CBattleFiiii
                                            (this,this->cActor,8,
                                             this->nCmd0_target,0xffffffffffffffff,
                                             *(undefined2 *)
                                              (iVar9 + this->nCmd0_target * 0x20 + 0x1c));
                                }
                                else if (iVar7 == 2) {
                                  DecMP__7CBattleFiiii
                                            (this,this->cActor,1,
                                             this->nCmd0_target,
                                             *(undefined2 *)
                                              (unaff_s0_lo + this->nCmd0_target * 0x40 + 0x18),
                                             *(undefined2 *)
                                              (unaff_s0_lo + this->nCmd0_target * 0x40 + 0x1e))
                                  ;
                                }
                                else if (iVar7 == 0) {
                                  DecMP__7CBattleFiiii
                                            (this,this->cActor,2,
                                             this->nCmd0_target,
                                             *(undefined2 *)
                                              (iVar8 + this->nCmd0_target * 0x44 + 0x18),
                                             *(undefined2 *)
                                              (iVar8 + this->nCmd0_target * 0x44 + 0x1e));
                                }
                                else if ((iVar7 == 1) &&
                                        (iVar7 = iGpffff83b4 +
                                                 (uint)*(byte *)(iGpffff83b4 + 2) * 0x200 +
                                                 this->nCmd0_target,
                                        *(char *)(iVar7 + 0xabc) = *(char *)(iVar7 + 0xabc) + -1,
                                        *(char *)(iGpffff83b4 +
                                                  (uint)*(byte *)(iGpffff83b4 + 2) * 0x200 +
                                                  this->nCmd0_target + 0xabc) == '\0')) {
                                  for (iVar7 = 0; iVar7 < 0xe; iVar7 = iVar7 + 1) {
                                    for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
                                      iVar13 = iGpffff83b4 + iVar7 * 0x10 + iVar8 * 4;
                                      if ((*(char *)(iVar13 + 0x10bc) == '\x01') &&
                                         ((long)*(short *)(iVar13 + 0x10be) ==
                                          (long)this->nCmd0_target)) {
                                        *(char *)(iVar13 + 0x10bc) = -1;
                                        *(undefined1 *)(iVar13 + 0x10bd) = 0xff;
                                        *(undefined2 *)(iVar13 + 0x10be) = 0xffff;
                                      }
                                    }
                                  }
                                  for (iVar7 = 0; iVar7 < 0x17; iVar7 = iVar7 + 1) {
                                    for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
                                      iVar13 = iGpffff83b4 + iVar7 * 0x10 + iVar8 * 4;
                                      if ((*(char *)(iVar13 + 0x119c) == '\x01') &&
                                         ((long)*(short *)(iVar13 + 0x119e) ==
                                          (long)this->nCmd0_target)) {
                                        *(char *)(iVar13 + 0x119c) = -1;
                                        *(undefined1 *)(iVar13 + 0x119d) = 0xff;
                                        *(undefined2 *)(iVar13 + 0x119e) = 0xffff;
                                      }
                                    }
                                  }
                                  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
                                    iVar8 = iGpffff83b4 + iVar7 * 4;
                                    if ((*(char *)(iVar8 + 0x130c) == '\x01') &&
                                       ((long)*(short *)(iVar8 + 0x130e) ==
                                        (long)this->nCmd0_target)) {
                                      *(char *)(iVar8 + 0x130c) = -1;
                                      *(undefined1 *)(iVar8 + 0x130d) = 0xff;
                                      *(undefined2 *)(iVar8 + 0x130e) = 0xffff;
                                    }
                                  }
                                  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
                                    iVar8 = iGpffff83b4 + iVar7 * 4;
                                    if ((*(char *)(iVar8 + 0x131c) == '\x01') &&
                                       ((long)*(short *)(iVar8 + 0x131e) ==
                                        (long)this->nCmd0_target)) {
                                      *(char *)(iVar8 + 0x131c) = -1;
                                      *(undefined1 *)(iVar8 + 0x131d) = 0xff;
                                      *(undefined2 *)(iVar8 + 0x131e) = 0xffff;
                                    }
                                  }
                                  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
                                    iVar8 = iGpffff83b4 + iVar7 * 4;
                                    if ((*(char *)(iVar8 + 0x132c) == '\x01') &&
                                       ((long)*(short *)(iVar8 + 0x132e) ==
                                        (long)this->nCmd0_target)) {
                                      *(char *)(iVar8 + 0x132c) = -1;
                                      *(undefined1 *)(iVar8 + 0x132d) = 0xff;
                                      *(undefined2 *)(iVar8 + 0x132e) = 0xffff;
                                    }
                                  }
                                }
                              }
                              if (this->wTurnPendMask != 0) {
                                this->wDeadMask =
                                     this->wDeadMask |
                                     (ushort)(1 << ((int)this->cActor & 0x1fU));
                              }
                              if ((*(short *)(*(int *)(this + this->cActor * 0x510 +
                                                      0x14c) + 0x510) == 0x31) ||
                                 (*(short *)(*(int *)(this + this->cActor * 0x510 +
                                                     0x14c) + 0x510) == 0x30)) {
                                if (chr(this,this->cActor)->f4b4 != 0
                                   ) {
                                  *(undefined4 *)
                                   (chr(this,this->cActor)->f4b4 +
                                   0x5c0) = 5;
                                }
                                chr(this,this->cActor)->f4b4 =
                                     0;
                                if (chr(this,this->cActor)->f4b0 != 0
                                   ) {
                                  (**(code **)(*(int *)(*(int *)(this + this->cActor *
                                                                          0x510 + 0x560) + 0x14) +
                                              0x3c))();
                                }
                                chr(this,this->cActor)->f4b0 =
                                     0;
                                SetBtlMotion__8BtlModelFif
                                          (0x3f800000,
                                           *(undefined4 *)
                                            (this + this->cActor * 0x510 + 0x14c),0x32
                                          );
                              }
                              if ((this->nCmdKind == 7) &&
                                 (*(uint *)(this + 0x58) != (uint)*(ushort *)(iGpffff83b4 + 0xfc3)
                                 )) {
                                *(uint *)(this + 0x58) =
                                     (uint)*(ushort *)(iGpffff83b4 + 0xfc3) -
                                     *(int *)(this + 0x58);
                                this->nStep = 10;
                                return;
                              }
                              this->nDestIdx = 0;
                              this->nStep = 0x12;
                              return;
                            }
                            if (sVar1 == 8) {
                              if (-1 < (long)((ulong)*(byte *)(this + this->nDataSlot *
                                                                        0x18 + 0x40c4) << 0x3a)) {
                                return;
                              }
                              if (this->nCmdKind == 1) {
                                if ((chr(this,this->cActor)->f4bc !=
                                     0) && (cVar4 = IOPReleaseCheck__6HNMSndFi(uGpffff8374,
                                                                    *(undefined4 *)
                                                                     (this + *(char *)(this + 
                                                  0x2c) * 0x510 + 0x570)), cVar4 == '\0')) {
                                  return;
                                }
                                chr(this,this->cActor)->f4c0 =
                                     0xffffffff;
                              }
                              else if ((chr(this,this->cActor)->bState
                                        == '\x10') &&
                                      (chr(this,this->cActor)->bState2 <
                                       '\x02')) {
                                return;
                              }
                              if (this->nCmdKind == 7) {
                                *(uint *)(this + 0x58) = (uint)*(ushort *)(iGpffff83b4 + 0xfc3);
                              }
                              this->bFlags25 = this->bFlags25 & 0xbf;
                              this->bFlags25 = this->bFlags25 & 0x7f;
                              *(byte *)(this + 0x26) = *(byte *)(this + 0x26) & 0xfe;
                              *(undefined4 *)(this + 0x490c) = 0;
                              this->nMsgHandle = 0xffff;
                              lVar11 = __nw__FUi(0x48);
                              uVar10 = 0;
                              if (lVar11 != 0) {
                                uVar10 = __ct__6EffectFPFPvi_vPvi(lVar11,0x472ce0,this,0);
                              }
                              this->pBtlResult = uVar10;
                              Create__6EffectFP9BufMemory(this->pBtlResult,
                                              *(undefined4 *)
                                               (this + this->nDataSlot * 0x18 + 0x40cc),
                                              1);
                              SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi(this->pBtlResult,0x472cb0,this,0);
                              DataRelease__7CBattleFiib
                                        (this,this->nDataSlot,0xc,1);
                              *(undefined2 *)(this + 0x3d90) = 1;
                              *(int *)(this + 0x3d94) = (int)this->cActor;
                              *(undefined4 *)(this + 0x3d98) =
                                   *(undefined4 *)
                                    (this + this->cActor * 0x510 + 0x14c);
                              *(int *)(this + 0x3d9c) =
                                   this + this->cActor * 0x510 + 0xb0;
                              GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                                        (this,this->cActor,
                                         this->nCmd1,
                                         ((ulong)*(ushort *)(unaff_s2_lo + 4) & 0x1ff) >> 7,
                                         ((ulong)*(byte *)(unaff_s2_lo + 5) & 0xf) >> 1,
                                         ((ulong)*(byte *)(unaff_s2_lo + 5) & 0x3f) >> 4,
                                         unaff_s2_lo + 8,&iStack_4);
                              iVar7 = aiStack_40[0];
                              if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50) {
                                iVar8 = 1;
                                while ((iVar8 < iStack_4 &&
                                       (*(short *)(this + aiStack_40[iVar8] * 0x510 + 0x19c) !=
                                        499))) {
                                  iVar8 = iVar8 + 1;
                                }
                                if (iVar8 < iStack_4) {
                                  aiStack_40[0] = aiStack_40[iVar8];
                                  aiStack_40[iVar8] = iVar7;
                                }
                              }
                              for (iVar7 = 0; iVar7 < iStack_4; iVar7 = iVar7 + 1) {
                                *(int *)(this + iVar7 * 0x14 + 0x3e84) = aiStack_40[iVar7];
                                *(undefined4 *)(this + iVar7 * 0x14 + 0x3e88) =
                                     *(undefined4 *)(this + aiStack_40[iVar7] * 0x510 + 0x14c);
                                *(int *)(this + iVar7 * 0x14 + 0x3e8c) =
                                     this + aiStack_40[iVar7] * 0x510 + 0xb0;
                              }
                              *(short *)(this + 0x3d92) = (short)iStack_4;
                              if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xef) {
                                GetDeadlyThrowTarget__7CBattleFv(this);
                              }
                              if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x70) {
                                lVar11 = 0;
                                while (lVar11 < 0xc) {
                                  iVar7 = (int)lVar11;
                                  if (((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                                       ((long)((ulong)chr(this,iVar7)->bFlagsA <<
                                              0x3e) < 0)) &&
                                      (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2
                                                  << 0x3c))) &&
                                     (((0 < chr(this,iVar7)->nHp &&
                                       (lVar11 != this->cActor)) &&
                                      ((chr(this,this->cActor)->bFlagsB
                                       & 1) == (chr(this,iVar7)->bFlagsB & 1))))) {
                                    iVar8 = 0;
                                    while ((iVar8 < 0x20 &&
                                           (((*(char *)(this + iVar7 * 0x510 + iVar8 * 0xc + 0x1d0
                                                       ) != 'T' ||
                                             (((ulong)*(byte *)(this + iVar7 * 0x510 + iVar8 * 0xc
                                                               + 0x1cd) & 0x3f) >> 3 != 0)) ||
                                            ((*(uint *)(this + iVar7 * 0x510 + iVar8 * 0xc + 0x1d4
                                                       ) & 0x20) == 0))))) {
                                      iVar8 = iVar8 + 1;
                                    }
                                    if (0x1f < iVar8) {
                                      lVar14 = 0;
                                      while ((lVar14 < *(short *)(this + 0x3d92) &&
                                             (*(int *)(this + (int)lVar14 * 0x14 + 0x3e84) !=
                                              lVar11))) {
                                        lVar14 = (long)((int)lVar14 + 1);
                                      }
                                      if (*(short *)(this + 0x3d92) <= lVar14) {
                                        *(int *)(this + *(short *)(this + 0x3d90) * 0x14 +
                                                0x3d94) = iVar7;
                                        *(undefined4 *)
                                         (this + *(short *)(this + 0x3d90) * 0x14 + 0x3d98) =
                                             chr(this,iVar7)->pModel;
                                        *(int *)(this + *(short *)(this + 0x3d90) * 0x14 +
                                                0x3d9c) = this + iVar7 * 0x510 + 0xb0;
                                        *(short *)(this + 0x3d90) =
                                             *(short *)(this + 0x3d90) + 1;
                                      }
                                    }
                                  }
                                  lVar11 = (long)(iVar7 + 1);
                                }
                              }
                              SetGenModel__6EffectFiP11tagModelSet(this->pBtlResult,
                                              *(undefined2 *)(this + 0x3d90),this + 0x3d94);
                              SetTarModel__6EffectFiP11tagModelSet(this->pBtlResult,
                                              *(undefined2 *)(this + 0x3d92),this + 0x3e84);
                              Run__6EffectFv(this->pBtlResult);
                              this->bFlags25 = this->bFlags25 & 0xef;
                              if (*(int *)(this + 0x45cc) != 0) {
                                *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
                              }
                              if (((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) {
                                if (-1 < this->nCmd1) {
                                  if ((chr(this,this->cActor)->bFlagsB &
                                      1) == 0) {
                                    *(short *)(this + 0x4630) =
                                         (short)this->nCmd1;
                                  }
                                  else {
                                    *(short *)(this + 0x4632) =
                                         (short)this->nCmd1;
                                  }
                                  this->nPartner = (short)this->nCmd1;
                                }
                              }
                              else if ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 1) &&
                                      (-1 < this->nCmd1)) {
                                if ((chr(this,this->cActor)->bFlagsB & 1
                                    ) == 0) {
                                  *(short *)(this + 0x4634) =
                                       (short)this->nCmd1;
                                }
                                else {
                                  *(short *)(this + 0x4636) =
                                       (short)this->nCmd1;
                                }
                              }
                              this->nStep = 9;
                              return;
                            }
                            if (sVar1 == 7) {
                              if (this->nCmdKind != 1) {
                                return;
                              }
                              if (chr(this,this->cActor)->bState !=
                                  '\a') {
                                return;
                              }
                              if ((long)((ulong)*(byte *)(*(int *)(this + this->cActor
                                                                            * 0x510 + 0x14c) + 0x4d0
                                                         ) << 0x3d) < 0) {
                                return;
                              }
                              if ((chr(this,this->cActor)->f4bc != 0)
                                 && (chr(this,this->cActor)->f4c0 !=
                                     -1)) {
                                cVar4 = SEEndCheck__6HNMSndFUii(uGpffff8374,0x60002003,
                                                        *(undefined4 *)
                                                         (this + this->cActor * 0x510
                                                         + 0x57c));
                                if (cVar4 == '\0') {
                                  return;
                                }
                                IOPRelease__6HNMSndFi(uGpffff8374,
                                                *(undefined4 *)
                                                 (this + this->cActor * 0x510 + 0x570)
                                               );
                              }
                              this->nStep = 8;
                              return;
                            }
                            if (sVar1 != 6) {
                              if (sVar1 != 5) {
                                if (sVar1 != 4) {
                                  if (sVar1 == 3) {
                                    if (((this->nCmdKind == 0) ||
                                        (this->nCmdKind == 2)) &&
                                       (*(short *)(unaff_s2_lo + 0x18) < 1000)) {
                                      if (-1 < *(short *)(this + this->cActor * 0x510
                                                         + 0x594)) {
                                        uVar5 = DataReadEntry__7CBattleFiii
                                                          (this,0xc,0x12,
                                                           *(undefined2 *)
                                                            (this + this->cActor *
                                                                      0x510 + 0x594));
                                        this->cDataId = uVar5;
                                      }
                                    }
                                    else if ((this->nCmdKind == 1) &&
                                            (*(int *)(this + this->cActor * 0x510 +
                                                     0x56c) != 0)) {
                                      iVar7 = this + this->cActor * 0x510;
                                      *(byte *)(iVar7 + 0xb1) = *(byte *)(iVar7 + 0xb1) & 0xfb | 4;
                                    }
                                    this->nDataSlot = 0xffffffff;
                                    if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x87) {
                                      cVar4 = CheckCycleHit__7CBattleFi
                                                        (this,this->nCmd1);
                                      if (cVar4 == '\x01') {
                                        uVar15 = rand();
                                        uVar16 = uVar15 & 3;
                                        if (((int)uVar15 < 0) && (uVar16 != 0)) {
                                          uVar16 = uVar16 - 4;
                                        }
                                        if (uVar16 == 0) {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x87)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                        else if (uVar16 == 1) {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfc)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                        else if (uVar16 == 2) {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfd)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                        else {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xfe)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                      }
                                      else {
                                        uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xf0);
                                        this->nDataSlot = uVar10;
                                      }
                                    }
                                    else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x89) {
                                      if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xe5) {
                                        if ((*(byte *)(this + 0x4654) & 3) == 1) {
                                          uVar10 = DataReadEntry__7CBattleFiii
                                                             (this,0xc,0xb,0x105);
                                          this->nDataSlot = uVar10;
                                        }
                                        else {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xe5)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                      }
                                      else if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0xde) {
                                        if (((*(byte *)(this + 0x4654) & 3) == 1) ||
                                           (cVar4 = Retail_CBattle_CheckAbilitySealed
                                                              (this,*(undefined4 *)
                                                                        (this + 0x48)),
                                           cVar4 != '\x01')) {
                                          uVar10 = DataReadEntry__7CBattleFiii
                                                             (this,0xc,0xb,0x104);
                                          this->nDataSlot = uVar10;
                                        }
                                        else {
                                          uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xde)
                                          ;
                                          this->nDataSlot = uVar10;
                                        }
                                      }
                                      else if (-1 < *(short *)(unaff_s2_lo + 0x18)) {
                                        if (*(short *)(unaff_s2_lo + 0x18) < 1000) {
                                          uVar10 = DataReadEntry__7CBattleFiii
                                                             (this,0xc,0xb,
                                                              *(undefined2 *)(unaff_s2_lo + 0x18));
                                          this->nDataSlot = uVar10;
                                        }
                                        else {
                                          uVar10 = DataReadEntry__7CBattleFiii
                                                             (this,0xc,0xb,
                                                              *(short *)(unaff_s2_lo + 0x18) + -1000
                                                             );
                                          this->nDataSlot = uVar10;
                                        }
                                      }
                                    }
                                    this->nStep = 4;
                                    return;
                                  }
                                  if (sVar1 == 2) {
                                    cVar4 = IsCapture__6SSHSysFv(uGpffff8408);
                                    if (cVar4 == '\0') {
                                      return;
                                    }
                                    if (*(int *)(this + 0x45d0) == 0) {
                                      lVar11 = __nw__FUi(0x5e0);
                                      uVar10 = 0;
                                      if (lVar11 != 0) {
                                        uVar10 = __ct__5JRingFsi(lVar11,0,0xc);
                                      }
                                      *(undefined4 *)(this + 0x45d0) = uVar10;
                                      SetPad__5JRingFP4CPad(uGpffff861c);
                                    }
                                    SetCallBack__5JRingFPFiPvPv_bPvUi(*(undefined4 *)(this + 0x45d0),0x472c10,
                                                    this,0x7c3);
                                    SetRingPos__5JRingFff(0x43aaaaab,0x43600000,
                                                    *(undefined4 *)(this + 0x45d0));
                                    iVar13 = this->nCmdKind;
                                    if (iVar13 == 2) {
                                      if ((((0 < *(short *)(unaff_s0_lo +
                                                            this->nCmd0_target * 0x40 + 0x22))
                                           && (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                               *(undefined2 *)
                                                                (unaff_s0_lo +
                                                                 this->nCmd0_target * 0x40 +
                                                                0x20),*(undefined2 *)
                                                                       (unaff_s0_lo +
                                                                        this->nCmd0_target *
                                                                        0x40 + 0x22),0,0),
                                              0 < *(short *)(unaff_s0_lo +
                                                             this->nCmd0_target * 0x40 + 0x26))
                                           ) && (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                                 *(undefined2 *)
                                                                  (unaff_s0_lo +
                                                                   this->nCmd0_target * 0x40 +
                                                                  0x24),*(undefined2 *)
                                                                         (unaff_s0_lo +
                                                                          this->nCmd0_target *
                                                                          0x40 + 0x26),0,0),
                                                0 < *(short *)(unaff_s0_lo +
                                                               this->nCmd0_target * 0x40 + 0x2a
                                                              ))) &&
                                         ((AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                           *(undefined2 *)
                                                            (unaff_s0_lo +
                                                             this->nCmd0_target * 0x40 + 0x28),
                                                           *(undefined2 *)
                                                            (unaff_s0_lo +
                                                             this->nCmd0_target * 0x40 + 0x2a),
                                                           0,0),
                                          0 < *(short *)(unaff_s0_lo +
                                                         this->nCmd0_target * 0x40 + 0x2e) &&
                                          (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                           *(undefined2 *)
                                                            (unaff_s0_lo +
                                                             this->nCmd0_target * 0x40 + 0x2c),
                                                           *(undefined2 *)
                                                            (unaff_s0_lo +
                                                             this->nCmd0_target * 0x40 + 0x2e),
                                                           0,0),
                                          0 < *(short *)(unaff_s0_lo +
                                                         this->nCmd0_target * 0x40 + 0x32)))))
                                      {
                                        AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x30),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x32),0,0
                                                       );
                                      }
                                      if (0 < *(short *)(unaff_s0_lo +
                                                         this->nCmd0_target * 0x40 + 0x36)) {
                                        AddModulateArea__5JRingFssssP7_rgba32P7_rgba32P7_rgba32(*(undefined4 *)(this + 0x45d0),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x34),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x36),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x38),
                                                        *(undefined2 *)
                                                         (unaff_s0_lo +
                                                          this->nCmd0_target * 0x40 + 0x3a),0,0
                                                        ,0);
                                      }
                                    }
                                    else if (iVar13 == 1) {
                                      AddStrikeArea__5JRingFsssP7_rgba32P7_rgba32(*(undefined4 *)(this + 0x45d0),
                                                      *(undefined2 *)
                                                       (iVar7 + this->nCmd0_target * 0x30 +
                                                       0x1c),*(undefined2 *)
                                                              (iVar7 + this->nCmd0_target *
                                                                       0x30 + 0x1e),
                                                      *(undefined2 *)
                                                       (iVar7 + this->nCmd0_target * 0x30 +
                                                       0x20),0,0);
                                    }
                                    else if (iVar13 == 0) {
                                      if (((0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                          0x22)) &&
                                          (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                           *(undefined2 *)
                                                            (iVar8 + this->nCmd0_target * 0x44
                                                            + 0x20),*(undefined2 *)
                                                                     (iVar8 + *(int *)(this + 0x44
                                                                                      ) * 0x44 +
                                                                     0x22),0,0),
                                          0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                        0x26))) &&
                                         ((AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                           *(undefined2 *)
                                                            (iVar8 + this->nCmd0_target * 0x44
                                                            + 0x24),*(undefined2 *)
                                                                     (iVar8 + *(int *)(this + 0x44
                                                                                      ) * 0x44 +
                                                                     0x26),0,0),
                                          0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                        0x2a) &&
                                          ((AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                            *(undefined2 *)
                                                             (iVar8 + this->nCmd0_target * 0x44
                                                             + 0x28),*(undefined2 *)
                                                                      (iVar8 + *(int *)(this + 
                                                  0x44) * 0x44 + 0x2a),0,0),
                                           0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                         0x2e) &&
                                           (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                            *(undefined2 *)
                                                             (iVar8 + this->nCmd0_target * 0x44
                                                             + 0x2c),*(undefined2 *)
                                                                      (iVar8 + *(int *)(this + 
                                                  0x44) * 0x44 + 0x2e),0,0),
                                           0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                         0x32))))))) {
                                        AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                                        *(undefined2 *)
                                                         (iVar8 + this->nCmd0_target * 0x44 +
                                                         0x30),*(undefined2 *)
                                                                (iVar8 + this->nCmd0_target *
                                                                         0x44 + 0x32),0,0);
                                      }
                                      if (0 < *(short *)(iVar8 + this->nCmd0_target * 0x44 +
                                                        0x36)) {
                                        AddModulateArea__5JRingFssssP7_rgba32P7_rgba32P7_rgba32(*(undefined4 *)(this + 0x45d0),
                                                        *(undefined2 *)
                                                         (iVar8 + this->nCmd0_target * 0x44 +
                                                         0x34),*(undefined2 *)
                                                                (iVar8 + this->nCmd0_target *
                                                                         0x44 + 0x36),
                                                        *(undefined2 *)
                                                         (iVar8 + this->nCmd0_target * 0x44 +
                                                         0x38),*(undefined2 *)
                                                                (iVar8 + this->nCmd0_target *
                                                                         0x44 + 0x3a),0,0,0);
                                      }
                                    }
                                    if ((*(char *)(this + 0x4866) == '\x01') &&
                                       (*(char *)(this + 0x4867) == '\n')) {
                                      SetMode__5JRingFsssss(*(undefined4 *)(this + 0x45d0),5,0,0,0,0);
                                    }
                                    else {
                                      SetMode__5JRingFsssss(*(undefined4 *)(this + 0x45d0),5,1,1,4,3);
                                    }
                                    if (((((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) &&
                                          (-1 < sVar6)) &&
                                         ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x86)) ||
                                        ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50)) &&
                                       (this->wTurnPendMask != 0)) {
                                      sVar1 = this->nComboCnt;
                                      if (sVar1 == 2) {
                                        fVar19 = 0.6;
                                      }
                                      else if (sVar1 == 1) {
                                        fVar19 = 0.75;
                                      }
                                      else if (sVar1 == 0) {
                                        fVar19 = 0.9;
                                      }
                                      else {
                                        fVar19 = 0.5;
                                      }
                                      iStack_4 = 0;
                                      fVar18 = 0.0;
                                      for (uVar15 = 0; (int)uVar15 < 0xc; uVar15 = uVar15 + 1) {
                                        if (((uint)this->wTurnPendMask & 1 << (uVar15 & 0x1f)
                                            ) != 0) {
                                          fVar18 = fVar18 + (float)(int)*(short *)(iGpffff83b4 +
                                                                                   *(short *)(this
                                                                                              + *(
                                                  char *)(this + 0x2c) * 0x510 + 0x120) * 0xc0 +
                                                  chr(this,uVar15)->nCharId * 2 +
                                                  0x7c) / 100.0;
                                          iStack_4 = iStack_4 + 1;
                                        }
                                      }
                                      if (iStack_4 != 0) {
                                        fVar19 = fVar19 + fVar18 / ((float)iStack_4 * 500.0);
                                      }
                                      SetCombo__5JRingFf(fVar19,*(undefined4 *)(this + 0x45d0));
                                    }
                                    bVar2 = *(byte *)(iGpffff83b4 +
                                                      *(short *)(this + this->cActor *
                                                                          0x510 + 0x120) * 0xc0 +
                                                     0x98) >> 6;
                                    if (bVar2 == 3) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 0xc;
                                    }
                                    else if (bVar2 == 2) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 8;
                                    }
                                    else if (bVar2 == 1) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 4;
                                    }
                                    else if (bVar2 == 0) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3;
                                    }
                                    iVar7 = this->nCmdKind;
                                    if (iVar7 == 2) {
                                      SetJRingStatus__7CBattleFiiPi
                                                (this,this->cActor,1,0);
                                    }
                                    else if (iVar7 == 1) {
                                      SetJRingStatus__7CBattleFiiPi
                                                (this,this->cActor,3,0);
                                    }
                                    else if (iVar7 == 0) {
                                      SetJRingStatus__7CBattleFiiPi
                                                (this,this->cActor,2,0);
                                    }
                                    if (((*(byte *)(this + this->cActor * 0x510 + 0xb4
                                                   ) & 1) == 0) &&
                                       ((*(byte *)(iGpffff83b4 +
                                                   *(short *)(this + this->cActor *
                                                                       0x510 + 0x120) * 0xc0 + 0x99)
                                        & 1) != 0)) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 4;
                                      *(undefined2 *)(*(int *)(this + 0x45d0) + 0x58c) = 10;
                                    }
                                    else if (this->nCmd3 != 0) {
                                      *(short *)(*(int *)(this + 0x45d0) + 0x58c) =
                                           (short)this->nCmd3 + 2;
                                    }
                                    RingActive__5JRingFv(*(undefined4 *)(this + 0x45d0));
                                    if (this->nComboCnt != 0) {
                                      *(byte *)(*(int *)(this + 0x45d0) + 0x42) =
                                           *(byte *)(*(int *)(this + 0x45d0) + 0x42) & 0x7f | 0x80
                                      ;
                                    }
                                    *(undefined2 *)(this + 0x45d6) = 0;
                                    if (((*(char *)(this + 0x4866) != '\x01') &&
                                        (*(char *)(this + 0x4866) != '\x02')) &&
                                       ((*(short *)(*(int *)(this + 0x45d0) + 0x58c) == 0 &&
                                        ((*(byte *)(this + this->cActor * 0x510 + 0xb4
                                                   ) & 1) == 0)))) {
                                      iVar7 = iGpffff83b4 +
                                              *(short *)(this + this->cActor * 0x510 +
                                                        0x120) * 0x24;
                                      *(int *)(iVar7 + 0x150c) = *(int *)(iVar7 + 0x150c) + 1;
                                      if (((long)((ulong)*(byte *)(*(int *)(this + 0x45d0) + 0x512
                                                                  ) << 0x3a) < 0) &&
                                         (*(byte *)(iGpffff83b4 +
                                                    *(short *)(this + this->cActor *
                                                                        0x510 + 0x120) * 0xc0 + 0x98
                                                   ) >> 6 != 1)) {
                                        iVar7 = iGpffff83b4 +
                                                *(short *)(this + this->cActor * 0x510
                                                          + 0x120) * 0x24;
                                        *(int *)(iVar7 + 0x1510) = *(int *)(iVar7 + 0x1510) + 1;
                                      }
                                      *(short *)(this + 0x4906) = *(short *)(this + 0x4906) + 1;
                                    }
                                    this->nStep = 3;
                                    this->bFlags24 = this->bFlags24 & 0xbf;
                                    if (((((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 0) ||
                                          (sVar6 < 0)) ||
                                         ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x86)) ||
                                        ((this->wTurnPendMask == 0 &&
                                         (this->nComboCnt == 0)))) &&
                                       ((((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x50 ||
                                         (this->wTurnPendMask == 0)) &&
                                        ((*(byte *)(this + this->cActor * 0x510 + 0xb4
                                                   ) & 1) == 0)))) {
                                      *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0x7f
                                      ;
                                    }
                                    if (*(char *)(this + 0x4866) != '\x01') {
                                      return;
                                    }
                                    if (*(char *)(this + 0x4867) != '\n') {
                                      return;
                                    }
                                    this->nStep = 100;
                                    return;
                                  }
                                  if (sVar1 == 1) {
                                    if (*(int *)(this->pParamDisp + 0x38) != 0) {
                                      return;
                                    }
                                    if (iGpffff8618->nCmd1 != 0) {
                                      return;
                                    }
                                    this->bFlags24 = this->bFlags24 & 0xfe | 1;
                                    this->bFlags24 = this->bFlags24 & 0xfd | 2;
                                    ScreenCapture__6SSHSysFi(uGpffff8408,1);
                                    this->nStep = 2;
                                    return;
                                  }
                                  if (sVar1 != 0) {
                                    return;
                                  }
                                  cVar4 = AllCSERelease__7CBattleFv(this);
                                  if (cVar4 == '\0') {
                                    return;
                                  }
                                  CloseBattleUI__7CBattleFb(this,1);
                                  if (chr(this,this->cActor)->bState ==
                                      '\x11') {
                                    *(undefined1 *)
                                     (this + this->cActor * 0x510 + 0xb8) = 7;
                                    *(undefined1 *)
                                     (this + this->cActor * 0x510 + 0xb9) = 1;
                                  }
                                  iVar7 = this + this->cActor * 0x510;
                                  *(byte *)(iVar7 + 0xb5) = *(byte *)(iVar7 + 0xb5) & 0xf7;
                                  if ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 1) &&
                                     (cVar4 = Retail_CBattle_SetAllChrEffMask(this,1),
                                     cVar4 == '\0')) {
                                    return;
                                  }
                                  if (chr(this,this->cActor)->bState !=
                                      '\a') {
                                    return;
                                  }
                                  if (chr(this,this->cActor)->bState2 !=
                                      '\x02') {
                                    return;
                                  }
                                  if ((long)((ulong)*(byte *)(*(int *)(this + *(char *)(this + 
                                                  0x2c) * 0x510 + 0x14c) + 0x4d0) << 0x3d) < 0) {
                                    return;
                                  }
                                  *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
                                  GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                                            (this,this->cActor,
                                             this->nCmd1,
                                             ((ulong)*(ushort *)(unaff_s2_lo + 4) & 0x1ff) >> 7,
                                             ((ulong)*(byte *)(unaff_s2_lo + 5) & 0xf) >> 1,
                                             ((ulong)*(byte *)(unaff_s2_lo + 5) & 0x3f) >> 4,
                                             unaff_s2_lo + 8,&iStack_4);
                                  if (iStack_4 == 0) {
                                    iVar7 = this->nCmdKind;
                                    if (iVar7 == 7) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,0,0,8,this->nCmd0_target,
                                                 unaff_s2_lo,unaff_s2_lo + 8,
                                                 this->cActor);
                                    }
                                    else if ((iVar7 == 3) || (iVar7 == 2)) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,0,0,1,this->nCmd0_target,
                                                 unaff_s2_lo,unaff_s2_lo + 8,
                                                 this->cActor);
                                    }
                                    else if (iVar7 == 0) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,0,0,2,this->nCmd0_target,
                                                 unaff_s2_lo,unaff_s2_lo + 8,
                                                 this->cActor);
                                    }
                                    else if (iVar7 == 1) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,0,0,3,this->nCmd0_target,
                                                 unaff_s2_lo,unaff_s2_lo + 8,
                                                 this->cActor);
                                    }
                                  }
                                  else {
                                    iVar7 = this->nCmdKind;
                                    if (iVar7 == 7) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,iStack_4,aiStack_40,8,
                                                 this->nCmd0_target,unaff_s2_lo,
                                                 unaff_s2_lo + 8,this->cActor);
                                    }
                                    else if ((iVar7 == 3) || (iVar7 == 2)) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,iStack_4,aiStack_40,1,
                                                 this->nCmd0_target,unaff_s2_lo,
                                                 unaff_s2_lo + 8,this->cActor);
                                    }
                                    else if (iVar7 == 0) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,iStack_4,aiStack_40,2,
                                                 this->nCmd0_target,unaff_s2_lo,
                                                 unaff_s2_lo + 8,this->cActor);
                                    }
                                    else if (iVar7 == 1) {
                                      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                                                ((float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0,
                                                 this,iStack_4,aiStack_40,3,
                                                 this->nCmd0_target,unaff_s2_lo,
                                                 unaff_s2_lo + 8,this->cActor);
                                    }
                                    if (((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) {
                                      for (iVar7 = 0; iVar7 < iStack_4; iVar7 = iVar7 + 1) {
                                        SetSelectChr__13TurnOrderDispFii
                                                  (this->pTurnOrderDisp,
                                                   aiStack_40[iVar7],2);
                                      }
                                    }
                                    else {
                                      for (iVar7 = 0; iVar7 < iStack_4; iVar7 = iVar7 + 1) {
                                        SetSelectChr__13TurnOrderDispFii
                                                  (this->pTurnOrderDisp,
                                                   aiStack_40[iVar7],1);
                                      }
                                    }
                                  }
                                  this->nShortcutTarget = 0xffffffff;
                                  uVar10 = SetBtlMessage__7CBattleFiPv(this,0x146,unaff_s6);
                                  this->nShortcutTarget = uVar10;
                                  if (((long)this->nCmd1 ==
                                       (long)this->cActor) ||
                                     (this->nCmd1 < 0)) {
                                    SetCharacterCamera3__9BtlCameraFib
                                              (this->pCamera,
                                               this->cActor,1);
                                  }
                                  else if (-1 < this->nCmd1) {
                                    SetTargetAngle__7CBattleFii
                                              (this,this->cActor,
                                               this->nCmd1);
                                    Retail_BtlModel_PrewarmDynamics
                                              (*(undefined4 *)
                                                (this + this->cActor * 0x510 + 0x14c))
                                    ;
                                    SetJudgementRingCamera1__9BtlCameraFiib
                                              (this->pCamera,
                                               this->cActor,
                                               this->nCmd1,1);
                                  }
                                  this->nStep = 1;
                                  MaxComboFunc__7CBattleFi(this,this->cActor);
                                  FilterOff__9BtlSocketFbb(iGpffff836c,0,1);
                                  if ((chr(this,this->cActor)->bFlagsB &
                                      1) != 0) {
                                    return;
                                  }
                                  iVar7 = this->nCmdKind;
                                  if (((iVar7 == 3) || (iVar7 == 7)) || (iVar7 == 2)) {
                                    *(byte *)(this + 0x4899) =
                                         *(byte *)(this + 0x4899) & 0xfd | 2;
                                    return;
                                  }
                                  if (iVar7 == 1) {
                                    *(byte *)(this + 0x4899) =
                                         *(byte *)(this + 0x4899) & 0xf7 | 8;
                                    return;
                                  }
                                  if (iVar7 != 0) {
                                    return;
                                  }
                                  *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xfb | 4
                                  ;
                                  return;
                                }
                                cVar4 = BtlChrReadyCheck__7CBattleFv(this);
                                if (cVar4 == '\0') {
                                  return;
                                }
                                if ((*(byte *)(this + 0x45d6) & 1) == 0) {
                                  return;
                                }
                                if (-1 < (long)((ulong)this->bFlags24 << 0x39)) {
                                  return;
                                }
                                if ((long)((ulong)this->bFlags24 << 0x3e) < 0) {
                                  ClearCapture__6SSHSysFv(uGpffff8408);
                                  this->bFlags24 = this->bFlags24 & 0xfd;
                                }
                                this->bFlags24 = this->bFlags24 & 0xfe;
                                FilterOn__9BtlSocketFbb(iGpffff836c,1,1);
                                if ((-1 < (long)((ulong)*(byte *)(this + 0x45d6) << 0x3b)) &&
                                   ((chr(this,this->cActor)->bFlagsB & 1
                                    ) == 0)) {
                                  if (1 < ((ulong)*(byte *)(this + 0x45d6) & 7) >> 1) {
                                    iVar7 = iGpffff83b4 +
                                            *(short *)(this + this->cActor * 0x510 +
                                                      0x120) * 0x24;
                                    *(int *)(iVar7 + 0x1514) = *(int *)(iVar7 + 0x1514) + 1;
                                  }
                                  if (((((ulong)*(byte *)(this + 0x45d6) & 7) >> 1 == 3) &&
                                      ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3a) < 0)) &&
                                     (*(byte *)(iGpffff83b4 +
                                                *(short *)(this + this->cActor * 0x510
                                                          + 0x120) * 0xc0 + 0x98) >> 6 != 1)) {
                                    iVar7 = iGpffff83b4 +
                                            *(short *)(this + this->cActor * 0x510 +
                                                      0x120) * 0x24;
                                    *(int *)(iVar7 + 0x1518) = *(int *)(iVar7 + 0x1518) + 1;
                                  }
                                  if (((long)((ulong)*(byte *)(this + 0x45d6) << 0x39) < 0) &&
                                     (iVar7 = iGpffff83b4 +
                                              *(short *)(this + this->cActor * 0x510 +
                                                        0x120) * 0x24,
                                     *(int *)(iVar7 + 0x151c) = *(int *)(iVar7 + 0x151c) + 1,
                                     (long)((ulong)*(byte *)(this + 0x45d6) << 0x3c) < 0)) {
                                    iVar7 = iGpffff83b4 +
                                            *(short *)(this + this->cActor * 0x510 +
                                                      0x120) * 0x24;
                                    *(int *)(iVar7 + 0x1520) = *(int *)(iVar7 + 0x1520) + 1;
                                  }
                                }
                                if ((((-1 < (long)((ulong)*(byte *)(this + 0x45d6) << 0x3c)) &&
                                     ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 0 ||
                                      (-1 < sVar6)))) &&
                                    ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 0 ||
                                     ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x86)))) &&
                                   (this->wTurnPendMask = 0,
                                   (long)((ulong)*(byte *)(this + 0x45d6) << 0x39) < 0)) {
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
                                }
                                if ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3b) < 0) {
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
                                }
                                if (1 < ((ulong)*(byte *)(this + 0x45d6) & 7) >> 1) {
                                  this->nStep = 6;
                                  if ((((((ulong)*(byte *)(this + 0x45d6) & 7) >> 1 < 3) &&
                                       ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3a) < 0)) &&
                                      (*(byte *)(iGpffff83b4 +
                                                 *(short *)(this + this->cActor *
                                                                     0x510 + 0x120) * 0xc0 + 0x98)
                                       >> 6 != 1)) &&
                                     ((chr(this,this->cActor)->bFlagsB &
                                      1) == 0)) {
                                    *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
                                  }
                                  if ((*(byte *)(iGpffff83b4 +
                                                 *(short *)(this + this->cActor *
                                                                     0x510 + 0x120) * 0xc0 + 0x98)
                                       >> 6 == 1) &&
                                     ((*(byte *)(this + 0x4898) =
                                            *(byte *)(this + 0x4898) & 0xbf,
                                      *(int *)(this + 0x45e8) < 10000 ||
                                      ((*(short *)(this + 0x45d4) == 1 &&
                                       (*(int *)(this + 0x45e0) < 10000)))))) {
                                    *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
                                  }
                                  if ((this->nComboCnt != 0) &&
                                     ((chr(this,this->cActor)->bFlagsB &
                                      1) == 0)) {
                                    AddFriendship__7CBattleFiis
                                              (this,*(undefined2 *)
                                                        (this + this->cActor * 0x510 +
                                                        0x120),
                                               *(undefined2 *)
                                                (this + this->cActorB * 0x510 + 0x120),
                                               100);
                                  }
                                  if ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x89) {
                                    return;
                                  }
                                  if (((ulong)*(byte *)(this + 0x45d6) & 7) >> 1 == 3) {
                                    uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0x89);
                                    this->nDataSlot = uVar10;
                                    return;
                                  }
                                  uVar10 = DataReadEntry__7CBattleFiii(this,0xc,0xb,0xf9);
                                  this->nDataSlot = uVar10;
                                  return;
                                }
                                this->nStep = 5;
                                ComboStopOff__Fi(0xffffffffffffffff);
                                if ((chr(this,this->cActor)->bFlagsB & 1
                                    ) == 0) {
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
                                  *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
                                }
                              }
                              if (-1 < this->cDataId) {
                                if (*(char *)(this + this->cDataId * 0x18 + 0x40c5)
                                    != '\x03') {
                                  return;
                                }
                                IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
                                DataRelease__7CBattleFiib
                                          (this,this->cDataId,0xc,0);
                                this->nIopHandle = 0xffffffff;
                                this->cDataId = 0xff;
                              }
                              if ((chr(this,this->cActor)->f4bc != 0)
                                 && (chr(this,this->cActor)->f4c0 !=
                                     -1)) {
                                if ((long)((ulong)*(byte *)(this + this->cActor *
                                                                     0x510 + 0xb1) << 0x3d) < 0) {
                                  return;
                                }
                                cVar4 = IsIOPRelease__6HNMSndFi(uGpffff8374,
                                                        *(undefined4 *)
                                                         (this + this->cActor * 0x510
                                                         + 0x570));
                                if (cVar4 == '\0') {
                                  IOPRelease__6HNMSndFi(uGpffff8374,
                                                  *(undefined4 *)
                                                   (this + this->cActor * 0x510 +
                                                   0x570));
                                }
                                cVar4 = IOPReleaseCheck__6HNMSndFi(uGpffff8374,
                                                        *(undefined4 *)
                                                         (this + this->cActor * 0x510
                                                         + 0x570));
                                if (cVar4 == '\0') {
                                  return;
                                }
                                chr(this,this->cActor)->f4c0 =
                                     0xffffffff;
                              }
                              if (-1 < this->nDataSlot) {
                                if (-1 < (long)((ulong)*(byte *)(this + this->nDataSlot
                                                                          * 0x18 + 0x40c4) << 0x3a))
                                {
                                  return;
                                }
                                DataRelease__7CBattleFiib
                                          (this,this->nDataSlot,0xc,0);
                              }
                              if (-1 < this->nShortcutTarget) {
                                SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
                              }
                              this->nPhase = 0x14;
                              this->nStep = 0;
                              this->nCmdKind = 0;
                              this->nCmdMask = 1 << ((int)this->cActor & 0x1fU)
                              ;
                              this->flTurnPush =
                                   (float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0;
                              if (((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) ||
                                  ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50)) &&
                                 (this->wTurnPendMask != 0)) {
                                return;
                              }
                              if (this->nComboCnt != 0) {
                                return;
                              }
                              this->bFlags25 = this->bFlags25 & 0xfb;
                              return;
                            }
                            if (-1 < this->cDataId) {
                              if (*(char *)(this + this->cDataId * 0x18 + 0x40c5) !=
                                  '\x03') {
                                return;
                              }
                              auVar20 = _lqc2(*(undefined1 (*) [16])
                                               (this + this->cActor * 0x510 + 0x160));
                              auVar21 = _lqc2(*(undefined1 (*) [16])
                                               (this + this->cActor * 0x510 + 0x3a0));
                              auVar20 = _vadd(auVar20,auVar21);
                              auStack_80 = _sqc2(auVar20);
                              __ct__7FVectorFPC7FVector(auStack_60,auStack_80);
                              uStack_50 = auStack_60._0_4_;
                              uStack_4c = auStack_60._4_4_;
                              uStack_48 = uStack_58;
                              uStack_44 = uStack_54;
                              if (((chr(this,this->cActor)->bFlagsB & 1)
                                   == 0) &&
                                 (-1 < (long)((ulong)*(byte *)(this + this->cActor *
                                                                        0x510 + 0xb1) << 0x3e))) {
                                if (((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) {
                                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000000,1,&uStack_50);
                                }
                                else if (((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 1) {
                                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000001,1,&uStack_50);
                                }
                                else {
                                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000002,1,&uStack_50);
                                }
                              }
                              else {
                                PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000000,1,&uStack_50);
                              }
                              DataRelease__7CBattleFiib
                                        (this,this->cDataId,0xc,0);
                            }
                            if ((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) ||
                               ((*(short *)(unaff_s2_lo + 0x18) == 0x50 &&
                                (this->wTurnPendMask != 0)))) {
                              for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                                if (((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                                     ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e
                                            ) < 0)) &&
                                    (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2 <<
                                                0x3c))) &&
                                   (((0 < chr(this,iVar7)->nHp &&
                                     ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3a
                                            ) < 0)) &&
                                    (('\x18' < chr(this,iVar7)->bState &&
                                     ((chr(this,iVar7)->bState < '+' &&
                                      (chr(this,iVar7)->f458 + 1 ==
                                       *(int *)(this + 0x40))))))))) {
                                  iVar8 = this + iVar7 * 0x510;
                                  *(byte *)(iVar8 + 0x504) = *(byte *)(iVar8 + 0x504) & 0xef | 0x10;
                                  chr(this,iVar7)->f458 =
                                       *(undefined4 *)(this + 0x40);
                                  chr(this,iVar7)->f464 =
                                       ((float)chr(this,iVar7)->f460 * 2.0) /
                                       100.0;
                                  chr(this,iVar7)->f468 = 0;
                                  if (((ulong)chr(this,iVar7)->bFlagsB & 7) >> 1 !=
                                      0) {
                                    chr(this,iVar7)->f468 = 0x3dcccccd;
                                  }
                                }
                              }
                            }
                            else {
                              ComboStopOff__Fi(0xffffffffffffffff);
                            }
                            if (this->nCmdKind == 1) {
                              chr(this,this->cActor)->bState =
                                   0x16;
                              chr(this,this->cActor)->bState2 = 0;
                              this->nStep = 7;
                              this->flMenuTimer = 0;
                              if (chr(this,this->cActor)->f4c0 != -1)
                              {
                                auVar20 = _lqc2(*(undefined1 (*) [16])
                                                 (this + this->cActor * 0x510 + 0x160)
                                               );
                                auVar21 = _lqc2(*(undefined1 (*) [16])
                                                 (this + this->cActor * 0x510 + 0x3a0)
                                               );
                                auVar20 = _vadd(auVar20,auVar21);
                                auStack_90 = _sqc2(auVar20);
                                __ct__7FVectorFPC7FVector(auStack_70,auStack_90);
                                uStack_50 = auStack_70._0_4_;
                                uStack_4c = auStack_70._4_4_;
                                uStack_48 = uStack_68;
                                uStack_44 = uStack_64;
                                uVar10 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60002003,1,&uStack_50);
                                chr(this,this->cActor)->f4cc =
                                     uVar10;
                              }
                              if (((long)this->nCmd1 == (long)this->cActor)
                                 || (this->nCmd1 < 0)) {
                                SetRetailCamera2__9BtlCameraFUiUib
                                          (this->pCamera,
                                           this->cActor,0xffffffffffffffff,1);
                              }
                              else {
                                SetTargetAngle__7CBattleFii
                                          (this,this->cActor,
                                           this->nCmd1);
                                Retail_BtlModel_PrewarmDynamics
                                          (*(undefined4 *)
                                            (this + this->cActor * 0x510 + 0x14c));
                                SetRetailCamera2__9BtlCameraFUiUib
                                          (this->pCamera,
                                           this->cActor,
                                           this->nCmd1,1);
                              }
                            }
                            else {
                              if (*(short *)(unaff_s2_lo + 0x18) < 1000) {
                                chr(this,this->cActor)->bState =
                                     0x10;
                                chr(this,this->cActor)->bState2 =
                                     0;
                                if (((long)this->nCmd1 == (long)this->cActor
                                    ) || (this->nCmd1 < 0)) {
                                  SetRetailCamera1__9BtlCameraFUiUib
                                            (this->pCamera,
                                             this->cActor,0xffffffffffffffff,1);
                                }
                                else {
                                  SetTargetAngle__7CBattleFii
                                            (this,this->cActor,
                                             this->nCmd1);
                                  Retail_BtlModel_PrewarmDynamics
                                            (*(undefined4 *)
                                              (this + this->cActor * 0x510 + 0x14c));
                                  SetRetailCamera1__9BtlCameraFUiUib
                                            (this->pCamera,
                                             this->cActor,
                                             this->nCmd1,1);
                                }
                              }
                              this->nStep = 8;
                            }
                            this->cMesWinId2 = 0xff;
                            if ((chr(this,this->cActor)->bFlagsB & 1) !=
                                0) {
                              return;
                            }
                            if (this->wTurnPendMask == 0) {
                              return;
                            }
                            if (-1 < (long)((ulong)*(byte *)(iGpffff83b4 + 3) << 0x3e)) {
                              return;
                            }
                            if ((((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 != 0) ||
                                 (sVar6 < 0)) ||
                                ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x86)) &&
                               ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 != 0x50)) {
                              return;
                            }
                            if ((long)((ulong)this->bFlags24 << 0x3a) < 0) {
                              return;
                            }
                            iStack_4 = 0;
                            for (uVar15 = 0; (int)uVar15 < 0xc; uVar15 = uVar15 + 1) {
                              if (((uint)this->wTurnPendMask & 1 << (uVar15 & 0x1f)) != 0) {
                                if ((long)((ulong)chr(this,uVar15)->bFlagsA1 << 0x3e)
                                    < 0) {
                                  if (((-1 < *(char *)(iGpffff83b4 +
                                                       chr(this,uVar15)->fa *
                                                       0x10 + 0x119c)) ||
                                      (-1 < *(char *)(iGpffff83b4 +
                                                      chr(this,uVar15)->fa *
                                                      0x10 + 0x11a0))) ||
                                     ((-1 < *(char *)(iGpffff83b4 +
                                                      chr(this,uVar15)->fa *
                                                      0x10 + 0x11a4) ||
                                      (-1 < *(char *)(iGpffff83b4 +
                                                      chr(this,uVar15)->fa *
                                                      0x10 + 0x11a8))))) {
                                    iStack_4 = iStack_4 + 1;
                                  }
                                }
                                else if (chr(this,uVar15)->nCharId == 6) {
                                  sVar6 = *(short *)(iGpffff836c + 0x750);
                                  if ((sVar6 == 4) || (sVar6 == 3)) {
                                    if ((-1 < *(char *)(iGpffff83b4 + 0x132c)) ||
                                       (((-1 < *(char *)(iGpffff83b4 + 0x1330) ||
                                         (-1 < *(char *)(iGpffff83b4 + 0x1334))) ||
                                        (-1 < *(char *)(iGpffff83b4 + 0x1338))))) {
                                      iStack_4 = iStack_4 + 1;
                                    }
                                  }
                                  else if (sVar6 == 2) {
                                    if (((-1 < *(char *)(iGpffff83b4 + 0x131c)) ||
                                        (-1 < *(char *)(iGpffff83b4 + 0x1320))) ||
                                       ((-1 < *(char *)(iGpffff83b4 + 0x1324) ||
                                        (-1 < *(char *)(iGpffff83b4 + 0x1328))))) {
                                      iStack_4 = iStack_4 + 1;
                                    }
                                  }
                                  else if (sVar6 == 1) {
                                    if (((-1 < *(char *)(iGpffff83b4 + 0x130c)) ||
                                        (-1 < *(char *)(iGpffff83b4 + 0x1310))) ||
                                       ((-1 < *(char *)(iGpffff83b4 + 0x1314) ||
                                        (-1 < *(char *)(iGpffff83b4 + 0x1318))))) {
                                      iStack_4 = iStack_4 + 1;
                                    }
                                  }
                                  else if ((((-1 < *(char *)(iGpffff83b4 + 0x111c)) ||
                                            (-1 < *(char *)(iGpffff83b4 + 0x1120))) ||
                                           (-1 < *(char *)(iGpffff83b4 + 0x1124))) ||
                                          (-1 < *(char *)(iGpffff83b4 + 0x1128))) {
                                    iStack_4 = iStack_4 + 1;
                                  }
                                }
                                else if (((-1 < *(char *)(iGpffff83b4 +
                                                          *(short *)(this + uVar15 * 0x510 + 0x120
                                                                    ) * 0x10 + 0x10bc)) ||
                                         (-1 < *(char *)(iGpffff83b4 +
                                                         chr(this,uVar15)->nCharId
                                                         * 0x10 + 0x10c0))) ||
                                        ((-1 < *(char *)(iGpffff83b4 +
                                                         chr(this,uVar15)->nCharId
                                                         * 0x10 + 0x10c4) ||
                                         (-1 < *(char *)(iGpffff83b4 +
                                                         chr(this,uVar15)->nCharId
                                                         * 0x10 + 0x10c8))))) {
                                  iStack_4 = iStack_4 + 1;
                                }
                              }
                            }
                            if (iStack_4 == 0) {
                              return;
                            }
                            if (*(int *)(this + 0x4624) == 0) {
                              lVar11 = __nw__FUi(0xb1c);
                              uVar10 = 0;
                              if (lVar11 != 0) {
                                uVar10 = __ct__7BtlMenuFib(lVar11,0x17,0);
                              }
                              *(undefined4 *)(this + 0x4624) = uVar10;
                            }
                            else {
                              SetMode__7BtlMenuFib(*(undefined4 *)(this + 0x4624),0x17,0);
                            }
                            *(int *)(iGpffff83b4 + 0x14dc) = *(int *)(iGpffff83b4 + 0x14dc) + 1;
                            return;
                          }
                          if ((this->pBtlResult != 0) &&
                             (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                            return;
                          }
                          iVar7 = this->pBtlResult;
                          if (iVar7 != 0) {
                            (**(code **)(*(int *)(iVar7 + 0x14) + 8))(iVar7,1);
                          }
                          this->pBtlResult = 0;
                          SetAlphaMode__8BtlFaderFUl(0x44);
                          Retail_CBattle_ReleaseChrWait(this);
                          this->nStep = 0xc;
                        }
                        sVar6 = GetFaderMode__8BtlFaderFv();
                        if (sVar6 != 0) {
                          return;
                        }
                        *(undefined4 *)(this + 0x5c) = 0;
                        while ((*(uint *)(this + 0x58) & 1 << (*(uint *)(this + 0x5c) & 0x1f))
                               == 0) {
                          *(int *)(this + 0x5c) = *(int *)(this + 0x5c) + 1;
                        }
                        iVar7 = GetRegDat__9RegDatApiFiii(0x3c,4,0xffffffffffffffff);
                        uVar12 = GetRegDat__9RegDatApiFiii(9,*(undefined2 *)
                                                    (iVar7 + *(int *)(this + 0x5c) * 0x40 + 2),
                                                 0xffffffffffffffff);
                        uVar10 = SetBtlMessage__7CBattleFiPv(this,0x7a,uVar12);
                        this->nShortcutTarget = uVar10;
                        PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x1002,1,0);
                        this->nStep = 0xd;
                        return;
                      }
                      if (chr(this,this->cActor)->nMonId != 499) {
                        cVar4 = DestinationSearch__7CBattleFi
                                          (this,this->cActor);
                        if (cVar4 != '\x01') {
                          return;
                        }
                        if (4 < this->nDestCount) {
                          DestinationListUp__7CBattleFii(this,4,this->cActor);
                        }
                      }
                      this->nStep = 0x13;
                    }
                    bVar3 = false;
                    if (*(int *)(this + 0x4624) != 0) {
                      if (*(short *)(*(int *)(this + 0x4624) + 0x28) != 0x14) {
                        *(undefined2 *)(*(int *)(this + 0x4624) + 0x28) = 0x17;
                        *(undefined2 *)(*(int *)(this + 0x4624) + 0x2a) = 3;
                      }
                      bVar3 = true;
                    }
                    if (bVar3) {
                      return;
                    }
                    this->nDestIdx = 0;
                    if (chr(this,this->cActor)->nMonId != 499) {
                      iVar7 = rand();
                      iVar7 = iVar7 % (int)this->nDestCount;
                      chr(this,this->cActor)->aDest =
                           *(undefined4 *)(this + iVar7 * 8 + 0x403c);
                      chr(this,this->cActor)->fc4 = 0;
                      chr(this,this->cActor)->fc8 =
                           *(undefined4 *)(this + iVar7 * 8 + 0x4040);
                      iVar7 = this + this->cActor * 0x510;
                      *(byte *)(iVar7 + 0xb1) = *(byte *)(iVar7 + 0xb1) & 0xdf | 0x20;
                    }
                    this->nPhase = 0x14;
                    this->nStep = 0;
                    this->nCmdKind = 0;
                    this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
                    this->flTurnPush = (float)*(ushort *)(unaff_s2_lo + 0x1a) / 100.0;
                    if (((((ulong)*(byte *)(unaff_s2_lo + 4) & 0x7f) >> 5 == 0) ||
                        ((int)*(short *)(unaff_s2_lo + 0x18) % 1000 == 0x50)) &&
                       (this->wTurnPendMask != 0)) {
                      return;
                    }
                    if (this->nComboCnt != 0) {
                      return;
                    }
                    this->bFlags25 = this->bFlags25 & 0xfb;
                    return;
                  }
                  if (-1 < this->cDataId) {
                    IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
                  }
                  this->nIopHandle = 0xffffffff;
                  this->cDataId = 0xff;
                  if (-1 < this->nShortcutTarget) {
                    SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
                  }
                  if (-1 < (long)((ulong)this->bFlags25 << 0x3b)) {
                    ComboStopOff__Fi(0xffffffffffffffff);
                    if (this->wTurnPendMask != 0) {
                      this->bFlags25 = this->bFlags25 & 0xf7;
                    }
                    this->cMesWinId2 = 0xff;
                  }
                  if (((chr(this,this->cActor)->bFlagsB & 1) == 0) &&
                     (this->nCmdKind == 2)) {
                    DecMP__7CBattleFiiii
                              (this,this->cActor,1,
                               this->nCmd0_target,
                               *(undefined2 *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x18),
                               *(undefined2 *)(unaff_s0_lo + this->nCmd0_target * 0x40 + 0x1e))
                    ;
                  }
                  if (this->wTurnPendMask != 0) {
                    this->wDeadMask =
                         this->wDeadMask |
                         (ushort)(1 << ((int)this->cActor & 0x1fU));
                  }
                  this->nStep = 0x1f;
                }
                bVar3 = false;
                if (*(int *)(this + 0x4624) != 0) {
                  if (*(short *)(*(int *)(this + 0x4624) + 0x28) != 0x14) {
                    *(undefined2 *)(*(int *)(this + 0x4624) + 0x28) = 0x17;
                    *(undefined2 *)(*(int *)(this + 0x4624) + 0x2a) = 3;
                  }
                  bVar3 = true;
                }
                if (bVar3) {
                  return;
                }
                if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
                  TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
                }
                this->nStep = 0x20;
                this->flTurnPush = 0;
                return;
              }
              if (*(int *)(iGpffff8618 + 0x3c) != 1) {
                return;
              }
              SetMesWinClose__7BtlMenuFi(this->nMsgHandle);
              this->nStep = 0x22;
            }
            lVar11 = FindMesWin__7BtlMenuFi(this->nMsgHandle);
            if (lVar11 != 0) {
              return;
            }
            this->nMsgHandle = 0xffff;
            this->nStep = 0x23;
            this->flMenuTimer = 0;
            lVar11 = __nw__FUi(0x49c);
            if (lVar11 == 0) {
              return;
            }
            __ct__8BtlBonusFv();
            return;
          }
          if (-1 < this->cDataId) {
            IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
          }
          this->nIopHandle = 0xffffffff;
          this->cDataId = 0xff;
          if (-1 < this->nShortcutTarget) {
            SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
          }
          if (-1 < (long)((ulong)this->bFlags25 << 0x3b)) {
            ComboStopOff__Fi(0xffffffffffffffff);
            if (this->wTurnPendMask != 0) {
              this->bFlags25 = this->bFlags25 & 0xf7;
            }
            this->cMesWinId2 = 0xff;
          }
          if (this->wTurnPendMask != 0) {
            this->wDeadMask =
                 this->wDeadMask |
                 (ushort)(1 << ((int)this->cActor & 0x1fU));
          }
          this->nStep = 0x29;
        }
        bVar3 = false;
        if (*(int *)(this + 0x4624) != 0) {
          if (*(short *)(*(int *)(this + 0x4624) + 0x28) != 0x14) {
            *(undefined2 *)(*(int *)(this + 0x4624) + 0x28) = 0x17;
            *(undefined2 *)(*(int *)(this + 0x4624) + 0x2a) = 3;
          }
          bVar3 = true;
        }
        if (!bVar3) {
          if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
            TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
          }
          this->nStep = 0x2a;
          this->flTurnPush = 0;
          if (-1 < this->nMsgHandle) {
            SetMesWinClose__7BtlMenuFi(this->nMsgHandle);
          }
        }
      }
    }
  }
  return;
}

/* ---- 0x0048c0d0  Retail_CBattle_Phase0B_RingSkill  (size 0x3d60) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5', '0x6', '0x7', '0x8', '0x9', '0xa']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0x10'] */
void Retail_CBattle_Phase0B_RingSkill(undefined8 this)

{
  short sVar1;
  byte bVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  long lVar8;
  undefined2 uVar9;
  int iVar10;
  uint uVar11;
  int this;
  uint uVar13;
  int iVar14;
  float fVar15;
  float fVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int aiStack_40 [15];
  int iStack_4;
  
  iVar5 = GetRegDat__9RegDatApiFiii(0x3f,0,0xffffffffffffffff);
  /* this = this */
  iVar14 = iVar5 + this->nCmd0_target * 0x40;
  uVar7 = GetRegDat__9RegDatApiFiii(0xc,this->nCmd0_target,0xffffffffffffffff);
  sVar1 = this->nStep;
  if (sVar1 == 0x14) {
    cVar3 = BtlChrReadyCheck__7CBattleFv(this);
    if (cVar3 == '\0') {
      return;
    }
    cVar3 = AllCSERelease__7CBattleFv(this);
    if (cVar3 == '\0') {
      return;
    }
    CloseBattleUI__7CBattleFb(this,1);
    if (chr(this,this->cActor)->bState == '\x11') {
      chr(this,this->cActor)->bState = 7;
      chr(this,this->cActor)->bState2 = 1;
    }
    iVar10 = this + this->cActor * 0x510;
    *(byte *)(iVar10 + 0xb5) = *(byte *)(iVar10 + 0xb5) & 0xf7;
    cVar3 = Retail_CBattle_SetAllChrEffMask(this,1);
    if (cVar3 == '\0') {
      return;
    }
    if (chr(this,this->cActor)->bState != '\a') {
      return;
    }
    if ((long)((ulong)*(byte *)(chr(this,this->cActor)->pModel + 0x4d0)
              << 0x3d) < 0) {
      return;
    }
    *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
    GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
              (this,this->cActor,this->nCmd1,
               ((ulong)*(ushort *)(iVar14 + 4) & 0x1ff) >> 7,
               ((ulong)*(byte *)(iVar14 + 5) & 0xf) >> 1,((ulong)*(byte *)(iVar14 + 5) & 0x3f) >> 4,
               iVar14 + 8,&iStack_4);
    if (iStack_4 == 0) {
      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                ((float)*(ushort *)(iVar14 + 0x1a) / 100.0,this,0,0,4,
                 this->nCmd0_target,iVar14,iVar14 + 8,this->cActor);
    }
    else {
      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                ((float)*(ushort *)(iVar14 + 0x1a) / 100.0,this,iStack_4,aiStack_40,4,
                 this->nCmd0_target,iVar14,iVar14 + 8,this->cActor);
      if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
        for (iVar10 = 0; iVar10 < iStack_4; iVar10 = iVar10 + 1) {
          SetSelectChr__13TurnOrderDispFii(this->pTurnOrderDisp,aiStack_40[iVar10],2);
        }
      }
      else {
        for (iVar10 = 0; iVar10 < iStack_4; iVar10 = iVar10 + 1) {
          SetSelectChr__13TurnOrderDispFii(this->pTurnOrderDisp,aiStack_40[iVar10],1);
        }
      }
    }
    this->nShortcutTarget = 0xffffffff;
    uVar6 = SetBtlMessage__7CBattleFiPv(this,0x146,uVar7);
    this->nShortcutTarget = uVar6;
    *(undefined2 *)(this + 0x45d6) = 0;
    if ((*(short *)(iVar14 + 0x18) < 1000) &&
       (-1 < chr(this,this->cActor)->f4e4)) {
      uVar4 = DataReadEntry__7CBattleFiii
                        (this,0xc,0x12,
                         chr(this,this->cActor)->f4e4);
      this->cDataId = uVar4;
    }
    this->nDataSlot = 0xffffffff;
    if (-1 < *(short *)(iVar14 + 0x18)) {
      if (*(short *)(iVar14 + 0x18) < 1000) {
        uVar6 = DataReadEntry__7CBattleFiii(this,0xc,0xb,*(undefined2 *)(iVar14 + 0x18));
        this->nDataSlot = uVar6;
      }
      else {
        uVar6 = DataReadEntry__7CBattleFiii(this,0xc,0xb,*(short *)(iVar14 + 0x18) + -1000);
        this->nDataSlot = uVar6;
      }
    }
    iVar10 = 0;
    if ((((0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x22)) &&
         (iVar10 = 1, 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x26))) &&
        (iVar10 = 2, 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x2a))) &&
       ((iVar10 = 3, 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x2e) &&
        (iVar10 = 4, 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x32))))) {
      iVar10 = 5;
    }
    uVar9 = (undefined2)(iVar10 + 1);
    *(undefined2 *)(this + 0x45d8) = uVar9;
    *(undefined2 *)(this + 0x45da) = uVar9;
    for (iVar5 = 0; iVar5 < 0x20; iVar5 = iVar5 + 1) {
      *(undefined1 *)(this + iVar5 + 0x45ec) = 0;
    }
    for (uVar11 = 0; (int)uVar11 < iVar10 + 1; uVar11 = uVar11 + 1) {
      uVar13 = uVar11 & 3;
      if (((int)uVar11 < 0) && (uVar13 != 0)) {
        uVar13 = uVar13 - 4;
      }
      iVar5 = this + ((int)uVar11 >> 2);
      *(byte *)(iVar5 + 0x45ec) = *(byte *)(iVar5 + 0x45ec) | (byte)(1 << ((uVar13 & 0xf) << 1));
    }
    *(undefined4 *)(this + 0x45dc) = 10000;
    *(undefined4 *)(this + 0x45e0) = 10000;
    *(undefined4 *)(this + 0x45e4) = 12000;
    *(undefined4 *)(this + 0x45e8) = 10000;
    *(byte *)(this + 0x45d6) = *(byte *)(this + 0x45d6) & 0xf9 | 4;
    *(byte *)(this + 0x45d6) = *(byte *)(this + 0x45d6) & 0xf7 | 8;
    this->nStep = 6;
    if (((chr(this,this->cActor)->bFlagsB & 1) == 0) &&
       (this->nComboCnt != 0)) {
      AddFriendship__7CBattleFiis
                (this,chr(this,this->cActor)->nCharId,
                 chr(this,this->cActorB)->nCharId,100);
    }
    if ((chr(this,this->cActor)->bFlagsB & 1) != 0) {
      return;
    }
    *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xfb | 4;
    if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
      if (this->wTurnPendMask != 0) {
        return;
      }
      if (this->nComboCnt != 0) {
        return;
      }
    }
    *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0x7f;
    return;
  }
  if (sVar1 != 10) {
    if (sVar1 != 9) {
      if (sVar1 == 8) {
        if ((-1 < (long)((ulong)this->bFlags25 << 0x39)) &&
           (-1 < (long)((ulong)this->bFlags25 << 0x38))) {
          return;
        }
        if ((-1 < this->nMsgHandle) &&
           ((lVar8 = FindMesWin__7BtlMenuFi(this->nMsgHandle), lVar8 != 0 &&
            (*(float *)((int)lVar8 + 0x3c) < 2.0)))) {
          return;
        }
        if ((long)((ulong)this->bFlags25 << 0x39) < 0) {
          iVar14 = this->pBtlResult;
          if (iVar14 != 0) {
            (**(code **)(*(int *)(iVar14 + 0x14) + 8))(iVar14,1);
          }
          this->pBtlResult = 0;
          SetAlphaMode__8BtlFaderFUl(0x44);
          Retail_CBattle_ReleaseChrWait(this);
        }
        if (-1 < this->cDataId) {
          IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
        }
        this->nIopHandle = 0xffffffff;
        this->cDataId = 0xff;
        if (-1 < this->nShortcutTarget) {
          SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
        }
        if (-1 < this->nMsgHandle) {
          SetMesWinClose__7BtlMenuFi(this->nMsgHandle);
        }
        this->nMsgHandle = 0xffff;
        if (-1 < (long)((ulong)this->bFlags25 << 0x3b)) {
          ComboStopOff__Fi(0xffffffffffffffff);
          if (this->wTurnPendMask != 0) {
            this->bFlags25 = this->bFlags25 & 0xf7;
          }
          this->cMesWinId2 = 0xff;
        }
        if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
          DecMP__7CBattleFiiii
                    (this,this->cActor,4,this->nCmd0_target,
                     *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x18),
                     *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x1e));
        }
        if (this->wTurnPendMask != 0) {
          this->wDeadMask =
               this->wDeadMask | (ushort)(1 << ((int)this->cActor & 0x1fU))
          ;
        }
        if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
          for (uVar11 = 0; (int)uVar11 < 0xc; uVar11 = uVar11 + 1) {
            uVar13 = uVar11;
            if (((uint)this->wDeadMask & 1 << (uVar11 & 0x1f)) != 0) {
              while (uVar13 = uVar13 + 1, (long)(int)uVar13 < (long)*(short *)(this + 0x3d90)) {
                if (((uint)this->wDeadMask & 1 << (uVar13 & 0x1f)) != 0) {
                  AddFriendship__7CBattleFiis
                            (this,*(undefined2 *)
                                      (this + *(int *)(this + uVar11 * 0x14 + 0x3d94) * 0x510 +
                                      0x120),
                             *(undefined2 *)
                              (this + *(int *)(this + uVar13 * 0x14 + 0x3d94) * 0x510 + 0x120),
                             100);
                }
              }
            }
          }
        }
        *(uint *)(iGpffff83b4 + 0xebc) =
             *(uint *)(iGpffff83b4 + 0xebc) | 1 << (this->nCmd0_target & 0x1f);
        if ((*(short *)(chr(this,this->cActor)->pModel + 0x510) == 0x31
            ) || (*(short *)(chr(this,this->cActor)->pModel + 0x510) ==
                  0x30)) {
          if (chr(this,this->cActor)->f4b4 != 0) {
            *(undefined4 *)(chr(this,this->cActor)->f4b4 + 0x5c0) = 5
            ;
          }
          chr(this,this->cActor)->f4b4 = 0;
          if (chr(this,this->cActor)->f4b0 != 0) {
            (**(code **)(*(int *)(chr(this,this->cActor)->f4b0 + 0x14
                                 ) + 0x3c))();
          }
          chr(this,this->cActor)->f4b0 = 0;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,this->cActor)->pModel,
                     0x32);
        }
        this->nDestIdx = 0;
        this->nStep = 9;
        return;
      }
      if (sVar1 == 7) {
        if (-1 < (long)((ulong)*(byte *)(this + this->nDataSlot * 0x18 + 0x40c4) << 0x3a
                       )) {
          return;
        }
        if ((chr(this,this->cActor)->bState == '\x10') &&
           (chr(this,this->cActor)->bState2 < '\x02')) {
          return;
        }
        this->bFlags25 = this->bFlags25 & 0xbf;
        this->bFlags25 = this->bFlags25 & 0x7f;
        *(byte *)(this + 0x26) = *(byte *)(this + 0x26) & 0xfe;
        *(undefined4 *)(this + 0x490c) = 0;
        this->nMsgHandle = 0xffff;
        lVar8 = __nw__FUi(0x48);
        uVar6 = 0;
        if (lVar8 != 0) {
          uVar6 = __ct__6EffectFPFPvi_vPvi(lVar8,0x472ce0,this,0);
        }
        this->pBtlResult = uVar6;
        Create__6EffectFP9BufMemory(this->pBtlResult,
                        *(undefined4 *)(this + this->nDataSlot * 0x18 + 0x40cc),1);
        SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi(this->pBtlResult,0x472cb0,this,0);
        DataRelease__7CBattleFiib(this,this->nDataSlot,0xc,1);
        *(int *)(this + 0x3d94) = (int)this->cActor;
        *(undefined4 *)(this + 0x3d98) =
             chr(this,this->cActor)->pModel;
        *(int *)(this + 0x3d9c) = this + this->cActor * 0x510 + 0xb0;
        *(undefined2 *)(this + 0x3d90) = 1;
        SetGenModel__6EffectFiP11tagModelSet(this->pBtlResult,*(undefined2 *)(this + 0x3d90),
                        this + 0x3d94);
        GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                  (this,this->cActor,this->nCmd1,
                   ((ulong)*(ushort *)(iVar14 + 4) & 0x1ff) >> 7,
                   ((ulong)*(byte *)(iVar14 + 5) & 0xf) >> 1,
                   ((ulong)*(byte *)(iVar14 + 5) & 0x3f) >> 4,iVar14 + 8,&iStack_4);
        for (iVar5 = 0; iVar5 < iStack_4; iVar5 = iVar5 + 1) {
          *(int *)(this + iVar5 * 0x14 + 0x3e84) = aiStack_40[iVar5];
          *(undefined4 *)(this + iVar5 * 0x14 + 0x3e88) =
               *(undefined4 *)(this + aiStack_40[iVar5] * 0x510 + 0x14c);
          *(int *)(this + iVar5 * 0x14 + 0x3e8c) = this + aiStack_40[iVar5] * 0x510 + 0xb0;
        }
        *(short *)(this + 0x3d92) = (short)iStack_4;
        SetTarModel__6EffectFiP11tagModelSet(this->pBtlResult,*(undefined2 *)(this + 0x3d92),
                        this + 0x3e84);
        Run__6EffectFv(this->pBtlResult);
        this->bFlags25 = this->bFlags25 & 0xef;
        if (*(int *)(this + 0x45cc) != 0) {
          *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
        }
        if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
          if (-1 < this->nCmd1) {
            if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
              *(short *)(this + 0x4630) = (short)this->nCmd1;
            }
            else {
              *(short *)(this + 0x4632) = (short)this->nCmd1;
            }
            this->nPartner = (short)this->nCmd1;
          }
        }
        else if ((((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 1) && (-1 < this->nCmd1)
                ) {
          if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
            *(short *)(this + 0x4634) = (short)this->nCmd1;
          }
          else {
            *(short *)(this + 0x4636) = (short)this->nCmd1;
          }
        }
        this->nStep = 8;
        return;
      }
      if (sVar1 == 6) {
        uStack_50 = in_zero_lo;
        uStack_4c = in_zero_hi;
        uStack_48 = in_zero_udw;
        uStack_44 = in_register_0000000c;
        if (-1 < this->cDataId) {
          if (*(char *)(this + this->cDataId * 0x18 + 0x40c5) != '\x03') {
            return;
          }
          auVar17 = _lqc2(*(undefined1 (*) [16])(this + this->cActor * 0x510 + 0x160))
          ;
          auVar18 = _lqc2(*(undefined1 (*) [16])(this + this->cActor * 0x510 + 0x3a0))
          ;
          auVar17 = _vadd(auVar17,auVar18);
          auStack_70 = _sqc2(auVar17);
          __ct__7FVectorFPC7FVector(auStack_60,auStack_70);
          uStack_50 = auStack_60._0_4_;
          uStack_4c = auStack_60._4_4_;
          uStack_48 = uStack_58;
          uStack_44 = uStack_54;
          if (((chr(this,this->cActor)->bFlagsB & 1) == 0) &&
             (-1 < (long)((ulong)chr(this,this->cActor)->bFlagsA1 << 0x3e
                         ))) {
            if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000000,1,&uStack_50);
            }
            else if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 1) {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000001,1,&uStack_50);
            }
            else {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000002,1,&uStack_50);
            }
          }
          else {
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000000,1,&uStack_50);
          }
          DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
        }
        if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
          for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
            if (((((chr(this,iVar5)->bFlagsA & 1) != 0) &&
                 ((long)((ulong)chr(this,iVar5)->bFlagsA << 0x3e) < 0)) &&
                (-1 < (long)((ulong)chr(this,iVar5)->bFlagsA2 << 0x3c))) &&
               (((0 < chr(this,iVar5)->nHp &&
                 ((long)((ulong)chr(this,iVar5)->bFlagsA << 0x3a) < 0)) &&
                (('\x18' < chr(this,iVar5)->bState &&
                 ((chr(this,iVar5)->bState < '+' &&
                  (chr(this,iVar5)->f458 + 1 == *(int *)(this + 0x40))))))))) {
              iVar10 = this + iVar5 * 0x510;
              *(byte *)(iVar10 + 0x504) = *(byte *)(iVar10 + 0x504) & 0xef | 0x10;
              chr(this,iVar5)->f458 = *(undefined4 *)(this + 0x40);
              chr(this,iVar5)->f464 =
                   ((float)chr(this,iVar5)->f460 * 2.0) / 100.0;
              chr(this,iVar5)->f468 = 0;
              if (((ulong)chr(this,iVar5)->bFlagsB & 7) >> 1 != 0) {
                chr(this,iVar5)->f468 = 0x3dcccccd;
              }
            }
          }
        }
        else {
          ComboStopOff__Fi(0xffffffffffffffff);
        }
        if (*(short *)(iVar14 + 0x18) < 1000) {
          chr(this,this->cActor)->bState = 0x10;
          chr(this,this->cActor)->bState2 = 0;
          if (((long)this->nCmd1 == (long)this->cActor) ||
             (this->nCmd1 < 0)) {
            SetRetailCamera1__9BtlCameraFUiUib
                      (this->pCamera,this->cActor,
                       0xffffffffffffffff,1);
          }
          else if (-1 < this->nCmd1) {
            SetTargetAngle__7CBattleFii
                      (this,this->cActor,this->nCmd1);
            Retail_BtlModel_PrewarmDynamics
                      (chr(this,this->cActor)->pModel);
            SetRetailCamera1__9BtlCameraFUiUib
                      (this->pCamera,this->cActor,
                       this->nCmd1,1);
          }
        }
        this->cMesWinId2 = 0xff;
        if (((((chr(this,this->cActor)->bFlagsB & 1) == 0) &&
             ((long)((ulong)*(byte *)(iGpffff83b4 + 3) << 0x3e) < 0)) &&
            (this->wTurnPendMask != 0)) &&
           (-1 < (long)((ulong)this->bFlags24 << 0x3a))) {
          iStack_4 = 0;
          for (uVar11 = 0; (int)uVar11 < 0xc; uVar11 = uVar11 + 1) {
            if (((uint)this->wTurnPendMask & 1 << (uVar11 & 0x1f)) != 0) {
              if ((long)((ulong)chr(this,uVar11)->bFlagsA1 << 0x3e) < 0) {
                if (((-1 < *(char *)(iGpffff83b4 + chr(this,uVar11)->fa * 0x10
                                    + 0x119c)) ||
                    (-1 < *(char *)(iGpffff83b4 + chr(this,uVar11)->fa * 0x10
                                   + 0x11a0))) ||
                   ((-1 < *(char *)(iGpffff83b4 + chr(this,uVar11)->fa * 0x10
                                   + 0x11a4) ||
                    (-1 < *(char *)(iGpffff83b4 + chr(this,uVar11)->fa * 0x10
                                   + 0x11a8))))) {
                  iStack_4 = iStack_4 + 1;
                }
              }
              else if (chr(this,uVar11)->nCharId == 6) {
                sVar1 = *(short *)(iGpffff836c + 0x750);
                if ((sVar1 == 4) || (sVar1 == 3)) {
                  if ((-1 < *(char *)(iGpffff83b4 + 0x132c)) ||
                     (((-1 < *(char *)(iGpffff83b4 + 0x1330) ||
                       (-1 < *(char *)(iGpffff83b4 + 0x1334))) ||
                      (-1 < *(char *)(iGpffff83b4 + 0x1338))))) {
                    iStack_4 = iStack_4 + 1;
                  }
                }
                else if (sVar1 == 2) {
                  if (((-1 < *(char *)(iGpffff83b4 + 0x131c)) ||
                      (-1 < *(char *)(iGpffff83b4 + 0x1320))) ||
                     ((-1 < *(char *)(iGpffff83b4 + 0x1324) ||
                      (-1 < *(char *)(iGpffff83b4 + 0x1328))))) {
                    iStack_4 = iStack_4 + 1;
                  }
                }
                else if (sVar1 == 1) {
                  if (((-1 < *(char *)(iGpffff83b4 + 0x130c)) ||
                      (-1 < *(char *)(iGpffff83b4 + 0x1310))) ||
                     ((-1 < *(char *)(iGpffff83b4 + 0x1314) ||
                      (-1 < *(char *)(iGpffff83b4 + 0x1318))))) {
                    iStack_4 = iStack_4 + 1;
                  }
                }
                else if ((((-1 < *(char *)(iGpffff83b4 + 0x111c)) ||
                          (-1 < *(char *)(iGpffff83b4 + 0x1120))) ||
                         (-1 < *(char *)(iGpffff83b4 + 0x1124))) ||
                        (-1 < *(char *)(iGpffff83b4 + 0x1128))) {
                  iStack_4 = iStack_4 + 1;
                }
              }
              else if (((-1 < *(char *)(iGpffff83b4 +
                                        chr(this,uVar11)->nCharId * 0x10 + 0x10bc)
                        ) || (-1 < *(char *)(iGpffff83b4 +
                                             chr(this,uVar11)->nCharId * 0x10 +
                                            0x10c0))) ||
                      ((-1 < *(char *)(iGpffff83b4 +
                                       chr(this,uVar11)->nCharId * 0x10 + 0x10c4)
                       || (-1 < *(char *)(iGpffff83b4 +
                                          chr(this,uVar11)->nCharId * 0x10 +
                                         0x10c8))))) {
                iStack_4 = iStack_4 + 1;
              }
            }
          }
          if (iStack_4 != 0) {
            if (*(int *)(this + 0x4624) == 0) {
              lVar8 = __nw__FUi(0xb1c);
              uVar6 = 0;
              if (lVar8 != 0) {
                uVar6 = __ct__7BtlMenuFib(lVar8,0x17,0);
              }
              *(undefined4 *)(this + 0x4624) = uVar6;
            }
            else {
              SetMode__7BtlMenuFib(*(undefined4 *)(this + 0x4624),0x17,0);
            }
            *(int *)(iGpffff83b4 + 0x14dc) = *(int *)(iGpffff83b4 + 0x14dc) + 1;
          }
        }
        this->nStep = 7;
        return;
      }
      if (sVar1 != 5) {
        if (sVar1 != 4) {
          if (sVar1 == 3) {
            if ((*(short *)(iVar14 + 0x18) < 1000) &&
               (-1 < chr(this,this->cActor)->f4e4)) {
              uVar4 = DataReadEntry__7CBattleFiii
                                (this,0xc,0x12,
                                 chr(this,this->cActor)->f4e4)
              ;
              this->cDataId = uVar4;
            }
            this->nDataSlot = 0xffffffff;
            if (-1 < *(short *)(iVar14 + 0x18)) {
              if (*(short *)(iVar14 + 0x18) < 1000) {
                uVar6 = DataReadEntry__7CBattleFiii(this,0xc,0xb,*(undefined2 *)(iVar14 + 0x18));
                this->nDataSlot = uVar6;
              }
              else {
                uVar6 = DataReadEntry__7CBattleFiii
                                  (this,0xc,0xb,*(short *)(iVar14 + 0x18) + -1000);
                this->nDataSlot = uVar6;
              }
            }
            this->nStep = 4;
            return;
          }
          if (sVar1 == 2) {
            cVar3 = IsCapture__6SSHSysFv(uGpffff8408);
            if (cVar3 == '\0') {
              return;
            }
            if (*(int *)(this + 0x45d0) == 0) {
              lVar8 = __nw__FUi(0x5e0);
              uVar6 = 0;
              if (lVar8 != 0) {
                uVar6 = __ct__5JRingFsi(lVar8,0,0xc);
              }
              *(undefined4 *)(this + 0x45d0) = uVar6;
              SetPad__5JRingFP4CPad(uGpffff861c);
            }
            SetCallBack__5JRingFPFiPvPv_bPvUi(*(undefined4 *)(this + 0x45d0),0x472c10,this,0x7c3);
            SetRingPos__5JRingFff(0x43aaaaab,0x43600000,*(undefined4 *)(this + 0x45d0));
            if (((0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x22)) &&
                (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                 *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x20),
                                 *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x22),0,0)
                , 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x26))) &&
               ((AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                 *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x24),
                                 *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x26),0,0)
                , 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x2a) &&
                ((AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                  *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x28),
                                  *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x2a),0,0
                                 ), 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x2e) &&
                 (AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                                  *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x2c),
                                  *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x2e),0,0
                                 ), 0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x32))))
                ))) {
              AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(this + 0x45d0),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x30),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x32),0,0);
            }
            if (0 < *(short *)(iVar5 + this->nCmd0_target * 0x40 + 0x36)) {
              AddModulateArea__5JRingFssssP7_rgba32P7_rgba32P7_rgba32(*(undefined4 *)(this + 0x45d0),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x34),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x36),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x38),
                              *(undefined2 *)(iVar5 + this->nCmd0_target * 0x40 + 0x3a),0,0,0);
            }
            SetMode__5JRingFsssss(*(undefined4 *)(this + 0x45d0),5,1,1,4,3);
            if ((((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) &&
               (this->wTurnPendMask != 0)) {
              sVar1 = this->nComboCnt;
              if (sVar1 == 2) {
                fVar16 = 0.6;
              }
              else if (sVar1 == 1) {
                fVar16 = 0.75;
              }
              else if (sVar1 == 0) {
                fVar16 = 0.9;
              }
              else {
                fVar16 = 0.5;
              }
              iStack_4 = 0;
              fVar15 = 0.0;
              for (uVar11 = 0; (int)uVar11 < 0xc; uVar11 = uVar11 + 1) {
                if (((uint)this->wTurnPendMask & 1 << (uVar11 & 0x1f)) != 0) {
                  fVar15 = fVar15 + (float)(int)*(short *)(iGpffff83b4 +
                                                           *(short *)(this + *(char *)(this + 
                                                  0x2c) * 0x510 + 0x120) * 0xc0 +
                                                  chr(this,uVar11)->nCharId * 2 +
                                                  0x7c) / 100.0;
                  iStack_4 = iStack_4 + 1;
                }
              }
              if (iStack_4 != 0) {
                fVar16 = fVar16 + fVar15 / ((float)iStack_4 * 500.0);
              }
              SetCombo__5JRingFf(fVar16,*(undefined4 *)(this + 0x45d0));
            }
            bVar2 = *(byte *)(iGpffff83b4 +
                              chr(this,this->cActor)->nCharId * 0xc0 +
                             0x98) >> 6;
            if (bVar2 == 3) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 0xc;
            }
            else if (bVar2 == 2) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 8;
            }
            else if (bVar2 == 1) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 4;
            }
            else if (bVar2 == 0) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3;
            }
            SetJRingStatus__7CBattleFiiPi(this,this->cActor,4,0);
            if (((chr(this,this->cActor)->bFlagsB & 1) == 0) &&
               ((*(byte *)(iGpffff83b4 +
                           chr(this,this->cActor)->nCharId * 0xc0 +
                          0x99) & 1) != 0)) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x41) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x41) & 0xf3 | 4;
              *(undefined2 *)(*(int *)(this + 0x45d0) + 0x58c) = 10;
            }
            else if (this->nCmd3 != 0) {
              *(short *)(*(int *)(this + 0x45d0) + 0x58c) =
                   (short)this->nCmd3 + 2;
            }
            RingActive__5JRingFv(*(undefined4 *)(this + 0x45d0));
            if (this->nComboCnt != 0) {
              *(byte *)(*(int *)(this + 0x45d0) + 0x42) =
                   *(byte *)(*(int *)(this + 0x45d0) + 0x42) & 0x7f | 0x80;
            }
            *(undefined2 *)(this + 0x45d6) = 0;
            if ((((*(char *)(this + 0x4866) != '\x01') && (*(char *)(this + 0x4866) != '\x02'))
                && (*(short *)(*(int *)(this + 0x45d0) + 0x58c) == 0)) &&
               ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
              iVar5 = iGpffff83b4 +
                      chr(this,this->cActor)->nCharId * 0x24;
              *(int *)(iVar5 + 0x150c) = *(int *)(iVar5 + 0x150c) + 1;
              if (((long)((ulong)*(byte *)(*(int *)(this + 0x45d0) + 0x512) << 0x3a) < 0) &&
                 (*(byte *)(iGpffff83b4 +
                            chr(this,this->cActor)->nCharId * 0xc0 +
                           0x98) >> 6 != 1)) {
                iVar5 = iGpffff83b4 +
                        chr(this,this->cActor)->nCharId * 0x24;
                *(int *)(iVar5 + 0x1510) = *(int *)(iVar5 + 0x1510) + 1;
              }
              *(short *)(this + 0x4906) = *(short *)(this + 0x4906) + 1;
            }
            this->nStep = 3;
            this->bFlags24 = this->bFlags24 & 0xbf;
            if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
              if (this->wTurnPendMask != 0) {
                return;
              }
              if (this->nComboCnt != 0) {
                return;
              }
            }
            if ((chr(this,this->cActor)->bFlagsB & 1) != 0) {
              return;
            }
            *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0x7f;
            return;
          }
          if (sVar1 == 1) {
            if (*(int *)(this->pParamDisp + 0x38) != 0) {
              return;
            }
            if (iGpffff8618->nCmd1 != 0) {
              return;
            }
            this->bFlags24 = this->bFlags24 & 0xfe | 1;
            this->bFlags24 = this->bFlags24 & 0xfd | 2;
            ScreenCapture__6SSHSysFi(uGpffff8408,1);
            this->nStep = 2;
            return;
          }
          if (sVar1 != 0) {
            return;
          }
          cVar3 = AllCSERelease__7CBattleFv(this);
          if (cVar3 == '\0') {
            return;
          }
          CloseBattleUI__7CBattleFb(this,1);
          if (chr(this,this->cActor)->bState == '\x11') {
            chr(this,this->cActor)->bState = 7;
            chr(this,this->cActor)->bState2 = 1;
          }
          iVar5 = this + this->cActor * 0x510;
          *(byte *)(iVar5 + 0xb5) = *(byte *)(iVar5 + 0xb5) & 0xf7;
          cVar3 = Retail_CBattle_SetAllChrEffMask(this,1);
          if (cVar3 == '\0') {
            return;
          }
          if (chr(this,this->cActor)->bState != '\a') {
            return;
          }
          if ((long)((ulong)*(byte *)(chr(this,this->cActor)->pModel +
                                     0x4d0) << 0x3d) < 0) {
            return;
          }
          *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
          GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
                    (this,this->cActor,this->nCmd1,
                     ((ulong)*(ushort *)(iVar14 + 4) & 0x1ff) >> 7,
                     ((ulong)*(byte *)(iVar14 + 5) & 0xf) >> 1,
                     ((ulong)*(byte *)(iVar14 + 5) & 0x3f) >> 4,iVar14 + 8,&iStack_4);
          if (iStack_4 == 0) {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      ((float)*(ushort *)(iVar14 + 0x1a) / 100.0,this,0,0,4,
                       this->nCmd0_target,iVar14,iVar14 + 8,
                       this->cActor);
          }
          else {
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      ((float)*(ushort *)(iVar14 + 0x1a) / 100.0,this,iStack_4,aiStack_40,4,
                       this->nCmd0_target,iVar14,iVar14 + 8,
                       this->cActor);
            if (((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) {
              for (iVar5 = 0; iVar5 < iStack_4; iVar5 = iVar5 + 1) {
                SetSelectChr__13TurnOrderDispFii
                          (this->pTurnOrderDisp,aiStack_40[iVar5],2);
              }
            }
            else {
              for (iVar5 = 0; iVar5 < iStack_4; iVar5 = iVar5 + 1) {
                SetSelectChr__13TurnOrderDispFii
                          (this->pTurnOrderDisp,aiStack_40[iVar5],1);
              }
            }
          }
          this->nShortcutTarget = 0xffffffff;
          if ((*(uint *)(iGpffff83b4 + 0xebc) & 1 << (this->nCmd0_target & 0x1f)) == 0) {
            uVar7 = GetRegDat__9RegDatApiFiii(0x2a,0x33,0xffffffffffffffff);
            uVar6 = SetBtlMessage__7CBattleFiPv(this,0x146,uVar7);
            this->nShortcutTarget = uVar6;
          }
          else {
            uVar6 = SetBtlMessage__7CBattleFiPv(this,0x146,uVar7);
            this->nShortcutTarget = uVar6;
          }
          if (((long)this->nCmd1 == (long)this->cActor) ||
             (this->nCmd1 < 0)) {
            SetCharacterCamera3__9BtlCameraFib
                      (this->pCamera,this->cActor,1);
          }
          else if (-1 < this->nCmd1) {
            SetTargetAngle__7CBattleFii
                      (this,this->cActor,this->nCmd1);
            Retail_BtlModel_PrewarmDynamics
                      (chr(this,this->cActor)->pModel);
            SetJudgementRingCamera1__9BtlCameraFiib
                      (this->pCamera,this->cActor,
                       this->nCmd1,1);
          }
          this->nStep = 1;
          MaxComboFunc__7CBattleFi(this,this->cActor);
          FilterOff__9BtlSocketFbb(iGpffff836c,0,1);
          if ((chr(this,this->cActor)->bFlagsB & 1) != 0) {
            return;
          }
          *(byte *)(this + 0x4899) = *(byte *)(this + 0x4899) & 0xfb | 4;
          return;
        }
        cVar3 = BtlChrReadyCheck__7CBattleFv(this);
        if (cVar3 == '\0') {
          return;
        }
        if ((*(byte *)(this + 0x45d6) & 1) == 0) {
          return;
        }
        if (-1 < (long)((ulong)this->bFlags24 << 0x39)) {
          return;
        }
        if ((long)((ulong)this->bFlags24 << 0x3e) < 0) {
          ClearCapture__6SSHSysFv(uGpffff8408);
          this->bFlags24 = this->bFlags24 & 0xfd;
        }
        this->bFlags24 = this->bFlags24 & 0xfe;
        FilterOn__9BtlSocketFbb(iGpffff836c,1,1);
        if ((-1 < (long)((ulong)*(byte *)(this + 0x45d6) << 0x3b)) &&
           ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
          if (1 < ((ulong)*(byte *)(this + 0x45d6) & 7) >> 1) {
            iVar5 = iGpffff83b4 +
                    chr(this,this->cActor)->nCharId * 0x24;
            *(int *)(iVar5 + 0x1514) = *(int *)(iVar5 + 0x1514) + 1;
          }
          if (((((ulong)*(byte *)(this + 0x45d6) & 7) >> 1 == 3) &&
              ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3a) < 0)) &&
             (*(byte *)(iGpffff83b4 +
                        chr(this,this->cActor)->nCharId * 0xc0 + 0x98)
              >> 6 != 1)) {
            iVar5 = iGpffff83b4 +
                    chr(this,this->cActor)->nCharId * 0x24;
            *(int *)(iVar5 + 0x1518) = *(int *)(iVar5 + 0x1518) + 1;
          }
          if (((long)((ulong)*(byte *)(this + 0x45d6) << 0x39) < 0) &&
             (iVar5 = iGpffff83b4 +
                      chr(this,this->cActor)->nCharId * 0x24,
             *(int *)(iVar5 + 0x151c) = *(int *)(iVar5 + 0x151c) + 1,
             (long)((ulong)*(byte *)(this + 0x45d6) << 0x3c) < 0)) {
            iVar5 = iGpffff83b4 +
                    chr(this,this->cActor)->nCharId * 0x24;
            *(int *)(iVar5 + 0x1520) = *(int *)(iVar5 + 0x1520) + 1;
          }
        }
        if ((-1 < (long)((ulong)*(byte *)(this + 0x45d6) << 0x3c)) &&
           (this->wTurnPendMask = 0,
           (long)((ulong)*(byte *)(this + 0x45d6) << 0x39) < 0)) {
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
        }
        if ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3b) < 0) {
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
        }
        if (1 < ((ulong)*(byte *)(this + 0x45d6) & 7) >> 1) {
          this->nStep = 6;
          if ((((((ulong)*(byte *)(this + 0x45d6) & 7) >> 1 < 3) &&
               ((long)((ulong)*(byte *)(this + 0x45d6) << 0x3a) < 0)) &&
              (*(byte *)(iGpffff83b4 +
                         chr(this,this->cActor)->nCharId * 0xc0 + 0x98
                        ) >> 6 != 1)) &&
             ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
            *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
          }
          if ((*(byte *)(iGpffff83b4 +
                         chr(this,this->cActor)->nCharId * 0xc0 + 0x98
                        ) >> 6 == 1) &&
             ((*(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf,
              *(int *)(this + 0x45e8) < 10000 ||
              ((*(short *)(this + 0x45d4) == 1 && (*(int *)(this + 0x45e0) < 10000)))))) {
            *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
          }
          if (this->nComboCnt == 0) {
            return;
          }
          if ((chr(this,this->cActor)->bFlagsB & 1) != 0) {
            return;
          }
          AddFriendship__7CBattleFiis
                    (this,chr(this,this->cActor)->nCharId,
                     chr(this,this->cActorB)->nCharId,100);
          return;
        }
        this->nStep = 5;
        ComboStopOff__Fi(0xffffffffffffffff);
        if ((chr(this,this->cActor)->bFlagsB & 1) == 0) {
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xdf;
          *(byte *)(this + 0x4898) = *(byte *)(this + 0x4898) & 0xbf;
        }
      }
      if (-1 < this->cDataId) {
        if (*(char *)(this + this->cDataId * 0x18 + 0x40c5) != '\x03') {
          return;
        }
        IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
        DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
        this->nIopHandle = 0xffffffff;
        this->cDataId = 0xff;
      }
      if ((chr(this,this->cActor)->f4bc != 0) &&
         (chr(this,this->cActor)->f4c0 != -1)) {
        if ((long)((ulong)chr(this,this->cActor)->bFlagsA1 << 0x3d) < 0)
        {
          return;
        }
        cVar3 = IsIOPRelease__6HNMSndFi(uGpffff8374,
                                chr(this,this->cActor)->f4c0);
        if (cVar3 == '\0') {
          IOPRelease__6HNMSndFi(uGpffff8374,
                          chr(this,this->cActor)->f4c0);
        }
        cVar3 = IOPReleaseCheck__6HNMSndFi(uGpffff8374,
                                chr(this,this->cActor)->f4c0);
        if (cVar3 == '\0') {
          return;
        }
        chr(this,this->cActor)->f4c0 = 0xffffffff;
      }
      if (-1 < this->nDataSlot) {
        if (-1 < (long)((ulong)*(byte *)(this + this->nDataSlot * 0x18 + 0x40c4) << 0x3a
                       )) {
          return;
        }
        DataRelease__7CBattleFiib(this,this->nDataSlot,0xc,0);
      }
      if (-1 < this->nShortcutTarget) {
        SetMesWinClose__7BtlMenuFi(this->nShortcutTarget);
      }
      this->nPhase = 0x14;
      this->nStep = 0;
      this->nCmdKind = 0;
      this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
      this->flTurnPush = (float)*(ushort *)(iVar14 + 0x1a) / 100.0;
      if ((((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 == 0) && (this->wTurnPendMask != 0)) {
        return;
      }
      if (this->nComboCnt != 0) {
        return;
      }
      this->bFlags25 = this->bFlags25 & 0xfb;
      return;
    }
    cVar3 = DestinationSearch__7CBattleFi(this,this->cActor);
    if (cVar3 != '\x01') {
      return;
    }
    if (4 < this->nDestCount) {
      DestinationListUp__7CBattleFii(this,4,this->cActor);
    }
    this->nDestIdx = 0;
    iVar5 = rand();
    iVar5 = iVar5 % (int)this->nDestCount;
    chr(this,this->cActor)->aDest =
         *(undefined4 *)(this + iVar5 * 8 + 0x403c);
    chr(this,this->cActor)->fc4 = 0;
    chr(this,this->cActor)->fc8 =
         *(undefined4 *)(this + iVar5 * 8 + 0x4040);
    iVar5 = this + this->cActor * 0x510;
    *(byte *)(iVar5 + 0xb1) = *(byte *)(iVar5 + 0xb1) & 0xdf | 0x20;
    this->nStep = 10;
  }
  if (*(int *)(this + 0x4624) == 0) {
    this->nPhase = 0x14;
    this->nStep = 0;
    this->nCmdKind = 0;
    this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
    this->flTurnPush = (float)*(ushort *)(iVar14 + 0x1a) / 100.0;
    if (((((ulong)*(byte *)(iVar14 + 4) & 0x7f) >> 5 != 0) || (this->wTurnPendMask == 0)) &&
       (this->nComboCnt == 0)) {
      this->bFlags25 = this->bFlags25 & 0xfb;
    }
  }
  else if (*(short *)(*(int *)(this + 0x4624) + 0x28) != 0x14) {
    *(undefined2 *)(*(int *)(this + 0x4624) + 0x28) = 0x17;
    *(undefined2 *)(*(int *)(this + 0x4624) + 0x2a) = 3;
  }
  return;
}

/* ---- 0x0048fe30  TarotEffectFunc__7CBattleFv  (size 0x23d0) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5', '0x6', '0x7', '0x8', '0xa', '0xb', '0xc', '0xd', '0xe', '0x14', '0x28', '0x32', '0x33', '0x34']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0x16'] */
void TarotEffectFunc__7CBattleFv(int this)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint auStack_e0 [35];
  int iStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int iStack_40;
  undefined4 *puStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  int iStack_1c;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  int iStack_10;
  
  iStack_10 = this;
  uStack_20 = GetRegDat__9RegDatApiFiii(0x44,0,0xffffffffffffffff);
  iStack_2c = iGpffff861c;
  uStack_16 = *(undefined2 *)(*(int *)(*(int *)(iGpffff861c + 4) * 4 + 0x43fca8) + 0x6c);
  sVar2 = iStack_10->nStep;
  uStack_14 = uStack_16;
  uStack_12 = uStack_16;
  if (sVar2 != 0x34) {
    if (sVar2 != 0x33) {
      if (sVar2 == 0x32) {
        if (-1 < iStack_10->nMsgHandle) {
          SetMesWinClose__7BtlMenuFi(iStack_10->nMsgHandle);
        }
        uVar4 = 0xffffffffffffffff;
        iStack_10->nMsgHandle = 0xffff;
        if (-1 < *(int *)(iStack_10 + 0x7c)) {
          uVar4 = SetMesWinClose__7BtlMenuFi(*(undefined4 *)(iStack_10 + 0x7c));
        }
        if (-1 < *(int *)(iStack_10 + 0x80)) {
          SetMesWinClose__7BtlMenuFi(*(undefined4 *)(iStack_10 + 0x80),uVar4);
        }
        for (iVar9 = 0x46; iVar9 < 0x4d; iVar9 = iVar9 + 1) {
          if ((*(int *)(iStack_10 + iVar9 * 4 + 0x4484) != 0) &&
             (iStack_54 = *(int *)(iStack_10 + iVar9 * 4 + 0x4484), iStack_54 != 0)) {
            (**(code **)(*(int *)(iStack_54 + 0x8c) + 8))(iStack_54,1);
          }
          *(undefined4 *)(iStack_10 + iVar9 * 4 + 0x4484) = 0;
        }
        DataRelease__7CBattleFiib(iStack_10,iStack_10->nDataSlot,0xc,0);
        iGpffff8620 = iGpffff8620 + 1;
        if (3 < iGpffff8620) {
          iGpffff8620 = 0;
        }
        if (-1 < (long)((ulong)iStack_10->bFlags25 << 0x3b)) {
          ComboStopOff__Fi(0xffffffffffffffff);
          if (iStack_10->wTurnPendMask != 0) {
            iStack_10->bFlags25 = iStack_10->bFlags25 & 0xf7;
          }
          iStack_10->cMesWinId2 = 0xff;
        }
        if (iStack_10->wTurnPendMask != 0) {
          iStack_10->wDeadMask =
               iStack_10->wDeadMask |
               (ushort)(1 << ((int)iStack_10->cActor & 0x1fU));
        }
        iStack_10->nDestIdx = 0;
        iStack_10->nStep = 0x33;
        return;
      }
      if (sVar2 == 0x28) {
        sVar2 = GetFaderMode__8BtlFaderFv();
        if (sVar2 != 0) {
          return;
        }
        iStack_10->flMenuTimer = iStack_10->flMenuTimer + iStack_10->flDeltaT;
        if (iStack_10->flMenuTimer < 0.5) {
          return;
        }
        if (((-1 < iStack_10->nMsgHandle) &&
            (lVar6 = FindMesWin__7BtlMenuFi(iStack_10->nMsgHandle), lVar6 != 0)) &&
           (*(float *)((int)lVar6 + 0x3c) < 2.0)) {
          return;
        }
        iStack_10->nStep = 0x32;
        iStack_10->flMenuTimer = 0;
        return;
      }
      if (sVar2 == 0x14) {
        if ((-1 < (long)((ulong)iStack_10->bFlags25 << 0x39)) &&
           (-1 < (long)((ulong)iStack_10->bFlags25 << 0x38))) {
          return;
        }
        if ((long)((ulong)iStack_10->bFlags25 << 0x39) < 0) {
          iStack_50 = iStack_10->pBtlResult;
          if (iStack_50 != 0) {
            (**(code **)(*(int *)(iStack_50 + 0x14) + 8))(iStack_50,1);
          }
          iStack_10->pBtlResult = 0;
          SetAlphaMode__8BtlFaderFUl(0x44);
          Retail_CBattle_ReleaseChrWait(iStack_10);
        }
        iStack_10->flMenuTimer = 0;
        iStack_10->nStep = 0x28;
        return;
      }
      if (sVar2 == 0xe) {
        iStack_10->flMenuTimer = iStack_10->flMenuTimer + iStack_10->flDeltaT;
        if (iStack_10->flMenuTimer < 2.0) {
          return;
        }
        if (((-1 < iStack_10->nMsgHandle) &&
            (lVar6 = FindMesWin__7BtlMenuFi(iStack_10->nMsgHandle), lVar6 != 0)) &&
           (*(float *)((int)lVar6 + 0x3c) < 2.0)) {
          return;
        }
        iStack_10->nStep = 0x32;
        return;
      }
      if (sVar2 == 0xd) {
        iStack_10->flMenuTimer = iStack_10->flMenuTimer + iStack_10->flDeltaT;
        if (iStack_10->flMenuTimer < 0.5) {
          return;
        }
        TarotApplyCard__7CBattleFii(iStack_10,0xffffffffffffffff);
        SetParty__9ParamDispFii(iStack_10->pParamDisp,3,0xffffffffffffffff);
        iStack_10->nStep = 0xe;
        iStack_10->flMenuTimer = 0;
        return;
      }
      if (sVar2 == 0xc) {
        sVar2 = GetFaderMode__8BtlFaderFv();
        if (sVar2 != 0) {
          return;
        }
        lVar6 = __nw__FUi(0x8a0);
        if (lVar6 != 0) {
          __ct__14BtlTarotEffectFv(lVar6,0,iStack_10->cActor);
        }
        iStack_10->nStep = 0xd;
        return;
      }
      if (sVar2 != 0xb) {
        if (sVar2 == 10) {
          cVar1 = AllCSERelease__7CBattleFv(iStack_10);
          if (cVar1 == '\0') {
            return;
          }
          cVar1 = BtlSEEndCheck__6HNMSndFi(uGpffff8374,4);
          if (cVar1 == '\0') {
            return;
          }
          for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
            if (((chr(iStack_10,iVar9)->bFlagsA & 1) != 0) &&
               ((long)((ulong)chr(iStack_10,iVar9)->bFlagsA << 0x3e) < 0)) {
              if (chr(iStack_10,iVar9)->f4c0 != -1) {
                IOPRelease__6HNMSndFi(uGpffff8374,chr(iStack_10,iVar9)->f4c0);
                chr(iStack_10,iVar9)->f4c0 = 0xffffffff;
              }
              if (chr(iStack_10,iVar9)->f4c8 != -1) {
                IOPRelease__6HNMSndFi(uGpffff8374,chr(iStack_10,iVar9)->f4c8);
                chr(iStack_10,iVar9)->f4c8 = 0xffffffff;
              }
            }
          }
          if (-1 < iStack_10->cDataId) {
            IOPRelease__6HNMSndFi(uGpffff8374,iStack_10->nIopHandle);
            DataRelease__7CBattleFiib(iStack_10,iStack_10->cDataId,0xc,0);
          }
          iStack_10->nIopHandle = 0xffffffff;
          iStack_10->cDataId = 0xff;
          Retail_CBtlPAfter2_SetDDispMode10(0x3f000000,uGpffff8618);
          AllBCurDestruct__7BtlMenuFv();
          iStack_10->nStep = 0xb;
          return;
        }
        if (sVar2 == 8) {
          if (*(char *)(iStack_10 + iStack_10->nDataSlot * 0x18 + 0x40c5) != '\x03') {
            return;
          }
          sVar2 = GetFaderMode__8BtlFaderFv();
          if (sVar2 != 0) {
            return;
          }
          iStack_10->cMesWinId2 = 0xff;
          chr(iStack_10,iStack_10->cActor)->bState = 0x16;
          chr(iStack_10,iStack_10->cActor)->bState2 = 0;
          iStack_10->nStep = 2;
          iStack_10->flMenuTimer = 0;
          return;
        }
        if (sVar2 == 7) {
          if ((long)((ulong)iStack_10->bFlags24 << 0x3e) < 0) {
            ClearCapture__6SSHSysFv(uGpffff8408);
            iStack_10->bFlags24 = iStack_10->bFlags24 & 0xfd;
          }
          iStack_10->bFlags24 = iStack_10->bFlags24 & 0xfe;
          uVar4 = FilterOn__9BtlSocketFbb(uGpffff836c,1,1);
          if (iStack_10->nCmd0_target != 0x14) {
            iStack_10->nStep = 10;
            return;
          }
          Retail_CBtlPAfter2_SetDDispMode10(0x3f000000,uGpffff8618,uVar4);
          AllBCurDestruct__7BtlMenuFv();
          iVar9 = GetRegCnt__9RegDatApiFii(0x44,0xffffffffffffffff);
          iVar7 = 0;
          for (uVar8 = 0; (int)uVar8 < iVar9; uVar8 = uVar8 + 1) {
            if (uVar8 != 0x14) {
              uVar10 = uVar8 & 7;
              if (((int)uVar8 < 0) && (uVar10 != 0)) {
                uVar10 = uVar10 - 8;
              }
              if (((uint)*(byte *)(iGpffff83b4 + ((int)uVar8 >> 3) + 0xf3f) & 1 << (uVar10 & 0x1f))
                  != 0) {
                auStack_e0[iVar7] = uVar8;
                iVar7 = iVar7 + 1;
              }
            }
          }
          iVar9 = rand();
          iStack_10->nCmd0_target = auStack_e0[iVar9 % iVar7];
          iStack_10->nCmd1 = iStack_10->nCmd1 + 1;
          for (iVar9 = 0x46; iVar9 < 0x4d; iVar9 = iVar9 + 1) {
            if ((*(int *)(iStack_10 + iVar9 * 4 + 0x4484) != 0) &&
               (iStack_40 = *(int *)(iStack_10 + iVar9 * 4 + 0x4484), iStack_40 != 0)) {
              (**(code **)(*(int *)(iStack_40 + 0x8c) + 8))(iStack_40,1);
            }
            *(undefined4 *)(iStack_10 + iVar9 * 4 + 0x4484) = 0;
          }
          DataRelease__7CBattleFiib(iStack_10,iStack_10->nDataSlot,0xc,0);
          iGpffff8620 = iGpffff8620 + 1;
          if (3 < iGpffff8620) {
            iGpffff8620 = 0;
          }
          uVar3 = DataReadEntry__7CBattleFiii(iStack_10,0xc,0xf,iStack_10->nCmd0_target);
          iStack_10->nDataSlot = uVar3;
          SetMode2__8BtlFaderFsf(0x3f000000,2);
          iStack_10->nStep = 8;
          return;
        }
        if (sVar2 == 6) {
          sVar2 = GetFaderMode__8BtlFaderFv();
          if (sVar2 != 1) {
            return;
          }
          (**(code **)(*(int *)(chr(iStack_10,iStack_10->cActor)->f4b0 +
                               0x14) + 0x30))();
          chr(iStack_10,iStack_10->cActor)->f4b0 = 0;
          iStack_10->nStep = 7;
          return;
        }
        if (sVar2 == 5) {
          if (*(char *)(chr(iStack_10,iStack_10->cActor)->f4b0 + 0x5e) !=
              '\x05') {
            return;
          }
          iStack_10->flMenuTimer = iStack_10->flMenuTimer + iStack_10->flDeltaT
          ;
          if (iStack_10->flMenuTimer < 0.5) {
            return;
          }
          SetAlphaMode__8BtlFaderFUl(0x44);
          uStack_28 = 0x80ffffff;
          puStack_3c = &uStack_28;
          SetMode__8BtlFaderFsf7_rgba32(0x3f000000,3,0x80ffffff);
          iStack_10->nStep = 6;
          iStack_10->flMenuTimer = 0;
          return;
        }
        if (sVar2 == 4) {
          cVar1 = IsCapture__6SSHSysFv(uGpffff8408);
          if (cVar1 == '\0') {
            return;
          }
          *(undefined1 *)(chr(iStack_10,iStack_10->cActor)->f4b0 + 0x5f)
               = 2;
          iStack_10->nStep = 5;
          iStack_10->flMenuTimer = 0;
          return;
        }
        if (sVar2 == 3) {
          iStack_10->bFlags24 = iStack_10->bFlags24 & 0xfe | 1;
          iStack_10->bFlags24 = iStack_10->bFlags24 & 0xfd | 2;
          ScreenCapture__6SSHSysFi(uGpffff8408,1);
          iStack_10->nStep = 4;
          return;
        }
        if (sVar2 != 2) {
          if (sVar2 == 1) {
            cVar1 = BtlChrReadyCheck__7CBattleFv(iStack_10);
            if (cVar1 == '\0') {
              return;
            }
            if (*(char *)(iStack_10 + iStack_10->nDataSlot * 0x18 + 0x40c5) != '\x03') {
              return;
            }
            ComboStopOff__Fi(0xffffffffffffffff);
            iStack_10->cMesWinId2 = 0xff;
            chr(iStack_10,iStack_10->cActor)->bState = 0x16;
            chr(iStack_10,iStack_10->cActor)->bState2 = 0;
            iStack_10->nStep = 2;
            iStack_10->flMenuTimer = 0;
            return;
          }
          if (sVar2 != 0) {
            return;
          }
          cVar1 = AllCSERelease__7CBattleFv(iStack_10);
          if (cVar1 == '\0') {
            return;
          }
          CloseBattleUI__7CBattleFb(iStack_10,1);
          if (chr(iStack_10,iStack_10->cActor)->bState == '\x11') {
            chr(iStack_10,iStack_10->cActor)->bState = 7;
            chr(iStack_10,iStack_10->cActor)->bState2 = 1;
          }
          iVar9 = iStack_10 + iStack_10->cActor * 0x510;
          *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
          cVar1 = Retail_CBattle_SetAllChrEffMask(iStack_10,1);
          if (cVar1 == '\0') {
            return;
          }
          if (chr(iStack_10,iStack_10->cActor)->bState != '\a') {
            return;
          }
          if ((long)((ulong)*(byte *)(*(int *)(iStack_10 + iStack_10->cActor * 0x510 +
                                              0x14c) + 0x4d0) << 0x3d) < 0) {
            return;
          }
          if ((iStack_10->nComboCnt != 0) &&
             ((chr(iStack_10,iStack_10->cActor)->bFlagsB & 1) == 0)) {
            MaxComboFunc__7CBattleFi(iStack_10,iStack_10->cActor);
            AddFriendship__7CBattleFiis
                      (iStack_10,
                       chr(iStack_10,iStack_10->cActor)->nCharId,
                       chr(iStack_10,iStack_10->cActorB)->nCharId,100)
            ;
          }
          iStack_30 = iStack_10->pTurnOrderDisp;
          *(undefined4 *)(iStack_30 + 0x5c) = 0;
          MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                    (0x40400000,iStack_10,0,0,0,0,0,0,iStack_10->cActor);
          iVar9 = GetRegCnt__9RegDatApiFii(0x44,0xffffffffffffffff);
          iVar7 = 0;
          for (uVar8 = 0; (int)uVar8 < iVar9; uVar8 = uVar8 + 1) {
            uVar10 = uVar8 & 7;
            if (((int)uVar8 < 0) && (uVar10 != 0)) {
              uVar10 = uVar10 - 8;
            }
            if (((uint)*(byte *)(iGpffff83b4 + ((int)uVar8 >> 3) + 0xf3f) & 1 << (uVar10 & 0x1f)) !=
                0) {
              auStack_e0[iVar7] = uVar8;
              iVar7 = iVar7 + 1;
            }
          }
          iVar9 = rand();
          iStack_10->nCmd0_target = auStack_e0[iVar9 % iVar7];
          iStack_10->nCmd1 = 0;
          *(undefined4 *)(iStack_10 + 0x80) = 0xffffffff;
          uVar4 = GetRegDat__9RegDatApiFiii(0x2a,0xf,0xffffffffffffffff);
          uVar3 = SetBtlMessage__7CBattleFiPv(iStack_10,0x146,uVar4);
          *(undefined4 *)(iStack_10 + 0x80) = uVar3;
          if (*(int *)(iStack_10 + 0x45cc) != 0) {
            iStack_34 = *(int *)(iStack_10 + 0x45cc);
            iStack_34->flDeltaT = 1;
          }
          SetCharacterCamera2__9BtlCameraFib
                    (iStack_10->pCamera,iStack_10->cActor,0,1);
          uVar4 = MaxComboFunc__7CBattleFi(iStack_10,iStack_10->cActor);
          uVar3 = DataReadEntry__7CBattleFiii
                            (iStack_10,0xc,0xf,iStack_10->nCmd0_target,uVar4);
          iStack_10->nDataSlot = uVar3;
          iStack_10->nStep = 1;
          if ((chr(iStack_10,iStack_10->cActor)->bFlagsB & 1) != 0) {
            return;
          }
          *(byte *)(iStack_10 + 0x4899) = *(byte *)(iStack_10 + 0x4899) & 0xfd | 2;
          *(byte *)(iStack_10 + 0x4898) = *(byte *)(iStack_10 + 0x4898) & 0x7f;
          return;
        }
        if (chr(iStack_10,iStack_10->cActor)->f4b0 == 0) {
          return;
        }
        if (*(char *)(chr(iStack_10,iStack_10->cActor)->f4b0 + 0x5f) <
            '\x01') {
          return;
        }
        FilterOff__9BtlSocketFbb(uGpffff836c,0,1);
        iStack_10->nStep = 3;
        return;
      }
      cVar1 = ReleaseCheck__6HNMSndFv(uGpffff8374);
      if (cVar1 == '\0') {
        return;
      }
      TarotRevertCard__7CBattleFii
                (iStack_10,iStack_10->nCmd0_target,iStack_10->nCmd1);
      iStack_10->nMsgHandle = 0xffff;
      if (((ulong)iStack_10->bTarotFlags & 0x1f) >> 3 == 0) {
        SetRetailCamera3__9BtlCameraFb(iStack_10->pCamera,1);
        SetMode2__8BtlFaderFsf(0x3f800000,2);
        iStack_10->nStep = 0xc;
        iStack_10->flMenuTimer = 0;
        return;
      }
      iVar9 = 0;
      for (uVar8 = 0; (int)uVar8 < 0xc; uVar8 = uVar8 + 1) {
        if ((((chr(iStack_10,uVar8)->bFlagsA & 1) != 0) &&
            ((long)((ulong)chr(iStack_10,uVar8)->bFlagsA << 0x3e) < 0)) &&
           (-1 < (long)((ulong)chr(iStack_10,uVar8)->bFlagsA2 << 0x3c))) {
          auStack_e0[iVar9] = uVar8;
          iVar9 = iVar9 + 1;
        }
      }
      *(undefined2 *)(iStack_10 + 0x3d92) = 0;
      iVar7 = 0;
      do {
        if (iVar9 <= iVar7) {
          if (*(short *)(iStack_10 + 0x3d92) < 1) {
            SetMode2__8BtlFaderFsf(0x3f800000,2);
            iStack_10->flMenuTimer = 0;
            iStack_10->nStep = 0x28;
            return;
          }
          iStack_10->bFlags25 = iStack_10->bFlags25 & 0xbf;
          iStack_10->bFlags25 = iStack_10->bFlags25 & 0x7f;
          *(byte *)(iStack_10 + 0x26) = *(byte *)(iStack_10 + 0x26) & 0xfe;
          *(undefined4 *)(iStack_10 + 0x490c) = 0;
          iStack_10->nMsgHandle = 0xffff;
          iStack_38 = *(int *)(iStack_10 + iStack_10->nDataSlot * 0x18 + 0x40cc);
          uVar3 = *(undefined4 *)(iStack_38 + 4);
          uStack_48 = uVar3;
          uStack_44 = uVar3;
          uStack_24 = GetFileSize(uVar3,7);
          uVar5 = GetFileEntry(uVar3,7);
          lVar6 = __nw__FUi(0x10);
          uVar4 = 0;
          if (lVar6 != 0) {
            uVar4 = __ct__9BufMemoryFUlUi(lVar6,uStack_24,0x80);
          }
          uStack_4c = *(undefined4 *)((int)uVar4 + 4);
          memcpy(uStack_4c,uVar5,uStack_24);
          lVar6 = __nw__FUi(0x48);
          uVar3 = 0;
          if (lVar6 != 0) {
            uVar3 = __ct__6EffectFPFPvi_vPvi(lVar6,0x472ce0,iStack_10,0);
          }
          iStack_10->pBtlResult = uVar3;
          Create__6EffectFP9BufMemory(iStack_10->pBtlResult,uVar4,1);
          SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi(iStack_10->pBtlResult,0x472cb0,iStack_10,0);
          *(undefined2 *)(iStack_10 + 0x3d90) = 1;
          *(int *)(iStack_10 + 0x3d94) = (int)iStack_10->cActor;
          *(undefined4 *)(iStack_10 + 0x3d98) =
               chr(iStack_10,iStack_10->cActor)->pModel;
          *(int *)(iStack_10 + 0x3d9c) = iStack_10 + iStack_10->cActor * 0x510 + 0xb0;
          SetGenModel__6EffectFiP11tagModelSet(iStack_10->pBtlResult,*(undefined2 *)(iStack_10 + 0x3d90),
                          iStack_10 + 0x3d94);
          SetTarModel__6EffectFiP11tagModelSet(iStack_10->pBtlResult,*(undefined2 *)(iStack_10 + 0x3d92),
                          iStack_10 + 0x3e84);
          Run__6EffectFv(iStack_10->pBtlResult);
          SetMode2__8BtlFaderFsf(0x3f000000,2);
          iStack_10->nStep = 0x14;
          return;
        }
        if ((((((ulong)iStack_10->bTarotFlags & 0x1f) >> 3 != 1) ||
             ((*(byte *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb4) & 1) == 0)) &&
            (((((ulong)iStack_10->bTarotFlags & 0x1f) >> 3 != 2 ||
              ((*(byte *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb4) & 1) != 0)) &&
             (((*(byte *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb4) & 1) == 0 ||
              (0 < *(int *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x130))))))) &&
           ((iStack_10->nTarotCard != 0xb ||
            (((((long)((ulong)iStack_10->bTarotFlags << 0x3e) < 0 ||
               (-1 < (long)((ulong)iStack_10->bTarotFlags << 0x3d))) &&
              ((-1 < (long)((ulong)iStack_10->bTarotFlags << 0x3e) ||
               ((long)((ulong)iStack_10->bTarotFlags << 0x3d) < 0)))) ||
             (((*(byte *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb4) & 1) != 0 ||
              (*(short *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x120) != 3)))))))) {
          if (((*(byte *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb4) & 1) != 0) ||
             (0 < *(int *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x130))) goto LAB_004914a0;
          if (iStack_10->nTarotCard == 0xb) {
            if ((long)((ulong)iStack_10->bTarotFlags << 0x3e) < 0) {
              if ((-1 < (long)((ulong)iStack_10->bTarotFlags << 0x3d)) &&
                 (*(short *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x120) == 3))
              goto LAB_004914a0;
            }
            else if (((long)((ulong)iStack_10->bTarotFlags << 0x3d) < 0) ||
                    (*(short *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x120) != 3)) {
LAB_004914a0:
              *(uint *)(iStack_10 + *(short *)(iStack_10 + 0x3d92) * 0x14 + 0x3e84) =
                   auStack_e0[iVar7];
              *(undefined4 *)(iStack_10 + *(short *)(iStack_10 + 0x3d92) * 0x14 + 0x3e88) =
                   *(undefined4 *)(iStack_10 + auStack_e0[iVar7] * 0x510 + 0x14c);
              *(uint *)(iStack_10 + *(short *)(iStack_10 + 0x3d92) * 0x14 + 0x3e8c) =
                   iStack_10 + auStack_e0[iVar7] * 0x510 + 0xb0;
              *(short *)(iStack_10 + 0x3d92) = *(short *)(iStack_10 + 0x3d92) + 1;
            }
          }
        }
        iVar7 = iVar7 + 1;
      } while( true );
    }
    if (chr(iStack_10,iStack_10->cActor)->nMonId != 499) {
      cVar1 = DestinationSearch__7CBattleFi(iStack_10,iStack_10->cActor);
      if (cVar1 != '\x01') {
        return;
      }
      if (4 < iStack_10->nDestCount) {
        DestinationListUp__7CBattleFii(iStack_10,4,iStack_10->cActor);
      }
    }
    iStack_10->nStep = 0x34;
  }
  iStack_1c = 0;
  if (*(int *)(iStack_10 + 0x4624) != 0) {
    if (*(short *)(*(int *)(iStack_10 + 0x4624) + 0x28) != 0x14) {
      *(undefined2 *)(*(int *)(iStack_10 + 0x4624) + 0x28) = 0x17;
      *(undefined2 *)(*(int *)(iStack_10 + 0x4624) + 0x2a) = 3;
    }
    iStack_1c = 1;
  }
  if (iStack_1c == 0) {
    iStack_10->nDestIdx = 0;
    if (chr(iStack_10,iStack_10->cActor)->nMonId != 499) {
      iVar9 = rand();
      iVar9 = iVar9 % (int)iStack_10->nDestCount;
      chr(iStack_10,iStack_10->cActor)->aDest =
           *(undefined4 *)(iStack_10 + iVar9 * 8 + 0x403c);
      chr(iStack_10,iStack_10->cActor)->fc4 = 0;
      chr(iStack_10,iStack_10->cActor)->fc8 =
           *(undefined4 *)(iStack_10 + iVar9 * 8 + 0x4040);
      iVar9 = iStack_10 + iStack_10->cActor * 0x510;
      *(byte *)(iVar9 + 0xb1) = *(byte *)(iVar9 + 0xb1) & 0xdf | 0x20;
    }
    iStack_10->nPhase = 0x14;
    iStack_10->nStep = 0;
    iStack_10->nCmdKind = 0;
    iStack_10->nCmdMask = 1 << ((int)iStack_10->cActor & 0x1fU);
    iStack_10->flTurnPush = 0x40400000;
    if (iStack_10->nComboCnt == 0) {
      iStack_10->bFlags25 = iStack_10->bFlags25 & 0xfb;
    }
  }
  return;
}

/* ---- 0x00492200  LastBossFunc__7CBattleFv  (size 0x1250) ----
 *   nStep values: ['0x0', '0x2', '0x3', '0x4', '0xa', '0xb', '0xc', '0xd']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7'] */
void LastBossFunc__7CBattleFv(int this)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  
  sVar2 = this->nStep;
  lVar7 = (long)sVar2;
  if (sVar2 != 0xd) {
    iVar6 = 0xc;
    if (sVar2 != 0xc) {
      iVar5 = 0xd;
      if (sVar2 != 0xb) {
        if (sVar2 != 10) {
          if (sVar2 == 4) {
            if ((-1 < (long)((ulong)this->bFlags25 << 0x39)) &&
               (-1 < (long)((ulong)this->bFlags25 << 0x38))) {
              return;
            }
            if ((long)((ulong)this->bFlags25 << 0x39) < 0) {
              iVar6 = this->pBtlResult;
              if (iVar6 != 0) {
                (**(code **)(*(int *)(iVar6 + 0x14) + 8))(iVar6,1);
              }
              this->pBtlResult = 0;
              SetAlphaMode__8BtlFaderFUl(0x44);
              Retail_CBattle_ReleaseChrWait(this);
            }
            LastBossSpecial__7CBattleFv(this);
            if (this->pParamDisp != 0) {
              SetParty__9ParamDispFii(this->pParamDisp,4,0xffffffffffffffff);
            }
            MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                      (0x40400000,this,0,0,0,0,0,0,this->cActor);
            this->flMenuTimer = 0;
            this->nPhase = 0x14;
            this->nStep = 0;
            this->nCmdKind = 1;
            this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
            this->flTurnPush = 0x40400000;
            if (this->nComboCnt != 0) {
              return;
            }
            this->bFlags25 = this->bFlags25 & 0xfb;
            return;
          }
          if (sVar2 != 3) {
            if (sVar2 != 2) {
              if (sVar2 != 0) {
                return;
              }
              cVar1 = AllCSERelease__7CBattleFv(this);
              if (cVar1 == '\0') {
                return;
              }
              CloseBattleUI__7CBattleFb(this,1);
              *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
              MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                        (0x40400000,this,0,0,0,0,0,0,this->cActor);
              if (*(int *)(this + 0x45cc) != 0) {
                *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
              }
              cVar1 = Retail_CBattle_SetAllChrEffMask(this,1);
              if (cVar1 == '\0') {
                return;
              }
              if (chr(this,this->cActor)->bState == '\x11') {
                chr(this,this->cActor)->bState = 7;
                chr(this,this->cActor)->bState2 = 1;
              }
              iVar6 = this + this->cActor * 0x510;
              *(byte *)(iVar6 + 0xb5) = *(byte *)(iVar6 + 0xb5) & 0xf7;
              if (*(short *)(chr(this,this->cActor)->pModel + 0x510)
                  != 1) {
                SetBtlMotion__8BtlModelFif
                          (0x3f800000,
                           chr(this,this->cActor)->pModel,1);
                chr(this,this->cActor)->bState = 7;
                chr(this,this->cActor)->bState2 = 2;
                iVar6 = this + this->cActor * 0x510;
                *(byte *)(iVar6 + 0xb4) = *(byte *)(iVar6 + 0xb4) & 0xf9;
                iVar6 = this + this->cActor * 0x510;
                *(byte *)(iVar6 + 0xb5) = *(byte *)(iVar6 + 0xb5) & 0xdf;
                iVar6 = this + this->cActor * 0x510;
                *(byte *)(iVar6 + 0xb5) = *(byte *)(iVar6 + 0xb5) & 0xbf;
              }
              SetCharacterCamera1__9BtlCameraFib
                        (this->pCamera,this->cActor,1);
              lVar7 = Retail_CBattle_FindLastBossPart(this,1);
              if (-1 < lVar7) {
                *(uint *)(this->pCamera + 0x140) =
                     *(uint *)(this->pCamera + 0x140) | 1 << ((uint)lVar7 & 0x1f);
              }
              lVar7 = Retail_CBattle_FindLastBossPart(this,2);
              if (-1 < lVar7) {
                *(uint *)(this->pCamera + 0x140) =
                     *(uint *)(this->pCamera + 0x140) | 1 << ((uint)lVar7 & 0x1f);
              }
              lVar7 = Retail_CBattle_FindLastBossPart(this,3);
              if (-1 < lVar7) {
                *(uint *)(this->pCamera + 0x140) =
                     *(uint *)(this->pCamera + 0x140) | 1 << ((uint)lVar7 & 0x1f);
              }
              this->nDataSlot = 0xffffffff;
              if ((long)((ulong)*(byte *)(this + 0x26) << 0x3c) < 0) {
                if ((this->pBtlResult == 0) ||
                   ((long)((ulong)this->bFlags25 << 0x39) < 0)) {
                  this->nStep = 0xb;
                }
                else {
                  EffectNext__6EffectFv(this->pBtlResult);
                  this->nStep = 10;
                }
                this->flMenuTimer = 0;
                return;
              }
              uVar3 = DataReadEntry__7CBattleFiii(this,0xc,0xd,0);
              this->nDataSlot = uVar3;
              if ((this->pBtlResult != 0) &&
                 (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                EffectNext__6EffectFv(this->pBtlResult);
                this->nStep = 2;
                return;
              }
              this->nStep = 3;
              return;
            }
            if ((this->pBtlResult != 0) &&
               (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
              return;
            }
            iVar6 = this->pBtlResult;
            if (iVar6 != 0) {
              (**(code **)(*(int *)(iVar6 + 0x14) + 8))(iVar6,1);
            }
            this->pBtlResult = 0;
            SetAlphaMode__8BtlFaderFUl(0x44);
            sVar2 = Retail_CBattle_ReleaseChrWait(this);
            this->nStep = 3;
            iVar6 = this;
          }
          cVar1 = BtlChrReadyCheck__7CBattleFv(this,iVar6,sVar2);
          if (cVar1 == '\0') {
            return;
          }
          if (*(char *)(this + this->nDataSlot * 0x18 + 0x40c5) != '\x03') {
            return;
          }
          this->bFlags25 = this->bFlags25 & 0xbf;
          this->bFlags25 = this->bFlags25 & 0x7f;
          *(byte *)(this + 0x26) = *(byte *)(this + 0x26) & 0xfe;
          *(undefined4 *)(this + 0x490c) = 0;
          this->nMsgHandle = 0xffff;
          lVar7 = __nw__FUi(0x48);
          uVar3 = 0;
          if (lVar7 != 0) {
            uVar3 = __ct__6EffectFPFPvi_vPvi(lVar7,0x472ce0,this,0);
          }
          this->pBtlResult = uVar3;
          Create__6EffectFP9BufMemory(this->pBtlResult,
                          *(undefined4 *)(this + this->nDataSlot * 0x18 + 0x40cc),1);
          SetReplaceCallback__6EffectFPFP6EffectPvi_vPvi(this->pBtlResult,0x472cb0,this,0);
          DataRelease__7CBattleFiib(this,this->nDataSlot,0xc,1);
          *(undefined2 *)(this + 0x3d90) = 1;
          *(int *)(this + 0x3d94) = (int)this->cActor;
          *(undefined4 *)(this + 0x3d98) =
               chr(this,this->cActor)->pModel;
          *(int *)(this + 0x3d9c) = this + this->cActor * 0x510 + 0xb0;
          lVar7 = Retail_CBattle_FindLastBossPart(this,1);
          if (-1 < lVar7) {
            iVar6 = (int)lVar7;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d94) = iVar6;
            *(undefined4 *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d98) =
                 chr(this,iVar6)->pModel;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d9c) =
                 this + iVar6 * 0x510 + 0xb0;
            *(short *)(this + 0x3d90) = *(short *)(this + 0x3d90) + 1;
          }
          lVar7 = Retail_CBattle_FindLastBossPart(this,2);
          if (-1 < lVar7) {
            iVar6 = (int)lVar7;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d94) = iVar6;
            *(undefined4 *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d98) =
                 chr(this,iVar6)->pModel;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d9c) =
                 this + iVar6 * 0x510 + 0xb0;
            *(short *)(this + 0x3d90) = *(short *)(this + 0x3d90) + 1;
          }
          lVar7 = Retail_CBattle_FindLastBossPart(this,3);
          if (-1 < lVar7) {
            iVar6 = (int)lVar7;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d94) = iVar6;
            *(undefined4 *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d98) =
                 chr(this,iVar6)->pModel;
            *(int *)(this + *(short *)(this + 0x3d90) * 0x14 + 0x3d9c) =
                 this + iVar6 * 0x510 + 0xb0;
            *(short *)(this + 0x3d90) = *(short *)(this + 0x3d90) + 1;
          }
          SetGenModel__6EffectFiP11tagModelSet(this->pBtlResult,*(undefined2 *)(this + 0x3d90),
                          this + 0x3d94);
          lVar7 = 0;
          while (lVar7 < *(short *)(this + 0x3d90)) {
            iVar6 = (int)lVar7;
            *(undefined4 *)(this + iVar6 * 0x14 + 0x3e84) =
                 *(undefined4 *)(this + iVar6 * 0x14 + 0x3d94);
            *(undefined4 *)(this + iVar6 * 0x14 + 0x3e88) =
                 *(undefined4 *)(this + iVar6 * 0x14 + 0x3d98);
            *(undefined4 *)(this + iVar6 * 0x14 + 0x3e8c) =
                 *(undefined4 *)(this + iVar6 * 0x14 + 0x3d9c);
            lVar7 = (long)(iVar6 + 1);
          }
          *(undefined2 *)(this + 0x3d92) = *(undefined2 *)(this + 0x3d90);
          uVar4 = SetTarModel__6EffectFiP11tagModelSet(this->pBtlResult,
                                  *(undefined2 *)(this + 0x3d92),this + 0x3e84);
          Run__6EffectFv(this->pBtlResult,uVar4);
          this->nStep = 4;
          ComboStopOff__Fi(0xffffffffffffffff);
          this->wTurnPendMask = 0;
          return;
        }
        if ((this->pBtlResult != 0) &&
           (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
          return;
        }
        iVar6 = this->pBtlResult;
        if (iVar6 != 0) {
          (**(code **)(*(int *)(iVar6 + 0x14) + 8))(iVar6,1);
        }
        this->pBtlResult = 0;
        uVar4 = SetAlphaMode__8BtlFaderFUl(0x44);
        sVar2 = Retail_CBattle_ReleaseChrWait(this,uVar4);
        this->nStep = 0xb;
        iVar6 = 0x3f000000;
        this->flMenuTimer = 0x3f000000;
        iVar5 = this;
      }
      sVar2 = GetFaderMode__8BtlFaderFv(iVar5,iVar6,sVar2);
      if (sVar2 != 0) {
        return;
      }
      this->flMenuTimer = this->flMenuTimer - this->flDeltaT;
      if (0.0 < this->flMenuTimer) {
        return;
      }
      SetMode__8BtlFaderFsf7_rgba32(0x3f000000,3,0x80ffffff);
      this->nStep = 0xc;
      return;
    }
    sVar2 = GetFaderMode__8BtlFaderFv();
    if (sVar2 != 1) {
      return;
    }
    LastBossSpecial__7CBattleFv(this);
    if (this->pParamDisp != 0) {
      SetParty__9ParamDispFii(this->pParamDisp,4,0xffffffffffffffff);
    }
    MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
              (0x40400000,this,0,0,0,0,0,0,this->cActor);
    sVar2 = SetMode2__8BtlFaderFsf(0x3f000000,2);
    lVar7 = (long)this;
    this->nStep = 0xd;
  }
  sVar2 = GetFaderMode__8BtlFaderFv(0xd,lVar7,sVar2);
  if (sVar2 == 0) {
    this->nPhase = 0x14;
    this->nStep = 0;
    this->flMenuTimer = 0;
    this->nCmdKind = 1;
    this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
    lVar7 = Retail_CBattle_FindLastBossPart(this,1);
    if (-1 < lVar7) {
      this->nCmdMask = this->nCmdMask | 1 << ((uint)lVar7 & 0x1f);
    }
    lVar7 = Retail_CBattle_FindLastBossPart(this,2);
    if (-1 < lVar7) {
      this->nCmdMask = this->nCmdMask | 1 << ((uint)lVar7 & 0x1f);
    }
    lVar7 = Retail_CBattle_FindLastBossPart(this,3);
    if (-1 < lVar7) {
      this->nCmdMask = this->nCmdMask | 1 << ((uint)lVar7 & 0x1f);
    }
    if (this->nComboCnt == 0) {
      this->bFlags25 = this->bFlags25 & 0xfb;
    }
  }
  return;
}

/* ---- 0x00493450  Retail_CBattle_Phase0F_BerserkApproachAlly  (size 0xa80) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0xb'] */
void Retail_CBattle_Phase0F_BerserkApproachAlly(undefined8 this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  int this;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  auStack_10._4_4_ = in_zero_hi;
  auStack_10._0_4_ = in_zero_lo;
  auStack_10._8_4_ = in_zero_udw;
  auStack_10._12_4_ = in_register_0000000c;
  /* this = this */
  switch(this->nStep) {
  case 0:
    cVar1 = AllCSERelease__7CBattleFv(this);
    if (cVar1 == '\0') {
      return;
    }
    CloseBattleUI__7CBattleFb(this,1);
    MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
              (0x40400000,this,0,0,0,0,0,0,this->cActor);
    *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
    SetSelectChr__13TurnOrderDispFii
              (this->pTurnOrderDisp,this->nCmd0_target,1);
    if (chr(this,this->cActor)->f4bc != 0) {
      iVar2 = this + this->cActor * 0x510;
      *(byte *)(iVar2 + 0xb1) = *(byte *)(iVar2 + 0xb1) & 0xfb | 4;
    }
    if (chr(this,this->nCmd0_target)->f4c4 != 0) {
      iVar2 = this + this->nCmd0_target * 0x510;
      *(byte *)(iVar2 + 0xb1) = *(byte *)(iVar2 + 0xb1) & 0xf7 | 8;
    }
    if ((this->nComboCnt != 0) &&
       ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
      MaxComboFunc__7CBattleFi(this,this->cActor);
      AddFriendship__7CBattleFiis
                (this,chr(this,this->cActor)->nCharId,
                 chr(this,this->cActorB)->nCharId,100);
    }
    this->nStep = 1;
  case 1:
    if (chr(this,this->cActor)->bState == '\x11') {
      chr(this,this->cActor)->bState = 7;
      chr(this,this->cActor)->bState2 = 1;
    }
    iVar2 = this + this->cActor * 0x510;
    *(byte *)(iVar2 + 0xb5) = *(byte *)(iVar2 + 0xb5) & 0xf7;
    if ((((chr(this,this->cActor)->f4bc == 0) ||
         (-1 < (long)((ulong)chr(this,this->cActor)->bFlagsA1 << 0x3d))) &&
        ((chr(this,this->nCmd0_target)->f4bc == 0 ||
         (-1 < (long)((ulong)chr(this,this->nCmd0_target)->bFlagsA1 << 0x3d)))))
       && (((chr(this,this->cActor)->bState == '\a' &&
            (-1 < (long)((ulong)*(byte *)(chr(this,this->cActor)->pModel
                                         + 0x4d0) << 0x3d))) &&
           (cVar1 = BtlChrReadyCheck__7CBattleFv(this), cVar1 != '\0')))) {
      FindAdjacentEffectPos__7CBattleFiifP7FVector
                (this,this->cActor,this->nCmd0_target,
                 this + this->cActor * 0x510 + 0x170,auStack_10);
      chr(this,this->cActor)->f2c = auStack_10._0_4_;
      chr(this,this->cActor)->f30 = auStack_10._8_4_;
      chr(this,this->cActor)->bState = 0xb;
      chr(this,this->cActor)->fc =
           this->nCmd0_target;
      chr(this,this->cActor)->bState2 = 0;
      auStack_10 = *(undefined1 (*) [16])(this + this->cActor * 0x510 + 0x170);
      auVar5 = _lqc2(*(undefined1 (*) [16])(this + this->cActor * 0x510 + 0x160));
      auVar6 = _lqc2(*(undefined1 (*) [16])(this + this->cActor * 0x510 + 0x3a0));
      auVar5 = _vadd(auVar5,auVar6);
      auStack_70 = _sqc2(auVar5);
      __ct__7FVectorFPC7FVector(auStack_30,auStack_70);
      auVar6 = _lqc2(auStack_30);
      auVar5 = _lqc2(auStack_10);
      auVar5 = _vsub(auVar5,auVar6);
      auStack_10 = _sqc2(auVar5);
      uVar3 = __ct__7FVectorFPC7FVector(auStack_50,auStack_10);
      Get3DAngle__F7FVector(auStack_40,uVar3);
      uStack_20 = auStack_40._0_4_;
      fStack_1c = auStack_40._4_4_;
      uStack_18 = uStack_38;
      uStack_14 = uStack_34;
      ChangeBtlChrAngle__7CBattleFif(180.0 - fStack_1c,this,this->cActor);
      uVar3 = __ct__7FVectorFPC7FVector(auStack_60,this + this->cActor * 0x510 + 0x170);
      SetMoveCamera1__9BtlCameraFi7FVectorib
                (this->pCamera,this->cActor,uVar3,
                 this->nCmd0_target,1);
      if (this->nComboCnt == 0) {
        this->bFlags25 = this->bFlags25 & 0xfb;
      }
      ComboStopOff__Fi(0xffffffffffffffff);
      this->nStep = 2;
      this->flMenuTimer = 0;
    }
    break;
  case 2:
    if (chr(this,this->cActor)->bState2 < '\x02') {
      return;
    }
    SetCharacterCamera2__9BtlCameraFib
              (this->pCamera,this->cActor,0,1);
    *(uint *)(this->pCamera + 0x140) =
         *(uint *)(this->pCamera + 0x140) | 3 << ((this->nCmd0_target & 0xf) << 1);
    this->nStep = 3;
  case 3:
    if ((chr(this,this->cActor)->bState == '\a') ||
       (chr(this,this->cActor)->bState == '\x11')) {
      this->nDestIdx = 0;
      this->nStep = 4;
    }
    break;
  case 4:
    cVar1 = DestinationSearch__7CBattleFi(this,this->cActor);
    if (cVar1 != '\x01') {
      return;
    }
    if (4 < this->nDestCount) {
      DestinationListUp__7CBattleFii(this,4,this->cActor);
    }
    this->nStep = 5;
  case 5:
    this->nDestIdx = 0;
    iVar2 = rand();
    iVar2 = iVar2 % (int)this->nDestCount;
    chr(this,this->cActor)->aDest =
         *(undefined4 *)(this + iVar2 * 8 + 0x403c);
    chr(this,this->cActor)->fc4 = 0;
    chr(this,this->cActor)->fc8 =
         *(undefined4 *)(this + iVar2 * 8 + 0x4040);
    iVar2 = this + this->cActor * 0x510;
    *(byte *)(iVar2 + 0xb1) = *(byte *)(iVar2 + 0xb1) & 0xdf | 0x20;
    this->nPhase = 0x14;
    this->nStep = 0;
    this->nCmdKind = 1;
    this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
    this->flTurnPush = 0x40400000;
  }
  return;
}

/* ---- 0x00493ed0  Retail_CBattle_Phase10_BerserkFindItem  (size 0xb30) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0xc'] */
void Retail_CBattle_Phase10_BerserkFindItem(int this)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined8 uStack_120;
  undefined1 uStack_118;
  undefined1 auStack_110 [256];
  int iStack_10;
  
  uStack_140 = (undefined4)_DAT_006e2e80;
  uStack_13c = (undefined4)((ulong)_DAT_006e2e80 >> 0x20);
  uStack_138 = DAT_006e2e88;
  uStack_134 = DAT_006e2e8c;
  uStack_130 = DAT_006e2e90;
  uStack_12c = DAT_006e2e94;
  uStack_128 = DAT_006e2e98;
  uStack_124 = DAT_006e2e9c;
  uStack_120 = DAT_006e2ea0;
  uStack_118 = DAT_006e2ea8;
  iStack_10 = this;
  switch(this->nStep) {
  case 0:
    cVar1 = AllCSERelease__7CBattleFv(this);
    if (cVar1 == '\0') {
      return;
    }
    CloseBattleUI__7CBattleFb(iStack_10,1);
    MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
              (0x40400000,iStack_10,0,0,0,0,0,0,iStack_10->cActor);
    *(undefined4 *)(iStack_10->pTurnOrderDisp + 0x5c) = 0;
    SetSelectChr__13TurnOrderDispFii
              (iStack_10->pTurnOrderDisp,iStack_10->nCmd0_target,1);
    if (chr(iStack_10,iStack_10->cActor)->f4bc != 0) {
      iVar3 = iStack_10 + iStack_10->cActor * 0x510;
      *(byte *)(iVar3 + 0xb1) = *(byte *)(iVar3 + 0xb1) & 0xfb | 4;
    }
    if ((iStack_10->nComboCnt != 0) &&
       ((chr(iStack_10,iStack_10->cActor)->bFlagsB & 1) == 0)) {
      MaxComboFunc__7CBattleFi(iStack_10,iStack_10->cActor);
      AddFriendship__7CBattleFiis
                (iStack_10,chr(iStack_10,iStack_10->cActor)->nCharId,
                 chr(iStack_10,iStack_10->cActorB)->nCharId,100);
    }
    iStack_10->nStep = 1;
  case 1:
    if (chr(iStack_10,iStack_10->cActor)->bState == '\x11') {
      chr(iStack_10,iStack_10->cActor)->bState = 7;
      chr(iStack_10,iStack_10->cActor)->bState2 = 1;
    }
    iVar3 = iStack_10 + iStack_10->cActor * 0x510;
    *(byte *)(iVar3 + 0xb5) = *(byte *)(iVar3 + 0xb5) & 0xf7;
    if ((((chr(iStack_10,iStack_10->cActor)->f4bc == 0) ||
         (-1 < (long)((ulong)chr(iStack_10,iStack_10->cActor)->bFlagsA1 <<
                     0x3d))) &&
        (chr(iStack_10,iStack_10->cActor)->bState == '\a')) &&
       ((-1 < (long)((ulong)*(byte *)(*(int *)(iStack_10 + iStack_10->cActor * 0x510 +
                                              0x14c) + 0x4d0) << 0x3d) &&
        (cVar1 = BtlChrReadyCheck__7CBattleFv(iStack_10), cVar1 != '\0')))) {
      chr(iStack_10,iStack_10->cActor)->bState = 0xc;
      chr(iStack_10,iStack_10->cActor)->bState2 = 0;
      SetCharacterCamera2__9BtlCameraFib
                (iStack_10->pCamera,iStack_10->cActor,1,1);
      uVar2 = SetBtlMessage__7CBattleFiPv(iStack_10,0x7b,0);
      iStack_10->nCmd0_target = uVar2;
      if (iStack_10->nComboCnt == 0) {
        iStack_10->bFlags25 = iStack_10->bFlags25 & 0xfb;
      }
      ComboStopOff__Fi(0xffffffffffffffff);
      iStack_10->nStep = 2;
    }
    break;
  case 2:
    if (chr(this,this->cActor)->bState2 < '\x02') {
      return;
    }
    lVar6 = FindMesWin__7BtlMenuFi(this->nCmd0_target);
    if (lVar6 != 0) {
      return;
    }
    SetNextBtlMotion__8BtlModelFif
              (0x3f800000,chr(iStack_10,iStack_10->cActor)->pModel,
               0x3a);
    iVar3 = rand();
    if (iVar3 % 10000 < 0x1389) {
      iVar8 = 0;
      for (iVar3 = 0; iVar3 < 0x29; iVar3 = iVar3 + 1) {
        iVar8 = iVar8 + (uint)*(byte *)((int)&uStack_140 + iVar3);
      }
      iVar3 = rand();
      iVar9 = 0;
      iVar7 = 0;
      while ((iVar7 < 0x29 &&
             (iVar9 = iVar9 + (uint)*(byte *)((int)&uStack_140 + iVar7), iVar9 < iVar3 % iVar8))) {
        iVar7 = iVar7 + 1;
      }
      uVar4 = GetRegDat__9RegDatApiFiii(6,iVar7,0xffffffffffffffff);
      uVar5 = Retail_GetItemKindTable(iVar7,0);
      sprintf(auStack_110,0x6e4908,uVar5,uVar4);
      uVar2 = SetBtlMessage__7CBattleFiPv(iStack_10,0x7c,auStack_110);
      iStack_10->nCmd0_target = uVar2;
      iVar3 = iGpffff83b4 + (uint)*(byte *)(iGpffff83b4 + 2) * 0x200 + iVar7;
      *(char *)(iVar3 + 0xabc) = *(char *)(iVar3 + 0xabc) + '\x01';
      if (99 < *(byte *)(iGpffff83b4 + (uint)*(byte *)(iGpffff83b4 + 2) * 0x200 + iVar7 + 0xabc)) {
        *(undefined1 *)(iGpffff83b4 + (uint)*(byte *)(iGpffff83b4 + 2) * 0x200 + iVar7 + 0xabc) = 99
        ;
      }
      PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x1002,1,0);
    }
    else {
      uVar2 = SetBtlMessage__7CBattleFiPv(iStack_10,0x7d,0);
      iStack_10->nCmd0_target = uVar2;
    }
    iStack_10->nStep = 3;
  case 3:
    if ((chr(iStack_10,iStack_10->cActor)->bState == '\a') &&
       (lVar6 = FindMesWin__7BtlMenuFi(iStack_10->nCmd0_target), lVar6 == 0)) {
      iStack_10->nDestIdx = 0;
      iStack_10->nStep = 4;
    }
    break;
  case 4:
    cVar1 = DestinationSearch__7CBattleFi(this,this->cActor);
    if (cVar1 != '\x01') {
      return;
    }
    if (4 < iStack_10->nDestCount) {
      DestinationListUp__7CBattleFii(iStack_10,4,iStack_10->cActor);
    }
    iStack_10->nStep = 5;
  case 5:
    iStack_10->nDestIdx = 0;
    iVar3 = rand();
    iVar3 = iVar3 % (int)iStack_10->nDestCount;
    chr(iStack_10,iStack_10->cActor)->aDest =
         *(undefined4 *)(iStack_10 + iVar3 * 8 + 0x403c);
    chr(iStack_10,iStack_10->cActor)->fc4 = 0;
    chr(iStack_10,iStack_10->cActor)->fc8 =
         *(undefined4 *)(iStack_10 + iVar3 * 8 + 0x4040);
    iVar3 = iStack_10 + iStack_10->cActor * 0x510;
    *(byte *)(iVar3 + 0xb1) = *(byte *)(iVar3 + 0xb1) & 0xdf | 0x20;
    iStack_10->nPhase = 0x14;
    iStack_10->nStep = 0;
    iStack_10->nCmdKind = 1;
    iStack_10->nCmdMask = 1 << ((int)iStack_10->cActor & 0x1fU);
    iStack_10->flTurnPush = 0x40400000;
  }
  return;
}

/* ---- 0x00494a00  Retail_CBattle_Phase11_BerserkTalk  (size 0x8d0) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0xd'] */
void Retail_CBattle_Phase11_BerserkTalk(int this)

{
  short sVar1;
  char cVar2;
  undefined4 uVar3;
  long lVar4;
  int iVar5;
  
  sVar1 = this->nStep;
  if (sVar1 != 4) {
    if (sVar1 != 3) {
      if (sVar1 == 2) {
        if (chr(this,this->cActor)->bState2 < '\x02') {
          return;
        }
        lVar4 = FindMesWin__7BtlMenuFi(this->nCmd0_target);
        if (lVar4 != 0) {
          return;
        }
        this->nDestIdx = 0;
        this->nStep = 3;
        return;
      }
      if (sVar1 != 1) {
        if (sVar1 != 0) {
          return;
        }
        cVar2 = AllCSERelease__7CBattleFv(this);
        if (cVar2 == '\0') {
          return;
        }
        CloseBattleUI__7CBattleFb(this,1);
        MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                  (0x40400000,this,0,0,0,0,0,0,this->cActor);
        *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
        SetSelectChr__13TurnOrderDispFii
                  (this->pTurnOrderDisp,this->nCmd0_target,1);
        if (chr(this,this->cActor)->f4bc != 0) {
          iVar5 = this + this->cActor * 0x510;
          *(byte *)(iVar5 + 0xb1) = *(byte *)(iVar5 + 0xb1) & 0xfb | 4;
        }
        if ((this->nComboCnt != 0) &&
           ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
          MaxComboFunc__7CBattleFi(this,this->cActor);
          AddFriendship__7CBattleFiis
                    (this,chr(this,this->cActor)->nCharId,
                     chr(this,this->cActorB)->nCharId,100);
        }
        this->nStep = 1;
      }
      if (chr(this,this->cActor)->bState == '\x11') {
        chr(this,this->cActor)->bState = 7;
        chr(this,this->cActor)->bState2 = 1;
      }
      iVar5 = this + this->cActor * 0x510;
      *(byte *)(iVar5 + 0xb5) = *(byte *)(iVar5 + 0xb5) & 0xf7;
      if ((chr(this,this->cActor)->f4bc != 0) &&
         ((long)((ulong)chr(this,this->cActor)->bFlagsA1 << 0x3d) < 0))
      {
        return;
      }
      if (chr(this,this->cActor)->bState != '\a') {
        return;
      }
      if ((long)((ulong)*(byte *)(chr(this,this->cActor)->pModel +
                                 0x4d0) << 0x3d) < 0) {
        return;
      }
      cVar2 = BtlChrReadyCheck__7CBattleFv(this);
      if (cVar2 == '\0') {
        return;
      }
      chr(this,this->cActor)->bState = 0xd;
      chr(this,this->cActor)->bState2 = 0;
      SetCharacterCamera2__9BtlCameraFib
                (this->pCamera,this->cActor,1,1);
      if (chr(this,this->cActor)->nCharId == 2) {
        uVar3 = SetBtlMessage__7CBattleFiPv(this,0x7e,0);
        this->nCmd0_target = uVar3;
      }
      else {
        uVar3 = SetBtlMessage__7CBattleFiPv(this,0x81,0);
        this->nCmd0_target = uVar3;
      }
      if (this->nComboCnt == 0) {
        this->bFlags25 = this->bFlags25 & 0xfb;
      }
      ComboStopOff__Fi(0xffffffffffffffff);
      this->nStep = 2;
      return;
    }
    cVar2 = DestinationSearch__7CBattleFi(this,this->cActor);
    if (cVar2 != '\x01') {
      return;
    }
    if (4 < this->nDestCount) {
      DestinationListUp__7CBattleFii(this,4,this->cActor);
    }
    this->nStep = 4;
  }
  this->nDestIdx = 0;
  iVar5 = rand();
  iVar5 = iVar5 % (int)this->nDestCount;
  chr(this,this->cActor)->aDest =
       *(undefined4 *)(this + iVar5 * 8 + 0x403c);
  chr(this,this->cActor)->fc4 = 0;
  chr(this,this->cActor)->fc8 =
       *(undefined4 *)(this + iVar5 * 8 + 0x4040);
  iVar5 = this + this->cActor * 0x510;
  *(byte *)(iVar5 + 0xb1) = *(byte *)(iVar5 + 0xb1) & 0xdf | 0x20;
  this->nPhase = 0x14;
  this->nStep = 0;
  this->nCmdKind = 1;
  this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
  this->flTurnPush = 0x40400000;
  return;
}

/* ---- 0x004952d0  Retail_CBattle_Phase12_BerserkPose  (size 0x600) ----
 *   nStep values: ['0x0', '0x1', '0x2']
 *   nPhase targets: ['0x14']
 *   bState targets: ['0x7', '0x26'] */
void Retail_CBattle_Phase12_BerserkPose(undefined8 this)

{
  short sVar1;
  char cVar2;
  undefined4 uVar3;
  long lVar4;
  int iVar5;
  int this;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  /* this = this */
  sVar1 = this->nStep;
  if (sVar1 == 2) {
    if ((chr(this,this->cActor)->bState == '*') &&
       (lVar4 = FindMesWin__7BtlMenuFi(this->nCmd0_target), lVar4 == 0)) {
      this->nPhase = 0x14;
      this->nStep = 0;
      this->nCmdKind = 1;
      this->nCmdMask = 1 << ((int)this->cActor & 0x1fU);
      this->flTurnPush = 0x40400000;
    }
  }
  else {
    if (sVar1 != 1) {
      if (sVar1 != 0) {
        return;
      }
      cVar2 = AllCSERelease__7CBattleFv(this);
      if (cVar2 == '\0') {
        return;
      }
      CloseBattleUI__7CBattleFb(this,1);
      MakeTurnOrderTable__7CBattleFfiPiiiPUisibi
                (0x40400000,this,0,0,0,0,0,0,this->cActor);
      *(undefined4 *)(this->pTurnOrderDisp + 0x5c) = 0;
      SetSelectChr__13TurnOrderDispFii
                (this->pTurnOrderDisp,this->nCmd0_target,1);
      if (chr(this,this->cActor)->f4c4 != 0) {
        iVar5 = this + this->cActor * 0x510;
        *(byte *)(iVar5 + 0xb1) = *(byte *)(iVar5 + 0xb1) & 0xf7 | 8;
      }
      if ((this->nComboCnt != 0) &&
         ((chr(this,this->cActor)->bFlagsB & 1) == 0)) {
        MaxComboFunc__7CBattleFi(this,this->cActor);
        AddFriendship__7CBattleFiis
                  (this,chr(this,this->cActor)->nCharId,
                   chr(this,this->cActorB)->nCharId,100);
      }
      this->nStep = 1;
    }
    if (chr(this,this->cActor)->bState == '\x11') {
      chr(this,this->cActor)->bState = 7;
      chr(this,this->cActor)->bState2 = 1;
    }
    iVar5 = this + this->cActor * 0x510;
    *(byte *)(iVar5 + 0xb5) = *(byte *)(iVar5 + 0xb5) & 0xf7;
    if ((((chr(this,this->cActor)->f4c4 == 0) ||
         (-1 < (long)((ulong)chr(this,this->cActor)->bFlagsA1 << 0x3c))) &&
        (chr(this,this->cActor)->bState == '\a')) &&
       ((-1 < (long)((ulong)*(byte *)(chr(this,this->cActor)->pModel +
                                     0x4d0) << 0x3d) &&
        (cVar2 = BtlChrReadyCheck__7CBattleFv(this), cVar2 != '\0')))) {
      chr(this,this->cActor)->bState = 0x26;
      chr(this,this->cActor)->bState2 = 0;
      iVar5 = this + this->cActor * 0x510;
      *(byte *)(iVar5 + 0xb6) = *(byte *)(iVar5 + 0xb6) & 0xef | 0x10;
      iVar5 = this + this->cActor * 0x510;
      uStack_8 = *(undefined4 *)(iVar5 + 0x178);
      uStack_4 = *(undefined4 *)(iVar5 + 0x17c);
      uStack_10 = (undefined4)*(undefined8 *)(iVar5 + 0x170);
      uStack_c = (undefined4)((ulong)*(undefined8 *)(iVar5 + 0x170) >> 0x20);
      PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000005,1,&uStack_10);
      SetCharacterCamera2__9BtlCameraFib
                (this->pCamera,this->cActor,1,1);
      uVar3 = SetBtlMessage__7CBattleFiPv(this,0x7f,0);
      this->nCmd0_target = uVar3;
      if (this->nComboCnt == 0) {
        this->bFlags25 = this->bFlags25 & 0xfb;
      }
      ComboStopOff__Fi(0xffffffffffffffff);
      this->nStep = 2;
    }
  }
  return;
}

/* ---- 0x004958d0  Retail_CBattle_Phase15_Win  (size 0x4270) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0x5', '0x15', '0x16', '0x17', '0x18', '0x19', '0x1a', '0x1b', '0x1c', '0x1d', '0x1e']
 *   nPhase targets: ['0x17', '0x18']
 *   bState targets: ['0x2e'] */
void Retail_CBattle_Phase15_Win(undefined8 this)

{
  ushort uVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  short sVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  long lVar10;
  int this;
  int iVar12;
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  int aiStack_30 [12];
  
  uVar1 = *(ushort *)(*(int *)(*(int *)(iGpffff861c + 4) * 4 + 0x43fca8) + 0x6c);
  /* this = this */
  sVar6 = this->nStep;
  if (sVar6 != 0x1d) {
    if (sVar6 != 0x1c) {
      if (sVar6 == 0x1b) {
        ClearCapture__6SSHSysFv(iGpffff8408);
        this->nStep = 0x1c;
        return;
      }
      if (sVar6 != 0x1a) {
        if (sVar6 != 0x19) {
          if (sVar6 != 0x18) {
            if (sVar6 != 0x17) {
              if (sVar6 != 0x16) {
                if (sVar6 != 0x15) {
                  if (sVar6 != 0x14) {
                    if (sVar6 != 5) {
                      if (sVar6 != 4) {
                        if (sVar6 != 3) {
                          if (sVar6 != 2) {
                            if (sVar6 != 1) {
                              if (sVar6 != 0) {
                                return;
                              }
                              cVar3 = BtlChrReadyCheck__7CBattleFv(this);
                              if (cVar3 == '\0') {
                                return;
                              }
                              if ((long)((ulong)this->bFlags24 << 0x3a) < 0) {
                                End__7CBattleFv(this);
                                return;
                              }
                              if (((*(char *)(iGpffff836c + 399) == '\0') &&
                                  (*(char *)(iGpffff836c + 0x18d) != '\x01')) &&
                                 (*(char *)(iGpffff8374 + 0x529) == '\0')) {
                                SetBtlResultBGMReadEntry__6HNMSndFv(iGpffff8374);
                              }
                              cVar3 = AllCSERelease__7CBattleFv(this);
                              cVar4 = SEEndCheck__6HNMSndFUii(iGpffff8374,0xffffffffffffffff,
                                                      0xffffffffffffffff);
                              if (cVar4 == '\0' || cVar3 == '\0') {
                                return;
                              }
                              iVar12 = 0;
                              for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                                if (((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                                   ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e)
                                    < 0)) {
                                  if (chr(this,iVar7)->f4c0 != -1) {
                                    IOPRelease__6HNMSndFi(iGpffff8374,
                                                    chr(this,iVar7)->f4c0)
                                    ;
                                    chr(this,iVar7)->f4c0 = 0xffffffff;
                                  }
                                  if (chr(this,iVar7)->f4c8 != -1) {
                                    IOPRelease__6HNMSndFi(iGpffff8374,
                                                    chr(this,iVar7)->f4c8)
                                    ;
                                    chr(this,iVar7)->f4c8 = 0xffffffff;
                                  }
                                  if (((ulong)chr(this,iVar7)->bFlagsA2 & 0x7f) >> 5
                                      == 1) {
                                    iVar9 = this + iVar7 * 0x510;
                                    *(byte *)(iVar9 + 0xb2) = *(byte *)(iVar9 + 0xb2) & 0x9f | 0x40;
                                  }
                                  if (((-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2
                                                   << 0x3c)) &&
                                      ((chr(this,iVar7)->bFlagsB & 1) == 0)) &&
                                     (0 < chr(this,iVar7)->nHp)) {
                                    aiStack_30[iVar12] = iVar7;
                                    iVar12 = iVar12 + 1;
                                  }
                                }
                              }
                              if (-1 < this->cDataId) {
                                IOPRelease__6HNMSndFi(iGpffff8374,this->nIopHandle);
                                DataRelease__7CBattleFiib
                                          (this,this->cDataId,0xc,0);
                              }
                              this->nIopHandle = 0xffffffff;
                              this->cDataId = 0xff;
                              if ((this->cActor < '\0') ||
                                 ((chr(this,this->cActor)->bFlagsB & 1)
                                  != 0)) {
                                iVar7 = rand();
                                this->cActor = (char)aiStack_30[iVar7 % iVar12];
                              }
                              this->nStep = 1;
                            }
                            cVar3 = ReleaseCheck__6HNMSndFv(iGpffff8374);
                            if (cVar3 == '\0') {
                              return;
                            }
                            if (-1 < chr(this,this->cActor)->f4e2)
                            {
                              sVar6 = chr(this,this->cActor)->f4e2;
                              iVar7 = rand();
                              uVar5 = DataReadEntry__7CBattleFiii
                                                (this,0xc,0x13,sVar6 * 100 + iVar7 % 10);
                              this->cDataId = uVar5;
                            }
                            if ((*(char *)(iGpffff836c + 399) == '\0') &&
                               (*(char *)(iGpffff836c + 0x18d) != '\x01')) {
                              SetBtlBGMFadeOut__6HNMSndFi(iGpffff8374,500);
                            }
                            if (*(char *)(iGpffff836c + 0x6b0) == '\0') {
                              *(undefined1 *)(iGpffff836c + 0x6b0) = 1;
                            }
                            *(undefined4 *)(this + 0x74) = 0;
                            if ((this->pBtlResult != 0) &&
                               (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                              *(undefined4 *)(this + 0x74) = 1;
                              SetHold__8BtlFaderFi(1);
                              EffectNext__6EffectFv(this->pBtlResult);
                              this->nStep = 2;
                              return;
                            }
                            this->nStep = 3;
                            return;
                          }
                          if ((this->pBtlResult != 0) &&
                             (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                            return;
                          }
                          iVar7 = this->pBtlResult;
                          if (iVar7 != 0) {
                            (**(code **)(*(int *)(iVar7 + 0x14) + 8))(iVar7,1);
                          }
                          this->pBtlResult = 0;
                          SetAlphaMode__8BtlFaderFUl(0x44);
                          Retail_CBattle_ReleaseChrWait(this);
                          this->nStep = 3;
                        }
                        if ((((*(char *)(iGpffff836c + 399) == '\0') &&
                             (*(char *)(iGpffff836c + 0x18d) != '\x01')) &&
                            (*(char *)(iGpffff8374 + 0x529) == '\x02')) &&
                           ((*(char *)(iGpffff8374 + 0x51c) == '\x03' ||
                            (*(char *)(iGpffff8374 + 0x51c) == '\0')))) {
                          SetBtlResultBGMPlay__6HNMSndFv(iGpffff8374);
                        }
                        if (*(char *)(this + 0x4850) != '\0') {
                          return;
                        }
                        if (*(char *)(this + 0x4858) != '\0') {
                          return;
                        }
                        bVar2 = false;
                        for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                          if ((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                              ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0))
                             && (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2 << 0x3c
                                            ))) {
                            if (chr(this,iVar7)->bState == ',') {
                              chr(this,iVar7)->bState2 = 3;
                              iVar12 = this + iVar7 * 0x510;
                              *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xfe | 1;
                              *(undefined4 *)(chr(this,iVar7)->pModel + 0x504) = 0;
                              OTRelease__8BtlModelFv
                                        (chr(this,iVar7)->pModel);
                              ShadowOff__8BtlModelFv
                                        (chr(this,iVar7)->pModel);
                              iVar12 = this + iVar7 * 0x510;
                              *(byte *)(iVar12 + 0xb2) = *(byte *)(iVar12 + 0xb2) & 0xf7 | 8;
                            }
                            else if ((chr(this,iVar7)->bFlagsB & 1) == 0) {
                              if (chr(this,iVar7)->nHp < 1) {
                                if (chr(this,iVar7)->bState != '*') {
                                  bVar2 = true;
                                }
                              }
                              else if (((chr(this,iVar7)->bState != '\a') &&
                                       (chr(this,iVar7)->bState != '\x11')) &&
                                      ((chr(this,iVar7)->bState != '\'' &&
                                       ((chr(this,iVar7)->bState != '(' &&
                                        (-1 < (long)((ulong)chr(this,iVar7)->bFlagsB2
                                                    << 0x3b))))))) {
                                bVar2 = true;
                              }
                            }
                            else if (chr(this,iVar7)->ff2 != -1) {
                              iVar12 = 0;
                              while ((iVar12 < 0x20 &&
                                     (((*(char *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d0) !=
                                        'T' || (((ulong)*(byte *)(this + iVar7 * 0x510 +
                                                                  iVar12 * 0xc + 0x1cd) & 0x3f) >> 3
                                                != 0)) ||
                                      ((*(uint *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d4) &
                                       0x24) == 0))))) {
                                iVar12 = iVar12 + 1;
                              }
                            }
                          }
                        }
                        if ((-1 < this->cDataId) &&
                           (*(char *)(this + this->cDataId * 0x18 + 0x40c5) != '\x03'
                           )) {
                          bVar2 = true;
                        }
                        if (((*(char *)(iGpffff836c + 399) == '\0') &&
                            (*(char *)(iGpffff836c + 0x18d) != '\x01')) &&
                           (*(char *)(iGpffff8374 + 0x529) != '\x04')) {
                          bVar2 = true;
                        }
                        if (*(char *)(iGpffff836c + 0x6b0) != '\x04') {
                          bVar2 = true;
                        }
                        this->flMenuTimer =
                             this->flMenuTimer + this->flDeltaT;
                        if (bVar2) {
                          return;
                        }
                        if (this->flMenuTimer < 0.5) {
                          return;
                        }
                        iVar7 = 0;
                        lVar10 = 0;
                        while (lVar10 < 0xc) {
                          iVar12 = (int)lVar10;
                          if ((((chr(this,iVar12)->bFlagsA & 1) != 0) &&
                              ((long)((ulong)chr(this,iVar12)->bFlagsA << 0x3e) < 0)
                              ) && ((-1 < (long)((ulong)chr(this,iVar12)->bFlagsA2 <<
                                                0x3c) &&
                                    (((chr(this,iVar12)->bFlagsB & 1) == 0 &&
                                     (this->cActor != lVar10)))))) {
                            aiStack_30[iVar7] = iVar12;
                            iVar7 = iVar7 + 1;
                          }
                          lVar10 = (long)(iVar12 + 1);
                        }
                        chr(this,this->cActor)->aPos = 0;
                        chr(this,this->cActor)->fb8 =
                             chr(this,this->cActor)->f2a4 + 3.0;
                        chr(this,this->cActor)->fd4 =
                             0x43340000;
                        CalcPushRange__7CBattleFi(this,this->cActor);
                        auVar13 = _lqc2(*(undefined1 (*) [16])
                                         (this + this->cActor * 0x510 + 0x160));
                        auVar14 = _lqc2(*(undefined1 (*) [16])
                                         (this + this->cActor * 0x510 + 0x3a0));
                        auVar13 = _vadd(auVar13,auVar14);
                        auStack_60 = _sqc2(auVar13);
                        __ct__7FVectorFPC7FVector(auStack_40,auStack_60);
                        iVar12 = this + this->cActor * 0x510;
                        *(int *)(iVar12 + 0x170) = auStack_40._0_4_;
                        *(int *)(iVar12 + 0x174) = auStack_40._4_4_;
                        *(undefined4 *)(iVar12 + 0x178) = uStack_38;
                        *(undefined4 *)(iVar12 + 0x17c) = uStack_34;
                        chr(this,this->cActor)->fc4 = 0;
                        iVar12 = this + this->cActor * 0x510;
                        *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xf7;
                        iVar12 = this + this->cActor * 0x510;
                        *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xdf;
                        iVar12 = this + this->cActor * 0x510;
                        *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xbf;
                        Retail_BtlModel_PrewarmDynamics
                                  (*(undefined4 *)
                                    (this + this->cActor * 0x510 + 0x14c));
                        iVar12 = aiStack_30[0];
                        iVar9 = 0;
                        while ((iVar9 < iVar7 &&
                               (*(short *)(this + aiStack_30[iVar9] * 0x510 + 0x120) != 6))) {
                          iVar9 = iVar9 + 1;
                        }
                        if (iVar9 < iVar7) {
                          aiStack_30[0] = aiStack_30[iVar9];
                          aiStack_30[iVar9] = iVar12;
                        }
                        if (0 < iVar7) {
                          *(float *)(this + aiStack_30[0] * 0x510 + 0x160) =
                               chr(this,this->cActor)->f2a4 + 3.0 +
                               *(float *)(this + aiStack_30[0] * 0x510 + 0x354);
                          *(float *)(this + aiStack_30[0] * 0x510 + 0x168) =
                               -*(float *)(this + aiStack_30[0] * 0x510 + 0x354) - 1.5;
                          *(undefined4 *)(this + aiStack_30[0] * 0x510 + 0x184) = 0x43340000;
                          iVar12 = this + aiStack_30[0] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xf7;
                          iVar12 = this + aiStack_30[0] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xdf;
                          iVar12 = this + aiStack_30[0] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xbf;
                        }
                        if (1 < iVar7) {
                          *(float *)(this + aiStack_30[1] * 0x510 + 0x160) =
                               (-chr(this,this->cActor)->f2a4 - 3.0
                               ) - *(float *)(this + aiStack_30[1] * 0x510 + 0x354);
                          *(float *)(this + aiStack_30[1] * 0x510 + 0x168) =
                               -*(float *)(this + aiStack_30[1] * 0x510 + 0x354) - 1.5;
                          *(undefined4 *)(this + aiStack_30[1] * 0x510 + 0x184) = 0x43340000;
                          iVar12 = this + aiStack_30[1] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xf7;
                          iVar12 = this + aiStack_30[1] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xdf;
                          iVar12 = this + aiStack_30[1] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xbf;
                        }
                        if (2 < iVar7) {
                          *(float *)(this + aiStack_30[2] * 0x510 + 0x160) =
                               ((*(float *)(this + aiStack_30[1] * 0x510 + 0x160) -
                                *(float *)(this + aiStack_30[1] * 0x510 + 0x354)) - 3.0) -
                               *(float *)(this + aiStack_30[2] * 0x510 + 0x354);
                          *(float *)(this + aiStack_30[2] * 0x510 + 0x168) =
                               -*(float *)(this + aiStack_30[2] * 0x510 + 0x354) - 1.5;
                          *(undefined4 *)(this + aiStack_30[2] * 0x510 + 0x184) = 0x43340000;
                          iVar12 = this + aiStack_30[2] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xf7;
                          iVar12 = this + aiStack_30[2] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xdf;
                          iVar12 = this + aiStack_30[2] * 0x510;
                          *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xbf;
                        }
                        if (chr(this,this->cActor)->nCharId == 2) {
                          iVar12 = this + this->cActor * 0x510;
                          *(float *)(iVar12 + 0x160) = *(float *)(iVar12 + 0x160) + 2.0;
                        }
                        for (iVar12 = 0; iVar12 < iVar7; iVar12 = iVar12 + 1) {
                          if (*(short *)(this + aiStack_30[iVar12] * 0x510 + 0x120) == 2) {
                            iVar9 = this + aiStack_30[iVar12] * 0x510;
                            *(float *)(iVar9 + 0x160) = *(float *)(iVar9 + 0x160) + 2.0;
                          }
                        }
                        for (iVar12 = 0; iVar12 < iVar7; iVar12 = iVar12 + 1) {
                          CalcPushRange__7CBattleFi(this,aiStack_30[iVar12]);
                          auVar13 = _lqc2(*(undefined1 (*) [16])
                                           (this + aiStack_30[iVar12] * 0x510 + 0x160));
                          auVar14 = _lqc2(*(undefined1 (*) [16])
                                           (this + aiStack_30[iVar12] * 0x510 + 0x3a0));
                          auVar13 = _vadd(auVar13,auVar14);
                          auStack_70 = _sqc2(auVar13);
                          __ct__7FVectorFPC7FVector(auStack_50,auStack_70);
                          iVar9 = this + aiStack_30[iVar12] * 0x510;
                          *(int *)(iVar9 + 0x170) = auStack_50._0_4_;
                          *(int *)(iVar9 + 0x174) = auStack_50._4_4_;
                          *(undefined4 *)(iVar9 + 0x178) = uStack_48;
                          *(undefined4 *)(iVar9 + 0x17c) = uStack_44;
                          *(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x174) = 0;
                          Retail_BtlModel_PrewarmDynamics
                                    (*(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x14c));
                        }
                        for (iVar12 = 0; iVar12 < 0xc; iVar12 = iVar12 + 1) {
                          if (((((chr(this,iVar12)->bFlagsA & 1) != 0) &&
                               ((long)((ulong)chr(this,iVar12)->bFlagsA << 0x3e) < 0
                               )) && (-1 < (long)((ulong)chr(this,iVar12)->bFlagsA2
                                                 << 0x3c))) &&
                             ((chr(this,iVar12)->bFlagsB & 1) != 0)) {
                            if ((chr(this,iVar12)->bState == '.') &&
                               (chr(this,iVar12)->bState2 == '\x02')) {
                              chr(this,iVar12)->bState2 = 3;
                            }
                            if (chr(this,iVar12)->ff2 != -1) {
                              iVar9 = 0;
                              while ((iVar9 < 0x20 &&
                                     (((*(char *)(this + iVar12 * 0x510 + iVar9 * 0xc + 0x1d0) !=
                                        'T' || (((ulong)*(byte *)(this + iVar12 * 0x510 +
                                                                  iVar9 * 0xc + 0x1cd) & 0x3f) >> 3
                                                != 0)) ||
                                      ((*(uint *)(this + iVar12 * 0x510 + iVar9 * 0xc + 0x1d4) &
                                       0x24) == 0))))) {
                                iVar9 = iVar9 + 1;
                              }
                              if (iVar9 < 0x20) {
                                AddTrophy__7CBattleFiP12MONSTERParam
                                          (this,iVar12,
                                           chr(this,iVar12)->pParam);
                                chr(this,iVar12)->ff2 = 0xff;
                                chr(this,iVar12)->bState = 0x2e;
                                chr(this,iVar12)->bState2 = 3;
                              }
                            }
                          }
                        }
                        MakeResultTrophy__7CBattleFi(this,0);
                        if ((-1 < *(short *)(this + 0x4910)) &&
                           ((*(byte *)(this + 0x4898) & 3) == 0)) {
                          if (((long)(*(char *)(iGpffff836c + 0x27) + 1) <
                               (long)*(char *)(iGpffff836c + 0x18c)) &&
                             ((*(byte *)(iGpffff836c + 0x1a0) & 3) == 0)) {
                            bVar2 = true;
                          }
                          else {
                            bVar2 = false;
                          }
                          if ((bVar2) && (*(char *)(iGpffff836c + 0x754) == '\0')) {
                            *(undefined1 *)(iGpffff836c + 0x754) = 1;
                          }
                        }
                        SetPosAngle__8BtlModelFP7FVectorP7FVector
                                  (*(undefined4 *)
                                    (this + this->cActor * 0x510 + 0x14c),
                                   this + this->cActor * 0x510 + 0x160,
                                   this + this->cActor * 0x510 + 0x180);
                        strcpy(chr(this,this->cActor)->pModel
                                        + 0x52c,0x6e4928);
                        SetBtlMotion__8BtlModelFif
                                  (0x3f800000,
                                   *(undefined4 *)
                                    (this + this->cActor * 0x510 + 0x14c),1);
                        if (chr(this,this->cActor)->f4b0 != 0) {
                          (**(code **)(*(int *)(*(int *)(this + this->cActor * 0x510 +
                                                        0x560) + 0x14) + 0x30))();
                        }
                        chr(this,this->cActor)->f4b0 = 0;
                        if ((long)((ulong)*(byte *)(*(int *)(this + this->cActor *
                                                                      0x510 + 0x14c) + 0x4d1) <<
                                  0x3e) < 0) {
                          OTEntry__8BtlModelFii
                                    (*(undefined4 *)
                                      (this + this->cActor * 0x510 + 0x14c),4,8);
                          ShadowOn__8BtlModelFv
                                    (*(undefined4 *)
                                      (this + this->cActor * 0x510 + 0x14c));
                        }
                        iVar12 = chr(this,this->cActor)->pModel;
                        *(byte *)(iVar12 + 0x4d1) = *(byte *)(iVar12 + 0x4d1) & 0xfd;
                        iVar12 = this + this->cActor * 0x510;
                        *(byte *)(iVar12 + 0xb6) = *(byte *)(iVar12 + 0xb6) & 0xef;
                        for (iVar12 = 0; iVar12 < iVar7; iVar12 = iVar12 + 1) {
                          if (*(int *)(this + aiStack_30[iVar12] * 0x510 + 0x130) < 1) {
                            *(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x130) = 1;
                          }
                          iVar9 = this + aiStack_30[iVar12] * 0x510;
                          *(byte *)(iVar9 + 0xb6) = *(byte *)(iVar9 + 0xb6) & 0xef;
                          *(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x538) = 0;
                          SetPosAngle__8BtlModelFP7FVectorP7FVector
                                    (*(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x14c),
                                     this + aiStack_30[iVar12] * 0x510 + 0x160,
                                     this + aiStack_30[iVar12] * 0x510 + 0x180);
                          strcpy(*(int *)(this + aiStack_30[iVar12] * 0x510 + 0x14c) +
                                          0x52c,0x6e4928);
                          if (*(char *)(this + aiStack_30[iVar12] * 0x510 + 0xb8) == '\a') {
                            SetBtlMotion__8BtlModelFif
                                      (0x3f800000,
                                       *(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x14c),
                                       1);
                          }
                          else if (*(char *)(this + aiStack_30[iVar12] * 0x510 + 0xb8) == '\x11')
                          {
                            *(undefined1 *)(this + aiStack_30[iVar12] * 0x510 + 0xb8) = 7;
                            *(undefined1 *)(this + aiStack_30[iVar12] * 0x510 + 0xb9) = 1;
                          }
                          iVar9 = this + aiStack_30[iVar12] * 0x510;
                          *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                          if (*(int *)(this + aiStack_30[iVar12] * 0x510 + 0x560) != 0) {
                            (**(code **)(*(int *)(*(int *)(this + aiStack_30[iVar12] * 0x510 +
                                                          0x560) + 0x14) + 0x30))();
                          }
                          *(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x560) = 0;
                          if ((long)((ulong)*(byte *)(*(int *)(this + aiStack_30[iVar12] * 0x510 +
                                                              0x14c) + 0x4d1) << 0x3e) < 0) {
                            OTEntry__8BtlModelFii
                                      (*(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x14c),
                                       4,8);
                            ShadowOn__8BtlModelFv
                                      (*(undefined4 *)(this + aiStack_30[iVar12] * 0x510 + 0x14c))
                            ;
                          }
                          iVar9 = *(int *)(this + aiStack_30[iVar12] * 0x510 + 0x14c);
                          *(byte *)(iVar9 + 0x4d1) = *(byte *)(iVar9 + 0x4d1) & 0xfd;
                        }
                        Retail_CBtlPAfter2_ShowAllHitInfo(uGpffff8618);
                        if (*(int *)(this + 0x45cc) != 0) {
                          *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
                        }
                        SetWinCamera1__9BtlCameraFib
                                  (this->pCamera,this->cActor,1
                                  );
                        if (*(int *)(this + 0x74) != 0) {
                          SetHold__8BtlFaderFi(0);
                          SetAlphaMode__8BtlFaderFUl(0x44);
                          sVar6 = GetFaderMode__8BtlFaderFv();
                          if (sVar6 != 0) {
                            SetMode2__8BtlFaderFsf(0x3f800000,2);
                          }
                        }
                        this->nCmd0_target = 0;
                        this->flMenuTimer = 0;
                        this->nStep = 4;
                        return;
                      }
                      if (*(int *)(this->pParamDisp + 0x38) == 2) {
                        ParamClose__9ParamDispFv(this->pParamDisp);
                      }
                      if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
                        TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
                      }
                      if ((*(char *)(iGpffff836c + 399) == '\0') &&
                         (*(char *)(iGpffff836c + 0x18d) != '\x01')) {
                        SetBtlResultBGMIOPEntry__6HNMSndFv(iGpffff8374);
                      }
                      this->nCmd0_target = 0;
                      if (-1 < *(short *)(this + 0x4910)) {
                        this->nCmd0_target = 10;
                      }
                      this->flMenuTimer = 0;
                      this->nCmd1 = 0;
                      this->nCmdKind = 0;
                      uVar8 = SetBtlMessage__7CBattleFiPv(this,0x69,0);
                      *(undefined4 *)(this + 0x80) = uVar8;
                      this->nStep = 5;
                    }
                    if ((this->pParamDisp != 0) &&
                       (*(int *)(this->pParamDisp + 0x38) == 0)) {
                      Destruct__9ParamDispFv(this->pParamDisp);
                      this->pParamDisp = 0;
                    }
                    if (*(int *)(this + 0x45cc) != 0) {
                      Destruct__9ComboFormFv(*(undefined4 *)(this + 0x45cc));
                      *(undefined4 *)(this + 0x45cc) = 0;
                    }
                    if ((this->pTurnOrderDisp != 0) &&
                       (*(int *)(this->pTurnOrderDisp + 0x38) == 0)) {
                      Destruct__13TurnOrderDispFv(this->pTurnOrderDisp);
                      this->pTurnOrderDisp = 0;
                    }
                    this->flMenuTimer =
                         this->flMenuTimer + this->flDeltaT;
                    for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                      if (((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                           ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0)) &&
                          (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2 << 0x3c))) &&
                         ((chr(this,iVar7)->bFlagsB & 1) == 0)) {
                        if ((chr(this,iVar7)->bState == '\'') ||
                           (chr(this,iVar7)->bState == '(')) {
                          for (iVar12 = 0; iVar12 < 0x20; iVar12 = iVar12 + 1) {
                            if (((*(char *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d0) == 'T')
                                && (((ulong)*(byte *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1cd)
                                    & 0x3f) >> 3 == 0)) &&
                               ((*(uint *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d4) & 0x20) !=
                                0)) {
                              *(undefined1 *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d0) = 0;
                            }
                          }
                        }
                        else if ((((chr(this,iVar7)->bState < '\x19') ||
                                  ('+' < chr(this,iVar7)->bState)) ||
                                 (chr(this,iVar7)->nHp < 1)) &&
                                ((long)((ulong)chr(this,iVar7)->bFlagsA1 << 0x3e) < 0
                                )) {
                          if (chr(this,iVar7)->nCharId == 0) {
                            if ((*(char *)(this + 0x4850) == '\0') &&
                               (-1 < (long)((ulong)this->bFlags24 << 0x38))) {
                              if (chr(this,iVar7)->nHp < 1) {
                                SetAutoFusionOff__7CBattleFii(this,iVar7,2);
                              }
                              else {
                                SetAutoFusionOff__7CBattleFii(this,iVar7,1);
                              }
                              *(uint *)(this->pCamera + 0x140) =
                                   *(uint *)(this->pCamera + 0x140) |
                                   3 << (((int)*(char *)(this + 0x4853) & 0xfU) << 1);
                            }
                          }
                          else if (((chr(this,iVar7)->nCharId == 7) &&
                                   (*(char *)(this + 0x4858) == '\0')) &&
                                  (-1 < (long)((ulong)this->bFlags24 << 0x38))) {
                            if (chr(this,iVar7)->nHp < 1) {
                              SetAutoFusionOff__7CBattleFii(this,iVar7,2);
                            }
                            else {
                              SetAutoFusionOff__7CBattleFii(this,iVar7,1);
                            }
                            *(uint *)(this->pCamera + 0x140) =
                                 *(uint *)(this->pCamera + 0x140) |
                                 3 << (((int)*(char *)(this + 0x485b) & 0xfU) << 1);
                          }
                        }
                      }
                    }
                    bVar2 = this->flMenuTimer < 0.2;
                    if (chr(this,this->cActor)->pModel == 0) {
                      bVar2 = true;
                    }
                    else if (*(short *)(chr(this,this->cActor)->pModel
                                       + 0x510) != 1) {
                      bVar2 = true;
                    }
                    if ((long)((ulong)chr(this,this->cActor)->bFlagsA1 <<
                              0x3e) < 0) {
                      bVar2 = true;
                    }
                    if ((chr(this,this->cActor)->nCharId == 0) &&
                       (*(char *)(this + 0x4850) != '\0')) {
                      bVar2 = true;
                    }
                    if ((chr(this,this->cActor)->nCharId == 7) &&
                       (*(char *)(this + 0x4858) != '\0')) {
                      bVar2 = true;
                    }
                    if ((this->nCmd1 & 1) != 0) {
                      bVar2 = true;
                    }
                    if (!bVar2) {
                      SetNextBtlMotion__8BtlModelFif
                                (0x3f800000,
                                 chr(this,this->cActor)->pModel,
                                 0x33);
                      if (-1 < this->cDataId) {
                        PlaySE__6HNMSndFUibP7FVector(iGpffff8374,0xffffffff90000000,1,0);
                      }
                      this->nCmd1 = this->nCmd1 | 1;
                    }
                    lVar10 = 0;
                    while (lVar10 < 0xc) {
                      iVar7 = (int)lVar10;
                      if (((((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                             ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0))
                            && (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2 << 0x3c)
                               )) && (((chr(this,iVar7)->bFlagsB & 1) == 0 &&
                                      (this->cActor != lVar10)))) &&
                          ((chr(this,iVar7)->nCharId != 0 ||
                           (*(char *)(this + 0x4850) == '\0')))) &&
                         (((chr(this,iVar7)->nCharId != 7 ||
                           (*(char *)(this + 0x4858) == '\0')) &&
                          (*(short *)(chr(this,iVar7)->pModel + 0x510) == 1)))) {
                        SetNextBtlMotion__8BtlModelFif
                                  (0x3f800000,chr(this,iVar7)->pModel,0x33);
                      }
                      lVar10 = (long)(iVar7 + 1);
                    }
                    iVar7 = this->nCmd0_target;
                    if (iVar7 == 0xb) {
                      this->flMenuTimer2 =
                           this->flMenuTimer2 + this->flDeltaT;
                      if (((uVar1 & 0x2000) == 0) && (this->flMenuTimer2 < 4.0)) {
                        return;
                      }
                      if (-1 < this->cDataId) {
                        IOPRelease__6HNMSndFi(iGpffff8374,this->nIopHandle);
                        DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
                      }
                      this->nIopHandle = 0xffffffff;
                      this->cDataId = 0xff;
                      iVar12 = 0;
                      for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                        if ((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                            ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0))
                           && ((chr(this,iVar7)->bFlagsB & 1) == 0)) {
                          aiStack_30[iVar12] = iVar7;
                          iVar12 = iVar12 + 1;
                        }
                      }
                      for (iVar7 = 0; iVar9 = iVar7, iVar7 < iVar12; iVar7 = iVar7 + 1) {
                        while (iVar9 = iVar9 + 1, iVar9 < iVar12) {
                          AddFriendship__7CBattleFiis
                                    (this,*(undefined2 *)
                                              (this + aiStack_30[iVar7] * 0x510 + 0x120),
                                     *(undefined2 *)(this + aiStack_30[iVar9] * 0x510 + 0x120),10)
                          ;
                        }
                      }
                      if (((long)(*(char *)(iGpffff836c + 0x27) + 1) <
                           (long)*(char *)(iGpffff836c + 0x18c)) &&
                         ((*(byte *)(iGpffff836c + 0x1a0) & 3) == 0)) {
                        bVar2 = true;
                      }
                      else {
                        bVar2 = false;
                      }
                      if (bVar2) {
                        this->nPhase = 0x18;
                        this->nStep = 0;
                        this->bFlags25 = this->bFlags25 & 0xfc;
                        this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
                        return;
                      }
                      this->nPhase = 0x17;
                      this->nStep = 0;
                      if ((*(byte *)(this + 0x4898) & 3) == 0) {
                        this->bFlags25 = this->bFlags25 & 0xfc;
                      }
                      else {
                        this->bFlags25 = this->bFlags25 & 0xfc | 1;
                      }
                      this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
                      if (-1 < (long)((ulong)this->bFlags24 << 0x3a)) {
                        return;
                      }
                      if (*(int *)(this + 0x98) == 0) {
                        return;
                      }
                      (**(code **)(this + 0x98))(4,0,0,*(undefined4 *)(this + 0x94));
                      return;
                    }
                    if (iVar7 != 10) {
                      if (iVar7 != 1) {
                        if (iVar7 != 0) {
                          return;
                        }
                        iVar7 = 0;
                        if (((this->nCmd1 & 1) != 0) &&
                           (*(short *)(chr(this,this->cActor)->pModel +
                                      0x510) == 2)) {
                          iVar7 = 1;
                        }
                        if ((uVar1 & 0x2000) != 0) {
                          iVar7 = 2;
                          this->nCmdKind = 1;
                        }
                        if (iVar7 == 0) {
                          return;
                        }
                        this->nCmd0_target = 1;
                        this->flMenuTimer2 = 0;
                        lVar10 = __nw__FUi(0x49c);
                        if (lVar10 != 0) {
                          __ct__8BtlBonusFv();
                        }
                        if (this->nCmdKind == 0) {
                          return;
                        }
                        iGpffff8378->flDeltaT = iGpffff8378->flDeltaT & 0xfb | 4;
                        return;
                      }
                      if ((iGpffff8378 != 0) && (*(short *)(iGpffff8378 + 0x3c) != 4)) {
                        return;
                      }
                      if (-1 < this->cDataId) {
                        IOPRelease__6HNMSndFi(iGpffff8374,this->nIopHandle);
                        DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
                      }
                      this->nIopHandle = 0xffffffff;
                      this->cDataId = 0xff;
                      iVar12 = 0;
                      for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                        if ((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                            ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0))
                           && ((chr(this,iVar7)->bFlagsB & 1) == 0)) {
                          aiStack_30[iVar12] = iVar7;
                          iVar12 = iVar12 + 1;
                        }
                      }
                      for (iVar7 = 0; iVar9 = iVar7, iVar7 < iVar12; iVar7 = iVar7 + 1) {
                        while (iVar9 = iVar9 + 1, iVar9 < iVar12) {
                          AddFriendship__7CBattleFiis
                                    (this,*(undefined2 *)
                                              (this + aiStack_30[iVar7] * 0x510 + 0x120),
                                     *(undefined2 *)(this + aiStack_30[iVar9] * 0x510 + 0x120),10)
                          ;
                        }
                      }
                      this->nPhase = 0x17;
                      this->nStep = 0;
                      this->bFlags25 = this->bFlags25 & 0xfc;
                      this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
                      if (-1 < (long)((ulong)this->bFlags24 << 0x3a)) {
                        return;
                      }
                      if (*(int *)(this + 0x98) == 0) {
                        return;
                      }
                      (**(code **)(this + 0x98))(4,0,0,*(undefined4 *)(this + 0x94));
                      return;
                    }
                    iVar7 = 0;
                    if (((this->nCmd1 & 1) != 0) &&
                       (*(short *)(chr(this,this->cActor)->pModel +
                                  0x510) == 2)) {
                      iVar7 = 1;
                    }
                    if ((uVar1 & 0x2000) != 0) {
                      iVar7 = 2;
                      this->nCmdKind = 1;
                    }
                    if (iVar7 == 0) {
                      return;
                    }
                    this->nCmd0_target = 0xb;
                    this->flMenuTimer2 = 0;
                    if ((*(byte *)(this + 0x4898) & 3) != 0) {
                      lVar10 = __nw__FUi(0x5c);
                      if (lVar10 == 0) {
                        return;
                      }
                      __ct__18BtlResultRetailFxBFv();
                      return;
                    }
                    lVar10 = __nw__FUi(0x5c);
                    if (lVar10 == 0) {
                      return;
                    }
                    __ct__18BtlResultRetailFxAFv();
                    return;
                  }
                  cVar3 = BtlChrReadyCheck__7CBattleFv(this);
                  if (cVar3 == '\0') {
                    return;
                  }
                  cVar3 = AllCSERelease__7CBattleFv(this);
                  cVar4 = SEEndCheck__6HNMSndFUii(iGpffff8374,0xffffffffffffffff,0xffffffffffffffff);
                  if (cVar4 == '\0' || cVar3 == '\0') {
                    return;
                  }
                  for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                    if (((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                       ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0)) {
                      if (chr(this,iVar7)->f4c0 != -1) {
                        IOPRelease__6HNMSndFi(iGpffff8374,chr(this,iVar7)->f4c0)
                        ;
                        chr(this,iVar7)->f4c0 = 0xffffffff;
                      }
                      if (chr(this,iVar7)->f4c8 != -1) {
                        IOPRelease__6HNMSndFi(iGpffff8374,chr(this,iVar7)->f4c8)
                        ;
                        chr(this,iVar7)->f4c8 = 0xffffffff;
                      }
                    }
                  }
                  if (-1 < this->cDataId) {
                    IOPRelease__6HNMSndFi(iGpffff8374,this->nIopHandle);
                    DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
                  }
                  this->nIopHandle = 0xffffffff;
                  this->cDataId = 0xff;
                  this->nStep = 0x15;
                }
                cVar3 = ReleaseCheck__6HNMSndFv(iGpffff8374);
                if (cVar3 == '\0') {
                  return;
                }
                this->nStep = 0x16;
              }
              if (*(char *)(this + 0x4850) != '\0') {
                return;
              }
              if (*(char *)(this + 0x4858) != '\0') {
                return;
              }
              bVar2 = false;
              for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
                if ((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
                    ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0)) &&
                   (-1 < (long)((ulong)chr(this,iVar7)->bFlagsA2 << 0x3c))) {
                  if (chr(this,iVar7)->bState == ',') {
                    chr(this,iVar7)->bState2 = 3;
                    iVar12 = this + iVar7 * 0x510;
                    *(byte *)(iVar12 + 0xb5) = *(byte *)(iVar12 + 0xb5) & 0xfe | 1;
                    *(undefined4 *)(chr(this,iVar7)->pModel + 0x504) = 0;
                    OTRelease__8BtlModelFv(chr(this,iVar7)->pModel);
                    ShadowOff__8BtlModelFv(chr(this,iVar7)->pModel);
                    iVar12 = this + iVar7 * 0x510;
                    *(byte *)(iVar12 + 0xb2) = *(byte *)(iVar12 + 0xb2) & 0xf7 | 8;
                  }
                  else if ((chr(this,iVar7)->bFlagsB & 1) == 0) {
                    if (chr(this,iVar7)->nHp < 1) {
                      if (chr(this,iVar7)->bState != '*') {
                        bVar2 = true;
                      }
                    }
                    else if (((chr(this,iVar7)->bState != '\a') &&
                             (chr(this,iVar7)->bState != '\x11')) &&
                            ((chr(this,iVar7)->bState != '\'' &&
                             (chr(this,iVar7)->bState != '(')))) {
                      bVar2 = true;
                    }
                  }
                  else if (chr(this,iVar7)->ff2 != -1) {
                    iVar12 = 0;
                    while ((iVar12 < 0x20 &&
                           (((*(char *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d0) != 'T' ||
                             (((ulong)*(byte *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1cd) &
                              0x3f) >> 3 != 0)) ||
                            ((*(uint *)(this + iVar7 * 0x510 + iVar12 * 0xc + 0x1d4) & 0x24) == 0)
                            )))) {
                      iVar12 = iVar12 + 1;
                    }
                  }
                }
              }
              if (bVar2) {
                return;
              }
              lVar10 = Retail_CBattle_FindLastBossPart(this,1);
              if (-1 < lVar10) {
                AddTrophy__7CBattleFiP12MONSTERParam
                          (this,lVar10,*(undefined4 *)(this + (int)lVar10 * 0x510 + 0x150));
              }
              lVar10 = Retail_CBattle_FindLastBossPart(this,2);
              if (-1 < lVar10) {
                AddTrophy__7CBattleFiP12MONSTERParam
                          (this,lVar10,*(undefined4 *)(this + (int)lVar10 * 0x510 + 0x150));
              }
              lVar10 = Retail_CBattle_FindLastBossPart(this,3);
              if (-1 < lVar10) {
                AddTrophy__7CBattleFiP12MONSTERParam
                          (this,lVar10,*(undefined4 *)(this + (int)lVar10 * 0x510 + 0x150));
              }
              MakeResultTrophy__7CBattleFi(this,0);
              this->nCmd0_target = 0;
              this->flMenuTimer = 0;
              if ((this->pBtlResult != 0) &&
                 (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                EffectNext__6EffectFv(this->pBtlResult);
                this->nStep = 0x17;
                return;
              }
              this->nStep = 0x18;
              return;
            }
            if ((this->pBtlResult != 0) &&
               (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
              return;
            }
            iVar7 = this->pBtlResult;
            if (iVar7 != 0) {
              (**(code **)(*(int *)(iVar7 + 0x14) + 8))(iVar7,1);
            }
            this->pBtlResult = 0;
            Retail_CBattle_ReleaseChrWait(this);
            this->nStep = 0x18;
          }
          if (*(int *)(this->pParamDisp + 0x38) == 2) {
            ParamClose__9ParamDispFv(this->pParamDisp);
          }
          if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
            TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
          }
          Retail_CBtlPAfter2_ShowAllHitInfo(uGpffff8618);
          this->nCmd0_target = 0;
          this->flMenuTimer = 0;
          this->nCmd1 = 0;
          this->nCmdKind = 0;
          this->nStep = 0x19;
        }
        this->flMenuTimer = this->flMenuTimer + this->flDeltaT;
        iVar12 = 0;
        for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
          if ((((chr(this,iVar7)->bFlagsA & 1) != 0) &&
              ((long)((ulong)chr(this,iVar7)->bFlagsA << 0x3e) < 0)) &&
             ((chr(this,iVar7)->bFlagsB & 1) == 0)) {
            aiStack_30[iVar12] = iVar7;
            iVar12 = iVar12 + 1;
          }
        }
        for (iVar7 = 0; iVar9 = iVar7, iVar7 < iVar12; iVar7 = iVar7 + 1) {
          while (iVar9 = iVar9 + 1, iVar9 < iVar12) {
            AddFriendship__7CBattleFiis
                      (this,*(undefined2 *)(this + aiStack_30[iVar7] * 0x510 + 0x120),
                       *(undefined2 *)(this + aiStack_30[iVar9] * 0x510 + 0x120),10);
          }
        }
        this->nStep = 0x1a;
        this->bFlags25 = this->bFlags25 & 0xfc;
        this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
      }
      if (-1 < (long)((ulong)this->bFlags24 << 0x3e)) {
        this->nStep = 0x1d;
        return;
      }
      cVar3 = IsCapture__6SSHSysFv(iGpffff8408);
      if (cVar3 == '\0') {
        return;
      }
      this->nStep = 0x1b;
      return;
    }
    if (*(int *)(iGpffff8408 + 0xa8) != 0) {
      return;
    }
    this->bFlags24 = this->bFlags24 & 0xfd;
    this->nStep = 0x1d;
  }
  if (*(int *)(iGpffff8408 + 0xa8) == 0) {
    iVar7 = 0;
    while ((iVar7 < 0x28 &&
           ((*(char *)(this + iVar7 * 0x18 + 0x40c5) == '\0' ||
            (*(char *)(this + iVar7 * 0x18 + 0x40c5) == '\x03'))))) {
      iVar7 = iVar7 + 1;
    }
    if (0x27 < iVar7) {
      this->nStep = 0x1e;
    }
  }
  else {
    ClearCapture__6SSHSysFv(iGpffff8408);
    this->bFlags24 = this->bFlags24 & 0xfd | 2;
    this->nStep = 0x1b;
  }
  return;
}

/* ---- 0x00499b40  Retail_CBattle_Phase16_Lose  (size 0x3190) ----
 *   nStep values: ['0x0', '0x1', '0x2', '0x3', '0x4', '0xa', '0xb', '0xc']
 *   nPhase targets: ['0x17']
 *   bState targets: ['0x3', '0x7', '0x2e'] */
void Retail_CBattle_Phase16_Lose(undefined8 this)

{
  short sVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  long lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int this;
  float fVar12;
  float fVar13;
  float fVar14;
  int aiStack_30 [4];
  int iStack_20;
  int iStack_1c;
  
  /* this = this */
  sVar1 = this->nStep;
  if (sVar1 != 0xc) {
    if (sVar1 != 0xb) {
      if (sVar1 != 10) {
        if (sVar1 != 4) {
          if (sVar1 != 3) {
            if (sVar1 != 2) {
              if (sVar1 != 1) {
                if (sVar1 != 0) {
                  return;
                }
                cVar3 = BtlChrReadyCheck__7CBattleFv(this);
                if (cVar3 == '\0') {
                  return;
                }
                if ((long)((ulong)this->bFlags24 << 0x3a) < 0) {
                  End__7CBattleFv(this);
                  return;
                }
                cVar3 = AllCSERelease__7CBattleFv(this);
                cVar4 = SEEndCheck__6HNMSndFUii(uGpffff8374,0xffffffffffffffff,0xffffffffffffffff);
                if (cVar4 == '\0' || cVar3 == '\0') {
                  return;
                }
                for (iVar8 = 0; iVar8 < 0xc; iVar8 = iVar8 + 1) {
                  if (((chr(this,iVar8)->bFlagsA & 1) != 0) &&
                     ((long)((ulong)chr(this,iVar8)->bFlagsA << 0x3e) < 0)) {
                    if (chr(this,iVar8)->f4c0 != -1) {
                      IOPRelease__6HNMSndFi(uGpffff8374,chr(this,iVar8)->f4c0);
                      chr(this,iVar8)->f4c0 = 0xffffffff;
                    }
                    if (chr(this,iVar8)->f4c8 != -1) {
                      IOPRelease__6HNMSndFi(uGpffff8374,chr(this,iVar8)->f4c8);
                      chr(this,iVar8)->f4c8 = 0xffffffff;
                    }
                    if (((ulong)chr(this,iVar8)->bFlagsA2 & 0x7f) >> 5 == 1) {
                      iVar9 = this + iVar8 * 0x510;
                      *(byte *)(iVar9 + 0xb2) = *(byte *)(iVar9 + 0xb2) & 0x9f | 0x40;
                    }
                  }
                }
                if (-1 < this->cDataId) {
                  IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
                  DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
                }
                this->nIopHandle = 0xffffffff;
                this->cDataId = 0xff;
                if (*(char *)(iGpffff836c + 0x18d) != '\x01') {
                  SetBtlBGMFadeOut__6HNMSndFi(uGpffff8374,1000);
                }
                if ((-1 < *(short *)(this + 0x4910)) && (*(char *)(iGpffff836c + 0x6b0) == '\0'))
                {
                  *(undefined1 *)(iGpffff836c + 0x6b0) = 1;
                }
                this->nStep = 1;
              }
              if (*(char *)(this + 0x4850) != '\0') {
                return;
              }
              if (*(char *)(this + 0x4858) != '\0') {
                return;
              }
              bVar2 = false;
              for (iVar8 = 0; iVar8 < 0xc; iVar8 = iVar8 + 1) {
                if ((((chr(this,iVar8)->bFlagsA & 1) != 0) &&
                    ((long)((ulong)chr(this,iVar8)->bFlagsA << 0x3e) < 0)) &&
                   (-1 < (long)((ulong)chr(this,iVar8)->bFlagsA2 << 0x3c))) {
                  if (chr(this,iVar8)->bState == ',') {
                    chr(this,iVar8)->bState2 = 3;
                    iVar9 = this + iVar8 * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xfe | 1;
                    *(undefined4 *)(chr(this,iVar8)->pModel + 0x504) = 0;
                    OTRelease__8BtlModelFv(chr(this,iVar8)->pModel);
                    ShadowOff__8BtlModelFv(chr(this,iVar8)->pModel);
                    iVar9 = this + iVar8 * 0x510;
                    *(byte *)(iVar9 + 0xb2) = *(byte *)(iVar9 + 0xb2) & 0xf7 | 8;
                  }
                  else if ((chr(this,iVar8)->bFlagsB & 1) == 0) {
                    if (((chr(this,iVar8)->bState != '*') &&
                        (chr(this,iVar8)->bState != '\'')) &&
                       (chr(this,iVar8)->bState != '(')) {
                      iVar9 = 0;
                      while ((iVar9 < 0x20 &&
                             (((*(char *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1d0) != 'T' ||
                               (((ulong)*(byte *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1cd) &
                                0x3f) >> 3 != 0)) ||
                              ((*(uint *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1d4) & 0x24) == 0
                              ))))) {
                        iVar9 = iVar9 + 1;
                      }
                      if (0x1f < iVar9) {
                        bVar2 = true;
                      }
                    }
                  }
                  else if (chr(this,iVar8)->nHp < 1) {
                    if (chr(this,iVar8)->ff2 != -1) {
                      bVar2 = true;
                    }
                  }
                  else if (((chr(this,iVar8)->bState != '\a') &&
                           (chr(this,iVar8)->bState != '\x11')) &&
                          ((chr(this,iVar8)->bState != '\'' &&
                           (chr(this,iVar8)->bState != '(')))) {
                    bVar2 = true;
                  }
                }
              }
              if ((-1 < *(short *)(this + 0x4910)) && (*(char *)(iGpffff836c + 0x6b0) != '\x04'))
              {
                bVar2 = true;
              }
              this->flMenuTimer = this->flMenuTimer + this->flDeltaT;
              if (bVar2) {
                return;
              }
              if (this->flMenuTimer < 0.5) {
                return;
              }
              iVar8 = 0;
              for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
                if ((((chr(this,iVar9)->bFlagsA & 1) != 0) &&
                    ((long)((ulong)chr(this,iVar9)->bFlagsA << 0x3e) < 0)) &&
                   ((-1 < (long)((ulong)chr(this,iVar9)->bFlagsA2 << 0x3c) &&
                    ((chr(this,iVar9)->bFlagsB & 1) == 0)))) {
                  if ((long)((ulong)*(byte *)(chr(this,iVar9)->pModel + 0x4d1) <<
                            0x3e) < 0) {
                    OTEntry__8BtlModelFii(chr(this,iVar9)->pModel,4,8);
                    ShadowOn__8BtlModelFv(chr(this,iVar9)->pModel);
                  }
                  iVar7 = chr(this,iVar9)->pModel;
                  *(byte *)(iVar7 + 0x4d1) = *(byte *)(iVar7 + 0x4d1) & 0xfd;
                  aiStack_30[iVar8] = iVar9;
                  iVar8 = iVar8 + 1;
                }
              }
              if (iVar8 != 0) {
                for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
                  if (((((chr(this,iVar9)->bFlagsA & 1) != 0) &&
                       ((long)((ulong)chr(this,iVar9)->bFlagsA << 0x3e) < 0)) &&
                      (-1 < (long)((ulong)chr(this,iVar9)->bFlagsA2 << 0x3c))) &&
                     ((chr(this,iVar9)->bFlagsB & 1) != 0)) {
                    chr(this,iVar9)->bState = 0x2e;
                    chr(this,iVar9)->bState2 = 3;
                    iVar7 = this + iVar9 * 0x510;
                    *(byte *)(iVar7 + 0xb5) = *(byte *)(iVar7 + 0xb5) & 0xfe | 1;
                    iVar7 = this + iVar9 * 0x510;
                    *(byte *)(iVar7 + 0xb2) = *(byte *)(iVar7 + 0xb2) & 0x9f | 0x20;
                    OTRelease__8BtlModelFv(chr(this,iVar9)->pModel);
                    ShadowOff__8BtlModelFv(chr(this,iVar9)->pModel);
                    iVar7 = chr(this,iVar9)->pModel;
                    *(byte *)(iVar7 + 0x4d1) = *(byte *)(iVar7 + 0x4d1) & 0xfd;
                  }
                }
                if (iVar8 == 2) {
                  fVar13 = *(float *)(this + aiStack_30[0] * 0x510 + 0x354);
                  if (fVar13 < *(float *)(this + aiStack_30[1] * 0x510 + 0x354)) {
                    fVar13 = *(float *)(this + aiStack_30[1] * 0x510 + 0x354);
                  }
                  *(float *)(this + aiStack_30[0] * 0x510 + 0x160) = -6.0 - fVar13;
                  *(undefined4 *)(this + aiStack_30[0] * 0x510 + 0x168) = 0;
                  *(float *)(this + aiStack_30[1] * 0x510 + 0x160) = fVar13 + 6.0;
                  *(undefined4 *)(this + aiStack_30[1] * 0x510 + 0x168) = 0;
                }
                else if (iVar8 == 1) {
                  iVar9 = this + aiStack_30[0] * 0x510;
                  *(undefined4 *)(iVar9 + 0x160) = 0;
                  *(undefined4 *)(iVar9 + 0x164) = 0;
                  *(undefined4 *)(iVar9 + 0x168) = 0;
                  *(undefined4 *)(iVar9 + 0x16c) = 0x3f800000;
                }
                else {
                  fVar13 = 0.0;
                  for (iVar9 = 0; iVar9 < iVar8; iVar9 = iVar9 + 1) {
                    if (fVar13 < *(float *)(this + aiStack_30[iVar9] * 0x510 + 0x354)) {
                      fVar13 = *(float *)(this + aiStack_30[iVar9] * 0x510 + 0x354);
                    }
                  }
                  fVar14 = ((fVar13 * 2.0 + 12.0) * (float)iVar8) / 6.2831855;
                  fVar13 = fVar13 * 2.0 + 12.0;
                  if (fVar13 <= fVar14) {
                    fVar13 = fVar14;
                  }
                  fVar14 = 0.0;
                  for (iVar9 = 0; iVar9 < iVar8; iVar9 = iVar9 + 1) {
                    fVar12 = (float)sinf(fVar14);
                    *(float *)(this + aiStack_30[iVar9] * 0x510 + 0x160) = fVar13 * -fVar12;
                    fVar12 = (float)cosf(fVar14);
                    *(float *)(this + aiStack_30[iVar9] * 0x510 + 0x168) = fVar13 * fVar12;
                    fVar14 = fVar14 + 6.2831855 / (float)iVar8;
                    if (3.1415927 <= fVar14) {
                      fVar14 = fVar14 - 6.2831855;
                    }
                  }
                }
                for (iVar9 = 0; iVar9 < iVar8; iVar9 = iVar9 + 1) {
                  SetPos__8BtlModelFP7FVector
                            (*(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x14c),
                             this + aiStack_30[iVar9] * 0x510 + 0x160);
                  uVar10 = 0;
                  for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
                    if ((*(char *)(this + aiStack_30[iVar9] * 0x510 + iVar7 * 0xc + 0x1d0) == 'T')
                       && (((ulong)*(byte *)(this + aiStack_30[iVar9] * 0x510 + iVar7 * 0xc +
                                            0x1cd) & 0x3f) >> 3 == 0)) {
                      if ((*(uint *)(this + aiStack_30[iVar9] * 0x510 + iVar7 * 0xc + 0x1d4) &
                          0x20) != 0) {
                        uVar10 = uVar10 | 2;
                      }
                      if ((*(uint *)(this + aiStack_30[iVar9] * 0x510 + iVar7 * 0xc + 0x1d4) & 4)
                          != 0) {
                        uVar10 = uVar10 | 1;
                      }
                    }
                  }
                  if ((uVar10 == 1) &&
                     (((ulong)*(byte *)(this + aiStack_30[iVar9] * 0x510 + 0xb4) & 7) >> 1 == 0))
                  {
                    *(undefined1 *)(this + aiStack_30[iVar9] * 0x510 + 0xb8) = 0x26;
                    *(undefined1 *)(this + aiStack_30[iVar9] * 0x510 + 0xb9) = 0;
                  }
                }
                this->flMenuTimer = 0;
                Retail_CBtlPAfter2_ShowAllHitInfo(uGpffff8618);
                if (*(int *)(this + 0x45cc) != 0) {
                  *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
                }
                SetLoseCamera1__9BtlCameraFb(this->pCamera,1);
                MakeResultTrophy__7CBattleFi(this,1);
                if ((this->pBtlResult != 0) &&
                   (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                  EffectNext__6EffectFv(this->pBtlResult);
                  this->nStep = 2;
                  return;
                }
                this->nStep = 3;
                return;
              }
              iVar8 = 0;
              for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
                if ((((chr(this,iVar9)->bFlagsA & 1) != 0) &&
                    ((long)((ulong)chr(this,iVar9)->bFlagsA << 0x3e) < 0)) &&
                   (-1 < (long)((ulong)chr(this,iVar9)->bFlagsA2 << 0x3c))) {
                  if ((chr(this,iVar9)->bFlagsB & 1) == 0) {
                    chr(this,iVar9)->bState = 3;
                    iVar7 = this + iVar9 * 0x510;
                    *(byte *)(iVar7 + 0xb5) = *(byte *)(iVar7 + 0xb5) & 0xfe | 1;
                    OTRelease__8BtlModelFv(chr(this,iVar9)->pModel);
                    ShadowOff__8BtlModelFv(chr(this,iVar9)->pModel);
                    iVar7 = chr(this,iVar9)->pModel;
                    *(byte *)(iVar7 + 0x4d1) = *(byte *)(iVar7 + 0x4d1) & 0xfd;
                  }
                  else if ((chr(this,iVar9)->bState == '.') &&
                          (chr(this,iVar9)->bState2 == '\x02')) {
                    chr(this,iVar9)->bState2 = 3;
                  }
                  else if (chr(this,iVar9)->ff2 != -1) {
                    chr(this,iVar9)->bState = 7;
                    chr(this,iVar9)->bState2 = 0;
                    aiStack_30[iVar8] = iVar9;
                    iVar8 = iVar8 + 1;
                  }
                }
              }
              iVar9 = 0;
              do {
                if (iVar8 <= iVar9) {
LAB_0049b160:
                  this->cActor = (char)aiStack_30[0];
                  *(undefined4 *)(this + aiStack_30[0] * 0x510 + 0x160) = 0;
                  *(float *)(this + aiStack_30[0] * 0x510 + 0x168) =
                       *(float *)(this + aiStack_30[0] * 0x510 + 0x354) + 3.0;
                  *(undefined4 *)(this + aiStack_30[0] * 0x510 + 0x184) = 0x43340000;
                  iVar9 = this + aiStack_30[0] * 0x510;
                  *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                  iVar9 = this + aiStack_30[0] * 0x510;
                  *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                  iVar9 = this + aiStack_30[0] * 0x510;
                  *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  this->cDataId = 0xff;
                  if (-1 < *(short *)(this + aiStack_30[0] * 0x510 + 0x594)) {
                    uVar5 = DataReadEntry__7CBattleFiii
                                      (this,0xc,0x12,
                                       *(undefined2 *)(this + aiStack_30[0] * 0x510 + 0x594));
                    this->cDataId = uVar5;
                  }
                  if (1 < iVar8) {
                    *(float *)(this + aiStack_30[1] * 0x510 + 0x160) =
                         *(float *)(this + aiStack_30[0] * 0x510 + 0x354) + 3.0 +
                         *(float *)(this + aiStack_30[1] * 0x510 + 0x354);
                    *(float *)(this + aiStack_30[1] * 0x510 + 0x168) =
                         -*(float *)(this + aiStack_30[1] * 0x510 + 0x354) - 1.5;
                    *(undefined4 *)(this + aiStack_30[1] * 0x510 + 0x184) = 0x43340000;
                    iVar9 = this + aiStack_30[1] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                    iVar9 = this + aiStack_30[1] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                    iVar9 = this + aiStack_30[1] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  }
                  if (2 < iVar8) {
                    *(float *)(this + aiStack_30[2] * 0x510 + 0x160) =
                         (-*(float *)(this + aiStack_30[0] * 0x510 + 0x354) - 3.0) -
                         *(float *)(this + aiStack_30[2] * 0x510 + 0x354);
                    *(float *)(this + aiStack_30[2] * 0x510 + 0x168) =
                         -*(float *)(this + aiStack_30[2] * 0x510 + 0x354) - 1.5;
                    *(undefined4 *)(this + aiStack_30[2] * 0x510 + 0x184) = 0x43340000;
                    iVar9 = this + aiStack_30[2] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                    iVar9 = this + aiStack_30[2] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                    iVar9 = this + aiStack_30[2] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  }
                  if (3 < iVar8) {
                    *(float *)(this + aiStack_30[3] * 0x510 + 0x160) =
                         *(float *)(this + aiStack_30[3] * 0x510 + 0x354) +
                         *(float *)(this + aiStack_30[1] * 0x510 + 0x160) +
                         *(float *)(this + aiStack_30[1] * 0x510 + 0x354) + 3.0;
                    *(float *)(this + aiStack_30[3] * 0x510 + 0x168) =
                         -*(float *)(this + aiStack_30[3] * 0x510 + 0x354) - 1.5;
                    *(undefined4 *)(this + aiStack_30[3] * 0x510 + 0x184) = 0x43340000;
                    iVar9 = this + aiStack_30[3] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                    iVar9 = this + aiStack_30[3] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                    iVar9 = this + aiStack_30[3] * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  }
                  if (4 < iVar8) {
                    chr(this,iStack_20)->aPos =
                         ((*(float *)(this + aiStack_30[2] * 0x510 + 0x160) -
                          *(float *)(this + aiStack_30[2] * 0x510 + 0x354)) - 3.0) -
                         chr(this,iStack_20)->f2a4;
                    chr(this,iStack_20)->fb8 =
                         -chr(this,iStack_20)->f2a4 - 1.5;
                    chr(this,iStack_20)->fd4 = 0x43340000;
                    iVar9 = this + iStack_20 * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                    iVar9 = this + iStack_20 * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                    iVar9 = this + iStack_20 * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  }
                  if (5 < iVar8) {
                    chr(this,iStack_1c)->aPos = 0;
                    chr(this,iStack_1c)->fb8 =
                         ((*(float *)(this + aiStack_30[2] * 0x510 + 0x168) -
                          *(float *)(this + aiStack_30[2] * 0x510 + 0x354)) - 1.5) -
                         chr(this,iStack_1c)->f2a4;
                    fVar13 = ((*(float *)(this + aiStack_30[3] * 0x510 + 0x168) -
                              *(float *)(this + aiStack_30[3] * 0x510 + 0x354)) - 1.5) -
                             chr(this,iStack_1c)->f2a4;
                    if (fVar13 < chr(this,iStack_1c)->fb8) {
                      chr(this,iStack_1c)->fb8 = fVar13;
                    }
                    chr(this,iStack_1c)->fd4 = 0x43340000;
                    iVar9 = this + iStack_1c * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xf7;
                    iVar9 = this + iStack_1c * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xdf;
                    iVar9 = this + iStack_1c * 0x510;
                    *(byte *)(iVar9 + 0xb5) = *(byte *)(iVar9 + 0xb5) & 0xbf;
                  }
                  MakeResultTrophy__7CBattleFi(this,1);
                  for (iVar9 = 0; iVar9 < iVar8; iVar9 = iVar9 + 1) {
                    SetPosAngle__8BtlModelFP7FVectorP7FVector
                              (*(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x14c),
                               this + aiStack_30[iVar9] * 0x510 + 0x160,
                               this + aiStack_30[iVar9] * 0x510 + 0x180);
                    strcpy(*(int *)(this + aiStack_30[iVar9] * 0x510 + 0x14c) + 0x52c,
                                    0x6e4928);
                    if (*(char *)(this + aiStack_30[iVar9] * 0x510 + 0xb8) == '\a') {
                      SetBtlMotion__8BtlModelFif
                                (0x3f800000,
                                 *(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x14c),1);
                    }
                    else if (*(char *)(this + aiStack_30[iVar9] * 0x510 + 0xb8) == '\x11') {
                      *(undefined1 *)(this + aiStack_30[iVar9] * 0x510 + 0xb8) = 7;
                      *(undefined1 *)(this + aiStack_30[iVar9] * 0x510 + 0xb9) = 1;
                    }
                    iVar7 = this + aiStack_30[iVar9] * 0x510;
                    *(byte *)(iVar7 + 0xb5) = *(byte *)(iVar7 + 0xb5) & 0xf7;
                    if (*(int *)(this + aiStack_30[iVar9] * 0x510 + 0x560) != 0) {
                      (**(code **)(*(int *)(*(int *)(this + aiStack_30[iVar9] * 0x510 + 0x560) +
                                           0x14) + 0x30))();
                    }
                    *(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x560) = 0;
                    if ((long)((ulong)*(byte *)(*(int *)(this + aiStack_30[iVar9] * 0x510 + 0x14c)
                                               + 0x4d1) << 0x3e) < 0) {
                      OTEntry__8BtlModelFii
                                (*(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x14c),4,8);
                      ShadowOn__8BtlModelFv
                                (*(undefined4 *)(this + aiStack_30[iVar9] * 0x510 + 0x14c));
                    }
                    iVar7 = *(int *)(this + aiStack_30[iVar9] * 0x510 + 0x14c);
                    *(byte *)(iVar7 + 0x4d1) = *(byte *)(iVar7 + 0x4d1) & 0xfd;
                  }
                  Retail_CBtlPAfter2_ShowAllHitInfo(uGpffff8618);
                  if (*(int *)(this + 0x45cc) != 0) {
                    *(undefined4 *)(*(int *)(this + 0x45cc) + 0x38) = 1;
                  }
                  SetWinCamera1__9BtlCameraFib(this->pCamera,aiStack_30[0],1);
                  this->nCmd0_target = 0;
                  this->flMenuTimer = 0;
                  if ((this->pBtlResult != 0) &&
                     (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
                    EffectNext__6EffectFv(this->pBtlResult);
                    this->nStep = 10;
                    return;
                  }
                  this->nStep = 0xb;
                  return;
                }
                if ((long)this->cActor == (long)aiStack_30[iVar9]) {
                  iVar7 = aiStack_30[iVar9];
                  aiStack_30[iVar9] = aiStack_30[0];
                  aiStack_30[0] = iVar7;
                  goto LAB_0049b160;
                }
                iVar9 = iVar9 + 1;
              } while( true );
            }
            if ((this->pBtlResult != 0) &&
               (-1 < (long)((ulong)this->bFlags25 << 0x39))) {
              return;
            }
            iVar8 = this->pBtlResult;
            if (iVar8 != 0) {
              (**(code **)(*(int *)(iVar8 + 0x14) + 8))(iVar8,1);
            }
            this->pBtlResult = 0;
            SetAlphaMode__8BtlFaderFUl(0x44);
            Retail_CBattle_ReleaseChrWait(this);
            this->nStep = 3;
          }
          if (*(int *)(this->pParamDisp + 0x38) == 2) {
            ParamClose__9ParamDispFv(this->pParamDisp);
          }
          if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
            TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
          }
          this->nStep = 4;
          this->nCmd0_target = 0;
        }
        if ((this->pParamDisp != 0) && (*(int *)(this->pParamDisp + 0x38) == 0)) {
          Destruct__9ParamDispFv(this->pParamDisp);
          this->pParamDisp = 0;
        }
        if (*(int *)(this + 0x45cc) != 0) {
          Destruct__9ComboFormFv(*(undefined4 *)(this + 0x45cc));
          *(undefined4 *)(this + 0x45cc) = 0;
        }
        if ((this->pTurnOrderDisp != 0) && (*(int *)(this->pTurnOrderDisp + 0x38) == 0)) {
          Destruct__13TurnOrderDispFv(this->pTurnOrderDisp);
          this->pTurnOrderDisp = 0;
        }
        this->flMenuTimer = this->flMenuTimer + this->flDeltaT;
        if (*(char *)(this + 0x4850) != '\0') {
          return;
        }
        if (*(char *)(this + 0x4858) != '\0') {
          return;
        }
        if (((1.0 <= this->flMenuTimer) && (this->nCmd0_target == 0)) &&
           (-1 < *(short *)(this + 0x4910))) {
          lVar6 = __nw__FUi(0x5c);
          if (lVar6 != 0) {
            __ct__18BtlResultRetailFxBFv();
          }
          this->nCmd0_target = 1;
          this->flMenuTimer = 0;
        }
        if (this->flMenuTimer < 3.0) {
          return;
        }
        SetHoldFade__8BtlFaderFfs(0x3f800000,3);
        Destruct__8CmbBreakFf(0x3f800000);
        SetStrength__18BtlResultRetailFxAFf(0x3f800000);
        SetStrength__18BtlResultRetailFxBFf(0x3f800000);
        this->nPhase = 0x17;
        this->nStep = 0;
        this->bFlags25 = this->bFlags25 & 0xfc | 1;
        this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
        if (-1 < (long)((ulong)this->bFlags24 << 0x3a)) {
          return;
        }
        if (*(int *)(this + 0x98) == 0) {
          return;
        }
        (**(code **)(this + 0x98))(4,0,0,*(undefined4 *)(this + 0x94));
        return;
      }
      if ((this->pBtlResult != 0) && (-1 < (long)((ulong)this->bFlags25 << 0x39))
         ) {
        return;
      }
      iVar8 = this->pBtlResult;
      if (iVar8 != 0) {
        (**(code **)(*(int *)(iVar8 + 0x14) + 8))(iVar8,1);
      }
      this->pBtlResult = 0;
      SetAlphaMode__8BtlFaderFUl(0x44);
      Retail_CBattle_ReleaseChrWait(this);
      this->nStep = 0xb;
    }
    if ((-1 < this->cDataId) &&
       (*(char *)(this + this->cDataId * 0x18 + 0x40c5) != '\x03')) {
      return;
    }
    if (*(int *)(this->pParamDisp + 0x38) == 2) {
      ParamClose__9ParamDispFv(this->pParamDisp);
    }
    if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
      TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
    }
    this->nCmd0_target = 0;
    this->flMenuTimer = 0;
    this->nCmd1 = 0;
    this->nCmdKind = 0;
    this->nStep = 0xc;
  }
  if ((this->pParamDisp != 0) && (*(int *)(this->pParamDisp + 0x38) == 0)) {
    Destruct__9ParamDispFv(this->pParamDisp);
    this->pParamDisp = 0;
  }
  if (*(int *)(this + 0x45cc) != 0) {
    Destruct__9ComboFormFv(*(undefined4 *)(this + 0x45cc));
    *(undefined4 *)(this + 0x45cc) = 0;
  }
  if ((this->pTurnOrderDisp != 0) && (*(int *)(this->pTurnOrderDisp + 0x38) == 0)) {
    Destruct__13TurnOrderDispFv(this->pTurnOrderDisp);
    this->pTurnOrderDisp = 0;
  }
  this->flMenuTimer = this->flMenuTimer + this->flDeltaT;
  for (iVar8 = 0; iVar8 < 0xc; iVar8 = iVar8 + 1) {
    if (((((chr(this,iVar8)->bFlagsA & 1) != 0) &&
         ((long)((ulong)chr(this,iVar8)->bFlagsA << 0x3e) < 0)) &&
        (-1 < (long)((ulong)chr(this,iVar8)->bFlagsA2 << 0x3c))) &&
       (((chr(this,iVar8)->bFlagsB & 1) != 0 &&
        ((chr(this,iVar8)->bState == '\'' ||
         (chr(this,iVar8)->bState == '(')))))) {
      for (iVar9 = 0; iVar9 < 0x20; iVar9 = iVar9 + 1) {
        if (((*(char *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1d0) == 'T') &&
            (((ulong)*(byte *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1cd) & 0x3f) >> 3 == 0)) &&
           ((*(uint *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1d4) & 0x20) != 0)) {
          *(undefined1 *)(this + iVar8 * 0x510 + iVar9 * 0xc + 0x1d0) = 0;
        }
      }
    }
  }
  bVar2 = this->flMenuTimer < 0.2;
  if (chr(this,this->cActor)->pModel == 0) {
    bVar2 = true;
  }
  else if (*(short *)(chr(this,this->cActor)->pModel + 0x510) != 1) {
    bVar2 = true;
  }
  if ((this->nCmd1 & 1 << ((int)this->cActor & 0x1fU)) != 0) {
    bVar2 = true;
  }
  if (!bVar2) {
    SetNextBtlMotion__8BtlModelFif
              (0x3f800000,chr(this,this->cActor)->pModel,0x30);
    if (-1 < this->cDataId) {
      PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0xffffffff90000000,1,0);
    }
    this->nCmd1 =
         this->nCmd1 | 1 << ((int)this->cActor & 0x1fU);
  }
  lVar6 = 0;
  while (lVar6 < 0xc) {
    uVar10 = (uint)lVar6;
    if ((((((chr(this,uVar10)->bFlagsA & 1) != 0) &&
          ((long)((ulong)chr(this,uVar10)->bFlagsA << 0x3e) < 0)) &&
         (-1 < (long)((ulong)chr(this,uVar10)->bFlagsA2 << 0x3c))) &&
        (((chr(this,uVar10)->bFlagsB & 1) != 0 &&
         (this->cActor != lVar6)))) &&
       ((*(short *)(chr(this,uVar10)->pModel + 0x510) == 1 &&
        ((this->nCmd1 & 1 << (uVar10 & 0x1f)) == 0)))) {
      SetNextBtlMotion__8BtlModelFif
                (0x3f800000,chr(this,uVar10)->pModel,0x30);
      this->nCmd1 = this->nCmd1 | 1 << (uVar10 & 0x1f);
    }
    lVar6 = (long)(int)(uVar10 + 1);
  }
  if ((*(char *)(this + 0x4850) == '\0') && (*(char *)(this + 0x4858) == '\0')) {
    if ((1.0 <= this->flMenuTimer) &&
       ((this->nCmd0_target == 0 && (-1 < *(short *)(this + 0x4910))))) {
      lVar6 = __nw__FUi(0x5c);
      if (lVar6 != 0) {
        __ct__18BtlResultRetailFxBFv();
      }
      this->nCmd0_target = 1;
      this->flMenuTimer = 0;
    }
    if (3.0 <= this->flMenuTimer) {
      if (-1 < this->cDataId) {
        IOPRelease__6HNMSndFi(uGpffff8374,this->nIopHandle);
        DataRelease__7CBattleFiib(this,this->cDataId,0xc,0);
      }
      this->nIopHandle = 0xffffffff;
      this->cDataId = 0xff;
      SetHoldFade__8BtlFaderFfs(0x3f800000,3);
      Destruct__8CmbBreakFf(0x3f800000);
      SetStrength__18BtlResultRetailFxAFf(0x3f800000);
      SetStrength__18BtlResultRetailFxBFf(0x3f800000);
      this->nPhase = 0x17;
      this->nStep = 0;
      this->bFlags25 = this->bFlags25 & 0xfc | 1;
      this->bFlags24 = this->bFlags24 & 0x7f | 0x80;
      if (((long)((ulong)this->bFlags24 << 0x3a) < 0) && (*(int *)(this + 0x98) != 0)) {
        (**(code **)(this + 0x98))(4,0,0,*(undefined4 *)(this + 0x94));
      }
    }
  }
  return;
}

/* ---- 0x0049ccd0  CloseBattleUI__7CBattleFb  (size 0x1c0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
bool CloseBattleUI__7CBattleFb(int this,char param_2)

{
  bool bVar1;
  
  if (-1 < this->cMesWinId) {
    SetMesWinClose__7BtlMenuFi(this->cMesWinId);
  }
  this->cMesWinId = 0xff;
  if (param_2 == '\x01') {
    this->cMesWinId2 = 0xff;
  }
  bVar1 = false;
  if (*(int *)(this->pParamDisp + 0x38) != 0) {
    if (*(int *)(this->pParamDisp + 0x38) == 2) {
      ParamClose__9ParamDispFv(this->pParamDisp);
    }
    bVar1 = true;
  }
  if (*(int *)(this->pTurnOrderDisp + 0x38) != 0) {
    if (*(int *)(this->pTurnOrderDisp + 0x38) == 2) {
      TurnOrderClose__13TurnOrderDispFv(this->pTurnOrderDisp);
    }
    bVar1 = true;
  }
  if (iGpffff8618->nCmd1 != 0) {
    if ((iGpffff8618->nCmd1 == 2) &&
       ((iGpffff8618->nCmd1 == 1 || (iGpffff8618->nCmd1 == 2)))) {
      iGpffff8618->nCmd1 = 3;
    }
    bVar1 = true;
  }
  return !bVar1;
}
