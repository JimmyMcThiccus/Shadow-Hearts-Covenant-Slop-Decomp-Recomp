# GameOver

Base class: `Menu`

`Menu` subclass created by `SSHSys::PollingApi` on state 0x30; creates its `GameOverScene` (`MENU/MSD/GAMEOVER.MSD`) and a default `GsxCamera` if none exists. `ReceiveEvent(event, menu)` is the `dataAccess` callback (4 finished, 5 loaded).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x50 | `GsxCamera *` | cam |

## Virtual table (`__vt__GameOver`)

| slot | function |
|---|---|
| 0x08 | `__dt__8GameOverFv` |
| 0x0c | `Polling__8GameOverFv` |
| 0x18 | `@24@__dt__8GameOverFv` |
| 0x1c | `@24@DelayDelete__8GameOverFv` |
| 0x20 | `Create__4MenuFP9BufMemory` |
| 0x24 | `Active__4MenuFs` |
| 0x28 | `Ready__4MenuFsss` |
| 0x2c | `GetKey__4MenuFv` |
| 0x30 | `DelayDelete__8GameOverFv` |

## Constructed by

`PollingApi__6SSHSysFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003abe10 | 0x8c | `ReceiveEvent__8GameOverFiPv` | `GameOver::ReceiveEvent(int, void*)` |
| 0x003abea0 | 0x298 | `__ct__8GameOverFv` | `GameOver::GameOver()` |
| 0x003ac140 | 0x84 | `__dt__8GameOverFv` | `GameOver::~GameOver()` |
| 0x003ac1d0 | 0x2c | `Polling__8GameOverFv` | `GameOver::Polling()` |
| 0x003ac200 | 0x4c | `DelayDelete__8GameOverFv` | `GameOver::DelayDelete()` |
| 0x003ac250 | 0x8 | `@24@DelayDelete__8GameOverFv` | `@24@DelayDelete__8GameOverFv` |
| 0x003ac260 | 0x8 | `@24@__dt__8GameOverFv` | `@24@__dt__8GameOverFv` |

## Rust port

`gameover::GameOverScene`.

## Open questions

- none recorded

Decompilation: `decomp/F/GameOver.c`
