/* Section I -- cleaned Ghidra output of the retail per-character sequencer and AI setup in SH2US_BATTLE.BIN.
 * The "AIInit family" (0x6abaf0-0x6cf020) is: CBattle::BtlChrSequence (a switch on chr bState, 0x6abaf0), five out-of-line state handlers
 * (State0E0F 0x6c6730, State31..34 0x6ce010-0x6ceb10), AddFriendship 0x6ceeb0, and AIInit 0x6cf020.
 * AIInit(i) is the single AI-script setup function: pAiCursor = pAiScript + 4 (skip the script header), clears the AI registers (aAiReg and the
 * six shorts at +0xfe..+0x10a) and wTurnCount.  It has no variants; the per-state differences live in BtlChrSequence's cases.
 * GetTarget 0x6d9450 (AI target selection), EffectCheck 0x6e0260 / EffectCheckCore 0x6e0320 follow.
 * Analysis output, not compilable source.  Field names as in us_battle_phases.c. */

/* ---- 0x006abaf0  BtlChrSequence__7CBattleFv  (size 0x1ac40) ----
 *   bState targets: ['0x0', '0x3', '0x6', '0x7', '0x11', '0x14', '0x18', '0x22', '0x23', '0x24', '0x28', '0x2a', '0x2b', '0x2e', '0x2f', '0x30'] */
void BtlChrSequence__7CBattleFv(undefined8 this)

{
  bool bVar1;
  short sVar2;
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  long lVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  ulong uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  long lVar19;
  int this;
  int iVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float unaff_f22;
  undefined1 in_vf0 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auStack_c40 [8];
  undefined4 uStack_c38;
  undefined4 uStack_c34;
  undefined1 auStack_c30 [8];
  undefined4 uStack_c28;
  undefined4 uStack_c24;
  undefined1 auStack_c20 [8];
  undefined4 uStack_c18;
  undefined4 uStack_c14;
  undefined1 auStack_c10 [16];
  undefined8 uStack_c00;
  undefined4 uStack_bf8;
  undefined4 uStack_bf4;
  undefined8 uStack_bf0;
  undefined4 uStack_be8;
  undefined4 uStack_be4;
  undefined1 auStack_be0 [8];
  undefined4 uStack_bd8;
  undefined4 uStack_bd4;
  undefined1 auStack_bd0 [16];
  undefined1 auStack_bc0 [16];
  undefined1 auStack_bb0 [8];
  undefined4 uStack_ba8;
  undefined4 uStack_ba4;
  undefined1 auStack_ba0 [8];
  undefined4 uStack_b98;
  undefined4 uStack_b94;
  undefined1 auStack_b90 [8];
  undefined4 uStack_b88;
  undefined4 uStack_b84;
  undefined1 auStack_b80 [8];
  undefined4 uStack_b78;
  undefined4 uStack_b74;
  undefined1 auStack_b70 [8];
  undefined4 uStack_b68;
  undefined4 uStack_b64;
  undefined1 auStack_b60 [8];
  undefined4 uStack_b58;
  undefined4 uStack_b54;
  undefined1 auStack_b50 [8];
  undefined4 uStack_b48;
  undefined4 uStack_b44;
  undefined1 auStack_b40 [8];
  undefined4 uStack_b38;
  undefined4 uStack_b34;
  undefined1 auStack_b30 [8];
  undefined4 uStack_b28;
  undefined4 uStack_b24;
  undefined1 auStack_b20 [8];
  undefined4 uStack_b18;
  undefined4 uStack_b14;
  undefined1 auStack_b10 [8];
  undefined4 uStack_b08;
  undefined4 uStack_b04;
  undefined8 uStack_b00;
  undefined4 uStack_af8;
  undefined4 uStack_af4;
  undefined1 auStack_af0 [8];
  undefined4 uStack_ae8;
  undefined4 uStack_ae4;
  undefined1 auStack_ae0 [8];
  undefined4 uStack_ad8;
  undefined4 uStack_ad4;
  undefined1 auStack_ad0 [16];
  undefined8 uStack_ac0;
  undefined4 uStack_ab8;
  undefined4 uStack_ab4;
  undefined8 uStack_ab0;
  undefined4 uStack_aa8;
  undefined4 uStack_aa4;
  undefined1 auStack_aa0 [8];
  undefined4 uStack_a98;
  undefined4 uStack_a94;
  undefined1 auStack_a90 [8];
  undefined4 uStack_a88;
  undefined4 uStack_a84;
  undefined1 auStack_a80 [8];
  undefined4 uStack_a78;
  undefined4 uStack_a74;
  undefined1 auStack_a70 [8];
  undefined4 uStack_a68;
  undefined4 uStack_a64;
  undefined1 auStack_a60 [8];
  undefined4 uStack_a58;
  undefined4 uStack_a54;
  undefined8 uStack_a50;
  undefined4 uStack_a48;
  undefined4 uStack_a44;
  undefined1 auStack_a40 [16];
  undefined1 auStack_a30 [8];
  undefined4 uStack_a28;
  undefined4 uStack_a24;
  undefined1 auStack_a20 [8];
  undefined4 uStack_a18;
  undefined4 uStack_a14;
  undefined1 auStack_a10 [8];
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined8 uStack_a00;
  undefined4 uStack_9f8;
  undefined4 uStack_9f4;
  undefined8 uStack_9f0;
  float fStack_9e8;
  undefined4 uStack_9e4;
  undefined1 auStack_9e0 [16];
  undefined1 auStack_9d0 [8];
  undefined4 uStack_9c8;
  undefined4 uStack_9c4;
  undefined1 auStack_9c0 [16];
  undefined8 uStack_9b0;
  undefined4 uStack_9a8;
  undefined4 uStack_9a4;
  undefined1 auStack_9a0 [16];
  undefined8 uStack_990;
  undefined4 uStack_988;
  undefined4 uStack_984;
  undefined8 uStack_980;
  float fStack_978;
  undefined4 uStack_974;
  undefined1 auStack_970 [16];
  undefined1 auStack_960 [8];
  undefined4 uStack_958;
  undefined4 uStack_954;
  undefined8 uStack_950;
  undefined4 uStack_948;
  undefined4 uStack_944;
  undefined1 auStack_940 [16];
  undefined1 auStack_930 [16];
  undefined8 uStack_920;
  undefined4 uStack_918;
  undefined4 uStack_914;
  undefined1 auStack_910 [16];
  undefined1 auStack_900 [8];
  undefined4 uStack_8f8;
  undefined4 uStack_8f4;
  undefined8 uStack_8f0;
  float fStack_8e8;
  undefined4 uStack_8e4;
  undefined1 auStack_8e0 [16];
  undefined1 auStack_8d0 [8];
  undefined4 uStack_8c8;
  undefined4 uStack_8c4;
  undefined8 uStack_8c0;
  undefined4 uStack_8b8;
  undefined4 uStack_8b4;
  undefined8 uStack_8b0;
  float fStack_8a8;
  undefined4 uStack_8a4;
  undefined1 auStack_8a0 [16];
  undefined1 auStack_890 [16];
  undefined8 uStack_880;
  undefined4 uStack_878;
  undefined4 uStack_874;
  undefined1 auStack_870 [16];
  undefined8 uStack_860;
  undefined4 uStack_858;
  undefined4 uStack_854;
  undefined8 uStack_850;
  undefined4 uStack_848;
  undefined4 uStack_844;
  undefined1 auStack_840 [8];
  undefined4 uStack_838;
  undefined4 uStack_834;
  undefined8 uStack_830;
  float fStack_828;
  undefined4 uStack_824;
  undefined1 auStack_820 [16];
  undefined1 auStack_810 [8];
  undefined4 uStack_808;
  undefined4 uStack_804;
  undefined8 uStack_800;
  undefined4 uStack_7f8;
  undefined4 uStack_7f4;
  undefined8 uStack_7f0;
  float fStack_7e8;
  undefined4 uStack_7e4;
  undefined1 auStack_7e0 [16];
  undefined1 auStack_7d0 [8];
  undefined4 uStack_7c8;
  undefined4 uStack_7c4;
  undefined1 auStack_7c0 [8];
  undefined4 uStack_7b8;
  undefined4 uStack_7b4;
  undefined1 auStack_7b0 [8];
  undefined4 uStack_7a8;
  undefined4 uStack_7a4;
  undefined8 uStack_7a0;
  float fStack_798;
  undefined4 uStack_794;
  undefined1 auStack_790 [16];
  undefined1 auStack_780 [8];
  undefined4 uStack_778;
  undefined4 uStack_774;
  undefined8 uStack_770;
  float fStack_768;
  undefined4 uStack_764;
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [8];
  undefined4 uStack_748;
  undefined4 uStack_744;
  undefined8 uStack_740;
  float fStack_738;
  undefined4 uStack_734;
  undefined1 auStack_730 [16];
  undefined1 auStack_720 [8];
  undefined4 uStack_718;
  undefined4 uStack_714;
  undefined1 auStack_710 [8];
  undefined4 uStack_708;
  undefined4 uStack_704;
  undefined8 uStack_700;
  undefined4 uStack_6f8;
  undefined4 uStack_6f4;
  undefined1 auStack_6f0 [16];
  undefined8 uStack_6e0;
  undefined4 uStack_6d8;
  undefined4 uStack_6d4;
  undefined8 uStack_6d0;
  undefined4 uStack_6c8;
  undefined4 uStack_6c4;
  undefined8 uStack_6c0;
  undefined4 uStack_6b8;
  undefined4 uStack_6b4;
  undefined8 uStack_6b0;
  undefined4 uStack_6a8;
  undefined4 uStack_6a4;
  undefined8 uStack_6a0;
  undefined4 uStack_698;
  undefined4 uStack_694;
  undefined8 uStack_690;
  undefined4 uStack_688;
  undefined4 uStack_684;
  undefined8 uStack_680;
  undefined4 uStack_678;
  undefined4 uStack_674;
  undefined8 uStack_670;
  undefined4 uStack_668;
  undefined4 uStack_664;
  undefined8 uStack_660;
  undefined4 uStack_658;
  undefined4 uStack_654;
  undefined8 uStack_650;
  undefined4 uStack_648;
  undefined4 uStack_644;
  undefined8 uStack_640;
  undefined4 uStack_638;
  undefined4 uStack_634;
  undefined8 uStack_630;
  undefined4 uStack_628;
  undefined4 uStack_624;
  undefined8 uStack_620;
  undefined4 uStack_618;
  undefined4 uStack_614;
  undefined8 uStack_610;
  undefined4 uStack_608;
  undefined4 uStack_604;
  undefined8 uStack_600;
  undefined4 uStack_5f8;
  undefined4 uStack_5f4;
  undefined8 uStack_5f0;
  undefined4 uStack_5e8;
  undefined4 uStack_5e4;
  undefined8 uStack_5e0;
  undefined4 uStack_5d8;
  undefined4 uStack_5d4;
  undefined8 uStack_5d0;
  undefined4 uStack_5c8;
  undefined4 uStack_5c4;
  undefined8 uStack_5c0;
  undefined4 uStack_5b8;
  undefined4 uStack_5b4;
  undefined1 auStack_5b0 [16];
  undefined8 uStack_5a0;
  undefined4 uStack_598;
  undefined4 uStack_594;
  undefined8 uStack_590;
  undefined4 uStack_588;
  undefined4 uStack_584;
  undefined8 uStack_580;
  undefined4 uStack_578;
  undefined4 uStack_574;
  undefined8 uStack_570;
  undefined4 uStack_568;
  undefined4 uStack_564;
  undefined8 uStack_560;
  undefined4 uStack_558;
  undefined4 uStack_554;
  undefined1 auStack_550 [16];
  undefined8 uStack_540;
  undefined4 uStack_538;
  undefined4 uStack_534;
  undefined8 uStack_530;
  undefined4 uStack_528;
  undefined4 uStack_524;
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [8];
  undefined4 uStack_508;
  undefined4 uStack_504;
  undefined1 auStack_500 [16];
  undefined8 uStack_4f0;
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  undefined1 auStack_4e0 [16];
  undefined8 uStack_4d0;
  undefined4 uStack_4c8;
  undefined4 uStack_4c4;
  undefined1 auStack_4c0 [8];
  undefined4 uStack_4b8;
  undefined4 uStack_4b4;
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined8 uStack_490;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined8 uStack_480;
  undefined4 uStack_478;
  undefined4 uStack_474;
  undefined1 auStack_470 [8];
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined1 auStack_460 [8];
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined8 uStack_450;
  float fStack_448;
  undefined4 uStack_444;
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [8];
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined1 auStack_420 [8];
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined1 auStack_410 [8];
  undefined4 uStack_408;
  undefined4 uStack_404;
  undefined1 auStack_400 [8];
  undefined4 uStack_3f8;
  undefined4 uStack_3f4;
  undefined1 auStack_3f0 [8];
  undefined4 uStack_3e8;
  undefined4 uStack_3e4;
  undefined1 auStack_3e0 [8];
  undefined4 uStack_3d8;
  undefined4 uStack_3d4;
  undefined1 auStack_3d0 [8];
  undefined4 uStack_3c8;
  undefined4 uStack_3c4;
  undefined8 uStack_3c0;
  undefined4 uStack_3b8;
  undefined4 uStack_3b4;
  ulong uStack_3b0;
  undefined4 uStack_3a8;
  undefined4 uStack_3a4;
  ulong uStack_3a0;
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined1 auStack_390 [16];
  undefined8 uStack_380;
  undefined4 uStack_378;
  undefined4 uStack_374;
  undefined1 auStack_370 [8];
  undefined4 uStack_368;
  undefined4 uStack_364;
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined8 uStack_320;
  undefined4 uStack_318;
  undefined4 uStack_314;
  undefined8 uStack_310;
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined1 auStack_300 [8];
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  undefined1 auStack_2f0 [8];
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined1 auStack_2e0 [8];
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined8 uStack_270;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [8];
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [8];
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [16];
  undefined8 uStack_230;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined8 uStack_170;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined8 uStack_160;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [8];
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [8];
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [8];
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [16];
  undefined4 auStack_e0 [2];
  undefined2 uStack_d8;
  byte bStack_9a;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined8 uStack_8;
  
  auStack_10._4_4_ = in_zero_hi;
  auStack_10._0_4_ = in_zero_lo;
  uStack_8._0_4_ = (float)in_zero_udw;
  uStack_8._4_4_ = in_register_0000000c;
  fStack_30 = in_zero_lo;
  fStack_2c = in_zero_hi;
  uStack_28 = in_zero_udw;
  uStack_24 = in_register_0000000c;
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  UnitMatrix__6MatrixFv(auStack_70);
  iVar4 = GetTimer__7SysToolFv();
  lVar19 = 0;
  do {
    /* this = this */
    if (0xb < lVar19) {
      if ((this->nPhase < 2) && (this->nStep < 5)) {
        for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
          if ((((chr(this,iVar4)->bFlagsA & 1) != 0) &&
              ((long)((ulong)chr(this,iVar4)->bFlagsA << 0x3e) < 0)) &&
             ((-1 < (long)((ulong)chr(this,iVar4)->bFlagsA2 << 0x3c) &&
              (iVar14 = chr(this,iVar4)->pModel,
              (**(code **)(*(int *)(iVar14 + 0x10) + 0x28))(iVar14,0),
              '\x02' < chr(this,iVar4)->bState)))) {
            CalcPushRange__7CBattleFi(this,iVar4);
          }
        }
      }
      else {
        PushCheck__7CBattleFv(this);
        for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
          if ((((chr(this,iVar4)->bFlagsA & 1) != 0) &&
              ((long)((ulong)chr(this,iVar4)->bFlagsA << 0x3e) < 0)) &&
             (-1 < (long)((ulong)chr(this,iVar4)->bFlagsA2 << 0x3c))) {
            iVar14 = chr(this,iVar4)->pModel;
            (**(code **)(*(int *)(iVar14 + 0x10) + 0x28))(iVar14,0);
            CalcPushRange__7CBattleFi(this,iVar4);
            AttackParam__7CBattleFi(this,iVar4);
          }
        }
        AttackHitCheck__7CBattleFv(this);
      }
      for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
        if ((*(int *)(this + iVar4 * 4 + 0x3d70) != 0) &&
           ((long)((ulong)*(byte *)(*(int *)(this + iVar4 * 4 + 0x3d70) + 0x4d1) << 0x39) < 0)) {
          (**(code **)(*(int *)(*(int *)(this + iVar4 * 4 + 0x3d70) + 0x10) + 0x2c))
                    this->flDeltaT;
          iVar14 = *(int *)(this + iVar4 * 4 + 0x3d70);
          (**(code **)(*(int *)(iVar14 + 0x10) + 0x28))(iVar14,0);
        }
      }
      return;
    }
    uVar18 = (uint)lVar19;
    if ((chr(this,uVar18)->bFlagsA & 1) != 0) {
      iVar14 = this + uVar18 * 0x510;
      *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfb;
      IconFunc__7CBattleFi(this,lVar19);
      fVar23 = 1.0;
      fVar25 = 1.0;
      if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) &&
         (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x38))) {
        if (lVar19 != this->cActor) {
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
            (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))(0);
          }
          goto LAB_006c63e8;
        }
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0x7f | 0x80;
      }
      if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x39) < 0) {
        if (chr(this,uVar18)->nHp < 1) {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xdf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xbf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0x7f;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb1) = *(byte *)(iVar14 + 0xb1) & 0xfe;
          chr(this,uVar18)->f114 = 0;
        }
        else {
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x1c4) = *(float *)(iVar14 + 0x1c4) - this->flDeltaT;
          if (chr(this,uVar18)->f114 <= 0.0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xdf | 0x20;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xbf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb1) = *(byte *)(iVar14 + 0xb1) & 0xfe;
            chr(this,uVar18)->f114 = 0;
            if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x38)) {
              if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
                (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))(0);
              }
              goto LAB_006c63e8;
            }
          }
        }
      }
      switch(chr(this,uVar18)->bState) {
      case 2:
        switch(chr(this,uVar18)->bState2) {
        case 0:
          iVar14 = GetTimer__7SysToolFv();
          if ((((float)(uint)(iVar14 - iVar4) * 0.03 < 0.3) &&
              ((long)((ulong)*(byte *)(this + chr(this,uVar18)->f4d4 * 0x18 +
                                      0x40c4) << 0x3a) < 0)) &&
             (((chr(this,uVar18)->f4d5 < '\0' ||
               ((long)((ulong)*(byte *)(this + chr(this,uVar18)->f4d5 * 0x18 +
                                       0x40c4) << 0x3a) < 0)) &&
              ((chr(this,uVar18)->f4d6 < '\0' ||
               ((long)((ulong)*(byte *)(this + chr(this,uVar18)->f4d6 * 0x18 +
                                       0x40c4) << 0x3a) < 0)))))) {
            if (chr(this,uVar18)->pModel == 0) {
              lVar11 = __nw__FUi(0x5f0);
              uVar12 = 0;
              if (lVar11 != 0) {
                uVar12 = __ct__8BtlModelFs(lVar11,(short)lVar19);
              }
              chr(this,uVar18)->pModel = uVar12;
            }
            chr(this,uVar18)->f4d0 = 0;
            chr(this,uVar18)->bState2 = 1;
          }
          break;
        case 1:
          iVar14 = GetTimer__7SysToolFv();
          if ((float)(uint)(iVar14 - iVar4) * 0.03 < 0.3) {
            uVar12 = *(undefined4 *)
                      (*(int *)(this + chr(this,uVar18)->f4d4 * 0x18 + 0x40cc)
                      + 4);
            uVar5 = GetFileCount(uVar12);
            for (uVar17 = chr(this,uVar18)->f4d0; uVar17 < uVar5;
                uVar17 = uVar17 + 1) {
              uVar10 = GetFileID(uVar12,uVar17);
              iVar14 = GetTimer__7SysToolFv();
              fVar23 = (float)(uint)(iVar14 - iVar4) * 0.03;
              lVar19 = strcmp(uVar10,0x6e6c78);
              if (lVar19 == 0) {
                if (0.075 <= fVar23) break;
                uVar10 = GetFileEntry(uVar12,0);
                iVar14 = chr(this,uVar18)->pModel;
                (**(code **)(*(int *)(iVar14 + 0x10) + 0x48))(iVar14,uVar10);
              }
              else {
                lVar19 = strcmp(uVar10,0x6e6f98);
                if (lVar19 == 0) {
                  if (0.075 <= fVar23) break;
                  uVar10 = GetFileEntry(uVar12,uVar17);
                  CreateShadow__8BtlModelFPUc
                            (chr(this,uVar18)->pModel,uVar10);
                }
                else {
                  lVar19 = strcmp(uVar10,0x6e6c70);
                  if (lVar19 == 0) {
                    if (0.3 <= fVar23) break;
                    uVar10 = GetFileEntry(uVar12,uVar17);
                    createMotion__5ModelFPUc(chr(this,uVar18)->pModel,uVar10);
                  }
                  else {
                    lVar19 = strcmp(uVar10,0x6e6fa0);
                    if (lVar19 == 0) {
                      if (0.3 <= fVar23) break;
                      uVar13 = GetFileEntry(uVar12,uVar17);
                      chr(this,uVar18)->f4bc = uVar13;
                    }
                    else {
                      lVar19 = strcmp(uVar10,0x6e6fa8);
                      if (lVar19 == 0) {
                        if (0.3 <= fVar23) break;
                        uVar13 = GetFileEntry(uVar12,uVar17);
                        chr(this,uVar18)->f4c4 = uVar13;
                      }
                      else {
                        lVar19 = strcmp(uVar10,0x6e6fb0);
                        if (lVar19 == 0) {
                          if (0.3 <= fVar23) break;
                          puVar7 = (undefined4 *)GetFileEntry(uVar12,uVar17);
                          chr(this,uVar18)->f4e2 = (short)*puVar7;
                        }
                        else {
                          lVar19 = strcmp(uVar10,0x6e6fb8);
                          if (lVar19 == 0) {
                            if (0.3 <= fVar23) break;
                            puVar7 = (undefined4 *)GetFileEntry(uVar12,uVar17);
                            chr(this,uVar18)->f4e4 = (short)*puVar7;
                          }
                          else {
                            lVar19 = strcmp(uVar10,0x6e6fc0);
                            if (lVar19 == 0) {
                              if (0.3 <= fVar23) break;
                              puVar7 = (undefined4 *)GetFileEntry(uVar12,uVar17);
                              chr(this,uVar18)->f4e6 = (short)*puVar7;
                            }
                            else {
                              lVar19 = strcmp(uVar10,0x6e6fc8);
                              if (lVar19 == 0) {
                                if (0.3 <= fVar23) break;
                                uVar13 = GetFileEntry(uVar12,uVar17);
                                chr(this,uVar18)->f490 = uVar13;
                                chr(this,uVar18)->f494 =
                                     chr(this,uVar18)->f490 + 0x30;
                              }
                              else {
                                lVar19 = strcmp(uVar10,0x6e6fd0);
                                if (lVar19 == 0) {
                                  if (0.3 <= fVar23) break;
                                  uVar10 = GetFileEntry(uVar12,uVar17);
                                  AddModelEffect__8BtlModelFiiPc
                                            (chr(this,uVar18)->pModel,
                                             chr(this,uVar18)->nMonId,0,
                                             uVar10);
                                }
                                else {
                                  lVar19 = strcmp(uVar10,0x6e6fd8);
                                  if (lVar19 == 0) {
                                    if (0.3 <= fVar23) break;
                                    uVar16 = 0x28;
                                    while (((int)uVar16 < 0x46 &&
                                           ((*(int *)(this + uVar16 * 4 + 0x4484) == 0 ||
                                            (*(int *)(*(int *)(this + uVar16 * 4 + 0x4484) + 0x84)
                                             != chr(this,uVar18)->f4d4 * 10)))))
                                    {
                                      uVar16 = uVar16 + 1;
                                    }
                                    if (0x45 < (int)uVar16) {
                                      for (uVar16 = 0x28; (int)uVar16 < 0x46; uVar16 = uVar16 + 1) {
                                        if (*(int *)(this + uVar16 * 4 + 0x4484) == 0) {
                                          uVar10 = GetFileEntry(uVar12,uVar17);
                                          lVar19 = __nw__FUi(0x90);
                                          uVar13 = 0;
                                          if (lVar19 != 0) {
                                            uVar13 = __ct__6JRCTexFUs(lVar19,uVar16 & 0xffff);
                                          }
                                          *(undefined4 *)(this + uVar16 * 4 + 0x4484) = uVar13;
                                          iVar14 = (int)uVar10;
                                          if ((*(byte *)(iVar14 + 8) & 7) == 1) {
                                            RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                             (this + uVar16 * 4 + 0x4484),0x1b,
                                                            *(undefined2 *)(iVar14 + 4),
                                                            *(undefined2 *)(iVar14 + 6));
                                          }
                                          else {
                                            RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                             (this + uVar16 * 4 + 0x4484),0x2c,
                                                            *(undefined2 *)(iVar14 + 4),
                                                            *(undefined2 *)(iVar14 + 6));
                                          }
                                          ClutCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                           (this + uVar16 * 4 + 0x4484),0,0x10,
                                                          0x10);
                                          Create__6JRCTexFPvUsUsUs(*(undefined4 *)
                                                           (this + uVar16 * 4 + 0x4484),uVar10,0,0
                                                          ,0);
                                          *(int *)(*(int *)(this + uVar16 * 4 + 0x4484) + 0x84) =
                                               chr(this,uVar18)->f4d4 * 10;
                                          break;
                                        }
                                      }
                                    }
                                    chr(this,uVar18)->f500 = (char)uVar16;
                                    iVar14 = *(int *)(this + uVar16 * 4 + 0x4484);
                                    iVar14->flMenuTimer2 =
                                         iVar14->flMenuTimer2 | 1 << (uVar18 & 0x1f);
                                  }
                                  else {
                                    lVar19 = strcmp(uVar10,0x6e6fe0);
                                    if (lVar19 == 0) {
                                      if (0.3 <= fVar23) break;
                                      uVar16 = 0x28;
                                      while (((int)uVar16 < 0x46 &&
                                             ((*(int *)(this + uVar16 * 4 + 0x4484) == 0 ||
                                              (*(int *)(*(int *)(this + uVar16 * 4 + 0x4484) +
                                                       0x84) !=
                                               chr(this,uVar18)->f4d4 * 10 + 1))
                                             ))) {
                                        uVar16 = uVar16 + 1;
                                      }
                                      if (0x45 < (int)uVar16) {
                                        for (uVar16 = 0x28; (int)uVar16 < 0x46; uVar16 = uVar16 + 1)
                                        {
                                          if (*(int *)(this + uVar16 * 4 + 0x4484) == 0) {
                                            uVar10 = GetFileEntry(uVar12,uVar17);
                                            lVar19 = __nw__FUi(0x90);
                                            uVar13 = 0;
                                            if (lVar19 != 0) {
                                              uVar13 = __ct__6JRCTexFUs(lVar19,uVar16 & 0xffff);
                                            }
                                            *(undefined4 *)(this + uVar16 * 4 + 0x4484) = uVar13;
                                            iVar14 = (int)uVar10;
                                            if ((*(byte *)(iVar14 + 8) & 7) == 1) {
                                              RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                               (this + uVar16 * 4 + 0x4484),0x1b,
                                                              *(undefined2 *)(iVar14 + 4),
                                                              *(undefined2 *)(iVar14 + 6));
                                            }
                                            else {
                                              RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                               (this + uVar16 * 4 + 0x4484),0x2c,
                                                              *(undefined2 *)(iVar14 + 4),
                                                              *(undefined2 *)(iVar14 + 6));
                                            }
                                            ClutCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                             (this + uVar16 * 4 + 0x4484),0,0x10,
                                                            0x10);
                                            Create__6JRCTexFPvUsUsUs(*(undefined4 *)
                                                             (this + uVar16 * 4 + 0x4484),uVar10,0
                                                            ,0,0);
                                            *(int *)(*(int *)(this + uVar16 * 4 + 0x4484) + 0x84)
                                                 = chr(this,uVar18)->f4d4 * 10 +
                                                   1;
                                            break;
                                          }
                                        }
                                      }
                                      chr(this,uVar18)->f501 = (char)uVar16;
                                      iVar14 = *(int *)(this + uVar16 * 4 + 0x4484);
                                      iVar14->flMenuTimer2 =
                                           iVar14->flMenuTimer2 | 1 << (uVar18 & 0x1f);
                                    }
                                    else {
                                      lVar19 = strcmp(uVar10,0x6e6fe8);
                                      if (lVar19 == 0) {
                                        if (0.3 <= fVar23) break;
                                        uVar16 = 0x28;
                                        while (((int)uVar16 < 0x46 &&
                                               ((*(int *)(this + uVar16 * 4 + 0x4484) == 0 ||
                                                (*(int *)(*(int *)(this + uVar16 * 4 + 0x4484) +
                                                         0x84) !=
                                                 chr(this,uVar18)->f4d4 * 10 + 2
                                                ))))) {
                                          uVar16 = uVar16 + 1;
                                        }
                                        if (0x45 < (int)uVar16) {
                                          for (uVar16 = 0x28; (int)uVar16 < 0x46;
                                              uVar16 = uVar16 + 1) {
                                            if (*(int *)(this + uVar16 * 4 + 0x4484) == 0) {
                                              uVar10 = GetFileEntry(uVar12,uVar17);
                                              lVar19 = __nw__FUi(0x90);
                                              uVar13 = 0;
                                              if (lVar19 != 0) {
                                                uVar13 = __ct__6JRCTexFUs(lVar19,uVar16 & 0xffff);
                                              }
                                              *(undefined4 *)(this + uVar16 * 4 + 0x4484) = uVar13
                                              ;
                                              iVar14 = (int)uVar10;
                                              if ((*(byte *)(iVar14 + 8) & 7) == 1) {
                                                RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                                 (this + uVar16 * 4 + 0x4484),0x1b
                                                                ,*(undefined2 *)(iVar14 + 4),
                                                                *(undefined2 *)(iVar14 + 6));
                                              }
                                              else {
                                                RasterCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                                 (this + uVar16 * 4 + 0x4484),0x2c
                                                                ,*(undefined2 *)(iVar14 + 4),
                                                                *(undefined2 *)(iVar14 + 6));
                                              }
                                              ClutCreate__6JRCTexF6GS_PSMUiUi(*(undefined4 *)
                                                               (this + uVar16 * 4 + 0x4484),0,0x10
                                                              ,0x10);
                                              Create__6JRCTexFPvUsUsUs(*(undefined4 *)
                                                               (this + uVar16 * 4 + 0x4484),uVar10
                                                              ,0,0,0);
                                              *(int *)(*(int *)(this + uVar16 * 4 + 0x4484) + 0x84
                                                      ) = chr(this,uVar18)->f4d4
                                                          * 10 + 2;
                                              break;
                                            }
                                          }
                                        }
                                        chr(this,uVar18)->f502 = (char)uVar16;
                                        iVar14 = *(int *)(this + uVar16 * 4 + 0x4484);
                                        iVar14->flMenuTimer2 =
                                             iVar14->flMenuTimer2 | 1 << (uVar18 & 0x1f);
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              chr(this,uVar18)->f4d0 = uVar17 + 1;
            }
            if (uVar5 <= chr(this,uVar18)->f4d0) {
              chr(this,uVar18)->bState2 = 2;
              chr(this,uVar18)->f4d0 = 0;
            }
          }
          break;
        case 2:
          iVar14 = GetTimer__7SysToolFv();
          if ((float)(uint)(iVar14 - iVar4) * 0.03 < 0.3) {
            if (-1 < chr(this,uVar18)->f4d5) {
              uVar12 = *(undefined4 *)
                        (*(int *)(this + chr(this,uVar18)->f4d5 * 0x18 +
                                 0x40cc) + 4);
              uVar5 = GetFileCount(uVar12);
              for (uVar17 = chr(this,uVar18)->f4d0; uVar17 < uVar5;
                  uVar17 = uVar17 + 1) {
                uVar10 = GetFileID(uVar12,uVar17);
                iVar14 = GetTimer__7SysToolFv();
                fVar23 = (float)(uint)(iVar14 - iVar4) * 0.03;
                lVar19 = strcmp(uVar10,0x6e6c80);
                if (lVar19 == 0) {
                  if (0.075 <= fVar23) break;
                  uVar10 = GetFileEntry(uVar12,uVar17);
                  CreateRightWeapon__8BtlModelFPUc
                            (chr(this,uVar18)->pModel,uVar10);
                }
                else {
                  lVar19 = strcmp(uVar10,0x6e6ff0);
                  if (lVar19 == 0) {
                    if (0.075 <= fVar23) break;
                    uVar10 = GetFileEntry(uVar12,uVar17);
                    CreateRightWeaponShadow__8BtlModelFPUc
                              (chr(this,uVar18)->pModel,uVar10);
                  }
                  else {
                    lVar19 = strcmp(uVar10,0x6e6c88);
                    if (lVar19 == 0) {
                      if (0.075 <= fVar23) break;
                      uVar10 = GetFileEntry(uVar12,uVar17);
                      CreateLeftWeapon__8BtlModelFPUc
                                (chr(this,uVar18)->pModel,uVar10);
                    }
                    else {
                      lVar19 = strcmp(uVar10,0x6e6ff8);
                      if (lVar19 == 0) {
                        if (0.075 <= fVar23) break;
                        uVar10 = GetFileEntry(uVar12,uVar17);
                        CreateLeftWeaponShadow__8BtlModelFPUc
                                  (chr(this,uVar18)->pModel,uVar10);
                      }
                      else {
                        lVar19 = strcmp(uVar10,0x6e6c70);
                        if (lVar19 == 0) {
                          if (0.3 <= fVar23) break;
                          if (*(int *)(chr(this,uVar18)->pModel + 0x540) != 0) {
                            uVar10 = GetFileEntry(uVar12,uVar17);
                            createMotion__5ModelFPUc(*(undefined4 *)
                                             (chr(this,uVar18)->pModel + 0x540),
                                            uVar10);
                          }
                          if (*(int *)(chr(this,uVar18)->pModel + 0x544) != 0) {
                            uVar10 = GetFileEntry(uVar12,uVar17);
                            createMotion__5ModelFPUc(*(undefined4 *)
                                             (chr(this,uVar18)->pModel + 0x544),
                                            uVar10);
                          }
                        }
                        else {
                          lVar19 = strcmp(uVar10,0x6e6fa0);
                          if (lVar19 == 0) {
                            if (0.3 <= fVar23) break;
                            uVar13 = GetFileEntry(uVar12,uVar17);
                            chr(this,uVar18)->f4bc = uVar13;
                          }
                          else {
                            lVar19 = strcmp(uVar10,0x6e6fa8);
                            if (lVar19 == 0) {
                              if (0.3 <= fVar23) break;
                              uVar13 = GetFileEntry(uVar12,uVar17);
                              chr(this,uVar18)->f4c4 = uVar13;
                            }
                            else {
                              lVar19 = strcmp(uVar10,0x6e6fc8);
                              if (lVar19 == 0) {
                                if (0.3 <= fVar23) break;
                                uVar13 = GetFileEntry(uVar12,uVar17);
                                *(undefined4 *)(this + 0x4658) = uVar13;
                                *(int *)(this + 0x465c) = *(int *)(this + 0x4658) + 0x30;
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
                chr(this,uVar18)->f4d0 = uVar17 + 1;
              }
              if (chr(this,uVar18)->f4d0 < uVar5) break;
            }
            chr(this,uVar18)->bState2 = 3;
            chr(this,uVar18)->f4d0 = 0;
          }
          break;
        case 3:
          iVar14 = GetTimer__7SysToolFv();
          if ((float)(uint)(iVar14 - iVar4) * 0.03 < 0.3) {
            if (-1 < chr(this,uVar18)->f4d6) {
              chr(this,uVar18)->pAiScript =
                   *(undefined4 *)
                    (*(int *)(this + chr(this,uVar18)->f4d6 * 0x18 + 0x40cc) +
                    4);
              AIInit__7CBattleFi(this,lVar19);
              chr(this,uVar18)->aAiReg = 0;
            }
            IdelMotionReset__Fi(lVar19,0);
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,1);
            SetPosAngle__8BtlModelFP7FVectorP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x180);
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
            chr(this,uVar18)->bState2 = 4;
          }
          break;
        case 4:
          iVar14 = GetTimer__7SysToolFv();
          if ((float)(uint)(iVar14 - iVar4) * 0.03 < 0.075) {
            MakeFrameList__7CBattleFi(this,lVar19);
            if (((chr(this,uVar18)->nCharId == 6) &&
                (*(short *)(iGpffff836c + 0x750) != 1)) &&
               ((sVar2 = chr(this,uVar18)->fee, sVar2 == 0x34 ||
                ((((sVar2 == 0x32 || (sVar2 == 0x31)) || (sVar2 == 0x30)) || (sVar2 == 0x2f)))))) {
              puVar7 = (undefined4 *)vx__7FVectorFv(auStack_f0);
              *puVar7 = 0;
              puVar7 = (undefined4 *)vy__7FVectorFv(auStack_f0);
              *puVar7 = 0;
              puVar7 = (undefined4 *)vz__7FVectorFv(auStack_f0);
              *puVar7 = 0xbf060a92;
              puVar7 = (undefined4 *)vw__7FVectorFv(auStack_f0);
              *puVar7 = 0x3f800000;
              SetIdleCtrlFrame__8BtlModelFi7FVector
                        (chr(this,uVar18)->pModel,0x21,auStack_f0);
            }
            chr(this,uVar18)->bState2 = 5;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd | 2;
            iVar14 = rand();
            fVar25 = ((float)iVar14 / 2.1474836e+09) * 60.0;
          }
          break;
        case 5:
          iVar14 = GetTimer__7SysToolFv();
          if ((float)(uint)(iVar14 - iVar4) * 0.03 < 0.075) {
            CalcPushRange__7CBattleFi(this,lVar19);
            if (((chr(this,uVar18)->bFlagsB & 1) == 0) &&
               (chr(this,uVar18)->nCharId == 6)) {
              iVar14 = GetRegDat__9RegDatApiFiii(0x48,0,0xffffffffffffffff);
              if ((*(byte *)(iVar14 + *(short *)(iGpffff836c + 0x750) * 0x10 + 4) & 1) != 0) {
                SetOpticalCamouflage__8BtlModelFii
                          (chr(this,uVar18)->pModel,3,0xc);
              }
            }
            else if (((chr(this,uVar18)->bFlagsB & 1) != 0) &&
                    (*(byte *)(chr(this,uVar18)->pParam + 0x15) >> 5 == 1)) {
              SetOpticalCamouflage__8BtlModelFii
                        (chr(this,uVar18)->pModel,3,0xc);
            }
            chr(this,uVar18)->bState = 3;
            chr(this,uVar18)->bState2 = 0;
          }
        }
        break;
      case 3:
        *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
        break;
      case 4:
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x01') {
          if (chr(this,uVar18)->f2c == 0.0) {
            Reset__15ModelEffManagerFP5Model(chr(this,uVar18)->pModel);
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) + this->flDeltaT * 2.0;
          if (1.0 <= chr(this,uVar18)->f2c) {
            chr(this,uVar18)->f2c = 0x3f800000;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) =
                 chr(this,uVar18)->f2c;
            if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 2) {
              chr(this,uVar18)->bState = 6;
            }
            else {
              chr(this,uVar18)->bState = 7;
            }
            chr(this,uVar18)->bState2 = 0;
            uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
            __ct__7FVectorFRC7FVector(auStack_100,uVar10);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x160) = auStack_100._0_4_;
            *(int *)(iVar14 + 0x164) = auStack_100._4_4_;
            *(undefined4 *)(iVar14 + 0x168) = uStack_f8;
            *(undefined4 *)(iVar14 + 0x16c) = uStack_f4;
            __pl__7FVectorCFRC7FVector
                      (auStack_110,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_110._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_110._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_108;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_104;
            chr(this,uVar18)->fc4 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f2c = ((float)iVar14 / 2.1474836e+09) * 0.5;
          }
          else {
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) =
                 chr(this,uVar18)->f2c;
          }
        }
        else if (cVar3 == '\0') {
          if (((chr(this,uVar18)->bFlagsB & 1) == 0) &&
             (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e))) {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,2);
          }
          OTEntry__8BtlModelFii(chr(this,uVar18)->pModel,4,8);
          ShadowOn__8BtlModelFv(chr(this,uVar18)->pModel);
          Reset__15ModelEffManagerFP5Model(chr(this,uVar18)->pModel);
          chr(this,uVar18)->bState2 = 1;
          chr(this,uVar18)->f2c = 0;
        }
        break;
      case 5:
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x01') {
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) - this->flDeltaT;
          if (chr(this,uVar18)->f2c <= 0.0) {
            chr(this,uVar18)->f2c = 0;
            chr(this,uVar18)->bState = 0;
            chr(this,uVar18)->bState2 = 0;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
          }
          *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) =
               chr(this,uVar18)->f2c;
        }
        else if (cVar3 == '\0') {
          chr(this,uVar18)->bState2 = 1;
          chr(this,uVar18)->f2c = 0x3f800000;
        }
        break;
      case 6:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_120,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_120._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_120._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_118;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_114;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if ((cVar3 != '\0') ||
             (iVar14 = this + uVar18 * 0x510,
             *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) - this->flDeltaT,
             0.0 < chr(this,uVar18)->f2c)) break;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,3);
          chr(this,uVar18)->bState2 = 1;
          chr(this,uVar18)->f2c = 0;
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
          __pl__7FVectorCFRC7FVector
                    (auStack_130,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_130._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_130._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_128;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_124;
          chr(this,uVar18)->fc4 = 0;
        }
        break;
      case 7:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_140,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_140._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_140._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_138;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_134;
        if (((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x3a) < 0) &&
           ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x39) < 0)) {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xbf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
          if ((((this->cActor != lVar19) &&
               ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0)) &&
              ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x38) < 0)) &&
             ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                          0x3d) &&
              ((this->nPhase != 9 || (lVar19 != this->nCmd1)))))) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0x7f;
            fVar25 = 0.0;
          }
        }
        else if (cVar3 == '\x01') {
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 1) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,1);
          }
          chr(this,uVar18)->bState2 = 2;
        }
        else if (cVar3 == '\0') {
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 1) {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,1);
          }
          chr(this,uVar18)->bState2 = 2;
        }
        break;
      case 8:
      case 9:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_150,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_150._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_150._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_148;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_144;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          chr(this,uVar18)->bState2 = 1;
          if (chr(this,uVar18)->bState == '\b') {
            GetMoveAngle__7CBattleFi(this,lVar19);
            chr(this,uVar18)->f10 = 1;
          }
          *(undefined4 *)(this + uVar18 * 0x510 + 200) = 1;
          chr(this,uVar18)->f24 = 0;
          chr(this,uVar18)->f20 = 0;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb6) = *(byte *)(iVar14 + 0xb6) & 0xfd;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xfe;
          SetBtlMotion__8BtlModelFif(0x3f800000,chr(this,uVar18)->pModel,4);
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf | 0x40;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xf9;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f | 0x80;
          chr(this,uVar18)->f4dc = 0xff;
          chr(this,uVar18)->f4dd = 0;
          chr(this,uVar18)->f4de = 0xff;
          if (chr(this,uVar18)->f4c0 != -1) {
            __pl__7FVectorCFRC7FVector
                      (&uStack_160,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_158;
            auStack_10 = (undefined1  [8])uStack_160;
            uStack_8._4_4_ = uStack_154;
            uVar12 = PlaySEHold__6HNMSndFUibP7FVector(uGpffff8374,0x60002000,1,auStack_10);
            chr(this,uVar18)->f4cc = uVar12;
          }
        }
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0xd0) = *(int *)(iVar14 + 0xd0) + 1;
        bVar1 = false;
        __ct__7FVectorFffff(chr(this,uVar18)->f2c,0,
                            chr(this,uVar18)->f30,0x3f800000,&uStack_170);
        uStack_8._0_4_ = (float)uStack_168;
        auStack_10 = (undefined1  [8])uStack_170;
        uStack_8._4_4_ = uStack_164;
        if (chr(this,uVar18)->bState == '\b') {
          if (chr(this,uVar18)->f24 == 0) {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_180,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_190,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,0x40400000,0x42480000,this,lVar19,uVar10,
                               0xffffffffffffffff,uVar9);
            bVar1 = cVar3 == '\x01';
            chr(this,uVar18)->f24 = 1;
          }
          else {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_1a0,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_1b0,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,0x40400000,0,this,lVar19,uVar10,0xffffffffffffffff,
                               uVar9);
            if (cVar3 == '\x01') {
              bVar1 = true;
            }
          }
        }
        else {
          fVar23 = *(float *)(this + chr(this,uVar18)->fc * 0x510 + 0x354) +
                   chr(this,uVar18)->f2a4 + 6.0;
          if (chr(this,uVar18)->f10 == 0) {
            if (chr(this,uVar18)->f24 == 0) {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_200,this + uVar18 * 0x510 + 0x170);
              cVar3 = HomingMove__7CBattleFi7FVectorifff
                                (0x3f800000,fVar23,0x42480000,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc);
              bVar1 = cVar3 == '\x01';
              chr(this,uVar18)->f24 = 1;
            }
            else {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_210,this + uVar18 * 0x510 + 0x170);
              cVar3 = HomingMove__7CBattleFi7FVectorifff
                                (0x3f800000,fVar23,0,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc);
              if (cVar3 == '\x01') {
                bVar1 = true;
              }
            }
          }
          else if (chr(this,uVar18)->f24 == 0) {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_1c0,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_1d0,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,fVar23,0x42480000,this,lVar19,uVar10,
                               chr(this,uVar18)->fc,uVar9);
            bVar1 = cVar3 == '\x01';
            chr(this,uVar18)->f24 = 1;
          }
          else {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_1e0,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_1f0,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,fVar23,0,this,lVar19,uVar10,
                               chr(this,uVar18)->fc,uVar9);
            if (cVar3 == '\x01') {
              bVar1 = true;
            }
          }
        }
        if (bVar1) {
          cVar3 = chr(this,uVar18)->bState;
          if (chr(this,uVar18)->f28 == 0) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 1;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
          }
          else {
            chr(this,uVar18)->bState = 0x11;
            chr(this,uVar18)->bState2 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
          }
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f;
          __pl__7FVectorCFRC7FVector
                    (auStack_220,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_220._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_220._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_218;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_214;
          chr(this,uVar18)->fc4 = 0;
          if ((chr(this,uVar18)->f4c0 != -1) &&
             (chr(this,uVar18)->f4cc != -1)) {
            SetSEEnd__6HNMSndFUii(uGpffff8374,0x60002000,chr(this,uVar18)->f4cc)
            ;
          }
          chr(this,uVar18)->f4cc = 0xffffffff;
          CheckComboMenber__7CBattleFi(this,0);
          if ((cVar3 == '\t') && (*(int *)(this + 0x45cc) != 0)) {
            ComboAreaReset__9ComboFormFv(*(undefined4 *)(this + 0x45cc));
          }
        }
        else if (((chr(this,uVar18)->f4c0 != -1) &&
                 (chr(this,uVar18)->f4cc != -1)) &&
                ((chr(this,uVar18)->f20 & 1) != 0)) {
          __pl__7FVectorCFRC7FVector
                    (&uStack_230,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          uStack_8._0_4_ = (float)uStack_228;
          auStack_10 = (undefined1  [8])uStack_230;
          uStack_8._4_4_ = uStack_224;
          uVar10 = __ct__7FVectorFPC7FVector(auStack_240,auStack_10);
          SetSEParam__6HNMSndFUi7FVectori(uGpffff8374,0x60002000,uVar10,
                          chr(this,uVar18)->f4cc);
        }
        break;
      case 10:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_250,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_250._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_250._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_248;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_244;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x02') {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            cVar3 = Retail_CBattle_FindRemoteEffectPos
                              (chr(this,uVar18)->f2c,this,lVar19,
                               chr(this,uVar18)->fc,auStack_10);
            if (cVar3 == '\x01') {
              chr(this,uVar18)->f10 = 1;
            }
            else {
              chr(this,uVar18)->f10 = 0;
            }
            chr(this,uVar18)->f14 = 0;
            chr(this,uVar18)->f30 = auStack_10._0_4_;
            chr(this,uVar18)->f34 = (float)uStack_8;
            chr(this,uVar18)->bState2 = 1;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb6) = *(byte *)(iVar14 + 0xb6) & 0xfd;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xfe;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,4);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf | 0x40;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xf9;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f | 0x80;
            chr(this,uVar18)->f4dc = 0xff;
            chr(this,uVar18)->f4dd = 0;
            chr(this,uVar18)->f4de = 0xff;
          }
          __pl__7FVectorCFRC7FVector
                    (auStack_260,this + chr(this,uVar18)->fc * 0x510 + 0x160,
                     this + chr(this,uVar18)->fc * 0x510 + 0x360);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_260._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_260._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_258;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_254;
          chr(this,uVar18)->fc4 = 0;
          if ((chr(this,uVar18)->bFlagsB1 & 1) == 0) {
            fVar23 = chr(this,uVar18)->f2c +
                     chr(this,uVar18)->f2a4 +
                     (*(float *)(this + chr(this,uVar18)->fc * 0x510 + 0x370)
                     + *(float *)(this + chr(this,uVar18)->fc * 0x510 + 0x378)
                     ) / 2.0;
          }
          else {
            fVar23 = chr(this,uVar18)->f2c;
          }
          bVar1 = false;
          if (chr(this,uVar18)->f10 == 0) {
            if (chr(this,uVar18)->f14 == 0) {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_2c0,this + uVar18 * 0x510 + 0x170);
              cVar3 = HomingMove__7CBattleFi7FVectorifff
                                (0x3f800000,fVar23,0,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc);
              if (cVar3 == '\x01') {
                bVar1 = true;
              }
            }
            else {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_2d0,this + uVar18 * 0x510 + 0x170);
              cVar3 = HomingMove__7CBattleFi7FVectorifff
                                (0x3f800000,fVar23,0x41700000,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc);
              if (cVar3 == '\x01') {
                bVar1 = true;
              }
            }
          }
          else {
            __ct__7FVectorFffff(chr(this,uVar18)->f30,0,
                                chr(this,uVar18)->f34,0x3f800000,
                                &uStack_270);
            uStack_8._0_4_ = (float)uStack_268;
            auStack_10 = (undefined1  [8])uStack_270;
            uStack_8._4_4_ = uStack_264;
            if (chr(this,uVar18)->f14 == 0) {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_280,this + uVar18 * 0x510 + 0x170);
              uVar9 = __ct__7FVectorFPC7FVector(auStack_290,auStack_10);
              cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                                (0x3f800000,fVar23,0,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc,uVar9);
              if (cVar3 == '\x01') {
                bVar1 = true;
              }
            }
            else {
              uVar10 = __ct__7FVectorFPC7FVector(auStack_2a0,this + uVar18 * 0x510 + 0x170);
              uVar9 = __ct__7FVectorFPC7FVector(auStack_2b0,auStack_10);
              cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                                (0x3f800000,fVar23,0x41700000,this,lVar19,uVar10,
                                 chr(this,uVar18)->fc,uVar9);
              if (cVar3 == '\x01') {
                bVar1 = true;
              }
            }
          }
          chr(this,uVar18)->f14 = 0;
          if (bVar1) {
            chr(this,uVar18)->bState2 = 2;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f;
            if (chr(this,uVar18)->f10 == 0) {
              __mi__7FVectorCFRC7FVector
                        (auStack_2e0,this + uVar18 * 0x510 + 0x170,this + uVar18 * 0x510 + 0x3a0
                        );
              iVar14 = this + uVar18 * 0x510;
              *(int *)(iVar14 + 0x160) = auStack_2e0._0_4_;
              *(int *)(iVar14 + 0x164) = auStack_2e0._4_4_;
              *(undefined4 *)(iVar14 + 0x168) = uStack_2d8;
              *(undefined4 *)(iVar14 + 0x16c) = uStack_2d4;
              chr(this,uVar18)->fb4 = 0;
              SetPos__8BtlModelFP7FVector
                        (chr(this,uVar18)->pModel,
                         this + uVar18 * 0x510 + 0x160);
            }
            else {
              __pl__7FVectorCFRC7FVector
                        (auStack_2f0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              iVar14 = this + uVar18 * 0x510;
              *(int *)(iVar14 + 0x170) = auStack_2f0._0_4_;
              *(int *)(iVar14 + 0x174) = auStack_2f0._4_4_;
              *(undefined4 *)(iVar14 + 0x178) = uStack_2e8;
              *(undefined4 *)(iVar14 + 0x17c) = uStack_2e4;
              chr(this,uVar18)->fc4 = 0;
            }
          }
        }
        break;
      case 0xb:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_300,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_300._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_300._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_2f8;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_2f4;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if ((((chr(this,uVar18)->f10 == 0) &&
               (-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d))) &&
              (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x45)) &&
             (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0)
             , 0.5 <= unaff_f22)) {
            chr(this,uVar18)->f10 = 1;
            memset(auStack_e0,0,0x70);
            iVar14 = 0;
            while ((iVar14 < 0x20 &&
                   (((*(char *)(this + chr(this,uVar18)->fc * 0x510 +
                                iVar14 * 0xc + 0x1d0) != 'T' ||
                     (((ulong)*(byte *)(this + chr(this,uVar18)->fc * 0x510 +
                                        iVar14 * 0xc + 0x1cd) & 0x3f) >> 3 != 0)) ||
                    ((*(uint *)(this + chr(this,uVar18)->fc * 0x510 +
                                iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
              iVar14 = iVar14 + 1;
            }
            if (iVar14 < 0x20) {
              bStack_9a = bStack_9a & 0xfd | 2;
              __mi__7FVectorCFRC7FVector
                        (&uStack_3a0,this + uVar18 * 0x510 + 0x170,
                         this + chr(this,uVar18)->fc * 0x510 + 0x170);
              uStack_8._0_4_ = (float)uStack_398;
              auStack_10 = (undefined1  [8])uStack_3a0;
              uStack_8._4_4_ = uStack_394;
              auStack_10 = (undefined1  [8])(uStack_3a0 & 0xffffffff);
              Normalize__7FVectorFv(auStack_10);
              __amu__7FVectorFf(*(float *)(this + chr(this,uVar18)->fc * 0x510 +
                                        0x354) + 1.0,auStack_10);
              auVar27 = _lqc2(*(undefined1 (*) [16])
                               (this + chr(this,uVar18)->fc * 0x510 + 0x170));
              auVar26 = _lqc2(_auStack_10);
              auVar26 = _vadd(auVar26,auVar27);
              auVar26 = _sqc2(auVar26);
              uStack_8 = auVar26._8_8_;
              auStack_10._0_4_ = auVar26._0_4_;
              auStack_10._4_4_ = 0xc0000000;
              EffectMesCall__7CBattleFiP8ECResultP7FVectorb
                        (this,chr(this,uVar18)->fc,auStack_e0,
                         auStack_10,0,0);
            }
            else {
              if ((*(byte *)(this + chr(this,uVar18)->fc * 0x510 + 0xb4) & 1)
                  == 0) {
                iVar14 = this + chr(this,uVar18)->fc * 0x510;
                *(short *)(iVar14 + 0x13a) = *(short *)(iVar14 + 0x13a) + -1;
                uStack_d8 = 0xffff;
              }
              else {
                iVar14 = this + chr(this,uVar18)->fc * 0x510;
                *(int *)(iVar14 + 0x130) = *(int *)(iVar14 + 0x130) + -1;
                iVar14 = this + chr(this,uVar18)->fc * 0x510;
                *(int *)(iVar14 + 0x520) = *(int *)(iVar14 + 0x520) + 1;
                auStack_e0[0] = 0xffffffff;
              }
              SetTargetAngle__7CBattleFii
                        (this,chr(this,uVar18)->fc,lVar19);
              IdelMotionReset__Fi(chr(this,uVar18)->fc,0);
              __mi__7FVectorCFRC7FVector
                        (&uStack_3b0,this + uVar18 * 0x510 + 0x170,
                         this + chr(this,uVar18)->fc * 0x510 + 0x170);
              uStack_8._0_4_ = (float)uStack_3a8;
              auStack_10 = (undefined1  [8])uStack_3b0;
              uStack_8._4_4_ = uStack_3a4;
              auStack_10 = (undefined1  [8])(uStack_3b0 & 0xffffffff);
              Normalize__7FVectorFv(auStack_10);
              __amu__7FVectorFf(*(float *)(this + chr(this,uVar18)->fc * 0x510 +
                                        0x354) + 1.0,auStack_10);
              auVar27 = _lqc2(*(undefined1 (*) [16])
                               (this + chr(this,uVar18)->fc * 0x510 + 0x170));
              auVar26 = _lqc2(_auStack_10);
              auVar26 = _vadd(auVar26,auVar27);
              auVar26 = _sqc2(auVar26);
              uStack_8 = auVar26._8_8_;
              auStack_10._0_4_ = auVar26._0_4_;
              auStack_10._4_4_ = 0xc0000000;
              if ((*(byte *)(this + chr(this,uVar18)->fc * 0x510 + 0xb4) & 1)
                  == 0) {
                EffectMesCall__7CBattleFiP8ECResultP7FVectorb
                          (this,chr(this,uVar18)->fc,auStack_e0,
                           auStack_10,0,0);
              }
              else {
                EffectMesCall__7CBattleFiP8ECResultP7FVectorb
                          (this,chr(this,uVar18)->fc,auStack_e0,
                           auStack_10,1,0);
              }
              PlayVibration__7CBattleFi(this,5);
              __pl__7FVectorCFRC7FVector
                        (&uStack_3c0,
                         this + chr(this,uVar18)->fc * 0x510 + 0x160,
                         this + chr(this,uVar18)->fc * 0x510 + 0x3a0);
              uStack_8._0_4_ = (float)uStack_3b8;
              auStack_10 = (undefined1  [8])uStack_3c0;
              uStack_8._4_4_ = uStack_3b4;
              if (*(int *)(this + chr(this,uVar18)->fc * 0x510 + 0x130) < 1) {
                if (-1 < (long)((ulong)*(byte *)(this + chr(this,uVar18)->fc *
                                                          0x510 + 0xb2) << 0x3d)) {
                  iVar14 = this + chr(this,uVar18)->fc * 0x510;
                  *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0xfb | 4;
                  DeadReset__7CBattleFi(this,chr(this,uVar18)->fc);
                }
                if ((*(byte *)(this + chr(this,uVar18)->fc * 0x510 + 0xb4) & 1
                    ) == 0) {
                  *(undefined1 *)(this + chr(this,uVar18)->fc * 0x510 + 0xb8)
                       = 0x26;
                  *(undefined1 *)(this + chr(this,uVar18)->fc * 0x510 + 0xb9)
                       = 0;
                }
                else {
                  DeathInit__7CBattleFi(this,chr(this,uVar18)->fc);
                  cVar3 = *(char *)(this + chr(this,uVar18)->fc * 0x510 +
                                   0x1a3);
                  if (((cVar3 == '\x03') || (cVar3 == '\x02')) || (cVar3 == '\x01')) {
                    *(undefined1 *)
                     (this + chr(this,uVar18)->fc * 0x510 + 0xb8) = 0x26;
                    *(undefined1 *)
                     (this + chr(this,uVar18)->fc * 0x510 + 0xb9) = 0;
                  }
                  else {
                    PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000003,1,auStack_10);
                  }
                }
              }
              else {
                if (*(char *)(this + chr(this,uVar18)->fc * 0x510 + 0xb8) ==
                    '\x11') {
                  *(undefined4 *)(this + chr(this,uVar18)->fc * 0x510 + 0xbc)
                       = 1;
                }
                else {
                  *(undefined4 *)(this + chr(this,uVar18)->fc * 0x510 + 0xbc)
                       = 0;
                }
                *(undefined1 *)(this + chr(this,uVar18)->fc * 0x510 + 0xb8) =
                     0x18;
                *(undefined1 *)(this + chr(this,uVar18)->fc * 0x510 + 0xb9) =
                     0;
                iVar14 = rand();
                iVar14 = iVar14 % 3;
                if (iVar14 == 2) {
                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000002,1,auStack_10);
                }
                else if (iVar14 == 1) {
                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000001,1,auStack_10);
                }
                else if (iVar14 == 0) {
                  PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000000,1,auStack_10);
                }
              }
            }
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x45) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 2;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            chr(this,uVar18)->bState2 = 1;
            *(undefined4 *)(this + uVar18 * 0x510 + 200) = 1;
            chr(this,uVar18)->f20 = 0;
            chr(this,uVar18)->f24 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb6) = *(byte *)(iVar14 + 0xb6) & 0xfd;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xfe;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,4);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf | 0x40;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xf9;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f | 0x80;
            chr(this,uVar18)->f4dc = 0xff;
            chr(this,uVar18)->f4dd = 0;
            chr(this,uVar18)->f4de = 0xff;
            if (chr(this,uVar18)->f4c0 != -1) {
              __pl__7FVectorCFRC7FVector
                        (&uStack_310,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              uStack_8._0_4_ = (float)uStack_308;
              auStack_10 = (undefined1  [8])uStack_310;
              uStack_8._4_4_ = uStack_304;
              uVar12 = PlaySEHold__6HNMSndFUibP7FVector(uGpffff8374,0x60002000,1,auStack_10);
              chr(this,uVar18)->f4cc = uVar12;
            }
          }
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0xd0) = *(int *)(iVar14 + 0xd0) + 1;
          bVar1 = false;
          __ct__7FVectorFffff(chr(this,uVar18)->f2c,0,
                              chr(this,uVar18)->f30,0x3f800000,&uStack_320
                             );
          uStack_8._0_4_ = (float)uStack_318;
          auStack_10 = (undefined1  [8])uStack_320;
          uStack_8._4_4_ = uStack_314;
          if (chr(this,uVar18)->f24 == 0) {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_330,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_340,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,0x3f800000,0x42480000,this,lVar19,uVar10,
                               0xffffffffffffffff,uVar9);
            bVar1 = cVar3 == '\x01';
            chr(this,uVar18)->f24 = 1;
          }
          else {
            uVar10 = __ct__7FVectorFPC7FVector(auStack_350,this + uVar18 * 0x510 + 0x170);
            uVar9 = __ct__7FVectorFPC7FVector(auStack_360,auStack_10);
            cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                              (0x3f800000,0x3f800000,0,this,lVar19,uVar10,0xffffffffffffffff,
                               uVar9);
            if (cVar3 == '\x01') {
              bVar1 = true;
            }
          }
          if (bVar1) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f;
            __mi__7FVectorCFRC7FVector
                      (auStack_370,this + uVar18 * 0x510 + 0x170,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x160) = auStack_370._0_4_;
            *(int *)(iVar14 + 0x164) = auStack_370._4_4_;
            *(undefined4 *)(iVar14 + 0x168) = uStack_368;
            *(undefined4 *)(iVar14 + 0x16c) = uStack_364;
            chr(this,uVar18)->fb4 = 0;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            if ((chr(this,uVar18)->f4c0 != -1) &&
               (chr(this,uVar18)->f4cc != -1)) {
              SetSEEnd__6HNMSndFUii(uGpffff8374,0x60002000,
                              chr(this,uVar18)->f4cc);
            }
            chr(this,uVar18)->f4cc = 0xffffffff;
            chr(this,uVar18)->bState2 = 2;
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x45);
            chr(this,uVar18)->f10 = 0;
          }
          else if (((chr(this,uVar18)->f4c0 != -1) &&
                   (chr(this,uVar18)->f4cc != -1)) &&
                  ((chr(this,uVar18)->f20 & 1) != 0)) {
            __pl__7FVectorCFRC7FVector
                      (&uStack_380,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_378;
            auStack_10 = (undefined1  [8])uStack_380;
            uStack_8._4_4_ = uStack_374;
            uVar10 = __ct__7FVectorFPC7FVector(auStack_390,auStack_10);
            SetSEParam__6HNMSndFUi7FVectori(uGpffff8374,0x60002000,uVar10,
                            chr(this,uVar18)->f4cc);
          }
        }
        break;
      case 0xc:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_3d0,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_3d0._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_3d0._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_3c8;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_3c4;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 2;
            if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3a)) {
              __pl__7FVectorCFRC7FVector
                        (auStack_3e0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              iVar14 = this + uVar18 * 0x510;
              *(int *)(iVar14 + 0x170) = auStack_3e0._0_4_;
              *(int *)(iVar14 + 0x174) = auStack_3e0._4_4_;
              *(undefined4 *)(iVar14 + 0x178) = uStack_3d8;
              *(undefined4 *)(iVar14 + 0x17c) = uStack_3d4;
              chr(this,uVar18)->fc4 = 0;
            }
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x38);
            chr(this,uVar18)->bState2 = 1;
          }
          if ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                          0x3d)) &&
             (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x39)) {
            chr(this,uVar18)->bState2 = 2;
          }
        }
        break;
      case 0xd:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_3f0,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_3f0._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_3f0._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_3e8;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_3e4;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 2;
            if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3a)) {
              __pl__7FVectorCFRC7FVector
                        (auStack_400,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              iVar14 = this + uVar18 * 0x510;
              *(int *)(iVar14 + 0x170) = auStack_400._0_4_;
              *(int *)(iVar14 + 0x174) = auStack_400._4_4_;
              *(undefined4 *)(iVar14 + 0x178) = uStack_3f8;
              *(undefined4 *)(iVar14 + 0x17c) = uStack_3f4;
              chr(this,uVar18)->fc4 = 0;
            }
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x33);
            chr(this,uVar18)->bState2 = 1;
          }
          if ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                          0x3d)) &&
             (*(short *)(chr(this,uVar18)->pModel + 0x510) == 2)) {
            chr(this,uVar18)->bState2 = 2;
          }
        }
        break;
      case 0xe:
      case 0xf:
        Retail_BtlChrSequence_State0E0F(0x3f800000,this,lVar19);
        break;
      case 0x10:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_410,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_410._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_410._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_408;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_404;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if (((*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) &&
              (chr(this,uVar18)->f4b4 == 0)) &&
             (chr(this,uVar18)->f4b0 == 0)) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 1;
            if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3a)) {
              __pl__7FVectorCFRC7FVector
                        (auStack_420,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              iVar14 = this + uVar18 * 0x510;
              *(int *)(iVar14 + 0x170) = auStack_420._0_4_;
              *(int *)(iVar14 + 0x174) = auStack_420._4_4_;
              *(undefined4 *)(iVar14 + 0x178) = uStack_418;
              *(undefined4 *)(iVar14 + 0x17c) = uStack_414;
              chr(this,uVar18)->fc4 = 0;
            }
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x30);
            chr(this,uVar18)->bState2 = 1;
            MagicStartEffectCall__Fi(lVar19);
            if (this->nComboCnt != 0) {
              SetBattleBlear__11CBtlPAfter2Fifff
                        (0x3f800000,0x3f89999a,0x3f000000,uGpffff8618,lVar19);
            }
          }
          if ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                          0x3d)) &&
             (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x31)) {
            chr(this,uVar18)->bState2 = 2;
          }
        }
        break;
      case 0x11:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_430,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_430._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_430._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_428;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_424;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x22) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x22);
          }
          chr(this,uVar18)->bState2 = 1;
        }
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        if (((this->cActor != lVar19) &&
            (fVar23 = fVar25, (long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0))
           && (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x38) < 0 &&
               (-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d))))) {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0x7f;
          fVar23 = 0.0;
        }
        fVar25 = fVar23;
        if (((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x3a) < 0) &&
           ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x39) < 0)) {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xbf;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
        }
        break;
      case 0x12:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x23);
          chr(this,uVar18)->bState2 = 1;
          iVar21 = (int)(((float)(int)chr(this,uVar18)->f45c * 30.0) / 100.0 +
                        0.5);
          iVar8 = 0;
          iVar14 = 1;
          if (chr(this,uVar18)->nMonId != 499) {
            for (; iVar14 < iVar21; iVar14 = iVar14 + 1) {
              iVar8 = iVar8 + iVar14;
            }
          }
          if (iVar8 == 0) {
            unaff_f22 = 0.0;
            fVar23 = 0.0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe | 1;
          }
          else {
            unaff_f22 = (((float)(int)chr(this,uVar18)->f45e / 12.0) *
                        (float)iVar21) / (float)iVar8;
            fVar23 = ((float)-(int)chr(this,uVar18)->f45e / 12.0) /
                     (float)iVar8;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe;
          }
          MoveWorkInit__7CBattleFiffff(unaff_f22,fVar23,0,0,this,lVar19);
          chr(this,uVar18)->f64 = 0;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        else {
          if (((chr(this,uVar18)->f454 & 1) == 0) &&
             (MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19),
             0.0 < chr(this,uVar18)->f2c)) {
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_440);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_450,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_448;
            auStack_10 = (undefined1  [8])uStack_450;
            uStack_8._4_4_ = uStack_444;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_450;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_448;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            __pl__7FVectorCFRC7FVector
                      (auStack_460,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_460._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_460._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_458;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_454;
            chr(this,uVar18)->fc4 = 0;
          }
          if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d)) &&
              (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x23)) &&
             (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0)
             , 0.5 <= unaff_f22)) {
            BtlEffAllEndSet__7CBattleFi(this,lVar19);
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x22) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x3a) < 0) {
              chr(this,uVar18)->bState = 7;
              chr(this,uVar18)->bState2 = 1;
              if ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x39) < 0) {
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf;
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xbf;
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
              }
            }
            else {
              chr(this,uVar18)->bState = 0x11;
              chr(this,uVar18)->bState2 = 0;
            }
          }
        }
        break;
      case 0x13:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x24);
          chr(this,uVar18)->bState2 = 1;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        else {
          if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d)) &&
              (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x24)) &&
             (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0)
             , 0.5 <= unaff_f22)) {
            BtlEffAllEndSet__7CBattleFi(this,lVar19);
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x22) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x3a) < 0) {
              chr(this,uVar18)->bState = 7;
              chr(this,uVar18)->bState2 = 1;
              if ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x39) < 0) {
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf;
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xbf;
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
              }
            }
            else {
              chr(this,uVar18)->bState = 0x11;
              chr(this,uVar18)->bState2 = 0;
            }
          }
        }
        break;
      case 0x14:
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_470,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_470._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_470._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_468;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_464;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
          __pl__7FVectorCFRC7FVector
                    (&uStack_4f0,this + chr(this,uVar18)->f10 * 0x510 + 0x160,
                     this + chr(this,uVar18)->f10 * 0x510 + 0x360);
          uStack_8._0_4_ = (float)uStack_4e8;
          auStack_10 = (undefined1  [8])uStack_4f0;
          uStack_8._4_4_ = uStack_4e4;
          __pl__7FVectorCFRC7FVector
                    (auStack_500,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x360);
          auVar27 = _lqc2(auStack_500);
          auVar26 = _lqc2(_auStack_10);
          auVar26 = _vsub(auVar26,auVar27);
          _auStack_10 = _sqc2(auVar26);
          uVar10 = __ct__7FVectorFPC7FVector(auStack_520,auStack_10);
          Get3DAngle__F7FVector(auStack_510,uVar10);
          fStack_30 = auStack_510._0_4_;
          fStack_2c = auStack_510._4_4_;
          uStack_28 = uStack_508;
          uStack_24 = uStack_504;
          for (fVar23 = (180.0 - fStack_2c) - chr(this,uVar18)->fd4;
              fVar23 < -180.0; fVar23 = fVar23 + 360.0) {
          }
          for (; 180.0 < fVar23; fVar23 = fVar23 - 360.0) {
          }
          if (this->flDeltaT == 0.0) {
            unaff_f22 = 0.0;
          }
          else {
            unaff_f22 = fVar23 * ((this->flDeltaT * 30.0) / 6.0);
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x184) = *(float *)(iVar14 + 0x184) + unaff_f22;
          SetAngle__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x180);
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            chr(this,uVar18)->bState2 = 1;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb6) = *(byte *)(iVar14 + 0xb6) & 0xfd;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xfe;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,4);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf | 0x40;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xf9;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f | 0x80;
            chr(this,uVar18)->f4dc = 0xff;
            chr(this,uVar18)->f4dd = 0;
            chr(this,uVar18)->f4de = 0xff;
            chr(this,uVar18)->f20 = 0;
            if (chr(this,uVar18)->f4c0 != -1) {
              __pl__7FVectorCFRC7FVector
                        (&uStack_480,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              uStack_8._0_4_ = (float)uStack_478;
              auStack_10 = (undefined1  [8])uStack_480;
              uStack_8._4_4_ = uStack_474;
              uVar12 = PlaySEHold__6HNMSndFUibP7FVector(uGpffff8374,0x60002000,1,auStack_10);
              chr(this,uVar18)->f4cc = uVar12;
            }
            if (((-1 < chr(this,uVar18)->f4e6) &&
                (-1 < chr(this,uVar18)->f4d9)) &&
               (*(char *)(this + chr(this,uVar18)->f4d9 * 0x18 + 0x40c5) ==
                '\x03')) {
              *(undefined1 *)(this + chr(this,uVar18)->f4d9 * 0x18 + 0x40c5) =
                   0xb;
              *(undefined2 *)(this + chr(this,uVar18)->f4d9 * 0x18 + 0x40d8) =
                   chr(this,this->nCmd0_target)->nCharId;
            }
          }
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0xd0) = *(int *)(iVar14 + 0xd0) + 1;
          __ct__7FVectorFffff(chr(this,uVar18)->f2c,0,
                              chr(this,uVar18)->f30,0x3f800000,&uStack_490
                             );
          uStack_8._0_4_ = (float)uStack_488;
          auStack_10 = (undefined1  [8])uStack_490;
          uStack_8._4_4_ = uStack_484;
          uVar10 = __ct__7FVectorFPC7FVector(auStack_4a0,this + uVar18 * 0x510 + 0x170);
          uVar9 = __ct__7FVectorFPC7FVector(auStack_4b0,auStack_10);
          cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                            (0x3f800000,0x40400000,0,this,lVar19,uVar10,
                             chr(this,uVar18)->fc,uVar9);
          if (cVar3 == '\x01') {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f;
            __mi__7FVectorCFRC7FVector
                      (auStack_4c0,this + uVar18 * 0x510 + 0x170,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x160) = auStack_4c0._0_4_;
            *(int *)(iVar14 + 0x164) = auStack_4c0._4_4_;
            *(undefined4 *)(iVar14 + 0x168) = uStack_4b8;
            *(undefined4 *)(iVar14 + 0x16c) = uStack_4b4;
            chr(this,uVar18)->fb4 = 0;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            if ((chr(this,uVar18)->f4c0 != -1) &&
               (chr(this,uVar18)->f4cc != -1)) {
              SetSEEnd__6HNMSndFUii(uGpffff8374,0x60002000,
                              chr(this,uVar18)->f4cc);
            }
            chr(this,uVar18)->f4cc = 0xffffffff;
            if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x22) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(this,uVar18)->pModel,0x22);
            }
            chr(this,uVar18)->bState2 = 2;
          }
          else if (((chr(this,uVar18)->f4c0 != -1) &&
                   (chr(this,uVar18)->f4cc != -1)) &&
                  ((chr(this,uVar18)->f20 & 1) != 0)) {
            __pl__7FVectorCFRC7FVector
                      (&uStack_4d0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_4c8;
            auStack_10 = (undefined1  [8])uStack_4d0;
            uStack_8._4_4_ = uStack_4c4;
            uVar10 = __ct__7FVectorFPC7FVector(auStack_4e0,auStack_10);
            SetSEParam__6HNMSndFUi7FVectori(uGpffff8374,0x60002000,uVar10,
                            chr(this,uVar18)->f4cc);
          }
        }
        break;
      case 0x15:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x24);
          chr(this,uVar18)->bState2 = 1;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        else {
          if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d)) &&
              (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x24)) &&
             (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0)
             , 0.5 <= unaff_f22)) {
            BtlEffAllEndSet__7CBattleFi(this,lVar19);
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x22) {
            chr(this,uVar18)->bState = 0x14;
            chr(this,uVar18)->bState2 = 2;
          }
        }
        break;
      case 0x16:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x2f);
          chr(this,uVar18)->bState2 = 1;
          chr(this,uVar18)->fc = 0;
        }
        if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                         0x3d)) &&
            (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x2f)) &&
           (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
           chr(this,uVar18)->fc == 0)) {
          bVar1 = false;
          if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
            switch(chr(this,uVar18)->fa) {
            default:
              if (0.475 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_6e0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_6d8;
                auStack_10 = (undefined1  [8])uStack_6e0;
                uStack_8._4_4_ = uStack_6d4;
                bVar1 = true;
              }
              break;
            case 1:
            case 2:
              if (0.515 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7008);
                getWorldPos__5FrameFi(&uStack_640,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_638;
                auStack_10 = (undefined1  [8])uStack_640;
                uStack_8._4_4_ = uStack_634;
                bVar1 = true;
              }
              break;
            case 4:
            case 5:
              if (0.5 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7000);
                getWorldPos__5FrameFi(&uStack_650,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_648;
                auStack_10 = (undefined1  [8])uStack_650;
                uStack_8._4_4_ = uStack_644;
                bVar1 = true;
              }
              break;
            case 7:
            case 8:
              if (0.425 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_660,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_658;
                auStack_10 = (undefined1  [8])uStack_660;
                uStack_8._4_4_ = uStack_654;
                bVar1 = true;
              }
              break;
            case 10:
            case 0xb:
              if (0.525 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7000);
                getWorldPos__5FrameFi(&uStack_670,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_668;
                auStack_10 = (undefined1  [8])uStack_670;
                uStack_8._4_4_ = uStack_664;
                bVar1 = true;
              }
              break;
            case 0xd:
            case 0xe:
              if (0.4 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_680,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_678;
                auStack_10 = (undefined1  [8])uStack_680;
                uStack_8._4_4_ = uStack_674;
                bVar1 = true;
              }
              break;
            case 0x10:
            case 0x11:
              if (0.525 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7008);
                getWorldPos__5FrameFi(&uStack_690,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_688;
                auStack_10 = (undefined1  [8])uStack_690;
                uStack_8._4_4_ = uStack_684;
                bVar1 = true;
              }
              break;
            case 0x12:
            case 0x13:
              if (0.5 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_6a0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_698;
                auStack_10 = (undefined1  [8])uStack_6a0;
                uStack_8._4_4_ = uStack_694;
                bVar1 = true;
              }
              break;
            case 0x14:
              if (0.49 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7008);
                getWorldPos__5FrameFi(&uStack_6b0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_6a8;
                auStack_10 = (undefined1  [8])uStack_6b0;
                uStack_8._4_4_ = uStack_6a4;
                bVar1 = true;
              }
              break;
            case 0x15:
              if (0.38 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_6c0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_6b8;
                auStack_10 = (undefined1  [8])uStack_6c0;
                uStack_8._4_4_ = uStack_6b4;
                bVar1 = true;
              }
              break;
            case 0x16:
              if (0.6 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_6d0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_6c8;
                auStack_10 = (undefined1  [8])uStack_6d0;
                uStack_8._4_4_ = uStack_6c4;
                bVar1 = true;
              }
            }
          }
          else {
            switch(chr(this,uVar18)->nCharId) {
            default:
              if (0.475 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_630,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_628;
                auStack_10 = (undefined1  [8])uStack_630;
                uStack_8._4_4_ = uStack_624;
                bVar1 = true;
              }
              break;
            case 1:
              if (0.4 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7000);
                getWorldPos__5FrameFi(&uStack_530,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_528;
                auStack_10 = (undefined1  [8])uStack_530;
                uStack_8._4_4_ = uStack_524;
                bVar1 = true;
              }
              break;
            case 2:
              if (0.6 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (*(int *)(chr(this,uVar18)->pModel +
                                                   0x544) + 0x30),0x6e7008);
                getWorldPos__5FrameFi(&uStack_540,
                                *(int *)(*(int *)(chr(this,uVar18)->pModel + 0x544)
                                        + 0x30) + iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_538;
                auStack_10 = (undefined1  [8])uStack_540;
                uStack_8._4_4_ = uStack_534;
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (*(int *)(chr(this,uVar18)->pModel +
                                                   0x544) + 0x30),0x6e7010);
                getWorldPos__5FrameFi(auStack_550,
                                *(int *)(*(int *)(chr(this,uVar18)->pModel + 0x544)
                                        + 0x30) + iVar14 * 0x1f0,bGpffff8240 & 1);
                auVar27 = _lqc2(auStack_550);
                auVar26 = _lqc2(_auStack_10);
                auVar26 = _vadd(auVar26,auVar27);
                _auStack_10 = _sqc2(auVar26);
                __adv__7FVectorFf(0x40000000,auStack_10);
                bVar1 = true;
              }
              break;
            case 3:
              if (0.45 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_560,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_558;
                auStack_10 = (undefined1  [8])uStack_560;
                uStack_8._4_4_ = uStack_554;
                bVar1 = true;
              }
              break;
            case 4:
              if (0.375 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_570,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_568;
                auStack_10 = (undefined1  [8])uStack_570;
                uStack_8._4_4_ = uStack_564;
                bVar1 = true;
              }
              break;
            case 5:
              if (0.55 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_580,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_578;
                auStack_10 = (undefined1  [8])uStack_580;
                uStack_8._4_4_ = uStack_574;
                bVar1 = true;
              }
              break;
            case 6:
              if (*(short *)(iGpffff836c + 0x750) == 1) {
                if (0.4 <= unaff_f22) {
                  iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                            (chr(this,uVar18)->pModel + 0x30),
                                           0x6e7008);
                  getWorldPos__5FrameFi(&uStack_5a0,
                                  *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                  iVar14 * 0x1f0,bGpffff8240 & 1);
                  uStack_8._0_4_ = (float)uStack_598;
                  auStack_10 = (undefined1  [8])uStack_5a0;
                  uStack_8._4_4_ = uStack_594;
                  iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                            (chr(this,uVar18)->pModel + 0x30),
                                           0x6e7010);
                  getWorldPos__5FrameFi(auStack_5b0,
                                  *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                  iVar14 * 0x1f0,bGpffff8240 & 1);
                  auVar27 = _lqc2(auStack_5b0);
                  auVar26 = _lqc2(_auStack_10);
                  auVar26 = _vadd(auVar26,auVar27);
                  _auStack_10 = _sqc2(auVar26);
                  __adv__7FVectorFf(0x40000000,auStack_10);
                  bVar1 = true;
                }
              }
              else if (0.435 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_590,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_588;
                auStack_10 = (undefined1  [8])uStack_590;
                uStack_8._4_4_ = uStack_584;
                bVar1 = true;
              }
              break;
            case 7:
              if (0.5 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_5c0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_5b8;
                auStack_10 = (undefined1  [8])uStack_5c0;
                uStack_8._4_4_ = uStack_5b4;
                bVar1 = true;
              }
              break;
            case 8:
              if (0.465 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_5d0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_5c8;
                auStack_10 = (undefined1  [8])uStack_5d0;
                uStack_8._4_4_ = uStack_5c4;
                bVar1 = true;
              }
              break;
            case 9:
              if (0.4 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_5e0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_5d8;
                auStack_10 = (undefined1  [8])uStack_5e0;
                uStack_8._4_4_ = uStack_5d4;
                bVar1 = true;
              }
              break;
            case 10:
              if (0.5 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7008);
                getWorldPos__5FrameFi(&uStack_5f0,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_5e8;
                auStack_10 = (undefined1  [8])uStack_5f0;
                uStack_8._4_4_ = uStack_5e4;
                bVar1 = true;
              }
              break;
            case 0xb:
              if (0.35 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_600,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_5f8;
                auStack_10 = (undefined1  [8])uStack_600;
                uStack_8._4_4_ = uStack_5f4;
                bVar1 = true;
              }
              break;
            case 0xc:
              if (0.5 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_610,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_608;
                auStack_10 = (undefined1  [8])uStack_610;
                uStack_8._4_4_ = uStack_604;
                bVar1 = true;
              }
              break;
            case 0xd:
              if (0.4 <= unaff_f22) {
                iVar14 = searchFrameIndex__5FrameFPCc(*(undefined4 *)
                                          (chr(this,uVar18)->pModel + 0x30),
                                         0x6e7010);
                getWorldPos__5FrameFi(&uStack_620,
                                *(int *)(chr(this,uVar18)->pModel + 0x30) +
                                iVar14 * 0x1f0,bGpffff8240 & 1);
                uStack_8._0_4_ = (float)uStack_618;
                auStack_10 = (undefined1  [8])uStack_620;
                uStack_8._4_4_ = uStack_614;
                bVar1 = true;
              }
            }
          }
          if (bVar1) {
            if (this->nPhase == 0xd) {
              lVar11 = __nw__FUi(0x150);
              uVar12 = 0;
              if (lVar11 != 0) {
                uVar10 = __ct__7FVectorFPC7FVector(auStack_6f0,auStack_10);
                uVar12 = __ct__13BtlTarotSelectFv
                                   (lVar11,0,lVar19,uVar10,this->nCmd1);
              }
              chr(this,uVar18)->f4b0 = uVar12;
            }
            else {
              lVar19 = __nw__FUi(0x5e0);
              uVar10 = 0;
              if (lVar19 != 0) {
                uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),10);
                uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0xb);
                uVar10 = __ct__6EffMdlFPUcPUcfii
                                   (0x3f800000,lVar19,uVar10,uVar9,0xffffffffffffffff,0);
              }
              setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
              SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
              OTEntry__6EffMdlFii(uVar10,4,8);
              __pl__7FVectorCFRC7FVector
                        (&uStack_700,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0
                        );
              uStack_8._0_4_ = (float)uStack_6f8;
              auStack_10 = (undefined1  [8])uStack_700;
              uStack_8._4_4_ = uStack_6f4;
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2002005,1,auStack_10);
            }
            chr(this,uVar18)->fc = 1;
          }
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
        }
        break;
      case 0x17:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_710,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_710._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_710._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_708;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_704;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          unaff_f22 = 1.0;
          if (chr(this,uVar18)->nMonId != 499) {
            unaff_f22 = ((float)(int)chr(this,uVar18)->f45e / 100.0) / 1.5;
          }
          SetBtlMotion__8BtlModelFif
                    (unaff_f22,chr(this,uVar18)->pModel,0x25);
          chr(this,uVar18)->bState2 = 1;
        }
        __pl__7FVectorCFRC7FVector
                  (auStack_720,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_720._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_720._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_718;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_714;
        chr(this,uVar18)->fc4 = 0;
        if ((*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) &&
           (chr(this,uVar18)->f458 != *(int *)(this + 0x40))) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
        }
        break;
      case 0x18:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x26);
          chr(this,uVar18)->bState2 = 1;
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
          if (chr(this,uVar18)->fc == 0) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 1;
          }
          else {
            chr(this,uVar18)->bState = 0x11;
            chr(this,uVar18)->bState2 = 0;
          }
          if (chr(this,uVar18)->f454 >> 5 == 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xef;
            chr(this,uVar18)->f460 = 0;
            chr(this,uVar18)->f464 = 0;
            chr(this,uVar18)->f468 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f46c =
                 ((float)iVar14 / 2.1474836e+09) * 0.05 + 0.975;
            chr(this,uVar18)->f470 = 0;
            chr(this,uVar18)->f474 = 0;
            chr(this,uVar18)->f478 = 0;
            chr(this,uVar18)->f47c = 0;
            chr(this,uVar18)->f480 = 0;
            chr(this,uVar18)->f484 = 0;
            chr(this,uVar18)->f48e = 0;
          }
        }
        break;
      case 0x19:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x26);
          chr(this,uVar18)->bState2 = 1;
          iVar21 = (int)(((float)(int)chr(this,uVar18)->f45c * 30.0) / 100.0 +
                        0.5);
          iVar8 = 0;
          iVar14 = 1;
          if (chr(this,uVar18)->nMonId != 499) {
            for (; iVar14 < iVar21; iVar14 = iVar14 + 1) {
              iVar8 = iVar8 + iVar14;
            }
          }
          if (iVar8 == 0) {
            unaff_f22 = 0.0;
            MoveWorkInit__7CBattleFiffff(0,0,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe | 1;
          }
          else {
            unaff_f22 = (((float)(int)chr(this,uVar18)->f45e / 10.0) *
                        (float)iVar21) / (float)iVar8;
            MoveWorkInit__7CBattleFiffff
                      (unaff_f22,
                       ((float)-(int)chr(this,uVar18)->f45e / 10.0) /
                       (float)iVar8,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe;
          }
          chr(this,uVar18)->f64 = 0;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          if (((chr(this,uVar18)->f454 & 1) == 0) &&
             (MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19),
             0.0 < chr(this,uVar18)->f2c)) {
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_730);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_740,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_738;
            auStack_10 = (undefined1  [8])uStack_740;
            uStack_8._4_4_ = uStack_734;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_740;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_738;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            __pl__7FVectorCFRC7FVector
                      (auStack_750,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_750._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_750._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_748;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_744;
            chr(this,uVar18)->fc4 = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          fVar25 = fVar23;
        }
        if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                         0x3d)) &&
            (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x26)) &&
           (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
           0.5 <= unaff_f22)) {
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
        }
        if ((*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) &&
           (chr(this,uVar18)->f458 != *(int *)(this + 0x40))) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
          MaxHitFunc__7CBattleFi(this,lVar19);
          if (chr(this,uVar18)->f454 >> 5 == 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xef;
            chr(this,uVar18)->f460 = 0;
            chr(this,uVar18)->f464 = 0;
            chr(this,uVar18)->f468 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f46c =
                 ((float)iVar14 / 2.1474836e+09) * 0.05 + 0.975;
            chr(this,uVar18)->f470 = 0;
            chr(this,uVar18)->f474 = 0;
            chr(this,uVar18)->f478 = 0;
            chr(this,uVar18)->f47c = 0;
            chr(this,uVar18)->f480 = 0;
            chr(this,uVar18)->f484 = 0;
            chr(this,uVar18)->f48e = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf | 0x20;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          if (((uint)this->wChrMask & 1 << (uVar18 & 0x1f)) != 0) {
            this->wChrMask =
                 this->wChrMask - (short)(1 << (uVar18 & 0x1f));
          }
        }
        break;
      case 0x1a:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x27);
          chr(this,uVar18)->bState2 = 1;
          iVar21 = (int)(((float)(int)chr(this,uVar18)->f45c * 30.0) / 100.0 +
                        0.5);
          iVar8 = 0;
          iVar14 = 1;
          if (chr(this,uVar18)->nMonId != 499) {
            for (; iVar14 < iVar21; iVar14 = iVar14 + 1) {
              iVar8 = iVar8 + iVar14;
            }
          }
          if (iVar8 == 0) {
            unaff_f22 = 0.0;
            MoveWorkInit__7CBattleFiffff(0,0,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe | 1;
          }
          else {
            unaff_f22 = (((float)(int)chr(this,uVar18)->f45e / 10.0) *
                        (float)iVar21) / (float)iVar8;
            MoveWorkInit__7CBattleFiffff
                      (unaff_f22,
                       ((float)-(int)chr(this,uVar18)->f45e / 10.0) /
                       (float)iVar8,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe;
          }
          chr(this,uVar18)->f64 = 0;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          if (((chr(this,uVar18)->f454 & 1) == 0) &&
             (MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19),
             0.0 < chr(this,uVar18)->f2c)) {
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_760);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_770,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_768;
            auStack_10 = (undefined1  [8])uStack_770;
            uStack_8._4_4_ = uStack_764;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_770;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_768;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            __pl__7FVectorCFRC7FVector
                      (auStack_780,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_780._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_780._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_778;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_774;
            chr(this,uVar18)->fc4 = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          fVar25 = fVar23;
        }
        if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                         0x3d)) &&
            (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x27)) &&
           (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
           0.5 <= unaff_f22)) {
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
        }
        if ((*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) &&
           (chr(this,uVar18)->f458 != *(int *)(this + 0x40))) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
          MaxHitFunc__7CBattleFi(this,lVar19);
          if (chr(this,uVar18)->f454 >> 5 == 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xef;
            chr(this,uVar18)->f460 = 0;
            chr(this,uVar18)->f464 = 0;
            chr(this,uVar18)->f468 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f46c =
                 ((float)iVar14 / 2.1474836e+09) * 0.05 + 0.975;
            chr(this,uVar18)->f470 = 0;
            chr(this,uVar18)->f474 = 0;
            chr(this,uVar18)->f478 = 0;
            chr(this,uVar18)->f47c = 0;
            chr(this,uVar18)->f480 = 0;
            chr(this,uVar18)->f484 = 0;
            chr(this,uVar18)->f48e = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf | 0x20;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          if (((uint)this->wChrMask & 1 << (uVar18 & 0x1f)) != 0) {
            this->wChrMask =
                 this->wChrMask - (short)(1 << (uVar18 & 0x1f));
          }
        }
        break;
      case 0x1b:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x26);
          chr(this,uVar18)->bState2 = 1;
          if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
              uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) &
                              0x3f) >> 3);
            }
            else {
              uVar17 = (uint)(*(byte *)(iGpffff83b4 +
                                        chr(this,uVar18)->fa * 0xc0 + 0x3c) >>
                             5);
            }
          }
          else {
            uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) &
                            0x3f) >> 3);
          }
          switch(uVar17) {
          case 0:
            unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
            uVar12 = 0xbd99999a;
            break;
          default:
            unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
            uVar12 = 0xbdcccccd;
            break;
          case 2:
            unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
            uVar12 = 0xbe000000;
            break;
          case 3:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
              uVar12 = 0xbd99999a;
            }
            else {
              unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
              uVar12 = 0xbdcccccd;
            }
            break;
          case 5:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
              uVar12 = 0xbe000000;
            }
            else {
              unaff_f22 = (float)(int)chr(this,uVar18)->f45e * 0.024;
              uVar12 = 0xbdcccccd;
            }
          }
          if (0.0 < unaff_f22) {
            MoveWorkInit__7CBattleFiffff(unaff_f22,uVar12,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe;
          }
          else {
            MoveWorkInit__7CBattleFiffff(0,0,0,0,this,lVar19);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xfe | 1;
          }
          chr(this,uVar18)->f64 = 0;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          if (((chr(this,uVar18)->f454 & 1) == 0) &&
             (MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19),
             0.0 < chr(this,uVar18)->f2c)) {
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_790);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_7a0,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_798;
            auStack_10 = (undefined1  [8])uStack_7a0;
            uStack_8._4_4_ = uStack_794;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_7a0;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_798;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            __pl__7FVectorCFRC7FVector
                      (auStack_7b0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_7b0._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_7b0._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_7a8;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_7a4;
            chr(this,uVar18)->fc4 = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          fVar25 = fVar23;
        }
        if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                         0x3d)) &&
            (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x26)) &&
           (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
           0.5 <= unaff_f22)) {
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 1) {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 1;
          MaxHitFunc__7CBattleFi(this,lVar19);
          if (chr(this,uVar18)->f454 >> 5 == 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xef;
            chr(this,uVar18)->f460 = 0;
            chr(this,uVar18)->f464 = 0;
            chr(this,uVar18)->f468 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f46c =
                 ((float)iVar14 / 2.1474836e+09) * 0.05 + 0.975;
            chr(this,uVar18)->f470 = 0;
            chr(this,uVar18)->f474 = 0;
            chr(this,uVar18)->f478 = 0;
            chr(this,uVar18)->f47c = 0;
            chr(this,uVar18)->f480 = 0;
            chr(this,uVar18)->f484 = 0;
            chr(this,uVar18)->f48e = 0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf | 0x20;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          if (((uint)this->wChrMask & 1 << (uVar18 & 0x1f)) != 0) {
            this->wChrMask =
                 this->wChrMask - (short)(1 << (uVar18 & 0x1f));
          }
        }
        break;
      case 0x1c:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if ((((ulong)chr(this,uVar18)->bFlagsB & 7) >> 1 != 0) ||
             (chr(this,uVar18)->fb4 < 0.0)) {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x29);
          }
          else {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x26);
          }
          chr(this,uVar18)->bState2 = 1;
          chr(this,uVar18)->f64 = 0;
          lVar11 = __nw__FUi(0x6c);
          if (lVar11 != 0) {
            __ct__17FrictionSmokeCallFii(lVar11,0,lVar19);
          }
        }
        if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                         0x3d)) &&
            (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x27)) &&
           (unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
           0.5 <= unaff_f22)) {
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
        }
        break;
      case 0x1d:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if ((cVar3 != '\x01') && (cVar3 == '\0')) {
          if ((((ulong)chr(this,uVar18)->bFlagsB & 7) >> 1 != 0) ||
             (chr(this,uVar18)->fb4 < 0.0)) {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x29);
          }
          else {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x26);
          }
          chr(this,uVar18)->bState2 = 1;
          (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))
                    (this->flDeltaT * fVar25);
          CalcPushRange__7CBattleFi(this,lVar19);
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfb | 4;
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_7c0,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_7c0._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_7c0._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_7b8;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_7b4;
          if (0.0 < chr(this,uVar18)->fb4) {
            chr(this,uVar18)->fb4 = 0;
          }
          __pl__7FVectorCFRC7FVector
                    (auStack_7d0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_7d0._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_7d0._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_7c8;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_7c4;
          chr(this,uVar18)->fc4 = 0;
          chr(this,uVar18)->f64 = 0;
        }
        break;
      case 0x1e:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x28);
          if (chr(this,uVar18)->f45c < 1) {
            unaff_f22 = ((float)(int)chr(this,uVar18)->f45e / 10.0) / 30.0;
            MoveWorkInit__7CBattleFiffff(unaff_f22,0,0,0x3d75c28f,this,lVar19);
          }
          else {
            iVar14 = 0;
            fVar22 = 0.0;
            for (fVar23 = (float)(int)chr(this,uVar18)->f45c * -0.015;
                fVar23 < 0.0; fVar23 = fVar23 + 0.06) {
              fVar22 = fVar22 + fVar23;
              iVar14 = iVar14 + 1;
            }
            while (fVar22 < 0.0) {
              iVar14 = iVar14 + 1;
              fVar22 = fVar22 + fVar23;
              fVar23 = fVar23 + 0.06;
            }
            unaff_f22 = ((float)(int)chr(this,uVar18)->f45e / 10.0) /
                        (float)iVar14;
            MoveWorkInit__7CBattleFiffff
                      (unaff_f22,0,(float)(int)chr(this,uVar18)->f45c * -0.015,
                       0x3d75c28f,this,lVar19);
          }
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          lVar11 = __nw__FUi(0x108);
          if (lVar11 != 0) {
            __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
          }
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
          __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_7e0);
          auVar26 = _vmr32(in_vf0);
          auVar27 = _vmr32(auVar26);
          auVar28 = _vmr32(auVar27);
          auStack_40 = _sqc2(in_vf0);
          auStack_50 = _sqc2(auVar26);
          auStack_60 = _sqc2(auVar27);
          auStack_70 = _sqc2(auVar28);
          uVar12 = GetRad(chr(this,uVar18)->fd4);
          sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
          ApplyMatrix__6MatrixCFRC7FVector(&uStack_7f0,auStack_70,auStack_10);
          uStack_8._0_4_ = fStack_7e8;
          auStack_10 = (undefined1  [8])uStack_7f0;
          uStack_8._4_4_ = uStack_7e4;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_7f0;
          if (chr(this,uVar18)->f30 < 0.0) {
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x164) =
                 *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30 * 0.75;
          }
          else {
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x164) =
                 *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_7e8;
          if (chr(this,uVar18)->f44 < 0.0) {
            unaff_f22 = (float)GetRiseTime__7CBattleFi(this,lVar19);
            fVar25 = 1.0 - chr(this,uVar18)->f64;
          }
          else {
            unaff_f22 = (float)GetFlightTime__7CBattleFi(this,lVar19);
            fVar25 = 2.0 - chr(this,uVar18)->f64;
          }
          if ((unaff_f22 == 0.0) || (fVar25 == 0.0)) {
            fVar25 = 1.0;
          }
          else {
            fVar25 = fVar25 / unaff_f22;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) =
               *(float *)(iVar14 + 0x114) + this->flDeltaT * fVar25;
          if (2.0 < chr(this,uVar18)->f64) {
            chr(this,uVar18)->f64 = 0x40000000;
          }
        }
        if ((0.0 < chr(this,uVar18)->f44) &&
           (0.0 <= chr(this,uVar18)->fb4)) {
          chr(this,uVar18)->bState = 0x22;
          chr(this,uVar18)->bState2 = 0;
          chr(this,uVar18)->fb4 = 0;
          chr(this,uVar18)->f488 = 0x3dcccccd;
          chr(this,uVar18)->f64 = 0;
          if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
              uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) & 0x3f) >> 3
              ;
            }
            else {
              uVar15 = (ulong)(*(byte *)(iGpffff83b4 +
                                         chr(this,uVar18)->fa * 0xc0 + 0x3c)
                              >> 5);
            }
          }
          else {
            uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) & 0x3f) >>
                     3;
          }
          __pl__7FVectorCFRC7FVector
                    (&uStack_800,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          uStack_8._0_4_ = (float)uStack_7f8;
          auStack_10 = (undefined1  [8])uStack_800;
          uStack_8._4_4_ = uStack_7f4;
          if ((uVar15 == 2) || (uVar15 == 5)) {
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001005,1,auStack_10);
          }
          else {
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001000,1,auStack_10);
          }
        }
        SetPos__8BtlModelFP7FVector
                  (chr(this,uVar18)->pModel,this + uVar18 * 0x510 + 0x160)
        ;
        __pl__7FVectorCFRC7FVector
                  (auStack_810,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_810._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_810._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_808;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_804;
        chr(this,uVar18)->fc4 = 0;
        break;
      case 0x1f:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar25 = 0.0;
          }
          else {
            if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
              DamMoveFutureSet__7CBattleFi(this,lVar19);
              break;
            }
            MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_8a0);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_8b0,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_8a8;
            auStack_10 = (undefined1  [8])uStack_8b0;
            uStack_8._4_4_ = uStack_8a4;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_8b0;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x164) =
                 *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_8a8;
            if (chr(this,uVar18)->f44 < 0.0) {
              unaff_f22 = (float)GetRiseTime__7CBattleFi(this,lVar19);
              fVar25 = 1.0 - chr(this,uVar18)->f64;
            }
            else {
              unaff_f22 = (float)GetFlightTime__7CBattleFi(this,lVar19);
              fVar25 = 2.0 - chr(this,uVar18)->f64;
            }
            if ((unaff_f22 == 0.0) || (fVar25 == 0.0)) {
              fVar25 = 1.0;
            }
            else {
              fVar25 = fVar25 / unaff_f22;
            }
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) =
                 *(float *)(iVar14 + 0x114) + this->flDeltaT * fVar25;
            if (2.0 < chr(this,uVar18)->f64) {
              chr(this,uVar18)->f64 = 0x40000000;
            }
          }
          if ((0.0 < chr(this,uVar18)->f44) &&
             (0.0 <= chr(this,uVar18)->fb4)) {
            chr(this,uVar18)->bState = 0x22;
            chr(this,uVar18)->bState2 = 0;
            chr(this,uVar18)->fb4 = 0;
            chr(this,uVar18)->f488 = 0x3dcccccd;
            chr(this,uVar18)->f64 = 0;
            if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
              if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
                uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) & 0x3f) >>
                         3;
              }
              else {
                uVar15 = (ulong)(*(byte *)(iGpffff83b4 +
                                           chr(this,uVar18)->fa * 0xc0 + 0x3c)
                                >> 5);
              }
            }
            else {
              uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) & 0x3f)
                       >> 3;
            }
            __pl__7FVectorCFRC7FVector
                      (&uStack_8c0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_8b8;
            auStack_10 = (undefined1  [8])uStack_8c0;
            uStack_8._4_4_ = uStack_8b4;
            if ((uVar15 == 2) || (uVar15 == 5)) {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001005,1,auStack_10);
            }
            else {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001000,1,auStack_10);
            }
          }
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          __pl__7FVectorCFRC7FVector
                    (auStack_8d0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_8d0._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_8d0._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_8c8;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_8c4;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x29);
            if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
              if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
                uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) &
                                0x3f) >> 3);
              }
              else {
                uVar17 = (uint)(*(byte *)(iGpffff83b4 +
                                          chr(this,uVar18)->fa * 0xc0 + 0x3c)
                               >> 5);
              }
            }
            else {
              uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) &
                              0x3f) >> 3);
            }
            switch(uVar17) {
            case 0:
              unaff_f22 = 2.5;
              uVar12 = 0x3ca3d70a;
              break;
            default:
              unaff_f22 = 2.25;
              uVar12 = 0x3d3851ec;
              break;
            case 2:
              unaff_f22 = 1.75;
              uVar12 = 0x3d8f5c29;
              break;
            case 3:
              if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
                unaff_f22 = 2.5;
                uVar12 = 0x3ca3d70a;
              }
              else {
                unaff_f22 = 2.25;
                uVar12 = 0x3d39f55a;
              }
              break;
            case 5:
              if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
                unaff_f22 = 1.75;
                uVar12 = 0x3d8f5c29;
              }
              else {
                unaff_f22 = 2.25;
                uVar12 = 0x3d3851ec;
              }
            }
            if (-3.0 <= chr(this,uVar18)->fb4) {
              MoveWorkInit__7CBattleFiffff(unaff_f22,0,0,0,this,lVar19);
            }
            else {
              MoveWorkInit__7CBattleFiffff(unaff_f22,0,0,uVar12,this,lVar19);
            }
            chr(this,uVar18)->f64 = 0;
            chr(this,uVar18)->f68 = uVar12;
            chr(this,uVar18)->bState2 = 1;
            lVar11 = __nw__FUi(0x108);
            if (lVar11 != 0) {
              __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,1);
            }
          }
          iVar14 = 0;
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar23 = 0.0;
          }
          else {
            if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
              DamMoveFutureSet__7CBattleFi(this,lVar19);
              break;
            }
            if (0.1 <= chr(this,uVar18)->f64) {
              chr(this,uVar18)->f48 =
                   chr(this,uVar18)->f68;
            }
            MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x114) = *(float *)(iVar8 + 0x114) + this->flDeltaT;
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_820);
            while (chr(this,uVar18)->fd4 < -180.0) {
              iVar8 = this + uVar18 * 0x510;
              *(float *)(iVar8 + 0x184) = *(float *)(iVar8 + 0x184) + 360.0;
            }
            while (180.0 < chr(this,uVar18)->fd4) {
              iVar8 = this + uVar18 * 0x510;
              *(float *)(iVar8 + 0x184) = *(float *)(iVar8 + 0x184) - 360.0;
            }
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_830,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_828;
            auStack_10 = (undefined1  [8])uStack_830;
            uStack_8._4_4_ = uStack_824;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x160) = *(float *)(iVar8 + 0x160) + (float)uStack_830;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x164) =
                 *(float *)(iVar8 + 0x164) + chr(this,uVar18)->f30;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x168) = *(float *)(iVar8 + 0x168) + fStack_828;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            __pl__7FVectorCFRC7FVector
                      (auStack_840,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar8 = this + uVar18 * 0x510;
            *(int *)(iVar8 + 0x170) = auStack_840._0_4_;
            *(int *)(iVar8 + 0x174) = auStack_840._4_4_;
            *(undefined4 *)(iVar8 + 0x178) = uStack_838;
            *(undefined4 *)(iVar8 + 0x17c) = uStack_834;
            chr(this,uVar18)->fc4 = 0;
            if ((((float)auStack_10._0_4_ < 0.0) &&
                (chr(this,uVar18)->aPos +
                 chr(this,uVar18)->f2f0 <
                 -*(float *)(this + 0x40b4) / 2.0 + chr(this,uVar18)->f2a4))
               && (((22.5 <= chr(this,uVar18)->fd4 &&
                    (chr(this,uVar18)->fd4 <= 157.5)) ||
                   ((chr(this,uVar18)->fd4 <= -22.5 &&
                    (-157.5 <= chr(this,uVar18)->fd4)))))) {
              iVar14 = 1;
            }
            if (((0.0 < (float)auStack_10._0_4_) &&
                (*(float *)(this + 0x40b4) / 2.0 - chr(this,uVar18)->f2a4 <
                 chr(this,uVar18)->aPos +
                 chr(this,uVar18)->f2f0)) &&
               (((22.5 <= chr(this,uVar18)->fd4 &&
                 (chr(this,uVar18)->fd4 <= 157.5)) ||
                ((chr(this,uVar18)->fd4 <= -22.5 &&
                 (-157.5 <= chr(this,uVar18)->fd4)))))) {
              iVar14 = 2;
            }
            if ((((float)uStack_8 < 0.0) &&
                (chr(this,uVar18)->fb8 +
                 chr(this,uVar18)->f2f8 <
                 -*(float *)(this + 0x40bc) / 2.0 + chr(this,uVar18)->f2a4))
               && (((chr(this,uVar18)->fd4 <= 67.5 &&
                    (-67.5 <= chr(this,uVar18)->fd4)) ||
                   ((112.5 <= chr(this,uVar18)->fd4 ||
                    (chr(this,uVar18)->fd4 <= -112.5)))))) {
              iVar14 = 4;
            }
            if (((0.0 < (float)uStack_8) &&
                (fVar23 = fVar25,
                *(float *)(this + 0x40bc) / 2.0 - chr(this,uVar18)->f2a4 <
                chr(this,uVar18)->fb8 +
                chr(this,uVar18)->f2f8)) &&
               (((chr(this,uVar18)->fd4 <= 67.5 &&
                 (-67.5 <= chr(this,uVar18)->fd4)) ||
                ((112.5 <= chr(this,uVar18)->fd4 ||
                 (chr(this,uVar18)->fd4 <= -112.5)))))) {
              iVar14 = 8;
            }
          }
          fVar25 = fVar23;
          if (((chr(this,uVar18)->f44 <= 0.0) ||
              (chr(this,uVar18)->f48 == 0.0)) ||
             (chr(this,uVar18)->fb4 < 0.0)) {
            if (iVar14 != 0) {
              lVar11 = __nw__FUi(0x5e0);
              uVar10 = 0;
              if (lVar11 != 0) {
                uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x14);
                uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x15);
                uVar10 = __ct__6EffMdlFPUcPUcfii
                                   (0x3f800000,lVar11,uVar10,uVar9,0xffffffffffffffff,0);
              }
              setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
              __pl__7FVectorCFRC7FVector
                        (&uStack_860,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x360
                        );
              uStack_8._0_4_ = (float)uStack_858;
              auStack_10 = (undefined1  [8])uStack_860;
              uStack_8._4_4_ = uStack_854;
              if (iVar14 == 8) {
                uStack_8._0_4_ = *(float *)(this + 0x40bc) / 2.0;
                unaff_f22 = 0.0;
              }
              else if (iVar14 == 4) {
                uStack_8._0_4_ = -*(float *)(this + 0x40bc) / 2.0;
                unaff_f22 = -3.1415927;
              }
              else if (iVar14 == 2) {
                auStack_10._0_4_ = *(float *)(this + 0x40b4) / 2.0;
                unaff_f22 = 1.5707964;
              }
              else if (iVar14 == 1) {
                auStack_10._0_4_ = -*(float *)(this + 0x40b4) / 2.0;
                unaff_f22 = -1.5707964;
              }
              uVar9 = __ct__7FVectorFPC7FVector(auStack_870,auStack_10);
              WallHitDamageSet__7CBattleFiif7FVector
                        (chr(this,uVar18)->f64,this,lVar19,
                         chr(this,uVar18)->f462,uVar9);
              SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001002,1,auStack_10);
              __ct__7FVectorFffff(0,unaff_f22,0,0x3f800000,&uStack_880);
              uStack_8._0_4_ = (float)uStack_878;
              auStack_10 = (undefined1  [8])uStack_880;
              uStack_8._4_4_ = uStack_874;
              SetAngle__6EffMdlFP7FVector(uVar10,auStack_10);
              uVar12 = 0x40000000;
              puVar7 = (undefined4 *)vx__7FVectorFv(auStack_890);
              *puVar7 = uVar12;
              uVar12 = 0x40000000;
              puVar7 = (undefined4 *)vy__7FVectorFv(auStack_890);
              *puVar7 = uVar12;
              uVar12 = 0x40000000;
              puVar7 = (undefined4 *)vz__7FVectorFv(auStack_890);
              *puVar7 = uVar12;
              uVar12 = 0x3f800000;
              puVar7 = (undefined4 *)vw__7FVectorFv(auStack_890);
              *puVar7 = uVar12;
              SetScale__6EffMdlF7FVector(uVar10,auStack_890);
              OTEntry__6EffMdlFii(uVar10,4,8);
              if (chr(this,uVar18)->bState == '\x1f') {
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
                SetBtlMotion__8BtlModelFif
                          (0x3f800000,chr(this,uVar18)->pModel,0x28);
                MoveWorkInit__7CBattleFiffff(0xbf000000,0,0xbfc00000,0x3d75c28f,this,lVar19);
                chr(this,uVar18)->f64 = 0;
                chr(this,uVar18)->bState2 = 2;
                lVar11 = __nw__FUi(0x108);
                if (lVar11 != 0) {
                  __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
                }
              }
              BtlEffAllEndSet__7CBattleFi(this,lVar19);
            }
          }
          else {
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2a);
            fVar25 = 1.0 / this->flDeltaT;
            chr(this,uVar18)->bState = 0x23;
            chr(this,uVar18)->bState2 = 0;
            chr(this,uVar18)->fb4 = 0;
            SetPos__8BtlModelFP7FVector
                      (chr(this,uVar18)->pModel,
                       this + uVar18 * 0x510 + 0x160);
            chr(this,uVar18)->f488 = 0x3dcccccd;
            chr(this,uVar18)->f64 = 0;
            if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
              if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
                uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) & 0x3f) >>
                         3;
              }
              else {
                uVar15 = (ulong)(*(byte *)(iGpffff83b4 +
                                           chr(this,uVar18)->fa * 0xc0 + 0x3c)
                                >> 5);
              }
            }
            else {
              uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) & 0x3f)
                       >> 3;
            }
            __pl__7FVectorCFRC7FVector
                      (&uStack_850,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_848;
            auStack_10 = (undefined1  [8])uStack_850;
            uStack_8._4_4_ = uStack_844;
            if ((uVar15 == 2) || (uVar15 == 5)) {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001005,1,auStack_10);
            }
            else {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001000,1,auStack_10);
            }
          }
        }
        break;
      case 0x20:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = 2.0;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
          SetBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x29);
          MoveWorkInit__7CBattleFiffff
                    (0x3f000000,0,
                     (float)(int)chr(this,uVar18)->f45c * 0.02 + 1.0,0,this,
                     lVar19);
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          lVar11 = __nw__FUi(0x108);
          if (lVar11 != 0) {
            __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
          }
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
          __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_8e0);
          auVar26 = _vmr32(in_vf0);
          auVar27 = _vmr32(auVar26);
          auVar28 = _vmr32(auVar27);
          auStack_40 = _sqc2(in_vf0);
          auStack_50 = _sqc2(auVar26);
          auStack_60 = _sqc2(auVar27);
          auStack_70 = _sqc2(auVar28);
          uVar12 = GetRad(chr(this,uVar18)->fd4);
          sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
          ApplyMatrix__6MatrixCFRC7FVector(&uStack_8f0,auStack_70,auStack_10);
          uStack_8._0_4_ = fStack_8e8;
          auStack_10 = (undefined1  [8])uStack_8f0;
          uStack_8._4_4_ = uStack_8e4;
          iVar14 = this + uVar18 * 0x510;
          uStack_18 = *(undefined4 *)(iVar14 + 0x168);
          uStack_14 = *(undefined4 *)(iVar14 + 0x16c);
          fStack_20 = (float)*(undefined8 *)(iVar14 + 0x160);
          fStack_1c = (float)((ulong)*(undefined8 *)(iVar14 + 0x160) >> 0x20);
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_8f0;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x164) =
               *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_8e8;
          if (0.0 < chr(this,uVar18)->f64) {
            uVar10 = __ct__7FVectorFffff(0,chr(this,uVar18)->f44,
                                         chr(this,uVar18)->f3c,0x3f800000,
                                         auStack_910);
            Get3DAngle__F7FVector(auStack_900,uVar10);
            fStack_20 = auStack_900._0_4_;
            fStack_1c = auStack_900._4_4_;
            uStack_18 = uStack_8f8;
            uStack_14 = uStack_8f4;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x180) =
                 *(float *)(iVar14 + 0x180) +
                 (-fStack_20 - chr(this,uVar18)->fd0) / 4.0;
          }
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
        }
        if ((0.0 <= chr(this,uVar18)->fb4) &&
           (chr(this,uVar18)->fb4 = 0,
           0.1 < chr(this,uVar18)->f64)) {
          lVar11 = __nw__FUi(0x5e0);
          uVar10 = 0;
          if (lVar11 != 0) {
            uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x14);
            uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x15);
            uVar10 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar11,uVar10,uVar9,0xffffffffffffffff,0);
          }
          setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
          __pl__7FVectorCFRC7FVector
                    (&uStack_920,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x360);
          uStack_8._0_4_ = (float)uStack_918;
          auStack_10 = (undefined1  [8])uStack_920;
          uStack_8._4_4_ = uStack_914;
          auStack_10._4_4_ = 0xbe4ccccd;
          auStack_10._0_4_ = (int)uStack_920;
          SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
          __ct__7FVectorFffff(0xbfc90fdb,0,0,0x3f800000,auStack_930);
          SetAngle__6EffMdlFP7FVector(uVar10,auStack_10);
          uVar12 = 0x40000000;
          puVar7 = (undefined4 *)vx__7FVectorFv(auStack_940);
          *puVar7 = uVar12;
          uVar12 = 0x40000000;
          puVar7 = (undefined4 *)vy__7FVectorFv(auStack_940);
          *puVar7 = uVar12;
          uVar12 = 0x40000000;
          puVar7 = (undefined4 *)vz__7FVectorFv(auStack_940);
          *puVar7 = uVar12;
          uVar12 = 0x3f800000;
          puVar7 = (undefined4 *)vw__7FVectorFv(auStack_940);
          *puVar7 = uVar12;
          SetScale__6EffMdlF7FVector(uVar10,auStack_940);
          OTEntry__6EffMdlFii(uVar10,4,8);
          chr(this,uVar18)->bState = 0x24;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x2b);
          chr(this,uVar18)->bState2 = 0;
          chr(this,uVar18)->f30 =
               chr(this,uVar18)->aPos +
               chr(this,uVar18)->f2f0;
          chr(this,uVar18)->f34 =
               chr(this,uVar18)->fb8 +
               chr(this,uVar18)->f2f8;
          chr(this,uVar18)->fd0 = 0;
          chr(this,uVar18)->f64 = 0;
          if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
              uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) & 0x3f) >> 3
              ;
            }
            else {
              uVar15 = (ulong)(*(byte *)(iGpffff83b4 +
                                         chr(this,uVar18)->fa * 0xc0 + 0x3c)
                              >> 5);
            }
          }
          else {
            uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) & 0x3f) >>
                     3;
          }
          __pl__7FVectorCFRC7FVector
                    (&uStack_950,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          uStack_8._0_4_ = (float)uStack_948;
          auStack_10 = (undefined1  [8])uStack_950;
          uStack_8._4_4_ = uStack_944;
          if ((uVar15 == 2) || (uVar15 == 5)) {
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001005,1,auStack_10);
          }
          else {
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001000,1,auStack_10);
          }
          switch((int)uVar15) {
          case 0:
            chr(this,uVar18)->f488 = 0x3e800000;
            break;
          default:
            chr(this,uVar18)->f488 = 0x3f000000;
            break;
          case 2:
            chr(this,uVar18)->f488 = 0x3f800000;
            break;
          case 3:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              chr(this,uVar18)->f488 = 0x3e800000;
            }
            else {
              chr(this,uVar18)->f488 = 0x3f000000;
            }
            break;
          case 5:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              chr(this,uVar18)->f488 = 0x3f800000;
            }
            else {
              chr(this,uVar18)->f488 = 0x3f000000;
            }
          }
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          lVar11 = __nw__FUi(0x108);
          if (lVar11 != 0) {
            __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
          }
        }
        SetPosAngle__8BtlModelFP7FVectorP7FVector
                  (chr(this,uVar18)->pModel,this + uVar18 * 0x510 + 0x160,
                   this + uVar18 * 0x510 + 0x180);
        __pl__7FVectorCFRC7FVector
                  (auStack_960,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_960._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_960._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_958;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_954;
        chr(this,uVar18)->fc4 = 0;
        break;
      case 0x21:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar25 = 0.0;
          }
          else {
            if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
              DamMoveFutureSet__7CBattleFi(this,lVar19);
              break;
            }
            MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_9e0);
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_9f0,auStack_70,auStack_10);
            uStack_8._0_4_ = fStack_9e8;
            auStack_10 = (undefined1  [8])uStack_9f0;
            uStack_8._4_4_ = uStack_9e4;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)uStack_9f0;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x164) =
                 *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + fStack_9e8;
            if (chr(this,uVar18)->f44 < 0.0) {
              unaff_f22 = (float)GetRiseTime__7CBattleFi(this,lVar19);
              fVar25 = 1.0 - chr(this,uVar18)->f64;
            }
            else {
              unaff_f22 = (float)GetFlightTime__7CBattleFi(this,lVar19);
              fVar25 = 2.0 - chr(this,uVar18)->f64;
            }
            if ((unaff_f22 == 0.0) || (fVar25 == 0.0)) {
              fVar25 = 1.0;
            }
            else {
              fVar25 = fVar25 / unaff_f22;
            }
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) =
                 *(float *)(iVar14 + 0x114) + this->flDeltaT * fVar25;
            if (2.0 < chr(this,uVar18)->f64) {
              chr(this,uVar18)->f64 = 0x40000000;
            }
          }
          if ((0.0 < chr(this,uVar18)->f44) &&
             (0.0 <= chr(this,uVar18)->fb4)) {
            chr(this,uVar18)->bState = 0x22;
            chr(this,uVar18)->bState2 = 0;
            chr(this,uVar18)->fb4 = 0;
            chr(this,uVar18)->f488 = 0x3f800000;
            chr(this,uVar18)->f64 = 0;
            if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
              if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
                uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) & 0x3f) >>
                         3;
              }
              else {
                uVar15 = (ulong)(*(byte *)(iGpffff83b4 +
                                           chr(this,uVar18)->fa * 0xc0 + 0x3c)
                                >> 5);
              }
            }
            else {
              uVar15 = ((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) & 0x3f)
                       >> 3;
            }
            __pl__7FVectorCFRC7FVector
                      (&uStack_a00,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_9f8;
            auStack_10 = (undefined1  [8])uStack_a00;
            uStack_8._4_4_ = uStack_9f4;
            if ((uVar15 == 2) || (uVar15 == 5)) {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001005,1,auStack_10);
            }
            else {
              PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001000,1,auStack_10);
            }
          }
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          __pl__7FVectorCFRC7FVector
                    (auStack_a10,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_a10._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_a10._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_a08;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_a04;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x29);
            MoveWorkInit__7CBattleFiffff(0x40800000,0,0,0,this,lVar19);
            chr(this,uVar18)->f64 = 0;
            chr(this,uVar18)->bState2 = 1;
            lVar11 = __nw__FUi(0x108);
            if (lVar11 != 0) {
              __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,1);
            }
            chr(this,uVar18)->f31c =
                 (short)(1 << ((int)chr(this,uVar18)->f455 & 0x1fU));
          }
          iVar14 = 0;
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar23 = 0.0;
          }
          else {
            if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
              DamMoveFutureSet__7CBattleFi(this,lVar19);
              break;
            }
            MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x114) = *(float *)(iVar8 + 0x114) + this->flDeltaT;
            __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_970);
            while (chr(this,uVar18)->fd4 < -180.0) {
              iVar8 = this + uVar18 * 0x510;
              *(float *)(iVar8 + 0x184) = *(float *)(iVar8 + 0x184) + 360.0;
            }
            while (180.0 < chr(this,uVar18)->fd4) {
              iVar8 = this + uVar18 * 0x510;
              *(float *)(iVar8 + 0x184) = *(float *)(iVar8 + 0x184) - 360.0;
            }
            auVar26 = _vmr32(in_vf0);
            auVar27 = _vmr32(auVar26);
            auVar28 = _vmr32(auVar27);
            auStack_40 = _sqc2(in_vf0);
            auStack_50 = _sqc2(auVar26);
            auStack_60 = _sqc2(auVar27);
            auStack_70 = _sqc2(auVar28);
            uVar12 = GetRad(chr(this,uVar18)->fd4);
            sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
            ApplyMatrix__6MatrixCFRC7FVector(&uStack_980,auStack_70,auStack_10);
            fVar22 = (float)uStack_980;
            uStack_8._0_4_ = fStack_978;
            auStack_10 = (undefined1  [8])uStack_980;
            uStack_8._4_4_ = uStack_974;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x160) = *(float *)(iVar8 + 0x160) + fVar22;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x164) =
                 *(float *)(iVar8 + 0x164) + chr(this,uVar18)->f30;
            iVar8 = this + uVar18 * 0x510;
            *(float *)(iVar8 + 0x168) = *(float *)(iVar8 + 0x168) + fStack_978;
            if (((fVar22 < 0.0) &&
                (chr(this,uVar18)->aPos +
                 chr(this,uVar18)->f2f0 <
                 -*(float *)(this + 0x40b4) / 2.0 + chr(this,uVar18)->f2a4))
               && (((22.5 <= chr(this,uVar18)->fd4 &&
                    (chr(this,uVar18)->fd4 <= 157.5)) ||
                   ((chr(this,uVar18)->fd4 <= -22.5 &&
                    (-157.5 <= chr(this,uVar18)->fd4)))))) {
              iVar14 = 1;
            }
            if (((0.0 < fVar22) &&
                (*(float *)(this + 0x40b4) / 2.0 - chr(this,uVar18)->f2a4 <
                 chr(this,uVar18)->aPos +
                 chr(this,uVar18)->f2f0)) &&
               (((22.5 <= chr(this,uVar18)->fd4 &&
                 (chr(this,uVar18)->fd4 <= 157.5)) ||
                ((chr(this,uVar18)->fd4 <= -22.5 &&
                 (-157.5 <= chr(this,uVar18)->fd4)))))) {
              iVar14 = 2;
            }
            if (((fStack_978 < 0.0) &&
                (chr(this,uVar18)->fb8 +
                 chr(this,uVar18)->f2f8 <
                 -*(float *)(this + 0x40bc) / 2.0 + chr(this,uVar18)->f2a4))
               && (((chr(this,uVar18)->fd4 <= 67.5 &&
                    (-67.5 <= chr(this,uVar18)->fd4)) ||
                   ((112.5 <= chr(this,uVar18)->fd4 ||
                    (chr(this,uVar18)->fd4 <= -112.5)))))) {
              iVar14 = 4;
            }
            if (((0.0 < fStack_978) &&
                (fVar23 = fVar25,
                *(float *)(this + 0x40bc) / 2.0 - chr(this,uVar18)->f2a4 <
                chr(this,uVar18)->fb8 +
                chr(this,uVar18)->f2f8)) &&
               (((chr(this,uVar18)->fd4 <= 67.5 &&
                 (-67.5 <= chr(this,uVar18)->fd4)) ||
                ((112.5 <= chr(this,uVar18)->fd4 ||
                 (chr(this,uVar18)->fd4 <= -112.5)))))) {
              iVar14 = 8;
            }
          }
          fVar25 = fVar23;
          if (iVar14 == 0) {
            InvolveHitCheck__7CBattleFi(this,lVar19);
          }
          else {
            lVar11 = __nw__FUi(0x5e0);
            uVar10 = 0;
            if (lVar11 != 0) {
              uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x14);
              uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x15);
              uVar10 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar11,uVar10,uVar9,0xffffffffffffffff,0);
            }
            setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
            __pl__7FVectorCFRC7FVector
                      (&uStack_990,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x360);
            uStack_8._0_4_ = (float)uStack_988;
            auStack_10 = (undefined1  [8])uStack_990;
            uStack_8._4_4_ = uStack_984;
            if (iVar14 == 8) {
              uStack_8._0_4_ = *(float *)(this + 0x40bc) / 2.0;
              unaff_f22 = 0.0;
            }
            else if (iVar14 == 4) {
              uStack_8._0_4_ = -*(float *)(this + 0x40bc) / 2.0;
              unaff_f22 = -3.1415927;
            }
            else if (iVar14 == 2) {
              auStack_10._0_4_ = *(float *)(this + 0x40b4) / 2.0;
              unaff_f22 = 1.5707964;
            }
            else if (iVar14 == 1) {
              auStack_10._0_4_ = -*(float *)(this + 0x40b4) / 2.0;
              unaff_f22 = -1.5707964;
            }
            uVar9 = __ct__7FVectorFPC7FVector(auStack_9a0,auStack_10);
            WallHitDamageSet__7CBattleFiif7FVector
                      (chr(this,uVar18)->f64,this,lVar19,
                       chr(this,uVar18)->f462,uVar9);
            SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001002,1,auStack_10);
            __ct__7FVectorFffff(0,unaff_f22,0,0x3f800000,&uStack_9b0);
            uStack_8._0_4_ = (float)uStack_9a8;
            auStack_10 = (undefined1  [8])uStack_9b0;
            uStack_8._4_4_ = uStack_9a4;
            SetAngle__6EffMdlFP7FVector(uVar10,auStack_10);
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vx__7FVectorFv(auStack_9c0);
            *puVar7 = uVar12;
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vy__7FVectorFv(auStack_9c0);
            *puVar7 = uVar12;
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vz__7FVectorFv(auStack_9c0);
            *puVar7 = uVar12;
            uVar12 = 0x3f800000;
            puVar7 = (undefined4 *)vw__7FVectorFv(auStack_9c0);
            *puVar7 = uVar12;
            SetScale__6EffMdlF7FVector(uVar10,auStack_9c0);
            OTEntry__6EffMdlFii(uVar10,4,8);
            if (chr(this,uVar18)->bState == '!') {
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
              SetBtlMotion__8BtlModelFif
                        (0x3f800000,chr(this,uVar18)->pModel,0x28);
              MoveWorkInit__7CBattleFiffff(0xbf000000,0,0xbfc00000,0x3d75c28f,this,lVar19);
              chr(this,uVar18)->f64 = 0;
              chr(this,uVar18)->bState2 = 2;
              lVar11 = __nw__FUi(0x108);
              if (lVar11 != 0) {
                __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
              }
            }
            BtlEffAllEndSet__7CBattleFi(this,lVar19);
          }
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          __pl__7FVectorCFRC7FVector
                    (auStack_9d0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_9d0._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_9d0._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_9c8;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_9c4;
          chr(this,uVar18)->fc4 = 0;
        }
        break;
      case 0x22:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2b);
          }
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 4;
        }
        if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) ||
           (-1 < (long)((ulong)this->bFlags24 << 0x3d))) {
          if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a)) {
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            iVar14 = 0;
            while ((iVar14 < 0x20 &&
                   (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                     (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                      != 0)) ||
                    ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
              iVar14 = iVar14 + 1;
            }
            if ((iVar14 < 0x20) && (0 < chr(this,uVar18)->nHp)) {
              chr(this,uVar18)->bState = 0x28;
              chr(this,uVar18)->bState2 = 0;
            }
            else {
              chr(this,uVar18)->bState = 0x2a;
              chr(this,uVar18)->bState2 = 0;
            }
          }
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_a20,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_a20._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_a20._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_a18;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_a14;
          __pl__7FVectorCFRC7FVector
                    (auStack_a30,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_a30._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_a30._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_a28;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_a24;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        break;
      case 0x23:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2b);
          }
          if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
            if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
              uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) &
                              0x3f) >> 3);
            }
            else {
              uVar17 = (uint)(*(byte *)(iGpffff83b4 +
                                        chr(this,uVar18)->fa * 0xc0 + 0x3c) >>
                             5);
            }
          }
          else {
            uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14) &
                            0x3f) >> 3);
          }
          switch(uVar17) {
          case 0:
            unaff_f22 = 2.5;
            break;
          default:
            unaff_f22 = 2.25;
            break;
          case 2:
            unaff_f22 = 1.75;
            break;
          case 3:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              unaff_f22 = 2.5;
            }
            else {
              unaff_f22 = 2.25;
            }
            break;
          case 5:
            if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
              unaff_f22 = 1.75;
            }
            else {
              unaff_f22 = 2.25;
            }
          }
          MoveWorkInit__7CBattleFiffff(unaff_f22,0xbd99999a,0,0,this,lVar19);
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 4;
        }
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        else {
          if ((long)((ulong)this->bFlags24 << 0x3d) < 0) {
            DamMoveFutureSet__7CBattleFi(this,lVar19);
            break;
          }
          MoveFunc__7CBattleFif(this->flDeltaT,this,lVar19);
          __ct__7FVectorFffff(0,0,chr(this,uVar18)->f2c,0,auStack_a40);
          auVar26 = _vmr32(in_vf0);
          auVar27 = _vmr32(auVar26);
          auVar28 = _vmr32(auVar27);
          auStack_40 = _sqc2(in_vf0);
          auStack_50 = _sqc2(auVar26);
          auStack_60 = _sqc2(auVar27);
          auStack_70 = _sqc2(auVar28);
          uVar12 = GetRad(chr(this,uVar18)->fd4);
          sceVu0RotMatrixY(uVar12,auStack_70,auStack_70);
          ApplyMatrix__6MatrixCFRC7FVector(&uStack_a50,auStack_70,auStack_10);
          uStack_8._0_4_ = (float)uStack_a48;
          auStack_10 = (undefined1  [8])uStack_a50;
          uStack_8._4_4_ = uStack_a44;
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_a60,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_a60._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_a60._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_a58;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_a54;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x160) = *(float *)(iVar14 + 0x160) + (float)auStack_10._0_4_;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x164) =
               *(float *)(iVar14 + 0x164) + chr(this,uVar18)->f30;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x168) = *(float *)(iVar14 + 0x168) + (float)uStack_8;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          fVar25 = fVar23;
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
          iVar14 = 0;
          while ((iVar14 < 0x20 &&
                 (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                   (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                    != 0)) ||
                  ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
            iVar14 = iVar14 + 1;
          }
          if ((iVar14 < 0x20) && (0 < chr(this,uVar18)->nHp)) {
            chr(this,uVar18)->bState = 0x28;
            chr(this,uVar18)->bState2 = 0;
          }
          else {
            chr(this,uVar18)->bState = 0x2a;
            chr(this,uVar18)->bState2 = 0;
            chr(this,uVar18)->f488 = 0x3dcccccd;
          }
        }
        SetPos__8BtlModelFP7FVector
                  (chr(this,uVar18)->pModel,this + uVar18 * 0x510 + 0x160)
        ;
        __pl__7FVectorCFRC7FVector
                  (auStack_a70,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_a70._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_a70._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_a68;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_a64;
        chr(this,uVar18)->fc4 = 0;
        break;
      case 0x24:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2b);
          }
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 4;
        }
        if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) ||
           (-1 < (long)((ulong)this->bFlags24 << 0x3d))) {
          if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a)) {
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            iVar14 = 0;
            while ((iVar14 < 0x20 &&
                   (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                     (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                      != 0)) ||
                    ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
              iVar14 = iVar14 + 1;
            }
            if ((iVar14 < 0x20) && (0 < chr(this,uVar18)->nHp)) {
              chr(this,uVar18)->bState = 0x28;
              chr(this,uVar18)->bState2 = 0;
            }
            else {
              chr(this,uVar18)->bState = 0x2a;
              chr(this,uVar18)->bState2 = 0;
            }
          }
          (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))
                    (this->flDeltaT * fVar25);
          CalcPushRange__7CBattleFi(this,lVar19);
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfb | 4;
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_a80,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_a80._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_a80._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_a78;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_a74;
          chr(this,uVar18)->aPos =
               chr(this,uVar18)->f30 -
               chr(this,uVar18)->f2f0;
          chr(this,uVar18)->fb4 = 0;
          chr(this,uVar18)->fb8 =
               chr(this,uVar18)->f34 -
               chr(this,uVar18)->f2f8;
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          __pl__7FVectorCFRC7FVector
                    (auStack_a90,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_a90._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_a90._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_a88;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_a84;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        break;
      case 0x25:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_aa0,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_aa0._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_aa0._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_a98;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_a94;
          chr(this,uVar18)->fb4 = 0;
          chr(this,uVar18)->f30 =
               chr(this,uVar18)->aPos +
               chr(this,uVar18)->f2f0;
          chr(this,uVar18)->f34 =
               chr(this,uVar18)->fb8 +
               chr(this,uVar18)->f2f8;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x2b);
          chr(this,uVar18)->f64 = 0;
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 4;
          if ((chr(this,uVar18)->f45c != 0) ||
             (chr(this,uVar18)->f45e != 0)) {
            lVar11 = __nw__FUi(0x5e0);
            uVar10 = 0;
            if (lVar11 != 0) {
              uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x14);
              uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0x15);
              uVar10 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar11,uVar10,uVar9,0xffffffffffffffff,0);
            }
            setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
            __pl__7FVectorCFRC7FVector
                      (&uStack_ab0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x360);
            uStack_8._0_4_ = (float)uStack_aa8;
            auStack_10 = (undefined1  [8])uStack_ab0;
            uStack_8._4_4_ = uStack_aa4;
            auStack_10._4_4_ = 0xbe4ccccd;
            auStack_10._0_4_ = (int)uStack_ab0;
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2001002,1,auStack_10);
            SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
            __ct__7FVectorFffff(0xbfc90fdb,0,0,0x3f800000,&uStack_ac0);
            uStack_8._0_4_ = (float)uStack_ab8;
            auStack_10 = (undefined1  [8])uStack_ac0;
            uStack_8._4_4_ = uStack_ab4;
            SetAngle__6EffMdlFP7FVector(uVar10,auStack_10);
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vx__7FVectorFv(auStack_ad0);
            *puVar7 = uVar12;
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vy__7FVectorFv(auStack_ad0);
            *puVar7 = uVar12;
            uVar12 = 0x40000000;
            puVar7 = (undefined4 *)vz__7FVectorFv(auStack_ad0);
            *puVar7 = uVar12;
            uVar12 = 0x3f800000;
            puVar7 = (undefined4 *)vw__7FVectorFv(auStack_ad0);
            *puVar7 = uVar12;
            SetScale__6EffMdlF7FVector(uVar10,auStack_ad0);
            OTEntry__6EffMdlFii(uVar10,4,8);
          }
          lVar11 = __nw__FUi(0x108);
          if (lVar11 != 0) {
            __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
          }
        }
        if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) ||
           (-1 < (long)((ulong)this->bFlags24 << 0x3d))) {
          if (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a)) {
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) = *(float *)(iVar14 + 0x114) + this->flDeltaT;
          }
          (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))
                    (this->flDeltaT * fVar25);
          CalcPushRange__7CBattleFi(this,lVar19);
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfb | 4;
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_ae0,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_ae0._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_ae0._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_ad8;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_ad4;
          chr(this,uVar18)->aPos =
               chr(this,uVar18)->f30 -
               chr(this,uVar18)->f2f0;
          chr(this,uVar18)->fb4 = 0;
          chr(this,uVar18)->fb8 =
               chr(this,uVar18)->f34 -
               chr(this,uVar18)->f2f8;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2b) {
            iVar14 = 0;
            while ((iVar14 < 0x20 &&
                   (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                     (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                      != 0)) ||
                    ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
              iVar14 = iVar14 + 1;
            }
            if ((iVar14 < 0x20) && (0 < chr(this,uVar18)->nHp)) {
              chr(this,uVar18)->bState = 0x28;
              chr(this,uVar18)->bState2 = 0;
            }
            else {
              chr(this,uVar18)->bState = 0x2a;
              chr(this,uVar18)->bState2 = 0;
              if ((chr(this,uVar18)->bFlagsB & 1) == 0) {
                if ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0) {
                  uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 4) &
                                  0x3f) >> 3);
                }
                else {
                  uVar17 = (uint)(*(byte *)(iGpffff83b4 +
                                            chr(this,uVar18)->fa * 0xc0 + 0x3c
                                           ) >> 5);
                }
              }
              else {
                uVar17 = (uint)(((ulong)*(byte *)(chr(this,uVar18)->pParam + 0x14)
                                & 0x3f) >> 3);
              }
              switch(uVar17) {
              case 0:
                chr(this,uVar18)->f488 = 0x3f000000;
                break;
              default:
                chr(this,uVar18)->f488 = 0x3f800000;
                break;
              case 2:
                chr(this,uVar18)->f488 = 0x3fc00000;
                break;
              case 3:
                if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
                  chr(this,uVar18)->f488 = 0x3f000000;
                }
                else {
                  chr(this,uVar18)->f488 = 0x3f800000;
                }
                break;
              case 5:
                if ((long)((ulong)chr(this,uVar18)->f454 << 0x3e) < 0) {
                  chr(this,uVar18)->f488 = 0x3fc00000;
                }
                else {
                  chr(this,uVar18)->f488 = 0x3f800000;
                }
              }
            }
          }
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          __pl__7FVectorCFRC7FVector
                    (auStack_af0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_af0._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_af0._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_ae8;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_ae4;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        break;
      case 0x26:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(this,uVar18)->pModel,0x2c);
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9;
          if (chr(this,uVar18)->f4c8 != -1) {
            __pl__7FVectorCFRC7FVector
                      (&uStack_b00,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_af8;
            auStack_10 = (undefined1  [8])uStack_b00;
            uStack_8._4_4_ = uStack_af4;
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x70000005,1,auStack_10);
          }
          MoveWorkInit__7CBattleFiffff(0,0,0,0,this,lVar19);
          lVar11 = __nw__FUi(0x108);
          if (lVar11 != 0) {
            __ct__16DownHitSmokeCallFiii(lVar11,0,lVar19,0);
          }
        }
        if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) ||
           (-1 < (long)((ulong)this->bFlags24 << 0x3d))) {
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x2c) {
            if ((long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) << 0x3d)
                < 0) {
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9;
            }
            else {
              unaff_f22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0)
              ;
              if (unaff_f22 < 0.33333334) {
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9;
              }
              else {
                iVar14 = this + uVar18 * 0x510;
                *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 2;
              }
            }
          }
          else {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 6;
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2c) {
            iVar14 = 0;
            while ((iVar14 < 0x20 &&
                   (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                     (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                      != 0)) ||
                    ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
              iVar14 = iVar14 + 1;
            }
            if ((iVar14 < 0x20) && (0 < chr(this,uVar18)->nHp)) {
              chr(this,uVar18)->bState = 0x28;
              chr(this,uVar18)->bState2 = 0;
            }
            else {
              chr(this,uVar18)->bState = 0x2a;
              chr(this,uVar18)->bState2 = 0;
              chr(this,uVar18)->f488 = 0x3dcccccd;
            }
          }
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_b10,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_b10._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_b10._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_b08;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_b04;
          __pl__7FVectorCFRC7FVector
                    (auStack_b20,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_b20._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_b20._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_b18;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_b14;
          chr(this,uVar18)->fc4 = 0;
        }
        else {
          DamMoveFutureSet__7CBattleFi(this,lVar19);
        }
        break;
      case 0x27:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          fVar25 = 0.0;
          iVar14 = 0;
          while ((iVar14 < 0x20 &&
                 (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                   (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                    != 0)) ||
                  ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
            iVar14 = iVar14 + 1;
          }
          if (0x1f < iVar14) {
            lVar11 = __nw__FUi(0x84);
            if (lVar11 != 0) {
              __ct__9BreakBBoxFiii(lVar11,0,lVar19,0);
            }
            ClutCtrl__8BtlModelFffff(0,0,0,0,chr(this,uVar18)->pModel);
            chr(this,uVar18)->bState = 0x18;
            chr(this,uVar18)->bState2 = 1;
            chr(this,uVar18)->fc = 0;
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x26);
            chr(this,uVar18)->bState2 = 1;
            chr(this,uVar18)->f64 = 0;
          }
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar25 = 0.0;
          }
          else {
            __mi__7FVectorCFRC7FVector
                      (auStack_b30,this + uVar18 * 0x510 + 0x170,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x160) = auStack_b30._0_4_;
            *(int *)(iVar14 + 0x164) = auStack_b30._4_4_;
            *(undefined4 *)(iVar14 + 0x168) = uStack_b28;
            *(undefined4 *)(iVar14 + 0x16c) = uStack_b24;
            chr(this,uVar18)->fb4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) =
                 *(float *)(iVar14 + 0x114) + this->flDeltaT * 2.0;
            if (1.0 <= chr(this,uVar18)->f64) {
              BtlEffAllEndSet__7CBattleFi(this,lVar19);
              chr(this,uVar18)->bState2 = 2;
              ClutCtrl__8BtlModelFffff
                        (0,0,0,0x3f800000,chr(this,uVar18)->pModel);
              fVar25 = 0.0;
            }
            else {
              fVar25 = 1.0 - chr(this,uVar18)->f64;
              ClutCtrl__8BtlModelFffff
                        (0,0,0,chr(this,uVar18)->f64,
                         chr(this,uVar18)->pModel);
            }
          }
        }
        break;
      case 0x28:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          fVar25 = 0.0;
          iVar14 = 0;
          while ((iVar14 < 0x20 &&
                 (((*(char *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d0) != 'T' ||
                   (((ulong)*(byte *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1cd) & 0x3f) >> 3
                    != 0)) ||
                  ((*(uint *)(this + uVar18 * 0x510 + iVar14 * 0xc + 0x1d4) & 0x20) == 0))))) {
            iVar14 = iVar14 + 1;
          }
          if (0x1f < iVar14) {
            lVar11 = __nw__FUi(0x84);
            if (lVar11 != 0) {
              __ct__9BreakBBoxFiii(lVar11,0,lVar19,0);
            }
            ClutCtrl__8BtlModelFffff(0,0,0,0,chr(this,uVar18)->pModel);
            chr(this,uVar18)->bState = 0x2a;
            chr(this,uVar18)->bState2 = 1;
            chr(this,uVar18)->f2c = 0;
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(this,uVar18)->pModel,0x2d);
            }
            chr(this,uVar18)->bState2 = 1;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 6;
            chr(this,uVar18)->f64 = 0;
            BtlEffAllEndSet__7CBattleFi(this,lVar19);
          }
          if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
            fVar25 = 0.0;
          }
          else {
            uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
            __ct__7FVectorFRC7FVector(auStack_b40,uVar10);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x160) = auStack_b40._0_4_;
            *(int *)(iVar14 + 0x164) = auStack_b40._4_4_;
            *(undefined4 *)(iVar14 + 0x168) = uStack_b38;
            *(undefined4 *)(iVar14 + 0x16c) = uStack_b34;
            __pl__7FVectorCFRC7FVector
                      (auStack_b50,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            iVar14 = this + uVar18 * 0x510;
            *(int *)(iVar14 + 0x170) = auStack_b50._0_4_;
            *(int *)(iVar14 + 0x174) = auStack_b50._4_4_;
            *(undefined4 *)(iVar14 + 0x178) = uStack_b48;
            *(undefined4 *)(iVar14 + 0x17c) = uStack_b44;
            chr(this,uVar18)->fc4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(float *)(iVar14 + 0x114) =
                 *(float *)(iVar14 + 0x114) + this->flDeltaT * 1.0 * 2.0;
            if (1.0 < chr(this,uVar18)->f64) {
              BtlEffAllEndSet__7CBattleFi(this,lVar19);
              chr(this,uVar18)->bState2 = 2;
              ClutCtrl__8BtlModelFffff
                        (0,0,0,0x3f800000,chr(this,uVar18)->pModel);
            }
            else {
              fVar25 = 1.0 - chr(this,uVar18)->f64;
              ClutCtrl__8BtlModelFffff
                        (0,0,0,chr(this,uVar18)->f64,
                         chr(this,uVar18)->pModel);
            }
          }
        }
        break;
      case 0x2a:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        fVar25 = fVar23;
        if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3a) < 0) {
          fVar25 = 0.0;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2d);
          }
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9 | 6;
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          if (((chr(this,uVar18)->bFlagsB & 1) != 0) &&
             ((long)((ulong)chr(this,uVar18)->bFlagsB << 0x3c) < 0)) {
            cVar3 = chr(this,uVar18)->ff3;
            if (cVar3 == '\x03') {
              chr(this,uVar18)->bState = 0x30;
              chr(this,uVar18)->bState2 = 0;
            }
            else if (cVar3 == '\x02') {
              chr(this,uVar18)->bState = 0x2f;
              chr(this,uVar18)->bState2 = 0;
            }
            else if (cVar3 == '\x01') {
              chr(this,uVar18)->bState = 0x2e;
              chr(this,uVar18)->bState2 = 0;
            }
          }
        }
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_b60,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_b60._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_b60._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_b58;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_b54;
        __pl__7FVectorCFRC7FVector
                  (auStack_b70,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_b70._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_b70._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_b68;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_b64;
        chr(this,uVar18)->fc4 = 0;
        iVar14 = this + uVar18 * 0x510;
        *(float *)(iVar14 + 0x538) = *(float *)(iVar14 + 0x538) - this->flDeltaT * fVar25
        ;
        if (chr(this,uVar18)->f488 <= 0.0) {
          chr(this,uVar18)->f488 = 0;
        }
        if (((((chr(this,uVar18)->bFlagsB & 1) == 0) &&
             ((long)((ulong)chr(this,uVar18)->bFlagsA1 << 0x3e) < 0)) &&
            (chr(this,uVar18)->nHp < 1)) &&
           (((chr(this,uVar18)->nCharId == 0 &&
             (*(char *)(this + 0x4850) == '\0')) ||
            ((chr(this,uVar18)->nCharId == 7 &&
             (*(char *)(this + 0x4858) == '\0')))))) {
          iVar14 = 0;
          for (iVar8 = 0; iVar8 < 0xc; iVar8 = iVar8 + 1) {
            if (((((chr(this,iVar8)->bFlagsA & 1) != 0) &&
                 ((long)((ulong)chr(this,iVar8)->bFlagsA << 0x3e) < 0)) &&
                ((-1 < (long)((ulong)chr(this,iVar8)->bFlagsA2 << 0x3c) &&
                 ((chr(this,iVar8)->bFlagsB & 1) == 0)))) &&
               ((((0 < chr(this,iVar8)->nHp ||
                  (*(char *)(iGpffff83b4 + chr(this,iVar8)->nCharId * 0xc0 + 0x6b)
                   == '\'')) ||
                 (*(char *)(iGpffff83b4 + chr(this,iVar8)->nCharId * 0xc0 + 0x6c)
                  == '\'')) ||
                (*(char *)(iGpffff83b4 + chr(this,iVar8)->nCharId * 0xc0 + 0x6d)
                 == '\'')))) {
              iVar14 = iVar14 + 1;
            }
          }
          if (((((iVar14 != 0) && (-1 < (long)((ulong)this->bFlags24 << 0x38))) &&
               ((this->pBtlResult == 0 ||
                (((long)((ulong)this->bFlags25 << 0x39) < 0 ||
                 ((long)((ulong)this->bFlags25 << 0x38) < 0)))))) &&
              (*(char *)(iGpffff83b4 + chr(this,uVar18)->nCharId * 0xc0 + 0x6b) !=
               '\'')) &&
             ((*(char *)(iGpffff83b4 + chr(this,uVar18)->nCharId * 0xc0 + 0x6c) !=
               '\'' && (*(char *)(iGpffff83b4 + chr(this,uVar18)->nCharId * 0xc0 +
                                 0x6d) != '\'')))) {
            SetAutoFusionOff__7CBattleFii(this,lVar19,2);
            break;
          }
        }
        if ((((0 < chr(this,uVar18)->nHp) &&
             (-1 < (long)((ulong)chr(this,uVar18)->bFlagsB2 << 0x3b))) &&
            (((chr(this,uVar18)->bFlagsB & 1) != 0 ||
             ((this->nPhase != 0x16 && (this->nPhase != 0x17)))))) &&
           ((chr(this,uVar18)->f488 <= 0.0 ||
            ((lVar19 == this->cActor ||
             ((long)((ulong)this->bFlags24 << 0x3d) < 0)))))) {
          chr(this,uVar18)->bState = 0x2b;
          chr(this,uVar18)->bState2 = 0;
          MaxHitFunc__7CBattleFi(this,lVar19);
          if (chr(this,uVar18)->f454 >> 5 == 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0x504) = *(byte *)(iVar14 + 0x504) & 0xef;
            chr(this,uVar18)->f460 = 0;
            chr(this,uVar18)->f464 = 0;
            chr(this,uVar18)->f468 = 0;
            iVar14 = rand();
            chr(this,uVar18)->f46c =
                 ((float)iVar14 / 2.1474836e+09) * 0.05 + 0.975;
            chr(this,uVar18)->f470 = 0;
            chr(this,uVar18)->f474 = 0;
            chr(this,uVar18)->f478 = 0;
            chr(this,uVar18)->f47c = 0;
            chr(this,uVar18)->f480 = 0;
            chr(this,uVar18)->f484 = 0;
            chr(this,uVar18)->f48e = 0;
          }
          if ((long)((ulong)chr(this,uVar18)->bFlagsB1 << 0x39) < 0) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xbf;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7;
          }
          else {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xdf | 0x20;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xf7 | 8;
          }
          BtlEffAllEndSet__7CBattleFi(this,lVar19);
          if (((uint)this->wChrMask & 1 << (uVar18 & 0x1f)) != 0) {
            this->wChrMask =
                 this->wChrMask - (short)(1 << (uVar18 & 0x1f));
          }
        }
        break;
      case 0x2b:
        iVar14 = this + uVar18 * 0x510;
        *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf;
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x01') {
          if (cVar3 != '\0') break;
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2e) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2e);
          }
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xf9;
        }
        if (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x2e) {
          if (((this->nPhase == 5) &&
              (chr(this,this->cActor)->fc == lVar19)) &&
             (((chr(this,this->cActor)->bState == '\x0e' ||
               (chr(this,this->cActor)->bState == '\x0f')) &&
              ((chr(this,this->cActor)->bState2 == '\x01' &&
               ((*(byte *)(this->pCamera + 0x19) & 1) != 0)))))) {
            chr(this,uVar18)->bState = 7;
            chr(this,uVar18)->bState2 = 0;
          }
        }
        else {
          chr(this,uVar18)->bState = 7;
          chr(this,uVar18)->bState2 = 0;
        }
        uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
        __ct__7FVectorFRC7FVector(auStack_b80,uVar10);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x160) = auStack_b80._0_4_;
        *(int *)(iVar14 + 0x164) = auStack_b80._4_4_;
        *(undefined4 *)(iVar14 + 0x168) = uStack_b78;
        *(undefined4 *)(iVar14 + 0x16c) = uStack_b74;
        __pl__7FVectorCFRC7FVector
                  (auStack_b90,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
        iVar14 = this + uVar18 * 0x510;
        *(int *)(iVar14 + 0x170) = auStack_b90._0_4_;
        *(int *)(iVar14 + 0x174) = auStack_b90._4_4_;
        *(undefined4 *)(iVar14 + 0x178) = uStack_b88;
        *(undefined4 *)(iVar14 + 0x17c) = uStack_b84;
        chr(this,uVar18)->fc4 = 0;
        break;
      case 0x2c:
        if (chr(this,uVar18)->bState2 < '\x03') {
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_ba0,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_ba0._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_ba0._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_b98;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_b94;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x03') {
          if (((ulong)chr(this,uVar18)->bFlagsA2 & 0x7f) >> 5 < 2) {
            fVar25 = 0.0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0x9f | 0x20;
          }
          else if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
            lVar11 = GetDDisp__11CBtlPAfter2Fi(uGpffff8618,lVar19);
            if (lVar11 != 0) {
              (**(code **)(*(int *)((int)lVar11 + 0x14) + 0x30))();
            }
            if (chr(this,uVar18)->f4c0 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c0);
              chr(this,uVar18)->f4c0 = 0xffffffff;
            }
            if (chr(this,uVar18)->f4c8 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c8);
              chr(this,uVar18)->f4c8 = 0xffffffff;
            }
            BtlEffAllDelete__7CBattleFi(this,lVar19);
            if (chr(this,uVar18)->pModel != 0) {
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x40))();
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x1c) + 0xc))();
            }
            chr(this,uVar18)->pModel = 0;
            if (chr(this,uVar18)->f4a4 != 0) {
              __dla__FPv(chr(this,uVar18)->f4a4);
            }
            chr(this,uVar18)->f4a4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
          else {
            chr(this,uVar18)->bState = 0;
            chr(this,uVar18)->bState2 = 0;
            if (-1 < chr(this,uVar18)->f500) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f500 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f500 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f501) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f501 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f501 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f502) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f502 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f502 = 0xff;
            }
            DataRelease__7CBattleFiib
                      (this,chr(this,uVar18)->f4d4,lVar19,0);
            if (-1 < chr(this,uVar18)->f4d7) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d7,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d5) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d5,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d8) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d8,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d6) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d6,lVar19,0);
            }
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfe;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
        }
        else if (cVar3 == '\x02') {
          uVar10 = __ct__7FVectorFPC7FVector(auStack_bd0,this + uVar18 * 0x510 + 0x170);
          HomingMove__7CBattleFi7FVectorifff
                    (0x3f800000,0x40400000,0,this,lVar19,uVar10,0xffffffffffffffff);
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) + this->flDeltaT;
          if (1.0 <= chr(this,uVar18)->f2c) {
            chr(this,uVar18)->f2c = 0x3f800000;
            chr(this,uVar18)->bState2 = 3;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
          }
          *(float *)(chr(this,uVar18)->pModel + 0x504) =
               1.0 - chr(this,uVar18)->f2c;
        }
        else if (cVar3 == '\x01') {
          uVar10 = __ct__7FVectorFPC7FVector(auStack_bc0,this + uVar18 * 0x510 + 0x170);
          HomingMove__7CBattleFi7FVectorifff
                    (0x3f800000,0x40400000,0,this,lVar19,uVar10,0xffffffffffffffff);
          if ((((chr(this,uVar18)->f2a0 & 1) != 0) ||
              ((long)((ulong)chr(this,uVar18)->f2a0 << 0x3e) < 0)) ||
             (((long)((ulong)chr(this,uVar18)->f2a0 << 0x3d) < 0 ||
              ((long)((ulong)chr(this,uVar18)->f2a0 << 0x3c) < 0)))) {
            chr(this,uVar18)->bState2 = 2;
            chr(this,uVar18)->f2c = 0;
          }
        }
        else if (cVar3 == '\0') {
          __ct__7FVectorFffff(this->flMenuTimer,0,this->flMenuTimer2,
                              0x3f800000,auStack_bb0);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x170) = auStack_bb0._0_4_;
          *(int *)(iVar14 + 0x174) = auStack_bb0._4_4_;
          *(undefined4 *)(iVar14 + 0x178) = uStack_ba8;
          *(undefined4 *)(iVar14 + 0x17c) = uStack_ba4;
          chr(this,uVar18)->f10 = 0;
          chr(this,uVar18)->bState2 = 1;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb6) = *(byte *)(iVar14 + 0xb6) & 0xfd;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xfe;
          SetBtlMotion__8BtlModelFif(0x3f800000,chr(this,uVar18)->pModel,4);
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0xbf | 0x40;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb7) = *(byte *)(iVar14 + 0xb7) & 0xf9;
          iVar14 = this + uVar18 * 0x510;
          *(byte *)(iVar14 + 0xb4) = *(byte *)(iVar14 + 0xb4) & 0x7f;
          chr(this,uVar18)->f4dc = 0xff;
          chr(this,uVar18)->f4dd = 0;
          chr(this,uVar18)->f4de = 0xff;
        }
        break;
      case 0x2d:
        if (chr(this,uVar18)->bState2 < '\x03') {
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_be0,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_be0._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_be0._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_bd8;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_bd4;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x03') {
          if (((ulong)chr(this,uVar18)->bFlagsA2 & 0x7f) >> 5 < 2) {
            fVar25 = 0.0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0x9f | 0x20;
          }
          else if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
            lVar11 = GetDDisp__11CBtlPAfter2Fi(uGpffff8618,lVar19);
            if (lVar11 != 0) {
              (**(code **)(*(int *)((int)lVar11 + 0x14) + 0x30))();
            }
            if (chr(this,uVar18)->f4c0 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c0);
              chr(this,uVar18)->f4c0 = 0xffffffff;
            }
            if (chr(this,uVar18)->f4c8 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c8);
              chr(this,uVar18)->f4c8 = 0xffffffff;
            }
            BtlEffAllDelete__7CBattleFi(this,lVar19);
            if (chr(this,uVar18)->pModel != 0) {
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x40))();
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x1c) + 0xc))();
            }
            chr(this,uVar18)->pModel = 0;
            if (chr(this,uVar18)->f4a4 != 0) {
              __dla__FPv(chr(this,uVar18)->f4a4);
            }
            chr(this,uVar18)->f4a4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
          else {
            chr(this,uVar18)->bState = 0;
            chr(this,uVar18)->bState2 = 0;
            if (-1 < chr(this,uVar18)->f500) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f500 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f500 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f501) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f501 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f501 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f502) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f502 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f502 = 0xff;
            }
            DataRelease__7CBattleFiib
                      (this,chr(this,uVar18)->f4d4,lVar19,0);
            if (-1 < chr(this,uVar18)->f4d7) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d7,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d5) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d5,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d8) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d8,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d6) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d6,lVar19,0);
            }
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfe;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
        }
        else if (cVar3 == '\x02') {
          fVar25 = 0.0;
          *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
          if (chr(this,uVar18)->ff2 == -1) {
            chr(this,uVar18)->bState2 = 3;
          }
        }
        else {
          if (cVar3 != '\x01') {
            if (cVar3 != '\0') break;
            iVar14 = this + uVar18 * 0x510;
            iVar8 = this + uVar18 * 0x510;
            uVar10 = *(undefined8 *)(iVar8 + 0x160);
            uVar12 = *(undefined4 *)(iVar8 + 0x168);
            uVar13 = *(undefined4 *)(iVar8 + 0x16c);
            *(int *)(iVar14 + 0x170) = (int)uVar10;
            *(int *)(iVar14 + 0x174) = (int)((ulong)uVar10 >> 0x20);
            *(undefined4 *)(iVar14 + 0x178) = uVar12;
            *(undefined4 *)(iVar14 + 0x17c) = uVar13;
            SetBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x26);
            chr(this,uVar18)->f2c = 0x3f800000;
            chr(this,uVar18)->bState2 = 1;
            chr(this,uVar18)->fc = 0;
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            lVar11 = __nw__FUi(0x60);
            if (lVar11 != 0) {
              __ct__15NormalDeathEfctFii(lVar11,0,lVar19);
            }
            __pl__7FVectorCFRC7FVector
                      (&uStack_bf0,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x3a0);
            uStack_8._0_4_ = (float)uStack_be8;
            auStack_10 = (undefined1  [8])uStack_bf0;
            uStack_8._4_4_ = uStack_be4;
            PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x2002001,1,auStack_10);
            AddTrophy__7CBattleFiP12MONSTERParam
                      (this,lVar19,chr(this,uVar18)->pParam);
          }
          if (((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                           0x3d)) &&
              (fVar23 = fVar25,
              *(short *)(chr(this,uVar18)->pModel + 0x510) == 0x26)) &&
             (fVar22 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(this,uVar18)->pModel,0),
             0.33333334 <= fVar22)) {
            fVar23 = 0.0;
          }
          __pl__7FVectorCFRC7FVector
                    (&uStack_c00,this + uVar18 * 0x510 + 0x160,this + uVar18 * 0x510 + 0x380);
          uStack_8._0_4_ = (float)uStack_bf8;
          auStack_10 = (undefined1  [8])uStack_c00;
          uStack_8._4_4_ = uStack_bf4;
          fVar25 = *(float *)(this + uVar18 * 0x510 + 900);
          fVar22 = chr(this,uVar18)->f2c;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) - this->flDeltaT * 3.75;
          if (chr(this,uVar18)->f2c <= 0.0) {
            chr(this,uVar18)->f2c = 0;
            chr(this,uVar18)->bState2 = 2;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
          }
          SetScale__8BtlModelFf
                    (chr(this,uVar18)->f2c,
                     chr(this,uVar18)->pModel);
          unaff_f22 = (fVar25 / fVar22) * chr(this,uVar18)->f2c;
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0x164) =
               *(float *)(iVar14 + 0x164) + (*(float *)(this + uVar18 * 0x510 + 900) - unaff_f22);
          SetPos__8BtlModelFP7FVector
                    (chr(this,uVar18)->pModel,
                     this + uVar18 * 0x510 + 0x160);
          if (1.0 - chr(this,uVar18)->f2c < 0.5) {
            fVar24 = (((1.0 - chr(this,uVar18)->f2c) * 128.0) / 0.5) / 128.0;
            fVar25 = fVar24;
            fVar22 = fVar24;
          }
          else {
            fVar24 = (128.0 - (((1.0 - chr(this,uVar18)->f2c) - 0.5) * 98.0) /
                              0.5) / 128.0;
            fVar25 = (128.0 - (((1.0 - chr(this,uVar18)->f2c) - 0.5) * 58.0) /
                              0.5) / 128.0;
            fVar22 = (128.0 - (((1.0 - chr(this,uVar18)->f2c) - 0.5) * 38.0) /
                              0.5) / 128.0;
          }
          ClutCtrl__8BtlModelFffff
                    (fVar25,fVar24,fVar22,0,chr(this,uVar18)->pModel);
          fVar25 = fVar23;
          if (chr(this,uVar18)->fc == 0) {
            lVar11 = __nw__FUi(0x5e0);
            uVar10 = 0;
            if (lVar11 != 0) {
              uVar10 = GetFileEntry(*(undefined4 *)(this + 0x484c),0xc);
              uVar9 = GetFileEntry(*(undefined4 *)(this + 0x484c),0xd);
              uVar10 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar11,uVar10,uVar9,lVar19,1);
            }
            setMotion__7ExModelFPCc((int)uVar10 + 0x20,0x6e6c90);
            SetPos__6EffMdlFP7FVector(uVar10,auStack_10);
            OTEntry__6EffMdlFii(uVar10,4,8);
            fVar23 = (float)Length__7FVectorCFv(this + uVar18 * 0x510 + 0x3b0);
            unaff_f22 = (fVar23 + 19.0) / 26.0;
            pfVar6 = (float *)vx__7FVectorFv(auStack_c10);
            *pfVar6 = unaff_f22;
            pfVar6 = (float *)vy__7FVectorFv(auStack_c10);
            *pfVar6 = unaff_f22;
            pfVar6 = (float *)vz__7FVectorFv(auStack_c10);
            *pfVar6 = unaff_f22;
            uVar12 = 0x3f800000;
            puVar7 = (undefined4 *)vw__7FVectorFv(auStack_c10);
            *puVar7 = uVar12;
            SetScale__6EffMdlF7FVector(uVar10,auStack_c10);
            chr(this,uVar18)->fc = 1;
          }
        }
        break;
      case 0x2e:
        if (chr(this,uVar18)->bState2 < '\x03') {
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_c20,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_c20._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_c20._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_c18;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_c14;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 != '\x04') {
          if (cVar3 == '\x03') {
            if (((ulong)chr(this,uVar18)->bFlagsA2 & 0x7f) >> 5 < 2) {
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
              *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
              OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
              ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0x9f | 0x20;
              fVar25 = 0.0;
            }
            else if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
              lVar11 = GetDDisp__11CBtlPAfter2Fi(uGpffff8618,lVar19);
              if (lVar11 != 0) {
                (**(code **)(*(int *)((int)lVar11 + 0x14) + 0x30))();
              }
              if (chr(this,uVar18)->f4c0 != -1) {
                IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c0);
                chr(this,uVar18)->f4c0 = 0xffffffff;
              }
              if (chr(this,uVar18)->f4c8 != -1) {
                IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c8);
                chr(this,uVar18)->f4c8 = 0xffffffff;
              }
              BtlEffAllDelete__7CBattleFi(this,lVar19);
              if (chr(this,uVar18)->pModel != 0) {
                (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x40))();
                (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x1c) + 0xc))();
              }
              chr(this,uVar18)->pModel = 0;
              if (chr(this,uVar18)->f4a4 != 0) {
                __dla__FPv(chr(this,uVar18)->f4a4);
              }
              chr(this,uVar18)->f4a4 = 0;
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
            }
            else {
              chr(this,uVar18)->bState = 0;
              chr(this,uVar18)->bState2 = 0;
              if (-1 < chr(this,uVar18)->f500) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
                iVar14->flMenuTimer2 =
                     iVar14->flMenuTimer2 -
                     (*(uint *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                        0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
                if (*(int *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                     0x4484) + 0x88) == 0) {
                  iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484
                                   );
                  if (iVar14 != 0) {
                    (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                  }
                  *(undefined4 *)(this + chr(this,uVar18)->f500 * 4 + 0x4484)
                       = 0;
                }
                chr(this,uVar18)->f500 = 0xff;
              }
              if (-1 < chr(this,uVar18)->f501) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
                iVar14->flMenuTimer2 =
                     iVar14->flMenuTimer2 -
                     (*(uint *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                        0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
                if (*(int *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                     0x4484) + 0x88) == 0) {
                  iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484
                                   );
                  if (iVar14 != 0) {
                    (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                  }
                  *(undefined4 *)(this + chr(this,uVar18)->f501 * 4 + 0x4484)
                       = 0;
                }
                chr(this,uVar18)->f501 = 0xff;
              }
              if (-1 < chr(this,uVar18)->f502) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
                iVar14->flMenuTimer2 =
                     iVar14->flMenuTimer2 -
                     (*(uint *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                        0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
                if (*(int *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                     0x4484) + 0x88) == 0) {
                  iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484
                                   );
                  if (iVar14 != 0) {
                    (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                  }
                  *(undefined4 *)(this + chr(this,uVar18)->f502 * 4 + 0x4484)
                       = 0;
                }
                chr(this,uVar18)->f502 = 0xff;
              }
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d4,lVar19,0);
              if (-1 < chr(this,uVar18)->f4d7) {
                DataRelease__7CBattleFiib
                          (this,chr(this,uVar18)->f4d7,lVar19,0);
              }
              if (-1 < chr(this,uVar18)->f4d5) {
                DataRelease__7CBattleFiib
                          (this,chr(this,uVar18)->f4d5,lVar19,0);
              }
              if (-1 < chr(this,uVar18)->f4d8) {
                DataRelease__7CBattleFiib
                          (this,chr(this,uVar18)->f4d8,lVar19,0);
              }
              if (-1 < chr(this,uVar18)->f4d6) {
                DataRelease__7CBattleFiib
                          (this,chr(this,uVar18)->f4d6,lVar19,0);
              }
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfe;
              iVar14 = this + uVar18 * 0x510;
              *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
            }
          }
          else if (cVar3 != '\x02') {
            if (cVar3 == '\x01') {
LAB_006c3c88:
              iVar14 = this + uVar18 * 0x510;
              *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) - this->flDeltaT;
              if (chr(this,uVar18)->f2c <= 0.0) {
                chr(this,uVar18)->bState2 = 2;
                chr(this,uVar18)->ff2 = 0xff;
              }
            }
            else if (cVar3 == '\0') {
              if ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0)
                              << 0x3d)) &&
                 (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x2d)) {
                chr(this,uVar18)->f2c = 0x3f800000;
                chr(this,uVar18)->bState2 = 1;
                AddTrophy__7CBattleFiP12MONSTERParam
                          (this,lVar19,chr(this,uVar18)->pParam);
                goto LAB_006c3c88;
              }
              if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(this,uVar18)->pModel,0x2d);
              }
            }
          }
        }
        break;
      case 0x2f:
        if (chr(this,uVar18)->bState2 < '\x03') {
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_c30,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_c30._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_c30._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_c28;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_c24;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x03') {
LAB_006c4b08:
          if (((ulong)chr(this,uVar18)->bFlagsA2 & 0x7f) >> 5 < 2) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0x9f | 0x20;
            fVar25 = 0.0;
          }
          else if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
            lVar11 = GetDDisp__11CBtlPAfter2Fi(uGpffff8618,lVar19);
            if (lVar11 != 0) {
              (**(code **)(*(int *)((int)lVar11 + 0x14) + 0x30))();
            }
            if (chr(this,uVar18)->f4c0 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c0);
              chr(this,uVar18)->f4c0 = 0xffffffff;
            }
            if (chr(this,uVar18)->f4c8 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c8);
              chr(this,uVar18)->f4c8 = 0xffffffff;
            }
            BtlEffAllDelete__7CBattleFi(this,lVar19);
            if (chr(this,uVar18)->pModel != 0) {
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x40))();
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x1c) + 0xc))();
            }
            chr(this,uVar18)->pModel = 0;
            if (chr(this,uVar18)->f4a4 != 0) {
              __dla__FPv(chr(this,uVar18)->f4a4);
            }
            chr(this,uVar18)->f4a4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
          else {
            chr(this,uVar18)->bState = 0;
            chr(this,uVar18)->bState2 = 0;
            if (-1 < chr(this,uVar18)->f500) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f500 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f500 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f501) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f501 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f501 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f502) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f502 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f502 = 0xff;
            }
            DataRelease__7CBattleFiib
                      (this,chr(this,uVar18)->f4d4,lVar19,0);
            if (-1 < chr(this,uVar18)->f4d7) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d7,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d5) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d5,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d8) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d8,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d6) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d6,lVar19,0);
            }
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfe;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
        }
        else if (cVar3 == '\x02') {
          iVar14 = this + uVar18 * 0x510;
          *(float *)(iVar14 + 0xdc) = *(float *)(iVar14 + 0xdc) - this->flDeltaT;
          if (chr(this,uVar18)->f2c <= 0.0) {
            chr(this,uVar18)->bState2 = 3;
            chr(this,uVar18)->ff2 = 0xff;
            goto LAB_006c4b08;
          }
          *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) =
               chr(this,uVar18)->f2c;
        }
        else if ((cVar3 != '\x01') && (cVar3 == '\0')) {
          if (((long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) << 0x3d) <
               0) || (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d)) {
            if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(this,uVar18)->pModel,0x2d);
            }
          }
          else {
            chr(this,uVar18)->f2c = 0x3f800000;
            chr(this,uVar18)->bState2 = 1;
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            AddTrophy__7CBattleFiP12MONSTERParam
                      (this,lVar19,chr(this,uVar18)->pParam);
          }
        }
        break;
      case 0x30:
        if (chr(this,uVar18)->bState2 < '\x02') {
          uVar10 = GetPos__8BtlModelFv(chr(this,uVar18)->pModel);
          __ct__7FVectorFRC7FVector(auStack_c40,uVar10);
          iVar14 = this + uVar18 * 0x510;
          *(int *)(iVar14 + 0x160) = auStack_c40._0_4_;
          *(int *)(iVar14 + 0x164) = auStack_c40._4_4_;
          *(undefined4 *)(iVar14 + 0x168) = uStack_c38;
          *(undefined4 *)(iVar14 + 0x16c) = uStack_c34;
        }
        cVar3 = chr(this,uVar18)->bState2;
        if (cVar3 == '\x02') {
          if (((ulong)chr(this,uVar18)->bFlagsA2 & 0x7f) >> 5 < 2) {
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb5) = *(byte *)(iVar14 + 0xb5) & 0xfe | 1;
            *(undefined4 *)(chr(this,uVar18)->pModel + 0x504) = 0;
            OTRelease__8BtlModelFv(chr(this,uVar18)->pModel);
            ShadowOff__8BtlModelFv(chr(this,uVar18)->pModel);
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb2) = *(byte *)(iVar14 + 0xb2) & 0x9f | 0x20;
            fVar25 = 0.0;
          }
          else if ((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) {
            lVar11 = GetDDisp__11CBtlPAfter2Fi(uGpffff8618,lVar19);
            if (lVar11 != 0) {
              (**(code **)(*(int *)((int)lVar11 + 0x14) + 0x30))();
            }
            if (chr(this,uVar18)->f4c0 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c0);
              chr(this,uVar18)->f4c0 = 0xffffffff;
            }
            if (chr(this,uVar18)->f4c8 != -1) {
              IOPRelease__6HNMSndFi(uGpffff8374,chr(this,uVar18)->f4c8);
              chr(this,uVar18)->f4c8 = 0xffffffff;
            }
            BtlEffAllDelete__7CBattleFi(this,lVar19);
            if (chr(this,uVar18)->pModel != 0) {
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x40))();
              (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x1c) + 0xc))();
            }
            chr(this,uVar18)->pModel = 0;
            if (chr(this,uVar18)->f4a4 != 0) {
              __dla__FPv(chr(this,uVar18)->f4a4);
            }
            chr(this,uVar18)->f4a4 = 0;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
          else {
            chr(this,uVar18)->bState = 0;
            chr(this,uVar18)->bState2 = 0;
            if (-1 < chr(this,uVar18)->f500) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f500 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f500 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f500 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f500 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f501) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f501 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f501 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f501 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f501 = 0xff;
            }
            if (-1 < chr(this,uVar18)->f502) {
              iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
              iVar14->flMenuTimer2 =
                   iVar14->flMenuTimer2 -
                   (*(uint *)(*(int *)(this + chr(this,uVar18)->f502 * 4 +
                                      0x4484) + 0x88) & 1 << (uVar18 & 0x1f));
              if (*(int *)(*(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484
                                   ) + 0x88) == 0) {
                iVar14 = *(int *)(this + chr(this,uVar18)->f502 * 4 + 0x4484);
                if (iVar14 != 0) {
                  (**(code **)(*(int *)(iVar14 + 0x8c) + 8))(iVar14,1);
                }
                *(undefined4 *)(this + chr(this,uVar18)->f502 * 4 + 0x4484) =
                     0;
              }
              chr(this,uVar18)->f502 = 0xff;
            }
            DataRelease__7CBattleFiib
                      (this,chr(this,uVar18)->f4d4,lVar19,0);
            if (-1 < chr(this,uVar18)->f4d7) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d7,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d5) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d5,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d8) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d8,lVar19,0);
            }
            if (-1 < chr(this,uVar18)->f4d6) {
              DataRelease__7CBattleFiib
                        (this,chr(this,uVar18)->f4d6,lVar19,0);
            }
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfe;
            iVar14 = this + uVar18 * 0x510;
            *(byte *)(iVar14 + 0xb0) = *(byte *)(iVar14 + 0xb0) & 0xfd;
          }
        }
        else if (cVar3 == '\x01') {
LAB_006c5820:
          if (chr(this,uVar18)->nMonId != 499) {
            fVar25 = 0.0;
          }
        }
        else if (cVar3 == '\0') {
          if ((chr(this,uVar18)->nMonId == 499) ||
             ((-1 < (long)((ulong)*(byte *)(chr(this,uVar18)->pModel + 0x4d0) <<
                          0x3d) &&
              (*(short *)(chr(this,uVar18)->pModel + 0x510) == 0x2d)))) {
            iVar14 = this + uVar18 * 0x510;
            iVar8 = this + uVar18 * 0x510;
            uVar10 = *(undefined8 *)(iVar8 + 0x160);
            uVar12 = *(undefined4 *)(iVar8 + 0x168);
            uVar13 = *(undefined4 *)(iVar8 + 0x16c);
            *(int *)(iVar14 + 0x170) = (int)uVar10;
            *(int *)(iVar14 + 0x174) = (int)((ulong)uVar10 >> 0x20);
            *(undefined4 *)(iVar14 + 0x178) = uVar12;
            *(undefined4 *)(iVar14 + 0x17c) = uVar13;
            chr(this,uVar18)->bState2 = 1;
            AddTrophy__7CBattleFiP12MONSTERParam
                      (this,lVar19,chr(this,uVar18)->pParam);
            goto LAB_006c5820;
          }
          if (*(short *)(chr(this,uVar18)->pModel + 0x510) != 0x2d) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(this,uVar18)->pModel,0x2d);
          }
        }
        break;
      case 0x31:
        Retail_BtlChrSequence_State31(this,lVar19);
        break;
      case 0x32:
        Retail_BtlChrSequence_State32(this,lVar19);
        break;
      case 0x33:
        Retail_BtlChrSequence_State33(this,lVar19);
        break;
      case 0x34:
        Retail_BtlChrSequence_State34(this,lVar19);
      }
      if (((long)((ulong)chr(this,uVar18)->bFlagsA << 0x3e) < 0) &&
         (-1 < (long)((ulong)chr(this,uVar18)->bFlagsA << 0x3d))) {
        (**(code **)(*(int *)(chr(this,uVar18)->pModel + 0x10) + 0x2c))
                  (this->flDeltaT * fVar25);
      }
    }
LAB_006c63e8:
    lVar19 = (long)(int)(uVar18 + 1);
  } while( true );
}

/* ---- 0x006c6730  Retail_BtlChrSequence_State0E0F  (size 0x78e0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: ['0x7'] */
void Retail_BtlChrSequence_State0E0F(undefined4 this,undefined8 param_2,undefined8 param_3)

{
  bool bVar1;
  short sVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  long lVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int unaff_s1_lo;
  uint uVar14;
  int iVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined1 in_vf0 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [8];
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  undefined1 auStack_2f0 [16];
  undefined8 uStack_2e0;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [8];
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [8];
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [8];
  undefined4 uStack_298;
  undefined4 uStack_294;
  uint uStack_290;
  undefined4 uStack_28c;
  undefined4 uStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [8];
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [16];
  undefined8 uStack_230;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined8 uStack_1e0;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 uStack_1d0;
  undefined4 uStack_1cc;
  float fStack_1c8;
  undefined4 uStack_1c4;
  undefined8 uStack_1c0;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined8 uStack_190;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  ulong uStack_130;
  undefined4 uStack_128;
  undefined4 uStack_124;
  uint uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  uint uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auStack_10._4_4_ = in_zero_hi;
  auStack_10._0_4_ = in_zero_lo;
  auStack_10._8_4_ = in_zero_udw;
  auStack_10._12_4_ = in_register_0000000c;
  auStack_20._4_4_ = in_zero_hi;
  auStack_20._0_4_ = in_zero_lo;
  auStack_20._8_4_ = in_zero_udw;
  auStack_20._12_4_ = in_register_0000000c;
  auVar19 = _vmr32(in_vf0);
  auVar20 = _vmr32(auVar19);
  auVar21 = _vmr32(auVar20);
  auStack_40 = _sqc2(in_vf0);
  auStack_50 = _sqc2(auVar19);
  auStack_60 = _sqc2(auVar20);
  auStack_70 = _sqc2(auVar21);
  iVar15 = (int)param_3;
  iVar13 = (int)param_2;
  __ct__7FVectorFRC7FVector(auStack_80,chr(iVar13,iVar15)->pModel + 0x4e0);
  iVar4 = iVar13 + iVar15 * 0x510;
  *(int *)(iVar4 + 0x160) = auStack_80._0_4_;
  *(int *)(iVar4 + 0x164) = auStack_80._4_4_;
  *(undefined4 *)(iVar4 + 0x168) = uStack_78;
  *(undefined4 *)(iVar4 + 0x16c) = uStack_74;
  iVar4 = GetRegDat__9RegDatApiFiii(0x40,chr(iVar13,iVar15)->f4b8,0xffffffffffffffff);
  iVar5 = GetRegDat__9RegDatApiFiii(0x41,*(undefined4 *)(iVar4 + 0xc),0xffffffffffffffff);
  cVar3 = chr(iVar13,iVar15)->bState2;
  if (cVar3 == '\n') {
    if ((*(byte *)(iVar13->pCamera + 0x19) & 1) == 0) {
      if ((((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) != 1) &&
           (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) != 0x25)) &&
          (chr(iVar13,iVar15)->f4b0 != 0)) &&
         (fVar18 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(iVar13,iVar15)->pModel,0),
         0.8 <= fVar18)) {
        (**(code **)(*(int *)(chr(iVar13,iVar15)->f4b0 + 0x14) + 0x40))();
        chr(iVar13,iVar15)->f4b0 = 0;
      }
      if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 1) &&
         (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 1)) {
        lVar10 = BtlEndCheck__7CBattleFv(param_2);
        bVar1 = (*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 1) ==
                0 || 0 < *(int *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x130)
        ;
        if (((long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                    0xb4) << 0x3c) < 0) &&
           (*(char *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x1a3) != '\x03'))
        {
          bVar1 = true;
        }
        if ((lVar10 == 0) || (!bVar1)) {
          if (((((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4)
                & 7) >> 1 == 1) ||
              (((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) &
               7) >> 1 == 2)) &&
             (-1 < (long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510
                                          + 0xb0) << 0x3a))) {
            auVar19 = _lqc2(*(undefined1 (*) [16])
                             (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
            auVar20 = _lqc2(*(undefined1 (*) [16])
                             (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
            auVar19 = _vadd(auVar19,auVar20);
            auStack_400 = _sqc2(auVar19);
            __ct__7FVectorFPC7FVector(&uStack_2e0,auStack_400);
            auStack_10._8_4_ = uStack_2d8;
            auStack_10._0_8_ = uStack_2e0;
            auStack_10._12_4_ = uStack_2d4;
            auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
            auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x360));
            auVar19 = _vadd(auVar19,auVar20);
            auStack_410 = _sqc2(auVar19);
            __ct__7FVectorFPC7FVector(auStack_2f0,auStack_410);
            auVar20 = _lqc2(auStack_2f0);
            auVar19 = _lqc2(auStack_10);
            auVar19 = _vsub(auVar19,auVar20);
            auStack_10 = _sqc2(auVar19);
            uVar8 = __ct__7FVectorFPC7FVector(auStack_310,auStack_10);
            Get3DAngle__F7FVector(auStack_300,uVar8);
            uStack_30 = auStack_300._0_4_;
            fStack_2c = auStack_300._4_4_;
            uStack_28 = uStack_2f8;
            uStack_24 = uStack_2f4;
            auStack_10._4_4_ = 0;
            fVar18 = (chr(iVar13,iVar15)->f2c0 +
                     chr(iVar13,iVar15)->f2c8) * 0.6;
            if (fVar18 < chr(iVar13,iVar15)->f2a4 * 1.2) {
              fVar18 = chr(iVar13,iVar15)->f2a4 * 1.2;
            }
            fVar16 = (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370)
                     + *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)
                     ) * 0.6;
            if (fVar16 < *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                   0x354) * 1.2) {
              fVar16 = *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x354)
                       * 1.2;
            }
            fVar17 = (float)Length__7FVectorCFv(auStack_10);
            if (fVar17 <= fVar18 + fVar16) {
              fVar18 = (float)Length__7FVectorCFv(iVar13 + chr(iVar13,iVar15)->fc *
                                                       0x510 + 0x370);
              fVar16 = (float)Length__7FVectorCFv(iVar13 + iVar15 * 0x510 + 0x370);
              if (fVar16 < fVar18) {
                SetBtlMotion__8BtlModelFif
                          (0x3faaaaab,chr(iVar13,iVar15)->pModel,0x25);
                for (fVar18 = 180.0 - fStack_2c; fVar18 < -180.0; fVar18 = fVar18 + 360.0) {
                }
                for (; 180.0 < fVar18; fVar18 = fVar18 - 360.0) {
                }
                chr(iVar13,iVar15)->fd4 = fVar18;
                SetAngle__8BtlModelFP7FVector
                          (chr(iVar13,iVar15)->pModel,
                           iVar13 + iVar15 * 0x510 + 0x180);
              }
            }
          }
        }
        else {
          chr(iVar13,iVar15)->bState = 7;
          chr(iVar13,iVar15)->bState2 = 0;
          iVar4 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar4 + 0xb4) = *(byte *)(iVar4 + 0xb4) & 0xbf;
          auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
          auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
          auVar19 = _vadd(auVar19,auVar20);
          auStack_3f0 = _sqc2(auVar19);
          __ct__7FVectorFPC7FVector(auStack_2d0,auStack_3f0);
          iVar4 = iVar13 + iVar15 * 0x510;
          *(int *)(iVar4 + 0x170) = auStack_2d0._0_4_;
          *(int *)(iVar4 + 0x174) = auStack_2d0._4_4_;
          *(undefined4 *)(iVar4 + 0x178) = uStack_2c8;
          *(undefined4 *)(iVar4 + 0x17c) = uStack_2c4;
          chr(iVar13,iVar15)->fc4 = 0;
          iVar13->wTurnPendMask = 0;
        }
      }
    }
    else {
      uStack_288 = chr(iVar13,iVar15)->f30;
      uStack_290 = chr(iVar13,iVar15)->f2c;
      uStack_28c = 0;
      uStack_284 = 0x3f800000;
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x170));
      auVar19._4_4_ = 0;
      auVar19._0_4_ = uStack_290;
      auVar19._8_4_ = uStack_288;
      auVar19._12_4_ = 0x3f800000;
      auVar19 = _lqc2(auVar19);
      auVar19 = _vsub(auVar20,auVar19);
      auStack_3d0 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_280,auStack_3d0);
      uVar8 = __ct__7FVectorFPC7FVector(auStack_2b0,auStack_10);
      Get3DAngle__F7FVector(auStack_2a0,uVar8);
      uStack_30 = auStack_2a0._0_4_;
      fStack_2c = auStack_2a0._4_4_;
      uStack_28 = uStack_298;
      uStack_24 = uStack_294;
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x170));
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
      auVar19 = _vsub(auVar19,auVar20);
      auStack_3e0 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_2c0,auStack_3e0);
      iVar4 = iVar13 + iVar15 * 0x510;
      *(int *)(iVar4 + 0x160) = auStack_2c0._0_4_;
      *(int *)(iVar4 + 0x164) = auStack_2c0._4_4_;
      *(undefined4 *)(iVar4 + 0x168) = uStack_2b8;
      *(undefined4 *)(iVar4 + 0x16c) = uStack_2b4;
      chr(iVar13,iVar15)->fb4 = 0;
      ChangeBtlChrAngle__7CBattleFif(180.0 - fStack_2c,param_2,param_3);
      chr(iVar13,iVar15)->bState = 7;
      chr(iVar13,iVar15)->bState2 = 0;
      iVar13 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar13 + 0xb4) = *(byte *)(iVar13 + 0xb4) & 0xbf;
    }
  }
  else if (cVar3 == '\x03') {
    cVar3 = DestinationSearch__7CBattleFi(param_2,param_3);
    if (cVar3 == '\x01') {
      if (4 < iVar13->nDestCount) {
        DestinationListUp__7CBattleFii(param_2,4,param_3);
      }
      iVar13->nDestIdx = 0;
      iVar4 = rand();
      iVar4 = iVar4 % (int)iVar13->nDestCount;
      chr(iVar13,iVar15)->bState2 = 10;
      chr(iVar13,iVar15)->aDest =
           *(undefined4 *)(iVar13 + iVar4 * 8 + 0x403c);
      chr(iVar13,iVar15)->fc4 = 0;
      chr(iVar13,iVar15)->fc8 =
           *(undefined4 *)(iVar13 + iVar4 * 8 + 0x4040);
      GetMoveAngle__7CBattleFi(param_2,param_3);
      iVar4 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar4 + 0xb4) = *(byte *)(iVar4 + 0xb4) & 0xbf | 0x40;
    }
    if ((((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) != 1) &&
         (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) != 0x25)) &&
        (chr(iVar13,iVar15)->f4b0 != 0)) &&
       (fVar18 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(iVar13,iVar15)->pModel,0),
       0.8 <= fVar18)) {
      (**(code **)(*(int *)(chr(iVar13,iVar15)->f4b0 + 0x14) + 0x40))();
      chr(iVar13,iVar15)->f4b0 = 0;
    }
    if (((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 1) &&
        ((((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 7)
          >> 1 == 1 ||
         (((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 7)
          >> 1 == 2)))) &&
       ((-1 < (long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                     0xb0) << 0x3a) &&
        (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 1)))) {
      auVar19 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_3a0 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(&uStack_230,auStack_3a0);
      auStack_10._8_4_ = uStack_228;
      auStack_10._0_8_ = uStack_230;
      auStack_10._12_4_ = uStack_224;
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x360));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_3b0 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_240,auStack_3b0);
      auVar20 = _lqc2(auStack_240);
      auVar19 = _lqc2(auStack_10);
      auVar19 = _vsub(auVar19,auVar20);
      auStack_10 = _sqc2(auVar19);
      uVar8 = __ct__7FVectorFPC7FVector(auStack_260,auStack_10);
      Get3DAngle__F7FVector(auStack_250,uVar8);
      uStack_30 = auStack_250._0_4_;
      fStack_2c = auStack_250._4_4_;
      uStack_28 = uStack_248;
      uStack_24 = uStack_244;
      auStack_10._4_4_ = 0;
      fVar18 = (chr(iVar13,iVar15)->f2c0 +
               chr(iVar13,iVar15)->f2c8) * 0.6;
      if (fVar18 < chr(iVar13,iVar15)->f2a4 * 1.2) {
        fVar18 = chr(iVar13,iVar15)->f2a4 * 1.2;
      }
      fVar16 = (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
               *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) * 0.6;
      if (fVar16 < *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x354) *
                   1.2) {
        fVar16 = *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x354) * 1.2
        ;
      }
      fVar17 = (float)Length__7FVectorCFv(auStack_10);
      if (fVar17 <= fVar18 + fVar16) {
        fVar18 = (float)Length__7FVectorCFv(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                        0x370);
        fVar16 = (float)Length__7FVectorCFv(iVar13 + iVar15 * 0x510 + 0x370);
        if (fVar16 < fVar18) {
          SetBtlMotion__8BtlModelFif
                    (0x3faaaaab,chr(iVar13,iVar15)->pModel,0x25);
          for (fVar18 = 180.0 - fStack_2c; fVar18 < -180.0; fVar18 = fVar18 + 360.0) {
          }
          for (; 180.0 < fVar18; fVar18 = fVar18 - 360.0) {
          }
          chr(iVar13,iVar15)->fd4 = fVar18;
          SetAngle__8BtlModelFP7FVector
                    (chr(iVar13,iVar15)->pModel,
                     iVar13 + iVar15 * 0x510 + 0x180);
          return;
        }
      }
      lVar10 = BtlEndCheck__7CBattleFv(param_2);
      bVar1 = (*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 1) == 0
              || 0 < *(int *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x130);
      if (((long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4)
                 << 0x3c) < 0) &&
         (*(char *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x1a3) != '\x03')) {
        bVar1 = true;
      }
      if ((lVar10 != 0) && (bVar1)) {
        chr(iVar13,iVar15)->bState = 7;
        chr(iVar13,iVar15)->bState2 = 0;
        iVar4 = iVar13 + iVar15 * 0x510;
        *(byte *)(iVar4 + 0xb4) = *(byte *)(iVar4 + 0xb4) & 0xbf;
        auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
        auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
        auVar19 = _vadd(auVar19,auVar20);
        auStack_3c0 = _sqc2(auVar19);
        __ct__7FVectorFPC7FVector(auStack_270,auStack_3c0);
        iVar4 = iVar13 + iVar15 * 0x510;
        *(int *)(iVar4 + 0x170) = auStack_270._0_4_;
        *(int *)(iVar4 + 0x174) = auStack_270._4_4_;
        *(undefined4 *)(iVar4 + 0x178) = uStack_268;
        *(undefined4 *)(iVar4 + 0x17c) = uStack_264;
        chr(iVar13,iVar15)->fc4 = 0;
        iVar13->wTurnPendMask = 0;
      }
    }
  }
  else if (cVar3 == '\x02') {
    if ((((long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb0)
                << 0x3a) < 0) && (chr(iVar13,iVar15)->f28 == 0)) &&
       (iVar11 = iVar13 + iVar15 * 0x510,
       *(float *)(iVar11 + 0x114) = *(float *)(iVar11 + 0x114) - iVar13->flDeltaT,
       chr(iVar13,iVar15)->f64 <= 0.0)) {
      ComboStopOff__Fi(0xffffffffffffffff);
      chr(iVar13,iVar15)->f28 = 1;
    }
    if ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x3e) < 0) {
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0xfe;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0xfd;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(short *)(iVar11 + 0x3c8) = *(short *)(iVar11 + 0x3c8) + 1;
      chr(iVar13,iVar15)->f43e = 0xffff;
      chr(iVar13,iVar15)->f43c = 0xffff;
      chr(iVar13,iVar15)->f43a = 0xffff;
      chr(iVar13,iVar15)->f438 = 0xffff;
    }
    if ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x3d) < 0) {
      iVar11 = iVar13 + iVar15 * 0x510;
      *(short *)(iVar11 + 0x3c6) = *(short *)(iVar11 + 0x3c6) + 1;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0xfb;
      if (((chr(iVar13,iVar15)->f314 != -1) &&
          ((long)chr(iVar13,iVar15)->f314 <=
           (long)(ulong)chr(iVar13,iVar15)->f316)) ||
         ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x3c) < 0)) {
        iVar11 = iVar13 + iVar15 * 0x510;
        *(byte *)(iVar11 + 0x3c1) = *(byte *)(iVar11 + 0x3c1) & 0xfb | 4;
      }
      if (((0 < chr(iVar13,iVar15)->f312) && (iVar13->wTurnPendMask != 0)) &&
         (((long)chr(iVar13,iVar15)->f312 <=
           (long)(ulong)chr(iVar13,iVar15)->f316 &&
          (((-1 < (long)((ulong)chr(iVar13,iVar15)->f310 << 0x3a) &&
            (-1 < (long)((ulong)chr(iVar13,iVar15)->f310 << 0x39))) &&
           (iVar13->wTurnPendMask != 0)))))) {
        iVar13->bFlags25 = iVar13->bFlags25 & 0xf7;
      }
    }
    if ((chr(iVar13,iVar15)->f311 & 1) != 0) {
      chr(iVar13,iVar15)->f43e = 0xffff;
      chr(iVar13,iVar15)->f43c = 0xffff;
      chr(iVar13,iVar15)->f43a = 0xffff;
      chr(iVar13,iVar15)->f438 = 0xffff;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c1) = *(byte *)(iVar11 + 0x3c1) & 0xfe;
      chr(iVar13,iVar15)->f318 = 0;
    }
    chr(iVar13,iVar15)->f450 = 0;
    if ((chr(iVar13,iVar15)->f314 == -1) ||
       ((long)(ulong)chr(iVar13,iVar15)->f316 <
        (long)chr(iVar13,iVar15)->f314)) {
      if (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 5) {
        chr(iVar13,iVar15)->f450 =
             iVar5 + (uint)chr(iVar13,iVar15)->f316 * 0x48;
        if ((long)chr(iVar13,iVar15)->f314 <=
            (long)(int)(chr(iVar13,iVar15)->f316 + 1)) {
          iVar4 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
        }
      }
      else if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1f) ||
              (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1c)) {
        if (chr(iVar13,iVar15)->f318 < 2) {
          if ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x38) < 0) {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 0xc) * 0x48;
            if (chr(iVar13,iVar15)->f318 == 1) {
              iVar4 = iVar13 + iVar15 * 0x510;
              *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
            }
          }
          else {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 3) * 0x48;
          }
        }
      }
      else if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x20) ||
              (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1d)) {
        if (chr(iVar13,iVar15)->f318 < 3) {
          if ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x38) < 0) {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 0xe) * 0x48;
            if (chr(iVar13,iVar15)->f318 == 2) {
              iVar4 = iVar13 + iVar15 * 0x510;
              *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
            }
          }
          else {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 5) * 0x48;
          }
        }
      }
      else if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x21) ||
              (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1e)) {
        if (chr(iVar13,iVar15)->f318 < 4) {
          if ((long)((ulong)chr(iVar13,iVar15)->f310 << 0x38) < 0) {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 0x11) * 0x48;
            if (chr(iVar13,iVar15)->f318 == 3) {
              iVar4 = iVar13 + iVar15 * 0x510;
              *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
            }
          }
          else {
            chr(iVar13,iVar15)->f450 =
                 iVar5 + ((uint)chr(iVar13,iVar15)->f318 +
                         (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 8) * 0x48;
          }
        }
      }
      else if ((((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 10) ||
                (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xd)) ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x10)) ||
              ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x13 ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x19)))) {
        chr(iVar13,iVar15)->f450 =
             iVar5 + (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) * 0x48;
        if (((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 10) ||
            ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xd ||
             (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x10)))) ||
           (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x13)) {
          if (*(short *)(chr(iVar13,iVar15)->pModel + 0x512) != 0) {
            iVar4 = iVar13 + iVar15 * 0x510;
            *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
          }
        }
        else {
          iVar4 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
        }
      }
      else if ((((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xb) ||
                (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xe)) ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x11)) ||
              ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x14 ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1a)))) {
        chr(iVar13,iVar15)->f450 =
             iVar5 + ((uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 1) * 0x48;
        if (((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xb) ||
            ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xe ||
             (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x11)))) ||
           (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x14)) {
          if (*(short *)(chr(iVar13,iVar15)->pModel + 0x512) != 0) {
            iVar4 = iVar13 + iVar15 * 0x510;
            *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
          }
        }
        else {
          iVar4 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
        }
      }
      else if ((((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xc) ||
                (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xf)) ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x12)) ||
              ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x15 ||
               (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x1b)))) {
        chr(iVar13,iVar15)->f450 =
             iVar5 + ((uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 2) * 0x48;
        if (((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xc) ||
            ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xf ||
             (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x12)))) ||
           (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x15)) {
          if (*(short *)(chr(iVar13,iVar15)->pModel + 0x512) != 0) {
            iVar4 = iVar13 + iVar15 * 0x510;
            *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
          }
        }
        else {
          iVar4 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar4 + 0x3c1) = *(byte *)(iVar4 + 0x3c1) & 0xfd | 2;
        }
      }
    }
    if ((((long)((ulong)chr(iVar13,iVar15)->f311 << 0x3d) < 0) &&
        (chr(iVar13,iVar15)->f4b0 != 0)) &&
       (fVar18 = (float)getSequenceProgress__5ModelFQ25Model10MotionKind(chr(iVar13,iVar15)->pModel,0),
       0.8 <= fVar18)) {
      (**(code **)(*(int *)(chr(iVar13,iVar15)->f4b0 + 0x14) + 0x40))();
      chr(iVar13,iVar15)->f4b0 = 0;
    }
    for (iVar4 = chr(iVar13,iVar15)->f4a8;
        (iVar4 != 0 && (iVar4->nCmdKind != 10)); iVar4 = *(int *)(iVar4 + 0x3c)) {
    }
    if (((long)((ulong)chr(iVar13,iVar15)->f311 << 0x3d) < 0) && (iVar4 == 0)) {
      chr(iVar13,iVar15)->f450 = 0;
      chr(iVar13,iVar15)->bState2 = 3;
    }
    else {
      if ((((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 7)
           >> 1 == 1) &&
         (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xf4) != 0.0)) {
        fStack_1c8 = (float)GetFlightTime__7CBattleFi
                                      (param_2,chr(iVar13,iVar15)->fc);
        fStack_1c8 = *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xec) *
                     fStack_1c8;
        uStack_1d0 = 0;
        uStack_1cc = 0;
        uStack_1c4 = 0;
        auStack_10 = ZEXT416((uint)fStack_1c8) << 0x40;
        auVar19 = _vmr32(in_vf0);
        auVar20 = _vmr32(auVar19);
        auVar21 = _vmr32(auVar20);
        auStack_40 = _sqc2(in_vf0);
        auStack_50 = _sqc2(auVar19);
        auStack_60 = _sqc2(auVar20);
        auStack_70 = _sqc2(auVar21);
        uVar6 = GetRad(*(undefined4 *)
                                 (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x184)
                               );
        sceVu0RotMatrixY(uVar6,auStack_70,auStack_70);
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_1e0,auStack_70,auStack_10);
        auStack_10._8_4_ = uStack_1d8;
        auStack_10._0_8_ = uStack_1e0;
        auStack_10._12_4_ = uStack_1d4;
        auVar19 = _lqc2(*(undefined1 (*) [16])
                         (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
        auVar20 = _lqc2(*(undefined1 (*) [16])
                         (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
        auVar19 = _vadd(auVar19,auVar20);
        auStack_380 = _sqc2(auVar19);
        __ct__7FVectorFPC7FVector(auStack_1f0,auStack_380);
        auVar20 = _lqc2(auStack_1f0);
        auVar19 = _lqc2(auStack_10);
        auVar19 = _vadd(auVar19,auVar20);
        auStack_10 = _sqc2(auVar19);
      }
      else {
        auVar19 = _lqc2(*(undefined1 (*) [16])
                         (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
        auVar20 = _lqc2(*(undefined1 (*) [16])
                         (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
        auVar19 = _vadd(auVar19,auVar20);
        auStack_370 = _sqc2(auVar19);
        __ct__7FVectorFPC7FVector(&uStack_1c0,auStack_370);
        auStack_10._8_4_ = uStack_1b8;
        auStack_10._0_8_ = uStack_1c0;
        auStack_10._12_4_ = uStack_1b4;
      }
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x360));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_390 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_200,auStack_390);
      auVar20 = _lqc2(auStack_200);
      auVar19 = _lqc2(auStack_10);
      auVar19 = _vsub(auVar19,auVar20);
      auStack_10 = _sqc2(auVar19);
      uVar8 = __ct__7FVectorFPC7FVector(auStack_220,auStack_10);
      Get3DAngle__F7FVector(auStack_210,uVar8);
      uStack_30 = auStack_210._0_4_;
      fStack_2c = auStack_210._4_4_;
      uStack_28 = uStack_208;
      uStack_24 = uStack_204;
      for (fVar18 = (180.0 - fStack_2c) - chr(iVar13,iVar15)->fd4;
          fVar18 < -180.0; fVar18 = fVar18 + 360.0) {
      }
      for (; 180.0 < fVar18; fVar18 = fVar18 - 360.0) {
      }
      if (iVar13->flDeltaT == 0.0) {
        fVar18 = 0.0;
      }
      else if ((long)((ulong)chr(iVar13,iVar15)->bFlagsB << 0x3a) < 0) {
        fVar18 = fVar18 / (iVar13->flDeltaT * 60.0 * 4.0);
      }
      else {
        fVar18 = fVar18 / (iVar13->flDeltaT * 60.0 * 8.0);
      }
      iVar4 = iVar13 + iVar15 * 0x510;
      *(float *)(iVar4 + 0x184) = *(float *)(iVar4 + 0x184) + fVar18;
      SetAngle__8BtlModelFP7FVector
                (chr(iVar13,iVar15)->pModel,iVar13 + iVar15 * 0x510 + 0x180);
    }
  }
  else {
    if (cVar3 != '\x01') {
      if (cVar3 != '\0') {
        return;
      }
      if (chr(iVar13,iVar15)->nMonId != 499) {
        SetNextBtlMotion__8BtlModelFif
                  (0x3f800000,chr(iVar13,iVar15)->pModel,4);
      }
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0xb4) = *(byte *)(iVar11 + 0xb4) & 0xbf | 0x40;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0xb7) = *(byte *)(iVar11 + 0xb7) & 0xf9;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0xb7) = *(byte *)(iVar11 + 0xb7) & 0xfe;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0xb4) = *(byte *)(iVar11 + 0xb4) & 0x7f | 0x80;
      chr(iVar13,iVar15)->f4dc = 0xff;
      chr(iVar13,iVar15)->f4dd = 0;
      chr(iVar13,iVar15)->f4de = 0xff;
      if ((chr(iVar13,iVar15)->f4c0 != -1) &&
         (chr(iVar13,iVar15)->nMonId != 499)) {
        auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
        auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
        auVar19 = _vadd(auVar19,auVar20);
        auStack_320 = _sqc2(auVar19);
        __ct__7FVectorFPC7FVector(&uStack_90,auStack_320);
        auStack_10._8_4_ = uStack_88;
        auStack_10._0_8_ = uStack_90;
        auStack_10._12_4_ = uStack_84;
        uVar6 = PlaySEHold__6HNMSndFUibP7FVector(uGpffff8374,0x60002000,1,auStack_10);
        chr(iVar13,iVar15)->f4cc = uVar6;
      }
      if (iVar13->nComboCnt != 0) {
        SetBattleBlear__11CBtlPAfter2Fifff(0x3f4ccccd,0x3f800000,0x3e800000,uGpffff8618,param_3);
      }
      *(undefined4 *)(iVar13 + iVar15 * 0x510 + 200) = 0;
      chr(iVar13,iVar15)->f1c = 0;
      chr(iVar13,iVar15)->f24 = 0;
      chr(iVar13,iVar15)->f68 = 0;
      chr(iVar13,iVar15)->bState2 = 1;
    }
    iVar11 = iVar13 + iVar15 * 0x510;
    *(int *)(iVar11 + 0xcc) = *(int *)(iVar11 + 0xcc) + 1;
    if ((*(byte *)(iVar4 + 2) & 7) == 0) {
      auVar19 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_330 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_a0,auStack_330);
      iVar11 = iVar13 + iVar15 * 0x510;
      *(int *)(iVar11 + 0x170) = auStack_a0._0_4_;
      *(int *)(iVar11 + 0x174) = auStack_a0._4_4_;
      *(undefined4 *)(iVar11 + 0x178) = uStack_98;
      *(undefined4 *)(iVar11 + 0x17c) = uStack_94;
      chr(iVar13,iVar15)->fc4 = 0;
      if ((((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb4) & 7)
           >> 1 == 1) &&
         (*(char *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb8) == '\x1e')) {
        if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 4) &&
           (-1 < (long)((ulong)*(byte *)(chr(iVar13,iVar15)->pModel + 0x4d0) << 0x3d)
           )) {
          fVar18 = *(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 6.25 +
                   (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
                   *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) /
                   2.0;
        }
        else {
          fVar18 = *(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 5.0 +
                   (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
                   *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) /
                   2.0;
        }
      }
      else if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 4) &&
              (-1 < (long)((ulong)*(byte *)(chr(iVar13,iVar15)->pModel + 0x4d0) <<
                          0x3d))) {
        fVar18 = *(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 11.25 +
                 (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
                 *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) /
                 2.0;
      }
      else {
        fVar18 = *(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 10.0 +
                 (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
                 *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) /
                 2.0;
      }
      if (chr(iVar13,iVar15)->bState == '\x0e') {
        fVar18 = fVar18 + chr(iVar13,iVar15)->f2a4 +
                          *(float *)(iVar4 + 4) *
                          *(float *)(chr(iVar13,iVar15)->pModel + 0x500);
      }
      else {
        if (chr(iVar13,iVar15)->f312 < 1) {
          unaff_s1_lo = 999;
        }
        else {
          if (0 < *(short *)(iVar4 + 0x16)) {
            unaff_s1_lo = (int)chr(iVar13,iVar15)->f314 /
                          (int)*(short *)(iVar4 + 0x16);
          }
          if ((chr(iVar13,iVar15)->f312 ==
               chr(iVar13,iVar15)->f314) &&
             (chr(iVar13,iVar15)->f31e != '\0')) {
            unaff_s1_lo = unaff_s1_lo + -1;
          }
        }
        if (unaff_s1_lo < 2) {
          fVar18 = fVar18 + chr(iVar13,iVar15)->f2a4 +
                            *(float *)(iVar4 + 4) *
                            *(float *)(chr(iVar13,iVar15)->pModel + 0x500);
        }
        else {
          fVar18 = fVar18 + chr(iVar13,iVar15)->f2a4 +
                            *(float *)(iVar4 + 8) *
                            *(float *)(chr(iVar13,iVar15)->pModel + 0x500);
        }
      }
      if ((*(short *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x19c) == 0x212)
         || (*(short *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x19c) == 0x213)
         ) {
        fVar18 = fVar18 + (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                     0x354) -
                          (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                     0x370) +
                          *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 +
                                    0x378)) / 2.0);
      }
      iVar11 = chr(iVar13,iVar15)->fc;
      if (-1 < chr(iVar13,iVar15)->f20) {
        fVar18 = fVar18 + *(float *)(iVar13 + chr(iVar13,iVar15)->f20 * 0x510 +
                                    0x354) * 2.0 + 5.0;
        iVar11 = chr(iVar13,iVar15)->f20;
      }
      bVar1 = false;
      if (chr(iVar13,iVar15)->f10 == 0) {
        if ((chr(iVar13,iVar15)->f24 == 0) &&
           ((*(byte *)(iVar13->pCamera + 0x19) & 1) != 0)) {
          iVar12 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar12 + 0xb7) = *(byte *)(iVar12 + 0xb7) & 0xfe | 1;
          uVar8 = __ct__7FVectorFPC7FVector(auStack_100,iVar13 + iVar15 * 0x510 + 0x170);
          cVar3 = HomingMove__7CBattleFi7FVectorifff
                            (this,fVar18,0x41700000,param_2,param_3,uVar8,iVar11);
          bVar1 = cVar3 == '\x01';
          chr(iVar13,iVar15)->f24 = 1;
        }
        else {
          uVar8 = __ct__7FVectorFPC7FVector(auStack_110,iVar13 + iVar15 * 0x510 + 0x170);
          cVar3 = HomingMove__7CBattleFi7FVectorifff(this,fVar18,0,param_2,param_3,uVar8,iVar11);
          if (cVar3 == '\x01') {
            bVar1 = true;
          }
        }
      }
      else {
        uStack_a8 = chr(iVar13,iVar15)->f30;
        uStack_b0 = chr(iVar13,iVar15)->f2c;
        uStack_ac = 0;
        uStack_a4 = 0x3f800000;
        auStack_10._4_4_ = 0;
        auStack_10._0_4_ = uStack_b0;
        auStack_10._8_4_ = uStack_a8;
        auStack_10._12_4_ = 0x3f800000;
        if ((chr(iVar13,iVar15)->f24 == 0) &&
           ((*(byte *)(iVar13->pCamera + 0x19) & 1) != 0)) {
          uVar8 = __ct__7FVectorFPC7FVector(auStack_c0,iVar13 + iVar15 * 0x510 + 0x170);
          uVar9 = __ct__7FVectorFPC7FVector(auStack_d0,auStack_10);
          cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                            (this,fVar18,0x41700000,param_2,param_3,uVar8,iVar11,uVar9);
          bVar1 = cVar3 == '\x01';
          chr(iVar13,iVar15)->f24 = 1;
        }
        else {
          uVar8 = __ct__7FVectorFPC7FVector(auStack_e0,iVar13 + iVar15 * 0x510 + 0x170);
          uVar9 = __ct__7FVectorFPC7FVector(auStack_f0,auStack_10);
          cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                            (this,fVar18,0,param_2,param_3,uVar8,iVar11,uVar9);
          if (cVar3 == '\x01') {
            bVar1 = true;
          }
        }
      }
    }
    else {
      uStack_118 = chr(iVar13,iVar15)->f30;
      uStack_120 = chr(iVar13,iVar15)->f2c;
      uStack_11c = 0;
      uStack_114 = 0x3f800000;
      auStack_10._4_4_ = 0;
      auStack_10._0_4_ = uStack_120;
      auStack_10._8_4_ = uStack_118;
      auStack_10._12_4_ = 0x3f800000;
      auVar19 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])
                       (iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x360));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_420 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_140,auStack_420);
      auVar19 = _lqc2(auStack_140);
      auVar20 = _lqc2(auStack_10);
      auVar19 = _vsub(auVar19,auVar20);
      auStack_340 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(&uStack_130,auStack_340);
      auStack_20._8_4_ = uStack_128;
      auStack_20._0_8_ = uStack_130;
      auStack_20._12_4_ = uStack_124;
      auStack_20._0_8_ = uStack_130 & 0xffffffff;
      Normalize__7FVectorFv(auStack_20);
      __amu__7FVectorFf(*(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 11.25 +
                      (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370)
                      + *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378
                                  )) / 2.0,auStack_20);
      auVar20 = _lqc2(auStack_10);
      auVar19 = _lqc2(auStack_20);
      auVar19 = _vadd(auVar19,auVar20);
      auStack_20 = _sqc2(auVar19);
      iVar11 = iVar13 + iVar15 * 0x510;
      *(int *)(iVar11 + 0x170) = auStack_20._0_4_;
      *(int *)(iVar11 + 0x174) = auStack_20._4_4_;
      *(undefined4 *)(iVar11 + 0x178) = auStack_20._8_4_;
      *(undefined4 *)(iVar11 + 0x17c) = auStack_20._12_4_;
      chr(iVar13,iVar15)->fc4 = 0;
      fVar18 = *(float *)(chr(iVar13,iVar15)->pModel + 0x500) * 11.25 +
               (*(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x370) +
               *(float *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0x378)) / 2.0;
      iVar11 = chr(iVar13,iVar15)->fc;
      if (-1 < chr(iVar13,iVar15)->f20) {
        fVar18 = fVar18 + *(float *)(iVar13 + chr(iVar13,iVar15)->f20 * 0x510 +
                                    0x354) * 2.0 + 5.0;
        iVar11 = chr(iVar13,iVar15)->f20;
      }
      bVar1 = false;
      if (chr(iVar13,iVar15)->f10 == 0) {
        bVar1 = true;
      }
      else if ((chr(iVar13,iVar15)->f24 == 0) &&
              ((*(byte *)(iVar13->pCamera + 0x19) & 1) != 0)) {
        iVar12 = iVar13 + iVar15 * 0x510;
        *(byte *)(iVar12 + 0xb7) = *(byte *)(iVar12 + 0xb7) & 0xfe | 1;
        uVar8 = __ct__7FVectorFPC7FVector(auStack_150,iVar13 + iVar15 * 0x510 + 0x170);
        uVar9 = __ct__7FVectorFPC7FVector(auStack_160,auStack_10);
        cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                          (this,fVar18,0x41700000,param_2,param_3,uVar8,iVar11,uVar9);
        bVar1 = cVar3 == '\x01';
        chr(iVar13,iVar15)->f24 = 1;
      }
      else {
        uVar8 = __ct__7FVectorFPC7FVector(auStack_170,iVar13 + iVar15 * 0x510 + 0x170);
        uVar9 = __ct__7FVectorFPC7FVector(auStack_180,auStack_10);
        cVar3 = HomingMoveEX__7CBattleFi7FVectori7FVectorfff
                          (this,fVar18,0,param_2,param_3,uVar8,iVar11,uVar9);
        if (cVar3 == '\x01') {
          bVar1 = true;
        }
      }
    }
    if ((bVar1) || (chr(iVar13,iVar15)->nMonId == 499)) {
      if (-1 < chr(iVar13,iVar15)->f20) {
        uVar6 = chr(iVar13,iVar15)->fc;
        chr(iVar13,iVar15)->fc =
             chr(iVar13,iVar15)->f20;
        chr(iVar13,iVar15)->f20 = uVar6;
      }
      if ((chr(iVar13,iVar15)->f4c0 != -1) &&
         (chr(iVar13,iVar15)->f4cc != -1)) {
        SetSEEnd__6HNMSndFUii(uGpffff8374,0x60002000,chr(iVar13,iVar15)->f4cc);
      }
      chr(iVar13,iVar15)->f4cc = 0xffffffff;
      chr(iVar13,iVar15)->bState2 = 2;
      if ((long)((ulong)*(byte *)(iVar13 + chr(iVar13,iVar15)->fc * 0x510 + 0xb0)
                << 0x3a) < 0) {
        if ((chr(iVar13,iVar15)->bState != '\x0e') ||
           ((float)(int)*(short *)(iVar4 + 0x10) <= 0.0)) {
          if ((chr(iVar13,iVar15)->bState != '\x0f') ||
             ((float)(int)*(short *)(iVar4 + 0x12) <= 0.0)) {
            ComboStopOff__Fi(0xffffffffffffffff);
            chr(iVar13,iVar15)->f28 = 1;
          }
          else {
            chr(iVar13,iVar15)->f64 =
                 (float)(int)*(short *)(iVar4 + 0x12) / 30.0;
            chr(iVar13,iVar15)->f28 = 0;
          }
        }
        else {
          chr(iVar13,iVar15)->f64 = (float)(int)*(short *)(iVar4 + 0x10) / 30.0;
          chr(iVar13,iVar15)->f28 = 0;
        }
      }
      else {
        ComboStopOff__Fi(0xffffffffffffffff);
        chr(iVar13,iVar15)->f28 = 1;
      }
      iVar12 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar12 + 0xb4) = *(byte *)(iVar12 + 0xb4) & 0xbf;
      iVar12 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar12 + 0xb4) = *(byte *)(iVar12 + 0xb4) & 0x7f;
      chr(iVar13,iVar15)->f310 = 0;
      if (chr(iVar13,iVar15)->bState == '\x0e') {
        switch(*(undefined1 *)(iVar4 + 2)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          break;
        case 8:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(iVar13,iVar15)->pModel,0x19);
          break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(iVar13,iVar15)->pModel,0x1a);
          break;
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x1f:
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(iVar13,iVar15)->pModel,0x1b);
          break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x58:
        case 0x59:
        case 0x5a:
        case 0x5b:
        case 0x5c:
        case 0x5d:
        case 0x5e:
        case 0x5f:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else {
            cVar3 = chr(iVar13,iVar15)->f31e;
            if (cVar3 == '\x03') {
              if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                 (chr(iVar13,iVar15)->nCharId == 2)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x18);
              }
              else if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                      (chr(iVar13,iVar15)->nCharId == 0xd)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x15);
              }
              else {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0xc);
              }
            }
            else if (cVar3 == '\x02') {
              if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                 (chr(iVar13,iVar15)->nCharId == 2)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x17);
              }
              else if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                      (chr(iVar13,iVar15)->nCharId == 0xd)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x14);
              }
              else {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0xb);
              }
            }
            else if (cVar3 == '\x01') {
              if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                 (chr(iVar13,iVar15)->nCharId == 2)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x16);
              }
              else if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
                      (chr(iVar13,iVar15)->nCharId == 0xd)) {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,0x13);
              }
              else {
                SetNextBtlMotion__8BtlModelFif
                          (0x3f800000,chr(iVar13,iVar15)->pModel,10);
              }
            }
            else {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,5);
            }
          }
          break;
        case 0x28:
        case 0x29:
        case 0x2a:
        case 0x2b:
        case 0x2c:
        case 0x2d:
        case 0x2e:
        case 0x2f:
        case 0x60:
        case 0x61:
        case 0x62:
        case 99:
        case 100:
        case 0x65:
        case 0x66:
        case 0x67:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x01') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,10);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          break;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x68:
        case 0x69:
        case 0x6a:
        case 0x6b:
        case 0x6c:
        case 0x6d:
        case 0x6e:
        case 0x6f:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x02') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0xb);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          break;
        case 0x38:
        case 0x39:
        case 0x3a:
        case 0x3b:
        case 0x3c:
        case 0x3d:
        case 0x3e:
        case 0x3f:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x03') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0xc);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          break;
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x78:
        case 0x79:
        case 0x7a:
        case 0x7b:
        case 0x7c:
        case 0x7d:
        case 0x7e:
        case 0x7f:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x01') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x19);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          break;
        case 0x48:
        case 0x49:
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4e:
        case 0x4f:
        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x85:
        case 0x86:
        case 0x87:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x02') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1a);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          break;
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x88:
        case 0x89:
        case 0x8a:
        case 0x8b:
        case 0x8c:
        case 0x8d:
        case 0x8e:
        case 0x8f:
          if ((chr(iVar13,iVar15)->f312 == 0) ||
             (*(short *)(iVar4 + 0x16) < chr(iVar13,iVar15)->f312)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
          else if (chr(iVar13,iVar15)->f31e == '\x03') {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1b);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          }
        }
      }
      else {
        if (chr(iVar13,iVar15)->f314 < 1) {
          iVar11 = 999;
        }
        else {
          if (0 < *(short *)(iVar4 + 0x16)) {
            iVar11 = (int)chr(iVar13,iVar15)->f314 /
                     (int)*(short *)(iVar4 + 0x16);
          }
          if ((chr(iVar13,iVar15)->f312 ==
               chr(iVar13,iVar15)->f314) &&
             (chr(iVar13,iVar15)->f31e != '\0')) {
            iVar11 = iVar11 + -1;
          }
        }
        switch(iVar11) {
        default:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f;
          iVar11 = rand();
          iVar11 = iVar11 % 3;
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            if (iVar11 == 0) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1c);
            }
            else if (iVar11 == 1) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1d);
            }
            else {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1e);
            }
          }
          else if (iVar11 == 0) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1f);
          }
          else if (iVar11 == 1) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x20);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x21);
          }
          break;
        case 1:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f | 0x80;
          SetNextBtlMotion__8BtlModelFif
                    (0x3f800000,chr(iVar13,iVar15)->pModel,5);
          break;
        case 2:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f | 0x80;
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1c);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1f);
          }
          break;
        case 3:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f | 0x80;
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1d);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x20);
          }
          break;
        case 4:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f | 0x80;
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1e);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x21);
          }
          break;
        case 5:
        case 8:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f;
          uVar7 = rand();
          uVar14 = uVar7 & 1;
          if (((int)uVar7 < 0) && (uVar14 != 0)) {
            uVar14 = uVar14 - 2;
          }
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            if (uVar14 == 0) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1c);
            }
            else {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1d);
            }
          }
          else if (uVar14 == 0) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1f);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x20);
          }
          break;
        case 6:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f;
          uVar7 = rand();
          uVar14 = uVar7 & 1;
          if (((int)uVar7 < 0) && (uVar14 != 0)) {
            uVar14 = uVar14 - 2;
          }
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            if (uVar14 == 0) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1c);
            }
            else {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1e);
            }
          }
          else if (uVar14 == 0) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x1f);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x21);
          }
          break;
        case 7:
          iVar11 = iVar13 + iVar15 * 0x510;
          *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0x7f;
          uVar7 = rand();
          uVar14 = uVar7 & 1;
          if (((int)uVar7 < 0) && (uVar14 != 0)) {
            uVar14 = uVar14 - 2;
          }
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (chr(iVar13,iVar15)->nCharId == 2)) {
            if (uVar14 == 0) {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1d);
            }
            else {
              SetNextBtlMotion__8BtlModelFif
                        (0x3f800000,chr(iVar13,iVar15)->pModel,0x1e);
            }
          }
          else if (uVar14 == 0) {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x20);
          }
          else {
            SetNextBtlMotion__8BtlModelFif
                      (0x3f800000,chr(iVar13,iVar15)->pModel,0x21);
          }
        }
      }
      if (chr(iVar13,iVar15)->f4c0 != -1) {
        auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
        auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
        auVar19 = _vadd(auVar19,auVar20);
        auStack_350 = _sqc2(auVar19);
        __ct__7FVectorFPC7FVector(&uStack_190,auStack_350);
        auStack_10._8_4_ = uStack_188;
        auStack_10._0_8_ = uStack_190;
        auStack_10._12_4_ = uStack_184;
        sVar2 = *(short *)(chr(iVar13,iVar15)->pModel + 0x510);
        if (sVar2 == 5) {
          uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001000,1,auStack_10);
          chr(iVar13,iVar15)->f4cc = uVar6;
        }
        else if (sVar2 == 0x21) {
          uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x6000100a,1,auStack_10);
          chr(iVar13,iVar15)->f4cc = uVar6;
        }
        else if (sVar2 == 0x20) {
          uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001009,1,auStack_10);
          chr(iVar13,iVar15)->f4cc = uVar6;
        }
        else if (sVar2 == 0x1f) {
          uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001008,1,auStack_10);
          chr(iVar13,iVar15)->f4cc = uVar6;
        }
        else if (sVar2 == 0x1b) {
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (((ulong)*(byte *)(iVar13 + 0x45d6) & 7) >> 1 == 3)) {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60003007,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
          else {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001007,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
        }
        else if (sVar2 == 0x1a) {
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (((ulong)*(byte *)(iVar13 + 0x45d6) & 7) >> 1 == 3)) {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60003006,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
          else {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001006,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
        }
        else if (sVar2 == 0x19) {
          if (((chr(iVar13,iVar15)->bFlagsB & 1) == 0) &&
             (((ulong)*(byte *)(iVar13 + 0x45d6) & 7) >> 1 == 3)) {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60003005,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
          else {
            uVar6 = PlaySE__6HNMSndFUibP7FVector(uGpffff8374,0x60001005,1,auStack_10);
            chr(iVar13,iVar15)->f4cc = uVar6;
          }
        }
      }
      chr(iVar13,iVar15)->f316 = 0;
      chr(iVar13,iVar15)->f318 = 0;
      chr(iVar13,iVar15)->f31a = 0;
      chr(iVar13,iVar15)->f43e = 0xffff;
      chr(iVar13,iVar15)->f43c = 0xffff;
      chr(iVar13,iVar15)->f43a = 0xffff;
      chr(iVar13,iVar15)->f438 = 0xffff;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0xf7;
      iVar11 = iVar13 + iVar15 * 0x510;
      *(byte *)(iVar11 + 0x3c0) = *(byte *)(iVar11 + 0x3c0) & 0xef;
      for (iVar11 = 0; iVar11 < 0xc; iVar11 = iVar11 + 1) {
        *(undefined1 *)(iVar13 + iVar15 * 0x510 + iVar11 + 0x4f4) = 0xff;
      }
      chr(iVar13,iVar15)->f450 = 0;
      chr(iVar13,iVar15)->f4b0 = 0;
      cVar3 = -1;
      if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 10) ||
         (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x13)) {
        cVar3 = *(char *)(iVar5 + (uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) * 0x48
                         + 2);
      }
      if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xb) ||
         (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x14)) {
        cVar3 = *(char *)(iVar5 + ((uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 1) *
                                  0x48 + 2);
      }
      if ((*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0xc) ||
         (*(short *)(chr(iVar13,iVar15)->pModel + 0x510) == 0x15)) {
        cVar3 = *(char *)(iVar5 + ((uint)*(byte *)(iVar4 + 1) * (int)*(short *)(iVar4 + 0x16) + 2) *
                                  0x48 + 2);
      }
      if ((cVar3 == -1) || (cVar3 == '\0')) {
        switch(*(undefined1 *)(iVar4 + 3)) {
        case 1:
          iVar4 = 0;
          while ((iVar4 < 0x20 && (*(char *)(iVar13 + iVar15 * 0x510 + iVar4 * 0xc + 0x1d0) != '#'))
                ) {
            iVar4 = iVar4 + 1;
          }
          if (iVar4 < 0x20) {
            lVar10 = __nw__FUi(0x9a0);
            uVar6 = 0;
            if (lVar10 != 0) {
              uVar6 = __ct__15FanLocusEffect1Fiiii
                                (lVar10,0,param_3,0,
                                 *(int *)(iVar13 + iVar15 * 0x510 + iVar4 * 0xc + 0x1d4) + 1);
            }
            chr(iVar13,iVar15)->f4b0 = uVar6;
          }
          else {
            lVar10 = __nw__FUi(0x9a0);
            uVar6 = 0;
            if (lVar10 != 0) {
              uVar6 = __ct__15FanLocusEffect1Fiiii(lVar10,0,param_3,0,0);
            }
            chr(iVar13,iVar15)->f4b0 = uVar6;
          }
          break;
        case 3:
          iVar4 = 0;
          while ((iVar4 < 0x20 && (*(char *)(iVar13 + iVar15 * 0x510 + iVar4 * 0xc + 0x1d0) != '#'))
                ) {
            iVar4 = iVar4 + 1;
          }
          if (iVar4 < 0x20) {
            lVar10 = __nw__FUi(0x9a0);
            uVar6 = 0;
            if (lVar10 != 0) {
              uVar6 = __ct__17SwordLocusEffect1Fiiib
                                (lVar10,0,param_3,
                                 *(int *)(iVar13 + iVar15 * 0x510 + iVar4 * 0xc + 0x1d4) + 1,0);
            }
            chr(iVar13,iVar15)->f4b0 = uVar6;
          }
          else {
            lVar10 = __nw__FUi(0x9a0);
            uVar6 = 0;
            if (lVar10 != 0) {
              uVar6 = __ct__17SwordLocusEffect1Fiiib(lVar10,0,param_3,0,0);
            }
            chr(iVar13,iVar15)->f4b0 = uVar6;
          }
          break;
        case 4:
          uVar8 = searchRWBBoxIndex__8BtlModelFPci
                            (chr(iVar13,iVar15)->pModel,0x6e7258,0);
          lVar10 = __nw__FUi(0x9a0);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__17SwordLocusEffect3Fiiiiii(lVar10,0,param_3,uVar8,0,1,1);
          }
          chr(iVar13,iVar15)->f4b0 = uVar6;
          break;
        case 5:
          lVar10 = __nw__FUi(14000);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__15WhipLocusEffectFiii(lVar10,0,param_3,0);
          }
          chr(iVar13,iVar15)->f4b0 = uVar6;
          break;
        case 6:
          uVar8 = searchRWBBoxIndex__8BtlModelFPci
                            (chr(iVar13,iVar15)->pModel,0x6e7260,0);
          lVar10 = __nw__FUi(0x9a0);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__17SwordLocusEffect3Fiiiiii(lVar10,0,param_3,uVar8,0,1,1);
          }
          chr(iVar13,iVar15)->f4b0 = uVar6;
          break;
        case 7:
          uVar8 = searchBBoxIndex__8BtlModelFPci
                            (chr(iVar13,iVar15)->pModel,0x6e7270,0);
          lVar10 = __nw__FUi(0x9a0);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__17SwordLocusEffect3Fiiiiii(lVar10,0,param_3,uVar8,2,2,1);
          }
          chr(iVar13,iVar15)->f4b0 = uVar6;
          break;
        case 8:
          lVar10 = __nw__FUi(14000);
          uVar6 = 0;
          if (lVar10 != 0) {
            uVar6 = __ct__15WhipLocusEffectFiii(lVar10,0,param_3,1);
          }
          chr(iVar13,iVar15)->f4b0 = uVar6;
        }
      }
    }
    else if ((((chr(iVar13,iVar15)->f4c0 != -1) &&
              (chr(iVar13,iVar15)->f4cc != -1)) &&
             (chr(iVar13,iVar15)->nMonId != 499)) &&
            ((chr(iVar13,iVar15)->f1c & 1) != 0)) {
      auVar19 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x160));
      auVar20 = _lqc2(*(undefined1 (*) [16])(iVar13 + iVar15 * 0x510 + 0x3a0));
      auVar19 = _vadd(auVar19,auVar20);
      auStack_360 = _sqc2(auVar19);
      __ct__7FVectorFPC7FVector(auStack_1a0,auStack_360);
      uVar8 = __ct__7FVectorFPC7FVector(auStack_1b0,auStack_10);
      SetSEParam__6HNMSndFUi7FVectori(uGpffff8374,0x60002000,uVar8,chr(iVar13,iVar15)->f4cc)
      ;
    }
  }
  return;
}

/* ---- 0x006ce010  Retail_BtlChrSequence_State31  (size 0x2f0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void Retail_BtlChrSequence_State31(int this,int param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFRC7FVector(auStack_10,chr(this,param_2)->pModel + 0x4e0);
  iVar2 = this + param_2 * 0x510;
  *(int *)(iVar2 + 0x160) = auStack_10._0_4_;
  *(int *)(iVar2 + 0x164) = auStack_10._4_4_;
  *(undefined4 *)(iVar2 + 0x168) = uStack_8;
  *(undefined4 *)(iVar2 + 0x16c) = uStack_4;
  cVar1 = chr(this,param_2)->bState2;
  if (cVar1 != '\x01') {
    if (cVar1 != '\0') {
      return;
    }
    if ((((long)((ulong)chr(this,param_2)->bFlagsA1 << 0x3e) < 0) ||
        (chr(this,param_2)->nCharId != 0)) ||
       ((*(byte *)(iGpffff83b4 + 0xec0) & 1) == 0)) {
      if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x34) {
        SetNextBtlMotion__8BtlModelFif
                  (0x3f800000,chr(this,param_2)->pModel,0x34);
      }
      if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x34) {
        return;
      }
    }
    else {
      if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x36) {
        SetNextBtlMotion__8BtlModelFif
                  (0x3f800000,chr(this,param_2)->pModel,0x36);
      }
      if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x36) {
        return;
      }
    }
    chr(this,param_2)->bState2 = 1;
  }
  if ((long)((ulong)*(byte *)(chr(this,param_2)->pModel + 0x4d0) << 0x3c) < 0) {
    chr(this,param_2)->bState2 = 2;
  }
  return;
}

/* ---- 0x006ce300  Retail_BtlChrSequence_State32  (size 0x470) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: ['0x7'] */
void Retail_BtlChrSequence_State32(int this,int param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  __ct__7FVectorFRC7FVector(auStack_10,chr(this,param_2)->pModel + 0x4e0);
  iVar2 = this + param_2 * 0x510;
  *(int *)(iVar2 + 0x160) = auStack_10._0_4_;
  *(int *)(iVar2 + 0x164) = auStack_10._4_4_;
  *(undefined4 *)(iVar2 + 0x168) = uStack_8;
  *(undefined4 *)(iVar2 + 0x16c) = uStack_4;
  cVar1 = chr(this,param_2)->bState2;
  if (cVar1 == '\x01') {
    if ((((long)((ulong)chr(this,param_2)->bFlagsA1 << 0x3e) < 0) ||
        (chr(this,param_2)->nCharId != 0)) ||
       ((*(byte *)(iGpffff83b4 + 0xec0) & 1) == 0)) {
      if (*(short *)(chr(this,param_2)->pModel + 0x510) == 0x35) {
        return;
      }
    }
    else if (*(short *)(chr(this,param_2)->pModel + 0x510) == 0x37) {
      return;
    }
    chr(this,param_2)->bState = 7;
    chr(this,param_2)->bState2 = 0;
    auVar3 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x160));
    auVar4 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x3a0));
    auVar3 = _vadd(auVar3,auVar4);
    auStack_30 = _sqc2(auVar3);
    __ct__7FVectorFPC7FVector(auStack_20,auStack_30);
    iVar2 = this + param_2 * 0x510;
    *(int *)(iVar2 + 0x170) = auStack_20._0_4_;
    *(int *)(iVar2 + 0x174) = auStack_20._4_4_;
    *(undefined4 *)(iVar2 + 0x178) = uStack_18;
    *(undefined4 *)(iVar2 + 0x17c) = uStack_14;
    chr(this,param_2)->fc4 = 0;
  }
  else if (cVar1 == '\0') {
    if ((((long)((ulong)chr(this,param_2)->bFlagsA1 << 0x3e) < 0) ||
        (chr(this,param_2)->nCharId != 0)) ||
       ((*(byte *)(iGpffff83b4 + 0xec0) & 1) == 0)) {
      if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x35) {
        SetBtlMotion__8BtlModelFif
                  (0x3f800000,chr(this,param_2)->pModel,0x35);
      }
    }
    else if (*(short *)(chr(this,param_2)->pModel + 0x510) != 0x37) {
      SetBtlMotion__8BtlModelFif(0x3f800000,chr(this,param_2)->pModel,0x37)
      ;
    }
    OTEntry__8BtlModelFii(chr(this,param_2)->pModel,4,8);
    ShadowOn__8BtlModelFv(chr(this,param_2)->pModel);
    chr(this,param_2)->bState2 = 1;
    chr(this,param_2)->f2c = 0;
  }
  return;
}

/* ---- 0x006ce770  Retail_BtlChrSequence_State33  (size 0x3a0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: ['0x7'] */
void Retail_BtlChrSequence_State33(int this,int param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  cVar1 = chr(this,param_2)->bState2;
  if (cVar1 == '\x01') {
    iVar2 = this + param_2 * 0x510;
    *(float *)(iVar2 + 0xdc) = *(float *)(iVar2 + 0xdc) + this->flDeltaT;
    if (1.0 <= chr(this,param_2)->f2c) {
      chr(this,param_2)->f2c = 0x3f800000;
      *(undefined4 *)(chr(this,param_2)->pModel + 0x504) =
           chr(this,param_2)->f2c;
      chr(this,param_2)->bState = 7;
      chr(this,param_2)->bState2 = 2;
      __ct__7FVectorFRC7FVector(auStack_10,chr(this,param_2)->pModel + 0x4e0);
      iVar2 = this + param_2 * 0x510;
      *(int *)(iVar2 + 0x160) = auStack_10._0_4_;
      *(int *)(iVar2 + 0x164) = auStack_10._4_4_;
      *(undefined4 *)(iVar2 + 0x168) = uStack_8;
      *(undefined4 *)(iVar2 + 0x16c) = uStack_4;
      auVar3 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x160));
      auVar4 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x3a0));
      auVar3 = _vadd(auVar3,auVar4);
      auStack_30 = _sqc2(auVar3);
      __ct__7FVectorFPC7FVector(auStack_20,auStack_30);
      iVar2 = this + param_2 * 0x510;
      *(int *)(iVar2 + 0x170) = auStack_20._0_4_;
      *(int *)(iVar2 + 0x174) = auStack_20._4_4_;
      *(undefined4 *)(iVar2 + 0x178) = uStack_18;
      *(undefined4 *)(iVar2 + 0x17c) = uStack_14;
      chr(this,param_2)->fc4 = 0;
      iVar2 = rand();
      chr(this,param_2)->f2c = ((float)iVar2 / 2.1474836e+09) * 0.5;
    }
    else {
      *(undefined4 *)(chr(this,param_2)->pModel + 0x504) =
           chr(this,param_2)->f2c;
    }
  }
  else if (cVar1 == '\0') {
    OTEntry__8BtlModelFii(chr(this,param_2)->pModel,4,8);
    ShadowOn__8BtlModelFv(chr(this,param_2)->pModel);
    chr(this,param_2)->bState2 = 1;
    chr(this,param_2)->f2c = 0;
  }
  return;
}

/* ---- 0x006ceb10  Retail_BtlChrSequence_State34  (size 0x3a0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: ['0x2a'] */
void Retail_BtlChrSequence_State34(int this,int param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar2 = this + param_2 * 0x510;
  *(byte *)(iVar2 + 0xb4) = *(byte *)(iVar2 + 0xb4) & 0xf9 | 6;
  cVar1 = chr(this,param_2)->bState2;
  if (cVar1 == '\x01') {
    iVar2 = this + param_2 * 0x510;
    *(float *)(iVar2 + 0xdc) = *(float *)(iVar2 + 0xdc) + this->flDeltaT;
    if (1.0 <= chr(this,param_2)->f2c) {
      chr(this,param_2)->f2c = 0x3f800000;
      *(undefined4 *)(chr(this,param_2)->pModel + 0x504) =
           chr(this,param_2)->f2c;
      chr(this,param_2)->bState = 0x2a;
      chr(this,param_2)->bState2 = 1;
      __ct__7FVectorFRC7FVector(auStack_10,chr(this,param_2)->pModel + 0x4e0);
      iVar2 = this + param_2 * 0x510;
      *(int *)(iVar2 + 0x160) = auStack_10._0_4_;
      *(int *)(iVar2 + 0x164) = auStack_10._4_4_;
      *(undefined4 *)(iVar2 + 0x168) = uStack_8;
      *(undefined4 *)(iVar2 + 0x16c) = uStack_4;
      auVar3 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x160));
      auVar4 = _lqc2(*(undefined1 (*) [16])(this + param_2 * 0x510 + 0x3a0));
      auVar3 = _vadd(auVar3,auVar4);
      auStack_30 = _sqc2(auVar3);
      __ct__7FVectorFPC7FVector(auStack_20,auStack_30);
      iVar2 = this + param_2 * 0x510;
      *(int *)(iVar2 + 0x170) = auStack_20._0_4_;
      *(int *)(iVar2 + 0x174) = auStack_20._4_4_;
      *(undefined4 *)(iVar2 + 0x178) = uStack_18;
      *(undefined4 *)(iVar2 + 0x17c) = uStack_14;
      chr(this,param_2)->fc4 = 0;
      chr(this,param_2)->f2c = 0;
    }
    else {
      *(undefined4 *)(chr(this,param_2)->pModel + 0x504) =
           chr(this,param_2)->f2c;
    }
  }
  else if (cVar1 == '\0') {
    OTEntry__8BtlModelFii(chr(this,param_2)->pModel,4,8);
    ShadowOn__8BtlModelFv(chr(this,param_2)->pModel);
    chr(this,param_2)->bState2 = 1;
    chr(this,param_2)->f2c = 0;
  }
  return;
}

/* ---- 0x006ceeb0  AddFriendship__7CBattleFiis  (size 0x170) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void AddFriendship__7CBattleFiis(undefined8 this,int param_2,int param_3,short param_4)

{
  int iVar1;
  
  iVar1 = iGpffff83b4 + param_2 * 0xc0 + param_3 * 2;
  *(short *)(iVar1 + 0x7c) = *(short *)(iVar1 + 0x7c) + param_4;
  if (10000 < *(short *)(iGpffff83b4 + param_2 * 0xc0 + param_3 * 2 + 0x7c)) {
    *(undefined2 *)(iGpffff83b4 + param_2 * 0xc0 + param_3 * 2 + 0x7c) = 10000;
  }
  iVar1 = iGpffff83b4 + param_3 * 0xc0 + param_2 * 2;
  *(short *)(iVar1 + 0x7c) = *(short *)(iVar1 + 0x7c) + param_4;
  if (10000 < *(short *)(iGpffff83b4 + param_3 * 0xc0 + param_2 * 2 + 0x7c)) {
    *(undefined2 *)(iGpffff83b4 + param_3 * 0xc0 + param_2 * 2 + 0x7c) = 10000;
  }
  return;
}

/* ---- 0x006cf020  AIInit__7CBattleFi  (size 0x1e0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void AIInit__7CBattleFi(int this,int param_2)

{
  chr(this,param_2)->pAiCursor = chr(this,param_2)->pAiScript + 4;
  chr(this,param_2)->f102 = 0;
  chr(this,param_2)->f100 = 0;
  chr(this,param_2)->ffe = 0;
  chr(this,param_2)->aAiReg = 0;
  chr(this,param_2)->f10a = 0;
  chr(this,param_2)->f108 = 0;
  chr(this,param_2)->f106 = 0;
  chr(this,param_2)->f104 = 0;
  chr(this,param_2)->wTurnCount = 0;
  return;
}

/* ---- 0x006d9450  GetTarget__7CBattleFiiiiii  (size 0x5b60) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
uint GetTarget__7CBattleFiiiiii
               (undefined8 this,uint param_2,int param_3,uint param_4,undefined8 param_5,
               int param_6,int param_7)

{
  undefined8 uVar1;
  bool bVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 *puVar9;
  int unaff_s0_lo;
  int iVar10;
  int this;
  uint uVar12;
  int iVar13;
  int iVar14;
  int unaff_s7_lo;
  float fVar15;
  float fVar16;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  int iStack_3d0;
  int iStack_3c0;
  int iStack_3a0;
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [8];
  undefined4 uStack_358;
  undefined4 uStack_354;
  uint auStack_350 [12];
  uint auStack_320 [12];
  undefined8 uStack_2f0;
  undefined4 auStack_2e8 [46];
  undefined1 auStack_230 [16];
  uint auStack_220 [12];
  uint auStack_1f0 [12];
  undefined4 uStack_1c0;
  char acStack_1bc [4];
  uint auStack_1b8 [70];
  uint uStack_a0;
  undefined1 uStack_9c;
  undefined1 uStack_9b;
  undefined2 uStack_9a;
  undefined4 uStack_98;
  uint auStack_40 [15];
  uint uStack_4;
  
  bVar2 = false;
  iVar14 = 0;
  iVar3 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
  /* this = this */
  switch(param_6) {
  case 0:
    for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
      if ((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
          ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
         ((-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c) &&
          (0 < chr(this,uVar12)->nHp)))) {
        auStack_40[iVar14] = uVar12;
        iVar14 = iVar14 + 1;
      }
    }
    break;
  case 1:
    for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
      if ((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
          ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
         ((-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c) &&
          (((chr(this,param_2)->bFlagsB & 1) !=
            (chr(this,uVar12)->bFlagsB & 1) &&
           (0 < chr(this,uVar12)->nHp)))))) {
        if (this->wChrMask == 0) {
          auStack_40[iVar14] = uVar12;
          iVar14 = iVar14 + 1;
        }
        else if (((uint)this->wChrMask & 1 << (uVar12 & 0x1f)) != 0) {
          auStack_40[iVar14] = uVar12;
          iVar14 = iVar14 + 1;
        }
      }
    }
    if ((this->nComboCnt != 0) && (iVar14 == 0)) {
      for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
        if (((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
             ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
            (-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c))) &&
           (((chr(this,param_2)->bFlagsB & 1) !=
             (chr(this,uVar12)->bFlagsB & 1) &&
            (0 < chr(this,uVar12)->nHp)))) {
          auStack_40[iVar14] = uVar12;
          iVar14 = iVar14 + 1;
        }
      }
    }
    bVar2 = true;
    break;
  case 2:
  case 3:
  case 4:
  case 5:
    if (param_6 == 5) {
      iVar4 = GetRegDat__9RegDatApiFiii(0x3f,0,0xffffffffffffffff);
      unaff_s0_lo = iVar4 + param_7 * 0x40;
    }
    else if (param_6 == 4) {
      iVar4 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
      unaff_s0_lo = iVar4 + param_7 * 0x30;
    }
    else if (param_6 == 3) {
      iVar4 = GetRegDat__9RegDatApiFiii(0x3e,0,0xffffffffffffffff);
      unaff_s0_lo = iVar4 + param_7 * 0x44;
    }
    else if (param_6 == 2) {
      if ((chr(this,param_2)->bFlagsB & 1) == 0) {
        iVar4 = Retail_CBattle_GetPAtkTable(this,param_2);
        unaff_s0_lo = iVar4 + param_7 * 0x40;
      }
      else {
        iVar4 = GetRegDat__9RegDatApiFiii(0x3c,0x19,0xffffffffffffffff);
        unaff_s0_lo = iVar4 + param_7 * 0x20;
      }
    }
    if (((ulong)*(byte *)(unaff_s0_lo + 4) & 0x7f) >> 5 == 0) {
      for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
        if (((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
             ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
            (-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c))) &&
           (((chr(this,param_2)->bFlagsB & 1) !=
             (chr(this,uVar12)->bFlagsB & 1) &&
            (0 < chr(this,uVar12)->nHp)))) {
          if (this->wChrMask == 0) {
            auStack_40[iVar14] = uVar12;
            iVar14 = iVar14 + 1;
          }
          else if (((uint)this->wChrMask & 1 << (uVar12 & 0x1f)) != 0) {
            auStack_40[iVar14] = uVar12;
            iVar14 = iVar14 + 1;
          }
        }
      }
      if ((this->nComboCnt != 0) && (iVar14 == 0)) {
        for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
          if (((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
               ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
              (-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c))) &&
             (((chr(this,param_2)->bFlagsB & 1) !=
               (chr(this,uVar12)->bFlagsB & 1) &&
              (0 < chr(this,uVar12)->nHp)))) {
            auStack_40[iVar14] = uVar12;
            iVar14 = iVar14 + 1;
          }
        }
      }
      bVar2 = true;
    }
    else {
      uStack_4 = 0;
      if (((*(byte *)(unaff_s0_lo + 0xb) >> 4 == 1) &&
          ((long)((ulong)*(byte *)(unaff_s0_lo + 0xb) << 0x3c) < 0)) &&
         (*(char *)(unaff_s0_lo + 10) == '(')) {
        uStack_4 = 1;
      }
      if (((ulong)*(ushort *)(unaff_s0_lo + 4) & 0x1ff) >> 7 == 0) {
        auStack_40[0] = param_2;
        iVar14 = 1;
      }
      else if (((ulong)*(ushort *)(unaff_s0_lo + 4) & 0x1ff) >> 7 == 1) {
        for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
          if ((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
              ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
             (((-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c) &&
               ((chr(this,param_2)->bFlagsB & 1) ==
                (chr(this,uVar12)->bFlagsB & 1))) &&
              ((*(short *)(unaff_s0_lo + 0x18) != 0x4a || (uVar12 != param_2)))))) {
            if (uStack_4 == 0) {
              if (0 < chr(this,uVar12)->nHp) {
                auStack_40[iVar14] = uVar12;
                iVar14 = iVar14 + 1;
              }
            }
            else if (chr(this,uVar12)->nHp < 1) {
              auStack_40[iVar14] = uVar12;
              iVar14 = iVar14 + 1;
            }
          }
        }
      }
      else if (((ulong)*(ushort *)(unaff_s0_lo + 4) & 0x1ff) >> 7 == 2) {
        for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
          if ((((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
                ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
               (-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c))) &&
              ((chr(this,param_2)->bFlagsB & 1) !=
               (chr(this,uVar12)->bFlagsB & 1))) &&
             ((*(short *)(unaff_s0_lo + 0x18) != 0x4a || (uVar12 != param_2)))) {
            if (uStack_4 == 0) {
              if (0 < chr(this,uVar12)->nHp) {
                auStack_40[iVar14] = uVar12;
                iVar14 = iVar14 + 1;
              }
            }
            else if (chr(this,uVar12)->nHp < 1) {
              auStack_40[iVar14] = uVar12;
              iVar14 = iVar14 + 1;
            }
          }
        }
        bVar2 = true;
      }
      else {
        for (uVar12 = 0; (int)uVar12 < 0xc; uVar12 = uVar12 + 1) {
          if ((((chr(this,uVar12)->bFlagsA & 1) != 0) &&
              ((long)((ulong)chr(this,uVar12)->bFlagsA << 0x3e) < 0)) &&
             ((-1 < (long)((ulong)chr(this,uVar12)->bFlagsA2 << 0x3c) &&
              ((*(short *)(unaff_s0_lo + 0x18) != 0x4a || (uVar12 != param_2)))))) {
            if (uStack_4 == 0) {
              if (0 < chr(this,uVar12)->nHp) {
                auStack_40[iVar14] = uVar12;
                iVar14 = iVar14 + 1;
              }
            }
            else if (chr(this,uVar12)->nHp < 1) {
              auStack_40[iVar14] = uVar12;
              iVar14 = iVar14 + 1;
            }
          }
        }
      }
    }
  }
  if (iVar14 == 0) {
    return 0xffffffff;
  }
  iVar4 = 0;
  while ((iVar13 = -1, iVar4 < iVar14 &&
         (((*(byte *)(this + auStack_40[iVar4] * 0x510 + 0xb4) & 1) != 0 ||
          (iVar13 = iVar4, *(short *)(this + auStack_40[iVar4] * 0x510 + 0x120) != 6))))) {
    iVar4 = iVar4 + 1;
  }
  if ((((1 < iVar14) && (-1 < iVar13)) &&
      ((*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb4) & 1) !=
       (chr(this,param_2)->bFlagsB & 1))) &&
     (iVar4 = GetRegDat__9RegDatApiFiii(0x48,0,0xffffffffffffffff),
     (*(byte *)(iVar4 + *(short *)(iGpffff836c + 0x750) * 0x10 + 4) & 1) != 0)) {
    for (; iVar13 < iVar14 + -1; iVar13 = iVar13 + 1) {
      auStack_40[iVar13] = auStack_40[iVar13 + 1];
    }
    iVar14 = iVar14 + -1;
  }
  iVar4 = 0;
  iStack_3c0 = 0;
  auStack_230._4_4_ = in_zero_hi;
  auStack_230._0_4_ = in_zero_lo;
  auStack_230._8_4_ = in_zero_udw;
  auStack_230._12_4_ = in_register_0000000c;
  puVar9 = &uStack_2f0;
  do {
    *(undefined4 *)puVar9 = in_zero_lo;
    *(undefined4 *)((int)puVar9 + 4) = in_zero_hi;
    *(undefined4 *)(puVar9 + 1) = in_zero_udw;
    *(undefined4 *)((int)puVar9 + 0xc) = in_register_0000000c;
    puVar9 = puVar9 + 2;
  } while (puVar9 != (undefined8 *)auStack_230);
  for (iVar13 = 0; iVar13 < iVar14; iVar13 = iVar13 + 1) {
    if (((((*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb0) << 0x3e) < 0)) &&
        ((-1 < (long)((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb2) << 0x3c) &&
         ((0 < *(int *)(this + auStack_40[iVar13] * 0x510 + 0x130) &&
          ((chr(this,param_2)->bFlagsB & 1) !=
           (*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb4) & 1))))))) &&
       ((*(char *)(this + auStack_40[iVar13] * 0x510 + 0xb8) != '\x12' &&
        ((*(char *)(this + auStack_40[iVar13] * 0x510 + 0xb8) < '\x19' ||
         ('*' < *(char *)(this + auStack_40[iVar13] * 0x510 + 0xb8))))))) {
      if (((long)((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb4) << 0x39) < 0) ||
         (((long)((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb5) << 0x3c) < 0 ||
          ((long)((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb1) << 0x3a) < 0)))) {
        iVar10 = this + auStack_40[iVar13] * 0x510;
        uVar1 = *(undefined8 *)(iVar10 + 0x170);
        uVar7 = *(undefined4 *)(iVar10 + 0x178);
        uVar8 = *(undefined4 *)(iVar10 + 0x17c);
        *(int *)(&uStack_2f0 + iVar4 * 2) = (int)uVar1;
        *(int *)((int)&uStack_2f0 + iVar4 * 0x10 + 4) = (int)((ulong)uVar1 >> 0x20);
        auStack_2e8[iVar4 * 4] = uVar7;
        auStack_2e8[iVar4 * 4 + 1] = uVar8;
      }
      else {
        auVar17 = _lqc2(*(undefined1 (*) [16])(this + auStack_40[iVar13] * 0x510 + 0x160));
        auVar18 = _lqc2(*(undefined1 (*) [16])(this + auStack_40[iVar13] * 0x510 + 0x3a0));
        auVar17 = _vadd(auVar17,auVar18);
        auStack_370 = _sqc2(auVar17);
        __ct__7FVectorFPC7FVector(auStack_360,auStack_370);
        *(int *)(&uStack_2f0 + iVar4 * 2) = auStack_360._0_4_;
        *(int *)((int)&uStack_2f0 + iVar4 * 0x10 + 4) = auStack_360._4_4_;
        auStack_2e8[iVar4 * 4] = uStack_358;
        auStack_2e8[iVar4 * 4 + 1] = uStack_354;
      }
      auStack_1f0[iVar4] = auStack_40[iVar13];
      iVar4 = iVar4 + 1;
    }
  }
  if (iVar4 != 0) {
    for (iVar13 = 0; iVar13 < iVar4; iVar13 = iVar13 + 1) {
      for (iVar10 = 0; iVar10 < iVar4; iVar10 = iVar10 + 1) {
        if (iVar10 != iVar13) {
          auStack_230._8_4_ = auStack_2e8[iVar13 * 4];
          auStack_230._0_8_ = (&uStack_2f0)[iVar13 * 2];
          auStack_230._12_4_ = auStack_2e8[iVar13 * 4 + 1];
          auVar18 = _lqc2(*(undefined1 (*) [16])(&uStack_2f0 + iVar10 * 2));
          auVar17 = _lqc2(auStack_230);
          auVar17 = _vsub(auVar17,auVar18);
          auVar17 = _sqc2(auVar17);
          auStack_230._8_8_ = auVar17._8_8_;
          auStack_230._0_4_ = auVar17._0_4_;
          auStack_230._4_4_ = 0;
          fVar16 = (float)Length__7FVectorCFv(auStack_230);
          if (fVar16 <= *(float *)(this + auStack_1f0[iVar13] * 0x510 + 0x354) +
                        *(float *)(this + auStack_1f0[iVar10] * 0x510 + 0x354) + 10.0) {
            auStack_220[iStack_3c0] = auStack_1f0[iVar13];
            iStack_3c0 = iStack_3c0 + 1;
            break;
          }
        }
      }
    }
  }
  if (iStack_3c0 != 0) {
    switch(param_3) {
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x3f:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
      for (iVar4 = 0; iVar14 = iStack_3c0, iVar4 < iStack_3c0; iVar4 = iVar4 + 1) {
        auStack_40[iVar4] = auStack_1f0[iVar4];
      }
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
      iVar4 = rand();
      if (iVar4 % 100 < 0x33) {
        for (iVar4 = 0; iVar14 = iStack_3c0, iVar4 < iStack_3c0; iVar4 = iVar4 + 1) {
          auStack_40[iVar4] = auStack_1f0[iVar4];
        }
      }
    }
  }
  iVar4 = 0;
  switch(param_3) {
  case 0:
  case 0x28:
  case 0x50:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      auStack_320[iVar3] = auStack_40[iVar3];
    }
    unaff_s7_lo = 100;
    iVar4 = iVar14;
    break;
  case 1:
  case 0xe:
  case 0x1b:
  case 0x29:
  case 0x36:
  case 0x43:
  case 0x51:
  case 0x5e:
  case 0x6b:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_320[0] * 0x510 + 0x130) <
            *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(int *)(this + auStack_320[0] * 0x510 + 0x130) ==
                 *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_40[iVar3] * 0x510 + 300) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
          }
          else {
            fVar15 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
            if (fVar16 < fVar15) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x51) && (param_3 != 0x29)) && (param_3 != 1)) {
      if (((param_3 == 0x6b) || (param_3 == 0x43)) || (param_3 == 0x1b)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x5e) || (param_3 == 0x36)) || (param_3 == 0xe)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 2:
  case 0xf:
  case 0x1c:
  case 0x2a:
  case 0x37:
  case 0x44:
  case 0x52:
  case 0x5f:
  case 0x6c:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) <
            *(int *)(this + auStack_320[0] * 0x510 + 0x130)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(int *)(this + auStack_320[0] * 0x510 + 0x130) ==
                 *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_40[iVar3] * 0x510 + 300) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
          }
          else {
            fVar15 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
            if (fVar15 < fVar16) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x52) && (param_3 != 0x2a)) && (param_3 != 2)) {
      if (((param_3 == 0x6c) || (param_3 == 0x44)) || (param_3 == 0x1c)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x5f) || (param_3 == 0x37)) || (param_3 == 0xf)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 3:
  case 0x10:
  case 0x1d:
  case 0x2b:
  case 0x38:
  case 0x45:
  case 0x53:
  case 0x60:
  case 0x6d:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_320[0] * 0x510 + 0x136) <
            *(short *)(this + auStack_40[iVar3] * 0x510 + 0x136)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(short *)(this + auStack_320[0] * 0x510 + 0x136) ==
                 *(short *)(this + auStack_40[iVar3] * 0x510 + 0x136)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x134) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x136) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x134);
          }
          else {
            fVar15 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x136) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x134);
            if (fVar16 < fVar15) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x53) && (param_3 != 0x2b)) && (param_3 != 3)) {
      if (((param_3 == 0x6d) || (param_3 == 0x45)) || (param_3 == 0x1d)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x60) || (param_3 == 0x38)) || (param_3 == 0x10)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 4:
  case 0x11:
  case 0x1e:
  case 0x2c:
  case 0x39:
  case 0x46:
  case 0x54:
  case 0x61:
  case 0x6e:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x136) <
            *(short *)(this + auStack_320[0] * 0x510 + 0x136)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(short *)(this + auStack_320[0] * 0x510 + 0x136) ==
                 *(short *)(this + auStack_40[iVar3] * 0x510 + 0x136)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x134) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x136) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x134);
          }
          else {
            fVar15 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x136) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x134);
            if (fVar15 < fVar16) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x54) && (param_3 != 0x2c)) && (param_3 != 4)) {
      if (((param_3 == 0x6e) || (param_3 == 0x46)) || (param_3 == 0x1e)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x61) || (param_3 == 0x39)) || (param_3 == 0x11)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 5:
  case 0x12:
  case 0x1f:
  case 0x2d:
  case 0x3a:
  case 0x47:
  case 0x55:
  case 0x62:
  case 0x6f:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_320[0] * 0x510 + 0x13a) <
            *(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(short *)(this + auStack_320[0] * 0x510 + 0x13a) ==
                 *(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x138) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x138);
          }
          else {
            fVar15 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x138);
            if (fVar16 < fVar15) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x55) && (param_3 != 0x2d)) && (param_3 != 5)) {
      if (((param_3 == 0x6f) || (param_3 == 0x47)) || (param_3 == 0x1f)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x62) || (param_3 == 0x3a)) || (param_3 == 0x12)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 6:
  case 0x13:
  case 0x20:
  case 0x2e:
  case 0x3b:
  case 0x48:
  case 0x56:
  case 99:
  case 0x70:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a) <
            *(short *)(this + auStack_320[0] * 0x510 + 0x13a)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(short *)(this + auStack_320[0] * 0x510 + 0x13a) ==
                 *(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x138) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x138);
          }
          else {
            fVar15 = (float)(int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x13a) /
                     (float)*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x138);
            if (fVar15 < fVar16) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
    }
    if (((param_3 != 0x56) && (param_3 != 0x2e)) && (param_3 != 6)) {
      if (((param_3 == 0x70) || (param_3 == 0x48)) || (param_3 == 0x20)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 99) || (param_3 == 0x3b)) || (param_3 == 0x13)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 7:
  case 0x14:
  case 0x21:
  case 0x2f:
  case 0x3c:
  case 0x49:
  case 0x57:
  case 100:
  case 0x71:
    auStack_320[0] = auStack_40[0];
    iVar4 = 1;
    for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x146) <
          *(ushort *)(this + auStack_320[0] * 0x510 + 0x146)) {
        auStack_320[0] = auStack_40[iVar3];
        iVar4 = 1;
      }
      else if (*(short *)(this + auStack_320[0] * 0x510 + 0x146) ==
               *(short *)(this + auStack_40[iVar3] * 0x510 + 0x146)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    if (((param_3 != 0x57) && (param_3 != 0x2f)) && (param_3 != 7)) {
      if (((param_3 == 0x71) || (param_3 == 0x49)) || (param_3 == 0x21)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 100) || (param_3 == 0x3c)) || (param_3 == 0x14)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 8:
  case 0x15:
  case 0x22:
  case 0x30:
  case 0x3d:
  case 0x4a:
  case 0x58:
  case 0x65:
  case 0x72:
    auStack_320[0] = auStack_40[0];
    iVar4 = 1;
    for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (*(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x144) <
          *(ushort *)(this + auStack_320[0] * 0x510 + 0x144)) {
        auStack_320[0] = auStack_40[iVar3];
        iVar4 = 1;
      }
      else if (*(short *)(this + auStack_320[0] * 0x510 + 0x144) ==
               *(short *)(this + auStack_40[iVar3] * 0x510 + 0x144)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    if (((param_3 != 0x58) && (param_3 != 0x30)) && (param_3 != 8)) {
      if (((param_3 == 0x72) || (param_3 == 0x4a)) || (param_3 == 0x22)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x65) || (param_3 == 0x3d)) || (param_3 == 0x15)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 9:
  case 0x16:
  case 0x23:
  case 0x31:
  case 0x3e:
  case 0x4b:
  case 0x59:
  case 0x66:
  case 0x73:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      for (iVar13 = 0; iVar13 < 0x20; iVar13 = iVar13 + 1) {
        if ((*(char *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d0) == 'T') &&
           (((ulong)*(byte *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cd) & 0x3f) >>
            3 == 0)) {
          if ((int)param_4 < 1) {
            auStack_320[iVar4] = auStack_40[iVar3];
            iVar4 = iVar4 + 1;
          }
          else if ((*(uint *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d4) & param_4)
                   != 0) {
            auStack_320[iVar4] = auStack_40[iVar3];
            iVar4 = iVar4 + 1;
          }
        }
      }
    }
    if (((param_3 != 0x59) && (param_3 != 0x31)) && (param_3 != 9)) {
      if (((param_3 == 0x73) || (param_3 == 0x4b)) || (param_3 == 0x23)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x66) || (param_3 == 0x3e)) || (param_3 == 0x16)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 10:
  case 0x17:
  case 0x24:
  case 0x32:
  case 0x3f:
  case 0x4c:
  case 0x5a:
  case 0x67:
  case 0x74:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      for (iVar13 = 0; iVar13 < 0x20; iVar13 = iVar13 + 1) {
        if ((*(char *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d0) == 'U') &&
           (((ulong)*(byte *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cd) & 0x3f) >>
            3 == 0)) {
          if ((int)param_4 < 1) {
            auStack_320[iVar4] = auStack_40[iVar3];
            iVar4 = iVar4 + 1;
          }
          else if ((*(uint *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d4) & param_4)
                   != 0) {
            auStack_320[iVar4] = auStack_40[iVar3];
            iVar4 = iVar4 + 1;
          }
        }
      }
    }
    if (((param_3 != 0x5a) && (param_3 != 0x32)) && (param_3 != 10)) {
      if (((param_3 == 0x74) || (param_3 == 0x4c)) || (param_3 == 0x24)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x67) || (param_3 == 0x3f)) || (param_3 == 0x17)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0xb:
  case 0x18:
  case 0x25:
  case 0x33:
  case 0x40:
  case 0x4d:
  case 0x5b:
  case 0x68:
  case 0x75:
    if (-1 < (long)((ulong)chr(this,param_2)->f10c << 0x3c)) {
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (((long)chr(this,param_2)->f10c & 0x3ffffU) >> 0xe ==
            (long)(int)auStack_40[iVar3]) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    if (iVar4 == 0) {
      iVar3 = 0;
      for (iVar4 = 0; iVar4 < iVar14; iVar4 = iVar4 + 1) {
        auStack_320[iVar3] = auStack_40[iVar4];
        iVar3 = iVar3 + 1;
      }
    }
  case 0xc:
  case 0x19:
  case 0x26:
  case 0x34:
  case 0x41:
  case 0x4e:
  case 0x5c:
  case 0x69:
  case 0x76:
    auStack_320[0] = auStack_40[0];
    iVar4 = 1;
    for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (*(ushort *)(this + auStack_320[0] * 0x510 + 0x142) <
          *(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x142)) {
        auStack_320[0] = auStack_40[iVar3];
        iVar4 = 1;
      }
      else if (*(short *)(this + auStack_320[0] * 0x510 + 0x142) ==
               *(short *)(this + auStack_40[iVar3] * 0x510 + 0x142)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    if (((param_3 != 0x5c) && (param_3 != 0x34)) && (param_3 != 0xc)) {
      if (((param_3 == 0x76) || (param_3 == 0x4e)) || (param_3 == 0x26)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x69) || (param_3 == 0x41)) || (param_3 == 0x19)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0xd:
  case 0x1a:
  case 0x27:
  case 0x35:
  case 0x42:
  case 0x4f:
  case 0x5d:
  case 0x6a:
  case 0x77:
    auStack_320[0] = auStack_40[0];
    iVar4 = 1;
    for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (*(ushort *)(this + auStack_320[0] * 0x510 + 0x140) <
          *(ushort *)(this + auStack_40[iVar3] * 0x510 + 0x140)) {
        auStack_320[0] = auStack_40[iVar3];
        iVar4 = 1;
      }
      else if (*(short *)(this + auStack_320[0] * 0x510 + 0x140) ==
               *(short *)(this + auStack_40[iVar3] * 0x510 + 0x140)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    if (((param_3 != 0x5d) && (param_3 != 0x35)) && (param_3 != 0xd)) {
      if (((param_3 == 0x77) || (param_3 == 0x4f)) || (param_3 == 0x27)) {
        unaff_s7_lo = 0x46;
        break;
      }
      if (((param_3 == 0x6a) || (param_3 == 0x42)) || (param_3 == 0x1a)) {
        unaff_s7_lo = 0x32;
        break;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x78:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0) &&
         (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) == 0xb)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x46;
    break;
  case 0x79:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      uStack_4 = 0;
      for (iVar13 = 0; iVar13 < 0x20; iVar13 = iVar13 + 1) {
        if ((*(char *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d0) == 'T') &&
           (((ulong)*(byte *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cd) & 0x3f) >>
            3 == 0)) {
          if ((int)param_4 < 1) {
            uStack_4 = 1;
          }
          else if ((*(uint *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d4) & param_4)
                   != 0) {
            uStack_4 = 1;
          }
        }
      }
      if (uStack_4 == 0) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x7a:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      uStack_4 = 0;
      for (iVar13 = 0; iVar13 < 0x20; iVar13 = iVar13 + 1) {
        if ((*(char *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d0) == 'U') &&
           (((ulong)*(byte *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cd) & 0x3f) >>
            3 == 0)) {
          if ((int)param_4 < 1) {
            uStack_4 = 1;
          }
          else if ((*(uint *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d4) & param_4)
                   != 0) {
            uStack_4 = 1;
          }
        }
      }
      if (uStack_4 == 0) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x7b:
    if ((int)param_4 < 0) {
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (param_2 == auStack_40[iVar3]) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    else {
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (param_4 == auStack_40[iVar3]) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
    }
    if (iVar4 == 0) {
      unaff_s7_lo = 0;
    }
    else {
      unaff_s7_lo = 100;
    }
    break;
  case 0x7c:
    if ((chr(this,param_2)->bFlagsB & 1) == 0) {
      if ((long)((ulong)chr(this,param_2)->bFlagsA1 << 0x3e) < 0) {
        switch(chr(this,param_2)->fa) {
        case 0:
        case 1:
        case 2:
          uStack_4 = 0xe;
          break;
        case 3:
        case 4:
        case 5:
          uStack_4 = 0xf;
          break;
        case 6:
        case 7:
        case 8:
          uStack_4 = 0x10;
          break;
        case 9:
        case 10:
        case 0xb:
          uStack_4 = 0x11;
          break;
        case 0xc:
        case 0xd:
        case 0xe:
          uStack_4 = 0x12;
          break;
        case 0xf:
        case 0x10:
        case 0x11:
          uStack_4 = 0x13;
          break;
        case 0x12:
        case 0x13:
          uStack_4 = 0x14;
          break;
        case 0x14:
          uStack_4 = 0x15;
          break;
        case 0x15:
          uStack_4 = 0x16;
          break;
        case 0x16:
          uStack_4 = 0x17;
        }
      }
      else {
        uStack_4 = (int)chr(this,param_2)->nCharId;
      }
    }
    else {
      uStack_4 = 0x18;
    }
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      iVar13 = 0;
      while ((iVar13 < 0x20 &&
             ((((*(char *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d0) == '\0' ||
                ((*(byte *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cc) & 0x3f) !=
                 uStack_4)) ||
               (((ulong)*(ushort *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1cc) &
                0x3ff) >> 6 != 1)) ||
              (*(ushort *)(this + auStack_40[iVar3] * 0x510 + iVar13 * 0xc + 0x1d2) >> 6 !=
               param_4))))) {
        iVar13 = iVar13 + 1;
      }
      if (iVar13 < 0x20) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x7d:
    unaff_s7_lo = 0;
    break;
  case 0x7e:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) < 1) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    if (iVar4 == 0) {
      unaff_s7_lo = 0;
    }
    else {
      unaff_s7_lo = 100;
    }
    break;
  case 0x7f:
    if (bVar2) {
      auStack_320[0] = auStack_40[0];
      iVar4 = 1;
      for (iVar3 = 1; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_320[0] * 0x510 + 0x130) <
            *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
          auStack_320[0] = auStack_40[iVar3];
          iVar4 = 1;
        }
        else if (*(int *)(this + auStack_320[0] * 0x510 + 0x130) ==
                 *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
          auStack_320[iVar4] = auStack_40[iVar3];
          iVar4 = iVar4 + 1;
        }
      }
      iVar3 = 1;
      for (iVar13 = 1; iVar13 < iVar14; iVar13 = iVar13 + 1) {
        if (*(int *)(this + auStack_40[iVar13] * 0x510 + 0x130) <
            *(int *)(this + auStack_40[0] * 0x510 + 0x130)) {
          auStack_40[0] = auStack_40[iVar13];
          iVar3 = 1;
        }
        else if (*(int *)(this + auStack_40[0] * 0x510 + 0x130) ==
                 *(int *)(this + auStack_40[iVar13] * 0x510 + 0x130)) {
          auStack_40[iVar3] = auStack_40[iVar13];
          iVar3 = iVar3 + 1;
        }
      }
    }
    else {
      iVar4 = 0;
      fVar16 = -1.0;
      for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
        if (*(int *)(this + auStack_40[iVar3] * 0x510 + 300) != 0) {
          if (iVar4 == 0) {
            auStack_320[0] = auStack_40[iVar3];
            iVar4 = 1;
            fVar16 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
          }
          else {
            fVar15 = (float)*(int *)(this + auStack_40[iVar3] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar3] * 0x510 + 300);
            if (fVar16 < fVar15) {
              auStack_320[0] = auStack_40[iVar3];
              iVar4 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_320[iVar4] = auStack_40[iVar3];
              iVar4 = iVar4 + 1;
            }
          }
        }
      }
      iVar3 = 0;
      fVar16 = 65535.0;
      for (iVar13 = 0; iVar13 < iVar14; iVar13 = iVar13 + 1) {
        if (*(int *)(this + auStack_40[iVar13] * 0x510 + 300) != 0) {
          if (iVar3 == 0) {
            auStack_40[0] = auStack_40[iVar13];
            iVar3 = 1;
            fVar16 = (float)*(int *)(this + auStack_40[iVar13] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar13] * 0x510 + 300);
          }
          else {
            fVar15 = (float)*(int *)(this + auStack_40[iVar13] * 0x510 + 0x130) /
                     (float)*(uint *)(this + auStack_40[iVar13] * 0x510 + 300);
            if (fVar15 < fVar16) {
              auStack_40[0] = auStack_40[iVar13];
              iVar3 = 1;
              fVar16 = fVar15;
            }
            else if (fVar16 == fVar15) {
              auStack_40[iVar3] = auStack_40[iVar13];
              iVar3 = iVar3 + 1;
            }
          }
        }
      }
    }
    iVar14 = iVar3;
    unaff_s7_lo = 0x32;
    break;
  case 0x80:
    uStack_a0 = CONCAT22(uStack_a0._2_2_,0x58);
    uStack_a0 = uStack_a0 & 0xfffc7fff;
    uStack_9c = 0x4e;
    uStack_9b = 100;
    uStack_9a = 0;
    uStack_98 = 0;
    iVar4 = 0;
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if ((0 < *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) &&
         (lVar6 = Retail_CBattle_EffectCheckCore(this,auStack_40[iVar3],1,&uStack_a0,0),
         lVar6 != 0)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x81:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0) &&
         (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) == 0)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x46;
    break;
  case 0x82:
    for (iVar13 = 0; iVar13 < iVar14; iVar13 = iVar13 + 1) {
      uStack_4 = 0;
      for (iVar10 = 0; iVar10 < 0x20; iVar10 = iVar10 + 1) {
        if ((*(char *)(this + auStack_40[iVar13] * 0x510 + iVar10 * 0xc + 0x1d0) == 'T') &&
           (((ulong)*(byte *)(this + auStack_40[iVar13] * 0x510 + iVar10 * 0xc + 0x1cd) & 0x3f) >>
            3 != 0)) {
          if (((long)*(int *)(this + auStack_40[iVar13] * 0x510 + iVar10 * 0xc + 0x1cc) & 0x1ffffU
              ) >> 0xf != 0) {
            uStack_4 = 1;
          }
          if ((int)param_4 < 1) {
            uStack_4 = 1;
          }
          else if ((*(uint *)(this + auStack_40[iVar13] * 0x510 + iVar10 * 0xc + 0x1d4) & param_4)
                   != 0) {
            uStack_4 = 1;
          }
        }
      }
      if ((*(byte *)(this + auStack_40[iVar13] * 0x510 + 0xb4) & 1) == 0) {
        iVar10 = iGpffff83b4 + *(short *)(this + auStack_40[iVar13] * 0x510 + 0x120) * 0xc0;
        iStack_3a0 = 0;
        if (-1 < *(char *)(iVar10 + 0x6b)) {
          iStack_3a0 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(*(undefined2 *)(this + auStack_40[iVar13] * 0x510 + 0x120),
                                       7,*(undefined1 *)(iVar10 + 0x6b),
                                       iVar3 + (*(char *)(iVar10 + 0x6b) * 10 +
                                               (int)*(char *)(iVar10 + 0x6b)) * 4 + 0x10,&uStack_1c0
                                       ,this + auStack_40[iVar13] * 0x510 + 0xb0);
        }
        if (-1 < *(char *)(iVar10 + 0x6c)) {
          iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(*(undefined2 *)(this + auStack_40[iVar13] * 0x510 + 0x120),7,
                                  *(undefined1 *)(iVar10 + 0x6c),
                                  iVar3 + (*(char *)(iVar10 + 0x6c) * 10 +
                                          (int)*(char *)(iVar10 + 0x6c)) * 4 + 0x10,
                                  &uStack_1c0 + iStack_3a0 * 3,
                                  this + auStack_40[iVar13] * 0x510 + 0xb0);
          iStack_3a0 = iStack_3a0 + iVar5;
        }
        if (-1 < *(char *)(iVar10 + 0x6d)) {
          iVar10 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(*(undefined2 *)(this + auStack_40[iVar13] * 0x510 + 0x120),7,
                                   *(undefined1 *)(iVar10 + 0x6d),
                                   iVar3 + (*(char *)(iVar10 + 0x6d) * 10 +
                                           (int)*(char *)(iVar10 + 0x6d)) * 4 + 0x10,
                                   &uStack_1c0 + iStack_3a0 * 3,
                                   this + auStack_40[iVar13] * 0x510 + 0xb0);
          iStack_3a0 = iStack_3a0 + iVar10;
        }
        for (iVar10 = 0; iVar10 < iStack_3a0; iVar10 = iVar10 + 1) {
          if ((acStack_1bc[iVar10 * 0xc] == 'T') &&
             (((ulong)*(byte *)((int)&uStack_1c0 + iVar10 * 0xc + 1) & 0x3f) >> 3 == 2)) {
            if (((long)(int)(&uStack_1c0)[iVar10 * 3] & 0x1ffffU) >> 0xf != 0) {
              uStack_4 = 1;
            }
            if ((int)param_4 < 1) {
              uStack_4 = 1;
            }
            else if ((param_4 & auStack_1b8[iVar10 * 3]) != 0) {
              uStack_4 = 1;
            }
          }
        }
      }
      else {
        iVar10 = *(int *)(this + auStack_40[iVar13] * 0x510 + 0x150);
        uVar12 = (uint)((*(byte *)(iVar10 + 0x34) & 1) != 0);
        if ((long)((ulong)*(byte *)(iVar10 + 0x34) << 0x3e) < 0) {
          uVar12 = uVar12 | 2;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x34) << 0x3d) < 0) {
          uVar12 = uVar12 | 4;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x34) << 0x3c) < 0) {
          uVar12 = uVar12 | 8;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x34) << 0x3b) < 0) {
          uVar12 = uVar12 | 0x20;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x34) << 0x3a) < 0) {
          uVar12 = uVar12 | 0x80;
        }
        if ((long)((ulong)iVar10->wTurnPendMask << 0x3b) < 0) {
          uVar12 = uVar12 | 0x800;
        }
        if ((long)((ulong)iVar10->wTurnPendMask << 0x3a) < 0) {
          uVar12 = uVar12 | 0x1000;
        }
        if ((long)((ulong)iVar10->wTurnPendMask << 0x39) < 0) {
          uVar12 = uVar12 | 0x2000;
        }
        if ((long)((ulong)iVar10->wTurnPendMask << 0x38) < 0) {
          uVar12 = uVar12 | 0x4000;
        }
        if ((*(byte *)(iVar10 + 0x33) & 1) != 0) {
          uVar12 = uVar12 | 0x8000;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x33) << 0x3e) < 0) {
          uVar12 = uVar12 | 0x10000;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x33) << 0x3d) < 0) {
          uVar12 = uVar12 | 0x20000;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x33) << 0x3c) < 0) {
          uVar12 = uVar12 | 0x40000;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x33) << 0x3b) < 0) {
          uVar12 = uVar12 | 0x80000;
        }
        if ((long)((ulong)*(byte *)(iVar10 + 0x33) << 0x3a) < 0) {
          uVar12 = uVar12 | 0x100;
        }
        if (uVar12 != 0) {
          if ((int)param_4 < 1) {
            uStack_4 = 1;
          }
          else if ((uVar12 & param_4) != 0) {
            uStack_4 = 1;
          }
        }
      }
      if (uStack_4 == 0) {
        auStack_320[iVar4] = auStack_40[iVar13];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x83:
    uStack_a0 = CONCAT22(uStack_a0._2_2_,0x58);
    uStack_a0 = uStack_a0 & 0xfffc7fff;
    uStack_9c = 0x4e;
    uStack_9b = 100;
    uStack_9a = 0;
    uStack_98 = 0;
    iVar4 = 0;
    uVar12 = 0;
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (0 < *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) {
        Retail_CBattle_EffectCheckCore(this,auStack_40[iVar3],1,&uStack_a0,&uStack_4);
        uVar12 = uVar12 | uStack_4;
      }
    }
    if ((uVar12 & 0x17) != 0) {
      uVar12 = uVar12 | 7;
    }
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((0 < *(int *)(this + auStack_40[iVar3] * 0x510 + 0x130)) &&
          ((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0)) &&
         ((uVar12 & 1 << ((int)*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) & 0x1fU)) != 0
         )) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 100;
    break;
  case 0x84:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      lVar6 = CheckGuard__7CBattleFi(this,auStack_40[iVar3]);
      if ((lVar6 != 0) && (lVar6 != 4)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x32;
    break;
  case 0x85:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0) &&
         (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) == 0xb)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x32;
    break;
  case 0x86:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0) &&
         (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) == 0xc)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x32;
    break;
  case 0x87:
    for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
      if (((*(byte *)(this + auStack_40[iVar3] * 0x510 + 0xb4) & 1) == 0) &&
         (*(short *)(this + auStack_40[iVar3] * 0x510 + 0x120) == 0xd)) {
        auStack_320[iVar4] = auStack_40[iVar3];
        iVar4 = iVar4 + 1;
      }
    }
    unaff_s7_lo = 0x32;
  }
  iStack_3d0 = 0;
  for (iVar3 = 0; iVar3 < iVar14; iVar3 = iVar3 + 1) {
    for (this = 0; (this < iVar4 && (auStack_320[this] != auStack_40[iVar3]));
        this = this + 1) {
    }
    if (iVar4 <= this) {
      auStack_350[iStack_3d0] = auStack_40[iVar3];
      iStack_3d0 = iStack_3d0 + 1;
    }
  }
  if ((iVar4 == 0) && (iStack_3d0 == 0)) {
    uVar12 = 0xffffffff;
  }
  else if (iVar4 == 0) {
    iVar14 = rand();
    uVar12 = auStack_350[iVar14 % iStack_3d0];
  }
  else if (iStack_3d0 == 0) {
    iVar14 = rand();
    uVar12 = auStack_320[iVar14 % iVar4];
  }
  else {
    iVar14 = rand();
    if (unaff_s7_lo < iVar14 % 100) {
      iVar14 = rand();
      uVar12 = auStack_350[iVar14 % iStack_3d0];
    }
    else {
      iVar14 = rand();
      uVar12 = auStack_320[iVar14 % iVar4];
    }
  }
  return uVar12;
}

/* ---- 0x006e0260  EffectCheck__7CBattleFiiiP12EFCTCOMParam  (size 0xc0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
void EffectCheck__7CBattleFiiiP12EFCTCOMParam
               (int this,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  undefined8 uVar1;
  undefined1 auStack_b0 [96];
  int iStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  int iStack_10;
  
  iStack_50 = this;
  uStack_40 = param_2;
  uStack_30 = param_3;
  uStack_20 = param_4;
  iStack_10 = param_5;
  uVar1 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(this->cActor,param_3,param_4,param_5 + 8,auStack_b0,
                          this + this->cActor * 0x510 + 0xb0);
  Retail_CBattle_EffectCheckCore(iStack_50,uStack_40,uVar1,auStack_b0,0);
  return;
}

/* ---- 0x006e0320  Retail_CBattle_EffectCheckCore  (size 0x23c0) ----
 *   nStep values: []
 *   nPhase targets: []
 *   bState targets: [] */
bool Retail_CBattle_EffectCheckCore(int this,int param_2,int param_3,int param_4,uint *param_5)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  ulong uVar7;
  int aiStack_1b0 [8];
  undefined4 auStack_190 [74];
  int iStack_68;
  uint uStack_64;
  uint uStack_60;
  uint uStack_5c;
  uint uStack_58;
  uint uStack_54;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  uint *puStack_10;
  
  uStack_58 = 0;
  uStack_5c = 0;
  uStack_60 = 0;
  iVar4 = 0;
  iStack_50 = this;
  iStack_40 = param_2;
  iStack_30 = param_3;
  iStack_20 = param_4;
  puStack_10 = param_5;
  iStack_68 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
  if (puStack_10 != (uint *)0x0) {
    *puStack_10 = 0;
  }
  if (chr(iStack_50,iStack_40)->nHp < 1) {
    uStack_58 = uStack_58 | 0x80;
  }
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    if (*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) == 'T') {
      if (((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cd) & 0x3f) >> 3 == 0)
      {
        uStack_58 = uStack_58 | *(uint *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4);
      }
    }
    else if ((*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) == 'U') &&
            (((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cd) & 0x3f) >> 3 ==
             0)) {
      if ((*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cc) & 0x3f) < 0x18) {
        uStack_5c = uStack_5c | *(uint *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4);
      }
      else {
        uStack_60 = uStack_60 | *(uint *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4);
      }
    }
  }
  uStack_64 = 0;
  bVar1 = (chr(iStack_50,iStack_50->cActor)->bFlagsB & 1) !=
          (chr(iStack_50,iStack_40)->bFlagsB & 1);
  if (bVar1) {
    uStack_64 = 1;
  }
  uStack_64 = (uint)bVar1;
  if ((chr(iStack_50,iStack_40)->bFlagsB & 1) == 0) {
    iVar3 = iGpffff83b4 + chr(iStack_50,iStack_40)->nCharId * 0xc0;
    if (-1 < *(char *)(iVar3 + 0x6b)) {
      iVar4 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(chr(iStack_50,iStack_40)->nCharId,7,
                              *(undefined1 *)(iVar3 + 0x6b),
                              iStack_68 +
                              (*(char *)(iVar3 + 0x6b) * 10 + (int)*(char *)(iVar3 + 0x6b)) * 4 +
                              0x10,auStack_190,iStack_50 + iStack_40 * 0x510 + 0xb0);
    }
    if (-1 < *(char *)(iVar3 + 0x6c)) {
      iVar5 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(chr(iStack_50,iStack_40)->nCharId,7,
                              *(undefined1 *)(iVar3 + 0x6c),
                              iStack_68 +
                              (*(char *)(iVar3 + 0x6c) * 10 + (int)*(char *)(iVar3 + 0x6c)) * 4 +
                              0x10,auStack_190 + iVar4 * 3,iStack_50 + iStack_40 * 0x510 + 0xb0);
      iVar4 = iVar4 + iVar5;
    }
    if (-1 < *(char *)(iVar3 + 0x6d)) {
      iVar3 = SpecialEffectCode__FiiiP7ECParamP6EFFTBLP11BtlChrParam(chr(iStack_50,iStack_40)->nCharId,7,
                              *(undefined1 *)(iVar3 + 0x6d),
                              iStack_68 +
                              (*(char *)(iVar3 + 0x6d) * 10 + (int)*(char *)(iVar3 + 0x6d)) * 4 +
                              0x10,auStack_190 + iVar4 * 3,iStack_50 + iStack_40 * 0x510 + 0xb0);
      iVar4 = iVar4 + iVar3;
    }
    for (iVar3 = 0; iVar3 < iVar4; iVar3 = iVar3 + 1) {
    }
  }
  iVar4 = 0;
  do {
    if (iStack_30 <= iVar4) {
      iVar3 = 0;
      for (iVar4 = 0; iVar4 < iStack_30; iVar4 = iVar4 + 1) {
        iVar3 = iVar3 + aiStack_1b0[iVar4];
      }
      return iVar3 / iStack_30 != 0;
    }
    aiStack_1b0[iVar4] = 10000;
    switch(*(undefined1 *)(iStack_20 + iVar4 * 0xc + 4)) {
    case 0xc:
    case 0xd:
    case 0xe:
    case 0x13:
    case 0x14:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
      for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
        if ((((*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) ==
               *(char *)(iStack_20 + iVar4 * 0xc + 4)) &&
             (((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cd) & 7) >> 2 ==
              ((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) & 7) >> 2)) &&
            ((*(int *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4) < 1 ||
             (-1 < *(int *)(iStack_20 + iVar4 * 0xc + 8))))) &&
           ((-1 < *(int *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4) ||
            (*(int *)(iStack_20 + iVar4 * 0xc + 8) < 1)))) {
          aiStack_1b0[iVar4] = 0;
          break;
        }
      }
      break;
    case 0x23:
      for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
        if ((*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) ==
             *(char *)(iStack_20 + iVar4 * 0xc + 4)) &&
           (*(int *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4) ==
            *(int *)(iStack_20 + iVar4 * 0xc + 8))) {
          aiStack_1b0[iVar4] = 0;
          break;
        }
      }
      break;
    case 0x29:
    case 0x2a:
      for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
        if ((*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) ==
             *(char *)(iStack_20 + iVar4 * 0xc + 4)) &&
           (((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cd) & 7) >> 2 ==
            ((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) & 7) >> 2)) {
          aiStack_1b0[iVar4] = 0;
          break;
        }
      }
      break;
    case 0x2b:
      if (0 < chr(iStack_50,iStack_40)->nHp) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x46:
      if ((-1 < (long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d)) &&
         (chr(iStack_50,iStack_40)->nHp <= *(int *)(iStack_20 + iVar4 * 0xc + 8)))
      {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x47:
      if ((-1 < (long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d)) &&
         ((long)chr(iStack_50,iStack_40)->f86 <=
          (long)*(int *)(iStack_20 + iVar4 * 0xc + 8))) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x48:
      if ((-1 < (long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d)) &&
         ((long)chr(iStack_50,iStack_40)->nSp <=
          (long)*(int *)(iStack_20 + iVar4 * 0xc + 8))) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x49:
      if ((long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d) < 0) {
        if (chr(iStack_50,iStack_40)->nHp <
            (int)((*(int *)(iStack_50 + iStack_40 * 0x510 + 300) *
                   *(int *)(iStack_20 + iVar4 * 0xc + 8) + 99U) / 100)) {
          aiStack_1b0[iVar4] = 0;
        }
      }
      else if (chr(iStack_50,iStack_40)->nHp <=
               *(int *)(iStack_20 + iVar4 * 0xc + 8)) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x4a:
      if ((long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d) < 0) {
        if ((long)chr(iStack_50,iStack_40)->f86 <
            (long)((int)((uint)chr(iStack_50,iStack_40)->f84 *
                         *(int *)(iStack_20 + iVar4 * 0xc + 8) + 99) / 100)) {
          aiStack_1b0[iVar4] = 0;
        }
      }
      else if ((long)chr(iStack_50,iStack_40)->f86 <=
               (long)*(int *)(iStack_20 + iVar4 * 0xc + 8)) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x4b:
      if ((long)((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) << 0x3d) < 0) {
        if ((long)chr(iStack_50,iStack_40)->nSp <
            (long)((int)((uint)chr(iStack_50,iStack_40)->f88 *
                         *(int *)(iStack_20 + iVar4 * 0xc + 8) + 99) / 100)) {
          aiStack_1b0[iVar4] = 0;
        }
      }
      else if ((long)chr(iStack_50,iStack_40)->nSp <=
               (long)*(int *)(iStack_20 + iVar4 * 0xc + 8)) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x4e:
      iVar3 = 0;
      for (iVar5 = 0; iVar5 < 0x20; iVar5 = iVar5 + 1) {
        cVar2 = *(char *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d0);
        if (cVar2 == 'U') {
          uVar7 = ((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cd) & 0x3f) >>
                  3;
          if ((uVar7 == 2) || (uVar7 == 1)) {
            iVar3 = iVar3 + 1;
            if (puStack_10 != (uint *)0x0) {
              *puStack_10 = *puStack_10 |
                            1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                                 0x1f);
            }
          }
          else if (((uVar7 == 0) &&
                   ((*(uint *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) & 0x1f800) != 0)
                   ) && (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (cVar2 == 'T') {
          uVar7 = ((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cd) & 0x3f) >>
                  3;
          if (((uVar7 == 2) || (uVar7 == 1)) && (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (((cVar2 == 'P') || (cVar2 == 'O')) ||
                ((cVar2 == '7' || (((cVar2 == '*' || (cVar2 == ')')) || (cVar2 == '#')))))) {
          iVar3 = iVar3 + 1;
          if (puStack_10 != (uint *)0x0) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (cVar2 == ':') {
          if ((long)((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cd) << 0x3d)
              < 0) {
            if ((*(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) < 100) &&
               (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
              *puStack_10 = *puStack_10 |
                            1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                                 0x1f);
            }
          }
          else if ((*(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) < 0) &&
                  (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (cVar2 == '6') {
          if ((0x78 < *(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4)) &&
             (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (cVar2 == '4') {
          if ((*(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) < 1) &&
             (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (((((cVar2 == '8') || (cVar2 == '3')) || (cVar2 == '\"')) ||
                 ((cVar2 == '!' || (cVar2 == '\x1e')))) || ((cVar2 == '\x1d' || (cVar2 == '\x1b'))))
        {
          if ((*(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) < 0) &&
             (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if (((cVar2 == '>') || (cVar2 == '<')) || (cVar2 == '5')) {
          if ((long)((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cd) << 0x3d)
              < 0) {
            if ((100 < *(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4)) &&
               (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
              *puStack_10 = *puStack_10 |
                            1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                                 0x1f);
            }
          }
          else if ((0 < *(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4)) &&
                  (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)) {
            *puStack_10 = *puStack_10 |
                          1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) &
                               0x1f);
          }
        }
        else if ((((((((cVar2 == ' ') || (cVar2 == '\x1f')) || (cVar2 == '9')) ||
                    (((cVar2 == '2' || (cVar2 == '(')) ||
                     ((cVar2 == '\'' || ((cVar2 == '&' || (cVar2 == '%')))))))) ||
                   ((cVar2 == '\x1c' ||
                    (((((cVar2 == '1' || (cVar2 == '0')) || (cVar2 == '\x1a')) ||
                      ((cVar2 == '\x18' || (cVar2 == '\x19')))) ||
                     ((cVar2 == '\x17' || ((cVar2 == '\x14' || (cVar2 == '\x13')))))))))) ||
                  (cVar2 == '\x0e')) || ((cVar2 == '\r' || (cVar2 == '\f')))) &&
                ((0 < *(int *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1d4) &&
                 (iVar3 = iVar3 + 1, puStack_10 != (uint *)0x0)))) {
          *puStack_10 = *puStack_10 |
                        1 << (*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar5 * 0xc + 0x1cc) & 0x1f)
          ;
        }
      }
      if (iVar3 == 0) {
        aiStack_1b0[iVar4] = 0;
      }
      break;
    case 0x54:
    case 0x55:
      uVar6 = *(uint *)(iStack_20 + iVar4 * 0xc + 8);
      for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
        if ((*(char *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d0) ==
             *(char *)(iStack_20 + iVar4 * 0xc + 4)) &&
           (((ulong)*(byte *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1cd) & 0x3f) >> 3 ==
            ((ulong)*(byte *)(iStack_20 + iVar4 * 0xc + 1) & 0x3f) >> 3)) {
          uStack_54 = *(uint *)(iStack_50 + iStack_40 * 0x510 + iVar3 * 0xc + 0x1d4) & uVar6;
          uVar6 = uVar6 - uStack_54;
        }
      }
      if (uVar6 == 0) {
        aiStack_1b0[iVar4] = 0;
      }
    }
    iVar4 = iVar4 + 1;
  } while( true );
}
