# Battle scene flow: BtlSocket → CBattle → BtlMenu → effects

Rust: `port/crates/sh2_battle/src/flow.rs` (phase machine, menu protocol, menu navigation, simplified action resolver).

```
field / event script ──SSHSys::StartBattle(_SysBtlParam*, returnPath)──▶ SSHSys.PollingApi byte +0x36 = 0x20
   │                                                                         │
   │            (0x20/0x21 → InitBtlSocket)                                  ▼
   │                                              InitBtlSocket (0x0032d4c0) : new BtlSocket(0x69c bytes)   ──▶ SSHSys::SetAPI(socket)
   │                                              BtlSocket::preLoad  : Overlay::Load("BATTLE.BIN") (state 0→1→2)
   │                                              BtlSocket::Start    : poller entry prio 0x80, resets result accumulators
   ▼                                              BtlSocket::Polling  : state machine below
 return to field (CField reloaded through cbBattleA)
```

## 1. Main-executable side

### SSHSys::StartBattle (0x003b6c20) / cbBattle / cbBattleA
`_SysBtlParam` (copied to `SSHSys+0x40…0x4f`): `u32 a; u32 b; u16 c; u8 d, e; u8 f?; u8 g,h,i` (monster-set index list, PC count, flags — see
class notes) and a field path string kept at `SSHSys+0x54` (the map to return to).  Sets `SSHSys.+0x36 = 0x20` (battle request).
After the fight `cbBattleA(code)`: code 0 → depending on the outcome bits of `BtlSocket+0x16c & 3` (0 win, 1 escaped/run?, 2/3 lost):
lose → `SSHSys+0x36 = 0x10 (field)` with 'game over' flag 0xff; win → `+0x36 = 0x10`; escaped → 0x30 (game over scene) only if no map path;
code 1 → `FieldPreLoad(path)`.

### BtlSocket (0x0032d610 … 0x0032f720; JP symbols)
| member | note |
|---|---|
| `+0x20` flags, `+0x24` overlay load state (0 idle, 1 loading, 2 loaded), `+0x28` **state** | see below |
| `+0x34` current monster-set index, `+0x58` number of sets, `+0x5c + i*0x10` copies of `MONSETTbl` | `SetMonsterSet/AddMonsterSet` (0x0032f260/0x0032f2b0) |
| `+0x47` roster count (≤8), `+0x49` number of PCs in this fight, `+0x4a…` PC ids (≤4 in front, 4 reserve) | `SetPC/AddPC` (0x0032efe0/0x0032f0e0): PC ids are inserted before the reserve |
| `+0x15c` background id, `+0x168` demo flag (1 = opening demo battle), `+0x16c` result (bits0-1 outcome, bits2-6 fights won) | |
| `+0x164/+0x160` result callback + arg (SSHSys::cbBattle) | called with 1 (battle over: continue) / 0 (everything released) |
| `+0x16e..` consolidated drops: `+0x170` item ids (s16 ×?), `+0x230` counts, `+0x290/+0x294/+0x298` exp/cash/sp totals, `+0x29c` per-PC exp[12], `+0x2cc/+0x44c` kills, `+0x526/+0x540/+0x5a0` trophy keys | filled by `BtlCBFunc` code 1 |
| `+0x600..0x602` loading of the transition graphics (`FileReadEntry("btlin…")`, 28 textures `JRCTex`) for the "Judgement ring"/UI sprites | |
| `+0x68c/0x690` `SmoothFilter` / `BlurFilter` (screen filters toggled by `FilterOn/FilterOff`) | |
| `+0x694` battle BGM number, `+0x698` Yoahism level (`BtlSaveSec::GetYoahism`; 3→4 when savedata bit set) | |

**BtlSocket::Polling** (`+0x28`): `1` create `CBattle` (`new 0x4660`, cb = `BtlCallBack`), `SetBtlBG(bg)`, `PCSet(n, ids)`, `MonsterSet(sets[idx])`, `Start()`,
→ 2 (running) ; `2` wait for `CBattle` callback code 0 (`BtlCBFunc`) → 4 ; `3` `BattleEnd()` was called → `CBattle::End` ; `4` battle finished: release sounds,
`FilterOff`, next monster set if `idx < nSets` and outcome==win (state 1 again), else show result (5 = `BtlBonus` victory screen / 6 = `BtlResult` for defeat) ;
`5/6` wait for the UI object to disappear ; `7` fade result BGM ; `8` wait sound release, state 0, callback(0) and return.
`BtlCBFunc(code, arg)`: code 0 → state 4; code 1 → accumulate the per-fight **result record** (below).

### Result record (what `CBattle::MakeResultTrophy` hands to `BtlSocket::BtlCBFunc`, ~0x470 bytes)
```
+0x000 u16  outcome in bits0-1 (0 win …) ; +0x002 u8 nItems ; +0x003 u8 nKills
+0x004 s16  item[nItems] ; +0x0c4 u8 count[nItems]
+0x124 i32  exp ; +0x128 i32 cash ; +0x12c u32 sp ; +0x130 i32 pcExp[12]
+0x160 s16  killId[nKills] ; +0x2e0 u8 killCount ; +0x3ba u8 nTrophyKeys ; +0x3d4 u8 key[], +0x434 u8 keyRare[]
```
`BtlBonus` (0x0034c810; `WinSequence` 0x003581f0 / `WinCreate` 0x00358530, `MakePacket` 0xad44 bytes) draws the victory windows (EXP, cash, items,
level-ups).  `BtlResult` is the defeat counterpart.  `BtlFader` (0x00371870) draws the full-screen fade (`SetMode(mode, time, rgba)`);
`BtlIn`/`BtlInBoss` (0x003ad2c0 / 0x003b2770) are the swirling battle-entry transition (`StartBtlIn`, `CaptureBtlIn`).

## 2. CBattle (BATTLE.BIN 0x00430a80; singleton `Sys__7CBattle`)

`CBattle::Polling` (0x004314a0, 105 KB!) switches on `phase = *(u16*)(this+0x28)` with `step = *(u16*)(this+0x2a)`:

| phase | name (ours) | delegate | notes |
|---|---|---|---|
| 1 | Init | inline (653 lines) + `InitSequence` | `DataReadEntry` of models/effects, `PCEntry`, `MonsterEntry`, `CheckGambit`, `BtlChrPosInit`, `InitTurnTiming` for all, create `BtlMenu`, `ParamDisp`, `ComboForm`, `HitInfo`; messages "enemies surrounded!" (ambush 1) / "surrounded by enemies!" (2) |
| 2 | TurnSelect | inline | `BtlEndCheck` → win(0x11)/lose(0x12); `GetNextTurnChr`, camera, windows, `TurnInitSubFunc`, `GetDefaultTarget`; → 3 or 4 |
| 3 | TurnBefore | `TurnBeforeFunc` (0x0044be00, 11 KB) | poison/status ticks, `DecSP`, aroma ticks (`AromaTurnReset/AromaEffectFunc`), berserk start; → 4 |
| 4 | Command | `BtlMenuFunc` (0x0044e970) | PC: BtlMenu callbacks (below); enemy/berserk PC: `AITurnFunc`; short-cut menu (step 0x28); friendship +100 |
| 5 | Attack | `AttackFunc` (0x00451010, 28 KB) | move to target (`Find*AttackPos`, `HomingMove`), judgement ring (`SetJRingStatus`, `GetJRingAreaResult`), hits (`PAtkHitSet` 22 KB → `GetPAtkDamage`), `CheckProtect`; → 0xf / 0x10 |
| 6 | Guard | inline | wait until `BtlChrReadyCheck`, `MaxComboFunc`, close windows → 0x10 |
| 7 | Link | inline | walk next to the partner (`Get3DAngle`, `ChangeBtlChrAngle`, `SetMoveCamera1`) → 0x10 |
| 8 | Escape | inline | `GetEscapeRate`, `SearchEscapePoint`, message "couldn't escape!" or fade + `MakeResultTrophy` → 0x13 / 0x10 |
| 9 | Fusion | inline (460 lines) | `FusMonInit`, `SetFusionCamera1`, load fusion model, effect, → 2 |
| 10 | Effect | `EffectFunc` (0x00459200, 25 KB) | items/magic/skills: `GetRegDat`, effect VM (`EffectResetFunc/EffectEndFunc/EffectCodeFunc` in main), `EffectDamageSet` (15 KB), `CheckCycleHit`, ring |
| 0xb | RingSkill | inline (940 lines) | judgement-ring skill (kind 4): creates a `JRing`, `AddStepArea/AddModulateArea`, `SetJRingStatus` |
| 0xc | Aroma | inline (735 lines) | aroma (Anna?) sequence with ring and `AromaEffectFunc`, `MakeAromaEffectMes` |
| 0xd | Tarot | `TarotEffectFunc` (0x0045f610, 16 bytes = stub) | not in the demo |
| 0xe | LastBoss | `LastBossFunc` (0x0045f620) → `LastBossSpecial` | final boss scripted sequence |
| 0xf | ActionDone | inline | BGM/fade bookkeeping → 0x10 |
| 0x10 | Death | inline (637 lines) | `DeathInit`, `CmbBreak`/`BreakBBox` break effects, `DeadReset`, win/lose test → 2 or 0xf |
| 0x11 | Win | inline | `SetWinCamera1`, victory pose, result BGM, `MakeResultTrophy(0)`, `End()` |
| 0x12 | Lose | inline | `SetLoseCamera1`, `SetAutoFusionOff`, `MakeResultTrophy`, fade → 0x13 |
| 0x13 | End | inline | release everything (`Destruct`), `DataPolling`, `BtlChrSequence`, `BtlBGSequence`, wait for fade, callback code 0 |

`End()` (0x0044bd00) can be requested from outside (`BtlSocket::BattleEnd`): fades out, `MakeResultTrophy(3)`, phase 0x13.

Command parameters live in `CBattle+0x44..0x58` (`structs::cbattle::CMD_*`).  Per-character animation is driven by `BtlChrSequence` (0x00464d10,
2 KB, called every frame from phase 0x13 and from the poller), `MotionEventCallBack` (0x004a2bf0, 22 KB: model motion events → damage frames, SE, effects)
and `MotionEndCallBack`.

## 3. BtlMenu (command UI) → CBattle protocol

`BtlMenu::SetCallBack(fn)` is set to `CBattle::BtlMenuCallBack` (0x00431150) which forwards to `BtlMenuCBFunc(chr,code,a,b,c,d,e)` (0x004a93d0):

| code | meaning | effect on CBattle |
|---|---|---|
| 0 | cursor on character `a` | `actor=a`, pending combo mask |= 1<<a, camera, `MakeTurnOrderTable(3.0…)` |
| 1,22 | window sequence finished | `step++` |
| 2 | | `step=2; timer=0` |
| 3 | camera on actor (PC: home or character camera by +0x57a) | |
| 4 | **attack**: target `b`, kind `c`, ring-skill `d` | phase 5, `+0x44=a`, `+0x48=b`, `+0x4c=c`, `+0x54/+0x58 = (3,d)` or `(0,-1)`; enemies step 0x14 |
| 5 | **item** `a` on `b` | phase 10, kind 0 |
| 6 | magic | phase 10, kind 1 |
| 7 | **guard** | phase 6 |
| 8 | camera | |
| 9 | **link/move** | phase 7 |
| 10 | **run** | phase 8 |
| 11 | **fusion** | phase 9 |
| 12 | special command | PC: phase 10 kind 2 ; fusion monster: phase 5 (id match) or 10 kind 3 |
| 13 | tarot | phase 0xd |
| 14 | aroma | phase 0xc |
| 15 | | phase 10 step 0x14 kind 6 |
| 16 | combo member camera | |
| 17 | ring skill | phase 0xb kind 4 |
| 18 | dim non-target models, show target ring | |
| 19 | target camera by shape `e` (0 single, 1 circle, 3 straight, 4 straight-EX, 5 all) | |
| 20 | store selection bytes at `+0x45ec..0x45ef` for the short-cut | |
| 21 | | `step = 0x15` |
| 23 | menu destroyed | `+0x4384 = 0` |

Menu structure (`BtlMenu`: `SetMainMenu` 0x005adc70 is 0xd470 bytes, `SetTargetMenu`, `SetMagicMenu`, `SetItemMenu`, `SetSkill1Menu`, `SetComboSkillMenu`,
`SetBaseAromaMenu/SetAddAromaMenu`, `SetComboShortCutMenu`, `SetFusionMenu`, `SetGuardMenu`, `SetMoveMenu`, `SetTutorialMenu`, windows `BMesWin`, cursor `BCursole`):
labels `BtlMenuItem_J` — 0 Attack, 1-4 Standard/Hard Hit/High Angle/Knock Down (attack shape; matching judgement-ring results ST/HH/HA/KD),
5 Combo Magic, 6 Crest Magic, 7 Formation, 8 Item, 9 Guard, 10 Link, 11 Run, 12 Fusion, 13 Paranormal, 14 Marionette, 15 Tarot, 16 Aroma, 17 Snap,
18 Album, 19 Sword Art, 20 Muscle Arts, 21 Incarnation, 22-24 Grenade, 25 White Magic, 26 Special (fusion-monster ability).
Port: `flow::CommandMenu` / `MenuEvent` / `MenuEvent::apply`.

## 4. Support objects (all `CPolObj` descendants entered into the game poller)
ParamDisp (party HP/MP/SP panel), TurnOrderDisp (timeline), ComboForm (combo ring/area), HitInfo/TotalHitInfo/HitCntEff/HitMark/HitImpact (damage numbers, hit counter),
TargetInfo, AbnIcon (status icons), CmbBreak/BreakBBox (death break), DownSmoke…, Sword/Fan/Whip/BlowLocusEffect (weapon trails), *AddAttribute1 (elemental weapon glow),
Bullet1-4 (+Child), CircleArea/StraightArea/StraightCircleArea (target markers), NormalDeathEfct, MgcInvkParticle, BtlBlear, CBtlPAfter/CBtlPAfter2 (post effects),
BtlScrnCapture (screen capture for the ring), BtlCamera (cameras per situation, 25 setters), BtlModel (battle model with weapon models & bounding boxes), BtlBG (background),
EffMdl (effect model), BtlEff (effect base).  All share the vtable shape `Polling / MakePacket / Destruct / EndSet / getPacket` (MakePacket builds VIF1 packets – GS layer = sections B/D).
