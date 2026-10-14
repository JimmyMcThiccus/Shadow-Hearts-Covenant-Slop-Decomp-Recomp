# CBattle

The battle director. A singleton (`Sys__7CBattle`), allocated by `BtlSocket::Polling` state 1 (`new 0x4660`), a `CPolObj` descendant.
`Polling` (0x004314a0, 105 KB) is a switch over `phase = *(u16*)(this+0x28)`, `step = *(u16*)(this+0x2a)`; see `battle_flow.md` section 2 for the phase table
and `battle_rules.md` for every formula (GetMaxHP/GetStr/.../GetPAtkDamage/GetSAtkDamage/GetTurnInterval/TurnEnd/GetEscapeRate/BtlEndCheck/AddTrophy).
Rust: `sh2_battle::{rules, structs, flow}`.

Method groups (167 total): lifecycle (`__ct`, `Start`, `End`, `Destruct`, `Polling`), menu protocol (`BtlMenuCallBack`, `BtlMenuCBFunc`, `BtlMenuFunc`),
turn system (`InitTurnTiming`, `GetTurnInterval`, `GetNextTurnChr`, `TurnEnd`, `MakeTurnOrderTable`, `TurnInitSubFunc`, `TurnBeforeFunc`), stats (`GetMaxHP/MP/SP`, `GetStr/Vit/Int/Pow/Agl/Luc`, `GetPAtk/SAtk/PDef/SDef`, `Get*Rate`),
actions (`AttackFunc`, `PAtkHitSet`, `EffectFunc`, `EffectDamageSet`, `CheckCycleHit`, `CheckComboSkill`, `MaxComboFunc`), AI (`AITurnFunc`, AIS VM), status (`SetStatus`, `ResetStatus`, `Aroma*`, `Berserk*`),
rewards (`AddTrophy`, `MakeResultTrophy`), end (`BtlEndCheck`, `DeathInit`, `DeadReset`), camera hooks (`Set*Camera1`), pad/ring (`SetJRingStatus`, `GetJRingAreaResult`).

Struct `CBattle`, total size 0x4660 (Ghidra struct applied to `this`; field names are provisional, derived from use):

| off | type | field |
|---|---|---|
| 0x0 | _unknown_ | pad (0x24 bytes) |
| 0x24 | `byte` | `bFlags24` |
| 0x25 | `byte` | `bFlags25` |
| 0x26 | _unknown_ | pad (0x2 bytes) |
| 0x28 | `short` | `nPhase` |
| 0x2a | `short` | `nStep` |
| 0x2c | `char` | `cActor` |
| 0x2d | `char` | `cActorB` |
| 0x2e | `short` | `nPartner` |
| 0x30 | `short` | `nCurTurnChr` |
| 0x32 | `ushort` | `wTurnPendMask` |
| 0x34 | _unknown_ | pad (0x2 bytes) |
| 0x36 | `short` | `nComboCnt` |
| 0x38 | `float` | `flDeltaT` |
| 0x3c | _unknown_ | pad (0x4 bytes) |
| 0x40 | `int` | `nTurnNo` |
| 0x44 | `int` | `nCmd0` |
| 0x48 | `int` | `nCmd1` |
| 0x4c | `int` | `nCmdKind` |
| 0x50 | `int` | `nCmd3` |
| 0x54 | `int` | `nCmd4` |
| 0x58 | `int` | `nCmd5` |
| 0x5c | _unknown_ | pad (0x4 bytes) |
| 0x60 | `int` | `nShortcutTarget` |
| 0x64 | _unknown_ | pad (0x20 bytes) |
| 0x84 | `float` | `flMenuTimer` |
| 0x88 | `float` | `flMenuTimer2` |
| 0x8c | _unknown_ | pad (0x8 bytes) |
| 0x94 | `void *` | `pCbArg` |
| 0x98 | `void *` | `pCallback` |
| 0x9c | _unknown_ | pad (0x14 bytes) |
| 0xb0 | `BtlChr` | `aChr[12]` |
| 0x3bf0 | _unknown_ | pad (0x224 bytes) |
| 0x3e14 | `short` | `aTurnTbl[64]` |
| 0x3e94 | `short` | `aSideAlive[2]` |
| 0x3e98 | _unknown_ | pad (0x44 bytes) |
| 0x3edc | `byte` | `bGmodFlags` |
| 0x3edd | _unknown_ | pad (0x1 bytes) |
| 0x3ede | `ushort` | `wGmodStat` |
| 0x3ee0 | `int` | `nGmodValue` |
| 0x3ee4 | _unknown_ | pad (0x440 bytes) |
| 0x4324 | `void *` | `pCamera` |
| 0x4328 | `void *` | `pParamDisp` |
| 0x432c | _unknown_ | pad (0x40 bytes) |
| 0x436c | `void *` | `pTurnOrderDisp` |
| 0x4370 | _unknown_ | pad (0x14 bytes) |
| 0x4384 | `void *` | `pBtlMenu` |
| 0x4388 | _unknown_ | pad (0x1c bytes) |
| 0x43a4 | `ushort` | `wMonFormation` |
| 0x43a6 | `ushort` | `aMonIds[6]` |
| 0x43b2 | `byte` | `bEscapeFlags` |
| 0x43b3 | _unknown_ | pad (0x20f bytes) |
| 0x45c2 | `byte` | `bNoEvade` |
| 0x45c3 | `byte` | `bBattleSub` |
| 0x45c4 | _unknown_ | pad (0x28 bytes) |
| 0x45ec | `byte` | `aMenuRes[4]` |
| 0x45f0 | `ushort` | `wComboMask` |
| 0x45f2 | _unknown_ | pad (0x2 bytes) |
| 0x45f4 | `ushort` | `wResultFlags` |
| 0x45f6 | `byte` | `bTrophyCount` |
| 0x45f7 | `byte` | `bKillCount` |
| 0x45f8 | `short` | `aTrophyItem[6]` |
| 0x4604 | `byte` | `aTrophyChance[6]` |
| 0x460a | `byte` | `aTrophyCnt[6]` |
| 0x4610 | `int` | `nRewardExp` |
| 0x4614 | `int` | `nRewardCash` |
| 0x4618 | `uint` | `dwRewardSP` |
| 0x461c | `short` | `aKillList[18]` |
| 0x4640 | `byte` | `aTrophyMon[6]` |
| 0x4646 | `byte` | `aTrophyRare[6]` |
| 0x464c | _unknown_ | pad (0x14 bytes) |

Character array: 12 `BtlChr` at `this+0xb0+idx*0x4f0` (idx 0-3 PC front row, 4-7 PC reserve, 8-11 enemies - see `structs::chr`). Decompiler offsets = element offset + 0xb0.
Turn table `aTurnTbl` (+0x3e14, 64 x s16) is the predicted order shown by `TurnOrderDisp`.

### `BtlChr` (0x4f0 bytes, `CBattle+0xb0+i*0x4f0`)

Struct `BtlChr`, total size 0x4f0 (Ghidra struct applied to `this`; field names are provisional, derived from use):

| off | type | field |
|---|---|---|
| 0x0 | `byte` | `bFlagsA` |
| 0x1 | `byte` | `bFlagsA1` |
| 0x2 | `byte` | `bFlagsA2` |
| 0x3 | `byte` | `bFlagsA3` |
| 0x4 | `byte` | `bFlagsB` |
| 0x5 | `byte` | `bFlagsB1` |
| 0x6 | `byte` | `bFlagsB2` |
| 0x7 | `byte` | `bFlagsB3` |
| 0x8 | `byte` | `bState` |
| 0x9 | `byte` | `bState2` |
| 0xa | `short` | `nSubId` |
| 0xc | `int` | `nFormation` |
| 0x10 | `int` | `nSlot` |
| 0x14 | _unknown_ | pad (0x58 bytes) |
| 0x6c | `char *` | `pNamePtr` |
| 0x70 | `short` | `nCharId` |
| 0x72 | `ushort` | `wMaxHP` |
| 0x74 | `short` | `nHp` |
| 0x76 | `ushort` | `wMaxMP` |
| 0x78 | `short` | `nMp` |
| 0x7a | `ushort` | `wMaxSP` |
| 0x7c | `short` | `nSp` |
| 0x7e | `ushort` | `wAgl` |
| 0x80 | `ushort` | `wLuc` |
| 0x82 | `ushort` | `wPatk` |
| 0x84 | `ushort` | `wSatk` |
| 0x86 | `ushort` | `wPdef` |
| 0x88 | `ushort` | `wSdef` |
| 0x8a | `short` | `nNameSuffix` |
| 0x8c | _unknown_ | pad (0x8 bytes) |
| 0x94 | `void *` | `pModel` |
| 0x98 | `void *` | `pParam` |
| 0x9c | _unknown_ | pad (0x4 bytes) |
| 0xa0 | `float` | `aPos[4]` |
| 0xb0 | _unknown_ | pad (0x20 bytes) |
| 0xd0 | `float` | `flTurnInterval` |
| 0xd4 | `float` | `flTurnTimer` |
| 0xd8 | `float` | `flTurnWaited` |
| 0xdc | _unknown_ | pad (0x8 bytes) |
| 0xe4 | `void *` | `pAiScript` |
| 0xe8 | `void *` | `pAiCursor` |
| 0xec | `short` | `aAiReg[8]` |
| 0xfc | `ushort` | `wTurnCount` |
| 0xfe | _unknown_ | pad (0x6 bytes) |
| 0x104 | `float` | `flNextTurnMul` |
| 0x108 | `StatRec` | `aStatus[32]` |
| 0x288 | _unknown_ | pad (0x1d0 bytes) |
| 0x458 | `int` | `nVulnTurn` |
| 0x45c | _unknown_ | pad (0x4 bytes) |
| 0x460 | `ushort` | `wVulnCount` |
| 0x462 | _unknown_ | pad (0x2 bytes) |
| 0x464 | `float` | `flVulnA` |
| 0x468 | `float` | `flVulnB` |
| 0x46c | `float` | `flVariance` |
| 0x470 | _unknown_ | pad (0x3c bytes) |
| 0x4ac | `int` | `nAtkTbl` |
| 0x4b0 | _unknown_ | pad (0x26 bytes) |
| 0x4d6 | `short` | `nSpFrac` |
| 0x4d8 | _unknown_ | pad (0x18 bytes) |

Status list: 32 x `StatRec` (12 bytes) at element +0x108: `{s16 turns; s16 chance; s16 percent; u16 kind; i32 value}` - exact decoding in `structs::parse_status_record`.
`kind` values 0x0c..0x47 (max HP ... status bitfield) are the 'modifier kinds' in `rules::modkind`.


## Methods (167)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00430a80 | 0045eb00 | 0x6d0 | `CBattle::__ct()` |
| 00431150 | 0045f1c0 | 0x60 | `CBattle::BtlMenuCallBack(int, int, int, int, int, void *, void *)` |
| 004311b0 | 0045f220 | 0x2f0 | `CBattle::__dt()` |
| 004314a0 |  | 0x19d20 | `CBattle::Polling()` |
| 0044b270 | 00472c10 | 0x40 | `CBattle::RingCallBack(int, void *, void *)` |
| 0044b310 | 00472cb0 | 0x30 | `CBattle::EffectReplaceCallBack(Effect *, void *, int)` |
| 0044b340 | 00472ce0 | 0x70 | `CBattle::EffectCallBack(void *, int)` |
| 0044b4a0 | 00472e40 | 0x1a0 | `CBattle::Initialize()` |
| 0044b640 | 00472ff0 | 0x5b0 | `CBattle::Destruct(bool)` |
| 0044bbf0 | 004735a0 | 0x110 | `CBattle::Start()` |
| 0044bd00 | 00473690 | 0x100 | `CBattle::End()` |
| 0044be00 |  | 0x2b70 | `CBattle::TurnBeforeFunc()` |
| 0044e970 |  | 0x26a0 | `CBattle::BtlMenuFunc()` |
| 00451010 | 0047b700 | 0x81f0 | `CBattle::AttackFunc()` |
| 00459200 | 00484650 | 0x6410 | `CBattle::EffectFunc()` |
| 0045f610 |  | 0x10 | `CBattle::TarotEffectFunc()` |
| 0045f620 |  | 0x1120 | `CBattle::LastBossFunc()` |
| 00460740 | 0049ce90 | 0x110 | `CBattle::PCSet(int, char *)` |
| 00460850 | 0049cfb0 | 0x1c0 | `CBattle::PCEntry()` |
| 00460a10 |  | 0x15c0 | `CBattle::PCInit(int, _PCParam_Ver00 *, int, int)` |
| 00461fd0 | 0049fb10 | 0x1450 | `CBattle::FusMonInit(int, int)` |
| 00463420 |  | 0x180 | `CBattle::MonsterSet(MONSETTbl *)` |
| 004635a0 | 004a12e0 | 0x200 | `CBattle::MonsterEntry()` |
| 004637a0 |  | 0x1100 | `CBattle::MonsterInit(int, MONSTERParam *, int, int)` |
| 004648a0 | 004a26e0 | 0x470 | `CBattle::MakeFrameList(int)` |
| 00464d10 |  | 0x1c180 | `CBattle::BtlChrSequence()` |
| 00480ee0 |  | 0x290 | `CBattle::DeathInit(int)` |
| 00481170 | 004a3130 | 0x1660 | `CBattle::CalcPushRange(int)` |
| 004827d0 | 004a4460 | 0x4ef0 | `CBattle::PushCheck()` |
| 004876c0 | 004a9350 | 0x134f0 | `CBattle::AttackParam(int)` |
| 0049abb0 | 004bab40 | 0x5d50 | `CBattle::AttackHitCheck()` |
| 004a0900 | 004c0950 | 0x800 | `CBattle::SearchFront(int)` |
| 004a1100 | 004c1140 | 0x120 | `CBattle::GetAttackPos(int, int, float, FVector *, int *, FVector *, int *)` |
| 004a1220 | 004c1260 | 0x5e0 | `CBattle::GetMoveAngle(int)` |
| 004a1800 | 004c1830 | 0x13f0 | `CBattle::GetComboMovePos(int, int)` |
| 004a2bf0 | 004c2d30 | 0x5e00 | `CBattle::MotionEventCallBack(short, char *, char *, ushort, int, uint)` |
| 004a89f0 | 004c95d0 | 0x5d0 | `CBattle::MotionEndCallBack(short, char *)` |
| 004a8fc0 | 004c9b80 | 0x50 | `CBattle::SetBtlBG(int)` |
| 004a9010 | 004c9bd0 | 0x3c0 | `CBattle::BtlBGSequence()` |
| 004a93d0 | 004c9fa0 | 0x14c0 | `CBattle::BtlMenuCBFunc(int, int, int, int, int, void *)` |
| 004aa890 |  | 0xd00 | `CBattle::SetBtlMessage(int, void *)` |
| 004ab590 | 004cb920 | 0x13a70 | `CBattle::BtlChrPosInit(bool)` |
| 004bf000 |  | 0x820 | `CBattle::CheckGambit()` |
| 004bf820 | 004dfe80 | 0x930 | `CBattle::GetTurnInterval(int)` |
| 004c0150 |  | 0x470 | `CBattle::InitTurnTiming(int)` |
| 004c05c0 |  | 0x2e0 | `CBattle::GetNextTurnChr2()` |
| 004c08a0 | 004e1b30 | 0x430 | `CBattle::GetTurnChrList(int *)` |
| 004c0cd0 | 004e1f60 | 0xf20 | `CBattle::GetNextTurnChr(int)` |
| 004c1bf0 | 004e2ee0 | 0x820 | `CBattle::TurnEnd(int, int, float)` |
| 004c2410 |  | 0x2250 | `CBattle::MakeTurnOrderTable(float, int, int *, int, int, uint *, short, int, bool, int)` |
| 004c4660 | 004e62d0 | 0x770 | `CBattle::GetEvasionRate(int, int)` |
| 004c4dd0 | 004e6990 | 0x6b0 | `CBattle::GetCriticalRate(int, int)` |
| 004c5480 | 004e6f80 | 0x8a0 | `CBattle::GetEscapeRate(int)` |
| 004c5d20 | 004e7770 | 0x3000 | `CBattle::SearchEscapePoint(int)` |
| 004c8d20 | 004ea770 | 0x70 | `CBattle::DestinationInit()` |
| 004c8d90 | 004ea7e0 | 0x2460 | `CBattle::DestinationSearch(int)` |
| 004cb1f0 | 004ecc80 | 0x840 | `CBattle::DestinationListUp(int, int)` |
| 004cba30 | 004ed4c0 | 0x11e0 | `CBattle::HomingMove(int, FVector, int, float, float, float)` |
| 004ccc10 | 004ee6d0 | 0x3ed0 | `CBattle::HomingMoveEX(int, FVector, int, FVector, float, float, float)` |
| 004d0ae0 | 004f2840 | 0x1e0 | `CBattle::MoveWorkInit(int, float, float, float, float)` |
| 004d0cc0 | 004f2a20 | 0x9c0 | `CBattle::MoveFunc(int, float)` |
| 004d1680 | 004f33e0 | 0x4360 | `CBattle::DamMoveFutureSet(int)` |
| 004d59e0 | 004f8050 | 0x6720 | `CBattle::DamMoveFuture(int, FVector *, int *)` |
| 004dc100 | 004fe770 | 0x1b0 | `CBattle::BtlEffEntry(int, BtlEff *)` |
| 004dc2b0 | 004fe920 | 0x1a0 | `CBattle::BtlEffRelease(int, BtlEff *)` |
| 004dc450 | 004feac0 | 0xa0 | `CBattle::BtlEffFind(int, int)` |
| 004dc4f0 | 004feb60 | 0xa0 | `CBattle::BtlEffAllDelete(int)` |
| 004dc590 | 004fec00 | 0x90 | `CBattle::BtlEffAllEndSet(int)` |
| 004dc620 | 004fec90 | 0xe0 | `CBattle::BtlAtkEffAllEndSet(int)` |
| 004dc700 | 004fed70 | 0xa0 | `CBattle::EffMdlEntry(EffMdl *)` |
| 004dc7a0 | 004fee10 | 0xc0 | `CBattle::EffMdlRelease(EffMdl *)` |
| 004dc860 | 004feed0 | 0x70 | `CBattle::EffMdlAllDelete()` |
| 004dc8d0 | 004fef40 | 0xa0 | `CBattle::AllEffMdlDispOn()` |
| 004dc970 | 004fefe0 | 0xa0 | `CBattle::AllEffMdlDispOff()` |
| 004dca10 |  | 0x10 | `@24@__dt__7CBattleFv` |
| 005db820 |  | 0x200 | `CBattle::StepEffectFunc(int, int *, EFFTBL *)` |
| 005e7a00 | 00633b90 | 0x2d0 | `CBattle::DataReadEntry(int, int, int)` |
| 005e7cd0 | 00633e90 | 0x1e0 | `CBattle::DataRelease(int, int, bool)` |
| 005e7eb0 | 00634070 | 0x2470 | `CBattle::DataPolling()` |
| 005ea320 | 00636b40 | 0x1e0 | `CBattle::AllCSERelease()` |
| 005ea500 | 00636d20 | 0x170 | `CBattle::AllCSEEndCheck()` |
| 005ea670 |  | 0xa40 | `CBattle::InitSequence()` |
| 005eb0b0 | 00636e90 | 0x7e0 | `CBattle::GetMaxHP(int)` |
| 005eb890 | 00637550 | 0x730 | `CBattle::GetMaxMP(int)` |
| 005ebfc0 | 00637b90 | 0x520 | `CBattle::GetMaxSP(int)` |
| 005ec4e0 | 00637fa0 | 0x600 | `CBattle::GetStr(int)` |
| 005ecae0 | 00638490 | 0x600 | `CBattle::GetVit(int)` |
| 005ed0e0 | 00638980 | 0x600 | `CBattle::GetInt(int)` |
| 005ed6e0 | 00638e70 | 0x600 | `CBattle::GetPow(int)` |
| 005edce0 |  | 0x7f0 | `CBattle::GetAgl(int, int)` |
| 005ee4d0 |  | 0x880 | `CBattle::GetLuc(int, int)` |
| 005eed50 |  | 0x960 | `CBattle::GetPAtk(int)` |
| 005ef6b0 |  | 0xa70 | `CBattle::GetSAtk(int)` |
| 005f0120 |  | 0x8c0 | `CBattle::GetPDef(int)` |
| 005f09e0 |  | 0x8c0 | `CBattle::GetSDef(int)` |
| 005f12a0 |  | 0x2700 | `CBattle::EffectResetFunc(int, int)` |
| 005f39a0 |  | 0x8b0 | `CBattle::EffectEndFunc(int, int, int)` |
| 005f4250 |  | 0x790 | `CBattle::CheckGuard(int)` |
| 005f49e0 | 0063f6f0 | 0xcc0 | `CBattle::VSCircleHitCheck(int, FVector, float, FVector *)` |
| 005f56a0 | 00640470 | 0x1eb0 | `CBattle::VSLineHitCheck(int, FVector, FVector, FVector *)` |
| 005f7550 | 006424b0 | 0x190 | `CBattle::GetRiseTime(int)` |
| 005f76e0 | 00642640 | 0x210 | `CBattle::GetFlightTime(int)` |
| 005f78f0 | 00642850 | 0x380 | `CBattle::InvolveHitCheck(int)` |
| 005f7c70 | 00642c10 | 0x2c50 | `CBattle::InvolveDamageSet(int, int, FVector)` |
| 005fa8c0 | 00645850 | 0x7350 | `CBattle::PAtkHitSet(int, int, FVector, float, int, int, int, int, ushort, ushort, float, int, int)` |
| 00601c10 |  | 0xe80 | `CBattle::WallHitDamageSet(int, int, float, FVector)` |
| 00602a90 |  | 0x3340 | `CBattle::GetPAtkDamage(int, int, int *, int *, int *, int, int, float, float *)` |
| 00605dd0 |  | 0x2c90 | `CBattle::GetSAtkDamage(int, int, int *, int *, int, float, int, float, float *)` |
| 00608a60 |  | 0x2ce0 | `CBattle::GetSkillPAtkDamage(int, int, int *, int *, int, float, int, float, float *)` |
| 0060b740 | 006565e0 | 0x3130 | `CBattle::FindAdjacentAttackPos(int, int, float, FVector *, int *, FVector *, int *)` |
| 0060e870 | 0065ab90 | 0x2050 | `CBattle::FindRemoteAttackPos(int, int, float, FVector *, int *, FVector *, int *)` |
| 006108c0 |  | 0xc70 | `CBattle::FindAdjacentEffectPos(int, int, float, FVector *)` |
| 00611530 | 0065f390 | 0x1a0 | `CBattle::RingCBFunc(int, void *)` |
| 006116d0 |  | 0x16c0 | `CBattle::SetJRingStatus(int, int, int *)` |
| 00612d90 | 00660ad0 | 0x2a0 | `CBattle::GetJRingAreaResult(int, uchar *, char *)` |
| 00613030 |  | 0xd0 | `CBattle::InitBtlResult()` |
| 00613100 | 00660ed0 | 0x450 | `CBattle::AddTrophy(int, MONSTERParam *)` |
| 00613550 |  | 0x1b30 | `CBattle::MakeResultTrophy(int)` |
| 00615080 |  | 0x8d0 | `CBattle::MakeAromaEffectMes(char *)` |
| 00615950 | 00663e30 | 0x460 | `CBattle::NameChange(int)` |
| 00615db0 |  | 0x78d0 | `CBattle::EffectMesCall(int, ECResult *, FVector *, bool)` |
| 0061d680 |  | 0x1540 | `CBattle::GetShortCutTarget()` |
| 0061ebc0 | 006704d0 | 0x1d0 | `CBattle::MaxHitFunc(int)` |
| 0061ed90 | 006706a0 | 0xd0 | `CBattle::MaxComboFunc(int)` |
| 0061ee60 |  | 0x1920 | `CBattle::TurnInitSubFunc()` |
| 00620780 | 00671bc0 | 0x3a0 | `CBattle::GetNextComboCnt()` |
| 00620b20 | 00671f50 | 0x130 | `CBattle::PlayVibration(int)` |
| 00620c50 |  | 0x1f0 | `CBattle::BtlChrReadyCheck()` |
| 00620e40 |  | 0x20d0 | `CBattle::InitBtlChrPosAngle(int, int)` |
| 00622f10 | 006792a0 | 0xec0 | `CBattle::CheckComboMenber(int)` |
| 00623dd0 | 0067a430 | 0x170 | `CBattle::SetTargetAngle(int, int)` |
| 00623f40 | 0067a5a0 | 0x390 | `CBattle::ChangeBtlChrAngle(int, float)` |
| 006242d0 |  | 0x340 | `CBattle::BtlEndCheck()` |
| 00624610 | 0067ad90 | 0x510 | `CBattle::GetDefaultTarget(int)` |
| 00624b20 | 0067b360 | 0x560 | `CBattle::SetAutoFusionOff(int, int)` |
| 00625080 | 0067b870 | 0x9e50 | `CBattle::FusionOffPolling()` |
| 0062eed0 | 00688350 | 0x1b30 | `CBattle::GetTargetList(int, int, int, int, int, ECCParam *, int *, int *)` |
| 00630a00 | 00690270 | 0x5f60 | `CBattle::BerserkFunc()` |
| 00636960 | 00696ab0 | 0x730 | `CBattle::PAtkEffectFunc(int, int, FVector *, ECResult *)` |
| 00637090 |  | 0xe40 | `CBattle::StatusRecovery(int, ECResult *, FVector *)` |
| 00637ed0 | 006984f0 | 0x1380 | `CBattle::CheckProtect(int)` |
| 00639250 |  | 0xc50 | `CBattle::CheckStandBy()` |
| 00639ea0 | 0069abe0 | 0x720 | `CBattle::CheckComboSkill(int, int *, int *)` |
| 0063a5c0 |  | 0x790 | `CBattle::DeadReset(int)` |
| 0063ad50 |  | 0xc70 | `CBattle::AromaTurnReset()` |
| 0063b9c0 |  | 0x1230 | `CBattle::AromaEffectFunc(int)` |
| 0063cbf0 | 006a4de0 | 0xb50 | `CBattle::DecMPp(int, int, int, int)` |
| 0063d740 | 006a58e0 | 0x100 | `CBattle::DecMP(int, int, int, int)` |
| 0063d840 | 006a59f0 | 0x8c0 | `CBattle::DecSPp(int, int, int)` |
| 0063e100 |  | 0xbf0 | `CBattle::DecSP(int, int)` |
| 0063ecf0 | 006a65f0 | 0x5e0 | `CBattle::CheckCycleHit(int)` |
| 0063f2d0 |  | 0x700 | `CBattle::GetIconList(int, int *, int *)` |
| 0063f9d0 | 006a79f0 | 0x830 | `CBattle::IconFunc(int)` |
| 00640200 | 006a83d0 | 0x340 | `CBattle::BerserkCheck()` |
| 00640540 |  | 0x300 | `CBattle::GetDeadlyThrowTarget()` |
| 00640840 | 006a9150 | 0x29c0 | `CBattle::LastBossSpecial()` |
| 00643200 |  | 0x1e0 | `CBattle::AIInit(int)` |
| 006433e0 |  | 0x1810 | `CBattle::AITurnFunc(int)` |
| 00644bf0 |  | 0x3a30 | `CBattle::AIIfFunc(int, short *)` |
| 00648620 |  | 0xe50 | `CBattle::AICalcFunc(int, short *)` |
| 00649470 | 006d7070 | 0x3a0 | `CBattle::AIGetValueOne(int, short *, short *)` |
| 00649810 |  | 0x17a0 | `CBattle::AIGetValue(int, short, short, short, short, short, short)` |
| 0064afb0 |  | 0x4110 | `CBattle::GetTarget(int, int, int, int, int, int)` |
| 0064f0c0 |  | 0x3d0 | `CBattle::GetMoveTarget(int, int, int, int)` |
| 0064f490 |  | 0x6e0 | `CBattle::GetComboTarget(int, bool)` |
| 0064fb70 |  | 0x510 | `CBattle::CheckComboTarget(int *, int *, int *, int *, int *, int *)` |
| 00650080 |  | 0x6780 | `CBattle::EffectCheck(int, int, int, EFCTCOMParam *)` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @24@ |
| +0xd | byte | 1 | @24@ |
| +0x14 | u32 | 1 | __dt__7CBattleFv |
| +0x20 | u32 | 2 | __dt__7CBattleFv |
| +0x24 | byte | 16 | CheckGambit |
| +0x25 | byte | 3 | EffectCallBack, __dt__7CBattleFv |
| +0x26 | byte | 11 | LastBossSpecial |
| +0x28 | short | 3 | GetIconList |
| +0x2c | char | 25 | CalcPushRange, PushCheck |
| +0x32 | ushort | 1 | GetNextComboCnt |
| +0x36 | short | 4 | EffectMesCall, MaxComboFunc |
| +0x7c | u32 | 1 | @24@ |
| +0x80 | int | 1 | @24@ |
| +0x94 | u32 | 1 | __dt__7CBattleFv |
| +0x98 | int | 1 | __dt__7CBattleFv |
| +0x3c30 | short | 6 | StepEffectFunc |
| +0x3e1e | byte | 1 | GetComboTarget |
| +0x3e98 | u16 | 1 | DestinationInit |
| +0x3edc | byte | 1 | EffectMesCall |
| +0x3ede | short | 1 | EffectMesCall |
| +0x3ee0 | uint | 1 | EffectMesCall |
| +0x3ef0 | short | 2 | MakeAromaEffectMes |
| +0x3ef4 | float | 1 | MakeAromaEffectMes |
| +0x3ef8 | ushort/byte | 2 | MakeAromaEffectMes |
| +0x3f00 | byte | 1 | MakeAromaEffectMes |
| +0x3f0c | u8 | 1 | SetBtlBG |
| +0x3f0d | char/u8 | 3 | BtlBGSequence, SetBtlBG |
| +0x3f0e | u8 | 1 | SetBtlBG |
| +0x3f0f | u8 | 1 | SetBtlBG |
| +0x3f10 | short | 2 | BtlBGSequence |
| +0x3f14 | float | 21 | GetComboMovePos, LastBossSpecial, PushCheck, SearchFront |
| +0x3f1c | float | 21 | GetComboMovePos, LastBossSpecial, PushCheck, SearchFront |
| +0x3f20 | u32 | 1 | SetBtlBG |
| +0x430c | int | 2 | @24@ |
| +0x4324 | int | 2 | __dt__7CBattleFv |
| +0x4370 | int/u32 | 8 | AllEffMdlDispOff, AllEffMdlDispOn, BtlAtkEffAllEndSet, BtlEffAllDelete, BtlEffAllEndSet, BtlEffEntry… |
| +0x4374 | int/u32 | 5 | BtlEffEntry, BtlEffRelease |
| +0x4378 | int/u32 | 5 | AllEffMdlDispOff, AllEffMdlDispOn, EffMdlAllDelete, EffMdlEntry, EffMdlRelease |
| +0x437c | int/u32 | 5 | EffMdlEntry, EffMdlRelease |
| +0x4380 | int | 8 | BtlEffEntry, BtlEffRelease, EffMdlEntry, EffMdlRelease |
| +0x4388 | int/u32 | 2 | EffectCallBack |
| +0x4390 | short | 1 | GetDefaultTarget |
| +0x4392 | short | 1 | GetDefaultTarget |
| +0x43a8 | int/u32 | 2 | @24@ |
| +0x43ac | int/u32 | 2 | @24@ |
| +0x43b4 | int | 1 | MakeFrameList |
| +0x43b8 | int | 1 | MakeFrameList |
| +0x43bc | u16 | 1 | MakeFrameList |
| +0x43be | short | 3 | CalcPushRange, MakeFrameList |
| +0x43c0 | int/u32 | 7 | CalcPushRange, MakeFrameList, __dt__7CBattleFv |
| +0x43c4 | int/u32 | 54 | CalcPushRange, MakeFrameList, PushCheck, __dt__7CBattleFv |
| +0x457f | char | 1 | @24@ |
| +0x4580 | int | 1 | @24@ |
| +0x4597 | char | 1 | __dt__7CBattleFv |
| +0x4598 | int | 1 | __dt__7CBattleFv |
| +0x45a8 | u32 | 3 | EffectMesCall, PlayVibration |
| +0x45c0 | u8 | 1 | LastBossSpecial |
| +0x45c2 | char | 1 | CheckGambit |
| +0x45d4 | short | 1 | LastBossSpecial |
| +0x45f4 | byte | 2 | EffectMesCall |
| +0x4634 | uint | 2 | MaxHitFunc |
| +0x4638 | int | 2 | MaxComboFunc |
| +0x4650 | int | 2 | StepEffectFunc |
