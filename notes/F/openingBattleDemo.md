# openingBattleDemo

Base class: `CPolObj`

Attract-mode battle: builds a party in the MENU section, configures `BtlSocket` (SetPC, SetMonsterSet from RegDat 0x2f, BGM) and lets BATTLE.BIN run an AI-controlled fight; cycles three setups (`m_mons`).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x1c | `s32` | state |
| 0x20 | `u8` | btl_done |
| 0x21 | `u8` | not_skipped |
| 0x22 | `u8` | go |
| 0x23 | `u8` | finished |
| 0x24 | `s32` | timer |
| 0x28 | `s32` | battle_no |
| 0x2c | `s32` | bgm |
| 0x30 | `s32` | monset |
| 0x34 | `prim2D *` | banner |
| 0x38 | `prim2D *` | p38 |
| 0x3c | `prim2D *` | p3c |
| 0x40 | `s32` | tex |
| 0x44 | `s32` | layer |

## Virtual table (`__vt__openingBattleDemo`)

| slot | function |
|---|---|
| 0x08 | `__dt__17openingBattleDemoFv` |
| 0x0c | `Polling__17openingBattleDemoFv` |

## Constructed by

`Polling__14openingMessageFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003ab510 | 0x78 | `__ct__17openingBattleDemoFv` | `openingBattleDemo::openingBattleDemo()` |
| 0x003ab590 | 0x84 | `__dt__17openingBattleDemoFv` | `openingBattleDemo::~openingBattleDemo()` |
| 0x003ab620 | 0x20 | `start__17openingBattleDemoFv` | `openingBattleDemo::start()` |
| 0x003ab640 | 0x1b4 | `initialize__17openingBattleDemoFPUci` | `openingBattleDemo::initialize(unsigned char*, int)` |
| 0x003ab800 | 0x4c0 | `Polling__17openingBattleDemoFv` | `openingBattleDemo::Polling()` |
| 0x003abcc0 | 0x38 | `BtlCallBack__17openingBattleDemoFiiPv` | `openingBattleDemo::BtlCallBack(int, int, void*)` |
| 0x003abd00 | 0x40 | `BtlCBFunc__17openingBattleDemoFii` | `openingBattleDemo::BtlCBFunc(int, int)` |

## Rust port

`title::OpeningBattleDemo`, `DEMO_BATTLES`.

## Open questions

- none recorded

Decompilation: `decomp/F/openingBattleDemo.c`
